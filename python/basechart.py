#
#  baseChart
#
#     this is an abstract class containing items belonging to all the graphs in the 
#     project
#
# modifications
#     27-feb-2024   JM  initial version

from PySide6.QtCharts import QChart,QValueAxis
from PySide6.QtCore import Qt,QMargins

class baseChart(QChart) :

  # constructor

  def __init__(self,chanlist) :
    super().__init__()

    # set the channels that are in the display

    self.m_channels = chanlist
    self.m_numchan = len(chanlist)

    # create the graphics 

    self.setMargins(QMargins(10,5,5,5))
    self.setBackgroundVisible(False)

    # default legend settings

    self.legend().hide()
    self.legend().setLabelBrush(Qt.lightGray)
    self.legend().detachFromChart()
    self.legend().setBackgroundVisible(False)
    self.legend().setInteractive(True)
    
        

