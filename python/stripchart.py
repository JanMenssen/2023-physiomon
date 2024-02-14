#
# stripchart
#    
#    implementation ot fhe <stripChart> class. This class updates the screen like a old fashioned 
#    paper recorder, old data is shifted to the left and new data is added on the right 
#
# modifications
#    26-jan-2024  JM   initial version

from basechart import baseChart
from PySide6.QtCore import QPointF

MAX_POINTS_IN_GRAPH = 2500

class stripChart(baseChart) :

  # constructor

  def __init__(self,nchan) :
    super().__init__(nchan)
    
    self.m_firstScreen = True
    self.m_curIndx = []
    self.m_databuffer = [[]]

    for i in range(nchan) :
      self.m_curIndx.append(0)
      self.m_dataBuffer.append([])

  # setTimeAxis
  #
  #    sets the time scale and peforms some initialisation
    
  def setTimeAxis(self,nsec) :

    super().setTimeAxis(nsec)
  
  # update
  #
  #   updates the graph with new samples

  def update(self,ichan,data) :

    # to make it faster

    indx = self.m_curIndx[ichan]     
    deltaT = self.m_deltaT[ichan]
    maxIndx = self.m_pntsInGraph[ichan]
    
    # downSample 

    data = self.m_downSampler[ichan].getData(data)
      
    # the first points differ from the points after the screen is cleared when the right is reached

    nsamples = len(data)    
    if (self.m_firstScreen == True) :

      # first screen, points should be appended to buffer  
  
      [self.m_dataBuffer[ichan].append(QPointF((indx + i)* deltaT,data[i])) for i in range(nsamples)]
      indx += nsamples

    else :
      
      # shift samples and append the samples

      for i in range(maxIndx-nsamples) :
        self.m_dataBuffer[ichan][i] = QPointF((i * deltaT),  self.m_dataBuffer[ichan][i + nsamples].y()) 
      
      indx = maxIndx - nsamples
      for i in range(nsamples) :
        self.m_dataBuffer[ichan][indx+i] = QPointF((indx + i)* deltaT,data[i])

    # and replace the new data to the series

    self.m_series[ichan].replace(self.m_dataBuffer[ichan])
    self.m_curIndx[ichan] = indx

  # finishUpdate
  #
  #   goto replace mode if the first screen is plotted
    
  def finishUpdate(self) :

    if (self.m_firstScreen == True) :

      endReached = True

      for i in range(self.m_numchan) :
        endReached = endReached and self.m_curIndx[i] >= self.m_pntsInGraph[i]    

      if (endReached == True) :

        self.m_pntsInGraph = [len(i) for i in self.m_dataBuffer]
        self.m_firstScreen = False


