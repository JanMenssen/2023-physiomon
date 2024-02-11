#ifndef _SETTINGS_DIALOG_H
#define _SETTINGS_DIALOG_H

#include "physiomon_settings.h"
#include "physiomon.h"
#include "measuredevice.h"

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class settings_dialog;
}
QT_END_NAMESPACE

class settings_dialog : public QDialog
{
    Q_OBJECT

public:
    settings_dialog(QWidget *parent = nullptr, int *numchan = nullptr ,channelStruct *m_channels = nullptr, 
       int *numdisp = nullptr, displayStruct *m_displays = nullptr, QString *events = nullptr, int numanalog = 0, const analogInStruct *analogInfo = nullptr);
    ~settings_dialog();

private slots:

    void on_okButton_clicked();
    void on_cancelButton_clicked();
    void on_numchan_editingFinished();
    void on_numdisp_editingFinished();
    void on_channelSelected_valueChanged(int value);
    void on_channelName_editingFinished();
    void on_channelUnit_editingFinished();
    void on_channelColor_editingFinished();
    void on_channelDisplaySelected_valueChanged(int value);
    void on_channelAnalog_rb_clicked();
    void on_channelWaveform_rb_clicked();
    void on_channelNumeric_rb_clicked();
    void on_channelSignalSelect_currentIndexChanged(int index);
    void on_displaySelected_valueChanged(int value);
    void on_displayTop_editingFinished();
    void on_displayLeft_editingFinished();
    void on_displayHeight_editingFinished();
    void on_displayWidth_editingFinished();
    void on_displayYmin_editingFinished();
    void on_displayYmax_editingFinished();
    void on_displayXaxis_editingFinished();
    void on_displayStripChart_rb_clicked();
    void on_displaySweepChart_rb_clicked();
    void on_displayScopeChart_rb_clicked();
    void on_displayNumeric_rb_clicked();

private:
    Ui::settings_dialog *ui;

    void setChannelRadioButtons(typeSignal typeSignal);
    void setDisplayRadioButtons(viewMode typeDisplay);

    // values that are not changed, the original that should be used in case of cancel

    int *m_nChanPtr = nullptr;
    int *m_nDispPtr = nullptr;

    channelStruct *m_channelPtr = nullptr;
    displayStruct *m_displayPtr = nullptr;
    QString *m_eventPtr = nullptr;

    // values that are changed in the dialog
    
    int m_numchan = 0;
    int m_numdisp = 0;

    channelStruct m_channels[MAX_CHANNELS];
    displayStruct m_displays[MAX_DISPLAYS];


};
#endif // DIALOG_H
