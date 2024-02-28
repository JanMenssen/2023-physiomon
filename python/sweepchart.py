#
# sweepchart
#
#     sweeps the display like an oscciloscope, at the end the graph is cleared and the plotting is
#     starting again from the left
#
# modifications
#   26-jan-2024   JM    initial version
#   27-feb-2024   JM    now derived from graphChart

from graphchart import graphChart
from PySide6.QtCore import QPointF

class sweepChart(graphChart) :  

  # constructor
  #
  #   allocate memory for the buffers to make it faster

  def __init__(self,chanlist) :

    super().__init__(chanlist)
  
  # updatePlot
  #
  #   updates the graph with new samples

  def updatePlot(self,ichan,data) :

    # to make it faster

    indx = self.m_indx[ichan]     
    maxindx = self.m_pntsInGraph[ichan]
    deltaT = self.m_deltaT[ichan]

    # downSample 
 
    data = self.m_downSampler[ichan].getData(data)
    nsamples = len(data)

    # place the data in the buffer (it is cleared afer each screen). Take care of the end of the 
    # buffer
      
    if (indx + nsamples > maxindx) : nsamples = maxindx - indx
    for i in range(nsamples) :
      self.m_dataBuffer[ichan].append(QPointF((indx * deltaT),data[i]))     
      indx += 1

    # done, update index
      
    self.m_indx[ichan] = indx

  # initUpdatePlot
  #
  #  checks if the end is reached and clear the buffer

  def initUpdatePlot(self) :

    endReached = super().initUpdatePlot()
    if (endReached == True) : [buffer.clear() for buffer in self.m_dataBuffer]

    return endReached



