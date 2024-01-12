//
// fysiomon.cpp
//
//      main file of the fysiomon project
//
// modifications
//    08-jan-2024   JM    initial version

#include <stdio.h>
#include "settings.h"
#include "channels.h"
#include "devfysiodaq.h"

#define ADDRESS  "tty.usbmodem101"

int main() {

  settings mySettings;
  channels myChannels;

  QString device= mySettings.iniRead();
  
  // Note, this should be done better in the future, it should be more easy to use 
  //       different devices

  devFysioDaq *myDevice = NULL;
  if (device == QString("fysiodaq")) myDevice = new devFysioDaq;

  myDevice->iniRead(device);

  printf("\n device name = %s",device.toStdString().c_str());
}