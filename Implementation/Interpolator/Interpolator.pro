#-------------------------------------------------
#
# Project created by QtCreator 2017-08-12T15:09:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Interpolator
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14
CONFIG += console

SOURCES += main.cpp\
        mainwindow.cpp \
    interpolator.cpp \
    vec2.cpp \
    optical_flow_calculator.cpp \
    boundary_smoothener.cpp \
    diamond_search.cpp \
    arps.cpp \
    lucas_kanade.cpp \
    horn_schunck.cpp \
    test/test_diamond_search.cpp

HEADERS  += mainwindow.h \
    interpolator.h \
    vec2.h \
    optical_flow_field.h \
    video_info.h \
    interpolator_options.h \
    algorithm.h \
    mv_corrector.h \
    optical_flow_calculator.h \
    boundary_smoothener.h \
    diamond_search.h \
    arps.h \
    lucas_kanade.h \
    horn_schunck.h \
    test/test_diamond_search.h

FORMS    += mainwindow.ui

INCLUDEPATH += /usr/include/opencv
LIBS += -L/usr/local/lib
LIBS += /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so -lopencv_calib3d 
LIBS += /usr/lib/x86_64-linux-gnu/libopencv_contrib.so -lopencv_contrib 
LIBS += /usr/lib/x86_64-linux-gnu/libopencv_core.so -lopencv_core 
LIBS += /usr/lib/x86_64-linux-gnu/libopencv_features2d.so -lopencv_features2d 
LIBS += /usr/lib/x86_64-linux-gnu/libopencv_flann.so -lopencv_flann 
LIBS += /usr/lib/x86_64-linux-gnu/libopencv_gpu.so -lopencv_gpu 
LIBS += /usr/lib/x86_64-linux-gnu/libopencv_highgui.so -lopencv_highgui 
LIBS += /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so -lopencv_imgproc 
LIBS += /usr/lib/x86_64-linux-gnu/libopencv_legacy.so -lopencv_legacy 
LIBS += /usr/lib/x86_64-linux-gnu/libopencv_ml.so -lopencv_ml 
LIBS += /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so -lopencv_objdetect 
LIBS += /usr/lib/x86_64-linux-gnu/libopencv_ocl.so -lopencv_ocl 
LIBS += /usr/lib/x86_64-linux-gnu/libopencv_photo.so -lopencv_photo 
LIBS += /usr/lib/x86_64-linux-gnu/libopencv_stitching.so -lopencv_stitching 
LIBS += /usr/lib/x86_64-linux-gnu/libopencv_superres.so -lopencv_superres 
LIBS += /usr/lib/x86_64-linux-gnu/libopencv_ts.so -lopencv_ts 
LIBS += /usr/lib/x86_64-linux-gnu/libopencv_video.so -lopencv_video 
LIBS += /usr/lib/x86_64-linux-gnu/libopencv_videostab.so -lopencv_videostab
