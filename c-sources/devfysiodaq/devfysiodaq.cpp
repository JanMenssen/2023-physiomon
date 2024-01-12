//
// devFysioDaq
//
//    implementation of the <devFysioDaq> device driver. This device is an arduino and samples the analog ports, data
//    is transfered to the host using the <arduinocomm> protocol
//
//  modifications
//     12-jan-2024    JM  initial version

#include <stdio.h>
#include <QSettings.h>

#include "devfysiodaq.h"

// constructor

devFysioDaq::devFysioDaq() {

  return;
}

// destructor

devFysioDaq::~devFysioDaq() {
  
  return;
}

// initialises
//
//    intiialises the device driver

void devFysioDaq::initialise() {

  m_arduino.initialise(m_address);
  return;
}

// isConnected
//
//    checks if the device is connected and returns a string with device info

QString devFysioDaq::isConnected() {
  
  QString devInfo = m_arduino.isConnected();
  return devInfo;
}

// setSampleRate
//
//    sets the sample rate of the arduino

void devFysioDaq::setSampleRate(int ms) {

  int data = ms;
  m_arduino.sendMsg('c',1,&data);
  
  return;
}

// setStartStop
//
//    starts or stops the device

void devFysioDaq::setStartStop(bool started) {

  measureDevice::setStartStop(started);
  m_arduino.startstop(started);

  return;
}

// isStarted
//
//    returns a TRUE if the device is started, else a FALSE is returned

bool devFysioDaq::isStarted() {

  bool on = measureDevice::isStarted();
  return on;
}

// iniRead
//
//    reads the settings (numchannels, gain, offset) from the device specific *.INI file

void devFysioDaq::iniRead(QString device) {

  printf("\n --> in devFysioDaq::iniRead");
  
  QSettings *settings = NULL;
  measureDevice::iniRead(device);
  
  settings = new QSettings(QSettings::IniFormat,QSettings::UserScope,"JanSoft",device);
  
  // read the device address

  settings->beginGroup(("algemeen"));
  m_address = settings->value("address").toString();
  settings->endGroup();

  // clean pointers and return

  delete settings;
  return;
}

//  read
//
//    reads samples (if available) from the device 

void devFysioDaq::read() {

  char cmd;
  int n;
  int *data;

  bool msgOK = m_arduino.rcvMsg(&cmd,&n,data);
  return;
}