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
#include "baseChart.h"

#include <QWidget>
#include <QGridLayout>
#include <QChartView>

enum viewMode {MODE_STRIP = 0, MODE_SWEEP = 1, MODE_SCOPE = 2};

struct dispSettingStruct {
  int nchan = 0;
  int chanlist[5];
  baseChart *chart = NULL;
};

class displays {

  public :

    displays(QWidget *centralWidget);
    ~displays();

    void initialise();
    void configure(settings *settings);
    void plot(channels *channels);

  private :

    int m_numDisplays = 0;
    dispSettingStruct *m_dispContents = NULL;
    QGridLayout *m_layout  = NULL;
};

#endif