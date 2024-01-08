//
// settings.h
//
//      header file for the settings class
//
// modifications
//    08-jan-2024   JM    initial version 

#ifndef _SETTINGS_H
#define _SETTINGS_H

class settings {

  public :
    settings();
    void initialise();
    void iniRead();

  private :
    void readGeneral();
    void readChannels();
    void readDisplaySettings();
    void readEventSettings();

};

#endif
