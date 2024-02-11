//
// physiomon_settings.cpp
//
//    implementation of the settings class. This class reads the settings from the INI file and 
//    distributes these to the other classes. It makes use of the Qsettings class of the QT
//    framework
//
// modifications
//    08-jan-2024 JM  initial version
//    11-feb-2024 JM  renamed to <physiomon_settings>

#include <stdio.h>
#include "physiomon_settings.h"

// constructor
//
//    initialise the superclass and set the default values

physiomon_settings::physiomon_settings() {

  m_settings = new QSettings(QSettings::IniFormat,QSettings::UserScope,"JanSoft","physiomon");
  
  m_numchan = 0;
  m_numdisp = 0;

  return;
}

// destructor
//
//    clear the memory

physiomon_settings::~physiomon_settings() {

  //-jm if (m_displays != NULL) delete m_displays;
  //-jm if (m_channels != NULL) delete m_channels;
  //-jm if (m_events != NULL) delete m_events;
  
  return;
}

//  initialisation

void physiomon_settings::initialise() {
  return;
}

// iniRead
//
//    Reads the configuration files. This is done in seperate steps and for each greup
//    a seperate (private) method is used
//
//    The device name is returned

QString physiomon_settings::iniRead() {

  readGeneral();
  readChannels();
  readDisplaySettings();
  readEventSettings();

  return(m_device);

}

// getEventString
//
//    returns the event string beloning by the event

QString physiomon_settings::getEventString(int iEvent) {

  return m_events[iEvent];
}

// readGeneral
//
//    this (private) method reads the settings belonging to the keyword <general>

void physiomon_settings::readGeneral() {

  m_settings->beginGroup("algemeen");
  m_numchan = m_settings->value("numchan",1).toInt();
  m_numdisp = m_settings->value("numdisp",1).toInt();
  m_device = m_settings->value("device","").toString();
  m_settings->endGroup();

}

// readChannels
//
//    this (private) method reads the information that are beloning to the channels and
//    store these in the <m_channels> property

void physiomon_settings::readChannels() {

  char keyName[10];

  for (int iChan = 0; iChan < m_numchan; iChan++) {

    snprintf(keyName,10,"channel %0d",iChan+1);

    m_settings->beginGroup(keyName);
    
    m_channels[iChan].name = m_settings->value("name","").toString();
    m_channels[iChan].source = m_settings->value("source",0).toInt();
    m_channels[iChan].display = m_settings->value("display",0).toInt();
    
    QString tmpType = m_settings->value("type","analog in").toString();
    if (tmpType == QString("analog in")) m_channels[iChan].type = TYPE_ANALOG_IN;
   
    m_settings->endGroup();

  }
}

// readDisplaySettings
//
//  this method reads about the size and position of the displays on the screen

void physiomon_settings::readDisplaySettings() {

  char keyName[10];

  for (int iDisp = 0; iDisp < m_numdisp; iDisp++) {

    snprintf(keyName,10,"display %0d",iDisp+1);

    m_settings->beginGroup(keyName);
    
    m_displays[iDisp].top = m_settings->value("top",0.0).toFloat();
    m_displays[iDisp].left = m_settings->value("left",0.0).toFloat();
    m_displays[iDisp].width = m_settings->value("width",1.0).toFloat();
    m_displays[iDisp].height = m_settings->value("height",1.0).toFloat();
    m_displays[iDisp].ymin = m_settings->value("ymin",0.0).toFloat();
    m_displays[iDisp].ymax = m_settings->value("ymax",0.0).toFloat();
    m_displays[iDisp].timescale = m_settings->value("timescale",0.0).toFloat();
    
    QString mode = m_settings->value("update mode","sweep").toString();
    if (mode.toLower() == QString("scope")) m_displays[iDisp].mode = DISPLAY_MODE_SCOPE;
    if (mode.toLower() == QString("sweep")) m_displays[iDisp].mode = DISPLAY_MODE_SWEEP;
    if (mode.toLower() == QString("strip")) m_displays[iDisp].mode = DISPLAY_MODE_STRIP;

    m_settings->endGroup();
  }
}

// readEventSettings
//
//    this (private) method reads the events labels

void physiomon_settings::readEventSettings() {

  char eventNr[3];
  char eventStr[9];

  for (int iEvent=0;iEvent<MAX_EVENTS;iEvent++) {
 
    snprintf(eventNr,3,"%d",iEvent+1);
    snprintf(eventStr,9,"event %d",iEvent+1);

    m_settings->beginGroup("events");
    m_events[iEvent] = m_settings->value(eventNr,"").toString();
    if (m_events[iEvent] == "") m_events[iEvent] = eventStr;
    m_settings->endGroup();
  }
}