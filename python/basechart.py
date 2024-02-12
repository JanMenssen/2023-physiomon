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

  def __init__(self,nchan) :

    self.m_sampleRate = []
    self.m_deltaT = []
    self.m_pntsInGraph = []
    self.m_downSampler = []

    for i in range(nchan) :
      self.m_sampleRate.append(500)
      self.m_deltaT.append(1/500)
      self.m_pntsInGraph.append(0)
      self.m_downSampler.append(downSampler())

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
    self.m_numchan = nchan

    self.m_series = []

    for ichan in range(self.m_numchan) :
      self.m_series.append(QLineSeries())

    for ichan in range(self.m_numchan) :

      self.m_chart.addSeries(self.m_series[ichan])

      self.m_series[ichan].attachAxis(self.m_axisX)
      self.m_series[ichan].attachAxis(self.m_axisY)

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

    # calculte the reduction factor in plots on the screen 

    for i in range(self.m_numchan) :
 
      rate = round(nsec * self.m_sampleRate[i] / MAX_POINTS_IN_GRAPH)
      if (rate == 0) : 
        rate = 1
      self.m_pntsInGraph[i] = round(nsec * self.m_sampleRate[i] / rate)
      self.m_deltaT[i] = rate / self.m_sampleRate[i]

      self.m_downSampler[i].setRate(rate)

      # and clear the data series
      
      self.m_series[i].clear()  

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

  # finshUpdate
  #
  #   empty function, only needed for scope display

  def finishUpdate(self) :
    return
  
      

