//
// measuredevice.h
//
//      header file abstract class for the device handler. This class should be inherited
//      by the device
//
// modificatons
//    12-jan-2024   JM    initial version

#ifndef _MEASUREDEVICE_H
#define _MEASUREDEVICE_H

#include <Qstring>
#include "settings.h"

struct analogInStruct {
  QString name;
  int sampleRate;
  float gain;
  float offset;
};

class measureDevice {

  public :

    measureDevice();
    ~measureDevice();

    void initialise();
    bool isStarted();
    void setStartStop(bool start);
    void iniRead(QString device);
    void configure(settings *settings);

    int m_nrAnalogIn = 0;
    int m_nrWaveIn = 0;
    int m_nrNumericIn = 0;
    
    analogInStruct *m_analogIn = NULL;

  private :
    
    bool m_started = false;

};

#endif