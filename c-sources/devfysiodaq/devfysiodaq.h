//
// devFysioDaq
//
//    header file for hte <devFysioDaq> device, an arduino than samples analog ports arduino
//    transfer the raw data to the host using the seriol ports

#ifndef _DEVFYSIODAQ_H
#define _DEVFYSIODAQ_H

class devFysioDaq {

  public :

  devFysioDaq();
  ~devFysioDaq();

  void initialise();
  void isConnected();
  void setSampleRate(int ms);
  bool isStarted();
  void setStartStop(bool start);
  void iniRead();
  void read(); 
};

#endif