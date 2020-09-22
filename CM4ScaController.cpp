//
// CM4ScaController.cpp
//
// Copyright (C) 2018-2025 Cloudminds. All Rights Reserved.
//
//

#include "CM4ScaCommon.h"

//
//	Global variables
//

CM4Log g_Log;
AxisMotionInfo *g_MotionInfo = NULL;
unsigned short g_AxisNum = 0;
bool g_StartGetPVCTimer = false;
bool g_CloseGetPVCThread = false;
pthread_t g_tid[ECU_COUNT];
string g_EcuIp[ECU_COUNT] = {"192.168.0.101"};
EcuRelatedInfo g_ecuRelatedInfo[ECU_COUNT];
short g_PvcTimeoutCount = 0;
ThreadParm g_ThreadParm[ECU_COUNT];

CM_SCA_Controller SCACtrller;

CM_SCA_Controller *CM_SCA_Controller::getInstance()
{
	return &SCACtrller;
}

// short CM_SCA_Controller::CM_InitController()
// {
// 	short rtn = ERR_NONE;
// 	short i = 0, tempRtn = 0;
// 	vector<short> Axis;
// 	const short nMaxTimeoutCount = 200;
// 	const short nMaxLoopCount = 1;

// 	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_InitController()");

// 	cout << "Enter CM_SCA_Controller::CM_InitController()" << endl;

// 	do
// 	{
// 		g_PvcTimeoutCount = 0;

// 		// 初始化
// 		rtn = SCACtrller.CM_Init();
// 		if (rtn != 0)
// 		{
// 			goto LABEL_EXIT;
// 		}

// 		cout << "Enter CM_SCA_Controller::CM_InitController() - CM_Init" << endl;		

// 		// sleep(1);

// 		// 开始GetPVC定时器
// 		SCACtrller.CM_StartGetPVCTimer(true);

// 		// 初始化完成sleep
// 		sleep(3);

// 		// 通讯的超时次数合理，正行退出
// 		if (g_PvcTimeoutCount <= nMaxTimeoutCount)
// 		{
// 			break;
// 		}
// 		else
// 		{
// 			// 通讯异常，停止getPVC
// 			SCACtrller.CM_StartGetPVCTimer(false);
// 			sleep(1);
// 		}

// 		cout << "Enter CM_SCA_Controller::CM_InitController() - CM_StartGetPVCTimer" << endl;		

// 		i++;
// 		if (i >= nMaxLoopCount)
// 		{
// 			rtn = ERR_WAITTING_TIMEOUT;
// 			goto LABEL_EXIT;
// 		}

// 		// release
// 		SCACtrller.CM_Release();
// 		sleep(1);
// 	} while (true);

// LABEL_EXIT:
// 	if (rtn == 0)
// 		g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_InitController()=%d", rtn);
// 	else
// 		g_Log.writeLog(CM4_LOG_LEVEL_ERROR, "Exit  CM_SCA_Controller::CM_InitController()=%d", rtn);
// 	return rtn;
// }

short CM_SCA_Controller::CM_InitController()
{
	short rtn = ERR_NONE;
	short i = 0, tempRtn = 0;
	vector<short> Axis;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_InitController()");
	cout << "Enter CM_SCA_Controller::CM_InitController()" << endl;
	
	// 连接Axis
	rtn = SCACtrller.CM_Connect();
	if (rtn != 0)
	{
		goto LABEL_EXIT;
	}

	// 得到所有轴id
	rtn = SCACtrller.CM_GetAllAxisID(Axis);
	if (rtn != 0)
	{
		goto LABEL_EXIT;
	}

	// 初始化所有的Axis
	rtn = SCACtrller.CM_InitAll();
	if (rtn != 0)
	{
		goto LABEL_EXIT;
	}

	// 3.设置缺省模式
	for (i = 0; i <Axis.size(); i++)
	{
		cout << "Axis.size() = " <<Axis.size() <<    endl;
		cout << "Axis.at() here  = " <<Axis.at(i)<<    endl;
		tempRtn = SCACtrller.CM_SetProfilePositionMode(Axis.at(i));
		if (0 != tempRtn)
		{
			cout << "Enter CM_InitController(), axis = " << i <<  ", CM_SetProfilePositionMode= " << tempRtn << endl;
			rtn = tempRtn;
		}
	}
	
	cout << "Enter CM_SCA_Controller::CM_InitController() - CM_SetProfilePositionMode" << endl;


	//
	// SCACtrller.SendBrakeFalse();
	//SCACtrller.SendBrakeTrue();

	
	// 开始GetPVC定时器
	SCACtrller.CM_StartGetPVCTimer(false);

	// 初始化完成sleep
	sleep(3);

LABEL_EXIT:
	if (rtn == 0)
		g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_InitController()=%d", rtn);
	else
		g_Log.writeLog(CM4_LOG_LEVEL_ERROR, "Exit  CM_SCA_Controller::CM_InitController()=%d", rtn);
	return rtn;
}


short CM_SCA_Controller::CM_Init()
{
	short rtn = ERR_NONE;
	short i = 0, tempRtn = 0;
	vector<short> Axis;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_Init()");

	// 连接Axis
	rtn = CM_Connect();
	if (rtn != 0)
	{
		goto LABEL_EXIT;
	}

	// 得到所有轴id
	rtn = CM_GetAllAxisID(Axis);
	if (rtn != 0)
	{
		goto LABEL_EXIT;
	}

	// 初始化所有的Axis
	rtn = CM_InitAll();
	if (rtn != 0)
	{
		goto LABEL_EXIT;
	}

	// 3.设置缺省模式
	for (i = 1; i <= 34; i++)
	{
		tempRtn = SCACtrller.CM_SetProfilePositionMode(i);
		if (0 != tempRtn)
		{
			rtn = tempRtn;
		}
	}

LABEL_EXIT:
	if (rtn == 0)
		g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_Init()=%d", rtn);
	else
		g_Log.writeLog(CM4_LOG_LEVEL_ERROR, "Exit  CM_SCA_Controller::CM_Init()=%d", rtn);
	return rtn;
}

short CM_SCA_Controller::CM_Connect()
{
	short rtn = ERR_NONE;
	short i = 0, j = 0, k = 0;
	vector<short> axis[ECU_COUNT];

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_Connect()");

	if (0 != g_AxisNum)
	{
		rtn = ERR_STATUS;
		goto LABEL_EXIT;
	}

	// 初始化ECU信息
	rtn = InitEcuRelatedInfo();
	if (ERR_NONE != rtn)
	{
		goto LABEL_EXIT;
	}

	// 对应多个ECU + PrepareWork
	for (i = 0; i < ECU_COUNT; i++)
	{
		rtn = PrepareWork(i, axis[i]);
		if (0 != rtn)
		{
			goto LABEL_EXIT;
		}
	}

	// 没有Axis
	if (0 == g_AxisNum)
	{
		rtn = ERR_EXECT;
		goto LABEL_EXIT;
	}

	// 申请内存g_MotionInfo
	g_MotionInfo = (struct AxisMotionInfo *)malloc(g_AxisNum * sizeof(struct AxisMotionInfo));
	if (g_MotionInfo == NULL)
	{
		rtn = ERR_MALLOC_MEMORY;
		goto LABEL_EXIT;
	}
	// 初始化申请的g_MotionInfo内存
	memset(g_MotionInfo, 0, g_AxisNum * sizeof(g_MotionInfo[0]));

	// 为每个Axis写入当前的ID和IP
	k = 0;
	for (i = 0; i < ECU_COUNT; i++)
	{
		for (j = 0; j < axis[i].size(); j++)
		{
			g_MotionInfo[k].IP = i;
			g_MotionInfo[k++].ID = axis[i].at(j);
		}
	}

	// 启动循环线程读取PVC的值，每个ECU（ip）对应一个线程
	g_CloseGetPVCThread = false;
	// ThreadParm threadParm[ECU_COUNT];

	for (i = 0; i < ECU_COUNT; i++)
	{
		g_ThreadParm[i].IP = i;
		g_ThreadParm[i].This = this;
		rtn = pthread_create(&g_tid[i], NULL, TimerGetPVC, &g_ThreadParm[i]);
		if (rtn < 0)
		{
			rtn = ERR_CREATE_THREAD;
			goto LABEL_EXIT;
		}
	}

LABEL_EXIT:
	if (rtn == 0)
		g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_Connect()=%d", rtn);
	else
		g_Log.writeLog(CM4_LOG_LEVEL_ERROR, "Exit  CM_SCA_Controller::CM_Connect()=%d", rtn);
	return rtn;
}

short CM_SCA_Controller::CM_Disconnect()
{
	short rtn = ERR_NONE;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_Disconnect(), AxisNum = %d", g_AxisNum);

	if (g_AxisNum == 0)
	{
		goto LABEL_EXIT;
	}

	// tbd: 退出时要保持当前状态
	// 关闭所有Axis
	// CM_CloseAll();

	// 去初始化ECU信息
	DeinitEcuRelatedInfo();

	// 释放内存g_MotionInfo
	if (g_MotionInfo != NULL)
	{
		free(g_MotionInfo);
		g_MotionInfo = NULL;
	}

	g_AxisNum = 0;

LABEL_EXIT:
	if (rtn == 0)
		g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_Disconnect()=%d", rtn);
	else
		g_Log.writeLog(CM4_LOG_LEVEL_ERROR, "Exit  CM_SCA_Controller::CM_Disconnect()=%d", rtn);
	return rtn;
}

short CM_SCA_Controller::CM_InitAll()
{
	short i;
	short rtn = ERR_NONE;
	vector<short> id;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_InitAll()");

	if (0 == g_AxisNum)
	{
		rtn = ERR_AXIS_NUM_IS_ZERO;
		goto LABEL_EXIT;
	}

	for (i = 0; i < g_AxisNum; i++)
	{
		id.push_back(g_MotionInfo[i].ID);
	}

	// open axis
	rtn = Open(id);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	// 设置所有axis的缺省值
	for (i = 0; i < g_AxisNum; i++)
	{
		// 打开限位开关
		rtn = CM_SetSoftLimitStatus(g_MotionInfo[i].ID, 1);

		// 清除报警
		CM_ClearAlarm(g_MotionInfo[i].ID);
	}

LABEL_EXIT:
	if (rtn == 0)
		g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_InitAll()=%d", rtn);
	else
		g_Log.writeLog(CM4_LOG_LEVEL_ERROR, "Exit  CM_SCA_Controller::CM_InitAll()=%d", rtn);
	return rtn;
}

short CM_SCA_Controller::CM_InitAxis(vector<short> axis)
{
	int i;
	short rtn = ERR_NONE;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_InitAxis(vector<short> axis)");

	if (0 == axis.size())
	{
		rtn = ERR_INPUT_PARM;
		goto LABEL_EXIT;
	}

	// input check
	for (i = 0; i < axis.size(); i++)
	{
		rtn = AxisID2Index(axis.at(i));
		if (-1 == rtn)
		{
			rtn = ERR_AXIS_NO_FOUND;
			goto LABEL_EXIT;
		}
	}

	// open axis
	rtn = Open(axis);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_InitAxis(vector<short> axis)=%d", rtn);
	return rtn;
}

short CM_SCA_Controller::CM_InitAxis(short axis)
{
	short rtn = ERR_NONE;
	vector<short> Axis;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_InitAxis(%d)", axis);

	Axis.push_back(axis);

	//input check
	rtn = AxisID2Index(axis);
	if (-1 == rtn)
	{
		rtn = ERR_AXIS_NO_FOUND;
		goto LABEL_EXIT;
	}

	rtn = Open(Axis);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_InitAxis(%d)=%d", axis, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_CloseAll()
{
	int i;
	short rtn = ERR_NONE;
	vector<short> id;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_CloseAll()");

	for (i = 0; i < g_AxisNum; i++)
	{
		id.push_back(g_MotionInfo[i].ID);
	}
	rtn = Close(id);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_CloseAll()=%d", rtn);
	return rtn;
}

short CM_SCA_Controller::CM_CloseAxis(vector<short> axis)
{
	int i;
	short rtn = ERR_NONE;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_CloseAxis(vector<short> axis)");

	// input check
	for (i = 0; i < axis.size(); i++)
	{
		rtn = AxisID2Index(axis.at(i));
		if (-1 == rtn)
		{
			rtn = ERR_AXIS_NO_FOUND;
			goto LABEL_EXIT;
		}
	}

	rtn = Close(axis);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_CloseAll()=%d", rtn);
	return rtn;
}

short CM_SCA_Controller::CM_CloseAxis(short axis)
{
	int i;
	short rtn = ERR_NONE;
	vector<short> Axis;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_CloseAxis(%d)", axis);

	Axis.push_back(axis);

	// input check
	rtn = AxisID2Index(axis);
	if (-1 == rtn)
	{
		rtn = ERR_AXIS_NO_FOUND;
		goto LABEL_EXIT;
	}

	// close axis
	rtn = Close(Axis);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_CloseAxis(%d)=%d", axis, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_ResetAll()
{
	short rtn = ERR_NONE;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_ResetAll()");
	rtn = CM_CloseAll();
	if (0 < rtn)
	{
		goto LABEL_EXIT;
	}

	rtn = CM_InitAll();
	if (0 < rtn)
	{
		goto LABEL_EXIT;
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_ResetAll()=%d", rtn);
	return rtn;
}

short CM_SCA_Controller::CM_ResetAxis(vector<short> axis)
{
	int i;
	short rtn = ERR_NONE;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_ResetAll(vector<short> axis)");

	//input check
	for (i = 0; i < axis.size(); i++)
	{
		rtn = AxisID2Index(axis.at(i));
		if (-1 == rtn)
		{
			rtn = ERR_AXIS_NO_FOUND;
			goto LABEL_EXIT;
		}
	}

	rtn = CM_CloseAxis(axis);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	rtn = CM_InitAxis(axis);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_ResetAxis(vector<short> axis)=%d", rtn);
	return rtn;
}

short CM_SCA_Controller::CM_ResetAxis(short axis)
{
	int i;
	short rtn = ERR_NONE;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_ResetAxis(%d)", axis);

	// input check
	rtn = AxisID2Index(axis);
	if (-1 == rtn)
	{
		rtn = ERR_AXIS_NO_FOUND;
		goto LABEL_EXIT;
	}

	rtn = CM_CloseAxis(axis);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	rtn = CM_InitAxis(axis);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_ResetAxis(%d)=%d", axis, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_GetAllAxisID(vector<short> &ID)
{
	int i, j;
	short rtn = ERR_NONE;
	bool flag;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_GetAllAxisID()");

	ID.clear();

	if (0 == g_AxisNum)
	{
		rtn = ERR_STATUS;
		goto LABEL_EXIT;
	}

	for (i = 0; i < g_AxisNum; i++)
	{
		ID.push_back(g_MotionInfo[i].ID);
	}
	sort(ID.begin(), ID.end());

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_GetAllAxisID()=%d", rtn);
	return rtn;
}

short CM_SCA_Controller::CM_ChangeAxisID(short ID1, short ID2)
{
	short rtn = ERR_NONE;
	short index, index2;
	bool flag = false;
	char code[4];
	CommunicationData CommData;
	short ip;
	EcuRelatedInfo *p = NULL;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_ChangeAxisID(%d, %d)", ID1, ID2);

	//input check
	index = AxisID2Index(ID1);
	if (-1 == index)
	{
		rtn = ERR_AXIS_NO_FOUND;
		goto LABEL_EXIT;
	}

	index2 = AxisID2Index(ID2);
	if (-1 != index2)
	{
		rtn = ERR_INPUT_PARM2;
		goto LABEL_EXIT;
	}

	ip = g_MotionInfo[index].IP;
	p = &g_ecuRelatedInfo[ip];

	//status check
	if (!g_MotionInfo[index].IsOpening || g_MotionInfo[index].IsRunning)
	{
		rtn = ERR_STATUS;
		goto LABEL_EXIT;
	}

	//thread lock
	pthread_mutex_lock(&p->mutexLock);

	//0x3d
	memset(&CommData, 0, sizeof(CommunicationData));
	CommData.SendAxis = ID1;
	CommData.SendCmd = CMD_SET_ACTUATOR_ID;
	CommData.SendDataLen = 5;
	memcpy(CommData.SendData, code, 4);
	CommData.SendData[4] = ID2;
	//CRC16_1(&CommData.SendData[0], (short)CommData.SendDataLen, CommData.SendCrc);
	rtn = CommSend(&CommData);
	if (0 != rtn)
	{
		//thread unlock
		pthread_mutex_unlock(&p->mutexLock);
		goto LABEL_EXIT;
	}
	rtn = CommRtn(&CommData);
	if (0 != rtn)
	{
		//thread unlock
		pthread_mutex_unlock(&p->mutexLock);
		goto LABEL_EXIT;
	}
	if (CommData.RtnAxis != ID2 || !(short)CommData.RtnData[0])
	{
		//thread unlock
		pthread_mutex_unlock(&p->mutexLock);
		rtn = ERR_EXECT;
		goto LABEL_EXIT;
	}

	//thread unlock
	pthread_mutex_unlock(&p->mutexLock);

	//set global variables
	g_MotionInfo[index].ID = index;

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_ChangeAxisID(%d, %d)=%d", ID1, ID2, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_SaveParm(short axis)
{
	short rtn = ERR_NONE;
	short index;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_SaveParm(%d)", axis);

	//input check
	index = AxisID2Index(axis);
	if (-1 == index)
	{
		rtn = ERR_AXIS_NO_FOUND;
		goto LABEL_EXIT;
	}

	//status check
	if (!g_MotionInfo[index].IsOpening || g_MotionInfo[index].IsRunning)
	{
		rtn = ERR_STATUS;
		goto LABEL_EXIT;
	}

	//save parm
	rtn = TransCommData(axis, CMD_SAVE_PARAMETER, 0x00, 0x01);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_SaveParm(%d)=%d", axis, rtn);
	return ERR_NONE;
}

short CM_SCA_Controller::CM_Zeros(short axis, double value)
{
	short rtn = ERR_NONE;
	long val;
	double delta;
	double NSoftLimit, PSoftLimit;
	short index;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_Zeros(%d, %lf)", axis, value);

	// input check
	index = AxisID2Index(axis);
	if (-1 == index)
	{
		rtn = ERR_AXIS_NO_FOUND;
		goto LABEL_EXIT;
	}

	//status check
	if (!g_MotionInfo[index].IsOpening ||
		g_MotionInfo[index].IsRunning ||
		g_MotionInfo[index].MotionMode != HOMING_MODE)
	{
		rtn = ERR_STATUS;
		goto LABEL_EXIT;
	}

	//double check, if it's not homing mode ,it will be very dangerous!!!
	rtn = CM_GetProfileMode(axis, val);
	if (rtn != 0)
	{
		goto LABEL_EXIT;
	}

	if (val != HOMING_MODE&& val != CURRENT_MODE)
	{
		rtn = ERR_AXIS_ISNOT_HOMING_MODE;
		goto LABEL_EXIT;
	}

	rtn = CM_GetSoftLimitValue(axis, NSoftLimit, PSoftLimit);
	if (rtn != 0)
	{
		goto LABEL_EXIT;
	}

	// 设置Homing的操作模式：01为手动，02为自动
	rtn = TransCommData(axis, CMD_SET_HOMING_OPERATE_MODE, 0x01, 0x01);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	rtn = TransCommData(axis, CMD_SET_HOMMING_POSITION, 0x04, value);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	// set limit pos
	// rtn = CM_SetSoftLimitValue(axis, NSoftLimit, PSoftLimit);
	// if (rtn != 0)
	// {
	// 	return rtn;
	// }

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_Zeros(%d, %lf)=%d", axis, value, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_GetSWVersion(char *version)
{
	short rtn = ERR_NONE;
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_GetSWVersion()");

	if (version == NULL)
	{
		rtn = ERR_INPUT_PARM;
		goto LABEL_EXIT;
	}

	//gcvt(CM_SCA_Controller_SDK_VERSION, 2, Version);
	sprintf(version, "%s", CM_SCA_CONTROLLER_SDK_VERSION);

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_GetSWVersion()=%d", rtn);
	return rtn;
}

short CM_SCA_Controller::CM_GetHWVersion(short axis, char *version)
{
	short rtn = ERR_NONE;
	double temp = 0.0;
	CommunicationData CommData;
	short index = AxisID2Index(axis);

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_GetHWVersion(%d, 0x%lf)", axis, version);

	// input check
	if (-1 == index)
	{
		rtn = ERR_AXIS_NO_FOUND;
		goto LABEL_EXIT;
	}

	if (version == NULL)
	{
		rtn = ERR_INPUT_PARM2;
		goto LABEL_EXIT;
	}

	// 0x01
	memset(&CommData, 0, sizeof(CommunicationData));
	CommData.SendAxis = (unsigned char)axis;
	CommData.SendCmd = CMD_GET_ACTUATOR_VERSION;
	CommData.SendDataLen = 0x00;
	rtn = CommProsses(&CommData);
	if (0 != rtn)
	{
		return rtn;
	}

	// temp = (double)CommData.RtnData[0] +
	// 	   (double)CommData.RtnData[1] / 10.0 +
	// 	   (double)CommData.RtnData[2] / 100.0;
	// gcvt(temp, 2, Version);

	sprintf(version, "%d.%d.%d", CommData.RtnData[0], CommData.RtnData[1], CommData.RtnData[2]);

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_GetHWVersion(%d, 0x%lf)=%d", axis, version, rtn);
	return rtn;
}

CM_SCA_Controller::CM_SCA_Controller() : m_bReadInfoFromBuff(true)
{
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "*** CM_SCA_Controller::CM_SCA_Controller()");
}

short CM_SCA_Controller::CM_Release()
{
	short rtn = 0;
	short i = 0;
	void *status;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_Release()");

	// 1.关闭GetPVC线程
	g_CloseGetPVCThread = true;
	// usleep(5000 * 2);
	sleep(1);
	for (i = 0; i < ECU_COUNT; i++)
	{
		// 等待线程结束
		pthread_join(g_tid[i], &status);
	}

	// 2.断开执行器的连接
	CM_Disconnect();

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_Release()");
	return rtn;
}

CM_SCA_Controller::~CM_SCA_Controller()
{
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::~CM_SCA_Controller()");
	cout << "Enter CM_SCA_Controller::~CM_SCA_Controller()" << endl;

	CM_Release();

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::~CM_SCA_Controller()");
	cout << "Exit  CM_SCA_Controller::~CM_SCA_Controller()" << endl;
}
