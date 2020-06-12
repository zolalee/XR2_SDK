//
// CM4Log.h
//
// Copyright (C) 2016-2020 Cloudminds Ltd., All Rights Reserved.
//

#ifndef __CM4_LOG_H__
#define __CM4_LOG_H__

//
// This is for each log message
//
typedef enum tagCM4LogMsgLevel
{
    CM4_LOG_LEVEL_ERROR,    // something causes the failure
    CM4_LOG_LEVEL_WARNING,  // not a failure but potentially impact the system
    CM4_LOG_LEVEL_INFO,     // to track workflow. The following should be in this catagory:
                            //      - 'Enter' or 'Exit' the API functions
                            //      - Major workflow
    CM4_LOG_LEVEL_DBG1,     // first level of debug info, for high level function call including following
                            //      - 
    CM4_LOG_LEVEL_DBG2,     // second level of debug info, for low level function call including
                            //      - 
    CM4_LOG_LEVEL_DBG3      // most detail debug info, including
                            //      - 
} CM4LogMsgLevel;

//
// Write log to where
//
typedef enum tagCM4LogWay
{
    CM4_LOG_WAY_FILE,
    CM4_LOG_WAY_CONSOLE
} CM4LogWay;


class CM4Log
{
public:
    CM4Log();
    ~CM4Log();

    // write log
    int writeLog(CM4LogMsgLevel LogLevel, const char *Fmt, ...);
    int writeLog(CM4LogMsgLevel LogLevel, int ecuNum, const char *Fmt, ...);

    // write specified file
    int writeSpecifiedFile(char *FileName, char *Buf, int Size, int Flag = 0);

    // time = "[%Y-%m-%d %H:%M:%S] "
    char *getCurrentTime();

    // file name = "/Home/log/YYYY-MM-DD(ecuNum).log"
    char *getLogFileName(int ecuNum=0);

private:
    CM4LogMsgLevel m_enuLogLevel;
    CM4LogWay m_enuLogWay;

};

#endif // __CM4_LOG_H__
