# -------------------------------------------------
# Project created by QtCreator 2011-09-14T21:21:45
# -------------------------------------------------
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = binaryreader

TEMPLATE = app

SOURCES += main.cpp mainwindow.cpp loadCalibration.cpp \
    parserthread.cpp

HEADERS += mainwindow.h H5Cpp.h loadCalibration.h \
    parserthread.h

FORMS += mainwindow.ui
CONFIG+=static

# INCLUDEPATH += include
# LIBS += -L/usr/lib/root
unix:LIBS += -L/usr/lib \
    -lhdf5_cpp \
    -lhdf5

#win32:DEFINES += HDF5CPP_USEDLL
#win32:LIBS += -LC:/HDF5/lib -lhdf5_cpp -lhdf5
#win32:INCLUDEPATH += C:/HDF5/include/cpp
## win32: DEPENDPATH += C:/Program\ Files/HDF_Group/HDF5/1.8.11/include/cpp
#win32:INCLUDEPATH += C:/HDF5/include
#win32:LIBS+=-LC:\Qt\Qt5.1.1\5.1.1\msvc2012_64\lib -lQt5Core -lQt5Gui -lQt5Widgets

# win32: DEPENDPATH += $$PWD/../../../../../HDF5/include
# win32:PRE_TARGETDEPS += C:/Program Files/HDF_Group/HDF5/1.8.11/lib/hdf5_cpp.lib

# win32: PRE_TARGETDEPS += $$PWD/../../../../../HDF5/lib/hdf5dll.lib
macx:QMAKE_LFLAGS_SONAME = -Wl,-install_name,@executable_path/../Frameworks/
macx:LIBS += -L/usr/local/hdf5/lib/ \
    -lhdf5_cpp \
    -lhdf5
macx:INCLUDEPATH += $$PWD/../../../../opt/local/include
macx:DEPENDPATH += $$PWD/../../../../opt/local/include
macx:PRE_TARGETDEPS += /usr/local/hdf5/lib/libhdf5_cpp.a
