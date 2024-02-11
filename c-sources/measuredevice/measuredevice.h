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
#include "physiomon_settings.h"

// analog structure. each data channel can be onnected to 5 display/stores

struct analogInStruct {
  QString name;
  float sampleRate;
  float gain;
  float offset;
  int nchan;
  int channels[5];
};

class measureDevice {

  public :

    measureDevice();
    ~measureDevice();

    void initialise();
    bool isStarted();
    void setStartStop(bool start);
    void iniRead(QString device);
    void configure(physiomon_settings *settings);
    void getAnalogInfo(int *ntal, analogInStruct *analogInfo);

    int m_nrAnalogIn = 0;
    int m_nrWaveIn = 0;
    int m_nrNumericIn = 0;
    
    analogInStruct *m_analogIn = nullptr;

  private :

    bool m_started = false;

};

#endif
