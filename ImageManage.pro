#-------------------------------------------------
#
# Project created by QtCreator 2018-01-02T19:40:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageManage
TEMPLATE = app

INCLUDEPATH += H:\openCV\opencv\build\include
                    H:\openCV\opencv\build\include\opencv
                    H:\openCV\opencv\build\include\opencv2

LIBS += H:\openCV\opencv\build\x64\vc15\lib\opencv_world340d.lib

SOURCES += main.cpp\
    HSL.cpp \
    ColorSpace.cpp \
     brightvaluedialog.cpp\
        mainwindow.cpp \
    twovaluedialog.cpp \
    imagemosaic.cpp \
    winddialog.cpp \
    blurdialog.cpp \
    gaussianblurdialog.cpp \
    medianblurdialog.cpp \
    bilateralblurdialog.cpp \
    hsbdialog.cpp

HEADERS  += mainwindow.h \
    ColorSpace.hpp \
    HSL.hpp \
    twovaluedialog.h \
     brightvaluedialog.h\
    imagemosaic.h \
    winddialog.h \
    blurdialog.h \
    gaussianblurdialog.h \
    medianblurdialog.h \
    bilateralblurdialog.h \
    hsbdialog.h

FORMS    += mainwindow.ui \
    twovaluedialog.ui \
    imagemosaic.ui \
    winddialog.ui \
    blurdialog.ui \
    gaussianblurdialog.ui \
    medianblurdialog.ui \
     brightvaluedialog.ui\
    bilateralblurdialog.ui \
    hsbdialog.ui

RESOURCES += \
    res.qrc


