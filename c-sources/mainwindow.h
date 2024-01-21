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
#include <QShortcut>

class mainWindow : public QMainWindow {

  Q_OBJECT

  public :

    mainWindow();
    ~mainWindow();
    void configure();

  private slots :
    
    void onStart();
    void onSave();
    void onDeviceInfo();
    void onTimeOut();
    void onDisplaySettingsChanged();
    void onDeviceSettingsChanged();
    void onEvent();
    void onPhysiomonHelp();

  private :    
  
    void createToolBar();
    void createMenu();
    void createEventKeys();

  // function keys are shortcuts for events
   
  QShortcut *keyF1 = NULL;
  QShortcut *keyF2 = NULL;
  QShortcut *keyF3 = NULL;
  QShortcut *keyF4 = NULL;
  QShortcut *keyF5 = NULL;
  QShortcut *keyF6 = NULL;
  QShortcut *keyF7 = NULL;
  QShortcut *keyF8 = NULL;
  QShortcut *keyF9 = NULL;
  QShortcut *keyF10 = NULL;

  settings *m_settings = NULL;
  devPhysioDaq *m_device = NULL;
  channels *m_channels = NULL;
  displays *m_displays = NULL;

};

#endif

