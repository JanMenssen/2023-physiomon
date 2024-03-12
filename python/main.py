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
from PySide6.QtWidgets import QApplication,QSplashScreen
from PySide6.QtGui import QPixmap
from PySide6.QtCore import QTimer

from mainwindow import mainWindow
from physiomon_icons import qInitResources

TIME_SPLASH_SCREEN = 2000

# main
#
#   this class does the job

class main() :

  def __init__(self) :

    app = QApplication(sys.argv)

    # create the splashscreen which if for TIME_SPLASH_SCREEN on the screen

    self.splash = QSplashScreen()
    self.splash.setPixmap(QPixmap(":/intro/splashscreen.png"))
    self.splash.show()

    # create the mainwindow but don't show it

    self.myWindow = mainWindow(1300,750)
    self.myWindow.show()
    self.myWindow.hide()

    # and start the time

    intro_timer = QTimer()
    intro_timer.setInterval(TIME_SPLASH_SCREEN)
    intro_timer.setSingleShot(True)
    intro_timer.start()
    intro_timer.timeout.connect(self.onTimeOut)

    sys.exit(app.exec())

  # onTimeOut
  #
  #   closes the splash screen and show the main screen 
    
  def onTimeOut(self) :

    self.splash.close()
    self.myWindow.show()


if __name__ == '__main__' :

  main()






  