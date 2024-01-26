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

  // setup the graphical parts

  mainWindow myWindow(1300,750);
  myWindow.show();

  // close choosen, leave program 
  
  return app.exec();

}