//
// mainwindow.h
//
//      this is the header file for window classes, used in the project
//
//  modifications
//    12-jan-2024   JM    initial version

#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#include "statusbar.h"

#include <QMainWindow>
#include <QObject>

class mainWindow : public QMainWindow {

  Q_OBJECT

  public :

    mainWindow();
    void createToolBar();

  private slots :
    
    void onStart();
    void onDeviceInfo();
    void onTimeOut();

  private :

    statusBarNew *m_statusBar = NULL;
     
};

#endif

