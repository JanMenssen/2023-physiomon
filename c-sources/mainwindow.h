//
// mainwindow.h
//
//      this is the header file for window classes, used in the project
//
//  modifications
//    12-jan-2024   JM    initial version

#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#include "displays.h"
#include "channels.h"
#include "devphysiodaq.h"
#include "settings.h"

#include <QMainWindow>
#include <QObject>

class mainWindow : public QMainWindow {

  Q_OBJECT

  public :

    mainWindow();
    ~mainWindow();
    void createToolBar();
    void createMenu();
    void configure();

  private slots :
    
    void onStart();
    void onDeviceInfo();
    void onTimeOut();
    void onDisplaySettingsChanged();
    void onDeviceSettingsChanged();
    void onFysiomonHelp();

  private :     

  settings *m_settings = NULL;
  devPhysioDaq *m_device = NULL;
  channels *m_channels = NULL;
  displays *m_displays = NULL;

};

#endif

