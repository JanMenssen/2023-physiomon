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
#include "stripchart.h"
#include "sweepchart.h"
#include "scopechart.h"

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

void physiomon_displays::configure(physiomon_settings *settings) {
  
  // these parameters are needed to calculate the position in the grid

  int irow = 0, nrow = 0, maxrow = 0;         
  int icol = 0, ncol = 9, maxcol = 0;         

  // first remove the current layout

  int count = m_layout->count();
  for (int i = 0 ; i < count ; i++) m_layout->removeItem(m_layout->itemAt(i));
  if (m_dispContents != NULL) delete m_dispContents;

  int numchan = settings->m_numchan;
  m_numDisplays = settings->m_numdisp;
  m_dispContents = new dispSettingStruct[m_numDisplays];

  for (int iDisp = 0; iDisp < m_numDisplays ; iDisp++) {
  
    displayStruct curDisplay = settings->m_displays[iDisp];
    
    // find the channels for the current display

    for (int iChan = 0 ; iChan < numchan ; iChan++) {
    
      if ((settings->m_channels[iChan].display-1) == iDisp) {
        m_dispContents[iDisp].chanlist[m_dispContents[iDisp].nchan++] = iChan;
   //-jm NITE, add colors and labels
      }   
    }
     
    // hwo to diplay the data

    switch (curDisplay.mode) {

      case DISPLAY_MODE_STRIP :
        m_dispContents[iDisp].chart = new stripChart(m_dispContents[iDisp].nchan);
        break;

      case DISPLAY_MODE_SWEEP :
        m_dispContents[iDisp].chart = new sweepChart(m_dispContents[iDisp].nchan);
        break;

      case DISPLAY_MODE_SCOPE :
        m_dispContents[iDisp].chart = new scopeChart(m_dispContents[iDisp].nchan);
        break;

      default :
        m_dispContents[iDisp].chart = new stripChart(m_dispContents[iDisp].nchan);
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

    QChartView *chartView = new QChartView(m_dispContents[iDisp].chart->getChart());
    m_layout->addWidget(chartView,irow,icol,nrow,ncol);

    // and set the graphic

    m_dispContents[iDisp].chart->setYaxis(curDisplay.ymin, curDisplay.ymax);
    m_dispContents[iDisp].chart->setTimeAxis(curDisplay.timescale);
    //-jm m_dispContents[iDisp].chart->setColors()
    //-jm m_dispContents[iDisp].chart->setLablels();
  }

  // check there is space left in the grid and fill it up with an empty
       
  irow = maxrow;
  icol = maxcol;
  nrow = 1/RESOLUTION - irow;
  ncol = 1/RESOLUTION - icol;
  
  QWidget *tmp = new QWidget();
  if (nrow > 0) m_layout->addWidget(tmp,irow,0,nrow,int(1/RESOLUTION));
  if (ncol > 0) m_layout->addWidget(tmp,0,icol,int(1/RESOLUTION),ncol);
  
}

// plot
//
//    plots the new data

void physiomon_displays::plot(physiomon_channels *channels) {

  float data[100];          // max 100 samples can be read
  int nSamples = 0;       
  dispSettingStruct dispSettings;

  for (int iDisp = 0; iDisp < m_numDisplays ; iDisp++) {

    dispSettings = m_dispContents[iDisp];

    // a display can have more channels, do it for all channels

    for (int ichan = 0;ichan < dispSettings.nchan; ichan++) {

      int curchan = dispSettings.chanlist[ichan];
      
      channels->readDisplay(curchan,&nSamples,data);
      dispSettings.chart->update(ichan,nSamples,data);
    }  
    
    dispSettings.chart->finishUpdate();
  }  

  return;
}