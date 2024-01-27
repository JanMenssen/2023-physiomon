#
# displays_grid.py
#
#         contains the software for the graphs and update the graphs on the screen. This in the
#         grid implementation 
#
#   modifications
#     16-jan-2024 JM    initial version

from PySide6.QtWidgets import QGridLayout,QWidget
from PySide6.QtCharts import QChartView
from stripchart import stripChart

RESOLUTION = 0.05

class displays() :

  # constructor

  def __init__(self,centralWidget) :

    self.m_graphDisplay = []
    self.m_numDisplay = 0
    self.m_chanlist = []

    self.m_layout = QGridLayout()
    self.m_layout.setHorizontalSpacing(0)
    self.m_layout.setVerticalSpacing(0)
    centralWidget.setLayout(self.m_layout)
      
    return
  
  # initialise
  #
  #   initialise the class

  def initialise(self) :

    return
  
  # configure
  #
  #   sets the number of required displays on the screen 

  def configure(self,settings) :
  
    # clear the current settings

    nWidgets = self.m_layout.count()
    for item in range(nWidgets) :
      self.m_layout.removeItem(item)
  
    self.m_graphDisplay = []
    self.m_numDisplay = 0
    self.m_chanlist = []

    # and add the stripcharts

    self.m_numDisplay = settings.m_numdisp
    
    maxcol = 0
    maxrow = 0

    for iDisplay in range(self.m_numDisplay) :

      self.m_chanlist.append([])
    
      # get the channel

      numChannels = settings.m_numchan
      for iChannel in range(numChannels) :

        if ((settings.m_channels[iChannel]["display"]-1) == iDisplay) :
          self.m_chanlist[iDisplay].append(iChannel)

      self.m_graphDisplay.append(stripChart())
    
      # set the widget at the position, we assume to have a grid layout of 20 x 20, this means each
      # relative position should divided by 0.05

      position,scale = settings.getDisplayInfo(iDisplay)

      irow = round(position["top"] / RESOLUTION)
      nrow = round(position["height"] / RESOLUTION)
      icol = round(position["left"] / RESOLUTION)
      ncol = round(position["width"] / RESOLUTION)

      # display is waveform        
      
      chartView = QChartView(self.m_graphDisplay[iDisplay].m_chart)
      self.m_layout.addWidget(chartView,irow,icol,nrow,ncol)

      # display is numeric, numeric should be added  

      # calculate max position

      if ((icol + ncol) > maxcol) :
        maxcol = icol + ncol
      if ((irow + nrow) > maxrow) :
        maxrow = irow + nrow

    # add items if necessary, to get a grid of 1/RESOLUTION x 1/RSOLUTION 
        
    irow = maxrow
    icol = maxcol
    nrow = 1/RESOLUTION - irow
    ncol = 1/RESOLUTION - icol
     
    if nrow > 0 :
      self.m_layout.addWidget(QWidget(),irow,0,nrow,int(1/RESOLUTION))
    if ncol > 0 :
      self.m_layout.addWidget(QWidget(),0,icol,int(1/RESOLUTION),ncol)
      
    return
  
  # plot
  #
  #   update the display with data

  def plot(self,channels) :

    if self.m_numDisplay > 0 :

      for iDisplay in range(self.m_numDisplay) :

        # get the channel list for this display and update the display

        chanList = self.m_chanlist[iDisplay]  

        # if display is analog

        for iChannel in chanList :  
          data = channels.readData(iChannel)
          self.m_graphDisplay[iDisplay].update(data)
  
        # if display is numeric
          
    return
  
  # setStartWaveFrom
  #
  #   sets the start time of the data

  def setStartWaveform(self) :
    return