#
#   stripchart.py
#
#       this class contains the stripchart.
#
# modifications
#   08-dec-2023  JM  initial version

from PySide6.QtCore import QPointF,Qt
from PySide6.QtCharts import QChart,QLineSeries,QValueAxis

SAMPLE_COUNT = 1000
RESOLUTION = 1

class stripChart :

  # constructor
  
  def __init__(self) :
    super().__init__()

    self.m_series = QLineSeries()
    
    self.m_chart = QChart()
    self.m_chart.addSeries(self.m_series)

    self.m_axisX = QValueAxis()
    self.m_axisX.setRange(0,SAMPLE_COUNT)
    self.m_axisX.setLabelFormat("%g")
    self.m_axisX.setTitleText("seconds")
    self.m_axisX.setTitleBrush(Qt.cyan)
    self.m_axisX.setGridLineVisible(False)
    self.m_axisX.setLabelsColor(Qt.cyan)

    self.m_axisY = QValueAxis()
    #-jm self.m_axisY.setRange(-1,1)
    self.setYaxis(-500,500)
    self.m_axisY.setTitleText("audio level")
    self.m_axisY.setTitleBrush(Qt.cyan)
    self.m_axisY.setGridLineVisible(False)
    self.m_axisY.setLabelsColor(Qt.cyan)

    self.m_chart.addAxis(self.m_axisX,Qt.AlignmentFlag.AlignBottom)
    self.m_chart.addAxis(self.m_axisY,Qt.AlignmentFlag.AlignLeft)
    self.m_series.attachAxis(self.m_axisX)
    self.m_series.attachAxis(self.m_axisY)

    self.m_chart.legend().hide()
    self.m_chart.setBackgroundVisible(False)
    
    #-jm title must be set with method or during initialisation, therefore these lines are
    #-jm commented
    #-jm 
    #-jm name = device.description()
    #-jm self.m_chart.setTitle(f"Data from the microphone ({name})")
    
    self.m_buffer = [QPointF(x, 0) for x in range(SAMPLE_COUNT)]
    self.m_series.append(self.m_buffer)

  # setYaxis
  #
  #     sets the scale of the Yaxis
    
  def setYaxis(self,ymin,ymax) :

    self.m_axisY.setRange(ymin,ymax)
    return
  
  # update
  #
  #   the update method is called at new samples

  def update(self,data) :

  #-jm  available_samples = data.size() // RESOLUTION
    available_samples = len(data) // RESOLUTION
    start = 0
    
    if (available_samples < SAMPLE_COUNT) :
      start = SAMPLE_COUNT - available_samples
      for s in range(start) :
        self.m_buffer[s].setY(self.m_buffer[s + available_samples].y())   
    
    data_index = 0
    for s in range(start, SAMPLE_COUNT) :
  #-jm    value = (ord(data[data_index]) - 128) / 128
      value = data[data_index]
      self.m_buffer[s].setY(value)
      data_index = data_index + RESOLUTION
    self.m_series.replace(self.m_buffer)
    return

