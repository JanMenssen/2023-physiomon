//
// stripChart.h
//
//    class that updates the screen like a paper strip recorder. If on the end of the screen, data is shifted
//    to the left and new points are added to the right
//
//  modifications
//    26-jan-2025   JM    initial version

#ifndef _STRIPCHART_H
#define _STRIPCHART_H

#include "basechart.h"

#include <QPointF>
#include <QList>

class stripChart: public baseChart {

  public :

    stripChart(int nchan,int *chanlist);
    ~stripChart();
    void update(int ichan, int nsamples, float *data); 
};

#endif