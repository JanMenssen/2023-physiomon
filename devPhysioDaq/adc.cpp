//
// asc.cpp
//
//  implementation of the <adc> class. This class samples all analag channels.
//  See <adc.h> for mare information
//
//  Modifications
//    20-jan-2013    JM    initial version
//    06-okt-2014    JM    simulator now sawtooth

#include <Arduino.h>
#include "adc.h"
#define SIMULATOR

// constructors, initialise and set the sample rate

adc::adc(int ms) {
  
  // set the samplerate
  
  mSampleRate = ms;
  mCountDown = mSampleRate;
  
  // initialise some variables
  
  mStartStop = false;
  mBusy = false;
  mAvailable = false;
  
  mDummy = 0;
}


// setSampleRate : this routine sets the sample rate in # ms. Assumed is a interrupt of
// 1 ms (see intr1ms), this routine sets the number of interrupts that must occur before
// acquisition is done

void adc::setSampleRate(int ms) {
  
  mSampleRate = ms;
  mCountDown = mSampleRate;
  
}


// getData : in the paramater <data> this routine returns the last acquired samples. If no 
// samples are avaiable the routine retuns a false

boolean adc::getData(int *n, int *data) {
  
  bool valid = mAvailable;
  
  // if data is available, read the data 
  
  if (mAvailable) {
    for (int i=0;i<MAX_ADC_CHANNELS;i++) data[i] = mData[i];
    *n = MAX_ADC_CHANNELS;
    mAvailable = false;
  }
  
  return valid;
}


// readADC. preforms the analog-digial conversion

void adc::readADC() {
  
  // decrement countdown if acquisition started
  
  if (mStartStop && !mBusy) mCountDown--;
  if (mCountDown == 0) {
  
#ifdef SIMULATOR

    // use the simulator, no analog ports are read

    mBusy = true;
    // for (int i=0;i<MAX_ADC_CHANNELS;i++) mData[i] = mDummy++;
    for (int i=0;i<MAX_ADC_CHANNELS;i++) mData[i] = mDummy++;
    if (mDummy > 1024) mDummy = 0;
    mBusy = false;
    mAvailable = true;

#else

    // real data
    
    mBusy = true;
    for (int i=0;i<MAX_ADC_CHANNELS;i++)  mData[i] = analogRead(A0+i); 
    mBusy = false;
    mAvailable = true;

#endif
    
    // reset the countdown counter
    
    mCountDown = mSampleRate;

  }  
}


// isStarted. Returns TRUE if the acquisistion is started

boolean adc::isStarted() {
  return mStartStop;
}


// isBusy : return RTRUE if a conversion is bsuy so the data is not reliable

boolean adc::isBusy() {
  return mBusy;
}


// isAvailable : returns TRUE if new data is available

boolean adc::isAvailable() {
  return mAvailable;
}


// setStartStop. starts or stops the acquisition

void adc::setStartStop(boolean state) {
  
  mStartStop = state;
  mCountDown = mSampleRate;        // reset the countdown counter 
}


