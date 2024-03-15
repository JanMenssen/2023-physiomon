//
// physiomon_settings.h
//
//      header file for the settings class
//
// modifications
//    08-jan-2024   JM    initial version 
//    11-feb-2024   JM    renamed to <physiomon_settings>

#ifndef _PHYSIOMON_SETTINGS_H
#define _PHYSIOMON_SETTINGS_H

#include <QSettings>
#include "physiomon.h"

// the channel structure is used in the initialisation file

struct channelStruct {
  QString name;
  typeSignal type;
  usedColors color;
  int source;
  int display;
  int store;
  int precision;
};

// the display structure is used for the position and the axis limits  of the displays

struct displayStruct {
  float top;
  float left;
  float width;
  float height;
  float ymin;
  float ymax;
  float timescale;
  viewMode mode;
};

// the store struct is used for which channels are stored

struct storeStruct {
  QString   groupname;
};

class physiomon_settings {

  public :
  
    physiomon_settings();
    ~physiomon_settings();
    void initialise();
    QString iniRead();
    QString getEventString(int iEvent);

  
    QSettings *m_settings = NULL;

    int m_numdisp = 0;
    int m_numchan = 0;
    int m_numstore = 0;
    QString m_device;
    channelStruct m_channels[MAX_CHANNELS];
    displayStruct m_displays[MAX_DISPLAYS];
    storeStruct m_stores[MAX_STORES];
    QString m_events[MAX_EVENTS];

  private :

    void readGeneral();
    void readChannels();
    void readDisplaySettings();
    void readStoreSettings();
    void readEventSettings();

};

#endif
