#
# baseChart
#
#    pythom implementation of the abstract display class
#
# modifications
#     28-jan-2024   JM    initial version

from PySide6.QtCharts import QChart,QLineSeries,QValueAxis
from PySide6.QtCore import Qt,QMargins

# some settings to speed up the software

MAX_POINTS_IN_GRAPH = 2500

# ----------------------------------------------------------------------
#   downSampler
# ----------------------------------------------------------------------- 

class downSampler :

  # constructor

  def __init__(self) :
    super().__init__()

    self.m_buffer = []
    self.m_decimateFactor = 1

  def setRate(self,rate) :

    self.m_decimateFactor = rate
    return
  
  def getData(self,data) : 

    if (self.m_decimateFactor > 1) :
      
      self.m_buffer.extend(data)
      data = self.m_buffer[::self.m_decimateFactor]
      self.m_buffer[:(self.m_decimateFactor * len(data))] = []

    return data

# ----------------------------------------------------------------------
#   baseChart
# ----------------------------------------------------------------------- 

class baseChart :

  # constructor
  #
  #   axis and series are created

  def __init__(self,chanlist) :

    self.m_firstScreen = True

    # channel list and umber of samples

    self.m_channels = chanlist
    self.m_numchan = len(chanlist)

    self.m_indx = [0] * self.m_numchan
    self.m_deltaT  = [0] * self.m_numchan
    self.m_pntsInGraph = [0] * self.m_numchan
    self.m_downSampler = [downSampler()] * self.m_numchan

    # create a new chart, margins are set to zero. Note this could be have strange effects
    # (labels, legends don't fit)
      
    self.m_chart = QChart()
    self.m_chart.setMargins(QMargins(10,5,5,5))
  
    self.m_axisX = QValueAxis()
    self.m_axisY = QValueAxis()

    self.m_chart.addAxis(self.m_axisX,Qt.AlignmentFlag.AlignBottom)
    self.m_chart.addAxis(self.m_axisY,Qt.AlignmentFlag.AlignLeft)

    self.m_axisX.setGridLineVisible(False)
    self.m_axisX.setLabelsColor(Qt.lightGray)

    self.m_axisY.setGridLineVisible(False)
    self.m_axisY.setLabelsColor(Qt.lightGray)

    self.m_chart.legend().hide()
    self.m_chart.setBackgroundVisible(False)

    # create for every channe a QLineSeries object and attach the series to the axis

    self.m_chart.removeAllSeries()
  
    self.m_series = []
    self.m_dataBuffer = [[]]

    for i in range(self.m_numchan) : 
      
      self.m_dataBuffer.append([])
      self.m_series.append(QLineSeries())

      self.m_chart.addSeries(self.m_series[i]) 
      self.m_series[i].attachAxis(self.m_axisX)
      self.m_series[i].attachAxis(self.m_axisY)

  # initUpdate
  #
  #     this routine is called just for updating the graphs, it:
  #        - checks graph is on the end of the screen (start again)
  #        - resets the first screen 
      
  def initUpdate(self) :

    endReached = all([self.m_indx[i] >= self.m_pntsInGraph[i] for i in range(self.m_numchan)])
    if endReached :
      self.m_indx = [0] * self.m_numchan
      self.m_firstScreen = False
      
    return endReached
  
  # finishUpdate
  #
  #     plots the data points in the buffers on the screen
      
  def finishUpdate(self) :

    for i in range(self.m_numchan) : self.m_series[i].replace(self.m_dataBuffer[i])

  # setYaxis
  #
  #     sets the upper and lower limit of the Y-axis    

  def setYaxis(self,ymin,ymax) :

    self.m_axisY.setRange(ymin,ymax)

  # getChart
  #
  #     returns a reference to the chart
    
  def getChart(self) :
    
    return self.m_chart
  
  # setTimeAxis
  #
  #     sets the tima axis and initialises a number of variables

  def setTimeAxis(self,nsec) :

    self.m_axisX.setRange(0,nsec)

  # initPlot
  #
  # configures the x-data using time on the x-axis and the sampleRate. To speed up the
  # process, we limit the number of points in the graph and use a downsampler if the
  # needed  

  def initPlot(self,channels) :

    # get the sample rate for each channel

    sampleRate = [channels.getSampleRate(i) for i in self.m_channels]
  
    # and calculate the downsample factor 
      
    nsec = self.m_axisX.max()
    rate = [int(round(nsec * iSample) / MAX_POINTS_IN_GRAPH) for iSample in sampleRate]
    rate = list(map(lambda x: 1 if x == 0  else x, rate))
    self.m_pntsInGraph = [round(nsec * iSampleRate/iRate) for iSampleRate, iRate in zip(sampleRate,rate)] 
    self.m_deltaT = [iRate/iSampleRate  for iSampleRate,iRate  in zip(sampleRate,rate)]   
    [sampler.setRate(irate) for sampler,irate in zip(self.m_downSampler,rate)]

  # getXaxisRef
  #
  #     returns the reference to the X axis   

  def getXaxisRef(self) :
    return self.m_axisX

  # getXaxisRef
  #
  #     returns the reference to the X axis   

  def getYaxisRef(self) :
    return self.m_axisY

  
      

