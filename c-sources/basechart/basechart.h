//
// baseChart.h
//
//    abstract class for the graphic displays. Do not use this class but use the inherited classes instead
// 
//        - scopeChart   : updating like an oscilloscope
//        - stripChart   : updating like a paper stripschart recorder
//        - sweepChart   : sweep updating mode
//
//  modifications
//    26-jan-2025   JM    initial version

#ifndef _BASECHART_H
#define _BASECHART_H

#include <QChart>
#include <QLineSeries>
#include <QValueAxis>


class baseChart {

  public :
  
    baseChart(int nchan);
    ~baseChart();
    QChart * getChart();

  private :

    QChart *m_chart = NULL;
    QLineSeries **m_series = NULL;
    QValueAxis *m_axisX = NULL;
    QValueAxis *m_axisY = NULL;


};

#endif