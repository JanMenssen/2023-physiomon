//
// baseChart.cpp
//
//      this is the implementation of the abstract class <baseChart>
//
//  modifications
//    26-jan-2024   JM  initial version

#include "basechart.h"
#include <string.h>

#include <QDebug>

// baseChart constructor 

baseChart::baseChart(int n, int *chanlist) {

  // set the channels that are in the display
  
  m_numchan = n;
  for (int i=0;i<m_numchan;i++) m_channels[i] = chanlist[i]; 

  // create the grapchids

  setMargins(QMargins(10,5,5,5));
  legend()->hide();
  setBackgroundVisible(false);  
}

// baseChart destructor

baseChart::~baseChart() {
}





