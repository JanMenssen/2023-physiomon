//
// physiomon_displays.cpp
//
//    implementation of the <displays> class. This class is responsible for the plotting
//    of the data.
//
//  modifications
//    14-jan-2024   JM  initial version
//    11=feb-2024   JM  renamed to <physiomon_displays>

#include "physiomon.h"
#include "physiomon_displays.h"
#include "basechart.h"
#include "stripchart.h"
#include "sweepchart.h"
#include "scopechart.h"
#include "numericchart.h"

// we use a 20x20 grid this means a resolution of 0.05

#define RESOLUTION 0.05F

// constructor

physiomon_displays::physiomon_displays(QWidget *centralWidget) {

  m_numDisplays = 0;
  
  m_layout = new QGridLayout();
  m_layout->setHorizontalSpacing(0);
  m_layout->setVerticalSpacing(0);
  centralWidget->setLayout(m_layout);
}

// destructor

physiomon_displays::~physiomon_displays() {
/*
  if (m_layout != NULL) delete m_layout;
  if (m_dispContents != NULL) delete m_dispContents;
*/
}

// initialise

void physiomon_displays::initialise() {

}
// configure

void physiomon_displays::configure(physiomon_settings *settings, physiomon_channels *channels) {
  
  int chanlist[MAX_CHANNELS_IN_DISPLAY] = {0,0,0};
  int nchan = 0;

  // these parameters are needed to calculate the position in the grid

  int irow = 0, nrow = 0, maxrow = 0;         
  int icol = 0, ncol = 9, maxcol = 0;         

  // first remove the current layout

  int count = m_layout->count();
  for (int i = 0 ; i < count ; i++) m_layout->removeItem(m_layout->itemAt(i));
  if (m_chart != nullptr) delete m_chart;

  // now make an array of pointers to a baseChart object
  
  m_numDisplays = settings->m_numdisp;
  m_chart = new baseChart *[m_numDisplays];

  for (int idisp = 0; idisp < m_numDisplays; idisp++) {
  
    nchan = 0;
    displayStruct curDisplay = settings->m_displays[idisp];
    
    // find the channels for the current display

    for (int ichan = 0 ; ichan < settings->m_numchan ; ichan++) {
      if ((settings->m_channels[ichan].display-1) == idisp) chanlist[nchan++] = ichan;
    }
     
    // hwo to diplay the data

    switch (curDisplay.mode) {

      case DISPLAY_MODE_STRIP :
        m_chart[idisp] = new stripChart(nchan,chanlist);
        m_chart[idisp]->setYaxis(curDisplay.ymin, curDisplay.ymax);
        m_chart[idisp]->setTimeAxis(curDisplay.timescale);
  
        break;

      case DISPLAY_MODE_SWEEP :
        m_chart[idisp] = new sweepChart(nchan,chanlist);
        m_chart[idisp]->setYaxis(curDisplay.ymin, curDisplay.ymax);
        m_chart[idisp]->setTimeAxis(curDisplay.timescale);
  
        break;

      case DISPLAY_MODE_SCOPE :
        m_chart[idisp] = new scopeChart(nchan,chanlist);
        m_chart[idisp]->setYaxis(curDisplay.ymin, curDisplay.ymax);
        m_chart[idisp]->setTimeAxis(curDisplay.timescale);
  
        break;

      case DISPLAY_MODE_NUMERIC :
        m_chart[idisp] = new numericChart(nchan,chanlist);
        break;

      default :
        m_chart[idisp] = new stripChart(nchan,chanlist);
        m_chart[idisp]->setYaxis(curDisplay.ymin, curDisplay.ymax);
        m_chart[idisp]->setTimeAxis(curDisplay.timescale);
  
        break;
    }

    // calculate the position. we use a gridview of RESOLUTION * RESOLUTION, calculate the column and rows
    // of thc current display
    
    irow = round(curDisplay.top / RESOLUTION);
    icol = round(curDisplay.left / RESOLUTION);
    nrow = round(curDisplay.height / RESOLUTION);
    ncol = round(curDisplay.width / RESOLUTION);

    maxrow = (nrow > maxrow ? nrow : maxrow);
    maxcol = (ncol > maxcol ? ncol : maxcol);

    QChartView *chartView = new QChartView(m_chart[idisp]);
    //-jm chartView->setRenderHint(QPainter::Antialiasing);    
    m_layout->addWidget(chartView,irow,icol,nrow,ncol);

    // colors and labels 

    m_chart[idisp]->setLabels(settings);
  }

  // check there is space left in the grid and fill it up with an empty
       
  irow = maxrow;
  icol = maxcol;
  nrow = 1/RESOLUTION - irow;
  ncol = 1/RESOLUTION - icol;
  
  QWidget *tmp = new QWidget();
  if (nrow > 0) m_layout->addWidget(tmp,irow,0,nrow,int(1/RESOLUTION));
  if (ncol > 0) m_layout->addWidget(tmp,0,icol,int(1/RESOLUTION),ncol);
  
  // and do some initialisation before the actual begin (downsampler)

  for (int idisp=0;idisp<m_numDisplays;idisp++) m_chart[idisp]->initPlot(channels);
}

// plot
//
//    plots the new data

void physiomon_displays::plot(physiomon_channels *channels) {

  float data[1000];                        // max 1000 samples can be read
  int *chanlist = nullptr;
  int nSamples = 0;       

  for (int idisp = 0; idisp < m_numDisplays ; idisp++) {
 
    m_chart[idisp]->initUpdate();
    chanlist = m_chart[idisp]->m_channels;
    int nchan = m_chart[idisp]->m_numchan;

    // a display can have more channels, do it for all channels

    for (int ichan = 0;ichan < nchan; ichan ++) {
      channels->readDisplay(chanlist[ichan],&nSamples,data);
      m_chart[idisp]->update(ichan,nSamples,data);
    }  

    m_chart[idisp]->finishUpdate();
  }  

  return;
}