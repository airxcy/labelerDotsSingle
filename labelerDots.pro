#-------------------------------------------------
#
# Project created by QtCreator 2014-12-22T23:23:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = labelerDots
TEMPLATE = app


SOURCES += \
    src/Qts/main.cpp \
    src/Qts/mainwindow.cpp \
    src/Qts/streamthread.cpp \
    src/Qts/viewqt.cpp \
    src/trackers/buffers.cpp \
    src/Qts/modelsqt.cpp

HEADERS  += \
    includes/Qts/mainwindow.h \
    includes/Qts/streamthread.h \
    includes/Qts/viewqt.h \
    includes/trackers/buffers.h \
    includes/Qts/modelsqt.h

FORMS    += mainwindow.ui

DISTFILES +=

RESOURCES += resources.qrc

# install
target.path = build/
INSTALLS += target

INCLUDEPATH += includes

win32:CONFIG(release, release): LIBS += -LC:/opencv/build/x86/vc12/lib/ -lopencv_calib3d249\
-lopencv_contrib249\
-lopencv_core249\
-lopencv_features2d249\
-lopencv_flann249\
-lopencv_gpu249\
-lopencv_highgui249\
-lopencv_imgproc249\
-lopencv_legacy249\
-lopencv_ml249\
-lopencv_nonfree249\
-lopencv_objdetect249\
-lopencv_ocl249\
-lopencv_photo249\
-lopencv_stitching249\
-lopencv_superres249\
-lopencv_ts249\
-lopencv_video249\
-lopencv_videostab249

else:win32:CONFIG(debug, debug|release): LIBS += -LC:/opencv/build/x86/vc12/lib/ -lopencv_calib3d249d\
-lopencv_contrib249d\
-lopencv_core249d\
-lopencv_features2d249d\
-lopencv_flann249d\
-lopencv_gpu249d\
-lopencv_highgui249d\
-lopencv_imgproc249d\
-lopencv_legacy249d\
-lopencv_ml249d\
-lopencv_nonfree249d\
-lopencv_objdetect249d\
-lopencv_ocl249d\
-lopencv_photo249d\
-lopencv_stitching249d\
-lopencv_superres249d\
-lopencv_ts249d\
-lopencv_video249d\
-lopencv_videostab249d

INCLUDEPATH += C:/opencv/build/include
DEPENDPATH += C:/opencv/build/include



