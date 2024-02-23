//
// numericChart.cpp
//
//      this is the implementation of the abstract class <graphChart>
//
//  modifications
//    26-jan-2024   JM  initial version
//    23-feb-2024   JM  renamed to graphchart, due to introduction numeric display

#include "numericchart.h"

// constructor 

numericChart::numericChart(int nchan, int *chanlist) : baseChart(nchan,chanlist) {

  // create the graphics 

  m_chart = new QChart;
  m_chart->setMargins(QMargins(10,5,5,5));

  m_chart->legend()->hide();
  m_chart->setBackgroundVisible(false);  
}

// destructor

numericChart::~numericChart() {

  if (m_chart != NULL) delete m_chart;
}

// getChart
//
//    returns a reference to the used chart

QChart *numericChart::getChart() {

  return m_chart;
}

// initPlot
//
 
void numericChart::initPlot(physiomon_channels *channels) {

}

// initUpdate

bool numericChart::initUpdate() {

  bool endReached = true;
  return endReached;
}

// finishUpdate

void numericChart::finishUpdate() {
}



