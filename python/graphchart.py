#
# graphChart
#
#    pythom implementation of the abstract graphics display class
#
# modifications
#     28-jan-2024   JM    initial version
#     27-feb-2024   JM    with the introduction of numericChart renamed to graphCHart

from PySide6.QtCharts import QLineSeries,QValueAxis
from PySide6.QtCore import Qt,QPointF
from basechart import baseChart

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
#   graphChart
# ----------------------------------------------------------------------- 

class graphChart (baseChart) :

  # constructor
  #
  #   axis and series are created

  def __init__(self,chanlist) :

    super().__init__(self,chanlist)

    # create members

    self.m_firstScreen = True
    self.m_indx = [0] * self.m_numchan
    self.m_deltaT  = [0] * self.m_numchan
    self.m_pntsInGraph = [0] * self.m_numchan
    self.m_downSampler = [downSampler()] * self.m_numchan

    # create the axis 
  
    self.m_axisX = QValueAxis()
    self.m_axisY = QValueAxis()

    super().addAxis(self.m_axisX,Qt.AlignmentFlag.AlignBottom)
    super().addAxis(self.m_axisY,Qt.AlignmentFlag.AlignLeft)

    self.m_axisX.setGridLineVisible(False)
    self.m_axisX.setLabelsColor(Qt.lightGray)

    self.m_axisY.setGridLineVisible(False)
    self.m_axisY.setLabelsColor(Qt.lightGray)

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

  # initUpdatePlot
  #
  #   this routine is called just before updating the seperate channels. It checks if the end of the
  #   screen is reached
      
  def initUpdatePlot(self) :

    endReached = all([self.m_indx[i] >= self.m_pntsInGraph[i] for i in range(self.m_numchan)])
    if endReached :
      self.m_indx = [0] * self.m_numchan
      self.m_firstScreen = False

    # done, plot the label (if we know how to handle a resize event, this can be moved to the
    # resize event handler)

    self.plotLabel()   
    return endReached
  
  # finishUpdatePlot
  #
  #     this routine is called after updating the seperate channels. It plots all new data
  #     (almost) simultaneous on the screen
      
  def finishUpdatePlot(self) :

    for i in range(self.m_numchan) : self.m_series[i].replace(self.m_dataBuffer[i])

  # setDownSampler
  #
  #     this method initialises the downSampler. Currently only 2500 points are allowed in one series, so
  #     it the sampleRate is too high or the X-axis is too long, a downsampling is done
    
  def setDownSampler(self, channels) :

    sampleRate = [channels.getSampleRate(i) for i in self.m_channels]
  
    # and calculate the downsample factor for every channel
      
    nsec = self.m_axisX.max()
    rate = [int(round(nsec * iSample) / MAX_POINTS_IN_GRAPH) for iSample in sampleRate]
    rate = list(map(lambda x: 1 if x == 0  else x, rate))
    self.m_pntsInGraph = [round(nsec * iSampleRate/iRate) for iSampleRate, iRate in zip(sampleRate,rate)] 
    self.m_deltaT = [iRate/iSampleRate  for iSampleRate,iRate  in zip(sampleRate,rate)]   
    [sampler.setRate(irate) for sampler,irate in zip(self.m_downSampler,rate)]

  # calcLabelPosition
  #
  #   given the current axis, this method calculates the position of the label (legend)
  #   in graph coordinates. YThe label is placed northwest, 80% of the x and y posiiton
  
  def calcLabelPosition(self) :

    yRange = self.getYaxisRef.max() - self.getYaxisRef.min()
    ypos = self.getYaxisRef.min + 1.1 * yRange
    xpos = 0.8 * self.getXaxisRef().max

    self.m_labelPos = QPointF(xpos,ypos)

  # plotLabel
  #
  #   knowing the position of the label in graph coordinates, a conversion is done to pixels
  #   and the label is plotted on the graph
    
  def plotLabel(self) :

    # first convert the graph coordinate system to pixels 

    pixelPos = super().mapToPosition(self.m_labelPos)

    super().legend().show()
    super().legend().setGeometry(pixelPos.x(),pixelPos.y(),120,len(self.m_numchan) * 30)
     
  # setYaxis
  #
  #     sets the upper and lower limit of the Y-axis    

  def setYaxis(self,ymin,ymax) :

    self.m_axisY.setRange(ymin,ymax)

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

    # set the downsampleer

    self.setDownSampler(channels)

    # calculate the position of the labels in graph coordinates (norteast) and set the 
    # labels

    self.calcLabelPosition()
    self.plotLabel()
    
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

  
      

