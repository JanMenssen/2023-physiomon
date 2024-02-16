//
// mainwindow.h
//
//      this is the header file for window classes, used in the project
//
//  modifications
//    12-jan-2024   JM    initial version

#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#include "physiomon.h"
#include "physiomon_displays.h"
#include "physiomon_channels.h"
#include "physiomon_settings.h"
#include "devphysiodaq.h"


#include <QMainWindow>
#include <QObject>
#include <QShortcut>

class mainWindow : public QMainWindow {

  Q_OBJECT

  public :

    mainWindow(int width, int heigth);
    ~mainWindow();
    void onConfigure();

  private slots :
    
    void onStart();
    void onSave();
    void onDeviceInfo();
    void onTimeOut();
    void onSettingsChanged();
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

  physiomon_settings *m_settings = nullptr;
  physiomon_channels *m_channels = nullptr;
  physiomon_displays *m_displays = nullptr;
  devPhysioDaq *m_device = nullptr;

  // actions for the GUI 
  
  QAction *m_startButtonAction = nullptr;
  QAction *m_saveButtonAction = nullptr; 
  QAction *m_generalButtonAction = nullptr;
  QAction *m_deviceButtonAction = nullptr;
  QAction *m_infoButtonAction = nullptr;

  QAction *m_startMenuAction = nullptr;
  QAction *m_saveMenuAction = nullptr; 
  QAction *m_generalMenuAction = nullptr;
  QAction *m_deviceMenuAction = nullptr;
  QAction *m_physiomonHelpMenuAction = nullptr;

  // and the timer

  QTimer *m_timer = nullptr;
};

#endif

