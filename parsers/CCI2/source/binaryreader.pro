# -------------------------------------------------
# Project created by QtCreator 2011-09-14T21:21:45
# -------------------------------------------------
QT += core \
    gui
TARGET = binaryreader
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    parserthread.cpp \
    loadCalibration.cpp
HEADERS += mainwindow.h \
    H5Cpp.h \
    parserthread.h \
    loadCalibration.h
FORMS += mainwindow.ui

INCLUDEPATH += /usr/include/hdf5/serial
# LIBS += -L/usr/lib/root
unix:LIBS += -L/usr/lib/x86_64-linux-gnu/hdf5/serial/ \
    -lhdf5_cpp \
    -lhdf5
win32:DEFINES += HDF5CPP_USEDLL
win32:LIBS += -LC:/HDF5/dll/ \
    -lhdf5_cppdll \
    -lhdf5dll
win32:INCLUDEPATH += C:/HDF5/include

# win32: DEPENDPATH += $$PWD/../../../../../HDF5/include/cpp
#win32:INCLUDEPATH += C:/HDF5/include

# win32: DEPENDPATH += $$PWD/../../../../../HDF5/include
#win32:PRE_TARGETDEPS += C:/HDF5/dll/hdf5_cppdll.lib

# win32: PRE_TARGETDEPS += $$PWD/../../../../../HDF5/lib/hdf5dll.lib
macx:QMAKE_LFLAGS_SONAME = -Wl,-install_name,@executable_path/../Frameworks/
macx:LIBS += -L$$PWD/../../../../opt/local/lib/ \
    -lhdf5_cpp \
    -lhdf5
macx:INCLUDEPATH += $$PWD/../../../../opt/local/include
macx:DEPENDPATH += $$PWD/../../../../opt/local/include
macx:PRE_TARGETDEPS += $$PWD/../../../../opt/local/lib/libhdf5_cpp.a
