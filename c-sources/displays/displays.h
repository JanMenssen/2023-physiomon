//
// displays
//
//    header file for the <displays> class, software for the graphics charts on
//    the screen
//
// modifications
//    14-jan-2024   JM   initial version

#ifndef _DISPLAYS_H
#define _DISPLAYS_H

#include "settings.h"
#include "channels.h"

class displays {

  public :

    displays();
    ~displays();

    void initialise();
    void configure(settings *settings);
    void plot(channels *channels);

};

#endif