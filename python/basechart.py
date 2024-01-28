#
# baseChart
#
#    pythom implementation of the abstract display class
#
# modifications
#     28-jan-2024   JM    initial version

from PySide6.QtCharts import QChart,QLineSeries,QValueAxis
from PySide6.QtCore import Qt

# some settings to speed up the software

MAX_POINTS_IN_GRAPH = 2500

# ----------------------------------------------------------------------
#   downSampler
# ----------------------------------------------------------------------- 

class downSampler :

  # constructor

  def __init__(self) :
    super().__init__()

  def setRate(self,rate) :
    return
  
  def getData(self,data) :
    return  


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

    for i in range(nchan) :
      self.m_sampleRate.append(500)
      self.m_deltaT.append(1/500)
      self.m_pntsInGraph.append(0)
  
    self.m_chart = QChart()

    self.m_axisX = QValueAxis()
    self.m_axisY = QValueAxis()

    self.m_chart.addAxis(self.m_axisX,Qt.AlignmentFlag.AlignBottom)
    self.m_chart.addAxis(self.m_axisY,Qt.AlignmentFlag.AlignLeft)

    self.m_axisX.setGridLineVisible(False)
    self.m_axisX.setLabelsColor(Qt.cyan)

    self.m_axisY.setGridLineVisible(False)
    self.m_axisY.setLabelsColor(Qt.cyan)

    self.m_chart.legend().hide()
    self.m_chart.setBackgroundVisible(False)

    self.m_series = QLineSeries()

    # create for every channe q QLineSeries object and attach the series to the axis

    self.m_chart.removeAllSeries()

    self.m_numchan = nchan

    #-jm for ichan in range(self.m_numchan) :

    #-jm  self.m_series.append(QLineSeries())
    self.m_chart.addSeries(self.m_series)

    self.m_series.attachAxis(self.m_axisX)
    self.m_series.attachAxis(self.m_axisY)

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

    for i in range(self.m_numchan) :
    #-jm 
    #-jm   rate = round((nsec * self.m_sampleRate[i]) / MAX_POINTS_IN_GRAPH)
    #-jm  self.m_pntsInGraph[i] = round(nsec * self.m_sampleRate[i] / rate)
      self.m_pntsInGraph[i] = 2500
    #-jm  self.m_deltaT[i] = rate / self.m_sampleRate[i]

    # and clear the data series
      
    self.m_series.clear()  
    #-jm [self.m_series[i].clear for i in range(self.m_numchan)]

