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

  def __init__(self,channels) :

    super().__init__(channels)

    # a vertical red position line should be drawn, make a series element
    # that could be plotted on the screen

    self.m_scopeLine = QLineSeries()
    self.m_chart.addSeries(self.m_scopeLine)
    self.m_scopeLine.attachAxis(self.m_axisX)
    self.m_scopeLine.attachAxis(self.m_axisY)

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

    indx = self.m_indx[ichan]     
    deltaT = self.m_deltaT[ichan]
    maxindx = self.m_pntsInGraph[ichan]

    # downSample
    
    data = self.m_downSampler[ichan].getData(data)

    # determint the numbef or samples that should be placed in the buffer, important if the
    # end of the buffer is reached

    nsamples = len(data)  
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

  # finishUpdate
  #
  #   finishUpdate draws the red vertical line on the screen (not the first screen)
    
  def finishUpdate(self) :

    super().finishUpdate()

    pnt_lower = QPointF((self.m_indx[0] * self.m_deltaT[0]), self.m_yLimits[0])
    pnt_upper = QPointF((self.m_indx[0] * self.m_deltaT[0]), self.m_yLimits[1])

    self.m_scopeLine.replace([pnt_lower, pnt_upper])
              