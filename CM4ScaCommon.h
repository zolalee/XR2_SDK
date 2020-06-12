//
// CM4ScaCommon.h
//
// Copyright (C) 2018-2025 Cloudminds. All Rights Reserved.
//
//

#ifndef __CM4_SCA_COMMON_H__
#define __CM4_SCA_COMMON_H__

//
// Internal function
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <algorithm>
#include <iostream>
#include <signal.h>
#include <sys/time.h>

#include "CM_SCA_Controller.h"
#include "CM4Log.h"

/*---------------------------------------------------------------------------------------
------
------	instructions defines
------
---------------------------------------------------------------------------------------*/
#define ECU_COUNT                               1      // ECU的个数
#define AXIS_COUNT                              2      // Axis的个数
#define CYC_GET_PVC_TIME                        5000    // 定时器循环得到PVC的时间间隔(ms)
#define PORT                                    2000    // 通讯端口号
#define COMMUNICATION_TIME                      500000  // 通讯超时时间(us)
#define COMMUNICATION_TIME_1                     10000  // 通讯超时时间(us)
#define VELOCITY_RANGE                          6000
#define SOFTLIMIT_THRESHOLD                     0.001
#define RUNNING_VEL_THRESHOLD                   5
#define CM_SCA_PULSE_NUM                        10000

// #define CM_SCA_Controller_SDK_VERSION 1.0
#define CM_SCA_CONTROLLER_SDK_VERSION           "1.1" // SDK软件版本号

//read1, send 0, rtn 1
#define CMD_COMMUNICATION_HANDSHAKE             0x00
#define CMD_GET_ACTUATOR_ONOFF_STATUS           0x2B
#define CMD_FIRST_COMMUNICATION                 0x44
#define CMD_GET_ACTUATOR_MODE                   0x55
#define CMD_GET_FILTER_CURRENT_STATUS           0x71
#define CMD_GET_FILTER_VELOCITY_STATUS          0x75
#define CMD_GET_FILTER_POSITION_STATUS          0x79
//#define CMD_GET_LASTCLOSESTATUS				0xB0
#define CMD_GET_LIMIT_STATUS                    0x8B

//read2, send 0, rtn 2
#define CMD_GET_CURRENT_RANGE                   0x53
#define CMD_GET_ACTUATOR_TEMPERATURE            0x5F
#define CMD_GET_DRIVER_TEMPERATURE 0x60
//#define CMD_GET_ACTUATOR_SAFE_TEMPERATURE		0x62
//#define CMD_GET_ACTUATER_RECOVER_TEMPERATURE	0x64
#define CMD_GET_FILTER_CURRENT_WIDTH            0x73
#define CMD_GET_FILTER_VELOCITY_WIDTH           0x77
#define CMD_GET_FILTER_POSITION_WIDTH           0x7B
#define CMD_GET_ERROR_CODE                      0xFF

//read3, send 0, rtn 3
#define CMD_GET_ACTUATOR_VERSION                0x01
//read4, send 0, rtn 4
#define CMD_GET_ACTUATOR_ADDRESS                0x02
#define CMD_GET_PROFILE_CURRENT                 0x04
#define CMD_GET_PROFILE_VELOCITY                0x05
#define CMD_GET_PROFILE_POSITION                0x06
#define CMD_GET_CURRENT_PORPORTION              0x15
#define CMD_GET_CURRENT_INTEGRAL                0x16
#define CMD_GET_VELOCITY_PORPORTION             0x17
#define CMD_GET_VELOCITY_INTEGRAL               0x18
#define CMD_GET_POSITION_PORPORTION             0x19
#define CMD_GET_POSITION_INTEGRAL               0x1A
#define CMD_GET_MAX_VEL_PRFPOS                  0x1C
#define CMD_GET_MAX_ACC_PRFPOS                  0x1D
#define CMD_GET_MAX_DEC_PRFPOS                  0x1E
#define CMD_GET_MAX_VEL_PRFVEL                  0x22
#define CMD_GET_MAX_ACC_PRFVEL                  0x23
#define CMD_GET_MAX_DEC_PRFVEL                  0x24
//#define CMD_GET_MIN_OUTPUT_CURRENT			0x34
//#define CMD_GET_MAX_OUTPUT_CURRENT			0x35
#define CMD_GET_MIN_OUTPUT_VELOCITY             0x36
#define CMD_GET_MAX_OUTPUT_VELOCITY             0x37
#define CMD_GET_MIN_OUTPUT_POSITION             0x38
#define CMD_GET_MAX_OUTPUT_POSITION             0x39

#define CMD_GET_PROFILE_VOLTAGE                 0x45

//#define CMD_GET_ACTUATOR_INERTIA				0x7D
//#define CMD_GET_PLUGGING_ENERGY				0x7F
#define CMD_GET_POSITIVE_SOFTLIMIT              0x85
#define CMD_GET_NEGITIVE_SOFTLIMIT              0x86
//#define CMD_GET_OFFSET_POSITION				0x8A
//#define CMD_GET_MIN_HOMMING_CURRENT			0x92
//#define CMD_GET_MAX_HOMMING_CURRENT			0x93

//read5, send 0, rtn multi
#define CMD_GET_PROFILE_PVC                     0x94
//write1, send 0, rtn 0
#define CMD_SET_ACTUATOR_ID                     0x3D
//write2, send 0, rtn 1
#define CMD_SAVE_PARAMETER                      0x0D
//#define CMD_HOMING_DATA						0x88
#define CMD_SET_HOMING_OPERATE_MODE             0x8D
#define CMD_CLEAR_ERROR_STATUS                  0xFE
//write3, send 1, rtn 1
#define CMD_SET_ACTUATIR_MODE                   0x07
#define CMD_SET_ACTUATER_ONOFF                  0x2A
#define CMD_SET_FILTER_CURRENT_STATUS           0x70
#define CMD_SET_FILTER_VELOCITY_STATUS          0x74
#define CMD_SET_FILTER_POSITION_STATUS          0x78
//write4, send 2, rtn 1
//#define CMD_SET_ACTUATOR_SAFE_TEMPERATURE		0x61
//#define CMD_SET_ACTUATER_RECOVER_TEMPERATURE	0x63
#define CMD_SET_FILTER_CURRENT_WIDTH            0x72
#define CMD_SET_FILTER_VELOCITY_WIDTH           0x76
#define CMD_SET_FILTER_POSITION_WIDTH           0x7A

#define CMD_GET_BRAKE_STATE                     0xB5
#define CMD_SET_BRAKE_STATE                     0xB6

#define CMD_GET_IMU_DATA                        0xC1

//write5, send 4, rtn 1/0
#define CMD_SET_PROFILE_CURRENT                 0x08
#define CMD_SET_PROFILE_VELOCITY                0x09
#define CMD_SET_PROFILE_POSITION                0x0A
#define CMD_SET_CURRENT_PORPORTION              0x0E
#define CMD_SET_CURRENT_INTEGRAL                0x0F
#define CMD_SET_VELOCITY_PORPORTION             0x10
#define CMD_SET_VELOCITY_INTEGRAL               0x11
#define CMD_SET_POSITION_PORPORTION             0x12
#define CMD_SET_POSITION_INTEGRAL               0x13
#define CMD_SET_MAX_VEL_PRFPOS                  0x1F
#define CMD_SET_MAX_ACC_PRFPOS                  0x20
#define CMD_SET_MAX_DEC_PRFPOS                  0x21
#define CMD_SET_MAX_VEL_PRFVEL                  0x25
#define CMD_SET_MAX_ACC_PRFVEL                  0x26
#define CMD_SET_MAX_DEC_PRFVEL                  0x27
//#define CMD_SET_MIN_OUTPUT_CURRENT			0x2E
//#define CMD_SET_MAX_OUTPUT_CURRENT			0x2F
#define CMD_SET_MIN_OUTPUT_VELOCITY             0x30
#define CMD_SET_MAX_OUTPUT_VELOCITY             0x31
#define CMD_SET_MIN_OUTPUT_POSITION             0x32
#define CMD_SET_MAX_OUTPUT_POSITION             0x33
//#define CMD_SET_PLUGGING_ENERGY				0x7E
#define CMD_SET_POSITIVE_SOFTLIMIT              0x83
#define CMD_SET_NEGITIVE_SOFTLIMIT              0x84
#define CMD_SET_HOMMING_POSITION                0x87
//#define CMD_SET_OFFSET_POSITION				0x89
#define CMD_SET_LIMIT_SWITCH 0X8C
//#define CMD_SET_MIN_HOMMING_CURRENT			0x90
//#define CMD_SET_MAX_HOMMING_CURRENT			0x91

// finger actuator temporary solution
#define IsFingerActuator(axis) ((axis >= 25 && axis <= 34) ? true : false)

/*---------------------------------------------------------------------------------------
------
------	Enum
------
---------------------------------------------------------------------------------------*/
enum MOTION_MODE
{
    NONE_MODE = 0,              // 0, 无运动模式
    CURRENT_MODE,               // 1, 电流模式
    VELLOCITY_MODE,             // 2, 速度模式
    POSITION_MODE,              // 3, 位置模式
    PROFILE_POSITION_MODE = 6,  // 6, profile位置模式
    PROFILE_VELOCITY_MODE,      // 7, profile速度模式
    HOMING_MODE,                // 8, homing模式
};

enum AXIS_STAUS
{
    AXIS_ALARM = 1,             // 1, 轴报警
    POSITIVE_lIMIT_ACTIVE,      // 2, 正限位触发（前沿驱动未提供）
    NEGETIVE_LIMIT_ACTIVE,      // 3, 负限位触发（前沿驱动未提供）
    AXIS_RUNNING,               // 4, 轴运动标志（前沿驱动未提供）
    AXIS_ARRIVE,                // 5, 轴到位标志（前沿驱动未提供）
    AXIS_OPEN,                  // 6, 轴启动
    AXIS_CONNECT,               // 7, 轴连接
    AXIS_OFFLINE,               // 8, 轴非在线
};

/*---------------------------------------------------------------------------------------
------
------	Structs
------
---------------------------------------------------------------------------------------*/
struct AxisMotionInfo
{
    unsigned short ID;
    unsigned short IP;
    unsigned short MotionMode;
    bool IsOpening;
    bool IsRunning;
    //bool IsArrived;
    bool LimitStatus;
    unsigned long Band;
    unsigned long BandTime;

    double LastPos;
    double LastVel;
    double LastCur;

    double CurrentPos;
    double CurrentVel;
    double CurrentCur;

    double CurrentRange;
    SafeParm SParm;
};

// ECU相关信息
struct EcuRelatedInfo
{
    // unsigned short IP;
    pthread_mutex_t mutexLock;
    int serverFd;
    sockaddr_in clientAddr;
    socklen_t addrLen;
};

// Thread传入参数
struct ThreadParm
{
    unsigned short IP;
    CM_SCA_Controller *This;
};

#endif // __CM4_SCA_COMMON_H__