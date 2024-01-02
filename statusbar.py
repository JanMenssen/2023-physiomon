#
# statusbar.py
#
#     In this class the statusbar as used in Matlab, LabView and now Python is created
#
#  modifications
#     15-dec-2023   JM  initial version

from PySide6.QtWidgets import QWidget,  QStatusBar
from PySide6.QtGui import QPainter, QPen
from PySide6.QtCore import Qt 
from datetime import datetime

class StatusBar(QStatusBar) :
  
  # constructor

  def __init__(self) :
    super().__init__()

  # setText
  #
  #     this method shows the text for the number of seconds
    
  def setText(self,txtToDisplay,timeToDisplay) :

    currentTime = datetime.now().strftime("%H:%M:%S")
    txtToDisplay = currentTime + " >>> " + txtToDisplay
    self.showMessage(txtToDisplay,(timeToDisplay * 1000))


