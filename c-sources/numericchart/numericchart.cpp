//
// numericChart.cpp
//
//      this is the implementation of the numerics chart
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

  // set the font used to the standard font

  m_usedFont = QFont();
  m_scaleFactor = 1;  
}

// destructor

numericChart::~numericChart() {
}

// setLabels
//
//    this routines copies the channel names from the settings struct so the <plotLabel> routine 
//    can plot them

void numericChart::setLabels(channelStruct *channelInfo) {

  for(int i=0;i<m_numchan;i++) {
    int curchan = m_channels[i];
    m_labelTxt.append(channelInfo[curchan].name);
  }
}

// setColors
//
//    sets the colors for the labels

void numericChart::setColors(channelStruct *channelInfo) {
  
  int alpha = 255;

  for (int ichan=0;ichan<m_numchan;ichan++) {

    int curchan = m_channels[ichan];
    switch (channelInfo[curchan].color) {

      case COLOR_RED :
        m_valueColor[ichan] = QColor(255,0,0,alpha);
        break;

      case COLOR_GREEN :
        m_valueColor[ichan] = QColor(0,255,0,alpha);
        break;

      case COLOR_BLUE :
        m_valueColor[ichan] = QColor(0,0,255,alpha);
        break;

      case COLOR_CYAN :
        m_valueColor[ichan] = QColor(0,255,255,alpha);
        break;

      case COLOR_MAGENTA :
        m_valueColor[ichan] = QColor(255,0,255,alpha);
        break;
      
      case COLOR_YELLOW:
        m_valueColor[ichan] = QColor(255,255,0,alpha);
        break;
      
      case COLOR_BLACK :
        m_valueColor[ichan] = QColor(0,0,0,alpha);
         break;
      
      case COLOR_WHITE :
        m_valueColor[ichan] = QColor(255,255,255,alpha);
        break;

      default :
        m_valueColor[ichan] = QColor(0,255,0,alpha);

    }
  }
}

// setPrecision
//
//    reads the precions (number of digits after decimal) for the selected channels
//    and stores this in an internal member variable that is used in <plotValues>

void numericChart::setPrecision(channelStruct *channelInfo) {

  for (int ichan=0;ichan<m_numchan;ichan++) {

    int curchan = m_channels[ichan];
    m_precision[ichan] = channelInfo[curchan].precision;
  }
}

// initPlot
//
//    initialises the plot, channels contains the color and the labels so set up
//    the labels 

void numericChart::initPlot(physiomon_channels *channels) {
  
  // calculate the position of the values and labels in graph coordinates

  calcValuePositions();
  calcLabelPositions();

  m_scaleFactor = calcScaleFactor();

  // and plot the label

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

  m_scaleFactor = calcScaleFactor();
  
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
    for (int i=0;i<m_numchan;i++) m_valuePos[i] = QPointF(0.5,1-(i+1)*y_inc);

  } else {

    // horizontal mode, numerics below each other

    float x_inc = 1.0 / (m_numchan + 1);
    for (int i=0;i<m_numchan;i++) m_valuePos[i] = QPointF((i+1)*x_inc,0.5);  
  }
}

// calcLabelPositions
//
//    this routine calculates the positions on the chart were the numeric values should be
//    displayed. These positions are in graph coordinates, these change during a resize

void numericChart::calcLabelPositions() {
  
  QRectF area = this->plotArea();
  
  if (area.height() >= area.width()) {
  
    // vertical mode, numerics above each other

    float y_inc = 1.0 / (m_numchan + 1);
    for (int i=0;i<m_numchan;i++) m_labelPos[i] = QPointF(0.5,1-(i+1)*y_inc+0.11);

  } else {

    // horizontal mode, numerics below each other

    float x_inc = 1.0 / (m_numchan + 1);
    for (int i=0;i<m_numchan;i++) m_labelPos[i] = QPointF((i+1)*x_inc,0.8);  
  }
}

// plotLabel
//
//    this routine plots the label (the signal name) on the screen. This is done by converting
//    the chart coordinates and place the label centered around the calculaed position

void numericChart::plotLabel(int n, QString labelTxt) {

  // first map to screen coordinates

  QPointF pixelPos = this->mapToPosition(m_labelPos[n]);

  // delete the current label if it exists

  if (m_label[n] != nullptr) delete(m_label[n]);

  // this should be done in the setLabel routine, however now it is tempory done here

  m_label[n] = new QGraphicsSimpleTextItem(labelTxt,this);
  m_label[n]->setFont(m_usedFont);
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

  float scaleFactor = 2.5;

  // map to screen coordinates

  QPointF pixelPos = this->mapToPosition(m_valuePos[n]);

  // delete the current label if it exists

  if (m_value[n] != nullptr) delete(m_value[n]);

  // this should be done in the setLabel routine, however now it is tempory done here

  QString valueTxt = QString::number(value,'f',m_precision[n]);

  m_value[n] = new QGraphicsSimpleTextItem(valueTxt,this);
  m_value[n]->setFont(m_usedFont);
  m_value[n]->setScale(m_scaleFactor);
  m_value[n]->setBrush(m_valueColor[n]);

  // and position in the middle of the calculated point

  QRectF rectangle = m_value[n]->boundingRect();
  m_value[n]->setPos((pixelPos.x() - m_scaleFactor * rectangle.width()/2), (pixelPos.y() - m_scaleFactor * rectangle.height()/2 ));

  // done
}

// calcScalefactor
//
//    calculates the factor the value are larger than the labels, this is calculated arbitrary and could be
//    done better

float numericChart::calcScaleFactor() {

float scale = 1.0;

  QPointF labelPosInPixel = this->mapToPosition(m_labelPos[0]);
  QPointF valuePosInPixel = this->mapToPosition(m_valuePos[0]);

  float diff = abs(labelPosInPixel.y() - valuePosInPixel.y());
  scale = diff / 12.5;

  return scale;
}
