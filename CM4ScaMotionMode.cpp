//
// CM4ScaMotionMode.cpp
//
// Copyright (C) 2018-2025 Cloudminds. All Rights Reserved.
//
//

#include "CM4ScaCommon.h"

extern CM4Log g_Log;
extern AxisMotionInfo *g_MotionInfo;
extern unsigned short g_AxisNum;
extern bool g_StartGetPVCTimer;
extern string g_EcuIp[ECU_COUNT];
extern EcuRelatedInfo g_ecuRelatedInfo[ECU_COUNT];
union EndianWrap_U
	{
		float v;
		char  c[4];
	};
//------------------------------------------------------------------

// motion mode
short CM_SCA_Controller::CM_SetPositionMode(short axis)
{
	short rtn = ERR_NONE;
	short index = AxisID2Index(axis);

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_SetPositionMode(%d)", axis);

	// input check
	if (-1 == index)
	{
		rtn = ERR_INPUT_PARM1;
		goto LABEL_EXIT;
	}

	// status check
	if (!g_MotionInfo[index].IsOpening || g_MotionInfo[index].IsRunning)
	{
		rtn = ERR_STATUS;
		goto LABEL_EXIT;
	}

	// 0x07
	rtn = TransCommData(axis, CMD_SET_ACTUATIR_MODE, 0x01, POSITION_MODE);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	// set global variables
	g_MotionInfo[index].MotionMode = POSITION_MODE;

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_SetPositionMode(%d)=%d", axis, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_SetProfilePositionMode(short axis)
{
	short rtn = ERR_NONE;
	bool status;
	short index = AxisID2Index(axis);

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_SetProfilePositionMode(%d)", axis);

	// input check
	if (-1 == index)
	{
		rtn = ERR_INPUT_PARM1;
		goto LABEL_EXIT;
	}

	// status check
	if (!g_MotionInfo[index].IsOpening || g_MotionInfo[index].IsRunning)
	{
		rtn = ERR_STATUS;
		goto LABEL_EXIT;
	}

	// 0x07
	rtn = TransCommData(axis, CMD_SET_ACTUATIR_MODE, 0x01, PROFILE_POSITION_MODE);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	// set global variables
	g_MotionInfo[index].MotionMode = PROFILE_POSITION_MODE;

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_SetProfilePositionMode(%d)=%d", axis, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_SetProfilePositionAcc(short axis, double acc)
{
	short rtn = ERR_NONE;
	short index = AxisID2Index(axis);

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_SetProfilePositionAcc(%d, %lf)", axis, acc);

	// input check
	if (-1 == index)
	{
		rtn = ERR_INPUT_PARM1;
		goto LABEL_EXIT;
	}

	if (acc <= 0)
	{
		rtn = ERR_INPUT_PARM2;
		goto LABEL_EXIT;
	}

	// status check
	if (!g_MotionInfo[index].IsOpening || g_MotionInfo[index].IsRunning)
	{
		rtn = ERR_STATUS;
		goto LABEL_EXIT;
	}

	// 0x20
	rtn = TransCommData1(axis, CMD_SET_MAX_ACC_PRFPOS, 0x04, acc);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_SetProfilePositionAcc(%d, %lf)=%d", axis, acc, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_SetProfilePositionVel(short axis, double vel)
{
	short rtn = ERR_NONE;
	short index = AxisID2Index(axis);

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_SetProfilePositionVel(%d, %lf)", axis, vel);

	// input check
	if (-1 == index)
	{
		rtn = ERR_INPUT_PARM1;
		goto LABEL_EXIT;
	}

	if (vel > g_MotionInfo[index].SParm.MaxOutputVel * VELOCITY_RANGE ||
		vel < g_MotionInfo[index].SParm.MinOutputVel * VELOCITY_RANGE ||
		vel <= 0)
	{
		rtn = ERR_INPUT_PARM2;
		goto LABEL_EXIT;
	}

	// status check
	if (!g_MotionInfo[index].IsOpening || g_MotionInfo[index].IsRunning)
	{
		rtn = ERR_STATUS;
		goto LABEL_EXIT;
	}

	// 0x1F
	rtn = TransCommData1(axis, CMD_SET_MAX_VEL_PRFPOS, 0x04, vel);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_SetProfilePositionVel(%d, %lf)=%d", axis, vel, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_SetProfilePositionDec(short axis, double dec)
{
	short rtn = ERR_NONE;
	short index = AxisID2Index(axis);

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_SetProfilePositionDec(%d, %lf)", axis, dec);

	// input check
	if (-1 == index)
	{
		rtn = ERR_INPUT_PARM1;
		goto LABEL_EXIT;
	}

	if (dec >= 0)
	{
		rtn = ERR_INPUT_PARM2;
		goto LABEL_EXIT;
	}

	// status check
	if (!g_MotionInfo[index].IsOpening || g_MotionInfo[index].IsRunning)
	{
		rtn = ERR_STATUS;
		goto LABEL_EXIT;
	}

	// 0x21
	rtn = TransCommData1(axis, CMD_SET_MAX_DEC_PRFPOS, 0x04, dec);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_SetProfilePositionDec(%d, %lf)=%d", axis, dec, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_GetProfilePositionAcc(short axis, double &acc)
{
	int i;
	short rtn = ERR_NONE;
	short index = AxisID2Index(axis);

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_GetProfilePositionAcc(%d, 0x%lf)", axis, acc);

	// input check
	if (-1 == index)
	{
		rtn = ERR_INPUT_PARM1;
		goto LABEL_EXIT;
	}

	acc = 0;

	//status check
	if (!g_MotionInfo[index].IsOpening)
	{
		rtn = ERR_AXIS_IS_CLOSED;
		goto LABEL_EXIT;
	}

	// 0x1D
	rtn = TransCommData1(axis, CMD_GET_MAX_ACC_PRFPOS, 0x00, 0, &acc);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_GetProfilePositionAcc(%d, 0x%lf)=%d", axis, acc, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_GetProfilePositionVel(short axis, double &vel)
{
	int i;
	short rtn = ERR_NONE;
	short index = AxisID2Index(axis);

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_GetProfilePositionVel(%d, 0x%lf)", axis, vel);

	// input check
	if (-1 == index)
	{
		rtn = ERR_INPUT_PARM1;
		goto LABEL_EXIT;
	}

	vel = 0;

	// status check
	if (!g_MotionInfo[index].IsOpening)
	{
		rtn = ERR_AXIS_IS_CLOSED;
		goto LABEL_EXIT;
	}

	// 0x1C
	rtn = TransCommData1(axis, CMD_GET_MAX_VEL_PRFPOS, 0x00, 0, &vel);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_GetProfilePositionVel(%d, 0x%lf)=%d", axis, vel, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_GetProfilePositionDec(short axis, double &dec)
{
	int i;
	short rtn = ERR_NONE;
	short index = AxisID2Index(axis);

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_GetProfilePositionDec(%d, 0x%lf)", axis, dec);

	// input check
	if (-1 == index)
	{
		rtn = ERR_INPUT_PARM1;
		goto LABEL_EXIT;
	}

	dec = 0;

	// status check
	if (!g_MotionInfo[index].IsOpening)
	{
		rtn = ERR_AXIS_IS_CLOSED;
		goto LABEL_EXIT;
	}

	// 0x1E
	rtn = TransCommData1(axis, CMD_GET_MAX_DEC_PRFPOS, 0x00, 1, &dec);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_GetProfilePositionDec(%d, 0x%lf)=%d", axis, dec, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_SetPosition(short axis, double pos)
{
	// if not open, return err
	short rtn = ERR_NONE;
	long value;
	CommunicationData CommData;
	short ip;
	EcuRelatedInfo *p = NULL;
	short index = AxisID2Index(axis);

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_SetPosition(%d, double(%.2lf))", axis, pos);

	// input check
	if (-1 == index)
	{
		rtn = ERR_INPUT_PARM1;
		goto LABEL_EXIT;
	}

	ip = g_MotionInfo[index].IP;
	p = &g_ecuRelatedInfo[ip];

	// Notes: 当前暂时屏蔽这个判断，init时已经打开了Axis的限位开关
	// // pos is incorrect
	// if (PositionIsIncorrect(index, pos))
	// {
	// 	rtn = ERR_AXIS_POSITION_IS_INCORRECT;
	// 	goto LABEL_EXIT;
	// }

	// status check

	if (!g_MotionInfo[index].IsOpening)
	{
		rtn = ERR_AXIS_IS_CLOSED;
		goto LABEL_EXIT;
	}
	if (!g_MotionInfo[index].LimitStatus)
	{
		rtn = ERR_AXIS_LIMIT_STATUS_IS_FALSE;
		goto LABEL_EXIT;
	}
	if (g_MotionInfo[index].MotionMode != POSITION_MODE &&
		g_MotionInfo[index].MotionMode != PROFILE_POSITION_MODE)
	{
		rtn = ERR_AXIS_ISNOT_POSITION_MODE;
		goto LABEL_EXIT;
	}

	// thread lock
	pthread_mutex_lock(&p->mutexLock);

	// 0x0A
	memset(&CommData, 0, sizeof(CommunicationData));
	CommData.SendAxis = (unsigned char)axis;
	CommData.SendCmd = CMD_SET_PROFILE_POSITION;
	CommData.SendDataLen = 0x04;
	Double2Fix(&CommData, pos);
	//CRC16_1(&CommData.SendData[0], (short)CommData.SendDataLen, CommData.SendCrc);

	rtn = CommSend(&CommData);
	if (rtn != 0)
	{
		// thread unlock
		pthread_mutex_unlock(&p->mutexLock);
		goto LABEL_EXIT;
	}

	// tbd: for test 暂时不考虑返回
	// // finger actuator temporary solution
	// if (IsFingerActuator(axis))
	// {
	// 	rtn = CommRtn(&CommData);
	// 	if (rtn != 0)
	// 	{
	// 		// thread unlock
	// 		pthread_mutex_unlock(&p->mutexLock);
	// 		goto LABEL_EXIT;
	// 	}
	// }

	// 赋值
	g_MotionInfo[index].LastPos = pos;

	// thread unlock
	pthread_mutex_unlock(&p->mutexLock);

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_SetPosition(%d, double(%.2lf))=%d", axis, pos, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_SetPosition(vector<short> axis, vector<double> pos)
{
	short rtn = ERR_NONE;
	int i = 0;
	short index;
	const int SendAxisLen = 12; // 发送一个Axis包的长度
	unsigned char sendBuff[SendAxisLen * AXIS_COUNT];
	int sendLength = 0;
	short ip;
	EcuRelatedInfo *p = NULL;
	int count = axis.size();
	int recvCount = 0;
	CommunicationData CommData;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_SetPosition(vector, vector)");

	if ((count <= 0) || (count != pos.size()))
	{
		rtn = ERR_INPUT_PARM;
		goto LABEL_EXIT;
	}

	// Note:
	// 1) 组发送只对应单个ECU下的axis组
	// 2) 只有IsFingerActuator的Axis才有接收返回

	// 打包数据
	for (i = 0; i < count; i++)
	{
		index = AxisID2Index(axis.at(i));
		if (-1 == index)
		{
			rtn = ERR_AXIS_NO_FOUND;
			goto LABEL_EXIT;
		}

		//
		// 当前轴有问题，则跳过去

		// status check
		if (!g_MotionInfo[index].IsOpening)
		{
			// rtn = ERR_AXIS_IS_CLOSED;
			// goto LABEL_EXIT;
			continue;
		}

		if (!g_MotionInfo[index].LimitStatus)
		{
			// rtn = ERR_AXIS_LIMIT_STATUS_IS_FALSE;
			// goto LABEL_EXIT;
			continue;
		}

		if (g_MotionInfo[index].MotionMode != POSITION_MODE &&
			g_MotionInfo[index].MotionMode != PROFILE_POSITION_MODE)
		{
			// rtn = ERR_AXIS_ISNOT_POSITION_MODE;
			// goto LABEL_EXIT;
			continue;
		}

		// Notes: 当前暂时屏蔽这个判断，init时已经打开了Axis的限位开关
		// // pos is incorrect
		// if (PositionIsIncorrect(index, pos.at(i)))
		// {
		// 	// rtn = ERR_AXIS_POSITION_IS_INCORRECT;
		// 	// goto LABEL_EXIT;
		// 	continue;
		// }

		memset(&CommData, 0, sizeof(CommunicationData));
		CommData.SendAxis = (unsigned char)axis.at(i);
		CommData.SendCmd = CMD_SET_PROFILE_POSITION;
		CommData.SendDataLen = 0x04;
		Double2Fix(&CommData, pos.at(i));
		//CRC16_1(&CommData.SendData[0], (short)CommData.SendDataLen, CommData.SendCrc);
		PackageCommSendData(&CommData);

		memcpy(sendBuff + i * CommData.SendCharLen, CommData.SendChar, CommData.SendCharLen);
		sendLength += CommData.SendCharLen;

		// // tbd: for test 都不考虑返回
		// if (IsFingerActuator(axis.at(i)))
		// {
		// 	recvCount++;
		// }
	}

	// 当前组没有需要发送的信息
	if (sendLength <= 0)
	{
		goto LABEL_EXIT;
	}

	// 发送打包的数据
	ip = g_MotionInfo[AxisID2Index(axis.at(0))].IP;
	rtn = SendAndRecvPackData(ip, sendBuff, sendLength, recvCount);
	if (rtn != ERR_NONE)
	{
		goto LABEL_EXIT;
	}

	// 赋值
	for (i = 0; i < count; i++)
	{
		index = AxisID2Index(axis.at(i));
		g_MotionInfo[index].LastPos = pos.at(i);
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_SetPosition(vector, vector)=%d", rtn);
	return rtn;
}

short CM_SCA_Controller::CM_SetPosition(short axis, long pos)
{
	short rtn = ERR_NONE;
	double value;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_SetPosition(%d, long(%lf))", axis, pos);

	value = ((double)pos / (double)CM_SCA_PULSE_NUM);
	rtn = CM_SetPosition(axis, value);

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_SetPosition(%d, long(%lf))=%d", axis, pos, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_AxisTrapMotion(short axis, double pos, long t)
{
	short rtn = ERR_NONE;
	vector<short> axisID;
	vector<double> position;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_AxisTrapMotion(%d, double(%lf), long(%lf))", axis, pos, t);

	axisID.push_back(axis);
	position.push_back(pos);
	rtn = CM_SynMultiAxisMotion(axisID, position, t);

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_AxisTrapMotion(%d, double(%lf), long(%lf))=%d", axis, pos, t, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_AxisTrapMotion(short axis, long pos, long t)
{
	short rtn = ERR_NONE;
	vector<short> axisID;
	vector<long> position;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_AxisTrapMotion(%d, long(%lf), long(%lf))", axis, pos, t);

	axisID.push_back(axis);
	position.push_back(pos);
	rtn = CM_SynMultiAxisMotion(axisID, position, t);

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_AxisTrapMotion(%d, long(%lf), long(%lf))=%d", axis, pos, t, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_SynMultiAxisMotion(vector<short> axis, vector<double> pos, long t)
{
	int i;
	short rtn = ERR_NONE;
	short AxisNum;
	long value;
	long minTime = 4;
	double VelStageProp = 0.5;
	double AccStageProp = 0.25;
	double MaxDistance;
	double TempVel;
	double TempAcc;
	vector<double> CunnrentPos;
	vector<double> distance;
	vector<double> acc; //acc=dec
	vector<double> vel;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_SynMultiAxisMotion(0x%lf, 0x%lf, long(%lf))", axis, pos, t);

	// input check
	if (0 == axis.size())
	{
		rtn = ERR_INPUT_PARM1;
		goto LABEL_EXIT;
	}
	if (axis.size() != pos.size())
	{
		rtn = ERR_INPUT_PARM2;
		goto LABEL_EXIT;
	}
	if (t < minTime)
	{
		rtn = ERR_INPUT_PARM3;
		goto LABEL_EXIT;
	}

	AxisNum = axis.size();
	CunnrentPos.resize(AxisNum);
	distance.resize(AxisNum);
	acc.resize(AxisNum);
	vel.resize(AxisNum);
	for (i = 0; i < AxisNum; i++)
	{
		rtn = AxisID2Index(axis.at(i));
		if (-1 == rtn)
		{
			rtn = ERR_AXIS_NO_FOUND;
			goto LABEL_EXIT;
		}
	}

	// status check
	for (i = 0; i < AxisNum; i++)
	{
		if (!g_MotionInfo[AxisID2Index(axis.at(i))].IsOpening ||
			g_MotionInfo[AxisID2Index(axis.at(i))].IsRunning ||
			!g_MotionInfo[AxisID2Index(axis.at(i))].LimitStatus)
		{
			rtn = ERR_STATUS;
			goto LABEL_EXIT;
		}

		//if not position mode, return err
		rtn = CM_GetProfileMode(axis.at(i), value);
		if (0 != rtn)
		{
			goto LABEL_EXIT;
		}
		if (6 != value)
		{
			rtn = ERR_AXIS_MODE_IS_INCORRECT;
			goto LABEL_EXIT;
		}
	}

	// current pos and distance
	for (i = 0; i < AxisNum; i++)
	{
		CM_GetProfilePosition(axis.at(i), CunnrentPos.at(i));
		distance.at(i) = fabs(pos.at(i) - CunnrentPos.at(i));
	}

	// find max distance
	MaxDistance = distance.at(0);
	for (i = 0; i < AxisNum; i++)
	{
		if (distance.at(i) > MaxDistance)
		{
			MaxDistance = distance.at(i);
		}
	}

	//defalut: 0.25t->acc, 0.5t->vel, 0.25t->dec
	//max_vel = 5*1200, max_acc = 2*1200
	//vel*(0.75t)=dist
	TempVel = MaxDistance / ((VelStageProp + AccStageProp) * double(t) / 60000);
	while (TempVel > VELOCITY_RANGE && VelStageProp <= 1.0)
	{
		VelStageProp += 0.05;
		AccStageProp = (1.0 - VelStageProp) / 2;
		TempVel = MaxDistance / ((VelStageProp + AccStageProp) * double(t) / 60000);
	}
	if (VelStageProp >= 0.8)
	{
		rtn = ERR_VEL_STAGE_PROP;
		goto LABEL_EXIT;
	}
	//a*(accProp*t)^2 + a*(accProp*t)*velProp*t=dist, a: rpm/s
	TempAcc = MaxDistance / (AccStageProp * (double(t) / 60000) * (double(t) / 60000) * (AccStageProp + VelStageProp)) / 60;
	if (TempAcc > 2400 && AccStageProp < 0.25)
	{
		rtn = ERR_ACC_STAGE_PROP;
		goto LABEL_EXIT;
	}
	while (TempAcc > 2400 && AccStageProp <= 1.0)
	{
		AccStageProp += 0.05;
		VelStageProp = 1.0 - 2 * AccStageProp;
		TempAcc = MaxDistance / (AccStageProp * (double(t) / 60000) * (double(t) / 60000) * (AccStageProp + VelStageProp)) / 60;
	}
	TempVel = MaxDistance / ((VelStageProp + AccStageProp) * double(t) / 60000);
	if (AccStageProp > 0.5 || TempVel > VELOCITY_RANGE || TempVel <= 0 || TempAcc <= 0)
	{
		rtn = ERR_ACC_STAGE_PROP;
		goto LABEL_EXIT;
	}

	for (i = 0; i < AxisNum; i++)
	{
		vel.at(i) = distance.at(i) / (VelStageProp * double(t) / 60000); //t: ms
		rtn = CM_SetProfilePositionVel(axis.at(i), fabs(vel.at(i)));
		if (0 != rtn)
		{
			goto LABEL_EXIT;
		}
		acc.at(i) = vel.at(i) / (AccStageProp * double(t) / 1000.0);
		rtn = CM_SetProfilePositionAcc(axis.at(i), fabs(acc.at(i)));
		if (0 != rtn)
		{
			goto LABEL_EXIT;
		}
		rtn = CM_SetProfilePositionDec(axis.at(i), -fabs(acc.at(i)));
		if (0 != rtn)
		{
			goto LABEL_EXIT;
		}
	}

	for (i = 0; i < AxisNum; i++)
	{
		CM_SetPosition(axis.at(i), pos.at(i));
		g_MotionInfo[AxisID2Index(axis.at(i))].LastPos = pos.at(i);
	}

	rtn = 0;

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_SynMultiAxisMotion(0x%lf, 0x%lf, long(%lf))=%d", axis, pos, t, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_SynMultiAxisMotion(vector<short> axis, vector<long> pos, long t)
{
	int i;
	int num;
	short rtn = ERR_NONE;
	vector<double> dPos;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_SynMultiAxisMotion(0x%lf, 0x%lf, long(%lf))", axis, pos, t);

	num = axis.size();
	dPos.resize(num);
	for (i = 0; i < num; i++)
	{
		dPos.at(i) = ((double)pos.at(i) / (double)CM_SCA_PULSE_NUM);
	}

	rtn = CM_SynMultiAxisMotion(axis, dPos, t);

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_SynMultiAxisMotion(0x%lf, 0x%lf, long(%lf))=%d", axis, pos, t, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_SetVelocityMode(short axis)
{
	//if not open, return err
	short rtn = ERR_NONE;
	short index = AxisID2Index(axis);

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_SetVelocityMode(%d)", axis);

	//input check
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

	//0X07
	rtn = TransCommData(axis, CMD_SET_ACTUATIR_MODE, 0x01, VELLOCITY_MODE);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	//set global variables
	g_MotionInfo[index].MotionMode = VELLOCITY_MODE;

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_SetVelocityMode(%d)=%d", axis, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_SetProfileVelocityMode(short axis)
{
	//if not open, return err
	short rtn = ERR_NONE;
	short index = AxisID2Index(axis);

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_SetProfileVelocityMode(%d)", axis);

	// input check
	if (-1 == index)
	{
		rtn = ERR_AXIS_NO_FOUND;
		goto LABEL_EXIT;
	}

	// status check
	if (!g_MotionInfo[index].IsOpening || g_MotionInfo[index].IsRunning)
	{
		rtn = ERR_STATUS;
		goto LABEL_EXIT;
	}

	// 0x07
	rtn = TransCommData(axis, CMD_SET_ACTUATIR_MODE, 0x01, PROFILE_VELOCITY_MODE);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	//set global variables
	g_MotionInfo[index].MotionMode = PROFILE_VELOCITY_MODE;

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_SetProfileVelocityMode(%d)=%d", axis, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_SetProfileVelocityAcc(short axis, double acc)
{
	short rtn = ERR_NONE;
	short index = AxisID2Index(axis);

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_SetProfileVelocityAcc(%d, %lf)", axis, acc);

	// input check
	if (-1 == index)
	{
		rtn = ERR_AXIS_NO_FOUND;
		goto LABEL_EXIT;
	}

	if (acc <= 0)
	{
		rtn = ERR_INPUT_PARM2;
		goto LABEL_EXIT;
	}

	// status check
	if (!g_MotionInfo[index].IsOpening || g_MotionInfo[index].IsRunning)
	{
		rtn = ERR_STATUS;
		goto LABEL_EXIT;
	}

	// 0x26
	rtn = TransCommData1(axis, CMD_SET_MAX_ACC_PRFVEL, 0x04, acc);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_SetProfileVelocityAcc(%d, %lf)=%d", axis, acc, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_SetProfileVelocityVel(short axis, double vel)
{
	short rtn = ERR_NONE;
	short index = AxisID2Index(axis);

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_SetProfileVelocityVel(%d, %lf)", axis, vel);

	// input check
	if (-1 == index)
	{
		rtn = ERR_AXIS_NO_FOUND;
		goto LABEL_EXIT;
	}

	if (vel > g_MotionInfo[index].SParm.MaxOutputVel * VELOCITY_RANGE ||
		vel < g_MotionInfo[index].SParm.MinOutputVel * VELOCITY_RANGE ||
		vel <= 0)
	{
		rtn = ERR_INPUT_PARM2;
		goto LABEL_EXIT;
	}

	// status check
	if (!g_MotionInfo[index].IsOpening || g_MotionInfo[index].IsRunning)
	{
		rtn = ERR_STATUS;
		goto LABEL_EXIT;
	}

	// 0x25
	rtn = TransCommData1(axis, CMD_SET_MAX_VEL_PRFVEL, 0x04, vel);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_SetProfileVelocityVel(%d, %lf)=%d", axis, vel, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_SetProfileVelocityDec(short axis, double dec)
{
	short rtn = ERR_NONE;
	short index = AxisID2Index(axis);

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_SetProfileVelocityDec(%d, %lf)", axis, dec);

	// input check
	if (-1 == index)
	{
		rtn = ERR_AXIS_NO_FOUND;
		goto LABEL_EXIT;
	}

	if (dec >= 0)
	{
		rtn = ERR_INPUT_PARM2;
		goto LABEL_EXIT;
	}

	// status check
	if (!g_MotionInfo[index].IsOpening || g_MotionInfo[index].IsRunning)
	{
		rtn = ERR_STATUS;
		goto LABEL_EXIT;
	}

	// 0x27
	rtn = TransCommData1(axis, CMD_SET_MAX_DEC_PRFVEL, 0x04, dec);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_SetProfileVelocityDec(%d, %lf)=%d", axis, dec, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_GetProfileVelocityAcc(short axis, double &acc)
{
	short rtn = ERR_NONE;
	short index = AxisID2Index(axis);

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_GetProfileVelocityAcc(%d, 0x%lf)", axis, acc);

	// input check
	if (-1 == index)
	{
		rtn = ERR_AXIS_NO_FOUND;
		goto LABEL_EXIT;
	}

	acc = 0;

	// status check
	if (!g_MotionInfo[index].IsOpening)
	{
		rtn = ERR_AXIS_IS_CLOSED;
		goto LABEL_EXIT;
	}

	// 0x23
	rtn = TransCommData1(axis, CMD_GET_MAX_ACC_PRFVEL, 0x00, 0, &acc);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_SetProfileVelocityDec(%d, 0x%lf)=%d", axis, acc, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_GetProfileVelocityVel(short axis, double &vel)
{
	short rtn = ERR_NONE;
	short index = AxisID2Index(axis);

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_GetProfileVelocityVel(%d, 0x%lf)", axis, vel);

	// input check
	if (-1 == index)
	{
		rtn = ERR_AXIS_NO_FOUND;
		goto LABEL_EXIT;
	}

	vel = 0;

	// status check
	if (!g_MotionInfo[index].IsOpening)
	{
		rtn = ERR_AXIS_IS_CLOSED;
		goto LABEL_EXIT;
	}

	// 0x22
	rtn = TransCommData1(axis, CMD_GET_MAX_VEL_PRFVEL, 0x00, 0, &vel);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_GetProfileVelocityVel(%d, 0x%lf)=%d", axis, vel, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_GetProfileVelocityDec(short axis, double &dec)
{
	short rtn = ERR_NONE;
	short index = AxisID2Index(axis);

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_GetProfileVelocityDec(%d, 0x%lf)", axis, dec);

	// input check
	if (-1 == index)
	{
		rtn = ERR_AXIS_NO_FOUND;
		goto LABEL_EXIT;
	}

	dec = 0;

	// status check
	if (!g_MotionInfo[index].IsOpening)
	{
		rtn = ERR_AXIS_IS_CLOSED;
		goto LABEL_EXIT;
	}

	// 0x24
	rtn = TransCommData1(axis, CMD_GET_MAX_DEC_PRFVEL, 0x00, 1, &dec);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_GetProfileVelocityDec(%d, 0x%lf)=%d", axis, dec, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_SetVelocity(short axis, double vel)
{
	short rtn = ERR_NONE;
	long value;
	CommunicationData CommData;
	short ip;
	EcuRelatedInfo *p = NULL;
	short index = AxisID2Index(axis);

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_SetVelocity(%d, %lf)", axis, vel);

	// input check
	if (-1 == index)
	{
		rtn = ERR_AXIS_NO_FOUND;
		goto LABEL_EXIT;
	}

	ip = g_MotionInfo[index].IP;
	p = &g_ecuRelatedInfo[ip];

	if (vel > (g_MotionInfo[index].SParm.MaxOutputVel) * VELOCITY_RANGE ||
		vel < (g_MotionInfo[index].SParm.MinOutputVel) * VELOCITY_RANGE)
	{
		rtn = ERR_INPUT_PARM2;
		goto LABEL_EXIT;
	}

	//status check
	if (!g_MotionInfo[index].IsOpening)
	{
		rtn = ERR_AXIS_IS_CLOSED;
		goto LABEL_EXIT;
	}
	if (g_MotionInfo[index].MotionMode != VELLOCITY_MODE &&
		g_MotionInfo[index].MotionMode != PROFILE_VELOCITY_MODE)
	{
		rtn = ERR_AXIS_ISNOT_VELLOCITY_MODE;
		goto LABEL_EXIT;
	}

	//thread lock
	pthread_mutex_lock(&p->mutexLock);

	//0X09
	memset(&CommData, 0, sizeof(CommunicationData));
	CommData.SendAxis = (unsigned char)axis;
	CommData.SendCmd = CMD_SET_PROFILE_VELOCITY;
	CommData.SendDataLen = 0x04;
	vel /= VELOCITY_RANGE;
	Double2Fix(&CommData, vel);
	//(&CommData.SendData[0], (short)CommData.SendDataLen, CommData.SendCrc);

	rtn = CommSend(&CommData);
	if (rtn != 0)
	{
		pthread_mutex_unlock(&p->mutexLock);
		goto LABEL_EXIT;
	}

	if (IsFingerActuator(axis))
	{
		rtn = CommRtn(&CommData);
		if (rtn != 0)
		{
			pthread_mutex_unlock(&p->mutexLock);
			goto LABEL_EXIT;
		}
	}
	g_MotionInfo[index].LastVel = vel * VELOCITY_RANGE;

	//thread unlock
	pthread_mutex_unlock(&p->mutexLock);

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_SetVelocity(%d, %lf)=%d", axis, vel, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_SetVelocity(vector<short> axis, vector<double> vel)
{
	short rtn = ERR_NONE;
	int i = 0;
	short index;
	const int SendAxisLen = 12; // position发送一个Axis包的长度
	unsigned char sendBuff[SendAxisLen * AXIS_COUNT];
	int sendLength = 0;
	short ip;
	EcuRelatedInfo *p = NULL;
	int count = axis.size();
	int recvCount = 0;
	CommunicationData CommData;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_SetVelocity(0x%lf, 0x%lf)", axis, vel);

	if ((count <= 0) || (count != vel.size()))
	{
		rtn = ERR_INPUT_PARM;
		goto LABEL_EXIT;
	}

	// Note:
	// 1) 组发送只对应单个ECU下的axis组
	// 2) IsFingerActuator才有Recv返回

	// 打包数据
	for (i = 0; i < count; i++)
	{
		index = AxisID2Index(axis.at(i));
		if (-1 == index)
		{
			rtn = ERR_AXIS_NO_FOUND;
			goto LABEL_EXIT;
		}

		// status check
		if (!g_MotionInfo[index].IsOpening)
		{
			rtn = ERR_AXIS_IS_CLOSED;
			goto LABEL_EXIT;
		}
		if (g_MotionInfo[index].MotionMode != VELLOCITY_MODE &&
			g_MotionInfo[index].MotionMode != PROFILE_VELOCITY_MODE)
		{
			rtn = ERR_AXIS_ISNOT_VELLOCITY_MODE;
			goto LABEL_EXIT;
		}

		// vel is right
		if (vel.at(i) > (g_MotionInfo[index].SParm.MaxOutputVel) * VELOCITY_RANGE ||
			vel.at(i) < (g_MotionInfo[index].SParm.MinOutputVel) * VELOCITY_RANGE)
		{
			rtn = ERR_AXIS_VELLOCITY_IS_INCORRECT;
			goto LABEL_EXIT;
		}

		vel.at(i) /= VELOCITY_RANGE;

		memset(&CommData, 0, sizeof(CommunicationData));
		CommData.SendAxis = (unsigned char)axis.at(i);
		CommData.SendCmd = CMD_SET_PROFILE_VELOCITY;
		CommData.SendDataLen = 0x04;
		Double2Fix(&CommData, vel.at(i));
		//CRC16_1(&CommData.SendData[0], (short)CommData.SendDataLen, CommData.SendCrc);
		PackageCommSendData(&CommData);

		memcpy(sendBuff + i * CommData.SendCharLen, CommData.SendChar, CommData.SendCharLen);
		sendLength += CommData.SendCharLen;

		// // tbd: for test 都不考虑返回
		// if (IsFingerActuator(axis.at(i)))
		// {
		// 	recvCount++;
		// }
	}

	// 发送和接收打包数据
	ip = g_MotionInfo[AxisID2Index(axis.at(0))].IP;
	rtn = SendAndRecvPackData(ip, sendBuff, sendLength, recvCount);
	if (rtn != ERR_NONE)
	{
		goto LABEL_EXIT;
	}

	// 赋值
	for (i = 0; i < count; i++)
	{
		index = AxisID2Index(axis.at(i));
		g_MotionInfo[index].LastVel = vel.at(i) * VELOCITY_RANGE;
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_SetVelocity(0x%lf, 0x%lf)=%d", axis, vel, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_SetVelocity(short axis, long vel)
{
	short rtn = ERR_NONE;
	double value;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_SetVelocity(%d, long(%lf))", axis, vel);

	value = 60000 * ((double)vel / (double)CM_SCA_PULSE_NUM);
	rtn = CM_SetVelocity(axis, value);

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_SetVelocity(%d, long(%lf))=%d", axis, vel, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_SetCurrentMode(short axis)
{
	short rtn = ERR_NONE;
	long value;
	short index = AxisID2Index(axis);

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_SetCurrentMode(%d)", axis);

	// input check
	if (-1 == index)
	{
		rtn = ERR_AXIS_NO_FOUND;
		goto LABEL_EXIT;
	}

	// status check
	if (!g_MotionInfo[index].IsOpening || g_MotionInfo[index].IsRunning)
	{
		rtn = ERR_STATUS;
		goto LABEL_EXIT;
	}

	// 0x07
	rtn = TransCommData(axis, CMD_SET_ACTUATIR_MODE, 0x01, CURRENT_MODE);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	// set global variables
	g_MotionInfo[AxisID2Index(axis)].MotionMode = CURRENT_MODE;

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_SetCurrentMode(%d)", axis);
	return rtn;
}

short CM_SCA_Controller::CM_SetCurrent(short axis, double cur)
{
	short rtn = ERR_NONE;
	long value;
	CommunicationData CommData;
	short ip;
	double CurrentPos_,CurrentVel_,CurrentCur_;
	double NSoftLimit_, PSoftLimit_;
	EcuRelatedInfo *p = NULL;
	short index = AxisID2Index(axis);

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_SetCurrent(%d, double(%lf))", axis, cur);

	// input check
	if (-1 == index)
	{
		rtn = ERR_AXIS_NO_FOUND;
		goto LABEL_EXIT;
	}

	// Notes: cur底层会有保护，因为每个Axis的电流范围不一样，所以不做判断

	ip = g_MotionInfo[index].IP;
	p = &g_ecuRelatedInfo[ip];

	// status check
	if (!g_MotionInfo[index].IsOpening)
	{
		rtn = ERR_AXIS_IS_CLOSED;
		goto LABEL_EXIT;
	}
	if (g_MotionInfo[index].MotionMode != CURRENT_MODE)
	{
		rtn = ERR_AXIS_ISNOT_CURRENT_MODE;
		goto LABEL_EXIT;
	}

    // rtn=CM_GetProfilePVC(axis,CurrentPos_,CurrentVel_,CurrentCur_);
	// {if (rtn !=0)
	// {cout << "get the pvc failed  = "<< axis << endl; 
	// goto LABEL_EXIT;}}
	// rtn=CM_GetSoftLimitValue(axis,NSoftLimit_, PSoftLimit_);
	// {if (rtn !=0)
	// {cout << "get the softlimit failed  "<< endl; 
	// goto LABEL_EXIT;}}
	// if(CurrentPos_<=NSoftLimit_ || CurrentPos_>=PSoftLimit_)
	// {
	// 	rtn = CM_SetPositionMode(axis);
	// 	cout << "the current position is out of  softlimit ,set current value failed  "<< endl; 
	// 	goto LABEL_EXIT;
	// }
	//thread lock
	pthread_mutex_lock(&p->mutexLock);

	// 0x08
	memset(&CommData, 0, sizeof(CommunicationData));
	CommData.SendAxis = (unsigned char)axis;
	CommData.SendCmd = CMD_SET_PROFILE_CURRENT;
	CommData.SendDataLen = 0x04;
	//cout << "CurrentRange "<<g_MotionInfo[index].CurrentRange<< endl;
	//cur /= g_MotionInfo[index].CurrentRange;
	Double2Fix(&CommData, cur);
	//CRC16_1(&CommData.SendData[0], (short)CommData.SendDataLen, CommData.SendCrc);

	rtn = CommSend(&CommData);
	if (rtn != 0)
	{
		pthread_mutex_unlock(&p->mutexLock);
		goto LABEL_EXIT;
	}

	{
		rtn = CommRtn(&CommData);
		if (rtn != 0)
		{
			pthread_mutex_unlock(&p->mutexLock);
			goto LABEL_EXIT;
		}
	}

	g_MotionInfo[index].LastCur = cur * g_MotionInfo[index].CurrentRange;

	// thread unlock
	pthread_mutex_unlock(&p->mutexLock);

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_SetCurrent(%d, double(%lf))=%d", axis, cur, rtn);
	return ERR_NONE;
}

short CM_SCA_Controller::CM_SetCurrent(vector<short> axis, vector<double> cur)
{
	short rtn = ERR_NONE;
	int i = 0;
	short index;
	const int SendAxisLen = 12; // position发送一个Axis包的长度
	unsigned char sendBuff[SendAxisLen * AXIS_COUNT];
	int sendLength = 0;
	short ip;
	EcuRelatedInfo *p = NULL;
	int count = axis.size();
	int recvCount = 0;
	CommunicationData CommData;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_SetCurrent(0x%lf, 0x%lf)", axis, cur);

	if ((count <= 0) || (count != cur.size()))
	{
		rtn = ERR_INPUT_PARM;
		goto LABEL_EXIT;
	}

	// Note:
	// 1) 组发送只对应单个ECU下的axis组
	// 2) IsFingerActuator才有Recv返回

	// 打包数据
	for (i = 0; i < count; i++)
	{
		index = AxisID2Index(axis.at(i));
		if (-1 == index)
		{
			rtn = ERR_AXIS_NO_FOUND;
			goto LABEL_EXIT;
		}

		// status check
		if (!g_MotionInfo[index].IsOpening)
		{
			rtn = ERR_AXIS_IS_CLOSED;
			goto LABEL_EXIT;
		}
		if (g_MotionInfo[index].MotionMode != CURRENT_MODE)
		{
			rtn = ERR_AXIS_ISNOT_CURRENT_MODE;
			goto LABEL_EXIT;
		}

		cur.at(i) /= g_MotionInfo[index].CurrentRange;

		memset(&CommData, 0, sizeof(CommunicationData));
		CommData.SendAxis = (unsigned char)axis.at(i);
		CommData.SendCmd = CMD_SET_PROFILE_VELOCITY;
		CommData.SendDataLen = 0x04;
		Double2Fix(&CommData, cur.at(i));
		//CRC16_1(&CommData.SendData[0], (short)CommData.SendDataLen, CommData.SendCrc);
		PackageCommSendData(&CommData);

		memcpy(sendBuff + i * CommData.SendCharLen, CommData.SendChar, CommData.SendCharLen);
		sendLength += CommData.SendCharLen;

		// // tbd: for test 都不考虑返回
		// if (IsFingerActuator(axis.at(i)))
		// {
		// 	recvCount++;
		// }
	}

	// 发送和接收打包数据
	ip = g_MotionInfo[AxisID2Index(axis.at(0))].IP;
	rtn = SendAndRecvPackData(ip, sendBuff, sendLength, recvCount);
	if (rtn != ERR_NONE)
	{
		return rtn;
	}

	// 赋值
	for (i = 0; i < count; i++)
	{
		index = AxisID2Index(axis.at(i));
		g_MotionInfo[index].LastCur = cur.at(i) * g_MotionInfo[index].CurrentRange;
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_SetCurrent(0x%lf, 0x%lf)", axis, cur);
	return rtn;
}

short CM_SCA_Controller::CM_SetHomingMode(short axis, int operateMode)
{
	short rtn = ERR_NONE;
	//long value;
	short index = AxisID2Index(axis);

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_SetHomingMode(%d, %d)", axis, operateMode);

	// input check
	if (-1 == index)
	{
		rtn = ERR_AXIS_NO_FOUND;
		goto LABEL_EXIT;
	}

	if (operateMode != 1 && operateMode != 2)
	{
		rtn = ERR_INPUT_PARM2;
		goto LABEL_EXIT;
	}

	// status check
	if (!g_MotionInfo[index].IsOpening || g_MotionInfo[index].IsRunning)
	{
		rtn = ERR_STATUS;
		goto LABEL_EXIT;
	}

	// 0x07
	rtn = TransCommData(axis, CMD_SET_ACTUATIR_MODE, 0x01, HOMING_MODE);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	// 设置Homing的操作模式：01为手动，02为自动
	rtn = TransCommData(axis, CMD_SET_HOMING_OPERATE_MODE, 0x01, operateMode);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	// set global variables
	g_MotionInfo[index].MotionMode = HOMING_MODE;
	cout<< "the homing sca id is"<<g_MotionInfo[index].ID<<endl;
LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_SetHomingMode(%d, %d)=%d", axis, operateMode, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_SetPositionTimeMode(short axis, short mode)
{
	return ERR_EXECT;
}

short CM_SCA_Controller::CM_GetPositionTimeSpace(short axis, short &Space, short fifo)
{
	return ERR_EXECT;
}

short CM_SCA_Controller::CM_PositionTimeData(short axis, double pos, long time, short type, short fifo)
{
	return ERR_EXECT;
}

short CM_SCA_Controller::CM_PositionTimeClear(short axis, short fifo)
{
	return ERR_EXECT;
}

short CM_SCA_Controller::CM_SetPositionTimeLoop(short axis, long loop)
{
	return ERR_EXECT;
}

short CM_SCA_Controller::CM_GetPositionTimeLoop(short axis, long &Loop)
{
	return ERR_EXECT;
}

short CM_SCA_Controller::CM_PositionTimeStart(long mask, long option)
{
	return ERR_EXECT;
}

short CM_SCA_Controller::CM_SetPositionTimeMemory(short axis, short memory)
{
	return ERR_EXECT;
}

short CM_SCA_Controller::CM_GetPositionTimeMemory(short axis, short &Memory)
{
	return ERR_EXECT;
}

short CM_SCA_Controller::CM_GetStatus(short axis, long &sts)
{
	int i;
	short rtn = ERR_NONE;
	bool status;
	double data;
	CommunicationData CommData;
	short index = AxisID2Index(axis);
	sts = 0;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_GetStatus(%d)", axis);

	// input check
	if (-1 == index)
	{
		rtn = ERR_AXIS_NO_FOUND;
		goto LABEL_EXIT;
	}

	// conect
	rtn = TransCommData(axis, CMD_COMMUNICATION_HANDSHAKE, 0x00, &data);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}
	status = (bool)data;

	// thread unlock
	if (status)
	{
		sts = AXIS_CONNECT;
	}
	else
	{
		sts = AXIS_OFFLINE;
	}

	// open
	rtn = TransCommData(axis, CMD_GET_ACTUATOR_ONOFF_STATUS, 0x00, &data);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}
	status = (bool)data;
	if (status)
	{
		sts = AXIS_OPEN;
	}
	else
	{
		rtn = ERR_NONE;
		goto LABEL_EXIT;
	}

	// running
	if (g_MotionInfo[index].IsRunning)
	{
		sts = AXIS_RUNNING;
	}

	// err 0xFF
	memset(&CommData, 0, sizeof(CommunicationData));
	CommData.SendAxis = (unsigned char)axis;
	CommData.SendCmd = CMD_GET_ERROR_CODE;
	CommData.SendDataLen = 0x00;
	rtn = CommProsses(&CommData);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	if (CommData.RtnData[1] == axis)
	{
		sts = AXIS_ALARM;
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_GetStatus(%d)=%d", axis, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_GetAlarmInfo(short axis, long &AlarmInfo)
{
	short rtn = ERR_NONE;
	double val;
	CommunicationData CommData;
	short index = AxisID2Index(axis);

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_GetAlarmInfo(%d, 0x%lf)", axis, AlarmInfo);

	// input check
	if (-1 == index)
	{
		rtn = ERR_AXIS_NO_FOUND;
		goto LABEL_EXIT;
	}

	AlarmInfo = 0;

	// 0xFF
	memset(&CommData, 0, sizeof(CommunicationData));
	CommData.SendAxis = (char)axis;
	CommData.SendCmd = CMD_GET_ERROR_CODE;
	CommData.SendDataLen = 0x00;
	rtn = CommProsses(&CommData);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	if (CommData.RtnData[1] != 0)
	{
		AlarmInfo = (long)CommData.RtnData[1];
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_GetAlarmInfo(%d, 0x%lf)=%d", axis, AlarmInfo, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_ClearAlarm(short axis)
{
	short rtn = ERR_NONE;
	long sts;
	CommunicationData CommData;
	short ip;
	EcuRelatedInfo *p = NULL;
	short index = AxisID2Index(axis);
	unsigned char senddata[] = {0xEE, 0xaa, CMD_CLEAR_ERROR_STATUS, 0x00,  0x00, 0xED};

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_ClearAlarm(%d,)", axis);

	// input check
	if (-1 == index)
	{
		rtn = ERR_AXIS_NO_FOUND;
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

	rtn = CM_GetStatus(axis, sts);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	if (AXIS_ALARM != sts)
	{
		rtn = ALERT_STATUS;
		goto LABEL_EXIT;
	}

	//thread lock
	pthread_mutex_lock(&p->mutexLock);

	memset(&CommData, 0, sizeof(CommunicationData));
	rtn = sendto(p->serverFd, senddata, 12, 0, (sockaddr *)&p->clientAddr, p->addrLen);
	if (rtn != 12)
	{
		//thread unlock
		pthread_mutex_unlock(&p->mutexLock);
		rtn = ERR_COMMUNICATION_SENDTO;
		goto LABEL_EXIT;
	}

	rtn = CommRtn(&CommData);
	if (0 != rtn)
	{
		//thread unlock
		pthread_mutex_unlock(&p->mutexLock);
		goto LABEL_EXIT;
	}

	//thread unlock
	pthread_mutex_unlock(&p->mutexLock);

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_ClearAlarm(%d)=%d", axis, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_GetProfileMode(short axis, long &value)
{
	short rtn = ERR_NONE;
	double data;
	short index = AxisID2Index(axis);

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_GetProfileMode(%d)", axis);

	//input check
	if (-1 == index)
	{
		rtn = ERR_AXIS_NO_FOUND;
		goto LABEL_EXIT;
	}

	value = 0;

	// status check
	if (!g_MotionInfo[index].IsOpening)
	{
		rtn = ERR_AXIS_IS_CLOSED;
		goto LABEL_EXIT;
	}

	rtn = TransCommData(axis, CMD_GET_ACTUATOR_MODE, 0x00, &data);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	// change data format
	value = (long)data;

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_GetProfileMode(%d)=%d", axis, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_GetProfilePVC(short axis, double &pos, double &vel, double &cur)
{
	
	 //cout<<" enter to get pvc"<<endl;

	short rtn = ERR_NONE;
	CommunicationData CommData;
	float lPos = 0;
	short index;
	float sVel = 0, sCur = 0;

	// Notes: 因为这个会频繁调用，所以log level设置为CM4_LOG_LEVEL_DBG1
	g_Log.writeLog(CM4_LOG_LEVEL_DBG1, "Enter CM_SCA_Controller::CM_GetProfilePVC(%d)", axis);

	pos = 0.0;
	vel = 0.0;
	cur = 0.0;

	// input check
	index = AxisID2Index(axis);
	if (-1 == index)
	{
		rtn = ERR_AXIS_NO_FOUND;
		goto LABEL_EXIT;
	}

	// status check
	if (!g_MotionInfo[index].IsOpening)
	{
		rtn = ERR_AXIS_IS_CLOSED;
		goto LABEL_EXIT;
	}
 //cout<<"the index is "<<index<<endl;

//	从缓存中读取
	// if (m_bReadInfoFromBuff)
	// {
	// 	pos = g_MotionInfo[index].CurrentPos;
	// 	vel = g_MotionInfo[index].CurrentVel;
	// 	cur = g_MotionInfo[index].CurrentCur;
	// 	goto LABEL_EXIT;
	// }

	memset(&CommData, 0, sizeof(CommunicationData));
	CommData.SendAxis = (unsigned char)axis;
	CommData.SendCmd = CMD_GET_PROFILE_PVC;
	CommData.SendDataLen = 0x00;
	//usleep(200);
	rtn = CommProsses(&CommData);
	//cout<<"CommProsses(&CommData)  is "<<rtn<<endl;
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}
	
 cout<<"CommData.RtnDataLen  is "<<int(CommData.RtnDataLen)<<endl;

	if (CommData.RtnDataLen != 12)
	{
		//rtn = CommProsses(&CommData);
		cout<<"enter the  CommData.RtnDataLen != 12"<<endl;
		rtn = ERR_RTN_PARM;
		goto LABEL_EXIT;
	}

	// 计算pos，vel， cur
{
EndianWrap_U w1,w2,w3;
for (int i = 0; i < 4; i++)
{

w1.c[i]=CommData.RtnData[11-i];
//data += (long)(CommData->RtnData[i ]) * (long)(pow(2, (8 *(i))));
}
pos = w1.v;

for (int i = 0; i < 4; i++)
{

w2.c[i]=CommData.RtnData[11-i-4];
//data += (long)(CommData->RtnData[i ]) * (long)(pow(2, (8 *(i))));
}
vel = w2.v;

for (int i = 0; i < 4; i++)
{

w3.c[i]=CommData.RtnData[11-i-8];
//data += (long)(CommData->RtnData[i ]) * (long)(pow(2, (8 *(i))));
}
cur = w3.v;
}


	// lPos = (long)(CommData.RtnData[8]) * (long)(pow(2, 0));
	// lPos += (long)(CommData.RtnData[9]) * (long)(pow(2, 8));
	// lPos += (long)(CommData.RtnData[10]) * (long)(pow(2, 16));
	// lPos += (long)(CommData.RtnData[11]) * (long)(pow(2, 24));

	// sVel = (short)(CommData.RtnData[4]) * (short)(pow(2, 0));
	// sVel += (short)(CommData.RtnData[5]) * (short)(pow(2, 8));
	// sVel += (short)(CommData.RtnData[6]) * (short)(pow(2, 16));
	// sVel += (short)(CommData.RtnData[7]) * (short)(pow(2, 24));


	// sCur = (short)(CommData.RtnData[0]) * (short)(pow(2, 0));
	// sCur += (short)(CommData.RtnData[1]) * (short)(pow(2, 8));
	// sCur += (short)(CommData.RtnData[2]) * (short)(pow(2, 16));
	// sCur += (short)(CommData.RtnData[3]) * (short)(pow(2, 24));

//	pos = InvIQ24(lPos);
	// vel = InvIQ24(sVel);
	// cur = InvIQ24(sCur);

	// if ((short)CommData.RtnData[8] > 0x80)
	// {
	// 	pos -= 256;
	// }

	//vel *= VELOCITY_RANGE;
	//cur *= g_MotionInfo[index].CurrentRange;

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_DBG1, "Enter CM_SCA_Controller::CM_GetProfilePVC(%d)=%d", axis, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_GetProfilePVC(short axis, long &pos, long &vel, long &cur)
{
	short rtn = ERR_NONE;
	double dPos = 0.0, dVel = 0.0, dCur = 0.0;

	// Notes: 因为这个会频繁调用，所以log level设置为CM4_LOG_LEVEL_DBG1
	g_Log.writeLog(CM4_LOG_LEVEL_DBG1, "Enter CM_SCA_Controller::CM_GetProfilePVC(%d)", axis);

	pos = 0;
	vel = 0;
	cur = 0;

	rtn = CM_GetProfilePVC(axis, dPos, dVel, dCur);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}
	pos = (long)(dPos * CM_SCA_PULSE_NUM);
	vel = (long)(dVel * CM_SCA_PULSE_NUM);
	cur = (long)(dCur * CM_SCA_PULSE_NUM);

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_DBG1, "Exit  CM_SCA_Controller::CM_GetProfilePVC(%d)=%d", axis, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_GetProfilePosition(short axis, double &value)
{
	short rtn = ERR_NONE;
	CommunicationData CommData;
	short index;
	value = 0;

	g_Log.writeLog(CM4_LOG_LEVEL_DBG1, "Enter CM_SCA_Controller::CM_GetProfilePosition(%d, 0x%lf)", axis, value);

	//input check
	index = AxisID2Index(axis);
	if (-1 == index)
	{
		rtn = ERR_AXIS_NO_FOUND;
		goto LABEL_EXIT;
	}

	//status check
	if (!g_MotionInfo[index].IsOpening)
	{
		rtn = ERR_AXIS_IS_CLOSED;
		goto LABEL_EXIT;
	}

	// if (m_bReadInfoFromBuff)
	// {
	// 	value = g_MotionInfo[index].CurrentPos;
	// 	goto LABEL_EXIT;
	// }

	rtn = TransCommData(axis, CMD_GET_PROFILE_POSITION, 0x00, &value);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_DBG1, "Exit  CM_SCA_Controller::CM_GetProfilePosition(%d, 0x%lf)", axis, value);
	return rtn;
}

short CM_SCA_Controller::CM_GetProfilePosition(short axis, long &value)
{
	short rtn = ERR_NONE;
	double val = 0.0;
	value = 0;

	g_Log.writeLog(CM4_LOG_LEVEL_DBG1, "Enter CM_SCA_Controller::CM_GetProfilePosition(%d, (long)0x%lf)", axis, value);

	rtn = CM_GetProfilePosition(axis, val);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}
	value = (long)(val * CM_SCA_PULSE_NUM);

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_DBG1, "Exit  CM_SCA_Controller::CM_GetProfilePosition(%d, (long)0x%lf)=%d", axis, value, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_GetProfileVelocity(short axis, double &value)
{
	short rtn = ERR_NONE;
	CommunicationData CommData;
	short index;
	value = 0;

	g_Log.writeLog(CM4_LOG_LEVEL_DBG1, "Enter CM_SCA_Controller::CM_GetProfileVelocity(%d, 0x%lf)", axis, value);

	// input check
	index = AxisID2Index(axis);
	if (-1 == index)
	{
		rtn = ERR_AXIS_NO_FOUND;
		goto LABEL_EXIT;
	}

	//status check
	if (!g_MotionInfo[index].IsOpening)
	{
		rtn = ERR_AXIS_IS_CLOSED;
		goto LABEL_EXIT;
	}

	// if (m_bReadInfoFromBuff)
	// {
	// 	value = g_MotionInfo[index].CurrentVel;
	// 	goto LABEL_EXIT;
	// }

	rtn = TransCommData(axis, CMD_GET_PROFILE_VELOCITY, 0x00, &value);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}
	value *= VELOCITY_RANGE;

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_DBG1, "Exit  CM_SCA_Controller::CM_GetProfileVelocity(%d, 0x%lf)=%d", axis, value, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_GetProfileVelocity(short axis, long &value)
{
	short rtn = ERR_NONE;
	double val = 0.0;
	value = 0;

	g_Log.writeLog(CM4_LOG_LEVEL_DBG1, "Enter CM_SCA_Controller::CM_GetProfileVelocity(%d, (long)0x%lf)", axis, value);

	rtn = CM_GetProfileVelocity(axis, val);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}
	value = (long)(val * CM_SCA_PULSE_NUM / 60000);

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_DBG1, "Exit  CM_SCA_Controller::CM_GetProfileVelocity(%d, (long)0x%lf)=%d", axis, value, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_GetProfileAcc(short axis, double &value)
{
	return ERR_EXECT;
}

short CM_SCA_Controller::CM_GetCurrent(short axis, double &value)
{
	short rtn = ERR_NONE;
	short index;

	g_Log.writeLog(CM4_LOG_LEVEL_DBG1, "Enter CM_SCA_Controller::CM_GetCurrent(%d, 0x%lf)", axis, value);

	//input check
	index = AxisID2Index(axis);
	if (-1 == index)
	{
		rtn = ERR_AXIS_NO_FOUND;
		goto LABEL_EXIT;
	}

	value = 0;

	// status check
	if (!g_MotionInfo[index].IsOpening)
	{
		rtn = ERR_AXIS_IS_CLOSED;
		goto LABEL_EXIT;
	}

	// if (m_bReadInfoFromBuff)
	// {
	// 	value = g_MotionInfo[index].CurrentCur;
	// 	goto LABEL_EXIT;
	// }

	rtn = TransCommData(axis, CMD_GET_PROFILE_CURRENT, 0x00, &value);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}
	//value *= g_MotionInfo[index].CurrentRange;

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_DBG1, "Exit  CM_SCA_Controller::CM_GetCurrent(%d, 0x%lf)=%d", axis, value, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_GetBrakeState(short axis, short &state)
{
	short rtn = ERR_NONE;
	short index;
	double value = 0;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_GetBrakeState(%d, 0x%lf)", axis, state);

	rtn = SendBrakeTrue();
	return rtn;

	// 	// input check
	// 	index = AxisID2Index(axis);
	// 	if (-1 == index)
	// 	{
	// 		rtn = ERR_AXIS_NO_FOUND;
	// 		goto LABEL_EXIT;
	// 	}

	// 	// status check
	// 	if (!g_MotionInfo[index].IsOpening)
	// 	{
	// 		rtn = ERR_AXIS_IS_CLOSED;
	// 		goto LABEL_EXIT;
	// 	}

	// 	rtn = TransCommData(axis, CMD_GET_BRAKE_STATE, 0x00, &value);
	// 	if (0 != rtn)
	// 	{
	// 		goto LABEL_EXIT;
	// 	}

	// 	state = (short)value;

	// LABEL_EXIT:
	// 	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_GetBrakeState(%d, 0x%lf)=%d", axis, state, rtn);
	// 	return rtn;
}

short CM_SCA_Controller::CM_SetBrakeState(short axis, short state)
{
	short rtn = ERR_NONE;
	short index = AxisID2Index(axis);

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_GetStatus(%d, %d)", axis, state);

	rtn = SendBrakeFalse();
	return rtn;

	// 	// input check
	// 	if (-1 == index)
	// 	{
	// 		rtn = ERR_AXIS_NO_FOUND;
	// 		goto LABEL_EXIT;
	// 	}

	// 	if (0 != state && 1 != state)
	// 	{
	// 		rtn = ERR_INPUT_PARM2;
	// 		goto LABEL_EXIT;
	// 	}

	// 	// status check
	// 	if (!g_MotionInfo[index].IsOpening || g_MotionInfo[index].IsRunning)
	// 	{
	// 		rtn = ERR_STATUS;
	// 		goto LABEL_EXIT;
	// 	}

	// 	rtn = TransCommData(axis, CMD_SET_BRAKE_STATE, 0x01, state);
	// 	if (0 != rtn)
	// 	{
	// 		goto LABEL_EXIT;
	// 	}

	// 	//g_MotionInfo[index].LimitStatus = Status;
	// LABEL_EXIT:
	// 	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_GetStatus(%d, %d)=%d", axis, state, rtn);
	// 	return rtn;
}

short CM_SCA_Controller::CM_GetProfileVoltage(short axis, double &value)
{
	short rtn = ERR_NONE;
	short index;
	value = 0;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_GetProfileVoltage(%d, 0x%lf)", axis, value);

	// input check
	index = AxisID2Index(axis);
	if (-1 == index)
	{
		rtn = ERR_AXIS_NO_FOUND;
		goto LABEL_EXIT;
	}

	//status check
	if (!g_MotionInfo[index].IsOpening)
	{
		rtn = ERR_AXIS_IS_CLOSED;
		goto LABEL_EXIT;
	}

	rtn = TransCommData2(axis, CMD_GET_PROFILE_VOLTAGE, 0x00, &value);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	// value *= g_MotionInfo[AxisID2Index(axis)].CurrentRange;
LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_GetProfileVoltage(%d, 0x%lf)=%d", axis, value, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_SetAxisBand(short axis, long band, long time)
{
	short rtn = ERR_NONE;
	short index;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_SetAxisBand(%d, %lf, %lf)", axis, band, time);

	// input check
	index = AxisID2Index(axis);
	if (-1 == index)
	{
		rtn = ERR_AXIS_NO_FOUND;
		goto LABEL_EXIT;
	}

	if (band > 1000 || band < 0)
	{
		rtn = ERR_INPUT_PARM2;
		goto LABEL_EXIT;
	}

	if (time > 10 || time < 0)
	{
		rtn = ERR_INPUT_PARM3;
		goto LABEL_EXIT;
	}

	// status check
	if (!g_MotionInfo[index].IsOpening || g_MotionInfo[index].IsRunning)
	{

		rtn = ERR_STATUS;
		goto LABEL_EXIT;
	}

	g_MotionInfo[index].Band = band;
	g_MotionInfo[index].BandTime = time;

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_SetAxisBand(%d, %lf, %lf)=%d", axis, band, time, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_GetAxisBand(short axis, long &Band, long &Time)
{
	short rtn = ERR_NONE;
	short index;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_GetAxisBand(%d, (long)0x%lf, (long)0x%lf)", axis, Band, Time);

	// input check
	index = AxisID2Index(axis);
	if (-1 == index)
	{
		rtn = ERR_AXIS_NO_FOUND;
		goto LABEL_EXIT;
	}

	//status check
	if (!g_MotionInfo[index].IsOpening)
	{
		rtn = ERR_AXIS_IS_CLOSED;
		goto LABEL_EXIT;
	}

	Band = g_MotionInfo[index].Band;
	Time = g_MotionInfo[index].BandTime;

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_GetAxisBand(%d, (long)0x%lf, (long)0x%lf)=%d", axis, Band, Time, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_Stop(short axis, long option)
{
	int i;
	double k;
	double restT;
	short rtn = ERR_NONE;
	double value, value1;
	double pos;
	short index;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_Stop(%d, 0x%lf)", axis, option);

	// input check
	index = AxisID2Index(axis);
	if (-1 == index)
	{
		rtn = ERR_AXIS_NO_FOUND;
		goto LABEL_EXIT;
	}

	// status check
	// if (!g_MotionInfo[index].IsOpening /*|| !g_MotionInfo[AxisID2Index(axis)].IsRunning*/)
	if (!g_MotionInfo[index].IsOpening)
	{
		rtn = ERR_AXIS_IS_CLOSED;
		goto LABEL_EXIT;
	}

	if (POSITION_MODE == g_MotionInfo[index].MotionMode ||
		NONE_MODE == g_MotionInfo[index].MotionMode)
	{
		rtn = ERR_STATUS;
		goto LABEL_EXIT;
	}

	//
	// Notes: Get需要判断返回值，Set暂时不需要（因为偶尔1、2次的Set失败没关系）

	switch (g_MotionInfo[index].MotionMode)
	{
	case VELLOCITY_MODE:
	case PROFILE_VELOCITY_MODE:
		rtn = CM_GetProfileVelocity(axis, value);
		if (0 != rtn)
		{
			goto LABEL_EXIT;
		}
		if (option)
		{
			k = 200; //loop time before stop
		}
		else
		{
			k = 600; //loop time before stop
		}
		for (i = 1; i <= k; i++)
		{
			CM_SetVelocity(axis, value * (1 - ((double)i / k)));
			usleep(2000);
		}
		break;
	case CURRENT_MODE:
		rtn = CM_GetCurrent(axis, value);
		if (0 != rtn)
		{
			goto LABEL_EXIT;
		}

		if (option)
		{
			k = 0.1; //decrease propotion
		}
		else
		{
			k = 0.03; //decrease propotion
		}
		while (g_MotionInfo[index].IsRunning)
		{
			value *= k;
			CM_SetCurrent(axis, -value * k);
			usleep(500);
		}
		CM_SetCurrent(axis, 0);
		break;
	case PROFILE_POSITION_MODE:
		rtn = CM_GetProfileVelocity(axis, value);
		if (0 != rtn)
		{
			goto LABEL_EXIT;
		}
		rtn = CM_GetProfilePosition(axis, value1);
		if (0 != rtn)
		{
			goto LABEL_EXIT;
		}
		restT = 60 * fabs(g_MotionInfo[index].LastPos - value1) / fabs(value);
		//剩余时间小于1.5s，则不stop
		if (restT < 1.5)
		{
			break;
		}
		else
		{
			if (option)
			{
				k = 0.3; //stop length propotion
			}
			else
			{
				k = 0.6; //stop length propotion
			}
			pos = value1 + k * fabs(g_MotionInfo[index].LastPos - value1);
			CM_SetPosition(axis, pos);
		}
		break;
	default:
		rtn = ERR_STATUS;
		goto LABEL_EXIT;
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_Stop(%d, 0x%lf)", axis, option);
	return rtn;
}

short CM_SCA_Controller::CM_GetImuData(double &w, double &x, double &y, double &z,
									   double &xa, double &ya, double &za, int &pres)
{
	short rtn = ERR_NONE;
	CommunicationData CommData;
	int q[4], a[3];
	int ipres;
	int i = 0;
	static double gravity_g = 9.81;
	const short oldDataLen = 18, newDataLen = 31;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_GetImuData");

	w = x = y = z = 0.0;
	xa = ya = za = 0.0;
	pres = 0;

	// ee 00 c1 00 01 01 7e80 ed
	memset(&CommData, 0, sizeof(CommunicationData));
	CommData.SendAxis = 0x00;
	CommData.SendCmd = CMD_GET_IMU_DATA;
	CommData.SendDataLen = 0x01;
	CommData.SendData[0] = 0x01;
	//CRC16_1(&CommData.SendData[0], (short)CommData.SendDataLen, CommData.SendCrc);

	rtn = CommProsses(1, &CommData);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	// 判断返回值
	if ((CommData.RtnDataLen != oldDataLen) && (CommData.RtnDataLen != newDataLen))
	{
		rtn = ERR_RTN_PARM;
		goto LABEL_EXIT;
	}

	// 得到四元组
	for (i = 0; i < 4; i++)
	{
		q[i] = 0;
		q[i] += (long)(CommData.RtnData[5 + i * 4]) * (long)(pow(2, 0));
		q[i] += (long)(CommData.RtnData[4 + i * 4]) * (long)(pow(2, 8));
		q[i] += (long)(CommData.RtnData[3 + i * 4]) * (long)(pow(2, 16));
		q[i] += (long)(CommData.RtnData[2 + i * 4]) * (long)(pow(2, 24));
	}

	w = InvIQ30(q[0]);
	x = InvIQ30(q[1]);
	y = InvIQ30(q[2]);
	z = InvIQ30(q[3]);

	// 得到加速度
	if (CommData.RtnDataLen == newDataLen)
	{
		for (i = 0; i < 3; i++)
		{
			a[i] = 0;
			a[i] += (long)(CommData.RtnData[21 + i * 4]) * (long)(pow(2, 0));
			a[i] += (long)(CommData.RtnData[20 + i * 4]) * (long)(pow(2, 8));
			a[i] += (long)(CommData.RtnData[19 + i * 4]) * (long)(pow(2, 16));
			a[i] += (long)(CommData.RtnData[18 + i * 4]) * (long)(pow(2, 24));
		}
		ipres = (int)(CommData.RtnData[30]) * (int)(pow(2, 0));

		xa = InvIQ16(a[0]) * gravity_g;
		ya = InvIQ16(a[1]) * gravity_g;
		za = InvIQ16(a[2]) * gravity_g;
		pres = ipres;
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_GetImuData()=%d", rtn);
	return rtn;
}
