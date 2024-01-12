//
// measuredevice.cpp
//
//    implementation of the abstract class <measuredevice>. This contains all general
//    methods needed for the specific device driver
//
//  modifications
//    12-JAN-2024   JM    inital version

#include <stdio.h>
#include <QSettings.h>
#include <qDebug>

#include "measuredevice.h"

// constructor

measureDevice::measureDevice() {

  m_nrAnalogIn = 0;
  return;
}

// destructor

measureDevice::~measureDevice() {

  if (m_analogIn != NULL) delete m_analogIn;

  return;
}

// initialise

void measureDevice::initialise() {

  return;
}

// setStartStop
//
//    starts or stops the device

void measureDevice::setStartStop(bool start) {

  m_started = start;
  return;
}

// isStarted
//
//    returns a true if the device is isStarted

bool measureDevice::isStarted() {

  return false;
}

// iniRead
// 
//    reads the general part of the device initialisation

void measureDevice::iniRead(QString device) {

  qDebug() << "--> in measureDevice::iniRead";

  QSettings *settings = NULL;
  settings = new QSettings(QSettings::IniFormat,QSettings::UserScope,"JanSoft",device);
  
  // read the number of analog input channels, waveform input and numeric input

  settings->beginGroup(("algemeen"));
  m_nrAnalogIn = settings->value("numAnalogIn",0).toInt();
  m_nrWaveIn = settings->value("numWaveformIn",0).toInt();
  m_nrNumericIn = settings->value("numNUmericIn",0).toInt();
  settings->endGroup();
  
  // read the info for the analog channels
 
  if (m_analogIn != NULL) delete m_analogIn;
  m_analogIn = new analogInStruct[m_nrAnalogIn];
  
  for (int iChan=0; iChan < m_nrAnalogIn; iChan++) {

    char keyName[12];
    snprintf(keyName,12,"analog_in %0d",iChan+1);

    settings->beginGroup(keyName);
    m_analogIn[iChan].name = settings->value("name","").toString();
    m_analogIn[iChan].sampleRate = settings->value("sampleRate",1).toInt();
    m_analogIn[iChan].gain = settings->value("gain",1.0).toFloat();
    m_analogIn[iChan].offset = settings->value("offset",0.0).toFloat(); 
    
    settings->endGroup();
  }

  // done remove tempory pointers

  delete settings;  
  return;
}

// configure
//
//    given the settings, configures the device handler

void measureDevice::configure() {

  return;
}