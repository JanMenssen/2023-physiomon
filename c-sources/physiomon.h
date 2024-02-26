//
// physiomon.h
//
//    this is the header file for the main program
//
// modifications
//    08-jan-2024 JM  initial version

#ifndef FYSIOMON_H
#define FYSIOMON_H

// currently only 10 channels and displays are allowed

#define MAX_CHANNELS 20
#define MAX_DISPLAYS 10
#define MAX_EVENTS   10

// some enums

enum typeSignal {TYPE_ANALOG_IN = 1, TYPE_NUMERIC_IN = 2 };
enum viewMode {DISPLAY_MODE_STRIP = 1, DISPLAY_MODE_SWEEP = 2, DISPLAY_MODE_SCOPE = 3, DISPLAY_MODE_NUMERIC = 4};

#endif