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

#include "mainwindow.h"
#include <QApplication>
  
// and main program

int main(int argc, char **argv) {

  QApplication app(argc,argv);

  settings mySettings;
  channels myChannels;
  devFysioDaq *myDevice = NULL;

  // read the settings and initialise the device. Note, this should be done better in the futurre 
  // if different devices are used

  QString device= mySettings.iniRead();
  if (device == QString("fysiodaq")) myDevice = new devFysioDaq;
  myDevice->iniRead(device);


  // and set the up the graphics part

  mainWindow myWindow;
  

  myWindow.show();
 
  // done, place ready text in the status bar and wait until quit

  

  return app.exec();

}