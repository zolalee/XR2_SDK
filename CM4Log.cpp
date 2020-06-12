//
// CM4Log.cpp
//
// Copyright (C) 2016-2020 Cloudminds Ltd., All Rights Reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include <stdarg.h>
#include <iostream>
#include "CM4Log.h"

#define CM_MSG_LEN 200

#ifndef MAX_PATH
#define MAX_PATH 256
#endif

CM4Log::CM4Log()
{
    // Notes: 如果log级别是CM4_LOG_LEVEL_INFO，因为时间因素，将会影响到机器人的执行速度，会有卡顿
    // m_enuLogLevel = CM4_LOG_LEVEL_INFO;

    m_enuLogLevel = CM4_LOG_LEVEL_ERROR;    

    // log输出到console
    // m_enuLogWay = CM4_LOG_WAY_CONSOLE;

    // log输出到文件
    m_enuLogWay = CM4_LOG_WAY_FILE;
}

CM4Log::~CM4Log()
{
}

char *CM4Log::getCurrentTime()
{
    static char timestr[40];
    time_t t;
    struct tm *nowtime;

    time(&t);
    nowtime = localtime(&t);
    strftime(timestr, sizeof(timestr), "[%Y-%m-%d %H:%M:%S] ", nowtime);
    return timestr;
}

char *CM4Log::getLogFileName(int ecuNum)
{
    static char datestr[20], fileName[40];
    time_t t;
    struct tm *nowtime;
    char *path = getenv("HOME");

    time(&t);
    nowtime = localtime(&t);
    strftime(datestr, sizeof(datestr), "%Y-%m-%d", nowtime);

    if (ecuNum <= 0)
    {
        sprintf(fileName, "%s/log/%s.log", path, datestr);
    }
    else
    {
        sprintf(fileName, "%s/log/%s(%d).log", path, datestr, ecuNum);
    }
    
    return fileName;
}

int CM4Log::writeLog(CM4LogMsgLevel LogLevel, const char *Fmt, ...)
{
    int nRet = 0;

    char FileName[MAX_PATH] = {0};
    char szTmpBuf[CM_MSG_LEN] = {0};
    char szLog[MAX_PATH] = {0};
    FILE *fp = NULL;
    va_list ap;

    if (m_enuLogLevel < LogLevel)
    {
        nRet = -1;
        return nRet;
    }    

    // Prepare the string based on format
    va_start(ap, Fmt);
    vsprintf(szTmpBuf, Fmt, ap);
    va_end(ap);

    // Timestamp + Content
    sprintf(szLog, "%s%s\n", getCurrentTime(), szTmpBuf);

    if (m_enuLogWay == CM4_LOG_WAY_CONSOLE)
    {
        std::cout << szLog;
    }
    else
    {
        // open log file
        strcpy(FileName, getLogFileName());
        fp = fopen(FileName, "ab+");
        if (fp == NULL)
        {
            nRet = -2;
            return nRet;
        }

        // write log
        fwrite(szLog, 1, strlen(szLog), fp);
        fclose(fp);
    }
    
    return nRet;
}

int CM4Log::writeLog(CM4LogMsgLevel LogLevel, int ecuNum, const char *Fmt, ...)
{
    int nRet = 0;

    char FileName[MAX_PATH] = {0};
    char szTmpBuf[CM_MSG_LEN] = {0};
    char szLog[MAX_PATH] = {0};
    FILE *fp = NULL;
    va_list ap;

    if (m_enuLogLevel < LogLevel)
    {
        nRet = -1;
        return nRet;
    }    

    // Prepare the string based on format
    va_start(ap, Fmt);
    vsprintf(szTmpBuf, Fmt, ap);
    va_end(ap);

    // Timestamp + Content
    sprintf(szLog, "%s%s\n", getCurrentTime(), szTmpBuf);

    if (m_enuLogWay == CM4_LOG_WAY_CONSOLE)
    {
        std::cout << szLog;
    }
    else
    {
        // open log file
        strcpy(FileName, getLogFileName(ecuNum));
        fp = fopen(FileName, "ab+");
        if (fp == NULL)
        {
            nRet = -2;
            return nRet;
        }

        // write log
        fwrite(szLog, 1, strlen(szLog), fp);
        fclose(fp);
    }
    
    return nRet;
}

int CM4Log::writeSpecifiedFile(char *FileName, char *Buf, int Size, int Flag)
{
    int nRet = 0;

    FILE *fp = NULL;
    if (Flag == 0)
    {
        fp = fopen(FileName, "ab+");
    }
    else
    {
        fp = fopen(FileName, "wb");
    }

    if (fp == NULL)
    {
        nRet = -1;
        return nRet;
    }

    fwrite(Buf, 1, Size, fp);
    fclose(fp);

    return nRet;
}
