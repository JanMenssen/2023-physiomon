//
// arduinocomm.h
//
//      header file for the communication with the arduino
//
//  modifications
//    08-jan-2024   JM  initial version

#ifndef ARDUINOCOMM_H
#define ARDUINOCOMM_H

class arduinocomm{

  public:
    arduinocomm();
    void startstop();
    void isConnected();
    void isStarted();
    void sendMsg();
    void rcvMsg();

  private :
    void encode();
    void decode();

};

#endif