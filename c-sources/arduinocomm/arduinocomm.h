//
// arduinocomm.h
//
//      header file for the communication with the arduino
//
//  modifications
//    08-jan-2024   JM  initial version

#ifndef ARDUINOCOMM_H
#define ARDUINOCOMM_H

#include <QSerialPort>

class arduinoComm{

  public:
    arduinoComm();
    ~arduinoComm();

    void initialise(QString port);
    void startstop(bool onoff);
    QString isConnected();
    bool isStarted();
    void sendMsg(char cmd, int n, short *data);
    bool rcvMsg(char *cmd, int *n, short *data);

  private :

    QSerialPort *m_port = NULL;
    bool m_started;
  
    void encode(char cmd, int n, short *data, QByteArray *bytesToWrite);
    bool decode(const QByteArray, char *cmd, int *len, short *data);

};

#endif