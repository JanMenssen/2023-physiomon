//
// mainwindow.cpp
//
//    implementation of the methods used for the windowing system for the project

#include "mainwindow.h"
#include "statusbar.h"
#include "channels.h"
#include "displays.h"
#include "devphysiodaq.h"
#include "devphysiodaq_dialog.h"
#include "settings_dialog.h"

#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QToolButton>
#include <QIcon>
#include <QAction>
#include <QShortcut>
#include <QTimer>
#include <QDebug>
#include <QWidget>


// constructor

mainWindow::mainWindow(int width, int height) {

  // first set the size
  
  resize(width,height);

  // create graphical parts

  createMenu();
  createToolBar();
  createEventKeys();

  statusBarNew *status = new statusBarNew;
  setStatusBar(status);
  
  // read the general and specific settings

  m_settings = new settings();
  QString deviceName = m_settings->iniRead();
 
  // Note, this should be done better, device should be set

  m_device = new devPhysioDaq();
  
  m_device->iniRead(deviceName);
  m_device->initialise();

  // create channels and displays and configure the program (displays currently not available). displays 
  // are created on the centralWidget

  QWidget *centralWidget = new QWidget();
  setCentralWidget(centralWidget);

  m_displays = new displays(centralWidget);
  m_channels = new channels(MAX_CHANNELS);

  onConfigure();

  // create the timer

  QTimer *myTimer = new QTimer();
  myTimer->start(100);
  connect(myTimer,SIGNAL(timeout()),this,SLOT(onTimeOut()));

  // and set ready

  setWindowTitle("PhysioMon v3.01");
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

  if (keyF1 != NULL) delete keyF1;
  if (keyF2 != NULL) delete keyF2;
  if (keyF3 != NULL) delete keyF3;
  if (keyF4 != NULL) delete keyF4;
  if (keyF5 != NULL) delete keyF5;
  if (keyF6 != NULL) delete keyF6;
  if (keyF7 != NULL) delete keyF7;
  if (keyF8 != NULL) delete keyF8;
  if (keyF9 != NULL) delete keyF9;
  if (keyF10 != NULL) delete keyF10;
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
  connect(startAction,SIGNAL(triggered()),this, SLOT(onStart()));
  fileMenu->addAction(startAction);

  QAction *saveAction = new QAction(tr("Save"));
  //-jm saveAction->setStatusTip("save data to file");
  connect(startAction,SIGNAL(triggered()),this, SLOT(onSave()));
  fileMenu->addAction(saveAction);
 
  QAction *settingsChangeAction = new QAction(tr("General Settings"));
  //-jm dispSettingsChangeAction->setStatusTip("edit display settings");
  connect(settingsChangeAction,SIGNAL(triggered()),this,SLOT(onSettingsChanged()));
  editMenu->addAction(settingsChangeAction);

  QAction *deviceSettingsChangeAction = new QAction(tr("Device Settings"));
  //-jm deviceSettingsChangeAction->setStatusTip("edit device settings");
  connect(deviceSettingsChangeAction,SIGNAL(triggered()),this,SLOT(onDeviceSettingsChanged()));
  editMenu->addAction(deviceSettingsChangeAction);

  QAction *physiomonHelpAction = new QAction(tr("Physiomon Help"));
  connect(physiomonHelpAction,SIGNAL(triggered()),this, SLOT(onPhysiomonHelp()));
  helpMenu->addAction(physiomonHelpAction);  
}

// createToolBar
//
//    this function creates the toolbar

void mainWindow::createToolBar() {

  QToolBar *toolbar = new QToolBar;
  toolbar->setFixedHeight(75);
  addToolBar(toolbar);

  // start

  QAction *startAction = new QAction();
  startAction->setIcon(QIcon("/Users/jan/OneDrive - Personal/my projects/2024 physiomon/play_13794082.png"));
  startAction->setText("start");
  startAction->setToolTip("start/stop the program");
  connect(startAction,SIGNAL(triggered()),this,SLOT(onStart()));
  
  QToolButton *startButton = new QToolButton();
  startButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  startButton->setDefaultAction(startAction);

  toolbar->addWidget(startButton);
  
  QAction *saveAction = new QAction();
  saveAction->setIcon(QIcon("/Users/jan/OneDrive - Personal/my projects/2024 physiomon/adjust_6048035.png"));
  saveAction->setText("save");
  saveAction->setToolTip("save data to file ");
  connect(saveAction,SIGNAL(triggered()),this,SLOT(onSave()));

  QToolButton *saveButton = new QToolButton();
  saveButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  saveButton->setDefaultAction(saveAction);

  toolbar->addWidget(saveButton);

  // display settings

  QAction *generalAction = new QAction();
  generalAction->setIcon(QIcon("/Users/jan/OneDrive - Personal/my projects/2024 physiomon/adjust_6048035.png"));
  generalAction->setText("general");
  generalAction->setToolTip("change general settings");
  connect(generalAction,SIGNAL(triggered()),this,SLOT(onSettingsChanged()));
  
  QToolButton *generalButton = new QToolButton();
  generalButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  generalButton->setDefaultAction(generalAction);

  toolbar->addWidget(generalButton);

  // device settings

  QAction *deviceAction = new QAction();
  deviceAction->setIcon(QIcon("/Users/jan/OneDrive - Personal/my projects/2024 physiomon/repair_5064596.png"));
  deviceAction->setText("device");
  deviceAction->setToolTip("change device settings");
  connect(deviceAction,SIGNAL(triggered()),this,SLOT(onDeviceSettingsChanged()));
    
  QToolButton *deviceButton = new QToolButton();
  deviceButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  deviceButton->setDefaultAction(deviceAction);

  toolbar->addWidget(deviceButton);
  
  // device info

  QAction *infoAction = new QAction();
  infoAction->setIcon(QIcon("/Users/jan/OneDrive - Personal/my projects/2024 physiomon/repair_5064596.png"));
  infoAction->setText("info");
  infoAction->setToolTip("get info about the device");
  connect(infoAction,SIGNAL(triggered()),this,SLOT(onDeviceInfo()));

  QToolButton *infoButton = new QToolButton();
  infoButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  infoButton->setDefaultAction(infoAction);

  toolbar->addWidget(infoButton);

}

// createEventKeys
//
//    this function handles the F1-F10 events

void mainWindow::createEventKeys() {

  keyF1 = new QShortcut(QKeySequence(Qt::Key_F1), this);
  connect(keyF1,SIGNAL(activated()),this,SLOT(onEvent()));
  
  keyF2 = new QShortcut(QKeySequence(Qt::Key_F2), this);
  connect(keyF2,SIGNAL(activated()),this,SLOT(onEvent()));

  keyF3 = new QShortcut(QKeySequence(Qt::Key_F3), this);
  connect(keyF3,SIGNAL(activated()),this,SLOT(onEvent()));

  keyF4 = new QShortcut(QKeySequence(Qt::Key_F4), this);
  connect(keyF4,SIGNAL(activated()),this,SLOT(onEvent()));

  keyF5 = new QShortcut(QKeySequence(Qt::Key_F5), this);
  connect(keyF5,SIGNAL(activated()),this,SLOT(onEvent()));

  keyF6 = new QShortcut(QKeySequence(Qt::Key_F6), this);
  connect(keyF6,SIGNAL(activated()),this,SLOT(onEvent()));

  keyF7 = new QShortcut(QKeySequence(Qt::Key_F7), this);
  connect(keyF7,SIGNAL(activated()),this,SLOT(onEvent()));

  keyF8 = new QShortcut(QKeySequence(Qt::Key_F8), this);
  connect(keyF8,SIGNAL(activated()),this,SLOT(onEvent()));
    
  keyF9 = new QShortcut(QKeySequence(Qt::Key_F9), this);
  connect(keyF9,SIGNAL(activated()),this,SLOT(onEvent()));

  keyF10 = new QShortcut(QKeySequence(Qt::Key_F10), this);
  connect(keyF10,SIGNAL(activated()),this,SLOT(onEvent()));
}

// onConfigure
//
//    configures the program, depending on the settings from the *.INI file or from the popup
//    menu

void mainWindow::onConfigure() {

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

// onSave
//
//      called when save button is presed

void mainWindow::onSave() {
  
  qDebug() << "--> on save";

  statusBarNew *status = (statusBarNew *)statusBar();
  status->setText("on save pressed",1.0);
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

  //-jm qDebug() << "--> onTimer";

  m_device->read(m_channels);
  m_displays->plot(m_channels);

  //-jm statusBarNew *status = (statusBarNew *)statusBar();
  //-jm status->setText("time out",1.0);
}

// onDeviceSettingsChanged
//
//    popup mennu is shown in which the device settings could be changed, only possible
//    if program is not started

void mainWindow::onDeviceSettingsChanged() {

  // NOTE, this should be done better, no public members

  int n = m_device->m_nrAnalogIn;
  analogInStruct *analogInfo = m_device->m_analogIn;

  statusBarNew *status = (statusBarNew *)statusBar();
  status->setText("device settings are modified ...",3.0);

  // get the analogInfo data and copy this to the dialog widget before executing it
  // m_device->getAnalogInfo(&n,analogInfo);

  devphysiodaq_dialog dlgBox(this,n,analogInfo);
  dlgBox.exec();

}

// onSettingsChanged
//
//    popuwp window is shown on which the display could be changed. Only possible if the
//    program is not started

void mainWindow::onSettingsChanged() {
  
int numdisp = m_settings->m_numdisp;
int numchan = m_settings->m_numchan;
int numanalog = m_device->m_nrAnalogIn;

channelStruct *channelInfo = m_settings->m_channels;
displayStruct *displayInfo = m_settings->m_displays;
QString *eventInfo = m_settings->m_events;
analogInStruct *analogInfo = m_device->m_analogIn;

statusBarNew *status = (statusBarNew *)statusBar();
status->setText("general settings are modified ...",3.0);

settings_dialog dlgBox(this,&numchan,channelInfo,&numdisp,displayInfo,eventInfo,numanalog,analogInfo);
dlgBox.exec();

}

// onEvent 
//
//    this function is called when an event is happened (key pressed)

void mainWindow::onEvent() {

  qDebug() << "--> on event";
  
  QString eventStr;

  // get the sender for this event handle It

  QObject* obj = sender();
  if( obj == keyF1) eventStr = m_settings->getEventString(0);
  if( obj == keyF2) eventStr = m_settings->getEventString(1);
  if( obj == keyF3) eventStr = m_settings->getEventString(2);
  if( obj == keyF4) eventStr = m_settings->getEventString(3);
  if( obj == keyF5) eventStr = m_settings->getEventString(4);
  if( obj == keyF6) eventStr = m_settings->getEventString(5);
  if( obj == keyF7) eventStr = m_settings->getEventString(6);
  if( obj == keyF8) eventStr = m_settings->getEventString(7);
  if( obj == keyF9) eventStr = m_settings->getEventString(8);
  if( obj == keyF10) eventStr = m_settings->getEventString(9);

  statusBarNew *status = (statusBarNew *)statusBar();
  status->setText(eventStr,5.0);
}

// onFysiomonHelp
//
//    help is handled
//

void mainWindow::onPhysiomonHelp() {
  
  statusBarNew *status = (statusBarNew *)statusBar();
  status->setText("on help pressed",1.0);
}