//
// scopeChart
//
//    implementation ot fhe <scopeChart> class. This class updates the screen like a oscilloscope, if on 
//    the upper right part of the screen the next point overrides the points on the left 
//
// modifications
//    26-jan-2024  JM   initial version

#include "scopechart.h"

// constructor

scopeChart::scopeChart(int nchan) : baseChart(nchan) {
 
  // create a red line reference for the current position

  QValueAxis *x_axis = getXaxisRef();
  QValueAxis *y_axis = getYaxisRef();

  m_scopeLine = new QLineSeries();
  m_chart->addSeries(m_scopeLine);
  m_scopeLine->attachAxis(x_axis);
  m_scopeLine->attachAxis(y_axis);

  QPen pen = m_scopeLine->pen();
  pen.setWidth(1);
  pen.setColor("red");
  m_scopeLine->setPen(pen);

  for (int i=0;i<m_numchan;i++) m_curIndx[i] = 0;
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

  baseChart::setYaxis(ymin,ymax);
  
  // and get the limits form the Y-axis (needed when applyNiceNumers is used)

  QValueAxis *yAxis= getYaxisRef();
  m_yLimits[0] = yAxis->min();
  m_yLimits[1] = yAxis->max();
}

// update
//
//    updates the graph with new points from data

void scopeChart::update(int ichan, int nsamples, float *data) {

  // locally variables are faster
  
  int indx = m_curIndx[ichan];
  float deltaT = m_deltaT[ichan];
  int maxindx = m_pntsInGraph[ichan];

  QVector<QPointF> *buffer = &m_dataBuffer[ichan];

  // downsample the data and place the points in the buffer

  m_downSampler[ichan].getData(&nsamples,data);

  if (m_firstScreen) {

    // first screen, append to the buffer
    
    for (int i = 0 ; i < nsamples ; i++) buffer->append(QPointF((indx+i) * deltaT, data[i]));
  
  } else {

    // replace points in the buffer

    for (int i = 0 ; i < nsamples ; i++) buffer->replace(indx+i,QPointF((indx+i)*deltaT, data[i]));
  }

  m_series[ichan]->replace(m_dataBuffer[ichan]);
  m_curIndx[ichan] = indx + nsamples;
}

// finishUpdate
//
//    performs actions on the chart, that are not series dependent

void scopeChart::initUpdate() {

  bool endReached = true;

  // check if end is reached for all channels and if this is the case reset the current index. Add some extra
  // points to avoid in the update loop every time a check on (index + nsamples) m_pntsInGraph

  for (int iChan=0;iChan<m_numchan;iChan++) endReached = endReached && (m_curIndx[iChan] >= m_pntsInGraph[iChan]);
  
  if (endReached) {

    for (int ichan=0;ichan<m_numchan;ichan++) m_curIndx[ichan] = 0;
    if (m_firstScreen) addExtraPoints(0.1);
    m_firstScreen = false;
    
  } 

  // draw a red horizontal line to indicate the current position, only after the first screen

  if (!m_firstScreen) {
  
    QVector<QPointF> posline;
    float atX = m_dataBuffer[0].at(m_curIndx[0]).x();
    posline.append(QPointF(atX,m_yLimits[0]));
    posline.append(QPointF(atX,m_yLimits[1]));

    m_scopeLine->replace(posline);
  }
}

// addExtraPoints
//
//    this routine add extra points for <time> s. This avoids the check in the update loop the current
//    position is larger as the points in the buffer. However more points are plotted 

void scopeChart::addExtraPoints(float time) {

  for (int ichan=0;ichan<m_numchan;ichan++) {

    QPointF tmp = QPointF((m_pntsInGraph[ichan] * m_deltaT[ichan]) + 0.1,0);

    int nSamples = time / m_deltaT[ichan];
    for (int iSample=0;iSample<nSamples;iSample++) m_dataBuffer[ichan].append(tmp);
  }
}
