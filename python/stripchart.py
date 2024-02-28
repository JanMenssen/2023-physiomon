#
# stripchart
#    
#    implementation ot fhe <stripChart> class. This class updates the screen like a old fashioned 
#    paper recorder, old data is shifted to the left and new data is added on the right 
#
# modifications
#    26-jan-2024  JM   initial version
#    27-feb-2024  JM   now derived from graphChart

from graphchart import graphChart
from PySide6.QtCore import QPointF

class stripChart(graphChart) :

  # constructor

  def __init__(self,chanlist) :
    super().__init__(chanlist)
    
  # updatePlot
  #
  #   updates the graph with new samples for one channel

  def updatePlot(self,ichan,data) :

    # to make it faster

    indx = self.m_indx[ichan]     
    deltaT = self.m_deltaT[ichan]
    maxindx = self.m_pntsInGraph[ichan]
    
    # downSample 

    data = self.m_downSampler[ichan].getData(data)   
    nsamples = len(data)    

    if (self.m_firstScreen == True) :

      # first screen, points should be appended to buffer. However if the end is reached already 
      # existing points should be shifted
  
      shift = nsamples - (maxindx - indx)  
      if (shift > 0) :
        
        for i in range(shift,indx) : self.m_dataBuffer[ichan][i-shift] = QPointF((i-shift) * deltaT,self.m_dataBuffer[ichan][i].y())
        for i,j in zip(range(indx-shift,indx),range(shift)) : self.m_dataBuffer[ichan][i] = QPointF(i * deltaT,data[j])
        for i in range(nsamples-shift) :
          self.m_dataBuffer[ichan].append(QPointF(indx * deltaT,data[i+shift]))
          indx += 1
     
      else :

        for i in range(nsamples):
          self.m_dataBuffer[ichan].append(QPointF(indx * deltaT,data[i]))
          indx += 1

    else :
      
      # other screens, only a shift is required and new samples should be added
            
      shift = maxindx - nsamples
      for i in range(shift) :
        self.m_dataBuffer[ichan][i] = QPointF((i * deltaT),self.m_dataBuffer[ichan][i+nsamples].y()) 
      for i in range(shift,maxindx) :
        self.m_dataBuffer[ichan][i] = QPointF(i * deltaT,data[i-shift])
    
    # done, update index

    self.m_indx[ichan] = indx




