//
// hostInterface.h
//
//  header file for the <hostInteface> class. This class is responsable for the 
//  interface between host and Arduino controller. The serial interface is used
//
//  Modifications
//    16-jan-2013    JM    initial version
//    29-jan-2015    JM    now callback functions are used
//    18-nov-2016    JM    in event function, n is no pointer      

#ifndef HOSTINTERFACE_H
#define HOSTINTERFACE_H

#define MAX_DATA_SIZE 64
#define BAUDRATE 115200
// #define BAUDRATE 9600
#define BUADRATE 1200
#define NR_COMMANDS 26

typedef void (*eventFunction)(int n,int *data);

class hostInterface {
  
  public:
    hostInterface(long int baudrate);
    void start();
    boolean isDataAvailable();
    boolean sendCmd(char cmd,int n,int *data);
    void handleCmd();
    boolean setEvent(char c,eventFunction);
  
  private:
    boolean getCmd(char *cmd,int *n,int *data);
     
  char mLastCmd;
  int  mLastData[MAX_DATA_SIZE];
  int  mDataLen;
  int cmd_buffer[50];
  long int  mBaudRate;
  eventFunction cmdEvents[NR_COMMANDS];
}; 

#endif
