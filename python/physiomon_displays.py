#
# physiomon_displays.py
#
#         contains the software for the graphs and update the graphs on the screen. This in the
#         grid implementation 
#
#   modifications
#     16-jan-2024 JM    initial version
#     11-feb-2024 JM    renamed to <physiomon_displays>

from PySide6.QtWidgets import QGridLayout,QWidget
from PySide6.QtCharts import QChartView
from PySide6.QtCore import Qt
from stripchart import stripChart
from sweepchart import sweepChart
from scopechart import scopeChart

RESOLUTION = 0.05

class physiomon_displays() :

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

    for iDisp in range(self.m_numDisplay) :

      curDisplay = settings.m_displays[iDisp]

      self.m_chanlist.append([])
    
      # get the channel

      numChannels = settings.m_numchan
      for iChannel in range(numChannels) :

        if ((settings.m_channels[iChannel]["display"]-1) == iDisp) :
          self.m_chanlist[iDisp].append(iChannel)

      # mode for the display

      nchan = len(self.m_chanlist[iDisp])

      if (curDisplay["mode"].lower() == 'sweep') :
        self.m_graphDisplay.append(sweepChart(nchan))
      if (curDisplay["mode"].lower() == 'scope') :
        self.m_graphDisplay.append(scopeChart(nchan))
      if (curDisplay["mode"].lower() == 'strip') :
        self.m_graphDisplay.append(stripChart(nchan))
   
    
      # set the widget at the position, we assume to have a grid layout of 20 x 20, this means each
      # relative position should divided by 0.05


      irow = round(curDisplay["top"] / RESOLUTION)
      nrow = round(curDisplay["height"] / RESOLUTION)
      icol = round(curDisplay["left"] / RESOLUTION)
      ncol = round(curDisplay["width"] / RESOLUTION)

      # display is waveform        
   
      chartView = QChartView(self.m_graphDisplay[iDisp].m_chart)
      self.m_layout.addWidget(chartView,irow,icol,nrow,ncol)

      # bug in using touchpad, changes in display causes a message, this bug is not solved by
      # this command
      
      chartView.setAttribute(Qt.WidgetAttribute.WA_AcceptTouchEvents, False)

      # display is numeric, numeric should be added  


      # calculate max position

      if ((icol + ncol) > maxcol) :
        maxcol = icol + ncol
      if ((irow + nrow) > maxrow) :
        maxrow = irow + nrow

      # and set the axis
        
      self.m_graphDisplay[iDisp].setYaxis(curDisplay['ymin'],curDisplay["ymax"])
      self.m_graphDisplay[iDisp].setTimeAxis(curDisplay["timescale"])
      
    # add items if necessary, to get a grid of 1/RESOLUTION x 1/RSOLUTION 
        
    irow = maxrow
    icol = maxcol
    nrow = 1/RESOLUTION - irow
    ncol = 1/RESOLUTION - icol
     
    if nrow > 0 :
      self.m_layout.addWidget(QWidget(),irow,0,nrow,int(1/RESOLUTION))
    if ncol > 0 :
      self.m_layout.addWidget(QWidget(),0,icol,int(1/RESOLUTION),ncol)

    # and set the axis

  # initPlot
  #
  #     initialises the current chart. Using the sampleRate information stored in the instance
  #     of channels, the baseChart method <initBuffers> is called
      
  def initPlot(self,channels) :
    
    if (self.m_numDisplay > 0) :

      for iDisplay in range(self.m_numDisplay) :  

        sampleRate = []
        chanList = self.m_chanlist[iDisplay]  
        nchan = len(chanList)

        for iChannel, i in zip(chanList,range(nchan)) :  
          sampleRate.append(channels.getSampleRate(iChannel))
          
        self.m_graphDisplay[iDisplay].initPlot(sampleRate)

 
  # plot
  #
  #   update the display with data

  def plot(self,channels) :

    if self.m_numDisplay > 0 :

      for iDisplay in range(self.m_numDisplay) :

        # get the channel list for this display and update the display
       
        self.m_graphDisplay[iDisplay].initUpdate()

        chanList = self.m_chanlist[iDisplay]  
        nchan = len(chanList)

        for iChannel, i in zip(chanList,range(nchan)) :  
          data = channels.readData(iChannel)
          self.m_graphDisplay[iDisplay].update(i,data)
  
