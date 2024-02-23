//
// stripChart.h
//
//    class that updates the screen like a paper strip recorder. If on the end of the screen, data is shifted
//    to the left and new points are added to the right
//
//  modifications
//    26-jan-2024   JM    initial version
//    23-feb-2024   JM    now based on graphchart due to introduction numeric display

#ifndef _STRIPCHART_H
#define _STRIPCHART_H

#include "graphchart.h"

#include <QPointF>
#include <QList>

class stripChart: public graphChart {

  public :

    stripChart(int nchan,int *chanlist);
    ~stripChart();
    void update(int ichan, int nsamples, float *data); 
};

#endif