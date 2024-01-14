//
// devFysioDaq
//
//    implementation of the <devFysioDaq> device driver. This device is an arduino and samples the analog ports, data
//    is transfered to the host using the <arduinocomm> protocol
//
//  modifications
//     12-jan-2024    JM  initial version


#include <QSettings.h>
#include <QDebug.h>

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
/*
  //-jm qDebug() << m_address;

  m_arduino.initialise(m_address);
 */
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

void devFysioDaq::iniRead(QString deviceName) {

  qDebug() << "--> in devFysioDaq::iniRead";

  measureDevice::iniRead(deviceName);
  
  QSettings *settings;
  settings = new QSettings(QSettings::IniFormat,QSettings::UserScope,"JanSoft",deviceName);
  
  // read the device address

  settings->beginGroup("algemeen");
  m_address = settings->value("address","").toString();
  settings->endGroup();

  // clean pointers and return
  
  delete settings;
  return;
}

//  read
//
//    reads samples (if available) from the device
//    currenty 8 bytes could be read (device has 6 channels)

void devFysioDaq::read(channels *channels) {

  char cmd;
  char ANALOG_CMD = 65;
  int n=0;
  int data[8];

  if (isStarted()) {

    bool msgOK = true;
    while (msgOK == true) {
      
      msgOK = m_arduino.rcvMsg(&cmd,&n,data);
      if (cmd == ANALOG_CMD) {

        for (int i=0;i<n;i++) {
          
          // convert to floating values

          float realValue = m_analogIn[i].gain * data[i] + m_analogIn[i].offset;

          // and write the data in the buffers for the connected channels
          
          int nchan = m_analogIn[i].nchan;
          for (int j=0;j<nchan;j++) {
            int iChan = m_analogIn[i].channels[j];
            channels->writeData(iChan,realValue);
          }
        }

      }
    }

  }

  return;
}