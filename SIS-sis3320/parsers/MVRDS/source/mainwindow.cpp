/*Binary reader for SIS3302/3320 binary data file version 1411
  Author: Cameron Bates Contributor:Struck Innovative Systeme GmbH
  This is a heavily modified version of the SIS binary to text
  file converter with hooks for both the creation of hdf5 files
  and root files


  */
#include <cstdio>
#include <iostream>
#include <sstream>


#include <QFileDialog>


#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this->ui->read, SIGNAL(clicked()),this,SLOT(readsis3302()));
    connect(this->ui->readfolder, SIGNAL(clicked()),this,SLOT(readfolder()));
    connect(this->ui->calFlag, SIGNAL(clicked()), this,SLOT(readCalFolder()));
    connect(&parsethread,SIGNAL(completion(double)),this,SLOT(updatecompletion(double)));
    connect(&parsethread,SIGNAL(finished()),this,SLOT(enableall()));

    folder = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updatecompletion(double percentdone){
    this->ui->progressBar->setValue((int)(percentdone*100.0));
}

int MainWindow::readfolder(){
    QString foldername = QFileDialog::getExistingDirectory ( this, "Select a folder with .dat files",QDir::currentPath());
    folderdir.setPath(foldername);
    QStringList filters;
    filters << "*.dat";
    folderdir.setNameFilters(filters);
    filelist = folderdir.entryList();
    folder = true;
    parsethread.filename = folderdir.filePath(filelist[0]);
    i = 0;
    readsis3302();
    return 0;
}

int MainWindow::readsis3302(){
    QString filename;
    this->ui->read->setEnabled(false);
    this->ui->readfolder->setEnabled(false);
    if (this->ui->sis3302->isChecked()){parsethread.rd3302 = 1;}
    else if (this->ui->sis3302wrap->isChecked()){parsethread.rd3302 = 2;}
    else{parsethread.rd3302 = 0;}
    this->ui->statusBar->showMessage(QString::number(parsethread.rd3302));
    if(!folder)
    {
        filename = QFileDialog::getOpenFileName(this,"Select .dat File",QDir::currentPath(),tr("SIS Data Files (*.dat);;All files (*.*)"),0);
        parsethread.filename = filename;
    }
    if(this->ui->calFlag->isChecked()){ parsethread.calMode = true; }
    else{ parsethread.calMode = false; }
    if(this->ui->norawFlag->isChecked()){ parsethread.noRawMode = true; }
    else{ parsethread.noRawMode = false; }
    filename = parsethread.filename;
    int lastind = filename.lastIndexOf("/");
    filename.remove(0,lastind+1);
    //this->ui->statusBar->showMessage(tr( filename.toAscii()));
    bool run = parsethread.isRunning();
    while(parsethread.isRunning()){}
    run = parsethread.isRunning();
    //timer.start();
    parsethread.parse();

    return 0;
}

int MainWindow::readCalFolder()
{
    QString calFileName;
    if(this->ui->calFlag->isChecked())
    {
        calFileName = QFileDialog::getOpenFileName(this,"Select calibration File",QDir::currentPath(),tr("Text files (*.txt);;All files (*.*)"),0);
        parsethread.calFileName = calFileName;
    }
    else {parsethread.calFileName = "None";}
    return 0;
}

void MainWindow::enableall(){

    //this->ui->statusBar->showMessage(QString::number(timer.elapsed()));
    if(folder){

        i++;
        if (i==filelist.count()){
            folder = false;
            this->ui->read->setEnabled(true);
            this->ui->readfolder->setEnabled(true);
            return;
        }
        parsethread.filename = folderdir.filePath(filelist[i]);
        readsis3302();

    }else{
        this->ui->read->setEnabled(true);
        this->ui->readfolder->setEnabled(true);
    }

}

