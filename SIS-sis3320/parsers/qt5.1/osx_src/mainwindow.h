#ifndef MAINWINDOW_H
#define MAINWINDOW_H
/*
 Author: Cameron Bates
 Description: Qt main window to unpack raw SIS data into an HDF5 file.
 Root bindings are also included but not used(no simple way to handle variable sized raw data arrays without using pointers)

 */
#include <QMainWindow>
//#include <QElapsedTimer>
#include <QDir>
#include "parserthread.h"



namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void updatecompletion(double percentdone);
    void enableall();

private:
    Ui::MainWindow *ui;
    parserthread parsethread;
    //QElapsedTimer timer;
    QStringList filelist;
    bool folder;
    int i;
    QDir folderdir;
private slots:
    int readsis3302();
    int readfolder();
    int readCalFolder();
    //int readsis3320();
};

#endif // MAINWINDOW_H
