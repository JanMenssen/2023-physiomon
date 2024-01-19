//
// adc
//
//  performs analog acquisition of all channels of the ARDUINO. Currently the
//  standard routine <analogInput> is used but in the future, a faster wriiten
//  routine should be used
//
//  Modifications
//    19-jan-2013    JM   initial version
//    04-okt-2014    JM   int mDummy added, for simulation 

#ifndef ADC_H
#define ADC_H
#define MAX_ADC_CHANNELS 6

class adc {
  
  public:
    adc(int ms);
    void setSampleRate(int ms);
    boolean getData(int *n, int *data);
    void readADC();
    boolean isStarted();
    boolean isAvailable();
    boolean isBusy();
    void setStartStop(boolean start);
  
  private:
    int mSampleRate;
    int mCountDown;
    int mDummy;
    boolean mBusy;
    int mData[MAX_ADC_CHANNELS];
    boolean mAvailable;
    boolean mStartStop;
    
    bool output;      // temporu for test purposes

};    

#endif



