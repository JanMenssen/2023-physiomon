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

// constructor

arduinocomm::arduinocomm() {
  printf("\n in arduinocomm constructor");
}

// startstop
//
//    this method start or stops the communication with the arduino

void arduinocomm::startstop() {
}

// isConnected
//
//    this method returns the information of the firmware in the arduino

void arduinocomm::isConnected() {
}

// isStarted
//
//    return a boolean indicating the communication with the arduino is isStarted

void arduinocomm::isStarted() { 
}

// sendMsg
//
//    this method sends a message to the arduino

void arduinocomm::sendMsg() {
}

// rcvMsg
//
//    returns a true if a message is received
//        - cmd     : command of the message
//        - data    : received data   
//    both <cmd> and <data> are only valid if a message is received

void arduinocomm::rcvMsg() {
}

// encode
//
//      encodes a message to a stream of bytes that can be sent to the arduino with
//      sendMsg

void arduinocomm::encode() {
}

// decode
//
//      decodes the stream of bytes in the receive buffer to a message

void arduinocomm::decode() {
}