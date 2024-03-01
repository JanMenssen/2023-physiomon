# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'settings_dialog.ui'
##
## Created by: Qt User Interface Compiler version 6.6.0
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide6.QtCore import (QCoreApplication, QDate, QDateTime, QLocale,
    QMetaObject, QObject, QPoint, QRect,
    QSize, QTime, QUrl, Qt)
from PySide6.QtGui import (QBrush, QColor, QConicalGradient, QCursor,
    QFont, QFontDatabase, QGradient, QIcon,
    QImage, QKeySequence, QLinearGradient, QPainter,
    QPalette, QPixmap, QRadialGradient, QTransform)
from PySide6.QtWidgets import (QApplication, QComboBox, QDialog, QGroupBox,
    QHBoxLayout, QLabel, QLineEdit, QPushButton,
    QRadioButton, QSizePolicy, QSpacerItem, QSpinBox,
    QTabWidget, QVBoxLayout, QWidget)

class Ui_settings_dialog(object):
    def setupUi(self, settings_dialog):
        if not settings_dialog.objectName():
            settings_dialog.setObjectName(u"settings_dialog")
        settings_dialog.resize(570, 445)
        settings_dialog.setAutoFillBackground(False)
        self.numchan = QLineEdit(settings_dialog)
        self.numchan.setObjectName(u"numchan")
        self.numchan.setGeometry(QRect(380, 40, 51, 21))
        self.numchan.setAlignment(Qt.AlignCenter)
        self.numdisp = QLineEdit(settings_dialog)
        self.numdisp.setObjectName(u"numdisp")
        self.numdisp.setGeometry(QRect(380, 70, 51, 21))
        self.numdisp.setAlignment(Qt.AlignCenter)
        self.label = QLabel(settings_dialog)
        self.label.setObjectName(u"label")
        self.label.setGeometry(QRect(60, 40, 121, 20))
        self.label_2 = QLabel(settings_dialog)
        self.label_2.setObjectName(u"label_2")
        self.label_2.setGeometry(QRect(60, 70, 121, 20))
        self.tabWidget = QTabWidget(settings_dialog)
        self.tabWidget.setObjectName(u"tabWidget")
        self.tabWidget.setEnabled(True)
        self.tabWidget.setGeometry(QRect(20, 120, 531, 271))
        self.tabWidget.setTabPosition(QTabWidget.North)
        self.tabWidget.setTabShape(QTabWidget.Rounded)
        self.tabWidget.setElideMode(Qt.ElideRight)
        self.channels = QWidget()
        self.channels.setObjectName(u"channels")
        self.groupBox = QGroupBox(self.channels)
        self.groupBox.setObjectName(u"groupBox")
        self.groupBox.setGeometry(QRect(260, 50, 241, 121))
        self.groupBox.setAutoFillBackground(True)
        self.groupBox.setFlat(False)
        self.channelAnalog_rb = QRadioButton(self.groupBox)
        self.channelAnalog_rb.setObjectName(u"channelAnalog_rb")
        self.channelAnalog_rb.setGeometry(QRect(60, 30, 181, 20))
        self.channelWaveform_rb = QRadioButton(self.groupBox)
        self.channelWaveform_rb.setObjectName(u"channelWaveform_rb")
        self.channelWaveform_rb.setEnabled(False)
        self.channelWaveform_rb.setGeometry(QRect(60, 60, 99, 20))
        self.channelNumeric_rb = QRadioButton(self.groupBox)
        self.channelNumeric_rb.setObjectName(u"channelNumeric_rb")
        self.channelNumeric_rb.setEnabled(False)
        self.channelNumeric_rb.setGeometry(QRect(60, 90, 99, 20))
        self.layoutWidget = QWidget(self.channels)
        self.layoutWidget.setObjectName(u"layoutWidget")
        self.layoutWidget.setGeometry(QRect(50, 20, 131, 23))
        self.horizontalLayout = QHBoxLayout(self.layoutWidget)
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.horizontalLayout.setContentsMargins(0, 0, 0, 0)
        self.label_3 = QLabel(self.layoutWidget)
        self.label_3.setObjectName(u"label_3")

        self.horizontalLayout.addWidget(self.label_3)

        self.horizontalSpacer = QSpacerItem(28, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout.addItem(self.horizontalSpacer)

        self.channelSelected = QSpinBox(self.layoutWidget)
        self.channelSelected.setObjectName(u"channelSelected")

        self.horizontalLayout.addWidget(self.channelSelected)

        self.layoutWidget1 = QWidget(self.channels)
        self.layoutWidget1.setObjectName(u"layoutWidget1")
        self.layoutWidget1.setGeometry(QRect(30, 80, 196, 23))
        self.horizontalLayout_2 = QHBoxLayout(self.layoutWidget1)
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.horizontalLayout_2.setContentsMargins(0, 0, 0, 0)
        self.label_4 = QLabel(self.layoutWidget1)
        self.label_4.setObjectName(u"label_4")

        self.horizontalLayout_2.addWidget(self.label_4)

        self.horizontalSpacer_2 = QSpacerItem(18, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_2.addItem(self.horizontalSpacer_2)

        self.channelName = QLineEdit(self.layoutWidget1)
        self.channelName.setObjectName(u"channelName")

        self.horizontalLayout_2.addWidget(self.channelName)

        self.layoutWidget2 = QWidget(self.channels)
        self.layoutWidget2.setObjectName(u"layoutWidget2")
        self.layoutWidget2.setGeometry(QRect(30, 140, 194, 23))
        self.horizontalLayout_3 = QHBoxLayout(self.layoutWidget2)
        self.horizontalLayout_3.setObjectName(u"horizontalLayout_3")
        self.horizontalLayout_3.setContentsMargins(0, 0, 0, 0)
        self.label_6 = QLabel(self.layoutWidget2)
        self.label_6.setObjectName(u"label_6")

        self.horizontalLayout_3.addWidget(self.label_6)

        self.horizontalSpacer_4 = QSpacerItem(18, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_3.addItem(self.horizontalSpacer_4)

        self.channelColor = QLineEdit(self.layoutWidget2)
        self.channelColor.setObjectName(u"channelColor")
        self.channelColor.setEnabled(False)

        self.horizontalLayout_3.addWidget(self.channelColor)

        self.layoutWidget3 = QWidget(self.channels)
        self.layoutWidget3.setObjectName(u"layoutWidget3")
        self.layoutWidget3.setGeometry(QRect(30, 110, 193, 23))
        self.horizontalLayout_4 = QHBoxLayout(self.layoutWidget3)
        self.horizontalLayout_4.setObjectName(u"horizontalLayout_4")
        self.horizontalLayout_4.setContentsMargins(0, 0, 0, 0)
        self.label_5 = QLabel(self.layoutWidget3)
        self.label_5.setObjectName(u"label_5")

        self.horizontalLayout_4.addWidget(self.label_5)

        self.horizontalSpacer_3 = QSpacerItem(18, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_4.addItem(self.horizontalSpacer_3)

        self.channelUnit = QLineEdit(self.layoutWidget3)
        self.channelUnit.setObjectName(u"channelUnit")
        self.channelUnit.setEnabled(False)

        self.horizontalLayout_4.addWidget(self.channelUnit)

        self.layoutWidget4 = QWidget(self.channels)
        self.layoutWidget4.setObjectName(u"layoutWidget4")
        self.layoutWidget4.setGeometry(QRect(26, 190, 191, 30))
        self.horizontalLayout_5 = QHBoxLayout(self.layoutWidget4)
        self.horizontalLayout_5.setObjectName(u"horizontalLayout_5")
        self.horizontalLayout_5.setContentsMargins(0, 0, 0, 0)
        self.label_7 = QLabel(self.layoutWidget4)
        self.label_7.setObjectName(u"label_7")

        self.horizontalLayout_5.addWidget(self.label_7)

        self.horizontalSpacer_5 = QSpacerItem(98, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_5.addItem(self.horizontalSpacer_5)

        self.channelDisplaySelected = QSpinBox(self.layoutWidget4)
        self.channelDisplaySelected.setObjectName(u"channelDisplaySelected")
        self.channelDisplaySelected.setAutoFillBackground(True)

        self.horizontalLayout_5.addWidget(self.channelDisplaySelected)

        self.layoutWidget5 = QWidget(self.channels)
        self.layoutWidget5.setObjectName(u"layoutWidget5")
        self.layoutWidget5.setGeometry(QRect(260, 190, 234, 32))
        self.horizontalLayout_6 = QHBoxLayout(self.layoutWidget5)
        self.horizontalLayout_6.setObjectName(u"horizontalLayout_6")
        self.horizontalLayout_6.setContentsMargins(0, 0, 0, 0)
        self.label_8 = QLabel(self.layoutWidget5)
        self.label_8.setObjectName(u"label_8")
        self.label_8.setAlignment(Qt.AlignCenter)

        self.horizontalLayout_6.addWidget(self.label_8)

        self.channelSignalSelect = QComboBox(self.layoutWidget5)
        self.channelSignalSelect.setObjectName(u"channelSignalSelect")
        self.channelSignalSelect.setMinimumSize(QSize(131, 0))
        self.channelSignalSelect.setAutoFillBackground(False)
        self.channelSignalSelect.setFrame(True)

        self.horizontalLayout_6.addWidget(self.channelSignalSelect)

        self.tabWidget.addTab(self.channels, "")
        self.displays = QWidget()
        self.displays.setObjectName(u"displays")
        self.groupBox_2 = QGroupBox(self.displays)
        self.groupBox_2.setObjectName(u"groupBox_2")
        self.groupBox_2.setGeometry(QRect(20, 70, 261, 91))
        self.groupBox_2.setAutoFillBackground(True)
        self.groupBox_2.setFlat(False)
        self.layoutWidget_2 = QWidget(self.groupBox_2)
        self.layoutWidget_2.setObjectName(u"layoutWidget_2")
        self.layoutWidget_2.setGeometry(QRect(80, 30, 41, 47))
        self.verticalLayout_4 = QVBoxLayout(self.layoutWidget_2)
        self.verticalLayout_4.setObjectName(u"verticalLayout_4")
        self.verticalLayout_4.setContentsMargins(0, 0, 0, 0)
        self.label_13 = QLabel(self.layoutWidget_2)
        self.label_13.setObjectName(u"label_13")
        self.label_13.setAlignment(Qt.AlignCenter)

        self.verticalLayout_4.addWidget(self.label_13)

        self.displayLeft = QLineEdit(self.layoutWidget_2)
        self.displayLeft.setObjectName(u"displayLeft")
        self.displayLeft.setAlignment(Qt.AlignCenter)

        self.verticalLayout_4.addWidget(self.displayLeft)

        self.layoutWidget_3 = QWidget(self.groupBox_2)
        self.layoutWidget_3.setObjectName(u"layoutWidget_3")
        self.layoutWidget_3.setGeometry(QRect(140, 30, 41, 47))
        self.verticalLayout_5 = QVBoxLayout(self.layoutWidget_3)
        self.verticalLayout_5.setObjectName(u"verticalLayout_5")
        self.verticalLayout_5.setContentsMargins(0, 0, 0, 0)
        self.label_14 = QLabel(self.layoutWidget_3)
        self.label_14.setObjectName(u"label_14")
        self.label_14.setAlignment(Qt.AlignCenter)

        self.verticalLayout_5.addWidget(self.label_14)

        self.displayHeight = QLineEdit(self.layoutWidget_3)
        self.displayHeight.setObjectName(u"displayHeight")
        self.displayHeight.setAlignment(Qt.AlignCenter)

        self.verticalLayout_5.addWidget(self.displayHeight)

        self.layoutWidget_4 = QWidget(self.groupBox_2)
        self.layoutWidget_4.setObjectName(u"layoutWidget_4")
        self.layoutWidget_4.setGeometry(QRect(200, 30, 41, 47))
        self.verticalLayout_6 = QVBoxLayout(self.layoutWidget_4)
        self.verticalLayout_6.setObjectName(u"verticalLayout_6")
        self.verticalLayout_6.setContentsMargins(0, 0, 0, 0)
        self.label_15 = QLabel(self.layoutWidget_4)
        self.label_15.setObjectName(u"label_15")
        self.label_15.setAlignment(Qt.AlignCenter)

        self.verticalLayout_6.addWidget(self.label_15)

        self.displayWidth = QLineEdit(self.layoutWidget_4)
        self.displayWidth.setObjectName(u"displayWidth")
        self.displayWidth.setAlignment(Qt.AlignCenter)

        self.verticalLayout_6.addWidget(self.displayWidth)

        self.layoutWidget6 = QWidget(self.groupBox_2)
        self.layoutWidget6.setObjectName(u"layoutWidget6")
        self.layoutWidget6.setGeometry(QRect(20, 30, 41, 47))
        self.verticalLayout = QVBoxLayout(self.layoutWidget6)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.label_10 = QLabel(self.layoutWidget6)
        self.label_10.setObjectName(u"label_10")
        self.label_10.setAlignment(Qt.AlignCenter)

        self.verticalLayout.addWidget(self.label_10)

        self.displayTop = QLineEdit(self.layoutWidget6)
        self.displayTop.setObjectName(u"displayTop")
        self.displayTop.setAlignment(Qt.AlignCenter)

        self.verticalLayout.addWidget(self.displayTop)

        self.groupBox_3 = QGroupBox(self.displays)
        self.groupBox_3.setObjectName(u"groupBox_3")
        self.groupBox_3.setGeometry(QRect(20, 170, 261, 61))
        self.groupBox_3.setAutoFillBackground(True)
        self.groupBox_3.setFlat(False)
        self.displayYmin = QLineEdit(self.groupBox_3)
        self.displayYmin.setObjectName(u"displayYmin")
        self.displayYmin.setGeometry(QRect(50, 30, 41, 21))
        self.displayYmin.setAlignment(Qt.AlignCenter)
        self.displayYmax = QLineEdit(self.groupBox_3)
        self.displayYmax.setObjectName(u"displayYmax")
        self.displayYmax.setGeometry(QRect(100, 30, 41, 21))
        self.displayYmax.setAlignment(Qt.AlignCenter)
        self.displayXaxis = QLineEdit(self.groupBox_3)
        self.displayXaxis.setObjectName(u"displayXaxis")
        self.displayXaxis.setGeometry(QRect(210, 30, 41, 21))
        self.displayXaxis.setAlignment(Qt.AlignCenter)
        self.label_16 = QLabel(self.groupBox_3)
        self.label_16.setObjectName(u"label_16")
        self.label_16.setGeometry(QRect(160, 20, 51, 41))
        self.label_17 = QLabel(self.groupBox_3)
        self.label_17.setObjectName(u"label_17")
        self.label_17.setGeometry(QRect(10, 20, 51, 41))
        self.groupBox_4 = QGroupBox(self.displays)
        self.groupBox_4.setObjectName(u"groupBox_4")
        self.groupBox_4.setGeometry(QRect(320, 70, 181, 161))
        self.groupBox_4.setAutoFillBackground(True)
        self.displayStripChart_rb = QRadioButton(self.groupBox_4)
        self.displayStripChart_rb.setObjectName(u"displayStripChart_rb")
        self.displayStripChart_rb.setGeometry(QRect(40, 30, 99, 20))
        self.displaySweepChart_rb = QRadioButton(self.groupBox_4)
        self.displaySweepChart_rb.setObjectName(u"displaySweepChart_rb")
        self.displaySweepChart_rb.setGeometry(QRect(40, 60, 99, 20))
        self.displayScopeChart_rb = QRadioButton(self.groupBox_4)
        self.displayScopeChart_rb.setObjectName(u"displayScopeChart_rb")
        self.displayScopeChart_rb.setGeometry(QRect(40, 90, 99, 20))
        self.displayNumeric_rb = QRadioButton(self.groupBox_4)
        self.displayNumeric_rb.setObjectName(u"displayNumeric_rb")
        self.displayNumeric_rb.setGeometry(QRect(40, 120, 99, 20))
        self.layoutWidget7 = QWidget(self.displays)
        self.layoutWidget7.setObjectName(u"layoutWidget7")
        self.layoutWidget7.setGeometry(QRect(50, 20, 131, 23))
        self.horizontalLayout_7 = QHBoxLayout(self.layoutWidget7)
        self.horizontalLayout_7.setObjectName(u"horizontalLayout_7")
        self.horizontalLayout_7.setContentsMargins(0, 0, 0, 0)
        self.label_9 = QLabel(self.layoutWidget7)
        self.label_9.setObjectName(u"label_9")

        self.horizontalLayout_7.addWidget(self.label_9)

        self.horizontalSpacer_7 = QSpacerItem(28, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_7.addItem(self.horizontalSpacer_7)

        self.displaySelected = QSpinBox(self.layoutWidget7)
        self.displaySelected.setObjectName(u"displaySelected")

        self.horizontalLayout_7.addWidget(self.displaySelected)

        self.tabWidget.addTab(self.displays, "")
        self.events = QWidget()
        self.events.setObjectName(u"events")
        self.layoutWidget_17 = QWidget(self.events)
        self.layoutWidget_17.setObjectName(u"layoutWidget_17")
        self.layoutWidget_17.setGeometry(QRect(20, 70, 485, 23))
        self.horizontalLayout_23 = QHBoxLayout(self.layoutWidget_17)
        self.horizontalLayout_23.setObjectName(u"horizontalLayout_23")
        self.horizontalLayout_23.setContentsMargins(0, 0, 0, 0)
        self.label_55 = QLabel(self.layoutWidget_17)
        self.label_55.setObjectName(u"label_55")

        self.horizontalLayout_23.addWidget(self.label_55)

        self.horizontalSpacer_8 = QSpacerItem(13, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_23.addItem(self.horizontalSpacer_8)

        self.event02 = QLineEdit(self.layoutWidget_17)
        self.event02.setObjectName(u"event02")
        self.event02.setMinimumSize(QSize(201, 0))

        self.horizontalLayout_23.addWidget(self.event02)

        self.horizontalSpacer_24 = QSpacerItem(17, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_23.addItem(self.horizontalSpacer_24)

        self.label_56 = QLabel(self.layoutWidget_17)
        self.label_56.setObjectName(u"label_56")

        self.horizontalLayout_23.addWidget(self.label_56)

        self.horizontalSpacer_10 = QSpacerItem(13, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_23.addItem(self.horizontalSpacer_10)

        self.event07 = QLineEdit(self.layoutWidget_17)
        self.event07.setObjectName(u"event07")
        self.event07.setMinimumSize(QSize(201, 0))

        self.horizontalLayout_23.addWidget(self.event07)

        self.layoutWidget_30 = QWidget(self.events)
        self.layoutWidget_30.setObjectName(u"layoutWidget_30")
        self.layoutWidget_30.setGeometry(QRect(20, 110, 485, 23))
        self.horizontalLayout_24 = QHBoxLayout(self.layoutWidget_30)
        self.horizontalLayout_24.setObjectName(u"horizontalLayout_24")
        self.horizontalLayout_24.setContentsMargins(0, 0, 0, 0)
        self.label_59 = QLabel(self.layoutWidget_30)
        self.label_59.setObjectName(u"label_59")

        self.horizontalLayout_24.addWidget(self.label_59)

        self.horizontalSpacer_12 = QSpacerItem(13, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_24.addItem(self.horizontalSpacer_12)

        self.event03 = QLineEdit(self.layoutWidget_30)
        self.event03.setObjectName(u"event03")
        self.event03.setMinimumSize(QSize(201, 0))

        self.horizontalLayout_24.addWidget(self.event03)

        self.horizontalSpacer_35 = QSpacerItem(17, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_24.addItem(self.horizontalSpacer_35)

        self.label_60 = QLabel(self.layoutWidget_30)
        self.label_60.setObjectName(u"label_60")

        self.horizontalLayout_24.addWidget(self.label_60)

        self.horizontalSpacer_11 = QSpacerItem(13, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_24.addItem(self.horizontalSpacer_11)

        self.event08 = QLineEdit(self.layoutWidget_30)
        self.event08.setObjectName(u"event08")
        self.event08.setMinimumSize(QSize(201, 0))

        self.horizontalLayout_24.addWidget(self.event08)

        self.layoutWidget_31 = QWidget(self.events)
        self.layoutWidget_31.setObjectName(u"layoutWidget_31")
        self.layoutWidget_31.setGeometry(QRect(20, 150, 485, 23))
        self.horizontalLayout_35 = QHBoxLayout(self.layoutWidget_31)
        self.horizontalLayout_35.setObjectName(u"horizontalLayout_35")
        self.horizontalLayout_35.setContentsMargins(0, 0, 0, 0)
        self.label_61 = QLabel(self.layoutWidget_31)
        self.label_61.setObjectName(u"label_61")

        self.horizontalLayout_35.addWidget(self.label_61)

        self.horizontalSpacer_14 = QSpacerItem(13, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_35.addItem(self.horizontalSpacer_14)

        self.event04 = QLineEdit(self.layoutWidget_31)
        self.event04.setObjectName(u"event04")
        self.event04.setMinimumSize(QSize(201, 0))

        self.horizontalLayout_35.addWidget(self.event04)

        self.horizontalSpacer_36 = QSpacerItem(17, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_35.addItem(self.horizontalSpacer_36)

        self.label_62 = QLabel(self.layoutWidget_31)
        self.label_62.setObjectName(u"label_62")

        self.horizontalLayout_35.addWidget(self.label_62)

        self.horizontalSpacer_13 = QSpacerItem(13, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_35.addItem(self.horizontalSpacer_13)

        self.event09 = QLineEdit(self.layoutWidget_31)
        self.event09.setObjectName(u"event09")
        self.event09.setMinimumSize(QSize(201, 0))

        self.horizontalLayout_35.addWidget(self.event09)

        self.layoutWidget_32 = QWidget(self.events)
        self.layoutWidget_32.setObjectName(u"layoutWidget_32")
        self.layoutWidget_32.setGeometry(QRect(20, 190, 485, 23))
        self.horizontalLayout_36 = QHBoxLayout(self.layoutWidget_32)
        self.horizontalLayout_36.setObjectName(u"horizontalLayout_36")
        self.horizontalLayout_36.setContentsMargins(0, 0, 0, 0)
        self.label_63 = QLabel(self.layoutWidget_32)
        self.label_63.setObjectName(u"label_63")

        self.horizontalLayout_36.addWidget(self.label_63)

        self.horizontalSpacer_16 = QSpacerItem(13, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_36.addItem(self.horizontalSpacer_16)

        self.event10 = QLineEdit(self.layoutWidget_32)
        self.event10.setObjectName(u"event10")
        self.event10.setMinimumSize(QSize(201, 0))

        self.horizontalLayout_36.addWidget(self.event10)

        self.horizontalSpacer_37 = QSpacerItem(17, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_36.addItem(self.horizontalSpacer_37)

        self.label_64 = QLabel(self.layoutWidget_32)
        self.label_64.setObjectName(u"label_64")

        self.horizontalLayout_36.addWidget(self.label_64)

        self.horizontalSpacer_15 = QSpacerItem(13, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_36.addItem(self.horizontalSpacer_15)

        self.event05 = QLineEdit(self.layoutWidget_32)
        self.event05.setObjectName(u"event05")
        self.event05.setMinimumSize(QSize(201, 0))

        self.horizontalLayout_36.addWidget(self.event05)

        self.layoutWidget8 = QWidget(self.events)
        self.layoutWidget8.setObjectName(u"layoutWidget8")
        self.layoutWidget8.setGeometry(QRect(20, 30, 485, 23))
        self.horizontalLayout_8 = QHBoxLayout(self.layoutWidget8)
        self.horizontalLayout_8.setObjectName(u"horizontalLayout_8")
        self.horizontalLayout_8.setContentsMargins(0, 0, 0, 0)
        self.label_18 = QLabel(self.layoutWidget8)
        self.label_18.setObjectName(u"label_18")

        self.horizontalLayout_8.addWidget(self.label_18)

        self.horizontalSpacer_6 = QSpacerItem(13, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_8.addItem(self.horizontalSpacer_6)

        self.event01 = QLineEdit(self.layoutWidget8)
        self.event01.setObjectName(u"event01")
        self.event01.setMinimumSize(QSize(201, 0))

        self.horizontalLayout_8.addWidget(self.event01)

        self.horizontalSpacer_23 = QSpacerItem(17, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_8.addItem(self.horizontalSpacer_23)

        self.label_39 = QLabel(self.layoutWidget8)
        self.label_39.setObjectName(u"label_39")

        self.horizontalLayout_8.addWidget(self.label_39)

        self.horizontalSpacer_9 = QSpacerItem(13, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_8.addItem(self.horizontalSpacer_9)

        self.event06 = QLineEdit(self.layoutWidget8)
        self.event06.setObjectName(u"event06")
        self.event06.setMinimumSize(QSize(201, 0))

        self.horizontalLayout_8.addWidget(self.event06)

        self.tabWidget.addTab(self.events, "")
        self.okButton = QPushButton(settings_dialog)
        self.okButton.setObjectName(u"okButton")
        self.okButton.setGeometry(QRect(410, 400, 81, 32))
        self.okButton.setAutoDefault(False)
        self.cancelButton = QPushButton(settings_dialog)
        self.cancelButton.setObjectName(u"cancelButton")
        self.cancelButton.setGeometry(QRect(320, 400, 81, 32))
        self.cancelButton.setAutoDefault(False)

        self.retranslateUi(settings_dialog)

        self.tabWidget.setCurrentIndex(1)


        QMetaObject.connectSlotsByName(settings_dialog)
    # setupUi

    def retranslateUi(self, settings_dialog):
        settings_dialog.setWindowTitle(QCoreApplication.translate("settings_dialog", u"physiomon settings", None))
#if QT_CONFIG(tooltip)
        self.numchan.setToolTip(QCoreApplication.translate("settings_dialog", u"enter the desired number of channels", None))
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        self.numdisp.setToolTip(QCoreApplication.translate("settings_dialog", u"enter the desired number of displays", None))
#endif // QT_CONFIG(tooltip)
        self.label.setText(QCoreApplication.translate("settings_dialog", u"number of channels", None))
        self.label_2.setText(QCoreApplication.translate("settings_dialog", u"number of displays", None))
        self.groupBox.setTitle(QCoreApplication.translate("settings_dialog", u"type signal", None))
#if QT_CONFIG(tooltip)
        self.channelAnalog_rb.setToolTip(QCoreApplication.translate("settings_dialog", u"select if the channel is an analog channel", None))
#endif // QT_CONFIG(tooltip)
        self.channelAnalog_rb.setText(QCoreApplication.translate("settings_dialog", u"analog", None))
#if QT_CONFIG(tooltip)
        self.channelWaveform_rb.setToolTip(QCoreApplication.translate("settings_dialog", u"select if the channel is a waveform", None))
#endif // QT_CONFIG(tooltip)
        self.channelWaveform_rb.setText(QCoreApplication.translate("settings_dialog", u"waveform", None))
#if QT_CONFIG(tooltip)
        self.channelNumeric_rb.setToolTip(QCoreApplication.translate("settings_dialog", u"select if the channel is numeric", None))
#endif // QT_CONFIG(tooltip)
        self.channelNumeric_rb.setText(QCoreApplication.translate("settings_dialog", u"numeric", None))
        self.label_3.setText(QCoreApplication.translate("settings_dialog", u"channel", None))
#if QT_CONFIG(tooltip)
        self.channelSelected.setToolTip(QCoreApplication.translate("settings_dialog", u"select the desired channel to edit", None))
#endif // QT_CONFIG(tooltip)
        self.label_4.setText(QCoreApplication.translate("settings_dialog", u"name", None))
#if QT_CONFIG(tooltip)
        self.channelName.setToolTip(QCoreApplication.translate("settings_dialog", u"enter the channel name", None))
#endif // QT_CONFIG(tooltip)
        self.label_6.setText(QCoreApplication.translate("settings_dialog", u"color", None))
        self.label_5.setText(QCoreApplication.translate("settings_dialog", u"units", None))
        self.label_7.setText(QCoreApplication.translate("settings_dialog", u"display", None))
#if QT_CONFIG(tooltip)
        self.channelDisplaySelected.setToolTip(QCoreApplication.translate("settings_dialog", u"select the display to to shwo the data for this channel", None))
#endif // QT_CONFIG(tooltip)
        self.label_8.setText(QCoreApplication.translate("settings_dialog", u"select signal", None))
#if QT_CONFIG(tooltip)
        self.channelSignalSelect.setToolTip(QCoreApplication.translate("settings_dialog", u"select the input for the channel", None))
#endif // QT_CONFIG(tooltip)
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.channels), QCoreApplication.translate("settings_dialog", u"channels", None))
        self.groupBox_2.setTitle(QCoreApplication.translate("settings_dialog", u"position (% of full window)", None))
        self.label_13.setText(QCoreApplication.translate("settings_dialog", u"left", None))
#if QT_CONFIG(tooltip)
        self.displayLeft.setToolTip(QCoreApplication.translate("settings_dialog", u"enter the left positon of the display", None))
#endif // QT_CONFIG(tooltip)
        self.label_14.setText(QCoreApplication.translate("settings_dialog", u"height", None))
#if QT_CONFIG(tooltip)
        self.displayHeight.setToolTip(QCoreApplication.translate("settings_dialog", u"enter the height of the display", None))
#endif // QT_CONFIG(tooltip)
        self.label_15.setText(QCoreApplication.translate("settings_dialog", u"width", None))
#if QT_CONFIG(tooltip)
        self.displayWidth.setToolTip(QCoreApplication.translate("settings_dialog", u"enter the width of the display", None))
#endif // QT_CONFIG(tooltip)
        self.label_10.setText(QCoreApplication.translate("settings_dialog", u"top", None))
#if QT_CONFIG(tooltip)
        self.displayTop.setToolTip(QCoreApplication.translate("settings_dialog", u"enter the top position", None))
#endif // QT_CONFIG(tooltip)
        self.groupBox_3.setTitle(QCoreApplication.translate("settings_dialog", u"scale", None))
#if QT_CONFIG(tooltip)
        self.displayYmin.setToolTip(QCoreApplication.translate("settings_dialog", u"enter the minimum value for the y-axis", None))
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        self.displayYmax.setToolTip(QCoreApplication.translate("settings_dialog", u"enter the maximum value on the y-axis", None))
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        self.displayXaxis.setToolTip(QCoreApplication.translate("settings_dialog", u"enter the time scale (x-axis) of the display", None))
#endif // QT_CONFIG(tooltip)
        self.label_16.setText(QCoreApplication.translate("settings_dialog", u"time (s)", None))
        self.label_17.setText(QCoreApplication.translate("settings_dialog", u"y axis", None))
        self.groupBox_4.setTitle(QCoreApplication.translate("settings_dialog", u"type", None))
#if QT_CONFIG(tooltip)
        self.displayStripChart_rb.setToolTip(QCoreApplication.translate("settings_dialog", u"select strip chart if you want it like a paper recorder", None))
#endif // QT_CONFIG(tooltip)
        self.displayStripChart_rb.setText(QCoreApplication.translate("settings_dialog", u"strip chart", None))
#if QT_CONFIG(tooltip)
        self.displaySweepChart_rb.setToolTip(QCoreApplication.translate("settings_dialog", u"select sweep schart if the display should be cleared at the end", None))
#endif // QT_CONFIG(tooltip)
        self.displaySweepChart_rb.setText(QCoreApplication.translate("settings_dialog", u"sweep chart", None))
#if QT_CONFIG(tooltip)
        self.displayScopeChart_rb.setToolTip(QCoreApplication.translate("settings_dialog", u"select scope chart if you want the display like an oscilloscope", None))
#endif // QT_CONFIG(tooltip)
        self.displayScopeChart_rb.setText(QCoreApplication.translate("settings_dialog", u"scope chart", None))
#if QT_CONFIG(tooltip)
        self.displayNumeric_rb.setToolTip(QCoreApplication.translate("settings_dialog", u"select numeric if you want only a numeric on the display", None))
#endif // QT_CONFIG(tooltip)
        self.displayNumeric_rb.setText(QCoreApplication.translate("settings_dialog", u"numeric", None))
        self.label_9.setText(QCoreApplication.translate("settings_dialog", u"display", None))
#if QT_CONFIG(tooltip)
        self.displaySelected.setToolTip(QCoreApplication.translate("settings_dialog", u"select the display to edit", None))
#endif // QT_CONFIG(tooltip)
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.displays), QCoreApplication.translate("settings_dialog", u"displays", None))
        self.label_55.setText(QCoreApplication.translate("settings_dialog", u"2", None))
#if QT_CONFIG(tooltip)
        self.event02.setToolTip(QCoreApplication.translate("settings_dialog", u"enter a text for this event", None))
#endif // QT_CONFIG(tooltip)
        self.label_56.setText(QCoreApplication.translate("settings_dialog", u" 7", None))
#if QT_CONFIG(tooltip)
        self.event07.setToolTip(QCoreApplication.translate("settings_dialog", u"enter a text for this event", None))
#endif // QT_CONFIG(tooltip)
        self.label_59.setText(QCoreApplication.translate("settings_dialog", u"3", None))
#if QT_CONFIG(tooltip)
        self.event03.setToolTip(QCoreApplication.translate("settings_dialog", u"enter a text for this event", None))
#endif // QT_CONFIG(tooltip)
        self.label_60.setText(QCoreApplication.translate("settings_dialog", u" 8", None))
#if QT_CONFIG(tooltip)
        self.event08.setToolTip(QCoreApplication.translate("settings_dialog", u"enter a text for this event", None))
#endif // QT_CONFIG(tooltip)
        self.label_61.setText(QCoreApplication.translate("settings_dialog", u"4", None))
#if QT_CONFIG(tooltip)
        self.event04.setToolTip(QCoreApplication.translate("settings_dialog", u"enter a text for this event", None))
#endif // QT_CONFIG(tooltip)
        self.label_62.setText(QCoreApplication.translate("settings_dialog", u" 9", None))
#if QT_CONFIG(tooltip)
        self.event09.setToolTip(QCoreApplication.translate("settings_dialog", u"enter a text for this event", None))
#endif // QT_CONFIG(tooltip)
        self.label_63.setText(QCoreApplication.translate("settings_dialog", u"5", None))
#if QT_CONFIG(tooltip)
        self.event10.setToolTip(QCoreApplication.translate("settings_dialog", u"enter a text for this event", None))
#endif // QT_CONFIG(tooltip)
        self.label_64.setText(QCoreApplication.translate("settings_dialog", u"10", None))
#if QT_CONFIG(tooltip)
        self.event05.setToolTip(QCoreApplication.translate("settings_dialog", u"enter a text for this event", None))
#endif // QT_CONFIG(tooltip)
        self.label_18.setText(QCoreApplication.translate("settings_dialog", u"1", None))
#if QT_CONFIG(tooltip)
        self.event01.setToolTip(QCoreApplication.translate("settings_dialog", u"enter a text for this event", None))
#endif // QT_CONFIG(tooltip)
        self.label_39.setText(QCoreApplication.translate("settings_dialog", u" 6", None))
#if QT_CONFIG(tooltip)
        self.event06.setToolTip(QCoreApplication.translate("settings_dialog", u"enter a text for this event", None))
#endif // QT_CONFIG(tooltip)
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.events), QCoreApplication.translate("settings_dialog", u"events", None))
#if QT_CONFIG(tooltip)
        self.okButton.setToolTip(QCoreApplication.translate("settings_dialog", u"exit the dialog box and save changes", None))
#endif // QT_CONFIG(tooltip)
        self.okButton.setText(QCoreApplication.translate("settings_dialog", u"OK", None))
#if QT_CONFIG(tooltip)
        self.cancelButton.setToolTip(QCoreApplication.translate("settings_dialog", u"exit dialog box without save changes", None))
#endif // QT_CONFIG(tooltip)
        self.cancelButton.setText(QCoreApplication.translate("settings_dialog", u"Cancel", None))
    # retranslateUi

