//
// settings.h
//
//      header file for the settings class
//
// modifications
//    08-jan-2024   JM    initial version 

#ifndef _SETTINGS_H
#define _SETTINGS_H

#include <QSettings>
#include "physiomon.h"

// the channel structure is used in the initialisation file

struct channelStruct {
  QString name;
  typeSignal type;
  int source;
  int display;
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


class settings {

  public :
  
    settings();
    ~settings();
    void initialise();
    QString iniRead();
    QString getEventString(int iEvent);

  
    QSettings *m_settings = NULL;

    int m_numdisp = 0;
    int m_numchan = 0;
    QString m_device;
    channelStruct m_channels[MAX_CHANNELS];
    displayStruct m_displays[MAX_DISPLAYS];
    QString m_events[MAX_EVENTS];

  private :

    void readGeneral();
    void readChannels();
    void readDisplaySettings();
    void readEventSettings();

};

#endif
