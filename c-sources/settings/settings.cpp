//
// settings.cpp
//
//    implementation of the settings class. This class reads the settings from the INI file and 
//    distributes these to the other classes. It makes use of the Qsettings class of the QT
//    framework
//
// modifications
//    08-jan-2024 JM  initial version

#include "settings.h"
#include <stdio.h>

// constructor

settings::settings() {
  printf("\n in settings constructor");
}

//  initialisation

void settings::initialise() {
}

// iniRead
//
//    Reads the configuration files. This is done in seperate steps and for each greup
//    a seperate (private) method is used

void settings::iniRead() {
}

// readGeneral
//
//    this (private) method reads the settings belonging to the keyword <general>

void settings::readGeneral() {
}

// readChannels
//
//    this (private) method reas the information that are beloning to the channels

void settings::readChannels() {
}

// readDisplaySettings
//
//  this method reads about the size and position of the displays on the screen

void settings::readDisplaySettings() {
}

// readEventSettings
//
//    this (private) method reads the events labels

void settings::readEventSettings() {
}
