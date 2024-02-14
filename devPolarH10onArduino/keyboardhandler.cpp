//
// keyboardhandler.cpp
//
//    implementation of the keyboardhandler class. This class mimics the hostInterface
//    class. Purpose is to use it for debugging, replacing hostInterface
//
//  modifications
//    17-jul-2022   JM    initial version
//    14-feb-2024   JM    tmpData remmoed from c-case

#include <Arduino.h>
#include "keyboardHandler.h"

// constructor

keyBoardHandler::keyBoardHandler(long int baudrate) {

  mBaudRate = baudrate;
  mDataLen = 0;
  mStartStop = false;

  for (int i=0;i<NR_COMMANDS;i++) cmdEvents[i] = NULL;
}

// init
//
//    initialises the serial port

void keyBoardHandler::init() {

  Serial.begin(mBaudRate);
  while (!Serial);
}


// setEvent
//
//    sets the event functions 

boolean keyBoardHandler::setEvent(char c, eventFunction callback) {
  int nr = byte(c) - byte('a');
  cmdEvents[nr] = callback;
  
  return true;
}


// handleCmd
//
//    handles the input

void keyBoardHandler::handleCmd() {

  int tmpData[18] = {80,111,108,97,114,32,72,49,48,32,54,51,49,51,50,52,50,66};
  
  if (Serial.available()) {
    
    char mLastCmd = Serial.read();
    int eventNr = mLastCmd - byte('a');
 
    Serial.print("---> "); Serial.println(mLastCmd);

    switch (mLastCmd) {

      // v-command is used to return the version
      
      case 'v' :

        mDataLen = 1;
        cmd_buffer[0] = 1;
        (*cmdEvents[eventNr])(mDataLen,cmd_buffer);
        
        break;
            
      // x-command is used to switch between start stop

      case 'x' :
        
        mDataLen = 1;

        cmd_buffer[0]= (!mStartStop ? 1 : 0);
        mStartStop = !mStartStop;
        (*cmdEvents[eventNr])(mDataLen,cmd_buffer);
        
        break;
      // c-command is used to configure
      
      case 'c'  :
    
        mDataLen = 18;

        
        for (int i=0;i<mDataLen;i++) cmd_buffer[i] = tmpData[i];
        (*cmdEvents[eventNr])(mDataLen,cmd_buffer);
        
        break;
      
      default :
        break;
    } 
  }
  return;
}


// sendCmd
//
//    mimics the sendCmd command

boolean keyBoardHandler::sendCmd(char cmd, int n, int *data) {

  Serial.print("cmd : "); Serial.print(cmd); 
  Serial.print(" len : "); Serial.print(n);
  Serial.print(" data : "); Serial.println(data[0]);
  
  return true;

}


