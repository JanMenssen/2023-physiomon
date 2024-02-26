//
// numericChart.cpp
//
//      this is the implementation of the abstract class <graphChart>
//
//  modifications
//    26-jan-2024   JM  initial version
//    23-feb-2024   JM  renamed to graphchart, due to introduction numeric display

#include "numericchart.h"
#include "QGraphicsScene"
#include "QGraphicsView.h"

// constructor 

numericChart::numericChart(int nchan, int *chanlist) : baseChart(nchan,chanlist) {

  // create the graphics

  m_axisX = new QValueAxis();
  m_axisY = new QValueAxis();

  addAxis(m_axisX,Qt::AlignBottom);
  addAxis(m_axisY,Qt::AlignLeft);

  m_axisX->setGridLineVisible(false);
  m_axisX->setLabelsColor(Qt::lightGray);

  m_axisY->setGridLineVisible(false);
  m_axisY->setLabelsColor(Qt::lightGray);

  // axis are hidden, but we make use of it

  m_axisY->hide();
  m_axisX->hide();

  this->removeAllSeries();

  m_series = new QScatterSeries();
  
  this->addSeries(m_series);
  m_series->attachAxis(m_axisX);
  m_series->attachAxis(m_axisY);
  m_series->setUseOpenGL(true);

  // and create pointers for the labels and the values

  m_label = new QGraphicsSimpleTextItem *[m_numchan];
  m_value = new QGraphicsSimpleTextItem *[m_numchan];
}

// destructor

numericChart::~numericChart() {
}

// setLabels
//
//    this routines copies the channel names from the settings struct so the <plotLabel> routine 
//    can plot them

void numericChart::setLabels(physiomon_settings *settings) {

  for(int i=0;i<m_numchan;i++) {
    int curchan = m_channels[i];
    m_labelTxt.append(settings->m_channels[curchan].name);
  }
}

// initPlot
//
//    initialises the plot, channels contains the color and the labels so set up
//    the labels 

void numericChart::initPlot(physiomon_channels *channels) {
  
  // determine vertical or horizontal mode

  calcValuePositions();
  calcLabelPositions();

  // and initial set label on the graph
  
  //-jm for (int i=0;i<m_numchan;i++) m_series->append(m_valuePos[i]);
  //-jm for (int i=0;i<m_numchan;i++) m_series->append(m_labelPos[i]);

  for (int i=0;i<m_numchan;i++) plotLabel(i,m_labelTxt[i]);

}


// updatePlot
//
//    place the average value on the screen if nsamples > 0, else keep the
//    value on the screen

void numericChart::updatePlot(int ichan, int nsamples, float *data) {

  // calculate the average value if nsamples > 0 and convert it to a string

  if (nsamples > 0) {
    m_average[ichan] =0.0;
    for (int i=0;i<nsamples;i++) m_average[ichan] += data[i];
    m_average[ichan] = m_average[ichan] / nsamples;
  }

  // and plot it on the screen

  plotValue(ichan,m_average[ichan]);

}

// initUpdatePlot
//
//    clears the current value on the screen

bool numericChart::initUpdatePlot() {

  // plot the label on the screen and return true

  for (int i=0;i<m_numchan;i++) plotLabel(i,m_labelTxt[i]);

  return true;
}

// finishUpdate

void numericChart::finishUpdatePlot() {
}

// calcValuePositions
//
//    this routine calculates the positions on the chart were the numeric values should be
//    displayed. These positions are in graph coordinates, these change during a resize

void numericChart::calcValuePositions() {
  
  QRectF area = this->plotArea();
  
  if (area.height() >= area.width()) {
  
    // vertical mode, numerics above each other

    float y_inc = 1.0 / (m_numchan + 1);
    for (int i=0;i<m_numchan;i++) m_valuePos[i] = QPointF(0.5,(i+1)*y_inc);

  } else {

    // horizontal mode, numerics below each other

    float x_inc = 1.0 / (m_numchan + 1);
    for (int i=0;i<m_numchan;i++) m_valuePos[i] = QPointF((i+1)*x_inc,0.5);  
  }
}

// calcLabelositions
//
//    this routine calculates the positions on the chart were the numeric values should be
//    displayed. These positions are in graph coordinates, these change during a resize

void numericChart::calcLabelPositions() {
  
  QRectF area = this->plotArea();
  
  if (area.height() >= area.width()) {
  
    // vertical mode, numerics above each other

    float y_inc = 1.0 / (m_numchan + 1);
    for (int i=0;i<m_numchan;i++) m_labelPos[i] = QPointF(0.5,(i+1)*y_inc+0.2);

  } else {

    // horizontal mode, numerics below each other

    float x_inc = 1.0 / (m_numchan + 1);
    for (int i=0;i<m_numchan;i++) m_labelPos[i] = QPointF((i+1)*x_inc,0.8);  
  }
}

// plotLabel
//
//    this routine plots the label (the signal name on the screen

void numericChart::plotLabel(int n, QString labelTxt) {

  // first map to screen coordinates

  QPointF pixelPos = this->mapToPosition(m_labelPos[n]);

  // delete the current label if it exists

  if (m_label[n] != nullptr) delete(m_label[n]);

  // this should be done in the setLabel routine, however now it is tempory done here

  m_label[n] = new QGraphicsSimpleTextItem(labelTxt,this);
  m_label[n]->setFont(QFont());
  m_label[n]->setBrush(Qt::lightGray);

  // and position in the middle of the calculated point

  QRectF rectangle = m_label[n]->boundingRect();
  m_label[n]->setPos((pixelPos.x() - rectangle.width()/2), (pixelPos.y() - rectangle.height()/2 ));

  // done
}

// plotValue
//
//    this routine plots the value on the screen

void numericChart::plotValue(int n, float value) {

  // map to screen coordinates

  QPointF pixelPos = this->mapToPosition(m_valuePos[n]);

  // delete the current label if it exists

  if (m_value[n] != nullptr) delete(m_value[n]);

  // this should be done in the setLabel routine, however now it is tempory done here

  QString valueTxt = QString("%1").arg(value,0,'f',1);
  
  m_value[n] = new QGraphicsSimpleTextItem(valueTxt,this);
  m_value[n]->setFont(QFont());
  m_value[n]->setBrush(Qt::green);

  // and position in the middle of the calculated point

  QRectF rectangle = m_value[n]->boundingRect();
  m_value[n]->setPos((pixelPos.x() - rectangle.width()/2), (pixelPos.y() - rectangle.height()/2 ));

  // done
}



