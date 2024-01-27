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

    stripChart(int nchan);
    ~stripChart();
    void setTimeAxis(float nsec);
    void update(int nchan, int nsamples, float *data);

  private :

    float *m_dataValues = NULL;
    QLineSeries *m_series = NULL;
    long m_npoints = 0;
    int m_sampleRate = 1000;
    QList<QPointF> m_buffer;  
};

#endif