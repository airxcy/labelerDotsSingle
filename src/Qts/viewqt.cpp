#include "Qts/viewqt.h"
#include "Qts/modelsqt.h"
#include "Qts/streamthread.h"

#include <iostream>

#include <QPainter>
#include <QBrush>
#include <QPixmap>
#include <cmath>
#include <QGraphicsSceneEvent>
#include <QMimeData>
#include <QByteArray>
#include <QFont>
char viewstrbuff[200];
void GraphicsView::resizeEvent(QResizeEvent * evt)
{

}
void DefaultScene::mousePressEvent ( QGraphicsSceneMouseEvent * event )
{
    emit clicked(event);
}
void DefaultScene::drawBackground(QPainter * painter, const QRectF & rect)
{
    QPen pen;
    QFont txtfont("Roman",40);
    txtfont.setBold(true);
    pen.setColor(QColor(255,255,255));
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);
    pen.setWidth(10);
    painter->setPen(QColor(243,134,48,150));
    painter->setFont(txtfont);
    painter->drawText(rect, Qt::AlignCenter,"打开文件\nOpen File");
}
TrkScene::TrkScene(const QRectF & sceneRect, QObject * parent):QGraphicsScene(sceneRect, parent)
{
    streamThd=NULL;
    isEditing=false;
    focusidx=-1;
    bb_N=0;
    pendingN=0;
    txtfont=QFont("System", 11);
}
TrkScene::TrkScene(qreal x, qreal y, qreal width, qreal height, QObject * parent):QGraphicsScene( x, y, width, height, parent)
{
    streamThd=NULL;
    isEditing=false;
    focusidx=-1;
    bb_N=0;
    pendingN=0;
    txtfont=QFont("System", 12);
    roidone=false;
}
void TrkScene::drawBackground(QPainter * painter, const QRectF & rect)
{
    if(streamThd!=NULL&&streamThd->inited)
    {
        updateFptr(streamThd->frameptr, streamThd->frameidx);
    }
    painter->setBrush(bgBrush);
    painter->drawRect(rect);
    painter->setPen(QColor(120,180,150));
    painter->setFont(txtfont);
    sprintf(viewstrbuff,"Frame %d|target目标ID:%d\0",frameidx,editidx);
    painter->drawText(QRectF (0,0,width(),height()), Qt::AlignLeft|Qt::AlignTop, viewstrbuff);

    if(roivec.size()>0)
    {
        painter->setPen(Qt::blue);
        if(isEditing)painter->setPen(Qt::white);
        DragDots* dot = roivec[0];
        int prex=dot->coord[0],prey=dot->coord[1];
        for(int i=0;i<roivec.size();i++)
        {
            dot = roivec[i];
            int x=dot->coord[0],y=dot->coord[1];
            painter->drawLine(prex,prey,x,y);
            prex=x,prey=y;
        }
        if(roidone)
        {
            DragDots* dot = roivec[0];
            int x=dot->coord[0],y=dot->coord[1];
            painter->drawLine(prex,prey,x,y);
        }
    }

    views().at(0)->update();
    update();

}
/*
void TrkScene::drawItems(QPainter *painter, int numItems,QGraphicsItem *items[],const QStyleOptionGraphicsItem options[],QWidget *widget)
{

    QGraphicsScene::drawItems(painter,numItems,items,options,widget);
    views().at(0)->update();
    update();

}
*/
/*
void TrkScene::drawForeground(QPainter * painter, const QRectF & rect)
{
    update(sceneRect());
    //views().at(0)->updateScene(sceneRect());

}
*/
void TrkScene::updateFptr(unsigned char * fptr,int fidx)
{
    bgBrush.setTextureImage(QImage(fptr,streamThd->framewidth,streamThd->frameheight,QImage::Format_RGB888));
    frameidx=fidx;
}
int TrkScene::init()
{
    if(streamThd!=NULL)
    {
        editidx=streamThd->editidx;
        while(bb_N<streamThd->bb_N)
        {
            int bb_i=bb_N;
            addADot(0,0);
            dotvec[bb_i]->setVisible(false);
            dotvec[bb_i]->ismovable=false;
            dotvec[bb_i]->isGood=true;
            if(bb_i==editidx)
            {
                dotvec[bb_i]->ismovable=true;
                dotvec[bb_i]->isGood=false;
                dotvec[bb_i]->range=10;
                //dotvec[bb_i]->setCoord(framewidth,frameheight);
            }
            //dotvec[bb_i]->setVisible(true);
            dotvec[bb_i]->setClr(feat_colos[bb_i%6][0],feat_colos[bb_i%6][1],feat_colos[bb_i%6][2]);
            dotvec[bb_i]->pid=bb_i;
        }
        if(!roidone&&streamThd->roidone)
        {
            for(int i=0;i<streamThd->roi.size();i++)
            {
                cv::Point2i& t = streamThd->roi[i];
                int x = t.x,y=t.y;
                DragDots* newdot = new DragDots(x,y);
                newdot->setClr(0,0,0);
                newdot->pid = roivec.size();
                sprintf(newdot->txt,"%d\0",newdot->pid);
                roivec.push_back(newdot);
            }
            roidone=true;
        }
        return 1;
    }
    return 0;
}
void TrkScene::startTrk(int bb_i)
{
    std::cout<<QThread::currentThreadId()<<std::endl;
    dotvec[editidx]->isGood=true;
    dotvec[bb_i]->setVisible(true);
}
void TrkScene::endTrk(int bb_i)
{
    dotvec[bb_i]->setVisible(true);
    dotvec[bb_i]->isGood=false;
}
void TrkScene::clear()
{

    for(int bb_i=0;bb_i<bb_N;bb_i++)
    {
        dotvec[bb_i]->ismovable=false;
        dotvec[bb_i]->isGood=false;
        dotvec[bb_i]->setVisible(false);
    }
    bb_N=0;
    mouseclicked=false;
    isEditing=false;
    //roidone=false;
}
void TrkScene::dragBBclicked(int bbidx)
{
    if(isEditing)
    {
    }
}
void TrkScene::startEdit()
{
    if(streamThd!=NULL)
    {
        if(streamThd->isTagging)
            isEditing=true;
        mouseclicked=false;
    }
}
void TrkScene::addADot(int x,int y)
{
    if(bb_N<dotvec.size())
    {
        DragDots* newdot= dotvec[bb_N];
        newdot->setClr(feat_colos[bb_N%6][0],feat_colos[bb_N%6][1],feat_colos[bb_N%6][2]);
        newdot->pid=bb_N;
        sprintf(newdot->txt,"%d\0",bb_N%100);

        newdot->setCoord(width(),height());
        newdot->setVisible(true);
        newdot->setCoord(width()/2,height()/2);
        newdot->setVisible(true);
        update();
    }
    else
    {
        DragDots* newdot = new DragDots(x,y);
        newdot->setClr(feat_colos[bb_N%6][0],feat_colos[bb_N%6][1],feat_colos[bb_N%6][2]);
        newdot->pid=bb_N;
        sprintf(newdot->txt,"%d\0",bb_N%100);
        dotvec.push_back(newdot);
        addItem(newdot);
        newdot->setCoord(width(),height());
        newdot->setVisible(true);
        newdot->setCoord(width()/2,height()/2);
        newdot->setVisible(true);
        update();
    }
    bb_N++;

}
void TrkScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()==Qt::LeftButton&&isEditing)
    {
        int x = event->scenePos().x(),y=event->scenePos().ry();
        if(dotvec[editidx]->isGood)
        {
        }
        else
        {
            dotvec[editidx]->isGood=true;
            dotvec[editidx]->setVisible(true);
        }
        //emit litDot(editidx);
        //dotvec[editidx]->setVisible(true);
        dotvec[editidx]->setCoord(x,y);
        QGraphicsScene::mousePressEvent(event);
        mouseclicked=true;
        //update();
        //views().at(0)->update();w
    }
    else if(event->button()==Qt::LeftButton&&!isEditing&&!roidone)
    {
        int x = event->scenePos().x(),y=event->scenePos().ry();
        DragDots* newdot = new DragDots(x,y);
        newdot->setClr(0,0,0);
        newdot->pid = roivec.size();
        sprintf(newdot->txt,"%d\0",newdot->pid);
        roivec.push_back(newdot);
        addItem(newdot);
    }
}
void TrkScene::addDragDot(int x,int y)
{
    addADot( x,y);
}

RefScene::RefScene(const QRectF & sceneRect, QObject * parent):QGraphicsScene(sceneRect, parent)
{
    streamThd=NULL;
    trkscene=NULL;
    dot=NULL;
    dot = new Dot(0,0);
    addItem(dot);
    dot->setVisible(true);
}
RefScene::RefScene(qreal x, qreal y, qreal width, qreal height, QObject * parent):QGraphicsScene( x, y, width, height, parent)
{
    streamThd=NULL;
    trkscene=NULL;
    dot=NULL;
    dot = new Dot(0,0);
    addItem(dot);
    dot->setVisible(true);
}
void RefScene::snapshot()
{
    if(streamThd!=NULL)
    {
        QImage tmpimg(streamThd->frameptr,streamThd->framewidth,streamThd->frameheight,QImage::Format_RGB888);
        bgimg = tmpimg.copy();
        setBackgroundBrush(bgimg);
        if(trkscene!=NULL)
        {
            DragDots* tmpdot = trkscene->dotvec[trkscene->editidx];
            int x = tmpdot->coord[0], y =tmpdot->coord[1];
            dot->setClr(tmpdot->rgb[0],tmpdot->rgb[1],tmpdot->rgb[2]);
            dot->pid=tmpdot->pid;
            sprintf(dot->txt,"%d\0",dot->pid);
            dot->setCoord(x,y);
            views().at(0)->centerOn( x, y);

        }
        views().at(0)->update();
    }

}
