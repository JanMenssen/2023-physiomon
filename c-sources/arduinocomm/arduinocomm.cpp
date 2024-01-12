//
// arduinocomm.cpp
//
//    implementation of the serial communication with the arduino. This class makes use of the 
//    QSerialPort class in the QT framework
//
//  modifications
//    08-jan-2024   JM    initial version

#include "arduinocomm.h"
#include <stdio.h>

#define BAUDRATE  QSerialPort::Baud115200

#define STX 0x02
#define ETX 0x00

// define some macro's for getting the high and low byte of a word

#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

// constructor

arduinocomm::arduinocomm() {

  printf("\n in arduinocomm constructor");

  m_started = false;
}

// destructor
//
arduinocomm::~arduinocomm() {

  //-jm if (m_port->isOpen()) m_port->close();   // NOTE results in an segementation fault ??
  if (m_port != NULL) delete m_port;

  return;
}

// initialize
//
//    initialises the serial port. This is a seperate routine and not in the constructor
//    because the device address (portname) is not known when the constructor is called

void arduinocomm::initialise(QString port) {

  m_port =new QSerialPort();

  m_port->setPortName(port);
  m_port->open(QIODevice::ReadWrite);
  
  m_port->setBaudRate(BAUDRATE);

  m_port->setDataBits(QSerialPort::Data8);
  m_port->setFlowControl(QSerialPort::NoFlowControl);
  m_port->setParity(QSerialPort::NoParity);
  m_port->setStopBits(QSerialPort::OneStop);

  m_port->flush();

  m_started = false;

  return;

}


// startstop
//
//    this method start or stops the communication with the arduino

void arduinocomm::startstop(bool onoff) {

  int data = (onoff? 1 : 0);
  sendMsg('x',1,&data);
  m_started = onoff;

  return;
}

// isConnected
//
//    this method returns the information of the firmware in the arduino

QString arduinocomm::isConnected() {

  return QString("");
}

// isStarted
//
//    return a boolean indicating the communication with the arduino is isStarted

bool arduinocomm::isStarted() { 

  return m_started;
}

// sendMsg
//
//    this method sends a message to the arduino

void arduinocomm::sendMsg(char cmd, int n, int *data) {

  QByteArray bytesToWrite;
  encode(cmd, n, data, &bytesToWrite);
  m_port->write(bytesToWrite);

  // tempory checky bytes written

  printf("\n current length of message %d",int(bytesToWrite.size()));
  for (int i=0;i<bytesToWrite.size();i++) {
    printf("\n current byte %d",bytesToWrite.at(i));
  }

  return;
}

// rcvMsg
//
//    returns a true if a message is received
//        - cmd     : command of the message
//        - data    : received data   
//    both <cmd> and <data> are only valid if a message is received

bool arduinocomm::rcvMsg(char *cmd, int *n, int *data) {

  static QByteArray rcvBuffer;
  bool msgOK = false;

  int nbytes = m_port->bytesAvailable();
  rcvBuffer += m_port->read(nbytes);

  // if there are more than 7 bytes received we know the length of the message, then
  // we try to find the STX and remove the bytes before

  if (rcvBuffer.size() >= 7) {
    
    while (rcvBuffer.first(1).toInt() != STX) rcvBuffer = rcvBuffer.sliced(1);

    int lenMsg = 2 * int(rcvBuffer.at(2)) + 5;
    if (rcvBuffer.size() > lenMsg) {
      msgOK = decode(rcvBuffer.sliced(0,lenMsg),cmd,n,data);
      if (msgOK) rcvBuffer = rcvBuffer.sliced(lenMsg);
    }
  }

  return msgOK;
}

// encode
//
//      encodes the cmd and data to a QByteArray that can be written to the
//      serial port

void arduinocomm::encode(char cmd, int n, int *data, QByteArray *bytesToWrite) {

  int checksum = 0;

  // start of transmission

  bytesToWrite->append(lowByte(STX));
  bytesToWrite->append(cmd);
  bytesToWrite->append(lowByte(n));

  // encode the data

  for (int i=0;i<n;i++) {
    checksum += data[i];
    bytesToWrite->append(highByte(data[i]));
    bytesToWrite->append(lowByte(data[i]));
  }

  // checksum and end of transmission

  bytesToWrite->append(lowByte(checksum));
  bytesToWrite->append(lowByte(ETX));

  return;

}


// decode
//
//      decodes the stream of bytes in the receive buffer to a message. Returns a 
//      true if the message is correct decoded

bool arduinocomm::decode(const QByteArray, char *cmd, int *n, int *data) {

  return false;
}