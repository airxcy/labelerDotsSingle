#ifndef VIEWQT
#define VIEWQT

#include <QGraphicsScene>
#include <QGraphicsView>
#include <vector>
#include <QThread>
class StreamThread;
class Dot;
class RefScene;
class DragVtx;
class DragDots;
class DefaultScene : public QGraphicsScene
{
    Q_OBJECT
public:
    DefaultScene(const QRectF & sceneRect, QObject * parent = 0):QGraphicsScene(sceneRect, parent)
    {

    }
    DefaultScene(qreal x, qreal y, qreal width, qreal height, QObject * parent = 0):QGraphicsScene( x, y, width, height, parent)
    {

    }
    virtual void mousePressEvent ( QGraphicsSceneMouseEvent * event ) Q_DECL_OVERRIDE;
    virtual void drawBackground(QPainter * painter, const QRectF & rect) Q_DECL_OVERRIDE;
signals:
    void clicked(QGraphicsSceneMouseEvent * event);
};
class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView(QGraphicsScene *scene) : QGraphicsView(scene)
    {
        setMouseTracking(true);
        setAcceptDrops(true);
        setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    }
    GraphicsView(QGraphicsScene *scene, QWidget * parent = 0) : QGraphicsView(scene,parent)
    {
        setMouseTracking(true);
        setAcceptDrops(true);
        setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    }
    virtual void resizeEvent(QResizeEvent *) Q_DECL_OVERRIDE;
};
class TrkScene :public QGraphicsScene
{
    Q_OBJECT
public:
    TrkScene(const QRectF & sceneRect, QObject * parent = 0);
    TrkScene(qreal x, qreal y, qreal width, qreal height, QObject * parent = 0);

    StreamThread* streamThd;
    RefScene* refscene;
    int bb_N,focusidx,pendingN,editidx;
    std::vector<DragDots *> dotvec;
    QBrush bgBrush;
    QBrush fgBrush;
    QFont txtfont;
    QImage snapshot;
    QPainter* pter;
    std::vector<DragDots *> roivec;
    int frameidx;
    bool isEditing,mouseclicked,roidone;
    virtual void drawBackground(QPainter * painter, const QRectF & rect) Q_DECL_OVERRIDE;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event)Q_DECL_OVERRIDE;
    //virtual void drawItems(QPainter *painter, int numItems,QGraphicsItem *items[],const QStyleOptionGraphicsItem options[],QWidget *widget)Q_DECL_OVERRIDE;
    //virtual void drawForeground(QPainter * painter, const QRectF & rect) Q_DECL_OVERRIDE;
    int init();
    void addDragDot(int x,int y);
    void updateFptr(unsigned char * fptr,int fidx);
    void clear();
public slots:
    void startEdit();
    void dragBBclicked(int bbidx);
    void addADot(int x,int y);
    void startTrk(int bb_i);
    void endTrk(int bb_i);
signals:
    void litDot(int bb_i);
};

class RefScene :public QGraphicsScene
{
    Q_OBJECT
 public:
    RefScene(const QRectF & sceneRect, QObject * parent = 0);
    RefScene(qreal x, qreal y, qreal width, qreal height, QObject * parent = 0);
    StreamThread* streamThd;
    TrkScene* trkscene;
    QImage bgimg;
    Dot* dot;
    void snapshot();
};

#endif // VIEWQT

