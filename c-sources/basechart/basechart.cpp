//
// baseChart.cpp
//
//      this is the implementation of the abstract class <baseChart>
//
//  modifications
//    26-jan-2024   JM  initial version

#include "baseChart.h"

// constructor

baseChart::baseChart(int nchan) {

  m_chart = new QChart();
  
  m_axisX = new QValueAxis();
  m_axisY = new QValueAxis();

  // create for every channel a QlineSeries object and add the axis to it
  
  for (int ichan = 0; ichan < nchan; ichan++) {

    m_series[ichan] = new QLineSeries();
    m_chart->addSeries(m_series[ichan]);

    m_series[ichan]->attachAxis(m_axisX);
    m_series[ichan]->attachAxis(m_axisY);
  }

  m_axisX->setGridLineVisible(false);
  m_axisX->setLabelsColor(Qt::cyan);

  m_axisY->setGridLineVisible(false);
  m_axisY->setLabelsColor(Qt::cyan);

  m_chart->legend()->hide();
  m_chart->setBackgroundVisible(false);

  m_chart->addAxis(m_axisX,Qt::AlignBottom);
  m_chart->addAxis(m_axisY,Qt::AlignLeft);

}

// destructor

baseChart::~baseChart() {

  if (m_axisY != NULL) delete m_axisY;
  if (m_axisX != NULL) delete m_axisX;
  if (m_series != NULL) delete m_series;
  if (m_chart != NULL) delete m_chart;

}

// getChart
//
//    returns the chart

QChart *baseChart::getChart() {
  
  return m_chart;
}
