#include "Qts/streamthread.h"

#include "Qts/viewqt.h"
#include "Qts/modelsqt.h"

#include <iostream>
#include <fstream>
//#include <stdlib.h>

//#include <direct.h>

#include <opencv2/opencv.hpp>
#include <QMessageBox>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QStringList>

using namespace cv;

VideoCapture cap;
Mat frame;
float fps=0;
char strbuff[100];
QDir qdirtmp;
StreamThread::StreamThread(QObject *parent) : QThread(parent)
{
    restart = false;
    abort = false;
    pause = false;
    bb_N=0,bufflen=0;
    trkscene=NULL;
    justUpdated=false;
    paused=false;
    isTagging=false;
    checking=true;
    replaying=true;
    inited=false;
    framebuff=NULL;
    firsttime=true;
    roidone=false;
    nextframeidx=0;
}
StreamThread::~StreamThread()
{
    /*
    mutex.lock();
    abort = true;
    condition.wakeOne();
    mutex.unlock();
    wait();
    */
    //QMutexLocker lock(&mutex);
    abort = true;
    cv0.wakeAll();
    wait();
}

bool StreamThread::init()
{
    //QMutexLocker lock(&mutex);

    restart=false,abort=false,pause=false,isTagging=false,paused=false,saveLast=false;
    bufflen=0,maxframe=0,maxskeyframe=0;
    //cap.open("C:/Users/xcy/Documents/CVProject/data/grandcentral/grandcentral.avi");
//    if(cap.isOpened())
//        cap.set(CV_CAP_PROP_POS_AVI_RATIO,0);
//    else
    if(!cap.isOpened())
    {
        cap.open(vidfname);
        std::cout<<"reopened"<<std::endl;
    }
    cap.set(CV_CAP_PROP_POS_FRAMES,nextframeidx);
    frameidx=nextframeidx;
    maxframe=cap.get(CV_CAP_PROP_FRAME_COUNT );
    int fps = cap.get(CV_CAP_PROP_FPS);
    std::cout<<"fps:"<<fps<<std::endl;
    parsefname();
    parsegt();
    cap>>frame;
    delay=25;
    bufflen=delay+10;
    maxskeyframe=maxframe/delay;
    cvtColor(frame,frame,CV_BGR2RGB);

    framewidth=frame.size[1],frameheight=frame.size[0];
    if(framebuff==NULL)
    {
        framebuff = new FrameBuff();
        framebuff->init(frame.elemSize(),framewidth,frameheight,bufflen);
    }
    else
        framebuff->clear();

    frameByteSize=frame.size[0]*frame.size[1]*frame.elemSize();
    framebuff->updateAFrame(frame.data);
    frameptr=framebuff->cur_frame_ptr;
    delayedFrameptr=framebuff->headptr;
    inited=true;
    firsttime=false;
    return cap.isOpened();
}
void StreamThread::updateItems()
{
    if(trkscene!=NULL)
    {
        //std::cout<<"updateItems"<<std::endl;
        if(isTagging)
        {
            int x1,y1,bb_i=trkscene->bb_N;
            DragDots * ddots = trkscene->dotvec[editidx];
            TrackBuff* trk = trackBuff[editidx];
            x1=ddots->coord[0],y1=ddots->coord[1];
            if(ddots->isGood)
            {
                if(trk->len<=0)
                {
//                    pttmp.x=x1,pttmp.y=y,pttmp.t=frameidx;
//                    trk->updateAFrame(&pttmp);
                }
                else
                {
                    int x0,y0;
                    TrkPts_p ptptr = trk->cur_frame_ptr;
                    x0=ptptr->x,y0=ptptr->y;
                    double intvlen=frameidx-lastframeidx+1;
                    for(int fidx=lastframeidx,llen=1;fidx<frameidx;fidx++,llen++)
                    {
                        double wa=llen/intvlen,wb=(intvlen-llen)/intvlen;
                        int x=x0*wb+x1*wa+0.5,y=y0*wb+y1*wa+0.5;
                        pttmp.x=x,pttmp.y=y,pttmp.t=fidx;
                        trk->updateAFrame(&pttmp);
                    }
                }
                pttmp.x=x1,pttmp.y=y1,pttmp.t=frameidx;
                trk->updateAFrame(&pttmp);
            }
            lastframeidx=frameidx+1;
            justUpdated=true;
        }
    }
}
void StreamThread::parsefname()
{
    char drive[100],dir[100],fname[100],ext[100];
    _splitpath(vidfname.data(),drive,dir,fname,ext);
    baseDirname=drive;
    baseDirname=baseDirname+dir;
    vidid=fname;
    ext[0]='_';
    vidid=vidid+ext;
    gtdir=baseDirname+vidid+"/";
    qdirstr=baseDirname+vidid+"/";
}
void StreamThread::getroi()
{
    if(trkscene!=NULL)
    {
        for(int i=0;i<trkscene->roivec.size();i++)
        {
            DragDots* dot = trkscene->roivec[i];
            int x=dot->coord[0],y=dot->coord[1];
            roi.push_back(Point2i(x,y));
        }
        /*
        qdirtmp.mkpath(gtdir.data());
        std::string savefname=gtdir+"roi.txt";
        std::ofstream outfile;
        outfile.open(savefname);
        outfile<< roi.size()<<std::endl;
        int x,y,fidx;
        std::string writestring;
        for(int i=0;i<roi.size();i++)
        {
            Point2i& ptr = roi[i];
            x=ptr.x,y=ptr.y;
            sprintf(strbuff,"%d,%d\0",x,y);
            writestring=strbuff;
            outfile << writestring<<std::endl;
        }
        */
        //QString qdirstr(gtdir.c_str());
        qdirtmp.mkpath(qdirstr);
        QString savefname=qdirstr+"roi.txt";
        QFile qoutfile(savefname);
        qoutfile.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream outts(&qoutfile);
        outts<< roi.size()<<"\n";
        int x,y;
        for(int i=0;i<roi.size();i++)
        {
            Point2i& ptr = roi[i];
            x=ptr.x,y=ptr.y;
            outts<<x<<","<<y<<"\n";
        }
        trkscene->roidone=true;
    }
}
void StreamThread::saveBBTrack(std::string& dir)
{
    pause=true;
    if(bb_N>0)
    {
        qdirtmp.mkpath(qdirstr);
        QString savefname;

        int bb_i=editidx;
        sprintf(strbuff,"%06d.txt\0",bb_i);
        savefname=qdirstr+strbuff;
        if(trackBuff[bb_i]->len>0)
        {
            QFile qoutfile(savefname);
            qoutfile.open(QIODevice::WriteOnly | QIODevice::Text);
            TrackBuff* bbtrkptr= trackBuff[bb_i];
            QTextStream outts(&qoutfile);
            outts<< bbtrkptr->len<<"\n";
            int x,y,fidx;
            for(int i=0;i<bbtrkptr->len;i++)
            {
                TrkPts_p bbptr = bbtrkptr->getPtr(i);
                x=bbptr->x+0.5,y=bbptr->y+0.5,fidx=bbptr->t;
                outts<<x<<","<<y<<","<<fidx<<"\n";
            }
            qoutfile.close();
        }
    }
}
double StreamThread::checkroi(int x, int y)
{
    if(roidone)
        return pointPolygonTest(roi,Point2f(x,y),1);
    return 1;
}
void StreamThread::parsegt()
{
    if(firsttime)
    {
        sprintf(strbuff,"%06d.txt\0",bb_N);
        QString savefname=qdirstr+strbuff;
        QFile qinfile(savefname);
        while(qinfile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream ints(&qinfile);
            int len=0;
            QString line = qinfile.readLine();
            len = line.toInt();
            TrackBuff * abbtrk =new TrackBuff();
            abbtrk->init(1,100);
            int x,y,fidx;
            for (int i = 0; i < len; i++)
            {
                line = qinfile.readLine();
                QStringList list = line.split(",", QString::SkipEmptyParts);
                pttmp.x=list[0].toInt(),pttmp.y=list[1].toInt(),pttmp.t=list[2].toInt();
                abbtrk->updateAFrame(&pttmp);
            }
            trackBuff.push_back(abbtrk);
            qinfile.close();
            std::cout<<bb_N<<",";
            bb_N++;
            sprintf(strbuff,"%06d.txt\0",bb_N);
            savefname=qdirstr+strbuff;
            qinfile.setFileName(savefname);
        }
        qinfile.close();
        std::cout<<std::endl;
    }
    if(bb_N<=0||trackBuff[bb_N-1]->len>0)
    {
        editidx=bb_N;
        TrackBuff* newtrk = new TrackBuff();
        newtrk->init(1,100);
        trackBuff.push_back(newtrk);
        bb_N++;
    }
    else
    {
        std::cout<<"-1len:"<<std::endl;
        editidx=bb_N-1;
    }
    std::cout<<"editidx:"<<editidx<<"len:"<<trackBuff[editidx]->len<<std::endl;
    if(!roidone)
    {
        QString savefname=qdirstr+"roi.txt";
        QFile qinfile(savefname);
        if(qinfile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            int len=0;
            QString line = qinfile.readLine();
            len = line.toInt();
            int x,y,fidx;
            for (int i = 0; i < len; i++)
            {
                line = qinfile.readLine();
                QStringList list = line.split(",", QString::SkipEmptyParts);
                roi.push_back(Point2i(list[0].toInt(),list[1].toInt()));
            }
            roidone=true;
        }
    }
}
void StreamThread::updateRefscene()
{
    delayedFrameptr=frameptr;
    if(bb_N>0)
    {
        //std::cout<<"updateRefscene"<<std::endl;
        for(int bb_i=0;bb_i<bb_N;bb_i++)
        {
            TrackBuff* bbtrkptr = trackBuff[bb_i];
            if(trackBuff[bb_i]->len>0 && bb_i!=editidx)
            {
                TrkPts_p bbptr=bbtrkptr->data;
                int startfidx = bbptr->t,len = bbtrkptr->len;
                DragDots* ddot = trkscene->dotvec[bb_i];
                if(frameidx==startfidx)
                {
                    ddot->setVisible(true);
                    //emit trkStart(bb_i);
                    ddot->setCoord(bbptr->x,bbptr->y);
                }
                else if(frameidx==startfidx+len)
                {
                    ddot->setVisible(false);
                    //emit trkEnd(bb_i);
                }
                else if(frameidx>startfidx&&frameidx<startfidx+len)
                {

                    if(!ddot->isVisible())
                        ddot->setVisible(true);
                        //emit trkStart(bb_i);
                    bbptr=bbtrkptr->getPtr(frameidx-startfidx);
                    ddot->setCoord(bbptr->x,bbptr->y);
                }
            }
        }
    }
}
void StreamThread::setPos(int stepPos)
{
    if(!isTagging)
    {
        nextframeidx=stepPos*delay;
        //cap.set(CV)
        //cap.set(CV_CAP_PROP_POS_AVI_RATIO,nextframeidx);
        std::cout<<nextframeidx<<std::endl;
    }
}
void StreamThread::streaming()
{
    forever
    {
        if(init())
        {
            emit initSig();
            //frameidx=0;
            lastframeidx=frameidx;
            while(!frame.empty())
            {
                if (restart)
                        break;
                if (abort)
                        return;
                if (pause)
                {
                    mutex.lock();
                    paused=true;
                    cv0.wait(&mutex);
                    paused=false;
                    mutex.unlock();
                }
                cap >> frame;
                if(frame.empty())
                    break;
                cvtColor(frame,frame,CV_BGR2RGB);
                framebuff->updateAFrame(frame.data);
                frameptr=framebuff->cur_frame_ptr;
                frameidx++;
                //std::cout<<cap.get(CV_CAP_PROP_POS_FRAMES)<<","<<frameidx<<std::endl;
                updateRefscene();
                if(frameidx%delay==0)
                {

                    pause=true;
                    emit stepReached();
                }
                msleep(10);
            }
        }
        else
        {
            //emit debug( "init Failed");
        }
        /*
        for(int i=0;i<bb_N;i++)
        {
            delete trackBuff[i];
        }
        trackBuff.clear();
        bb_N=0;
        */
        if(saveLast)
        {
            std::string dirpath;
            saveBBTrack(dirpath);
        }
        else
        {
            trackBuff[editidx]->clear();
        }
        trkscene->clear();
        saveLast=false;
        inited=false;
        /*
        mutex.lock();
        if (!restart)
            condition.wait(&mutex);
        restart = false;
        mutex.unlock();
        */
    }
}
void StreamThread::abandon()
{
    if(inited&&bb_N>0)
    {
        delete trackBuff[editidx];
        trackBuff.pop_back();
        bb_N--;
    }
}
void StreamThread::run()
{
    streaming();
}

void StreamThread::streamStart(std::string & filename)
{
    QMutexLocker locker(&mutex);
    //QMessageBox::question(NULL, "Test", "msg",QMessageBox::Ok);
    if (!isRunning()) {
        vidfname=filename;
        start(InheritPriority);
    }
    else
    {
        restart=true;
    }
}
