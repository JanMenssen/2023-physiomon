//
// fysiomon.cpp
//
//      main file of the fysiomon project
//
// modifications
//    08-jan-2024   JM    initial version

#include <stdio.h>
#include "settings.h"
#include "arduinocomm.h"
#include "channels.h"

#define ADDRESS  "tty.usbmodem101"

int main() {

  QString device;

  settings mySettings;
  arduinocomm myComm;
  channels myChannels;

  printf("\n this is a test\n");
  device = mySettings.iniRead();
  printf("\n device name = %s",device.toStdString().c_str());
}