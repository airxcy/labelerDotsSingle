#ifndef STREAMTHREAD
#define STREAMTHREAD

#include "trackers/buffers.h"
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <opencv2/core/core.hpp>

//class NoTracker;
class BBox;
class TrkScene;
class RefScene;
class StreamThread : public QThread
{
    Q_OBJECT
public:
    //StreamThread(){};
    StreamThread(QObject *parent = 0);
    ~StreamThread();
    void streaming();

public:
    std::string vidfname;
    QString qdirstr,baseDirname,vidid,gtdir;
    unsigned char * frameptr,* delayedFrameptr;
    int framewidth,frameheight,frameidx,frameByteSize,lastframeidx,maxframe,maxskeyframe,nextframeidx;
    QMutex mutex;
    QWaitCondition cv0;

//    NoTracker* tracker;
    TrkScene* trkscene;
    RefScene* refscene;
    //tracking items
    int bb_N,editidx;
    std::vector<cv::Point2i> roi;
    std::vector<TrackBuff *> trackBuff;
    std::vector<BBoxBuff *> bbBuff;
    TrkPts pttmp;
    Buff<REAL> targetLoc,targetBB;

    int delay,bufflen,justUpdated;
    FrameBuff* framebuff;

public slots:
    void updateItems();
    void streamStart(std::string &filename);
    bool init();
    void updateRefscene();
    void saveBBTrack(std::string &dir);
    void parsefname();
    void parsegt();
    void setPos(int stepPos);
    void getroi();
    double checkroi(int x, int y);
    void abandon();
signals:
    void aFrameDone();
    void debug(const char * msg);
    void initSig();
    void refadd(int x,int y);
    void stepReached();
    void startreplay();
    void trkStart(int bb_i);
    void trkEnd(int bb_i);

protected:
    void run();
public:
    bool restart,abort,pause,paused,
    isTagging,checking,replaying,
    inited,roidone,firsttime,saveLast;
};

#endif // STREAMTHREAD

