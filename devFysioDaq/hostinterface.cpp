//
// hostInterface.cpp
//
//  implementation of the <hostInterface> class. For a description and methods see the
//  header file
//
//  Modifications
//    20-jan-2013   JM    initial version
//    24-mrt-2015   JM    include of Serial library removed
//    29-jan-2016   JM    now function pointers are used
//    18-jan-2016   JM    in Event function, n is no pointer
//    25-feb-2017   JM    not used variables removed

#include <Arduino.h>
#include "hostinterface.h"

// some defines for transmitting

#define STX  0x02
#define ETX  0x00

// and for the size of the receive buffer

#define RCV_BUFFER_LEN 256

// constructors, initialize

hostInterface::hostInterface(long int baudrate) {
    
  // initialise the members
  
  mBaudRate = baudrate;
  
  mLastCmd = 0;
  mDataLen = 0;

  for (int i=0;i<NR_COMMANDS;i++) {
    cmdEvents[i] = NULL;   
  }
}

// init
//
//    initialises teh serial port

void hostInterface::start() {

  Serial.begin(mBaudRate);
  while(!Serial);
  
}


// seEvent
//
//    sets the callback function for the comamnd

boolean hostInterface::setEvent(char c, eventFunction callBack) {

  int nr = byte(c) - byte('a');
  cmdEvents[nr] = callBack;
  
  return true;

}


// isDataAvailable
//
//    returns TRUE is a new command is received, else a FALSE is returned

boolean hostInterface::isDataAvailable() {
  
  static byte dataBuffer[RCV_BUFFER_LEN];   // holds not completed commands
  static int curPos;                        // position of the buffer
  int lenData = 0;                          // length of the current parameter/data blokc
  int checksum = 0;                         // checksum
 
  // only if no command in the buffer

  if (mLastCmd == 0x00) {

    // check the number of bytes in the buffer, this must be more than the lenght of a command
    
    int nrBytesBuffer = Serial.available();      
    if (nrBytesBuffer > 0) {
      
      for (int i=0;i<nrBytesBuffer;i++) dataBuffer[curPos++] = Serial.read();  
      if (curPos > 3) lenData = (int)dataBuffer[2];
      if (curPos >= (2 * lenData + 5)) {
  
        // enough data, read it and check valid
        
        for (int i=0;i<lenData;i++) {
          mLastData[i] = 256 * dataBuffer[3+2*i] + dataBuffer[4+2*i];
          checksum += mLastData[i];
        }   

        if ((lowByte(checksum) == dataBuffer[2*lenData+3]) && (dataBuffer[0] == STX) && (dataBuffer[2*lenData+4] == ETX)) {     
          mLastCmd = dataBuffer[1];
          mDataLen = lenData;
        } 
     
        curPos = 0;
      
  } } } 
  
  return (mLastCmd != 0x00);
}


// sendCmd
//
//    sends the command that's in the parameter, together with the data tho the host

boolean hostInterface::sendCmd(char cmd,int n,int *data) {
  
  int checksum = 0;
  
  // start of transmission, command and number of data bytes
  
  Serial.write(STX);           
  Serial.write(cmd);              
  Serial.write(lowByte(n));  
   
  // send the data
  
  for (int i=0; i<n; i++) {
    checksum += data[i];
    Serial.write(highByte(data[i]));
    Serial.write(lowByte(data[i]));
  }
  
  // checksum and enod of transmission
  
  Serial.write(lowByte(checksum));
  Serial.write(lowByte(ETX));             
  
  return true;
}


// getCMD
//
//    returns TRUE if new data is received from the host and the data is in the paramaters

boolean hostInterface::getCmd(char *command, int *n, int *data) {
  
  boolean avail = false;

  // if no last command, check data is available 
  
  if (mLastCmd == 0x00)  avail = isDataAvailable();
    
  // if new command is available, copy to the output and clear the internal states

  if (avail) {
   
    *command = mLastCmd;
    *n = mDataLen;
    for (int i=0;i<mDataLen;i++) data[i] = mLastData[i];
  
    mLastCmd = 0x00;
    mDataLen = 0;
  }
  
  return avail;
}


// handleCmd
//
//   handles the command. If a command is received, it calls the function that is set with

void hostInterface::handleCmd() {

  char command;
  int lenData;
 
  if (getCmd(&command,&lenData,cmd_buffer)) {
    int nr = byte(command) - byte('a');
    (*cmdEvents[nr])(lenData,cmd_buffer);
  }
  
  return;
}

