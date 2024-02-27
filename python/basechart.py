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

    # set the channels that are in the display

    self.m_channels = chanlist

    # create the graphics 

    super().setMargins(QMargins(10,5,5,5))
    super().setBackgoundVisible(False)

    # default legend settings

    super().legend().hide
    super().legend().setLabelBrush(Qt.lightGray)
    super().legend().detachFromChart()
    super().legend().setBackgroundVisible(False)
    super().legend().setInteractive(True)
    
        

