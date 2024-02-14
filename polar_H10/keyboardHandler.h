//
// keyBoardHandler
//
//    Interface file for the keyboard handler. This class mimics the hostInterface class
//    so programs can be debugged using the terminal
//
//  modifications
//    17-ju;-2022   JM    initial version

#ifndef KEYBOARDHANDLER_H
#define KEYBOARDHANDLER_H

#define MAX_DATA_SIZE 64
#define BAUDRATE 115200

#define NR_COMMANDS 26

typedef void (*eventFunction)(int n, int *data);

class keyBoardHandler {

  public:
    keyBoardHandler(long int baudrate);
    void init();
    boolean sendCmd(char cmd, int n, int *data);
    void handleCmd();
    boolean setEvent(char c, eventFunction);

  private:
    boolean getCmd(char *cmd, int *n, int *data);

    char mLastCmd;
    boolean mStartStop;
    int mDataLen;
    int cmd_buffer[50];
    long int mBaudRate;
    eventFunction cmdEvents[NR_COMMANDS];
};

#endif
