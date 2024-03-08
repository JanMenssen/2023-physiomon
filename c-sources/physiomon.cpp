//
// physiomon.cpp
//
//      main file of the fysiomon project
//
// modifications
//    08-jan-2024   JM    initial version

#include "mainwindow.h"
#include <QApplication>

// and main program

int main(int argc, char **argv) {

  QApplication app(argc,argv);

  // setup the splash screen

  // setup the main window

  mainWindow myWindow(1300,750);
  
  // close the splash screen after 2.5 seconds and show the main window
  
  myWindow.show();

  // close choosen, leave program 
  
  return app.exec();

}