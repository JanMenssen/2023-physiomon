#
# main.py
#
#     this is the main file for the FysioMon project. Visualisation and storage of physiological
#     signals
#
# Modifications
#     15-dec-2023  JM  initial version
#     12-jan-2024  JM  a lot of changes, stuff moved to mainWindow

import sys
from PySide6.QtWidgets import QApplication\

from mainwindow import mainWindow
      
if __name__ == '__main__' :

  app = QApplication(sys.argv)

  # create the graphical structure and show

  myWindow = mainWindow()
  myWindow.show()

  # and return until exit

  sys.exit(app.exec())



    

    