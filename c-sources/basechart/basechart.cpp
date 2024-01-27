//
// baseChart.cpp
//
//      this is the implementation of the abstract class <baseChart>
//
//  modifications
//    26-jan-2024   JM  initial version

#include "basechart.h"
#include <QDebug>

// constructor

baseChart::baseChart(int nchan) {

  qDebug() << "--> baseChart::baseChart";

  m_chart = new QChart;
  
  m_axisX = new QValueAxis();
  m_axisY = new QValueAxis();

  m_chart->addAxis(m_axisX,Qt::AlignBottom);
  m_chart->addAxis(m_axisY,Qt::AlignLeft);

  m_axisX->setGridLineVisible(false);
  m_axisX->setLabelsColor(Qt::cyan);

  m_axisY->setGridLineVisible(false);
  m_axisY->setLabelsColor(Qt::cyan);

  m_chart->legend()->hide();
  m_chart->setBackgroundVisible(false);

  // create for every channel a QlineSeries object and add the axis to it
  
  m_series = new QLineSeries[nchan];
  for (int ichan = 0; ichan < nchan; ichan++) {

    m_chart->addSeries(&m_series[ichan]);

    m_series[ichan].attachAxis(m_axisX);
    m_series[ichan].attachAxis(m_axisY);
  }
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

// gertSeries
//
//    returns a reference to the m_series

QLineSeries *baseChart::getSeries() {
  
  return m_series;
}

// setYaxis
//
//    set the scale of the Y axis 

void baseChart::setYaxis(float ymin, float ymax) {

  m_axisY->setRange(ymin,ymax);
}

// setTimeAxis
//
//    set the X-axis (= time) from 0 to <nsec> seconds 

void baseChart::setTimeAxis(float nsec) {

  qDebug() << "-->in basechart::setTimexAxis";
  m_axisX->setRange(0,nsec);
}
