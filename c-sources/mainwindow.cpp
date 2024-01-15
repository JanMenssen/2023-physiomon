//
// mainwindow.cpp
//
//    implementation of the methods used for the windowing system for the project

#include "mainwindow.h"
#include "statusbar.h"

#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QAction>
#include <QTimer>
#include "QDebug"

// constructor

mainWindow::mainWindow() {

  // create the subwindows
  
  // create graphical parts

  createMenu();
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

  m_displays = new displays();
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
  if (m_displays != NULL) delete m_displays;
  if (m_device != NULL) delete m_device;

}

// createMeneu
//
//    creates the menu

void mainWindow::createMenu() {

  QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
  QMenu *editMenu = menuBar()->addMenu(tr(("&Edit")));
  QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));

  QAction *startAction = new QAction(tr("&Start"));
  //-jm startAction->setStatusTip("start/stop the program");
  connect(startAction,SIGNAL(clicked()),this, SLOT(onStart()));
  fileMenu->addAction(startAction);

  QAction *saveAction = new QAction(tr("Save"));
  //-jm saveAction->setStatusTip("save data to file");
  connect(startAction,SIGNAL(clicked()),this, SLOT(onStart()));
  fileMenu->addAction(saveAction);
 
  QAction *dispSettingsChangeAction = new QAction(tr("Display"));
  //-jm dispSettingsChangeAction->setStatusTip("edit display settings");
  connect(dispSettingsChangeAction,SIGNAL(triggered()),this,SLOT(onDisplaySettingsChanged()));
  editMenu->addAction(dispSettingsChangeAction);

  QAction *deviceSettingsChangeAction = new QAction(tr("Device"));
  //-jm deviceSettingsChangeAction->setStatusTip("edit device settings");
  connect(deviceSettingsChangeAction,SIGNAL(triggered()),this,SLOT(onDeviceSettingsChanged()));
  editMenu->addAction(deviceSettingsChangeAction);

  QAction *fysiomonHelpAction = new QAction(tr("Fysiomon Help"));
  connect(fysiomonHelpAction,SIGNAL(triggered()),this, SLOT(onFysiomonHelp()));
  helpMenu->addAction(fysiomonHelpAction);  
}

// createToolBar
//
//    this function creates the toolbar

void mainWindow::createToolBar() {

  QToolBar *toolbar = new QToolBar;
  addToolBar(toolbar);

  // start
  
  QAction *startAction = new QAction("start");
  startAction->setToolTip("start/stop the program");
  toolbar->addAction(startAction);
  connect(startAction,SIGNAL(triggered()),this,SLOT(onStart()));
  
  // save 
  
  QAction *saveAction = new QAction("save");
  saveAction->setToolTip("save data to file ");
  toolbar->addAction(saveAction);
  connect(saveAction,SIGNAL(triggered()),this,SLOT(onStart()));

  // device info

  QAction *devInfoAction = new QAction("device");
  devInfoAction->setToolTip("get info about the device");
  toolbar->addAction(devInfoAction);
  connect(devInfoAction,SIGNAL(triggered()),this,SLOT(onDeviceInfo()));
}

// configure
//
//    configures the program, depending on the settings from the *.INI file or from the popup
//    menu

void mainWindow::configure() {

  m_displays->configure(m_settings);
  m_device->configure(m_settings);
  m_channels->configure(m_settings,m_device);

  return;
}

// onStart
//
//      called when start is pressed, device is started or stopped

void mainWindow::onStart() {

  bool started = m_device->isStarted();
  statusBarNew *status = (statusBarNew *)statusBar();
 
  if (!started) {
    m_device->setStartStop(true);
    status->setText("device is started ...",2.5);
  } else {
    m_device->setStartStop(false);
    status->setText("device is stopped ...",2.5);
  }

  return;
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

  m_device->read(m_channels);
  m_displays->plot(m_channels);

  statusBarNew *status = (statusBarNew *)statusBar();
  status->setText("time out",1.0);
}

// onDeviceSettingsChanged
//
//    popup mennu is shown in which the device settings could be changed, only possible
//    if program is not started

void mainWindow::onDeviceSettingsChanged() {

}

// onDisplaySettingsChanged
//
//    popuwp window is shown on which the display could be changed. Only possible if the
//    program is not started

void mainWindow::onDisplaySettingsChanged() {

}

// onFysiomonHelp
//
//    help is handled
//

void mainWindow::onFysiomonHelp() {

}