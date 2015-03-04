

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGraphicsView>
#include <QLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QLabel>
#include <QSlider>

class StreamThread;
class TrkScene;
class GraphicsView;
class RefScene;
class DefaultScene;

//! [0]
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

    StreamThread* streamThd;
    QWidget* cWidget;
    TrkScene* trkscene;
    RefScene* refscene[3];
    GraphicsView* gview;
    GraphicsView* refview[3];

    DefaultScene* defaultscene;
    QGridLayout* layout,* layout1;
    QScrollArea* scrollarea;
    QWidget* scrollwidget;
    QBoxLayout* blayout0,* blayout;
    QLabel* label;

    QPushButton* startTag;
    QPushButton* editTag;
    QPushButton* saveBtn;
    QPushButton* roiBtin;
    QPushButton* framedoneBtn;
    QPushButton* relabelBtn;
    QSlider* slider;
    int updaderidx;
    bool firsttime;
    void setupLayout();
    void makeConns();
public slots:
    void gviewClicked(QGraphicsSceneMouseEvent * event);
    void initUI();
    void startTagging();
    void resume();
    void saveBBTrack();
    void setVidPos();
    void stepReached();
    void setRoi();
    void frameDone();
    void relabel();
};
//! [0]

#endif // MAINWINDOW_H
