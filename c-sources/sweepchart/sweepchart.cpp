//
// sweepChart.cpp
//
//    implementation of the <sweepChart> class. This class updates the screen like a oscilloscope in sweep 
//    mode. If on the end of ths screen, the scteen is cleared and the next pixel is on the levt 
//
//  modifications
//    26-jan-2025   JM    initial version

#include "sweepchart.h"

// constructor
// 
//    allocate memory for the points buffer -> faster

sweepChart::sweepChart(int nchan) : baseChart(nchan) {

}

// destructor

sweepChart::~sweepChart() {
  
}

// update

void sweepChart::update(int ichan, int nsamples, float *data) {

  // faster

  int indx = m_curIndx[ichan];           
  double deltaT = m_deltaT[ichan];
  QVector<QPointF> *buffer = &m_dataBuffer[ichan];

  // downsample the data
 
  m_downSampler[ichan].getData(&nsamples,data);
 
  // and place the data in the (cleared) buffer

  for (int i = 0 ; i < nsamples ; i++) buffer->append(QPointF((indx+i) * deltaT,data[i]));

  // and append the new data to the series, this is not faster as append point for point
  // so m_buffer is in fact not needed. However, in stripchart and scopechart 

  m_series[ichan]->replace(m_dataBuffer[ichan]);
  m_curIndx[ichan] = indx + nsamples;
}

// finishUpdate
//
//    performs actions on the chart, that are not series dependent

void sweepChart::finishUpdate() {

  // check if end is reached for all channels and if this is the case reset the current index and clear the 
  // dataBuffer 

  bool endReached = true;
  for (int iChan=0;iChan<m_numchan;iChan++) endReached = endReached && (m_curIndx[iChan] >= m_pntsInGraph[iChan]);
  
  if (endReached) {
    m_first = false;
    for (int ichan=0;ichan<m_numchan;ichan++) {
      m_curIndx[ichan] = 0;
      m_dataBuffer[ichan].clear();
    }
  }

  // done
  
}
  