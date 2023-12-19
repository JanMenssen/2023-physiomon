#
# display.py
#
#         contains the software for the graphs and update the graphs on the screen
#
#   modifications
#     19-dec-2023 JM    initial version

from PySide6.QtWidgets import QMdiSubWindow
from PySide6.QtCharts import QChartView
from stripchart import stripChart

class display() :

  # constructor

  def __init__(self,mdiArea) :

    self.m_mdiArea = mdiArea
    self.m_graphDisplay = []
    self.m_numDisplay = 0

    return
  
  # initialise
  #
  #   initialise the class

  def initialise(self) :

    return
  
  # configure
  #
  #   sets the number of required displays on the screen 

  def configure(self,settings) :

    # clear the current settings

    allGraphDisplays = self.m_mdiArea.subWindowList()
    for curGraphDisplay in allGraphDisplays :
      self.m_mdiArea.removeSubWindow(curGraphDisplay)

    self.m_graphDisplay = []
    self.m_numDisplay = 0

    # and add the stripcharts
    # Note : this is a tempory solution, the number of displays is not equal the number of channels

    self.m_numDisplay = settings.general["numchan"]
    for i in range(self.m_numDisplay) :
    
      stripchart = stripChart("stripchart")
      self.m_graphDisplay.append(stripchart)

      chartView = QChartView(stripchart.m_chart)

      sub = QMdiSubWindow()
      sub.setWidget(chartView)
      sub.setWindowTitle("Sub Windows " + str(i))

      self.m_mdiArea.addSubWindow(sub)
      sub.show()

    return
  
  # plot
  #
  #   update the display with data

  def plot(self,data) :

    if self.m_numDisplay > 0 :
      for iDisplay in range(self.m_numDisplay) :
        self.m_graphDisplay[iDisplay].update(data)
    return
  
  # setStartWaveFrom
  #
  #   sets the start time of the data

  def setStartWaveform(self) :
    return
