//
// CM4ScaInternal.cpp
//
// Copyright (C) 2018-2025 Cloudminds. All Rights Reserved.
//
//

#include "CM4ScaCommon.h"

/*---------------------------------------------------------------------------------------
------
------	Crc check
------
---------------------------------------------------------------------------------------*/
const unsigned char ChCRCHTalbe[] = {
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40};

const unsigned char ChCRCLTalbe[] = {
	0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7,
	0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E,
	0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9,
	0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC,
	0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
	0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32,
	0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D,
	0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38,
	0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF,
	0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
	0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1,
	0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4,
	0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB,
	0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA,
	0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
	0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0,
	0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97,
	0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E,
	0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89,
	0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
	0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83,
	0x41, 0x81, 0x80, 0x40};

extern CM4Log g_Log;
extern AxisMotionInfo *g_MotionInfo;
extern unsigned short g_AxisNum;
extern bool g_StartGetPVCTimer;
extern bool g_CloseGetPVCThread;
extern pthread_t g_tid[ECU_COUNT];
extern string g_EcuIp[ECU_COUNT];
extern EcuRelatedInfo g_ecuRelatedInfo[ECU_COUNT];
extern short g_PvcTimeoutCount;

// private
long CM_SCA_Controller::IQ8(double value)
{
	return (long)(value * pow(2, 8));
}

double CM_SCA_Controller::InvIQ8(long value)
{
	return (double)(value) / (pow(2.0, 8));
}

long CM_SCA_Controller::IQ10(double value)
{
	return (long)(value * pow(2, 10));
}

double CM_SCA_Controller::InvIQ10(long value)
{
	return (double)(value) / (pow(2.0, 10));
}

long CM_SCA_Controller::IQ14(double value)
{
	return (long)(value * pow(2, 14));
}

double CM_SCA_Controller::InvIQ14(long value)
{
	return (double)(value) / (pow(2.0, 14));
}

long CM_SCA_Controller::IQ24(double value)
{
	long temp = pow(2, 24);
	return (long)(value * pow(2, 24));
}

double CM_SCA_Controller::InvIQ24(long value)
{
	return (double)(value) / (pow(2.0, 24));
}

double CM_SCA_Controller::InvIQ30(int value)
{
	return (double)(value) / (pow(2.0, 30));
}

double CM_SCA_Controller::InvIQ16(int value)
{
	return (double)(value) / (pow(2.0, 16));
}


void CM_SCA_Controller::Fix2Double(CommunicationData *CommData, double &value)
{
	int i;
	long data = 0;

	value = 0;

	for (i = 0; i < CommData->RtnDataLen; i++)
	{
		data += (long)(CommData->RtnData[CommData->RtnDataLen - 1 - i]) * (long)(pow(2, (8 * i)));
	}

	switch (CommData->RtnDataLen)
	{
	case 1:
		value = data;
		break;
	case 2:
		value = InvIQ8(data);
		break;
	case 4:
		value = InvIQ24(data);
		break;
	default:
		break;
	}

	if ((short)CommData->RtnData[0] > 0x80)
	{
		value -= 256;
	}
}

void CM_SCA_Controller::Double2Fix(CommunicationData *CommData, double &value)
{
	int i;
	int j;
	long data;
	long temp;

	switch (CommData->SendDataLen)
	{
	case 1:
		data = value;
		break;
	case 2:
		data = IQ8(value);
		break;
	case 4:
		data = IQ24(value);
		break;
	default:
		break;
	}
	temp = abs(data);

	for (i = 0; i < CommData->SendDataLen; i++)
	{
		j = CommData->SendDataLen - 1 - i;
		if (data >= 0)
		{
			CommData->SendData[i] = temp / (long)(pow(2, (8 * j)));
		}
		else
		{
			CommData->SendData[i] = 255 - temp / (long)(pow(2, (8 * j)));
		}
		temp %= (long)(pow(2, (8 * j)));
	}
}

void CM_SCA_Controller::Double2Fix1(CommunicationData *CommData, double &value)
{
	int i;
	int j;
	long data;
	long temp;
	double TempVal;

	TempVal = value * pow(2, 20) / 60;
	temp = fabs(TempVal);
	for (i = 0; i < CommData->SendDataLen; i++)
	{
		j = CommData->SendDataLen - 1 - i;
		if (TempVal >= 0)
		{
			CommData->SendData[i] = temp / (long)(pow(2, (8 * j)));
		}
		else
		{
			CommData->SendData[i] = 255 - temp / (long)(pow(2, (8 * j)));
		}
		temp %= (long)(pow(2, (8 * j)));
	}
}

short CM_SCA_Controller::CommSend(CommunicationData *CommData)
{
	int rtn = ERR_NONE;
	int Datalen;
	short axis;
	short ip;
	short index;
	EcuRelatedInfo *p = NULL;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CommSend()");

	// Notes: CommSend是内部函数，所以axis应该有值
	axis = (short)CommData->SendAxis;

	index = AxisID2Index(axis);
	if (-1 == index)
	{
		rtn = ERR_AXIS_NO_FOUND;
		goto LABEL_EXIT;
	}

	// 得到当前的ip和ecu信息
	ip = g_MotionInfo[index].IP;
	p = &g_ecuRelatedInfo[ip];

	// 打包发送数据
	rtn = PackageCommSendData(CommData);
	if (rtn != 0)
	{
		goto LABEL_EXIT;
	}

	// 清空当前socket缓存
	CleanSocketBuff(p->serverFd);

	// 发送命令
	rtn = sendto(p->serverFd, &CommData->SendChar, CommData->SendCharLen, 0, (sockaddr *)&p->clientAddr, p->addrLen);
	if (rtn < 0 || CommData->SendCharLen != rtn)
	{
		rtn = ERR_COMMUNICATION_SENDTO;
		goto LABEL_EXIT;
	}

	rtn = 0;

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CommSend()=%d", rtn);
	return rtn;
}

short CM_SCA_Controller::PackageCommSendData(CommunicationData *CommData)
{
	int rtn = ERR_NONE;
	int Datalen;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::PackageCommSendData()");

	memset(CommData->SendChar, '\0', sizeof(CommData->SendChar));
	CommData->SendChar[0] = 0xEE;
	memcpy(CommData->SendChar + 1, &CommData->SendAxis, 1);
	memcpy(CommData->SendChar + 2, &CommData->SendCmd, 1);
	memset(CommData->SendChar + 3, 0, 1);
	memcpy(CommData->SendChar + 4, &CommData->SendDataLen, 1);
	Datalen = (int)CommData->SendDataLen;

	switch (Datalen)
	{
	case 0:
		CommData->SendChar[5] = 0xED;
		CommData->SendCharLen = 6;
		break;
	case 1:
		memcpy(CommData->SendChar + 5, &CommData->SendData, 1);
		//memcpy(CommData->SendChar + 6, &CommData->SendCrc, 2);
		//CommData->SendChar[8] = 0xED;
		CommData->SendChar[6] = 0xED;
		CommData->SendCharLen = 7;
		break;
	case 2:
		memcpy(CommData->SendChar + 5, &CommData->SendData, 2);
		//CRC16_1(CommData->SendData, 2, CommData->SendCrc);
		//memcpy(CommData->SendChar + 7, &CommData->SendCrc, 2);
		CommData->SendChar[7] = 0xED;
		CommData->SendCharLen = 8;
		break;
	case 3:
		memcpy(CommData->SendChar + 5, &CommData->SendData, 3);
		//CRC16_1(CommData->SendData, 2, CommData->SendCrc);
		//memcpy(CommData->SendChar + 9, &CommData->SendCrc, 2);
		CommData->SendChar[8] = 0xED;
		CommData->SendCharLen = 9;
		break;
	case 4:
		memcpy(CommData->SendChar + 5, &CommData->SendData, 4);
		//CRC16_1(CommData->SendData, 2, CommData->SendCrc);
		//memcpy(CommData->SendChar + 10, &CommData->SendCrc, 2);
		CommData->SendChar[9] = 0xED;
		CommData->SendCharLen = 10;
		break;
	case 5:
		memcpy(CommData->SendChar + 5, &CommData->SendData, 5);
		//CRC16_1(CommData->SendData, 2, CommData->SendCrc);
		//memcpy(CommData->SendChar + 10, &CommData->SendCrc, 2);
		CommData->SendChar[10] = 0xED;
		CommData->SendCharLen = 11;
		break;		
	default:
		rtn = ERR_INPUT_PARM;
	}

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::PackageCommSendData()=%d", rtn);
	return rtn;
}

short CM_SCA_Controller::CommSend(short ip, CommunicationData *CommData)
{
	int rtn;
	int Datalen;
	short axis;
	EcuRelatedInfo *p = &g_ecuRelatedInfo[ip];

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CommSend(%d)", ip);

	// 打包发送数据
	rtn = PackageCommSendData(CommData);
	if (rtn != 0)
	{
		goto LABEL_EXIT;
	}

	// 清空当前socket缓存
	CleanSocketBuff(p->serverFd);

	// 发送命令
	rtn = sendto(p->serverFd, &CommData->SendChar, CommData->SendCharLen, 0, (sockaddr *)&p->clientAddr, p->addrLen);
	if (rtn < 0 || CommData->SendCharLen != rtn)
	{
		rtn = ERR_COMMUNICATION_SENDTO;
		goto LABEL_EXIT;
	}

	rtn = 0;

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CommSend(%d)=%d", ip, rtn);
	return rtn;
}

short CM_SCA_Controller::CommRtn(CommunicationData *CommData)
{
	int rtn = ERR_NONE;
	int Datalen;
	int result = -1;
	fd_set readFd;
	timeval g_Timeout;
	sockaddr_in tempClientAddr;
	short index;
	short axis;
	short ip;
	EcuRelatedInfo *p = NULL;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CommRtn()");

	axis = (short)CommData->SendAxis;
	index = AxisID2Index(axis);
	if (-1 == index)
	{
		rtn = ERR_AXIS_NO_FOUND;
		goto LABEL_EXIT;
	}

	// 得到当前的ip和ecu信息
	ip = g_MotionInfo[index].IP;
	p = &g_ecuRelatedInfo[ip];

	FD_ZERO(&readFd);			  //初始化readfd
	FD_SET(p->serverFd, &readFd); //把server_fd加入readfd

	g_Timeout.tv_sec = 0;
	g_Timeout.tv_usec = COMMUNICATION_TIME;
	result = select(p->serverFd + 1, &readFd, NULL, NULL, &g_Timeout);
	if (result <= 0)
	{
		rtn = ERR_WAITTING_TIMEOUT;
		goto LABEL_EXIT;
	}

	rtn = recvfrom(p->serverFd, &CommData->RtnChar, 64, 0, (sockaddr *)&tempClientAddr, &p->addrLen);
	if (rtn <= 0)
	{
		rtn = ERR_COMMUNICATION_RECVFROM;
		goto LABEL_EXIT;
	}

	memcpy(&CommData->RtnAxis, CommData->RtnChar + 1, 1);
	memcpy(&CommData->RtnCmd, CommData->RtnChar + 2, 1);
	memcpy(&CommData->RtnDataLen, CommData->RtnChar + 4, 1);
	//Datalen = strtol((char *)CommData->RtnDataLen, NULL,10);
	Datalen = (int)CommData->RtnDataLen;
	memcpy(&CommData->RtnData, CommData->RtnChar + 5, Datalen);
	if (0xED != (int)CommData->RtnChar[5 + Datalen])
	{
		memcpy(&CommData->RtnCrc, CommData->RtnChar + 5 + Datalen, 2);
	}

	rtn = 0;

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CommRtn()=%d", rtn);
	return rtn;
}

short CM_SCA_Controller::CommRtn(short ip, CommunicationData *CommData)
{
	int rtn = ERR_NONE;
	int Datalen;
	int result = -1;
	fd_set readFd;
	timeval g_Timeout;
	sockaddr_in tempClientAddr;
	EcuRelatedInfo *p = &g_ecuRelatedInfo[ip];

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CommRtn(%d)", ip);

	FD_ZERO(&readFd);			  //初始化readfd
	FD_SET(p->serverFd, &readFd); //把server_fd加入readfd

	g_Timeout.tv_sec = 0;
	g_Timeout.tv_usec = COMMUNICATION_TIME;
	result = select(p->serverFd + 1, &readFd, NULL, NULL, &g_Timeout);
	if (result <= 0)
	{
		rtn = ERR_WAITTING_TIMEOUT;
		goto LABEL_EXIT;
	}

	rtn = recvfrom(p->serverFd, &CommData->RtnChar, 64, 0, (sockaddr *)&tempClientAddr, &p->addrLen);
	if (rtn <= 0)
	{
		rtn = ERR_COMMUNICATION_RECVFROM;
		goto LABEL_EXIT;
	}

	memcpy(&CommData->RtnAxis, CommData->RtnChar + 1, 1);
	memcpy(&CommData->RtnCmd, CommData->RtnChar + 2, 1);
	memcpy(&CommData->RtnDataLen, CommData->RtnChar + 4, 1);
	//Datalen = strtol((char *)CommData->RtnDataLen, NULL,10);
	Datalen = (int)CommData->RtnDataLen;
	memcpy(&CommData->RtnData, CommData->RtnChar + 5, Datalen);
	if (0xED != (int)CommData->RtnChar[5 + Datalen])
	{
		memcpy(&CommData->RtnCrc, CommData->RtnChar + 5 + Datalen, 2);
	}

	rtn = 0;

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CommRtn(%d)=%d", ip, rtn);
	return rtn;
}

short CM_SCA_Controller::RtnCheck(CommunicationData *CommData)
{
	short rtn = ERR_NONE;
	int i;
	unsigned char crc[2];

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::RtnCheck()");

	if (CommData->RtnAxis != CommData->SendAxis || CommData->RtnCmd != CommData->SendCmd)
	{
		rtn = ERR_RTN_PARM_AXIS;
		goto LABEL_EXIT;
	}
	if (0xED != CommData->RtnChar[5 + (int)CommData->RtnDataLen])
	{
		CRC16_1(CommData->RtnData, CommData->RtnDataLen, crc);
		for (i = 0; i < 2; i++)
		{
			if (crc[i] != CommData->RtnCrc[i])
			{
				rtn = ERR_RTN_PARM_CRC;
				goto LABEL_EXIT;
			}
		}
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::RtnCheck()=%d", rtn);
	return rtn;
}

short CM_SCA_Controller::CommProsses(CommunicationData *CommData)
{
	short rtn = ERR_NONE;
	short axis = 0, ip = 0;
	EcuRelatedInfo *p = NULL;
	short index;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CommProsses()");

	axis = (short)CommData->SendAxis;
	index = AxisID2Index(axis);
	if (-1 == index)
	{
		rtn = ERR_AXIS_NO_FOUND;
		goto LABEL_EXIT;
	}

	ip = g_MotionInfo[index].IP;
	p = &g_ecuRelatedInfo[ip];

	// thread lock
	pthread_mutex_lock(&p->mutexLock);

	//test
	// timeval timeStart, timeEnd;
	// double TimeVal=0;
	// gettimeofday(&timeStart, NULL);
	//end

	rtn = CommSend(CommData);
	if (0 != rtn)
	{
		pthread_mutex_unlock(&p->mutexLock);
		goto LABEL_EXIT;
	}
	rtn = CommRtn(CommData);
	if (0 != rtn)
	{
		pthread_mutex_unlock(&p->mutexLock);
		goto LABEL_EXIT;
	}

	//test
	// gettimeofday( &timeEnd, NULL);
	// TimeVal = (timeEnd.tv_sec - timeStart.tv_sec)*1000000 + (double)(timeEnd.tv_usec -timeStart.tv_usec);
	// //if(TimeVal > 1000)
	// {
	// 	printf("timeval is %f\n", TimeVal);
	// }
	//end

	// rtn check
	rtn = RtnCheck(CommData);
	if (0 != rtn)
	{
		pthread_mutex_unlock(&p->mutexLock);
		rtn = ERR_RTN_PARM;
		goto LABEL_EXIT;
	}

	pthread_mutex_unlock(&p->mutexLock);

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CommProsses()=%d", rtn);
	return rtn;
}

short CM_SCA_Controller::CommProsses(short ip, CommunicationData *CommData)
{
	short rtn = ERR_NONE;
	short axis = 0;
	EcuRelatedInfo *p = &g_ecuRelatedInfo[ip];

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::CommProsses(%d)", ip);

	//thread lock
	pthread_mutex_lock(&p->mutexLock);

	rtn = CommSend(ip, CommData);
	if (0 != rtn)
	{
		pthread_mutex_unlock(&p->mutexLock);
		goto LABEL_EXIT;
	}

	rtn = CommRtn(ip, CommData);
	if (0 != rtn)
	{
		pthread_mutex_unlock(&p->mutexLock);
		goto LABEL_EXIT;
	}

	// rtn check
	rtn = RtnCheck(CommData);
	if (0 != rtn)
	{
		pthread_mutex_unlock(&p->mutexLock);
		goto LABEL_EXIT;
	}

	pthread_mutex_unlock(&p->mutexLock);

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::CommProsses(%d)=%d", ip, rtn);
	return rtn;
}

void CM_SCA_Controller::CRC16_1(unsigned char *pchMsg, short wDataLen, unsigned char *crc)
{
	unsigned char chCRCHi = 0xFF; // 高CRC字节初始化
	unsigned char chCRCLo = 0xFF; // 低CRC字节初始化
	short wIndex;				  // CRC循环中的索引
	while (wDataLen--)
	{
		// 计算CRC
		wIndex = chCRCHi ^ *pchMsg++;
		chCRCHi = chCRCLo ^ ChCRCHTalbe[wIndex];
		chCRCLo = ChCRCLTalbe[wIndex];
	}
	crc[0] = chCRCHi;
	crc[1] = chCRCLo;
}

short CM_SCA_Controller::TransCommData(short axis, short cmd, short DataLen, double data)
{
	short rtn = ERR_NONE;
	CommunicationData CommData;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::TransCommData(%d, 0x%x, %d, %lf)", axis, cmd, DataLen, data);

	memset(&CommData, 0, sizeof(CommunicationData));
	CommData.SendAxis = (unsigned char)axis;
	CommData.SendCmd = (unsigned char)cmd;
	CommData.SendDataLen = (unsigned char)DataLen;
	Double2Fix(&CommData, data);
	//CRC16_1(&CommData.SendData[0], (short)CommData.SendDataLen, CommData.SendCrc);
	rtn = CommProsses(&CommData);
	if (rtn != 0)
	{
		goto LABEL_EXIT;
	}

	if (!(short)CommData.RtnData[0])
	{
		rtn = ERR_EXECT;
		goto LABEL_EXIT;
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::TransCommData(%d, 0x%x, %d, %lf)=%d", axis, cmd, DataLen, data, rtn);
	return rtn;
}

short CM_SCA_Controller::TransCommDataThruIP(short ip, short axis, short cmd, short DataLen, double data)
{
	short rtn = ERR_NONE;
	CommunicationData CommData;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::TransCommDataThruIP(%d, %d, 0x%x, %d, %lf)", ip, axis, cmd, DataLen, data);

	memset(&CommData, 0, sizeof(CommunicationData));
	CommData.SendAxis = (unsigned char)axis;
	CommData.SendCmd = (unsigned char)cmd;
	CommData.SendDataLen = (unsigned char)DataLen;
	Double2Fix(&CommData, data);
	CRC16_1(&CommData.SendData[0], (short)CommData.SendDataLen, CommData.SendCrc);
	rtn = CommProsses(ip, &CommData);
	if (rtn != 0)
	{
		goto LABEL_EXIT;
	}
	if (!(short)CommData.RtnData[0])
	{
		rtn = ERR_EXECT;
		goto LABEL_EXIT;
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::TransCommDataThruIP(%d, %d, 0x%x, %d, %lf)=%d", ip, axis, cmd, DataLen, data, rtn);
	return rtn;
}

short CM_SCA_Controller::TransCommData1(short axis, short cmd, short DataLen, double data)
{
	short rtn = ERR_NONE;
	CommunicationData CommData;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::TransCommData1(%d, 0x%x, %d, %lf)", axis, cmd, DataLen, data);

	memset(&CommData, 0, sizeof(CommunicationData));
	CommData.SendAxis = (unsigned char)axis;
	CommData.SendCmd = (unsigned char)cmd;
	CommData.SendDataLen = (unsigned char)DataLen;
	Double2Fix1(&CommData, data);
	//CRC16_1(&CommData.SendData[0], (short)CommData.SendDataLen, CommData.SendCrc);
	rtn = CommProsses(&CommData);
	if (rtn != 0)
	{
		goto LABEL_EXIT;
	}
	if (!(short)CommData.RtnData[0])
	{
		rtn = ERR_EXECT;
		goto LABEL_EXIT;
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::TransCommData1(%d, 0x%x, %d, %lf)=%d", axis, cmd, DataLen, data, rtn);
	return rtn;
}

short CM_SCA_Controller::TransCommData(short axis, short cmd, short DataLen, double *data)
{
	short rtn;
	CommunicationData CommData;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::TransCommData(%d, 0x%x, %d)", axis, cmd, DataLen);

	memset(&CommData, 0, sizeof(CommunicationData));
	CommData.SendAxis = (unsigned char)axis;
	CommData.SendCmd = (unsigned char)cmd;
	CommData.SendDataLen = (unsigned char)DataLen;
	rtn = CommProsses(&CommData);
	if (rtn != 0)
	{
		goto LABEL_EXIT;
	}

	Fix2Double(&CommData, *data);

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::TransCommData(%d, 0x%x, %d)=%d", axis, cmd, DataLen, rtn);
	return rtn;
}

short CM_SCA_Controller::TransCommData1(short axis, short cmd, short DataLen, short stage, double *data)
{
	short rtn = ERR_NONE;
	int i;
	CommunicationData CommData;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::TransCommData1(%d, 0x%x, %d, %d)", axis, cmd, DataLen, stage);

	memset(&CommData, 0, sizeof(CommunicationData));
	CommData.SendAxis = (unsigned char)axis;
	CommData.SendCmd = (unsigned char)cmd;
	CommData.SendDataLen = (unsigned char)DataLen;
	rtn = CommProsses(&CommData);
	if (rtn != 0)
	{
		goto LABEL_EXIT;
	}

	if (stage == 0)
	{
		for (i = 0; i < 4; i++)
		{
			*data += (long)(CommData.RtnData[3 - i]) * (long)(pow(2, (8 * i)));
		}
		*data = *data * 60 / pow(2, 20);
	}
	else
	{
		for (i = 0; i < 4; i++)
		{
			*data += (255 - (long)(CommData.RtnData[3 - i])) * (long)(pow(2, (8 * i)));
		}
		*data = -*data * 60 / pow(2, 20);
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::TransCommData1(%d, 0x%x, %d, %d)=%d", axis, cmd, DataLen, stage, rtn);
	return rtn;
}

short CM_SCA_Controller::TransCommData2(short axis, short cmd, short DataLen, double *data)
{
	short rtn;
	int i = 0;
	CommunicationData CommData;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::TransCommData2(%d, 0x%x, %d)", axis, cmd, DataLen);

	memset(&CommData, 0, sizeof(CommunicationData));
	CommData.SendAxis = (unsigned char)axis;
	CommData.SendCmd = (unsigned char)cmd;
	CommData.SendDataLen = (unsigned char)DataLen;
	rtn = CommProsses(&CommData);
	if (rtn != 0)
	{
		goto LABEL_EXIT;
	}

	// Fix2Double(&CommData, *data);
	for (i = 0; i < CommData.RtnDataLen; i++)
	{
		*data += (long)(CommData.RtnData[CommData.RtnDataLen - 1 - i]) * (long)(pow(2, (8 * i)));
	}

	*data = InvIQ10(*data);

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::TransCommData2(%d, 0x%x, %d)=%d", axis, cmd, DataLen, rtn);
	return rtn;
}

short CM_SCA_Controller::PrepareWork(short ip, vector<short> &axis)
{
	short rtn = ERR_NONE;
	CommunicationData CommData;
	EcuRelatedInfo *p = &g_ecuRelatedInfo[ip];

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::PrepareWork(%d)", ip);

	//pre work
	rtn = TransCommDataThruIP(ip, 0x00, CMD_FIRST_COMMUNICATION, 0x00, 0x01);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

	//thread lock
	pthread_mutex_lock(&p->mutexLock);

	//ask
	memset(&CommData, 0, sizeof(CommunicationData));
	CommData.SendAxis = 0x00;
	CommData.SendCmd = CMD_GET_ACTUATOR_ADDRESS;
	CommData.SendDataLen = 0x00;
	rtn = CommSend(ip, &CommData);
	if (0 != rtn)
	{
		//thread unlock
		pthread_mutex_unlock(&p->mutexLock);
		goto LABEL_EXIT;
	}

	while (true)
	{
		rtn = CommRtn(ip, &CommData);
		if (0 == rtn)
		{
			g_AxisNum += 1;
			axis.push_back((short)CommData.RtnAxis);
		}
		else
		{
			break;
		}
		usleep(100);
	}

	//thread unlock
	pthread_mutex_unlock(&p->mutexLock);

	rtn = 0;

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::PrepareWork(%d)=%d", ip, rtn);
	return rtn;
}

short CM_SCA_Controller::GetCurrentRange(short axis, double &value)
{
	short rtn = ERR_NONE;
	short index;
	value = 0;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::GetCurrentRange(%d)", axis);

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

	// 0x53
	rtn = TransCommData(axis, CMD_GET_CURRENT_RANGE, 0x00, &value);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::GetCurrentRange(%d, %.2lf)=%d", axis, value, rtn);
	return ERR_NONE;
}

short CM_SCA_Controller::IsOpened(short axis, bool &status)
{
	short rtn = ERR_NONE;
	short index;
	short IP;
	long sts;
	double data;
	SafeParm parm;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::IsOpened(%d)", axis);

	index = AxisID2Index(axis);
	if (-1 == index)
	{
		rtn = ERR_INPUT_PARM1;
		goto LABEL_EXIT;
	}

	memset(&parm, 0, sizeof(struct SafeParm));
	status = false;

	//open check
	rtn = TransCommData(axis, CMD_GET_ACTUATOR_ONOFF_STATUS, 0x00, &data);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}
	status = (bool)data;
	if (!status)
	{
		IP = g_MotionInfo[index].IP;
		memset(&g_MotionInfo[index], 0, sizeof(struct AxisMotionInfo));
		g_MotionInfo[index].ID = axis;
		g_MotionInfo[index].IP = IP;
		//g_MotionInfo[AxisID2Index(axis)].IsOpening = false;
		rtn = ERR_NONE;
		goto LABEL_EXIT;
	}

	//set global variables
	g_MotionInfo[index].IsOpening = true;
	if (IsFingerActuator(g_MotionInfo[index].ID))
	{
		g_MotionInfo[index].CurrentRange = 1.0;
		g_MotionInfo[index].SParm.MaxOutputPos = 1.0;
		g_MotionInfo[index].SParm.MinOutputPos = -1.0;
		g_MotionInfo[index].SParm.MaxOutputVel = 1.0;
		g_MotionInfo[index].SParm.MinOutputVel = -1.0;
		rtn = CM_GetSoftLimitValue(g_MotionInfo[index].ID, g_MotionInfo[index].SParm.NegativeSoftLimit, g_MotionInfo[index].SParm.PositiveSoftLimit);
		if (0 != rtn)
		{
			goto LABEL_EXIT;
		}
	}
	else
	{
		rtn = GetCurrentRange(axis, g_MotionInfo[index].CurrentRange);
		if (0 != rtn)
		{
			goto LABEL_EXIT;
		}

		rtn = CM_GetSafeParm(g_MotionInfo[index].ID, &parm);
		if (0 != rtn)
		{
			goto LABEL_EXIT;
		}
		memcpy(&g_MotionInfo[index].SParm, &parm, sizeof(SafeParm));
	}

	rtn = CM_GetSoftLimitStatus(g_MotionInfo[index].ID, sts);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}
	g_MotionInfo[index].LimitStatus = sts;
	rtn = CM_GetStatus(axis, sts);
	if (sts == AXIS_RUNNING)
	{
		g_MotionInfo[index].IsRunning = sts;
	}

	rtn = CM_GetProfileMode(g_MotionInfo[index].ID, sts);
	if (0 != rtn)
	{
		goto LABEL_EXIT;
	}
	g_MotionInfo[index].MotionMode = sts;

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::IsOpened(%d)=%d", axis, rtn);
	return rtn;
}

short CM_SCA_Controller::Open(vector<short> axis)
{
	int i;
	short rtn = ERR_NONE;
	short id, index;
	short IP;
	bool status;
	long sts;
	vector<short> ClosedAxis;
	SafeParm parm;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::Open(vector<short> axis)");

	memset(&parm, 0, sizeof(struct SafeParm));

	// open check
	for (i = 0; i < axis.size(); i++)
	{
		rtn = IsOpened(axis.at(i), status);
		if (0 != rtn)
		{
			goto LABEL_EXIT;
		}
		if (true != status)
		{
			ClosedAxis.push_back(axis.at(i));
		}
		if (g_MotionInfo[AxisID2Index(axis.at(i))].IsRunning == true)
		{
			rtn = ERR_AXIS_IS_RUNNING;
			goto LABEL_EXIT;
		}
	}

	// open
	for (i = 0; i < ClosedAxis.size(); i++)
	{
		rtn = TransCommData(ClosedAxis.at(i), CMD_SET_ACTUATER_ONOFF, 0x01, 0x01);
		if (0 != rtn)
		{
			goto LABEL_EXIT;
		}
		usleep(100000);
	}

	if (ClosedAxis.size() > 0)
	{
		sleep(4); //sleep time after open
	}

	// set global variables
	for (i = 0; i < ClosedAxis.size(); i++)
	{
		id = ClosedAxis.at(i);
		index = AxisID2Index(id);
		IP = g_MotionInfo[index].IP;
		//clear alarm, if on alarm
		//no need to check rtn
		CM_ClearAlarm(id);
		memset(&g_MotionInfo[index], 0, sizeof(struct AxisMotionInfo));
		g_MotionInfo[index].ID = id;
		g_MotionInfo[index].IP = IP;
		g_MotionInfo[index].IsOpening = true;

		if (IsFingerActuator(g_MotionInfo[index].ID))
		{
			g_MotionInfo[index].CurrentRange = 1.0;
			g_MotionInfo[index].SParm.MaxOutputPos = 1.0;
			g_MotionInfo[index].SParm.MinOutputPos = -1.0;
			g_MotionInfo[index].SParm.MaxOutputVel = 1.0;
			g_MotionInfo[index].SParm.MinOutputVel = -1.0;

			rtn = CM_GetSoftLimitValue(g_MotionInfo[i].ID, g_MotionInfo[i].SParm.NegativeSoftLimit, g_MotionInfo[i].SParm.PositiveSoftLimit);
			if (0 != rtn)
			{
				goto LABEL_EXIT;
			}
		}
		else
		{
			rtn = GetCurrentRange(id, g_MotionInfo[index].CurrentRange);
			if (0 != rtn)
			{
				goto LABEL_EXIT;
			}

			rtn = CM_GetSafeParm(g_MotionInfo[index].ID, &parm);
			if (0 != rtn)
			{
				goto LABEL_EXIT;
			}
			memcpy(&g_MotionInfo[index].SParm, &parm, sizeof(struct SafeParm));
		}

		rtn = CM_GetSoftLimitStatus(g_MotionInfo[index].ID, sts);
		if (0 != rtn)
		{
			goto LABEL_EXIT;
		}
		g_MotionInfo[index].LimitStatus = sts;

		rtn = CM_GetProfileMode(g_MotionInfo[index].ID, sts);
		if (0 != rtn)
		{
			goto LABEL_EXIT;
		}
		g_MotionInfo[index].MotionMode = sts;
	}

	rtn = ERR_NONE;

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::Open(vector<short> axis)=%d", rtn);
	return rtn;
}

short CM_SCA_Controller::Close(vector<short> axis)
{
	int i;
	int index;
	short IP;
	double data;
	short rtn = ERR_NONE;
	bool sts = false;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::Close(vector<short> axis)");

	for (i = 0; i < axis.size(); i++)
	{
		index = AxisID2Index(axis.at(i));
		// input check
		if (-1 == index)
		{
			g_Log.writeLog(CM4_LOG_LEVEL_INFO, "AxisID2Index = %d, no found.", axis.at(i));
			rtn = ERR_AXIS_NO_FOUND;
			goto LABEL_EXIT;
		}

		IP = g_MotionInfo[index].IP;
		//status check
		if (g_MotionInfo[index].IsRunning)
		{
			rtn = ERR_AXIS_IS_RUNNING;
			goto LABEL_EXIT;
		}

		// 返回数据：01表示开机，00表示关机
		rtn = TransCommData(axis.at(i), CMD_GET_ACTUATOR_ONOFF_STATUS, 0x00, &data);
		if (0 != rtn)
		{
			// 当前Axis出错后，continue
			g_Log.writeLog(CM4_LOG_LEVEL_INFO, "TransCommData(%d, CMD_GET_ACTUATOR_ONOFF_STATUS)=%d", axis.at(i), rtn);
			continue;
		}

		//if ((bool)data == false)
		if (data == 0)
		{
			sts = true;
			continue;
		}

		// close
		rtn = TransCommData(axis.at(i), CMD_SET_ACTUATER_ONOFF, 0x01, 0.0);
		if (0 != rtn)
		{
			// 当前Axis出错后，continue
			g_Log.writeLog(CM4_LOG_LEVEL_INFO, "TransCommData(%d, CMD_SET_ACTUATER_ONOFF)=%d", axis.at(i), rtn);
			continue;
		}
		//clear global variables
		memset(&g_MotionInfo[index], 0, sizeof(struct AxisMotionInfo));
		g_MotionInfo[index].ID = axis.at(i);
		g_MotionInfo[index].IP = IP;
	}

	if (sts)
	{
		rtn = ALERT_STATUS;
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::Close(vector<short> axis)=%d", rtn);
	return rtn;
}

short CM_SCA_Controller::AxisID2Index(short axis)
{
	short i;
	short index = -1;

	for (i = 0; i < g_AxisNum; i++)
	{
		if (g_MotionInfo[i].ID == axis)
		{
			index = i;
			break;
		}
	}
	return index;
}

void CM_SCA_Controller::CleanSocketBuff(int sock)
{
	int sock_conn = sock;

	// 设置select立即返回
	timeval time_out;
	time_out.tv_sec = 0;
	time_out.tv_usec = 0;

	// 设置select对sock_conn的读取感兴趣
	fd_set read_fds;
	FD_ZERO(&read_fds);
	FD_SET(sock_conn, &read_fds);
	int res = -1;
	int len = 0;

	// tbd: for test
	//char recv_data[2];
	char recv_data[24];
	memset(recv_data, 0, sizeof(recv_data));
	while (true)
	{
		res = select(FD_SETSIZE, &read_fds, NULL, NULL, &time_out);
		if (res == 0)
			break;						   //数据读取完毕，缓存区清空成功
		len = recv(sock_conn, recv_data, 23, 0); //触发数据读取
	}
}

short CM_SCA_Controller::InitEcuRelatedInfo()
{
	int rtn = ERR_NONE;
	int i = 0;
	EcuRelatedInfo *p = NULL;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::InitEcuRelatedInfo()");

	for (i = 0; i < ECU_COUNT; i++)
	{
		p = &g_ecuRelatedInfo[i];
		rtn = pthread_mutex_init(&p->mutexLock, NULL);
		if (0 != rtn)
		{
			rtn = ERR_THREAD_MUTEX_INIT;
			goto LABEL_EXIT;
		}

		// 创建socket对象
		p->serverFd = socket(AF_INET, SOCK_DGRAM, 0);
		if (-1 == p->serverFd)
		{
			rtn = ERR_CREATE_SOCKET;
			goto LABEL_EXIT;
		}

		// 创建网络通信对象
		memset(&p->clientAddr, 0, sizeof(p->clientAddr));
		p->clientAddr.sin_family = AF_INET;
		p->clientAddr.sin_port = htons(PORT);
		p->addrLen = sizeof(struct sockaddr);
		p->clientAddr.sin_addr.s_addr = inet_addr(g_EcuIp[i].c_str());
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::InitEcuRelatedInfo()=%d", rtn);
	return rtn;
}

short CM_SCA_Controller::DeinitEcuRelatedInfo()
{
	int rtn = ERR_NONE;
	int i = 0;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::DeinitEcuRelatedInfo()");

	for (i = 0; i < ECU_COUNT; i++)
	{
		// 清空当前socket缓存
		CleanSocketBuff(g_ecuRelatedInfo[i].serverFd);

		// 关闭当前socket
		close(g_ecuRelatedInfo[i].serverFd);

		// 销毁mutex
		pthread_mutex_destroy(&g_ecuRelatedInfo[i].mutexLock);
	}

LABEL_EXIT:
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::DeinitEcuRelatedInfo()=%d", rtn);
	return rtn;
}

bool CM_SCA_Controller::PositionIsIncorrect(short index, double &pos)
{
	bool bRet = true;

	double pSoftLimit = g_MotionInfo[index].SParm.PositiveSoftLimit;
	double nSoftLimit = g_MotionInfo[index].SParm.NegativeSoftLimit;

	if ((pos >= pSoftLimit + SOFTLIMIT_THRESHOLD) || (pos <= nSoftLimit - SOFTLIMIT_THRESHOLD))
	{
		// pos的值可能就是异常的，所以不用打印了
		// g_Log.writeLog(CM4_LOG_LEVEL_ERROR, "CM_SCA_Controller::PositionIsIncorrect(%d), pos=%lf, PositiveSoftLimit=%lf, NegativeSoftLimit=%lf", index, pos, pSoftLimit, nSoftLimit);
		return bRet;
	}

	if ((pos >= pSoftLimit) && (pos <= pSoftLimit + SOFTLIMIT_THRESHOLD))
	{
		pos = pSoftLimit - SOFTLIMIT_THRESHOLD;
	}
	else if ((pos <= pSoftLimit) && (pos > pSoftLimit - SOFTLIMIT_THRESHOLD))
	{
		pos = pSoftLimit - SOFTLIMIT_THRESHOLD;
	}
	else if ((pos <= nSoftLimit) && (pos >= nSoftLimit - SOFTLIMIT_THRESHOLD))
	{
		pos = nSoftLimit + SOFTLIMIT_THRESHOLD;
	}
	else if ((pos >= nSoftLimit) && (pos < nSoftLimit + SOFTLIMIT_THRESHOLD))
	{
		pos = nSoftLimit + SOFTLIMIT_THRESHOLD;
	}

	bRet = false;
	return bRet;
}

short CM_SCA_Controller::SendAndRecvPackData(short ip, unsigned char *sendBuff, int sendLength, int recvCount)
{
	short rtn = ERR_NONE;
	int i = 0;
	short index;
	EcuRelatedInfo *p = NULL;
	unsigned char RtnChar[32]; //返回的字符串
	fd_set readFd;
	timeval g_Timeout;
	sockaddr_in tempClientAddr;
	int result = -1;

	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Enter CM_SCA_Controller::SendAndRecvPackData(%d, buff, %d, %d)", ip, sendLength, recvCount);

	// 发送打包的数据
	p = &g_ecuRelatedInfo[ip];

	pthread_mutex_lock(&p->mutexLock);

	// 清空当前socket缓存
	CleanSocketBuff(p->serverFd);

	// 发送命令
	rtn = sendto(p->serverFd, sendBuff, sendLength, 0, (sockaddr *)&p->clientAddr, p->addrLen);
	if (rtn < 0 || sendLength != rtn)
	{
		rtn = ERR_COMMUNICATION_SENDTO;
		goto LABEL_EXIT;
	}

	// 接收数据
	for (i = 0; i < recvCount; i++)
	{
		FD_ZERO(&readFd);			  //初始化readfd
		FD_SET(p->serverFd, &readFd); //把server_fd加入readfd

		g_Timeout.tv_sec = 0;
		g_Timeout.tv_usec = COMMUNICATION_TIME;

		result = select(p->serverFd + 1, &readFd, NULL, NULL, &g_Timeout);
		if (result <= 0)
		{
			rtn = ERR_WAITTING_TIMEOUT;
			goto LABEL_EXIT;
		}

		rtn = recvfrom(p->serverFd, &RtnChar, 64, 0, (sockaddr *)&tempClientAddr, &p->addrLen);
		if (rtn <= 0)
		{
			rtn = ERR_COMMUNICATION_RECVFROM;
			goto LABEL_EXIT;
		}
	}

LABEL_EXIT:
	// Notes: 这里的pthread_mutex_unlock放在LABEL_EXIT标签下
	pthread_mutex_unlock(&p->mutexLock);
	g_Log.writeLog(CM4_LOG_LEVEL_INFO, "Exit  CM_SCA_Controller::SendAndRecvPackData(%d, buff, %d, %d)=%d", ip, sendLength, recvCount, rtn);
	return rtn;
}

//----------------------------------------------------------------------------------

void *CM_SCA_Controller::TimerGetPVC(void *parm)
{
	ThreadParm *threadParm = (ThreadParm *)parm;
	CM_SCA_Controller *pThis = threadParm->This;
	unsigned short ip = threadParm->IP;

	int sleepTime = 0;
	const int Interval = CYC_GET_PVC_TIME;
	unsigned short nSwitch = 0;

	g_PvcTimeoutCount = 0;

	while (true)
	{
		// 关闭GetPVC线程
		if (g_CloseGetPVCThread)
		{
			break;
		}

		// 没有启动定时器
		if (!g_StartGetPVCTimer)
		{
			usleep(Interval);
			continue;
		}

		//test
		timeval timeStart, timeEnd;
		double TimeVal = 0;
		gettimeofday(&timeStart, NULL);
		//end

		// tbd: for test
		if ((ip == 2) || (ip == 3))
		{
			if (nSwitch == 0)
			{
				pThis->GetEcuAxisPVC2(ip, CMD_GET_PROFILE_POSITION);
			}
			else if (nSwitch == 3)
			{
				pThis->GetEcuAxisPVC2(ip, CMD_GET_PROFILE_CURRENT);
			}

			nSwitch++;
			if (nSwitch > 4)
				nSwitch = 0;
		}
		else
		{
			pThis->GetEcuAxisPVC2(ip, CMD_GET_PROFILE_PVC);
		}


		// pThis->GetEcuAxisPVC(ip);


		//test
		gettimeofday(&timeEnd, NULL);
		TimeVal = (timeEnd.tv_sec - timeStart.tv_sec) * 1000000 + (double)(timeEnd.tv_usec - timeStart.tv_usec);

		// cout << "*** TimeVal = " << TimeVal << endl;
		//end

		sleepTime = Interval - TimeVal;
		if (sleepTime > 0)
		{
			usleep(sleepTime);
		}
		else
		{
			if (++g_PvcTimeoutCount > 10000)
			{
				g_PvcTimeoutCount = 0;
			}
			cout << "No. " << g_PvcTimeoutCount << ", TimeVal = " << TimeVal << ", IP = " << ip << endl;
		}
	}

	return NULL;
}

short CM_SCA_Controller::GetAllAxisPVC()
{
	short rtn = ERR_NONE;

	short i = 0;
	double pos, vel, cur;

	for (i = 0; i < g_AxisNum; i++)
	{
		rtn = CM_GetProfilePVC(g_MotionInfo[i].ID, pos, vel, cur);
		if (rtn == 0)
		{
			g_MotionInfo[i].CurrentPos = pos;
			g_MotionInfo[i].CurrentVel = vel;
			g_MotionInfo[i].CurrentCur = cur;
		}
	}

	return rtn;
}

short CM_SCA_Controller::GetEcuAxisPVC(unsigned short ip)
{
	//
	// Note: 考虑init成功后，需要Sleep 3秒才能进入该函数，否则send成功，但select=0失败
	//

	short rtn = ERR_NONE;

	short i = 0;
	short count = 0;
	double pos, vel, cur;
	long lPos = 0;
	short index;
	short sVel = 0, sCur = 0;

	CommunicationData CommData;
	int Datalen;
	double data;
	unsigned char SendBuf[100];
	int SendDataLen = 0;
	EcuRelatedInfo *p = &g_ecuRelatedInfo[ip];
	unsigned char RtnChar[32]; //返回的字符串
	fd_set readFd;
	timeval g_Timeout;
	sockaddr_in tempClientAddr;
	int result = -1;
	unsigned short logIP = ip + 1;

	pthread_mutex_lock(&p->mutexLock);

	for (i = 0; i < g_AxisNum; i++)
	{
		if (ip == g_MotionInfo[i].IP)
		{
			if (IsFingerActuator(g_MotionInfo[i].ID))
			{
				// package P
				SendBuf[count * 6] = 0xEE;
				SendBuf[count * 6 + 1] = g_MotionInfo[i].ID;
				SendBuf[count * 6 + 2] = CMD_GET_PROFILE_POSITION;
				SendBuf[count * 6 + 3] = 0;
				SendBuf[count * 6 + 4] = 0x00;
				SendBuf[count * 6 + 5] = 0xED;
				count++;

				// Finger 没有V值

				// package C
				SendBuf[count * 6] = 0xEE;
				SendBuf[count * 6 + 1] = g_MotionInfo[i].ID;
				SendBuf[count * 6 + 2] = CMD_GET_PROFILE_CURRENT;
				SendBuf[count * 6 + 3] = 0;
				SendBuf[count * 6 + 4] = 0x00;
				SendBuf[count * 6 + 5] = 0xED;
				count++;
			}
			else
			{
				// package PVC
				SendBuf[count * 6] = 0xEE;
				SendBuf[count * 6 + 1] = g_MotionInfo[i].ID;
				SendBuf[count * 6 + 2] = CMD_GET_PROFILE_PVC;
				SendBuf[count * 6 + 3] = 0;
				SendBuf[count * 6 + 4] = 0x00;
				SendBuf[count * 6 + 5] = 0xED;
				count++;
			}
		}
	}

	SendDataLen = count * 6;

	if (SendDataLen == 0)
	{
		// tbd: 理论上不会=0，但测试中由于不是所有ECU都用到了。所以会出现
		goto LABEL_EXIT;
	}

	// 清空当前socket缓存
	CleanSocketBuff(p->serverFd);

	// 发送打包数据
	rtn = sendto(p->serverFd, &SendBuf, SendDataLen, 0, (sockaddr *)&p->clientAddr, p->addrLen);
	if (rtn < 0 || SendDataLen != rtn)
	{
		rtn = ERR_COMMUNICATION_SENDTO;
		g_Log.writeLog(CM4_LOG_LEVEL_ERROR, logIP, "*** CM_SCA_Controller::GetEcuAxisPVC(%d)=%d, SendDataLen = %d", ip, rtn, SendDataLen);
		goto LABEL_EXIT;
	}

	// for test
	// if (count > 0)
	// {
	// 	cout << "*** count = " << count << ", sendLength = " << SendDataLen << endl;
	// }

	// 接收返回
	for (i = 0; i < count; i++)
	{
		FD_ZERO(&readFd);			  //初始化readfd
		FD_SET(p->serverFd, &readFd); //把server_fd加入readfd

		g_Timeout.tv_sec = 0;
		g_Timeout.tv_usec = COMMUNICATION_TIME;
		result = select(p->serverFd + 1, &readFd, NULL, NULL, &g_Timeout);
		if (result <= 0)
		{
			rtn = ERR_WAITTING_TIMEOUT;
			g_Log.writeLog(CM4_LOG_LEVEL_ERROR, logIP, "*** CM_SCA_Controller::GetEcuAxisPVC(%d)=%d, i = %d, count = %d", ip, rtn, i, count);
			goto LABEL_EXIT;
		}

		rtn = recvfrom(p->serverFd, &CommData.RtnChar, 64, 0, (sockaddr *)&tempClientAddr, &p->addrLen);
		if (rtn <= 0)
		{
			rtn = ERR_COMMUNICATION_RECVFROM;
			g_Log.writeLog(CM4_LOG_LEVEL_ERROR, logIP, "*** CM_SCA_Controller::GetEcuAxisPVC(%d)=%d, i = %d, count = %d", ip, rtn, i, count);
			goto LABEL_EXIT;
		}
		memcpy(&CommData.RtnAxis, CommData.RtnChar + 1, 1);
		memcpy(&CommData.RtnCmd, CommData.RtnChar + 2, 1);
		memcpy(&CommData.RtnDataLen, CommData.RtnChar + 4, 1);
		Datalen = (int)CommData.RtnDataLen;
		memcpy(&CommData.RtnData, CommData.RtnChar + 5, Datalen);
		if (0xED != (int)CommData.RtnChar[5 + Datalen])
		{
			memcpy(&CommData.RtnCrc, CommData.RtnChar + 5 + Datalen, 2);
		}

		// 解析返回的data
		Fix2Double(&CommData, data);

		index = AxisID2Index(CommData.RtnAxis);
		if (-1 == index)
		{
			// tbd: 这些错误，是否应该只是打印log就好
			rtn = ERR_AXIS_NO_FOUND;
			g_Log.writeLog(CM4_LOG_LEVEL_ERROR, logIP, "*** CM_SCA_Controller::GetEcuAxisPVC(%d)=%d, i = %d", ip, rtn, i);
			// goto LABEL_EXIT;
		}

		if (CommData.RtnCmd == CMD_GET_PROFILE_POSITION)
		{
			pos = data;
			g_MotionInfo[index].CurrentPos = pos;
		}
		else if (CommData.RtnCmd == CMD_GET_PROFILE_CURRENT)
		{
			cur = data * g_MotionInfo[index].CurrentRange;
			g_MotionInfo[index].CurrentCur = cur;
		}
		else if (CommData.RtnCmd == CMD_GET_PROFILE_PVC)
		{
			if (CommData.RtnDataLen != 7)
			{
				// tbd: 这些错误，是否应该只是打印log就好
				// pthread_mutex_unlock(&p->mutexLock);
				// return ERR_RTN_PARM;
				rtn = ERR_RTN_PARM_DATA_LEN;
				g_Log.writeLog(CM4_LOG_LEVEL_ERROR, logIP, "*** CM_SCA_Controller::GetEcuAxisPVC(%d)=%d, CommData.RtnDataLen = %d", ip, rtn, CommData.RtnDataLen);
			}

			lPos = (long)(CommData.RtnData[2]) * (long)(pow(2, 8));
			lPos += (long)(CommData.RtnData[1]) * (long)(pow(2, 16));
			lPos += (long)(CommData.RtnData[0]) * (long)(pow(2, 24));

			sVel = (short)(CommData.RtnData[4]) * (short)(pow(2, 0));
			sVel += (short)(CommData.RtnData[3]) * (short)(pow(2, 8));
			sCur = (short)(CommData.RtnData[6]) * (short)(pow(2, 0));
			sCur += (short)(CommData.RtnData[5]) * (short)(pow(2, 8));

			pos = InvIQ24(lPos);
			vel = InvIQ14(sVel);
			cur = InvIQ14(sCur);

			if ((short)CommData.RtnData[0] > 0x80)
			{
				pos -= 256;
			}

			vel *= VELOCITY_RANGE;
			cur *= g_MotionInfo[index].CurrentRange;

			g_MotionInfo[index].CurrentPos = pos;
			g_MotionInfo[index].CurrentVel = vel;
			g_MotionInfo[index].CurrentCur = cur;
		}
	}

LABEL_EXIT:
	pthread_mutex_unlock(&p->mutexLock);
	return rtn;
}

short CM_SCA_Controller::GetEcuAxisPVC2(unsigned short ip, unsigned char cmd)
{
	//
	// Note: 考虑init成功后，需要Sleep 3秒才能进入该函数，否则send成功，但select=0失败
	//

	short rtn = ERR_NONE;

	short i = 0;
	short count = 0;
	double pos, vel, cur;
	long lPos = 0;
	short index;
	short sVel = 0, sCur = 0;

	CommunicationData CommData;
	short Datalen;
	double data;
	unsigned char SendBuf[100];
	short SendDataLen = 0;
	EcuRelatedInfo *p = &g_ecuRelatedInfo[ip];
	unsigned char RtnChar[32]; //返回的字符串
	fd_set readFd;
	timeval g_Timeout;
	sockaddr_in tempClientAddr;
	int result = -1;
	unsigned short logIP = ip + 1;

	pthread_mutex_lock(&p->mutexLock);

	for (i = 0; i < g_AxisNum; i++)
	{
		if (ip == g_MotionInfo[i].IP)
		{
			SendBuf[count * 6] = 0xEE;
			SendBuf[count * 6 + 1] = g_MotionInfo[i].ID;
			SendBuf[count * 6 + 2] = cmd;
			SendBuf[count * 6 + 3] = 0;
			SendBuf[count * 6 + 4] = 0x00;
			SendBuf[count * 6 + 5] = 0xED;
			count++;
		}
	}

	SendDataLen = count * 6;
	if (SendDataLen == 0)
	{
		// tbd: 理论上不会=0，但测试中由于不是所有ECU都用到了。所以会出现
		goto LABEL_EXIT;
	}

	// 清空当前socket缓存
	CleanSocketBuff(p->serverFd);

	// 发送打包数据
	rtn = sendto(p->serverFd, &SendBuf, SendDataLen, 0, (sockaddr *)&p->clientAddr, p->addrLen);
	if (rtn < 0 || SendDataLen != rtn)
	{
		rtn = ERR_COMMUNICATION_SENDTO;
		g_Log.writeLog(CM4_LOG_LEVEL_ERROR, logIP, "*** CM_SCA_Controller::GetEcuAxisPVC(%d)=%d, SendDataLen = %d", ip, rtn, SendDataLen);
		goto LABEL_EXIT;
	}

	// 接收返回
	for (i = 0; i < count; i++)
	{
		FD_ZERO(&readFd);			  //初始化readfd
		FD_SET(p->serverFd, &readFd); //把server_fd加入readfd

		g_Timeout.tv_sec = 0;
		g_Timeout.tv_usec = COMMUNICATION_TIME_1;
		result = select(p->serverFd + 1, &readFd, NULL, NULL, &g_Timeout);
		if (result <= 0)
		{
			rtn = ERR_WAITTING_TIMEOUT;
			g_Log.writeLog(CM4_LOG_LEVEL_ERROR, logIP, "*** CM_SCA_Controller::GetEcuAxisPVC(%d)=%d, i = %d, count = %d", ip, rtn, i, count);
			goto LABEL_EXIT;
		}

		rtn = recvfrom(p->serverFd, &CommData.RtnChar, 64, 0, (sockaddr *)&tempClientAddr, &p->addrLen);
		if (rtn <= 0)
		{
			rtn = ERR_COMMUNICATION_RECVFROM;
			g_Log.writeLog(CM4_LOG_LEVEL_ERROR, logIP, "*** CM_SCA_Controller::GetEcuAxisPVC(%d)=%d, i = %d, count = %d", ip, rtn, i, count);
			goto LABEL_EXIT;
		}
		memcpy(&CommData.RtnAxis, CommData.RtnChar + 1, 1);
		memcpy(&CommData.RtnCmd, CommData.RtnChar + 2, 1);
		memcpy(&CommData.RtnDataLen, CommData.RtnChar + 4, 1);
		Datalen = (int)CommData.RtnDataLen;
		memcpy(&CommData.RtnData, CommData.RtnChar + 5, Datalen);
		if (0xED != (int)CommData.RtnChar[5 + Datalen])
		{
			memcpy(&CommData.RtnCrc, CommData.RtnChar + 5 + Datalen, 2);
		}

		// 解析返回的data
		Fix2Double(&CommData, data);

		index = AxisID2Index(CommData.RtnAxis);
		if (-1 == index)
		{
			// tbd: 这些错误，是否应该只是打印log就好
			rtn = ERR_AXIS_NO_FOUND;
			g_Log.writeLog(CM4_LOG_LEVEL_ERROR, logIP, "*** CM_SCA_Controller::GetEcuAxisPVC(%d)=%d, i = %d", ip, rtn, i);
			// goto LABEL_EXIT;
		}

		if (CommData.RtnCmd == CMD_GET_PROFILE_POSITION)
		{
			pos = data;
			g_MotionInfo[index].CurrentPos = pos;
		}
		else if (CommData.RtnCmd == CMD_GET_PROFILE_CURRENT)
		{
			cur = data * g_MotionInfo[index].CurrentRange;
			g_MotionInfo[index].CurrentCur = cur;
		}
		else if (CommData.RtnCmd == CMD_GET_PROFILE_PVC)
		{
			if (CommData.RtnDataLen != 7)
			{
				// tbd: 这些错误，是否应该只是打印log就好
				// pthread_mutex_unlock(&p->mutexLock);
				// return ERR_RTN_PARM;
				rtn = ERR_RTN_PARM_DATA_LEN;
				g_Log.writeLog(CM4_LOG_LEVEL_ERROR, logIP, "*** CM_SCA_Controller::GetEcuAxisPVC(%d)=%d, CommData.RtnDataLen = %d", ip, rtn, CommData.RtnDataLen);
			}

			lPos = (long)(CommData.RtnData[2]) * (long)(pow(2, 8));
			lPos += (long)(CommData.RtnData[1]) * (long)(pow(2, 16));
			lPos += (long)(CommData.RtnData[0]) * (long)(pow(2, 24));

			sVel = (short)(CommData.RtnData[4]) * (short)(pow(2, 0));
			sVel += (short)(CommData.RtnData[3]) * (short)(pow(2, 8));
			sCur = (short)(CommData.RtnData[6]) * (short)(pow(2, 0));
			sCur += (short)(CommData.RtnData[5]) * (short)(pow(2, 8));

			pos = InvIQ24(lPos);
			vel = InvIQ14(sVel);
			cur = InvIQ14(sCur);

			if ((short)CommData.RtnData[0] > 0x80)
			{
				pos -= 256;
			}

			vel *= VELOCITY_RANGE;
			cur *= g_MotionInfo[index].CurrentRange;

			g_MotionInfo[index].CurrentPos = pos;
			g_MotionInfo[index].CurrentVel = vel;
			g_MotionInfo[index].CurrentCur = cur;
		}
	}

LABEL_EXIT:
	pthread_mutex_unlock(&p->mutexLock);
	return rtn;
}

short CM_SCA_Controller::CM_StartGetPVCTimer(bool flag)
{
	int rtn = ERR_NONE;

	g_StartGetPVCTimer = flag;

	return rtn;
}


//------------------------------------------------------------------------------
short CM_SCA_Controller::SendBrakeTrue()
{
	short rtn = ERR_NONE;

	unsigned short ip = 1;
	unsigned char SendBuf[12];
	EcuRelatedInfo *p = &g_ecuRelatedInfo[ip];
	short SendDataLen = 11;

	pthread_mutex_lock(&p->mutexLock);
	
	// "ee 00 c1 00 03 31 01 01 e0 5f ed"
	
	SendBuf[0] = 0xEE;
	SendBuf[1] = 0x00;
	SendBuf[2] = 0xC1;
	SendBuf[3] = 0x00;
	SendBuf[4] = 0x03;
	SendBuf[5] = 0x31;
	SendBuf[6] = 0x01;
	SendBuf[7] = 0x01;
	SendBuf[8] = 0xE0;
	SendBuf[9] = 0x5F;
	SendBuf[10] = 0xED;
	
	// 清空当前socket缓存
	CleanSocketBuff(p->serverFd);
	
	// 发送打包数据
	rtn = sendto(p->serverFd, &SendBuf, SendDataLen, 0, (sockaddr *)&p->clientAddr, p->addrLen);
	if (rtn < 0 || SendDataLen != rtn)
	{
		rtn = ERR_COMMUNICATION_SENDTO;
		goto LABEL_EXIT;
	}
	
	usleep(100);
	
	// "ee 00 c1 00 03 31 02 01 e0 af ed"
	SendBuf[0] = 0xEE;
	SendBuf[1] = 0x00;
	SendBuf[2] = 0xC1;
	SendBuf[3] = 0x00;
	SendBuf[4] = 0x03;
	SendBuf[5] = 0x31;
	SendBuf[6] = 0x02;
	SendBuf[7] = 0x01;
	SendBuf[8] = 0xE0;
	SendBuf[9] = 0xAF;
	SendBuf[10] = 0xED;
	
	// 清空当前socket缓存
	CleanSocketBuff(p->serverFd);
	
	// 发送打包数据
	rtn = sendto(p->serverFd, &SendBuf, SendDataLen, 0, (sockaddr *)&p->clientAddr, p->addrLen);
	if (rtn < 0 || SendDataLen != rtn)
	{
		rtn = ERR_COMMUNICATION_SENDTO;
		goto LABEL_EXIT;
	}
	
	
LABEL_EXIT:
	pthread_mutex_unlock(&p->mutexLock);
	return rtn;
}

short CM_SCA_Controller::SendBrakeFalse()
{
	short rtn = ERR_NONE;

	unsigned short ip = 1;
	unsigned char SendBuf[12];
	EcuRelatedInfo *p = &g_ecuRelatedInfo[ip];
	short SendDataLen = 11;

	pthread_mutex_lock(&p->mutexLock);
	
	// "ee 00 c1 00 03 31 01 00 21 9f ed"
	
	SendBuf[0] = 0xEE;
	SendBuf[1] = 0x00;
	SendBuf[2] = 0xC1;
	SendBuf[3] = 0x00;
	SendBuf[4] = 0x03;
	SendBuf[5] = 0x31;
	SendBuf[6] = 0x01;
	SendBuf[7] = 0x00;
	SendBuf[8] = 0x21;
	SendBuf[9] = 0x9F;
	SendBuf[10] = 0xED;
	
	// 清空当前socket缓存
	CleanSocketBuff(p->serverFd);
	
	// 发送打包数据
	rtn = sendto(p->serverFd, &SendBuf, SendDataLen, 0, (sockaddr *)&p->clientAddr, p->addrLen);
	if (rtn < 0 || SendDataLen != rtn)
	{
		rtn = ERR_COMMUNICATION_SENDTO;
		goto LABEL_EXIT;
	}
	
	usleep(100);
	
	// "ee 00 c1 00 03 31 02 00 21 6f ed"
	SendBuf[0] = 0xEE;
	SendBuf[1] = 0x00;
	SendBuf[2] = 0xC1;
	SendBuf[3] = 0x00;
	SendBuf[4] = 0x03;
	SendBuf[5] = 0x31;
	SendBuf[6] = 0x02;
	SendBuf[7] = 0x00;
	SendBuf[8] = 0x21;
	SendBuf[9] = 0x6F;
	SendBuf[10] = 0xED;
	
	// 清空当前socket缓存
	CleanSocketBuff(p->serverFd);
	
	// 发送打包数据
	rtn = sendto(p->serverFd, &SendBuf, SendDataLen, 0, (sockaddr *)&p->clientAddr, p->addrLen);
	if (rtn < 0 || SendDataLen != rtn)
	{
		rtn = ERR_COMMUNICATION_SENDTO;
		goto LABEL_EXIT;
	}
	
	
LABEL_EXIT:
	pthread_mutex_unlock(&p->mutexLock);
	return rtn;
}
