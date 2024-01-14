//
// devFysioDaq
//
//    header file for hte <devFysioDaq> device, an arduino than samples analog ports arduino
//    transfer the raw data to the host using the seriol ports

#ifndef _DEVFYSIODAQ_H
#define _DEVFYSIODAQ_H

#include <QString>
#include "arduinocomm.h"
#include "measuredevice.h"

class devFysioDaq : public measureDevice {

  public :

    devFysioDaq();
    ~devFysioDaq();

    void initialise();
    QString isConnected();
    void setSampleRate(int ms);
    bool isStarted();
    void setStartStop(bool start);
    void iniRead(QString deviceName);
    void read(); 

  private :

    QString m_address = "";
    arduinoComm m_arduino;

};

#endif