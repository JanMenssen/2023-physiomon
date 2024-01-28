#
# stripchart
#    
#    implementation ot fhe <stripChart> class. This class updates the screen like a old fashioned 
#    paper recorder, old data is shifted to the left and new data is added on the right 
#
# modifications
#    26-jan-2024  JM   initial version

from basechart import baseChart
from pySide6.QtCore import QPointF

MAX_POINTS_IN_GRAPH = 2500

class stripChart(baseChart) :

  # constructor

  def __init__(self,nchan) :
    super().__init__()

    for i in range[nchan] :
      self.m_first[i] = True
      self.m_buffer[i].reserve(MAX_POINTS_IN_GRAPH)

  # setTimeAxis
  #
  #    sets the time scale and peforms some initialisation
    
  def setTimeAxis(self,nsec) :

    baseChart.setTimeAxis(nsec)

    for i in range(self.m_numchan) :
      
      self.m_first = True
      self.m_buffer[i].clear()
      self.m_curIndx[i] = 0
  
  # update
  #
  #   updates the graph with new samples

  def update(self,nchan,data) :

    # to make it faster

    curIndx = self.m_curIndx[nchan]     
    deltaT = self.m_deltaT[nchan]
    
    # sweep back at the end of the scrren

    if (curIndx >= maxIndx) :
      self.m_pntsInGraph[chan] = self.m_buffer[nchan].count()
      curIndx = 0
      self.m_first[nchan] = False

    maxIndx = self.m_pntsInGraph[nchan]

    # downSample (Note : should be added)
      
    # the first points differ from the points after the screen is cleared when the right is reached

    nsamples = data.size    
    if (self.m_first[nchan] == True) :

      for i in range(nsamples) :
        self.buffer[nchan].append(QPointF((curIndx * deltaT),data[i]))
        curIndx += 1

    else :
      
      # shift samples
  
      for i in range(maxIndx - nsamples) :
        tmp = self.m_buffer[nchan].at(i + nsamples)
        self.buffer[nchan].replace(i,tmp)
      curIndx = maxIndx - nsamples

      # and add new samples

      for i in range(nsamples)
        
        tmp = QPointF((curIndx * deltaT),data[i])
        self.buffer[nchan].replace(tmp)
        
        if (curIndx > maxIndx) :
          curIndx = 0

    # and replace the new data to the series

    self.m_series[nchan].replace(self.m_buffer[nchan])
    self.m_curIndx[nchan] = curIndx



