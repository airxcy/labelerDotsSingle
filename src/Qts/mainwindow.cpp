#include "Qts/mainwindow.h"
#include "Qts/streamthread.h"
#include "Qts/viewqt.h"
#include "Qts/modelsqt.h"

//#include <direct.h>

#include <QtWidgets>
#include <QSizePolicy>
#include <iostream>
#include <QPalette>
#include <QKeySequence>
#include <QFontDatabase>
#include <QStringList>
//! [1]
char cbuff[200];
MainWindow::MainWindow()
{
    cWidget = new QWidget(this);
    setCentralWidget(cWidget);
    updaderidx=0;
    streamThd = new StreamThread(this);
    setStyleSheet("QWidget { background-color: rgb(105,210,231); }");
    cWidget->setStyleSheet("QWidget { background-color: rgb(105,210,231); }");
    setupLayout();
    makeConns();
    //setWindowFlags(Qt::FramelessWindowHint);
    setStyleSheet(" QPushButton:disabled {background: rgba(0,0,0,100)}");
    setFixedSize(cWidget->minimumSize());
    //cWidget->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    move(100, 0);
    firsttime=true;

}
void MainWindow::setupLayout()
{
    /** add font **/
    int fontid = QFontDatabase::addApplicationFont(":/fonts/Minecrafter.Alt.ttf");
    fontid = QFontDatabase::addApplicationFont(":/fonts/DJBAlmostPerfect.ttf");
    fontid = QFontDatabase::addApplicationFont(":/fonts/Precursive_1_FREE.otf");
    QStringList fontstr = QFontDatabase::applicationFontFamilies(fontid);
    for(int i =0;i<fontstr.length();i++)
    {
        std::cout<<fontstr.at(i).toStdString()<<std::endl;
    }

    /** layout **/
    layout=new QGridLayout(cWidget);
    layout->setSizeConstraint(QLayout::SetFixedSize);
    cWidget->setLayout(layout);
    cWidget->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    int frameGridSize=1;

    /** scroll area **/
    scrollarea = new QScrollArea(cWidget);
    scrollarea->setFixedSize(900,240);
    layout->addWidget(scrollarea,0,0,1,frameGridSize,Qt::AlignCenter);
    scrollwidget = new QWidget(scrollarea);
    scrollarea->setWidget(scrollwidget);
    layout1 =new QGridLayout(scrollwidget);
    scrollwidget->setLayout(layout1);
    layout1->setSizeConstraint(QLayout::SetFixedSize);
    scrollwidget->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);


    /** views **/
    defaultscene = new DefaultScene(0, 0, 440, 240);
    gview = new GraphicsView(defaultscene,scrollwidget);
    gview->setFixedSize(defaultscene->width()+2,defaultscene->height()+2);
    gview->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    refview[0] = new GraphicsView(new QGraphicsScene(0, 0, 440, 240),scrollwidget);
    refview[0]->setFixedSize(200,200);
    refview[0]->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    refview[0]->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    refview[1] = new GraphicsView(new QGraphicsScene(0, 0, 440, 240),scrollwidget);
    refview[1]->setFixedSize(200,200);
    refview[1]->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    refview[1]->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    refview[2] = new GraphicsView(new QGraphicsScene(0, 0, 440, 240),scrollwidget);
    refview[2]->setFixedSize(200,200);
    refview[2]->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    refview[2]->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    layout1->addWidget(gview,0,0,3,frameGridSize,Qt::AlignTop);
    layout1->addWidget(refview[0],0,frameGridSize,1,frameGridSize,Qt::AlignTop);
    layout1->addWidget(refview[1],1,frameGridSize,1,frameGridSize,Qt::AlignTop);
    layout1->addWidget(refview[2],2,frameGridSize,1,frameGridSize,Qt::AlignTop);
    layout1->setMargin(0);
    layout1->setSpacing(0);

    scrollarea->setFixedHeight(240+20);




    /** buttons **/
    blayout0 = new QBoxLayout(QBoxLayout::LeftToRight,cWidget);
    layout->addLayout(blayout0,1,0,1,frameGridSize);
    blayout = new QBoxLayout(QBoxLayout::LeftToRight,cWidget);

    QString btnstyle = "QPushButton { background: rgba(243,134,48,100); color:rgba(243,134,48); padding: 3px;} QPushButton:disabled{background: rgba(0,0,0,50)}";
    QFont btnfont("PreCursive",20);
    btnfont.setBold(true);

    int btnHt=30,startidx=0;
    startTag = new QPushButton(cWidget);
    startTag->setStyleSheet(btnstyle);
    startTag->setText("开始当前桢");
    startTag->setFont(btnfont);
    startTag->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    startTag->setShortcut(QKeySequence("w"));
    blayout0->addWidget(startTag);
    editTag = new QPushButton(cWidget);
    editTag->setStyleSheet(btnstyle+"QPushButton { background: rgba(255,0,255,200);}");
    editTag->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    editTag->setText("下一桢");
    editTag->setShortcut(QKeySequence(" "));
    editTag->setFont(btnfont);
    blayout0->addWidget(editTag);
    relabelBtn = new QPushButton(cWidget);
    relabelBtn->setStyleSheet(btnstyle+"QPushButton { background: rgba(255,0,255,200);}");
    relabelBtn->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    relabelBtn->setText("重标目标");
    relabelBtn->setShortcut(QKeySequence("p"));
    relabelBtn->setFont(btnfont);
    blayout0->addWidget(relabelBtn);
    saveBtn = new QPushButton(cWidget);
    saveBtn->setStyleSheet(btnstyle);
    saveBtn->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    saveBtn->setText("完成一个保存");
    saveBtn->setFont(btnfont);
    blayout0->addWidget(saveBtn);
    roiBtin = new QPushButton(cWidget);
    roiBtin->setStyleSheet(btnstyle);
    roiBtin->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    roiBtin->setText("setRoi");
    roiBtin->setFont(btnfont);
    blayout0->addWidget(roiBtin);
    framedoneBtn = new QPushButton(cWidget);
    framedoneBtn->setStyleSheet(btnstyle);
    framedoneBtn->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    framedoneBtn->setText("这帧标满");
    framedoneBtn->setFont(btnfont);
    blayout0->addWidget(framedoneBtn);

    layout->addLayout(blayout,2,0,1,frameGridSize);
    slider =new QSlider(Qt::Horizontal,this);
    slider->setMaximum(100);
    slider->setTickPosition(QSlider::TicksBelow);
    slider->setEnabled(false);
    slider->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Minimum);
    blayout->addWidget(slider);
    label=new QLabel(this);
    label->setText("0/0");
    label->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    blayout->addWidget(label);

    //blayout0->addStretch();
    btnfont.setPixelSize(20);
    startidx=frameGridSize;
    btnHt=40;

    scrollarea->horizontalScrollBar()->setValue(0);
    scrollarea->verticalScrollBar()->setValue(0);
}
void MainWindow::makeConns()
{
    connect(defaultscene,SIGNAL(clicked(QGraphicsSceneMouseEvent *)),this,SLOT(gviewClicked(QGraphicsSceneMouseEvent *)));
    connect(streamThd,SIGNAL(initSig()),this,SLOT(initUI()),Qt::BlockingQueuedConnection);
}
void MainWindow::gviewClicked(QGraphicsSceneMouseEvent * event)
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open vid"), "../", tr("Vid Files (*.avi *.mp4 *.mkv *.mts)"));
    if(!fileName.isEmpty())
    {
        streamThd->streamStart(fileName.toStdString());
    }
}

void MainWindow::initUI()
{
    int fw=streamThd->framewidth,fh=streamThd->frameheight;
    if(firsttime)
    {
        QDesktopWidget *dwsktopwidget = QApplication::desktop();
        QRect deskrect = dwsktopwidget->availableGeometry();
        QRect screenrect = dwsktopwidget->screenGeometry();
        int scrcount = dwsktopwidget->screenCount();
        qCritical("screenrect.w==%s,",qPrintable(QString::number(screenrect.width())));
        qCritical("screenrect.h==%s\n",qPrintable(QString::number(screenrect.height())));
        qCritical("deskrect.w==%s,",qPrintable(QString::number(deskrect.width())));
        qCritical("deskrect.h==%s\n",qPrintable(QString::number(deskrect.height())));
        qCritical("scrcount==%s\n",qPrintable(QString::number(scrcount)));
        std::cout<<cWidget->minimumSize().width()<<","<<cWidget->minimumSize().height()<<std::endl;

        trkscene = new TrkScene(0, 0, fw, fh);
        refscene[0] = new RefScene(0, 0, fw, fh);
        refscene[1] = new RefScene(0, 0, fw, fh);
        refscene[2] = new RefScene(0, 0, fw, fh);
        trkscene->streamThd=streamThd;
        streamThd->trkscene=trkscene;
        refscene[0]->streamThd=streamThd;
        refscene[1]->streamThd=streamThd;
        refscene[2]->streamThd=streamThd;
        streamThd->refscene=refscene[0];
        trkscene->refscene=refscene[0];
        refscene[0]->trkscene=trkscene;
        refscene[1]->trkscene=trkscene;
        refscene[2]->trkscene=trkscene;

        gview->setFixedSize(fw+2,fh+2);

        gview->setScene(trkscene);
        refview[0]->setScene(refscene[0]);
        refview[1]->setScene(refscene[1]);
        refview[2]->setScene(refscene[2]);
        //refview->setFixedSize(fw+2,fh+2);
        scrollwidget->setFixedHeight(layout1->minimumSize().height());
        scrollarea->setFixedHeight(deskrect.height()-200);
        scrollarea->setFixedWidth(deskrect.width()-100);
        //scrollarea->setFixedHeight(scrollwidget->minimumHeight()+20);
        //scrollarea->setFixedWidth(fw+20+200);
        //scrollarea->horizontalScrollBar()->setValue(scrollarea->horizontalScrollBar()->maximum());
        scrollarea->horizontalScrollBar()->setValue(0);
        scrollarea->verticalScrollBar()->setValue(0);
        slider->setMaximum(streamThd->maxskeyframe);

        setWindowTitle(streamThd->vidid);
        move(50, 0);
        connect(startTag,SIGNAL(clicked()),this,SLOT(startTagging()));
        connect(editTag,SIGNAL(clicked()),this,SLOT(resume()));
        connect(saveBtn,SIGNAL(clicked()),this,SLOT(saveBBTrack()));
        //connect(streamThd,SIGNAL(stepReached()),trkscene,SLOT(startEdit()));//,Qt::BlockingQueuedConnection);
        connect(streamThd,SIGNAL(stepReached()),this,SLOT(stepReached()),Qt::BlockingQueuedConnection);
        //connect(slider,SIGNAL(sliderReleased()),this,SLOT(setVidPos()));
        connect(framedoneBtn,SIGNAL(clicked()),this,SLOT(frameDone()));
        connect(relabelBtn,SIGNAL(clicked()),this,SLOT(relabel()));
        //connect(streamThd,SIGNAL(trkStart(int )),trkscene,SLOT(startTrk(int )));
        //connect(streamThd,SIGNAL(trkEnd(int )),trkscene,SLOT(endTrk(int )));
        //connect(trkscene,SIGNAL(litDot(int )),trkscene,SLOT(startTrk(int )));
        if(!streamThd->roidone)
            connect(roiBtin,SIGNAL(clicked()),this,SLOT(setRoi()));

        trkscene->updateFptr(streamThd->frameptr,streamThd->frameidx);



        firsttime=false;
    }
    std::cout<<"mainThread ID:"<<QThread::currentThreadId()<<std::endl;
    sprintf(cbuff,"%06d/%06d",0,streamThd->maxframe);
    slider->setValue(0);
    label->setText(cbuff);


    trkscene->init();
    startTag->setEnabled(true);
    saveBtn->setEnabled(false);
    editTag->setEnabled(true);
    relabelBtn->setEnabled(true);
    framedoneBtn->setEnabled(true);

}

void MainWindow::startTagging()
{
    if(streamThd!=NULL && streamThd->paused)
    {
        streamThd->isTagging=true;
        trkscene->isEditing=true;
        startTag->setEnabled(false);
        editTag->setEnabled(true);
        saveBtn->setEnabled(true);
        relabelBtn->setEnabled(true);
        framedoneBtn->setEnabled(false);
        scrollarea->update();
    }
}
void MainWindow::resume()
{
    if(streamThd!=NULL&&streamThd->paused)
    {
        if(!streamThd->isTagging)
        {
            streamThd->pause=false;
            gview->update();
            streamThd->cv0.wakeAll();
        }
        else if(streamThd->isTagging && trkscene->mouseclicked )
        {
            int preidx= (updaderidx-1)%3;
            if(preidx>=0)
            {
                refview[0]->setScene(refscene[preidx]);
                refview[0]->centerOn(refscene[preidx]->dot->coord[0],refscene[preidx]->dot->coord[1]);
                refview[0]->update();
            }
            int curidx=(updaderidx)%3;
            if(curidx>=0)
            {
                refview[1]->setScene(refscene[curidx]);
                refview[1]->centerOn(refscene[curidx]->dot->coord[0],refscene[curidx]->dot->coord[1]);
                refview[1]->update();
            }
            //updaderidx=(updaderidx+1)%3;
            int nextidx=(updaderidx+1)%3;
            if(curidx>=0)
            {
            refview[2]->setScene(refscene[nextidx]);
            refscene[nextidx]->snapshot();
            updaderidx++;
            }
            streamThd->pause=false;
            streamThd->updateItems();
            trkscene->isEditing=false;
            gview->update();
            streamThd->cv0.wakeAll();
        }
    }
}
void MainWindow::saveBBTrack()
{
    if(streamThd!=NULL&&streamThd->trackBuff[streamThd->editidx]->len>0)
    {
        //std::string dirpath;//=streamThd->baseDirname+streamThd->vidid+"/";
        //streamThd->saveBBTrack(dirpath);
        //trkscene->clear();
        streamThd->saveLast=true;
        streamThd->isTagging=false;
        streamThd->restart=true;
        streamThd->pause=false;
        streamThd->cv0.wakeAll();
        std::cout<<"restarted"<<std::endl;
    }
}
void MainWindow::setVidPos()
{
    if(streamThd!=NULL&&streamThd->inited)
    {
        streamThd->setPos(slider->value());
    }
}
void MainWindow::stepReached()
{
    if(streamThd!=NULL)
    {
        trkscene->startEdit();
        int pos = streamThd->frameidx/streamThd->delay;
        slider->setValue(pos);
        sprintf(cbuff,"%06d/%06d",streamThd->frameidx,streamThd->maxframe);
        label->setText(cbuff);
    }
}
void MainWindow::setRoi()
{
    if(streamThd!=NULL&&!streamThd->isTagging&&trkscene->roivec.size()>0)
    {
        std::cout<<"seted"<<std::endl;
        streamThd->getroi();
        trkscene->roidone=true;
    }
}
void MainWindow::frameDone()
{
    if(streamThd!=NULL&&streamThd->frameidx>20&&streamThd->paused)
    {
        streamThd->nextframeidx=streamThd->frameidx-15;
        framedoneBtn->setEnabled(false);
        trkscene->clear();
        streamThd->isTagging=false;
        streamThd->restart=true;
        streamThd->pause=false;
        streamThd->cv0.wakeAll();
    }
}
void MainWindow::relabel()
{
    if(streamThd!=NULL&&streamThd->paused)//&&streamThd->isTagging)
    {
        //streamThd->trackBuff[streamThd->editidx]->clear();
        //trkscene->clear();
        streamThd->saveLast=false;
        streamThd->isTagging=false;
        streamThd->restart=true;
        streamThd->pause=false;
        streamThd->cv0.wakeAll();
    }
}
