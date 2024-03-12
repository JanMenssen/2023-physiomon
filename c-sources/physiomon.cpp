//
// physiomon.cpp
//
//      main file of the fysiomon project
//
// modifications
//    08-jan-2024   JM    initial version

#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

// and main program

int main(int argc, char **argv) {

  QApplication app(argc,argv);

  // setup the splash screen

  QSplashScreen *splash = new QSplashScreen;
  splash->setPixmap(QPixmap(":/intro/splashscreen"));
  splash->show();

  // setup the main window, show to create the widgets and hide it directy

  mainWindow myWindow(1300,750);
  myWindow.show();
  myWindow.hide();
  
  // close the splash screen after 2.5 seconds and show the main window
  
  QTimer::singleShot(TIME_SPLASH_SCREEN,splash,SLOT(close()));
  QTimer::singleShot(TIME_WINDOW_SHOW,&myWindow,SLOT(show()));

  // close choosen, leave program 
  
  return app.exec();

}