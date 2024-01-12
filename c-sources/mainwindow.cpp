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

  // create the subwindows
  
  // create graphical parts

  createToolBar();

  statusBarNew *status = new statusBarNew;
  setStatusBar(status);
  
  // read the general and specific settings

  m_settings = new settings();
  QString deviceName = m_settings->iniRead();
 
  // Note, this should be done better, device should be set

  m_device = new devFysioDaq();
  
  m_device->iniRead(deviceName);
  m_device->initialise();

  // create channels and displays and configure the program (displays currently not available)

  //-jm m_displays = new displays();
  m_channels = new channels(5);

  configure();

  // create the timer

  QTimer *myTimer = new QTimer();
  myTimer->start(2500);
  connect(myTimer,SIGNAL(timeout()),this,SLOT(onTimeOut()));

  // and set ready

  setWindowTitle("fysiomon v1.01");
  status->setText("ready ...",5.0);

}
 
// destructor
//
//    clear the stuff

mainWindow::~mainWindow() {

  if (m_settings != NULL) delete m_settings;
  if (m_channels != NULL) delete m_channels;
  //-jm if (m_displays != NULL) delete m_displays;
  if (m_device != NULL) delete m_device;

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

// configure
//
//    configures the program, depending on the settings from the *.INI file or from the popup
//    menu

void mainWindow::configure() {

  //-jm m_displays->configure(m_settings);
  //-jm m_device->configure(m_settings);
  //-jm m_channels->configure(m_settings,m_device);

  return;
}

// onStart
//
//      called when start is pressed, device is started or stopped

void mainWindow::onStart() {
  
  qDebug() << "--> onStart";

  statusBarNew *status = (statusBarNew *)statusBar();
  status->setText("on start",1);


}

// onDeviceInfo
//
//      called when device is pressed. the version from the device is asked

void mainWindow::onDeviceInfo() {
  
  qDebug() << "--> onDeviceInfo";

  statusBarNew *status = (statusBarNew *)statusBar();
  status->setText("on device info presed",1.0);
}

// onTimeOut
//
//      routine called at a time onTimeOut

void mainWindow::onTimeOut() {

  qDebug() << "--> onTimer";

  statusBarNew *status = (statusBarNew *)statusBar();
  status->setText("time out",1.0);
}