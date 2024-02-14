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

class scopeChart(baseChart) :

  # constructor

  def __init__(self,nchan) :
    super().__init__(nchan)

    self.m_firstScreen = True
    self.m_curIndx = []

    for i in range(nchan) :
      self.m_curIndx.append(0)
      self.m_dataBuffer.append([])

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
     
  # setYaxis
  #
  #   scope has it's own implementation of setYaxis, limits must be known for the
  #   scopeline
      
  def setYaxis(self,ymin,ymax) :

    super().setYaxis(ymin,ymax)  
    self.m_yLimits = [self.m_axisY.min(), self.m_axisY.max()]
  

  # update
  #
  #   updates the graph with new samples

  def update(self,ichan,data) :

    # to make it faster

    indx = self.m_curIndx[ichan]     
    deltaT = self.m_deltaT[ichan]

    # downSample
    
    data = self.m_downSampler[ichan].getData(data)
      
    # the first points differ from the points after the screen is cleared when the right is reached

    nsamples = len(data)      
    if (self.m_firstScreen == True) :

      for i in range(nsamples) :
        self.m_dataBuffer[ichan].append(QPointF((indx * deltaT),data[i]))
        indx += 1
        
    else :
      
      for i in range(nsamples) :
        self.m_dataBuffer[ichan][indx] = QPointF((indx * deltaT),data[i])
        indx += 1

    # and replace the new data to the series

    self.m_series[ichan].replace(self.m_dataBuffer[ichan])
    self.m_curIndx[ichan] = indx

  # finishUpdate
  #
  #   finishUpdate is for scope not an empty function, it draws the scope line
    
  def finishUpdate(self) :

    # checck we are at the end of the screen with all channels

    endReached = True

    for i in range(self.m_numchan) :
      endReached = endReached and self.m_curIndx[i] >= self.m_pntsInGraph[i]

    if (endReached) :
      self.m_firstScreen = False
      self.m_curIndx = [0 for i in range(self.m_numchan)]


    # draw only after one sweep

    if (self.m_firstScreen == False) :

      pnt_lower = QPointF((self.m_curIndx[0] * self.m_deltaT[0]), self.m_yLimits[0])
      pnt_upper = QPointF((self.m_curIndx[0] * self.m_deltaT[0]), self.m_yLimits[1])

      line = [pnt_lower, pnt_upper]
      self.m_scopeLine.replace(line)
              