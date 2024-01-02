#
# displays.py
#
#         contains the software for the graphs and update the graphs on the screen
#
#   modifications
#     19-dec-2023 JM    initial version

from PySide6.QtWidgets import QMdiSubWindow
from PySide6.QtCharts import QChartView
from stripchart import stripChart

class displays() :

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

    self.m_numDisplay = settings.m_general["numdisp"]
    for i in range(self.m_numDisplay) :
    
      position,scale = settings.getDisplayInfo(i)

      stripchart = stripChart("stripchart")
      #-jm stripchart.setYaxis(scale["ymin"],scale["ymax"])
                    
      self.m_graphDisplay.append(stripchart)

      chartView = QChartView(stripchart.m_chart)

      sub = QMdiSubWindow()
      sub.setGeometry(0,0,800,400)
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
