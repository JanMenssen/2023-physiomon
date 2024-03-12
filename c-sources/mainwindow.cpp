//
// mainwindow.cpp
//
//    implementation of the methods used for the windowing system for the project

#include "mainwindow.h"
#include "statusbar.h"
#include "physiomon_channels.h"
#include "physiomon_displays.h"
#include "physiomon_settings.h"
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

#define ICON_SIZE 20
#define ICON_FIXED_WIDTH 40
#define TIMER_PERIOD 100

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

  m_settings = new physiomon_settings();
  QString deviceName = m_settings->iniRead();
 
  // Note, this should be done better, device should be set

  m_device = new devPhysioDaq();
  
  m_device->iniRead(deviceName);
  m_device->initialise();

  // create channels and displays and configure the program (displays currently not available). displays 
  // are created on the centralWidget

  QWidget *centralWidget = new QWidget();
  setCentralWidget(centralWidget);

  m_displays = new physiomon_displays(centralWidget);
  m_channels = new physiomon_channels(5);

  onConfigure();

  // create the timer(s)

  m_periodic_timer = new QTimer();
  m_periodic_timer->setInterval(TIMER_PERIOD);

  m_oneShot_timer = new QTimer();
  m_oneShot_timer->setInterval(TIMER_PERIOD);
  m_oneShot_timer->setSingleShot(true);
  m_oneShot_timer->start();

  connect(m_periodic_timer,SIGNAL(timeout()),this,SLOT(onTimeOut()));
  connect(m_oneShot_timer,SIGNAL(timeout()),this,SLOT(onOneShot()));

  // and set ready

  setWindowTitle("PhysioMon v3.01 - C++ version");
  status->setText("ready ...",3.0);
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

  m_startMenuAction = new QAction(tr("&Start"));
  m_startMenuAction->setToolTip("start/stop acquisiiton");
  connect(m_startMenuAction,SIGNAL(triggered()),this, SLOT(onStart()));
  fileMenu->addAction(m_startMenuAction);

  m_saveMenuAction = new QAction(tr("Save"));
  m_saveMenuAction->setToolTip("save data to disk");
  connect(m_saveMenuAction,SIGNAL(triggered()),this, SLOT(onSave()));
  fileMenu->addAction(m_saveMenuAction);
 
  m_generalMenuAction = new QAction(tr("General Settings"));
  m_generalMenuAction->setToolTip("change general settings");
  connect(m_generalMenuAction,SIGNAL(triggered()),this,SLOT(onSettingsChanged()));
  editMenu->addAction(m_generalMenuAction);

  m_deviceMenuAction = new QAction(tr("Device Settings"));
  m_deviceMenuAction->setToolTip("change device settings");
  connect(m_deviceMenuAction,SIGNAL(triggered()),this,SLOT(onDeviceSettingsChanged()));
  editMenu->addAction(m_deviceMenuAction);

  m_physiomonHelpMenuAction = new QAction(tr("Physiomon Help"));
  m_physiomonHelpMenuAction->setToolTip("gives help");
  connect(m_physiomonHelpMenuAction,SIGNAL(triggered()),this, SLOT(onPhysiomonHelp()));
  helpMenu->addAction(m_physiomonHelpMenuAction);  
}

// createToolBar
//
//    this function creates the toolbar

void mainWindow::createToolBar() {

  QToolBar *toolbar = new QToolBar;
  toolbar->setIconSize(QSize(ICON_SIZE, ICON_SIZE));
  toolbar->setFixedHeight(60);
  addToolBar(toolbar);

  // start

  m_startButtonAction = new QAction();
  m_startButtonAction->setIcon(QIcon(":/icons/play_13794082.png"));
  m_startButtonAction->setText("start");
  m_startButtonAction->setToolTip("start/stop the program");
  connect(m_startButtonAction,SIGNAL(triggered()),this,SLOT(onStart()));
  
  QToolButton *startButton = new QToolButton();
  startButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  startButton->setDefaultAction(m_startButtonAction);
  startButton->setFixedWidth(ICON_FIXED_WIDTH);

  toolbar->addWidget(startButton);
  
  m_saveButtonAction = new QAction();
  m_saveButtonAction->setIcon(QIcon(":/icons/saving-content_11753556.png"));
  m_saveButtonAction->setText("save");
  m_saveButtonAction->setToolTip("save data to file ");
  connect(m_saveButtonAction,SIGNAL(triggered()),this,SLOT(onSave()));

  QToolButton *saveButton = new QToolButton();
  saveButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  saveButton->setDefaultAction(m_saveButtonAction);
  saveButton->setFixedWidth(ICON_FIXED_WIDTH);

  toolbar->addWidget(saveButton);

  // general settings

  m_generalButtonAction = new QAction();
  m_generalButtonAction->setIcon(QIcon(":/icons/adjust_6048035.png"));
  m_generalButtonAction->setText("general");
  m_generalButtonAction->setToolTip("change general settings");
  connect(m_generalButtonAction,SIGNAL(triggered()),this,SLOT(onSettingsChanged()));
  
  QToolButton *generalButton = new QToolButton();
  generalButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  generalButton->setDefaultAction(m_generalButtonAction);
  generalButton->setFixedWidth(ICON_FIXED_WIDTH);

  toolbar->addWidget(generalButton);

  // device settings

  m_deviceButtonAction = new QAction();
  m_deviceButtonAction->setIcon(QIcon(":/icons/repair_5064596.png"));
  m_deviceButtonAction->setText("device");
  m_deviceButtonAction->setToolTip("change device settings");
  connect(m_deviceButtonAction,SIGNAL(triggered()),this,SLOT(onDeviceSettingsChanged()));
    
  QToolButton *deviceButton = new QToolButton();
  deviceButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  deviceButton->setDefaultAction(m_deviceButtonAction);
  deviceButton->setFixedWidth(ICON_FIXED_WIDTH);

  toolbar->addWidget(deviceButton);
  
  // device info

  m_infoButtonAction = new QAction();
  m_infoButtonAction->setIcon(QIcon(":/icons/report_4517968"));
  m_infoButtonAction->setText("info");
  m_infoButtonAction->setToolTip("get info about the device");
  connect(m_infoButtonAction,SIGNAL(triggered()),this,SLOT(onDeviceInfo()));

  QToolButton *infoButton = new QToolButton();
  infoButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  infoButton->setDefaultAction(m_infoButtonAction);
  infoButton->setFixedWidth(ICON_FIXED_WIDTH);

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
  
  m_device->configure(m_settings);
  m_channels->configure(m_settings,m_device);
  m_displays->configure(m_settings);

  return;
}

// onStart
//
//      called when start is pressed, device is started or stopped

void mainWindow::onStart() {

  bool started = m_device->isStarted();
  statusBarNew *status = (statusBarNew *)statusBar();
 
  if (!started) {

    m_startButtonAction->setIcon(QIcon(":/icons/stop_9503472.png"));
    m_startButtonAction->setText("stop");
    m_startMenuAction->setText("Stop");
                                   
    m_generalButtonAction->setDisabled(true);
    m_deviceButtonAction->setDisabled(true);
    m_infoButtonAction->setDisabled(true);

    m_generalMenuAction->setDisabled(true);
    m_deviceMenuAction->setDisabled(true);

    m_device->setStartStop(true);
    m_periodic_timer->start();
    status->setText("device is started ...",2.5);

  } else {

    m_startButtonAction->setIcon(QIcon(":/icons/play_13794082.png"));
    m_startButtonAction->setText("start");
    m_startMenuAction->setText("Start");
                                   
    m_generalButtonAction->setDisabled(false);
    m_deviceButtonAction->setDisabled(false);
    m_infoButtonAction->setDisabled(false);

    m_generalMenuAction->setDisabled(false);
    m_deviceMenuAction->setDisabled(false);

    m_device->setStartStop(false);
    m_periodic_timer->stop();
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
  
  QString dataStr = m_device->isConnected();
  
  qDebug() << "-" << dataStr << "-";

  statusBarNew *status = (statusBarNew *)statusBar();
  status->setText(dataStr,1.0);
}

// onTimeOut
//
//      routine called at a time onTimeOut

void mainWindow::onTimeOut() {

  m_device->read(m_channels);
  m_displays->plot(m_channels);
  
  //-jm qDebug() << "<-- timer : " << m_periodic_timer->remainingTime();

  //-jm statusBarNew *status = (statusBarNew *)statusBar();
  //-jm status->setText("time out",1.0);
}

// onOneShot
//
//    this is the callback for the one shot timer, this timer is used to initialise
//    the QCharts which size is not known until the widgets are rendered (see QT forum)

void mainWindow::onOneShot() {

  m_displays->initPlot(m_channels);
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
  status->setText("edit device settings ...",3.0);

  // get the analogInfo data and copy this to the dialog widget before executing it
  // m_device->getAnalogInfo(&n,analogInfo);

  devphysiodaq_dialog dlgBox(this,n,analogInfo);
  if (dlgBox.exec() == QDialog::Accepted) {
    status->setText("changed settings are saved ...",3.0);
  } else {
    status->setText("changed settings not saved ...",3.0);
  }

  // configure and start the one shot timer to wait 100 ms to update the graph

  onConfigure();
  m_oneShot_timer->start();
}

// onSettingsChanged
//
//    popuwp window is shown on which the display could be changed. Only possible if the
//    program is not started

void mainWindow::onSettingsChanged() {

  channelStruct *channelInfo = m_settings->m_channels;
  displayStruct *displayInfo = m_settings->m_displays;
  QString *eventInfo = m_settings->m_events;
  analogInStruct *analogInfo = m_device->m_analogIn;

  statusBarNew *status = (statusBarNew *)statusBar();
  status->setText("edit general settings ...",3.0);

  settings_dialog dlgBox(this,&m_settings->m_numchan,channelInfo,&m_settings->m_numdisp,displayInfo,eventInfo,m_device->m_nrAnalogIn,analogInfo);
  if (dlgBox.exec() == QDialog::Accepted) {
    status->setText("changed settings are saved ...",3.0);
  } else {
    status->setText("changed settings not saved ...",3.0);
  }
  
  // configure and start the one shot timer to wait 100 ms to update the graph

  onConfigure();
  m_oneShot_timer->start();
}

// onEvent 
//
//    this function is called when an event is happened (key pressed)

void mainWindow::onEvent() {
  
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