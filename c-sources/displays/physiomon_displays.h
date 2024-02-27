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
#include "basechart.h"
#include "physiomon_settings.h"
#include "physiomon_channels.h"

#include <QWidget>
#include <QGridLayout>
#include <QChartView>


class physiomon_displays {

  public :

    physiomon_displays(QWidget *centralWidget);
    ~physiomon_displays();

    void initialise();
    void configure(physiomon_settings *settings);
    void plot(physiomon_channels *channels);
    void initPlot(physiomon_channels *channels);

  private :

    int m_numDisplays = 0;
    baseChart **m_chart;
    QGridLayout *m_layout  = NULL;
};

#endif