#
# sweepchart
#
#     sweeps the display like an oscciloscope, at the end the graph is cleared and the plotting is
#     starting again from the left

from basechart import baseChart
from PySide6.QtCore import QPointF

MAX_POINTS_IN_GRAPH = 2500

class sweepChart(baseChart) :  

  # constructor
  #
  #   allocate memory for the buffers to make it faster

  def __init__(self,nchan) :

    super().__init__(nchan)

    self.m_curIndx = []
    self.m_buffer = [[]]

    for i in range(nchan) :
      self.m_curIndx.append(i)
      self.m_dataBuffer.append([])
      
  # setTimeAxis
  #
  #    sets the time scale (done by superclass) and initialises some settings

  def setTimeAxis(self,nsec) :

    super().setTimeAxis(nsec)
    self.m_curIndx = [0 for i in self.m_curIndx]
  
  # update
  #
  #   updates the graph with new samples

  def update(self,ichan,data) :

    # to make it faster

    indx = self.m_curIndx[ichan]     
    deltaT = self.m_deltaT[ichan]
  
    # downSample 
 
    data = self.m_downSampler[ichan].getData(data)

    # place the data in the (cleared) buffer
      
    nsamples = len(data)

    for i in range(nsamples) :
      self.m_dataBuffer[ichan].append(QPointF((indx * deltaT),data[i]))     
      indx += 1

    # and append the new data to the series

    self.m_series[ichan].replace(self.m_dataBuffer[ichan])
    self.m_curIndx[ichan] = indx

  # initUpdate
  #
  #   clears the buffer if the end of the screen is reached

  def initUpdate(self) :

    endReached = True
    for i in range(self.m_numchan) :
      endReached = endReached and self.m_curIndx[i] >= self.m_pntsInGraph[i]

    if (endReached == True) :
      self.m_curIndx = [0 for i in self.m_curIndx]
      [buffer.clear() for buffer in self.m_dataBuffer]



