//
// physiomon_displays
//
//    header file for the <displays> class, software for the graphics charts on
//    the screen
//
// modifications
//    14-jan-2024   JM   initial version
//    11-feb-2024   JM   renamed to <physiomon_displays

#ifndef _PHYSIOMON_DISPLAYS_H
#define _PHYSIOMON_DISPLAYS_H

#include "physiomon.h"
#include "physiomon_settings.h"
#include "physiomon_channels.h"
#include "basechart.h"

#include <QWidget>
#include <QGridLayout>
#include <QChartView>



struct dispSettingStruct {
  int nchan = 0;
  int chanlist[5];
  //jm enum colors 
  //jm labels ?
  baseChart *chart = NULL;
};

class physiomon_displays {

  public :

    physiomon_displays(QWidget *centralWidget);
    ~physiomon_displays();

    void initialise();
    void configure(physiomon_settings *settings);
    void initPlot(physiomon_channels *channels);
    void plot(physiomon_channels *channels);

  private :

    int m_numDisplays = 0;
    dispSettingStruct *m_dispContents = NULL;
    QGridLayout *m_layout  = NULL;
};

#endif