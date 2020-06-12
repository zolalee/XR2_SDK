//
// CM4ScaConfiguration.cpp
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


// system configuration
short CM_SCA_Controller::CM_SetConfigParm(short axis, ConfigParm *parm)
{
	short rtn = ERR_NONE;
	CommunicationData CommData;
	short index = AxisID2Index(axis);

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_SetConfigParm(%d, 0x%lf)", axis, parm);

	// input check
	if (-1 == index)
	{
		rtn = ERR_INPUT_PARM1;
		goto LABEL_EXIT;
	}

	if (parm == NULL)
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

	// 0x0E
	rtn = TransCommData(axis, CMD_SET_CURRENT_PORPORTION, 0x04, parm->CurProp);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	// 0x0F
	rtn = TransCommData(axis, CMD_SET_CURRENT_INTEGRAL, 0x04, parm->CurInteg);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	// 0x10
	rtn = TransCommData(axis, CMD_SET_VELOCITY_PORPORTION, 0x04, parm->VelProp);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	// 0x11
	rtn = TransCommData(axis, CMD_SET_VELOCITY_INTEGRAL, 0x04, parm->VelInteg);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	// 0x12
	rtn = TransCommData(axis, CMD_SET_POSITION_PORPORTION, 0x04, parm->PosProp);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	// 0x13
	rtn = TransCommData(axis, CMD_SET_POSITION_INTEGRAL, 0x04, parm->PosInteg);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	// 0x70
	rtn = TransCommData(axis, CMD_SET_FILTER_CURRENT_STATUS, 0x01, parm->FilterCStatus);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	// 0x72
	rtn = TransCommData(axis, CMD_SET_FILTER_CURRENT_WIDTH, 0x04, parm->FilterCValue);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	// 0x74
	rtn = TransCommData(axis, CMD_SET_FILTER_VELOCITY_STATUS, 0x01, parm->FilterVStatus);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	// 0x76
	rtn = TransCommData(axis, CMD_SET_FILTER_VELOCITY_WIDTH, 0x04, parm->FilterVValue);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	// 0x78
	rtn = TransCommData(axis, CMD_SET_FILTER_POSITION_STATUS, 0x01, parm->FilterPStatus);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	// 0x7A
	rtn = TransCommData(axis, CMD_SET_FILTER_POSITION_WIDTH, 0x04, parm->FilterPValue);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_SetConfigParm(%d, 0x%lf)=%d", axis, parm, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_GetConfigParm(short axis, ConfigParm *parm)
{
	short rtn = ERR_NONE;
	CommunicationData CommData;
	short index = AxisID2Index(axis);

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_GetConfigParm(%d, 0x%lf)", axis, parm);

	// input check
	if (-1 == index)
	{
		rtn = ERR_INPUT_PARM1;
		goto LABEL_EXIT;
	}

	if (parm == NULL)
	{
		rtn = ERR_INPUT_PARM2;
		goto LABEL_EXIT;
	}

	memset(parm, 0, sizeof(struct ConfigParm));

	// status check
	if (!g_MotionInfo[index].IsOpening)
	{
		rtn = ERR_AXIS_IS_CLOSED;
		goto LABEL_EXIT;
	}

	// 0x15
	rtn = TransCommData(axis, CMD_GET_CURRENT_PORPORTION, 0x00, &parm->CurProp);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	// 0x16
	rtn = TransCommData(axis, CMD_GET_CURRENT_INTEGRAL, 0x00, &parm->CurInteg);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	// 0x17
	rtn = TransCommData(axis, CMD_GET_VELOCITY_PORPORTION, 0x00, &parm->VelProp);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	// 0x18
	rtn = TransCommData(axis, CMD_GET_VELOCITY_INTEGRAL, 0x00, &parm->VelInteg);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	// 0x19
	rtn = TransCommData(axis, CMD_GET_POSITION_PORPORTION, 0x00, &parm->PosProp);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	// 0x1A
	rtn = TransCommData(axis, CMD_GET_POSITION_INTEGRAL, 0x00, &parm->PosInteg);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	// FilterCStatus 0x71
	memset(&CommData, 0, sizeof(CommunicationData));
	CommData.SendAxis = (unsigned char)axis;
	CommData.SendCmd = CMD_GET_FILTER_CURRENT_STATUS;
	CommData.SendDataLen = 0x00;
	rtn = CommProsses(&CommData);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}
	parm->FilterCStatus = (bool)CommData.RtnData[0];

	// FilterCWidth 0x73
	rtn = TransCommData(axis, CMD_GET_FILTER_CURRENT_WIDTH, 0x00, &parm->FilterCValue);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	// FilterVStatus 0x75
	memset(&CommData, 0, sizeof(CommunicationData));
	CommData.SendAxis = (unsigned char)axis;
	CommData.SendCmd = CMD_GET_FILTER_VELOCITY_STATUS;
	CommData.SendDataLen = 0x00;
	rtn = CommProsses(&CommData);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}
	parm->FilterVStatus = (bool)CommData.RtnData[0];

	// FilterVWidth 0x77
	rtn = TransCommData(axis, CMD_GET_FILTER_VELOCITY_WIDTH, 0x00, &parm->FilterVValue);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	// FilterPStatus 0x79
	memset(&CommData, 0, sizeof(CommunicationData));
	CommData.SendAxis = (unsigned char)axis;
	CommData.SendCmd = CMD_GET_FILTER_POSITION_STATUS;
	CommData.SendDataLen = 0x00;
	rtn = CommProsses(&CommData);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}
	parm->FilterPStatus = (bool)CommData.RtnData[0];

	// FilterPWidth 0x7B
	rtn = TransCommData(axis, CMD_GET_FILTER_POSITION_WIDTH, 0x00, &parm->FilterPValue);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_GetConfigParm(%d, 0x%lf)=%d", axis, parm, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_GetActuatorT(short axis, double &T)
{
	// if not open, 需要open才可读取, return err
	short rtn = ERR_NONE;
	short index = AxisID2Index(axis);

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_GetActuatorT(%d, %lf)", axis, T);

	// input check
	if (-1 == index)
	{
		rtn = ERR_INPUT_PARM1;
		goto LABEL_EXIT;
	}

	T = 0;

	// status check
	if (!g_MotionInfo[index].IsOpening)
	{
		rtn = ERR_AXIS_IS_CLOSED;
		goto LABEL_EXIT;
	}

	// 0x5F
	rtn = TransCommData(axis, CMD_GET_ACTUATOR_TEMPERATURE, 0x00, &T);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_GetActuatorT(%d, %lf)=%d", axis, T, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_GetDriverT(short axis, double &T)
{
	// if not open, 需要open才可读取, return err
	short rtn = ERR_NONE;
	short index = AxisID2Index(axis);

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_GetDriverT(%d, %lf)", axis, T);

	// input check
	rtn = AxisID2Index(axis);
	if (-1 == rtn)
	{
		rtn = ERR_INPUT_PARM1;
		goto LABEL_EXIT;
	}

	T = 0;

	// status check
	if (!g_MotionInfo[index].IsOpening)
	{
		rtn = ERR_AXIS_IS_CLOSED;
		goto LABEL_EXIT;
	}

	// 0x60
	rtn = TransCommData(axis, CMD_GET_DRIVER_TEMPERATURE, 0x00, &T);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_GetDriverT(%d, %lf)=%d", axis, T, rtn);
	return rtn;
}

// Security configuration
short CM_SCA_Controller::CM_SetSoftLimitValue(short axis, double NSoftLimit, double PSoftLimit)
{
	short rtn = ERR_NONE;
	short index = AxisID2Index(axis);

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_SetSoftLimitValue(%d, %lf, %lf)", axis, NSoftLimit, PSoftLimit);

	// input check
	if (-1 == index)
	{
		rtn = ERR_INPUT_PARM1;
		goto LABEL_EXIT;
	}

	if (NSoftLimit >= PSoftLimit)
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

	// NegativeSoftLimit 0x84
	rtn = TransCommData(axis, CMD_SET_NEGITIVE_SOFTLIMIT, 0x04, NSoftLimit);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}
	g_MotionInfo[index].SParm.NegativeSoftLimit = NSoftLimit;

	// PositiveSoftLimit 0x83
	rtn = TransCommData(axis, CMD_SET_POSITIVE_SOFTLIMIT, 0x04, PSoftLimit);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}
	g_MotionInfo[index].SParm.PositiveSoftLimit = PSoftLimit;

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_SetSoftLimitValue(%d, %lf, %lf)", axis, NSoftLimit, PSoftLimit);
	return rtn;
}

short CM_SCA_Controller::CM_GetSoftLimitValue(short axis, double &NSoftLimit, double &PSoftLimit)
{
	short rtn = ERR_NONE;
	short index = AxisID2Index(axis);

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_GetSoftLimitValue(%d, %lf, %lf)", axis, NSoftLimit, PSoftLimit);

	// input check
	if (-1 == index)
	{
		rtn = ERR_INPUT_PARM1;
		goto LABEL_EXIT;
	}

	NSoftLimit = 0.0;
	PSoftLimit = 0.0;

	// status check
	if (!g_MotionInfo[index].IsOpening)
	{
		rtn = ERR_AXIS_IS_CLOSED;
		goto LABEL_EXIT;
	}

	// NegativeSoftLimit 0x86
	rtn = TransCommData(axis, CMD_GET_NEGITIVE_SOFTLIMIT, 0x00, &NSoftLimit);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	// PositiveSoftLimit 0x85
	rtn = TransCommData(axis, CMD_GET_POSITIVE_SOFTLIMIT, 0x00, &PSoftLimit);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_GetSoftLimitValue(%d, %lf, %lf)=%d", axis, NSoftLimit, PSoftLimit, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_SetSafeParm(short axis, SafeParm *parm)
{
	short rtn = ERR_NONE;
	short index = AxisID2Index(axis);

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_SetSafeParm(%d)", axis);

	//input check
	if (-1 == index)
	{
		rtn = ERR_INPUT_PARM1;
		goto LABEL_EXIT;
	}

	if ((parm == NULL) ||
		(parm->NegativeSoftLimit >= parm->PositiveSoftLimit) ||
		(parm->NegativeSoftLimit <= -128 || parm->NegativeSoftLimit >= 128) ||
		(parm->PositiveSoftLimit <= -128 || parm->PositiveSoftLimit >= 128) ||
		(parm->MinOutputVel >= parm->MaxOutputVel) ||
		(parm->MaxOutputVel < -1 || parm->MaxOutputVel > 1) ||
		(parm->MinOutputVel < -1 || parm->MinOutputVel > 1) ||
		(parm->MinOutputPos >= parm->MaxOutputPos) ||
		(parm->MaxOutputPos < -1 || parm->MaxOutputPos > 1) ||
		(parm->MinOutputPos < -1 || parm->MinOutputPos > 1))
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

	// NegativeSoftLimit 0x84
	rtn = TransCommData(axis, CMD_SET_NEGITIVE_SOFTLIMIT, 0x04, parm->NegativeSoftLimit);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}
	g_MotionInfo[index].SParm.NegativeSoftLimit = parm->NegativeSoftLimit;

	// PositiveSoftLimit 0x83
	rtn = TransCommData(axis, CMD_SET_POSITIVE_SOFTLIMIT, 0x04, parm->PositiveSoftLimit);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}
	g_MotionInfo[index].SParm.PositiveSoftLimit = parm->PositiveSoftLimit;

	// MaxOutputVel 0x31
	rtn = TransCommData(axis, CMD_SET_MAX_OUTPUT_VELOCITY, 0x04, parm->MaxOutputVel);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}
	g_MotionInfo[index].SParm.MaxOutputVel = parm->MaxOutputVel;

	// MinOutputVel 0x30
	rtn = TransCommData(axis, CMD_SET_MIN_OUTPUT_VELOCITY, 0x04, parm->MinOutputVel);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}
	g_MotionInfo[index].SParm.MinOutputVel = parm->MinOutputVel;

	// MaxOutputPos 0x33
	rtn = TransCommData(axis, CMD_SET_MAX_OUTPUT_POSITION, 0x04, parm->MaxOutputPos);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}
	g_MotionInfo[index].SParm.MaxOutputPos = parm->MaxOutputPos;

	// MinOutputPos 0x32
	rtn = TransCommData(axis, CMD_SET_MIN_OUTPUT_POSITION, 0x04, parm->MinOutputPos);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}
	g_MotionInfo[index].SParm.MinOutputPos = parm->MinOutputPos;

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_SetSafeParm(%d)=%d", axis, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_GetSafeParm(short axis, SafeParm *parm)
{
	short rtn = ERR_NONE;
	short index = AxisID2Index(axis);

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_GetSafeParm(%d)", axis);

	// input check
	if (-1 == index)
	{
		rtn = ERR_INPUT_PARM1;
		goto LABEL_EXIT;
	}

	if (parm == NULL)
	{
		rtn = ERR_INPUT_PARM2;
		goto LABEL_EXIT;
	}

	memset(parm, 0, sizeof(struct SafeParm));

	// status check
	if (!g_MotionInfo[index].IsOpening)
	{
		rtn = ERR_AXIS_IS_CLOSED;
		goto LABEL_EXIT;
	}

	// 0x86
	rtn = TransCommData(axis, CMD_GET_NEGITIVE_SOFTLIMIT, 0x00, &parm->NegativeSoftLimit);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	// 0x85
	rtn = TransCommData(axis, CMD_GET_POSITIVE_SOFTLIMIT, 0x00, &parm->PositiveSoftLimit);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	// 0x37
	rtn = TransCommData(axis, CMD_GET_MAX_OUTPUT_VELOCITY, 0x00, &parm->MaxOutputVel);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	// 0x36
	rtn = TransCommData(axis, CMD_GET_MIN_OUTPUT_VELOCITY, 0x00, &parm->MinOutputVel);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	// 0x39
	rtn = TransCommData(axis, CMD_GET_MAX_OUTPUT_POSITION, 0x00, &parm->MaxOutputPos);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	// 0x38
	rtn = TransCommData(axis, CMD_GET_MIN_OUTPUT_POSITION, 0x00, &parm->MinOutputPos);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_GetSafeParm(%d)=%d", axis, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_SetSoftLimitStatus(short axis, long status)
{
	short rtn = ERR_NONE;
	short index = AxisID2Index(axis);

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_SetSoftLimitStatus(%d, %ld)", axis, status);

	// input check
	if (-1 == index)
	{
		rtn = ERR_INPUT_PARM1;
		goto LABEL_EXIT;
	}

	if (0 != status && 1 != status)
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

	// 0x8C
	rtn = TransCommData(axis, CMD_SET_LIMIT_SWITCH, 0x01, status);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}
	g_MotionInfo[index].LimitStatus = status;

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_SetSoftLimitStatus(%d, %ld)=%d", axis, status, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_SetAllSoftLimitStatus(long status)
{
	short i;
	short rtn = ERR_NONE;
	short tempRtn = ERR_NONE;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_SetAllSoftLimitStatus(%ld)", status);

	for (i = 0; i < g_AxisNum; i++)
	{
		tempRtn = CM_SetSoftLimitStatus(g_MotionInfo[i].ID, status);
		if (tempRtn != 0)
		{
			rtn = tempRtn;
		}
	}

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_SetAllSoftLimitStatus(%ld)=%d", status, rtn);
	return rtn;
}

short CM_SCA_Controller::CM_GetSoftLimitStatus(short axis, long &status)
{
	short rtn = ERR_NONE;
	double data;
	CommunicationData CommData;
	short index = AxisID2Index(axis);

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CM_GetSoftLimitStatus(%d, 0x%lf)", axis, status);

	// input check
	if (-1 == index)
	{
		rtn = ERR_INPUT_PARM1;
		goto LABEL_EXIT;
	}

	status = 0;

	// status check
	if (!g_MotionInfo[index].IsOpening)
	{
		rtn = ERR_AXIS_IS_CLOSED;
		goto LABEL_EXIT;
	}

	// 0x8B
	memset(&CommData, 0, sizeof(CommunicationData));
	CommData.SendAxis = (unsigned char)axis;
	CommData.SendCmd = CMD_GET_LIMIT_STATUS;
	CommData.SendDataLen = 0x00;

	rtn = CommProsses(&CommData);
	if (0 == rtn)
	{
		status = (CommData.RtnData[0] || CommData.RtnData[1]);
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CM_GetSoftLimitStatus(%d, 0x%lf)=%d", axis, status, rtn);
	return rtn;
}
