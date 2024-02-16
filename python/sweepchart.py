#
# sweepchart
#
#     sweeps the display like an oscciloscope, at the end the graph is cleared and the plotting is
#     starting again from the left

from basechart import baseChart
from PySide6.QtCore import QPointF

class sweepChart(baseChart) :  

  # constructor
  #
  #   allocate memory for the buffers to make it faster

  def __init__(self,chanlist) :

    super().__init__(chanlist)
  
  # update
  #
  #   updates the graph with new samples

  def update(self,ichan,data) :

    # to make it faster

    indx = self.m_indx[ichan]     
    maxindx = self.m_pntsInGraph[ichan]
    deltaT = self.m_deltaT[ichan]

    # downSample 
 
    data = self.m_downSampler[ichan].getData(data)

    # place the data in the buffer (it is cleared afer each screen). Take care of the end of the 
    # buffer
      
    nsamples = len(data)
    if (indx + nsamples > maxindx) : nsamples = maxindx - indx

    for i in range(nsamples) :
      self.m_dataBuffer[ichan].append(QPointF((indx * deltaT),data[i]))     
      indx += 1

    # done, update index
      
    self.m_indx[ichan] = indx

  # initUpdate
  #
  #  checks if the end is reached and clear the buffer

  def initUpdate(self) :

    endReached = super().initUpdate()
    if (endReached == True) : [buffer.clear() for buffer in self.m_dataBuffer]

    return endReached



