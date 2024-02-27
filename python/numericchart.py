#
# numericChart.py
#
#      this is the implementation of the numerics chart
#
#  modifications
#    27-feb--2024   JM  initial version

from basechart import baseChart
from PySide6.QtCharts import QValueAxis,QScatterSeries
from PySide6.QtCore import Qt,QPointF
from PySide6.QtGui import QFont
from PySide6.QtWidgets import QGraphicsSimpleTextItem

class numericChart (baseChart) :

  # constructor

  def __init__(self) :
    
    # this class makes also use of axis, to position some elements, however these axis are
    # hidden

    self.m_axisX = QValueAxis()
    self.m_axisY = QValueAxis()

    super().addAxis(self.m_axisX,Qt.AlignmentFlag.AlignBottom)
    super().addAxis(self.m_axisY,Qt.AlignmentFlag.AlignLeft)

    self.m_axisX.setGridLineVisible(False)
    self.m_axisX.setLabelsColor(Qt.lightGray)

    self.m_axisY.setGridLineVisible(False)
    self.m_axisY.setLabelsColor(Qt.lightGray)

    self.m_axisX.hide()
    self.m_axisY.hide()

    # create a scatter series to determine the axis coordinate system (0-1)

    self.m_chart.removeAllSeries()
  
    self.m_series = QScatterSeries()
    self.m_chart.addSeries(self.m_series) 
    self.m_series.attachAxis(self.m_axisX)
    self.m_series.attachAxis(self.m_axisY)

    # and set the font and the initial scale factor (scaling between labels and value)

    self.m_usedFont = QFont()
    self.m_scaleFactor = 1

    self.m_label = [[]]
    self.m_value = [[]]

  # setLabels
  #
  #     this routine copies the names from the channel structure toa QString list that can be
  #     used to show on the screen (see plotlabels)

  def setLabels(self,channels) :

    self.m_labelText = []
    for ichan in super().m_channels : self.m_labelTxt.append(channels[ichan]["name"])

  # setPrecision
  #
  #     this routine reads the precision from the channel struct for the selected channel and uses
  #     it on the screen
    
  def setPrecision(self,channels) :

    self.m_precision = []
    for ichan in super().m_channels : self.m_precision.append(channels[ichan]["precision"])

  # initPlot
  #
  #   initialises the plot, can only be called when widgets are rendered, this is not the
  #   case when charts are initialised. Note channels are used to be compatible with the
  #   graphChart routine
    
  def initPlot(self,channels) :

    # calculate the position of the labels and the values in chart coordinates

    self.calcValuePosition(self)
    self.calcLabelPosition(self)

    # and place the label on the screen

    for label,i in zip(self.m_labelTxt,range(super().m_numchan)) : self.plotLabel(i,label)

  # updatePlot
  #
  #   this routine plots the average value of the data in a numeric on the screen for the
  #   selected value
    
  def updatePlot(self,ichan,data) :

    # calculate the mean if there is new data and plot this on the screen

    if len(data) > 0 : self.m_average[ichan] = sum(data) / len(data)
    self.plotValue(ichan,self.m_average[ichan])

  # initUpdatePlot
  #
  #   this routine is called before the seperate channels are updated, the labels are plotted
    
  def initUpdatePlot(self) :
 
    for label,i in zip(self.m_labelTxt,range(super().m_numchan)) : self.plotLabel(i,label)

  # finishUpdatePlot
  #
  #    this is just a stub function to be compatible with the graphCharts
    
  def finishUpdatePlot(self) :
    return
  
  # calcValuePositions
  #
  #     this routine calculates the positions where to display the values on the screen. This is
  #     in the chart coordinate systen

  def calcValuePositions(self) :

    area = self.plotArea()
    self.m_valuePos = []

    if (area.height() >= area.width) :

      # vertical mode

      y_inc = 1.0 / super().m_numchan
      for i in range(super().m_numchan) : self.m_ValuePos.append(QPointF(0.5,1-(i+1)*y_inc))

    else :
      
      # horizontal mode
      
      x_inc = 1.0 / super().m_numchan
      for i in range(super().m_numchan) : self.m_ValuePos.append(QPointF(i+1)*x_inc,0.5)

  # calcLabelPositions
  #
  #     this routine calculates the positions where to display the labels on the screen. This is
  #     in the chart coordinate systen

  def calcLabelPosition(self) :

    area = self.plotArea()
    self.m_labelPos = []

    if (area.height() >= area.width) :

      # vertical mode

      y_inc = 1.0 / super().m_numchan
      for i in range(super().m_numchan) : self.m_labelPos.append(QPointF(0.5,1-(i+1)*y_inc))

    else :
      
      # horizontal mode
      
      x_inc = 1.0 / super().m_numchan
      for i in range(super().m_numchan) : self.m_labelPos.append(QPointF(i+1)*x_inc,0.5)

  # plotLabel
  #
  #    this routine sets the label on the screen. This is done by converting the chart coorindates
  #    to pixel coordinates. The label is centered around this position
  
  def plotLabel(self,n,labelTxt) :

    pixelPos = self.mapToPosition(self.m_labelPos[n])
    del self.m_label[n]

    self.m_label[n] = QGraphicsSimpleTextItem(labelTxt,self)
    self.m_label[n].setFont(self.m_usedFont)
    self.m_label[n].setBrush(Qt.lightGray)

    # and positio to the middle

    rectangle = self.m_label[n].boundingRect()
    self.m_label[n].setPos((pixelPos.x() - rectangle.width()/2), (pixelPos.y() - rectangle.height()/2))


  # plotValue
  #
  #    this routine sets the value on the screen. This is done by converting the chart coorindates
  #    to pixel coordinates. The value is centered around this position and scaled depending on the
  #    screen sze
  
  def plotValue(self,n,value) :

    pixelPos = self.mapToPosition(self.m_labelPos[n])
    del self.m_value[n]

    valueTxt = QString::number(value,'f',self.m_precision[n])

    self.m_value[n] = QGraphicsSimpleTextItem(valueTxt,self)
    self.m_value[n].setFont(self.m_usedFont)
    self.m_value[n].setBrush(Qt.lightGray)

    # and positio to the middle

    rectangle = self.m_label[n].boundingRect()
    self.m_value[n].setPos((pixelPos.x() - rectangle.width()/2), (pixelPos.y() - rectangle.height()/2))

  # calcScalefactor
  #
  #   calculates the factor the value are larger than the labels, this is calculated arbitrary and could be
  #   done better

  def calcScaleFactor(self) :

    scale = 1.0

    labelPosInPixel = self.mapToPosition(self.m_labelPos[0])
    valuePosInPixel = self.mapToPosition(self.m_valuePos[0])

    diff = abs(labelPosInPixel.y() - valuePosInPixel.y())
    scale = diff / 12.5

    return scale


  
