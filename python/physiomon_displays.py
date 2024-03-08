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
from numericchart import numericChart

RESOLUTION = 0.05

class physiomon_displays() :

  # constructor

  def __init__(self,centralWidget) :

    self.m_chart = []
    self.m_numDisplay = 0

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
    child = self.m_layout.takeAt(0)
    while (child) :
      childWidget = child.widget()
      childWidget.deleteLater()
      child = self.m_layout.takeAt(0)

    self.m_chart = []

    self.m_numDisplay = len(settings.m_displays)
    numchan  = len(settings.m_channels)

    maxcol = 0
    maxrow = 0
    
    for idisp in range(self.m_numDisplay) :
    
      curDisplay = settings.m_displays[idisp]

      # create a list of channels that are in the display

      chanlist = []

      for channel,i in zip(settings.m_channels,range(numchan)) :

        if ((channel["display"]-1) == idisp) : chanlist.append(i)

      # mode for the display

      if (curDisplay["mode"].lower() == 'sweep') :
        self.m_chart.append(sweepChart(chanlist))
        self.m_chart[-1].setYaxis(curDisplay['ymin'],curDisplay["ymax"])
        self.m_chart[-1].setTimeAxis(curDisplay["timescale"])
      
      if (curDisplay["mode"].lower() == 'scope') :
        self.m_chart.append(scopeChart(chanlist))
        self.m_chart[-1].setYaxis(curDisplay['ymin'],curDisplay["ymax"])
        self.m_chart[-1].setTimeAxis(curDisplay["timescale"])
      
      if (curDisplay["mode"].lower() == 'strip') :
        self.m_chart.append(stripChart(chanlist))
        self.m_chart[-1].setYaxis(curDisplay['ymin'],curDisplay["ymax"])
        self.m_chart[-1].setTimeAxis(curDisplay["timescale"])
      
      if (curDisplay["mode"].lower() == 'numeric') :
        self.m_chart.append(numericChart(chanlist))
        self.m_chart[-1].setPrecision(settings.m_channels)
       
      # set the widget at the position, we assume to have a grid layout of 20 x 20, this means each
      # relative position should divided by 0.05

      irow = round(curDisplay["top"] / RESOLUTION)
      nrow = round(curDisplay["height"] / RESOLUTION)
      icol = round(curDisplay["left"] / RESOLUTION)
      ncol = round(curDisplay["width"] / RESOLUTION)

      # display is waveform        
   
      chartView = QChartView(self.m_chart[idisp])
      self.m_layout.addWidget(chartView,irow,icol,nrow,ncol)

      # calculate max position, needed to add extra widgets to fill the empty space

      if ((icol + ncol) > maxcol) : maxcol = icol + ncol
      if ((irow + nrow) > maxrow) : maxrow = irow + nrow

      # add label and colors

      self.m_chart[idisp].setLabels(settings.m_channels)
      self.m_chart[idisp].setColors(settings.m_channewls)

    # add items if necessary, to get a grid of 1/RESOLUTION x 1/RSOLUTION 
        
    irow = maxrow
    icol = maxcol
    nrow = 1/RESOLUTION - irow
    ncol = 1/RESOLUTION - icol
     
    if nrow > 0 : self.m_layout.addWidget(QWidget(),irow,0,nrow,int(1/RESOLUTION))
    if ncol > 0 : self.m_layout.addWidget(QWidget(),0,icol,int(1/RESOLUTION),ncol)

    # and set the axis

  # initPLot
  #
  #   initialises the chart after rendering is done and the coordinates are known
    
  def initPlot(self,channels) :

    [chart.initPlot(channels) for chart in self.m_chart]

  # plot
  #
  #   update the display with data

  def plot(self,channels) :

    for idisp in range(self.m_numDisplay) :

      # get the channel list for this display and update the display
         
      self.m_chart[idisp].initUpdatePlot()

      chanlist = self.m_chart[idisp].m_channels
      for ichan,i in zip(chanlist,range(len(chanlist))) : 
        data = channels.readData(ichan)
        self.m_chart[idisp].updatePlot(i,data)
        
      self.m_chart[idisp].finishUpdatePlot()
  
