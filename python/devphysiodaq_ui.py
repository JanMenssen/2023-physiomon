# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'devphysiodaq_dialog.ui'
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
from PySide6.QtWidgets import (QApplication, QComboBox, QDialog, QFrame,
    QLabel, QLineEdit, QPushButton, QSizePolicy,
    QWidget)

class Ui_devphysiodaq_dialog(object):
    def setupUi(self, devphysiodaq_dialog):
        if not devphysiodaq_dialog.objectName():
            devphysiodaq_dialog.setObjectName(u"devphysiodaq_dialog")
        devphysiodaq_dialog.resize(376, 250)
        self.frame = QFrame(devphysiodaq_dialog)
        self.frame.setObjectName(u"frame")
        self.frame.setGeometry(QRect(30, 90, 311, 91))
        self.frame.setFrameShape(QFrame.StyledPanel)
        self.frame.setFrameShadow(QFrame.Raised)
        self.offsetEdit = QLineEdit(self.frame)
        self.offsetEdit.setObjectName(u"offsetEdit")
        self.offsetEdit.setGeometry(QRect(180, 50, 81, 21))
        self.offsetEdit.setAlignment(Qt.AlignCenter)
        self.gainEdit = QLineEdit(self.frame)
        self.gainEdit.setObjectName(u"gainEdit")
        self.gainEdit.setGeometry(QRect(180, 20, 81, 21))
        self.gainEdit.setAlignment(Qt.AlignCenter)
        self.offsetLabel = QLabel(self.frame)
        self.offsetLabel.setObjectName(u"offsetLabel")
        self.offsetLabel.setGeometry(QRect(60, 50, 58, 16))
        self.gainLabel = QLabel(self.frame)
        self.gainLabel.setObjectName(u"gainLabel")
        self.gainLabel.setGeometry(QRect(60, 20, 58, 16))
        self.channelLabel = QLabel(devphysiodaq_dialog)
        self.channelLabel.setObjectName(u"channelLabel")
        self.channelLabel.setGeometry(QRect(80, 33, 58, 20))
        self.channelComboBox = QComboBox(devphysiodaq_dialog)
        self.channelComboBox.setObjectName(u"channelComboBox")
        self.channelComboBox.setGeometry(QRect(150, 30, 161, 32))
        self.okButton = QPushButton(devphysiodaq_dialog)
        self.okButton.setObjectName(u"okButton")
        self.okButton.setGeometry(QRect(250, 200, 81, 32))
        self.okButton.setAutoDefault(False)
        self.cancelButton = QPushButton(devphysiodaq_dialog)
        self.cancelButton.setObjectName(u"cancelButton")
        self.cancelButton.setGeometry(QRect(150, 200, 81, 32))
        self.cancelButton.setAutoDefault(False)
        QWidget.setTabOrder(self.channelComboBox, self.gainEdit)
        QWidget.setTabOrder(self.gainEdit, self.offsetEdit)
        QWidget.setTabOrder(self.offsetEdit, self.okButton)
        QWidget.setTabOrder(self.okButton, self.cancelButton)

        self.retranslateUi(devphysiodaq_dialog)

        QMetaObject.connectSlotsByName(devphysiodaq_dialog)
    # setupUi

    def retranslateUi(self, devphysiodaq_dialog):
        devphysiodaq_dialog.setWindowTitle(QCoreApplication.translate("devphysiodaq_dialog", u"devphysiodaq_dialog", None))
#if QT_CONFIG(tooltip)
        self.offsetEdit.setToolTip(QCoreApplication.translate("devphysiodaq_dialog", u"enter the offset of the channel", None))
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        self.gainEdit.setToolTip(QCoreApplication.translate("devphysiodaq_dialog", u"enter the gain of the channel", None))
#endif // QT_CONFIG(tooltip)
        self.offsetLabel.setText(QCoreApplication.translate("devphysiodaq_dialog", u"offset", None))
        self.gainLabel.setText(QCoreApplication.translate("devphysiodaq_dialog", u"gain", None))
        self.channelLabel.setText(QCoreApplication.translate("devphysiodaq_dialog", u"channel", None))
#if QT_CONFIG(tooltip)
        self.channelComboBox.setToolTip(QCoreApplication.translate("devphysiodaq_dialog", u"select a channel", None))
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        self.okButton.setToolTip(QCoreApplication.translate("devphysiodaq_dialog", u"leave dialog with changed settings", None))
#endif // QT_CONFIG(tooltip)
        self.okButton.setText(QCoreApplication.translate("devphysiodaq_dialog", u"OK", None))
#if QT_CONFIG(tooltip)
        self.cancelButton.setToolTip(QCoreApplication.translate("devphysiodaq_dialog", u"leaving dialog without changed settings", None))
#endif // QT_CONFIG(tooltip)
        self.cancelButton.setText(QCoreApplication.translate("devphysiodaq_dialog", u"Cancel", None))
    # retranslateUi

