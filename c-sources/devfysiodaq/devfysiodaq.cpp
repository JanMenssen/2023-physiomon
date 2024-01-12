//
// devFysioDaq
//
//    implementation of the <devFysioDaq> device driver. This device is an arduino and samples the analog ports, data
//    is transfered to the host using the <arduinocomm> protocol
//
//  modifications
//     12-jan-2024    JM  initial version

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

  return;
}

// isConnected
//
//    checks if the device is connected and returns a string with device info

void isConnected() {
  
  return;
}

// setSampleRate
//
//    sets the sample rate of the arduino

void devFysioDaq::setSampleRate(int ms) {
  
  return;
}

// setStartStop
//
//    starts or stops the device

void devFysioDaq::setStartStop(bool started) {

  return;
}

// isStarted
//
//    returns a TRUE if the device is started, else a FALSE is returned

bool devFysioDaq::isStarted() {

  return false;
}

// iniRead
//
//    reads the settings (numchannels, gain, offset) from the device specific *.INI file

void devFysioDaq::iniRead() {

  return;
}

//  read
//
//    reads samples (if available) from the device 

void devFysioDaq::read() {

  return;
}