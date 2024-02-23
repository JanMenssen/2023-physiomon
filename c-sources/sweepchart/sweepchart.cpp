//
// sweepChart.cpp
//
//    implementation of the <sweepChart> class. This class updates the screen like a oscilloscope in sweep 
//    mode. If on the end of ths screen, the scteen is cleared and the next pixel is on the levt 
//
//  modifications
//    26-jan-2025   JM    initial version
//    24-jan-2024   JM    now based on <graphchart> due to introduction numeric display

#include "sweepchart.h"

// constructor
// 
//    allocate memory for the points buffer -> faster

sweepChart::sweepChart(int nchan, int *chanlist) : graphChart(nchan, chanlist) {

}

// destructor

sweepChart::~sweepChart() {
  
}

// update

void sweepChart::update(int ichan, int nsamples, float *data) {

  // faster to use local variables

  int indx = m_indx[ichan];    
  int maxindx = m_pntsInGraph[ichan];       
  double deltaT = m_deltaT[ichan];
  QVector<QPointF> *buffer = &m_dataBuffer[ichan];

  // downsample the data
 
  m_downSampler[ichan].getData(&nsamples,data);
 
  // and place the data in the (cleared) buffer, checks the samples exceeds the size of the buffer

  if (indx + nsamples > maxindx) nsamples = maxindx - indx;
  for (int i = 0 ; i < nsamples ; i++) buffer->append(QPointF((indx+i) * deltaT,data[i]));

  // and update the current position

  m_indx[ichan] = indx + nsamples;
}

// initUpdate
//
//    clear the screen if the plotting is on the end of the screen 

bool sweepChart::initUpdate() {

  bool endReached  = graphChart::initUpdate();
  
  if (endReached) {
    for (int ichan=0;ichan<m_numchan;ichan++) m_dataBuffer[ichan].clear();
  }  

  return endReached;
}
  