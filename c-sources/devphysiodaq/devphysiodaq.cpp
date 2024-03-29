//
// devPhysioDaq
//
//    implementation of the <devPhysioDaq> device driver. This device is an arduino and samples the analog ports, data
//    is transfered to the host using the <arduinocomm> protocol
//
//  modifications
//     12-jan-2024    JM  initial version


#include <QSettings.h>
#include <QDebug.h>

#include "devphysiodaq.h"

// constructor

devPhysioDaq::devPhysioDaq() {

  return;
}

// destructor

devPhysioDaq::~devPhysioDaq() {
  
  return;
}

// initialises
//
//    intiialises the device driver

void devPhysioDaq::initialise() {

  m_arduino = new arduinoComm(m_address,230400);
  return;
  
}

// isConnected
//
//    checks if the device is connected and returns a string with device info

QString devPhysioDaq::isConnected() {
  
  QString devInfo = m_arduino->isConnected();
  return devInfo;
}

// setSampleRate
//
//    sets the sample rate of the arduino

void devPhysioDaq::setSampleRate(int ms) {

  short data = ms;
  m_arduino->sendMsg('c',1,&data);
  
  return;
}

// setStartStop
//
//    starts or stops the device

void devPhysioDaq::setStartStop(bool started) {

  measureDevice::setStartStop(started);
  m_arduino->startstop(started);

  return;
}

// isStarted
//
//    returns a TRUE if the device is started, else a FALSE is returned

bool devPhysioDaq::isStarted() {

  bool on = measureDevice::isStarted();
  return on;
}

// iniRead
//
//    reads the settings (numchannels, gain, offset) from the device specific *.INI file

void devPhysioDaq::iniRead(QString deviceName) {

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

void devPhysioDaq::read(physiomon_channels *channels) {

  char cmd;
  char ANALOG_CMD = 65;
  int n=0;
  short data[8];
  
  if (isStarted()) {

    int i = 0;
    bool msgOK = true;
    while (msgOK == true) {
      
      msgOK = m_arduino->rcvMsg(&cmd,&n,data);
      if (cmd == ANALOG_CMD) {
        for (int i=0;i<n;i++) writeValueToAllChannels(&m_analogIn[i],channels,data[i]);
      }
      i++;
    }
  }

  return;
}

void devPhysioDaq::writeValueToAllChannels(analogInStruct *analogIn, physiomon_channels *channels, short value) {

  // first convert do float data

  float realValue = analogIn->gain * value + analogIn->offset;
    
  int numchan = analogIn->nchan;
  for (int i=0;i<numchan;i++) {
    int ichan = analogIn->channels[i];
    channels->writeData(ichan,realValue);
  }

  return;    
}