//
// mainwindow.cpp
//
//    implementation of the methods used for the windowing system for the project

#include <stdio.h>

#include "mainwindow.h"
#include "statusbar.h"

#include <QToolBar>
#include <QAction>
#include <QTimer>
#include "QDebug"

// constructor

mainWindow::mainWindow() {

  setWindowTitle("fysiomon v1.01");

  // create graphical parts

  createToolBar();

  m_statusBar = new statusBarNew;
  setStatusBar(m_statusBar);
  
  // create the timer

  QTimer *myTimer = new QTimer();
  myTimer->start(2500);
  connect(myTimer,SIGNAL(timeout()),this,SLOT(onTimeOut()));
}
 
// createToolBar
//
//    this function creates the toolbar

void mainWindow::createToolBar() {

  QToolBar *toolbar = new QToolBar;
  addToolBar(toolbar);

  // start
  
  QAction *startAction = new QAction("start");
  startAction->setStatusTip("start/stop the program");
  toolbar->addAction(startAction);
  connect(startAction,SIGNAL(triggered()),this,SLOT(onStart()));
  
  // device info

  QAction *devInfoAction = new QAction("device");
  devInfoAction->setStatusTip("get info about the device");
  toolbar->addAction(devInfoAction);
  connect(devInfoAction,SIGNAL(triggered()),this,SLOT(onDeviceInfo()));

}

// onStart
//
//      called when start is pressed, device is started or stopped

void mainWindow::onStart() {
  
  qDebug() << "--> onStart";
}

// onDeviceInfo
//
//      called when device is pressed. the version from the device is asked

void mainWindow::onDeviceInfo() {
  
  qDebug() << "--> onDeviceInfo";
}

// onTimeOut
//
//      routine called at a time onTimeOut

void mainWindow::onTimeOut() {

  qDebug() << "--> onTimer";
  m_statusBar->setText(QString("ready"),0.5);

}