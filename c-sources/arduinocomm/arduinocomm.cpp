//
// arduinocomm.cpp
//
//    implementation of the serial communication with the arduino. This class makes use of the 
//    QSerialPort class in the QT framework
//
//  modifications
//    08-jan-2024   JM    initial version
//    11-feb-2024   JM    initialise removed, now in constructor

#include "arduinocomm.h"

#include <QDebug.h>
#include <QByteArray>

#define BAUDRATE  QSerialPort::Baud115200

#define STX QByteArray::fromHex("2")
#define ETX QByteArray::fromHex("0")

// define some macro's for getting the high and low byte of a word

#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

// constructor

arduinoComm::arduinoComm(QString port, int baudRate) {

  m_port = new QSerialPort();

  m_port->setPortName(port);
  m_port->open(QIODevice::ReadWrite);
  
  m_port->setBaudRate(baudRate);

  m_port->setDataBits(QSerialPort::Data8);
  m_port->setFlowControl(QSerialPort::NoFlowControl);
  m_port->setParity(QSerialPort::NoParity);
  m_port->setStopBits(QSerialPort::OneStop);

  m_port->flush();

  m_started = false;
}

// destructor
//
arduinoComm::~arduinoComm() {

  if (m_port->isOpen()) m_port->close();  
  if (m_port != NULL) delete m_port;

  return;
}

// startstop
//
//    this method start or stops the communication with the arduino

void arduinoComm::startstop(bool onoff) {

  short data = (onoff? 1 : 0);
  sendMsg('x',1,&data);
  m_started = onoff;

  // clear the data in the read and write buffer

  m_port->flush();
  m_port->readAll();

  return;
}

// isConnected
//
//    this method returns the information of the firmware in the arduino

QString arduinoComm::isConnected() {

  return QString("");
}

// isStarted
//
//    return a boolean indicating the communication with the arduino is isStarted

bool arduinoComm::isStarted() { 

  return m_started;
}

// sendMsg
//
//    this method sends a message to the arduino

void arduinoComm::sendMsg(char cmd, int n, short *data) {

  QByteArray bytesToWrite;
  encode(cmd, n, data, &bytesToWrite);
  m_port->write(bytesToWrite);

  return;
}

// rcvMsg
//
//    returns a true if a message is received
//        - cmd     : command of the message
//        - data    : received data   
//    both <cmd> and <data> are only valid if a message is received

bool arduinoComm::rcvMsg(char *cmd, int *n, short *data) {
  
  static QByteArray rcvBuffer;
  bool msgOK = false;

  int nbytes = m_port->bytesAvailable();
  rcvBuffer += m_port->read(nbytes);

  // while no STX is found, remove data from buffer
  // Note : there should be always one byte in the buffer

  while ((rcvBuffer.first(1) != STX)  && (rcvBuffer.size() > 1)) {
    rcvBuffer = rcvBuffer.sliced(1);
  }

  // STX found? than decode message

  if ((rcvBuffer.first(1) == STX) && (rcvBuffer.size() > 3)) {
    
    int lenMsg = 2 * int(rcvBuffer.at(2)) + 5;
    if (rcvBuffer.size() >= lenMsg) {
      msgOK = decode(rcvBuffer.sliced(0,lenMsg),cmd,n,data);
      rcvBuffer = rcvBuffer.sliced(lenMsg-1);                   
    }
  }
  return msgOK;
}

// encode
//
//      encodes the cmd and data to a QByteArray that can be written to the
//      serial port

void arduinoComm::encode(char cmd, int n, short *data, QByteArray *bytesToWrite) {

  int checksum = 0;

  // start of transmission

  bytesToWrite->append(STX);
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
  bytesToWrite->append(ETX);

  return;

}

// decode
//
//      decodes the stream of bytes in the receive buffer to a message. Returns a 
//      true if the message is correct decoded

bool arduinoComm::decode(const QByteArray rawData, char *cmd, int *n, short *data) {

  short checksumCalc = 0;

  // get the command and the length of the data

  *cmd = rawData.at(1);
  *n = rawData.at(2);

  // decode the data to integers

  for (int i=0;i<*n;i++) {
    
    uint8_t highByte = rawData.at(3+2*i);
    uint8_t lowByte = rawData.at(4+2*i); 
    data[i] = (highByte << 8) + lowByte;
    checksumCalc += data[i];
  }
  checksumCalc = lowByte(checksumCalc);

  // get the checksum and return a true if it is correct

  uint8_t checksumMsg = rawData.at(3 + 2 * (*n));
 
  return (checksumMsg == checksumCalc);
}