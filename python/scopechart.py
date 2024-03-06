#
# scopechart
#    
#    implementation ot fhe <scopeChart> class. This class updates the screen like a oscilloscope, if on 
#    the upper right part of the screen the next point overrides the points on the left 
#
# modifications
#    26-jan-2024  JM   initial version
#    27-feb-2024  JM    now derived from graphChart

from graphchart import graphChart
from PySide6.QtCore import QPointF
from PySide6.QtCharts import QLineSeries

MAX_POINTS_IN_GRAPH = 2500

class scopeChart(graphChart) :

  # constructor

  def __init__(self,channels) :

    super().__init__(channels)

    # a vertical red position line should be drawn, make a series element
    # that could be plotted on the screen

    self.m_scopeLine = QLineSeries()
    self.addSeries(self.m_scopeLine)
    self.m_scopeLine.attachAxis(self.m_axisX)
    self.m_scopeLine.attachAxis(self.m_axisY)
    
    self.m_scopeLine.setName("current pos.")

    pen = self.m_scopeLine.pen()
    pen.setWidth(1)
    pen.setColor("red")
    self.m_scopeLine.setPen(pen)

    # clear some values

    self.m_indx = [0] * self.m_numchan
    #-jm for buffer in self.m_dataBuffer : buffer.reserve(MAX_POINTS_IN_GRAPH)
     
  # setYaxis
  #
  #   scope has it's own implementation of setYaxis, limits must be known for the
  #   scopeline
      
  def setYaxis(self,ymin,ymax) :

    super().setYaxis(ymin,ymax)  
    self.m_yLimits = [self.m_axisY.min(), self.m_axisY.max()]
  
  # updatePlot
  #
  #   updates the graph with new samples

  def updatePlot(self,ichan,data) :

    # to make it faster

    indx = self.m_indx[ichan]     
    deltaT = self.m_deltaT[ichan]
    maxindx = self.m_pntsInGraph[ichan]

    # downSample
    
    data = self.m_downSampler[ichan].getData(data)
    nsamples = len(data)  

    # determint the numbef or samples that should be placed in the buffer, important if the
    # end of the buffer is reached   
    
    if (indx + nsamples > maxindx) : nsamples = maxindx - indx

    # and place in the buffer, depending on the first screen 

    if (self.m_firstScreen == True) :

      for i in range(nsamples) :
        self.m_dataBuffer[ichan].append(QPointF((indx * deltaT),data[i]))
        indx += 1
        
    else :
      
      for i in range(nsamples) :
        self.m_dataBuffer[ichan][indx] = QPointF((indx * deltaT),data[i])
        indx += 1

    # done, update the index

    self.m_indx[ichan] = indx

  # finishUpdatePlot
  #
  #   finishUpdate draws the red vertical line on the screen (not the first screen)
    
  def finishUpdatePlot(self) :

    super().finishUpdatePlot()

    if self.m_firstScreen == False : 
      
      pnt_lower = QPointF((self.m_indx[0] * self.m_deltaT[0]), self.m_yLimits[0])
      pnt_upper = QPointF((self.m_indx[0] * self.m_deltaT[0]), self.m_yLimits[1])

      self.m_scopeLine.replace([pnt_lower, pnt_upper])
              