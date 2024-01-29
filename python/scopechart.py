#
# scopechart
#    
#    implementation ot fhe <scopeChart> class. This class updates the screen like a oscilloscope, if on 
#    the upper right part of the screen the next point overrides the points on the left 
#
# modifications
#    26-jan-2024  JM   initial version

from basechart import baseChart, downSampler
from PySide6.QtCore import QPointF

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

  # setTimeAxis
  #
  #    sets the time scale and peforms some initialisation
    
  def setTimeAxis(self,nsec) :

    super().setTimeAxis(nsec)

    for i in range(self.m_numchan) :
      
      self.m_first[i]= True
      self.m_buffer[i].clear()
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
        if (curIndx < maxIndx) :
          curIndx += 1
        else :
          curIndx = 0

    # and replace the new data to the series

    self.m_series.replace(self.m_buffer[nchan])
    self.m_curIndx[nchan] = curIndx




