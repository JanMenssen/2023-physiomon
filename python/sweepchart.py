#
# sweepchart
#
#     sweeps the display like an oscciloscope, at the end the graph is cleared and the plotting is
#     starting again from the left

from basechart import baseChart
from pySide6.QtCore import QPointF

MAX_POINTS_IN_GRAPH = 2500

class sweepChart(baseChart) :  

  # constructor
  #
  #   allocate memory for the buffers to make it faster

  def __init__(self,nchan) :
    super().__init__()

    self.m_curIndx = []
    
    [self.m_buffer[i].reserve(MAX_POINTS_IN_GRAPH) for i in range(nchan)]

  # setTimeAxis
  #
  #    sets the time scale (done by superclass) and initialises some settings

  def setTimeAxis(self,nsec) :

    baseChart.setTimeAxis(nsec)
    for i in range(self.m_numchan) :
      self.m_curIndx[i] = 0
  
  # update
  #
  #   updates the graph with new samples

  def update(self,nchan,data) :

    # to make it faster

    curIndx = self.m_curIndx[nchan]     
    maxIndx = self.m_pntsInGraph[nchan]
    deltaT = self.m_deltaT[nchan]
    
    # sweep back at the end of the scrren

    if (curIndx >= maxIndx) :
      curIndx = 0
      self.m_series[nchan].clear()

    # downSample (Note : should be added)
      
    # place the data in the (cleared) buffer
      
    self.m_buffer[nchan].clear()
  
    for i in range(data.size) :
      self.m_buffer[nchan].append(QPointF((curIndx * deltaT),data[i]))     
      curIndx += 1

    # and append the new data to the series

    self.m_series[nchan].append(self.m_buffer[nchan])
    self.m_curIndx[nchan] = curIndx



