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
    self.m_chanlist = []

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
    self.m_chanlist = []

    # and add the stripcharts

    self.m_numDisplay = settings.m_general["numdisp"]
    for iDisplay in range(self.m_numDisplay) :

      self.m_chanlist.append([])
    
      # get the channel

      numChannels = settings.m_general["numchan"]
      for iChannel in range(numChannels) :
        if ((settings.m_channels[iChannel]["display"]-1) == iDisplay) :
          self.m_chanlist[iDisplay].append(iChannel)

      # set the display properties

      position,scale = settings.getDisplayInfo(iDisplay)

      stripchart = stripChart("stripchart")
      #-jm stripchart.setYaxis(scale["ymin"],scale["ymax"])
                    
      self.m_graphDisplay.append(stripchart)

      chartView = QChartView(stripchart.m_chart)

      sub = QMdiSubWindow()
      sub.setGeometry(0,0,800,400)
      sub.setWidget(chartView)
      sub.setWindowTitle("Sub Window " + str(iDisplay))

      self.m_mdiArea.addSubWindow(sub)
      sub.show()

    return
  
  # plot
  #
  #   update the display with data

  def plot(self,channels) :

    if self.m_numDisplay > 0 :

      for iDisplay in range(self.m_numDisplay) :

        # get the channel list for this display and update the display

        chanList = self.m_chanlist[iDisplay]  
        for iChannel in chanList :  
          data = channels.readData(iChannel)
          self.m_graphDisplay[iDisplay].update(data)
  
    return
  
  # setStartWaveFrom
  #
  #   sets the start time of the data

  def setStartWaveform(self) :
    return
