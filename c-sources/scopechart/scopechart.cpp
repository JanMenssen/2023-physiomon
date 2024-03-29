//
// scopeChart
//
//    implementation ot fhe <scopeChart> class. This class updates the screen like a oscilloscope, if on 
//    the upper right part of the screen the next point overrides the points on the left 
//
// modifications
//    26-jan-2024  JM   initial version
//    23-feb-2024  JM   now derived from <graphchart> due to introduction numeric display

#include "scopechart.h"

// constructor

scopeChart::scopeChart(int nchan, int *chanlist) : graphChart(nchan,chanlist) {
 
  // create a red line reference for the current position

  m_scopeLine = new QLineSeries();
  this->addSeries(m_scopeLine);
  m_scopeLine->attachAxis(getXaxisRef());
  m_scopeLine->attachAxis(getYaxisRef());
  
  // the legend show a red line name "current pos."
  
  m_scopeLine->setName("current pos.");

  QPen pen = m_scopeLine->pen();
  pen.setWidth(1);
  pen.setColor("red");
  m_scopeLine->setPen(pen);

  for (int i=0;i<m_numchan;i++) m_indx[i] = 0;
  for (int i=0;i<m_numchan;i++) m_dataBuffer[i].reserve(MAX_POINTS_IN_GRAPH);

  m_firstScreen = true;
}

// destructor

scopeChart::~scopeChart() {

}

// setYaxis
//
//  method is overriden because limits should be known

void scopeChart::setYaxis(float ymin, float ymax) {

  graphChart::setYaxis(ymin,ymax);
  
  // and get the limits form the Y-axis (needed when applyNiceNumers is used)

  QValueAxis *yAxis= getYaxisRef();
  m_yLimits[0] = yAxis->min();
  m_yLimits[1] = yAxis->max();
}

// updatePlot
//
//    updates the graph with new points from data

void scopeChart::updatePlot(int ichan, int nsamples, float *data) {

  // locally variables are faster
  
  int indx = m_indx[ichan];
  float deltaT = m_deltaT[ichan];
  int maxindx = m_pntsInGraph[ichan];

  QVector<QPointF> *buffer = &m_dataBuffer[ichan];

  // downsample the data and place the points in the buffer

  m_downSampler[ichan].getData(&nsamples,data);

  if (m_firstScreen) {

    // first screen, append to the buffer (until the number of samples exceed the buffer size)
    
    if (indx + nsamples > maxindx) nsamples = maxindx - indx;
    for (int i = 0 ; i < nsamples ; i++) buffer->append(QPointF((indx+i) * deltaT, data[i]));
  
  } else {

    // replace points in the buffer

    if (indx + nsamples > maxindx) nsamples = maxindx - indx;
    for (int i = 0 ; i < nsamples ; i++) buffer->replace(indx+i,QPointF((indx+i)*deltaT, data[i]));
  }

  // donem update the current position

  m_indx[ichan] = indx + nsamples;
}

// finishUpdatePlot
//
//    draws the red line on the screen after the first screen

void scopeChart::finishUpdatePlot() {

  graphChart::finishUpdatePlot();
  
  if (!m_firstScreen) {
    
    QVector<QPointF> posline;
    float atX = m_indx[0] * m_deltaT[0];
    posline.append(QPointF(atX,m_yLimits[0]));
    posline.append(QPointF(atX,m_yLimits[1]));

    m_scopeLine->replace(posline);
  }
}

