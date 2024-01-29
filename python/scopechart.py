#
# scopechart
#    
#    implementation ot fhe <scopeChart> class. This class updates the screen like a oscilloscope, if on 
#    the upper right part of the screen the next point overrides the points on the left 
#
# modifications
#    26-jan-2024  JM   initial version

from basechart import baseChart
from PySide6.QtCore import QPointF
from PySide6.QtCharts import QLineSeries

MAX_POINTS_IN_GRAPH = 2500

class scopeChart(baseChart) :

  # constructor

  def __init__(self,nchan) :
    super().__init__(nchan)

    self.m_first = []
    self.m_curIndx = []
    self.m_buffer = [[]]

    for i in range(nchan) :
      self.m_first.append(True)
      self.m_curIndx.append(0)
      self.m_buffer.append([])

    x_axis = super().getXaxisRef()
    y_axis = super().getYaxisRef()

    self.m_scopeLine = QLineSeries()
    self.m_chart.addSeries(self.m_scopeLine)
    self.m_scopeLine.attachAxis(x_axis)
    self.m_scopeLine.attachAxis(y_axis)

    pen = self.m_scopeLine.pen()
    pen.setWidth(1)
    pen.setColor("red")
    self.m_scopeLine.setPen(pen)
     
  # setTimeAxis
  #
  #    sets the time scale and peforms some initialisation
    
  def setTimeAxis(self,nsec) :

    super().setTimeAxis(nsec)

    for i in range(self.m_numchan) :
      
      self.m_first[i]= True
      self.m_buffer[i].clear()
      self.m_curIndx[i] = 0
  
  # setYaxis
  #
  #   scope has it's own implementation of setYaxis, limits must be known for the
  #   scopeline
      
  def setYaxis(self,ymin,ymax) :

    super().setYaxis(ymin,ymax)  
    self.m_yLimits = [ymin, ymax]
  

  # update
  #
  #   updates the graph with new samples

  def update(self,nchan,data) :

    # to make it faster

    curIndx = self.m_curIndx[nchan]     
    maxIndx = self.m_pntsInGraph[nchan]
    deltaT = self.m_deltaT[nchan]
    
    # sweep back at the end of the scrren

    if (curIndx > maxIndx) :
      curIndx = 0
      if (self.m_first[nchan] == True) :
        self.m_pntsInGraph[nchan] = self.m_series[nchan].count()
        maxIndx = self.m_pntsInGraph[nchan]
        self.m_first[nchan] = False

    # downSample
    
    data = self.m_downSampler[nchan].getData(data)
      
    # the first points differ from the points after the screen is cleared when the right is reached

    nsamples = len(data)      
    if (self.m_first[nchan] == True) :

      for i in range(nsamples) :
        self.m_buffer[nchan].append(QPointF((curIndx * deltaT),data[i]))
        curIndx += 1
        
    else :
      
      for i in range(nsamples) :
        self.m_buffer[nchan][curIndx] = QPointF((curIndx * deltaT),data[i])
        curIndx += 1
        if (curIndx >= maxIndx) :
          curIndx = 0

    # and replace the new data to the series

    self.m_series[nchan].replace(self.m_buffer[nchan])
    self.m_curIndx[nchan] = curIndx

  # finishUpdate
  #
  #   finishUpdate is for scope not an empty function, it draws the scope line
    
  def finishUpdate(self) :

    # draw only after one sweep

    if (self.m_first[0] == False) :

      pnt_lower = QPointF((self.m_curIndx[0] * self.m_deltaT[0]), self.m_yLimits[0])
      pnt_upper = QPointF((self.m_curIndx[0] * self.m_deltaT[0]), self.m_yLimits[1])

      line = [pnt_lower, pnt_upper]
      self.m_scopeLine.replace(line)
              