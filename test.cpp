#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <iostream>
#include <sys/time.h>
#include "CM_SCA_Controller.h"

#define RED "\033[31m"
#define RESET "\033[0m"
#define Pi 3.1415926535

extern CM_SCA_Controller SCACtrller;

int test_CM_GetProfilePVC(CM_SCA_Controller &SCACtrller, short axis);
int test_CircleGetPVC(CM_SCA_Controller &SCACtrller, vector<short> Axis);

int main()
{
	int i, j;
	short rtn;
	bool status = false;
	double value;
	long val;
	//char *pVersion;
	char SwVersion[12] = {0};
	char HwVersion[12] = {0}; // 最大的版本号是：255.255.255，so 最大值定为12
	vector<short> Axis;
	vector<double> pos;
	long time;
	// CM_SCA_Controller SCACtrller;
	ConfigParm Cparm;
	SafeParm Sparm;

	double pos1 = 0.0, vel1 = 0.0, cur1 = 0.0;

	while (1)
	{
		rtn = SCACtrller.CM_GetSWVersion(SwVersion);
		cout << "GetSWVersion = " << rtn << ", SwVersion = " << SwVersion << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR GetSWVersion!!!" << RESET << endl;
		}

		/*
		rtn = SCACtrller.CM_Connect();
		cout << "Connect = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR Connect!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_GetAllAxisID(Axis);
		cout << "GetAllAxisID = " << rtn << ", AxisID = ";
		for (i = 0; i < Axis.size(); i++)
		{
			cout << Axis.at(i) << " ";
		}
		cout << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR GetAllAxisID!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_InitAll();
		cout << "InitAll = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR InitAll!!!" << RESET << endl;
		}

		// rtn = SCACtrller.CM_SetBrakeState(7, 0);
		// rtn = SCACtrller.CM_SetBrakeState(5, 0);
		// rtn = SCACtrller.CM_SetBrakeState(6, 0);
		// usleep(5000);

		for (i = 0; i < Axis.size(); i++)
		{
			rtn = SCACtrller.CM_SetProfilePositionMode(i);
		}



		rtn = SCACtrller.CM_StartGetPVCTimer(true);	

		// while (true)
		// {
		// 	sleep(1);
		// }
		*/
/*----------------------------------test for this --------------------*/
		rtn = SCACtrller.CM_InitController();
		if (0 != rtn)
		{
			cout << RED << "ERR CM_InitController!!!, rtn = " << rtn << RESET << endl;
			return rtn;
		}

		rtn = SCACtrller.CM_GetAllAxisID(Axis);
		cout << "GetAllAxisID = " << rtn << ", AxisID = ";
		for (i = 0; i < Axis.size(); i++)
		{
			cout << Axis.at(i) << " ";
		}

		cout << endl;

		rtn = SCACtrller.CM_GetProfileVoltage(7, value);
		cout << "CM_GetProfileVoltage = " << value << endl;

/*---------------------------------for the imu data ----------------------------------*/
		// for (i=0; i<10; i++)
		// {
		// 	// IMU
		// 	double w, x, y, z;
		// 	double xa, ya, za;
		// 	int pres;
		// 	rtn = SCACtrller.CM_GetImuData(w, x, y, z, xa, ya, za, pres);
		// 	if (0 != rtn)
		// 	{
		// 		cout << "ERR CM_GetImuData!!!, rtn = " << rtn << endl;
		// 		return rtn;
		// 	}
		// 	else
		// 	{
		// 		cout << "x=" << x << ",y=" << y << ",z=" << z << ", w=" << w;
		// 		cout << ", xa=" << xa << ",ya=" << ya << ",za=" << za << ", pres=" << pres << endl;
		// 	}
		// }

/*---------------------------------for the imu data ----------------------------------*/
		// 抱闸设置
		// rtn = SCACtrller.SendBrakeFalse();
		// rtn = SCACtrller.SendBrakeTrue();

		//////////////////////////////////////////////////////////////////////////////
		// {
		// 	// 测试：CM_SetPosition(vector<short> axis, vector<double> pos)

		// 	vector<double> leftPosition(7);
		// 	vector<double> rightPosition(7);
		// 	double rtnPos;
		// 	vector<double> getPos(7);
		// 	double cnt1 = 0.0;
		// 	vector<short> leftArm, rightArm;

		// 	for (i = 11; i < 18; i++)
		// 	{
		// 		leftArm.push_back(i);
		// 	}
		// 	for (i = 18; i < 25; i++)
		// 	{
		// 		rightArm.push_back(i);
		// 	}

		// 	for (i = 0; i < 7; i++)
		// 	{
		// 		rightPosition.at(i) = 0.0;
		// 		leftPosition.at(i) = 0.0;
		// 	}

		// 	rtn = SCACtrller.CM_SetPosition(leftArm, leftPosition);
		// 	rtn = SCACtrller.CM_SetPosition(rightArm, rightPosition);

		// 	sleep(3);

		// 	for (i = 0; i < Axis.size(); i++)
		// 	{
		// 		rtn = SCACtrller.CM_SetPositionMode(Axis.at(i));
		// 	}
		// 	while (1)
		// 	{
		// 		//test
		// 		static int nCount = 0;
		// 		int sleepTime = 0;
		// 		const int Interval = 5000;
		// 		timeval timeStart, timeEnd, timeEnd1;
		// 		double TimeVal = 0;
		// 		gettimeofday(&timeStart, NULL);
		// 		std::vector<short> jointGroup;
		// 		std::vector<double> jointGroupPos;
		// 		//end

		// 		for (i = 0; i < Axis.size(); i++)
		// 		{
		// 			rtn = SCACtrller.CM_GetProfilePVC(Axis.at(i), pos1, vel1, cur1);
		// 			cout << "Axis(" << i << "), pos = " << pos1 << ", rtn = " << rtn <<endl;
		// 		}

		// 		leftPosition.at(0) = 2 * sin(cnt1);
		// 		rightPosition.at(0) = 2 * sin(cnt1);

		// 		leftPosition.at(1) = 2 * cos(cnt1 + Pi) + 2; //left
		// 		rightPosition.at(1) = 2 * cos(cnt1) - 2;	 //right

		// 		leftPosition.at(2) = 1 * sin(cnt1);
		// 		rightPosition.at(2) = 1 * sin(cnt1);

		// 		leftPosition.at(3) = 2 * cos(cnt1) - 2;		  //left
		// 		rightPosition.at(3) = 2 * cos(cnt1 - Pi) + 2; //right

		// 		leftPosition.at(4) = 1 * sin(cnt1);
		// 		rightPosition.at(4) = 1 * sin(cnt1);

		// 		leftPosition.at(5) = 1 * sin(cnt1);
		// 		rightPosition.at(5) = 1 * sin(cnt1);

		// 		leftPosition.at(6) = 1 * sin(cnt1);
		// 		rightPosition.at(6) = 1 * sin(cnt1);

		// 		rtn = SCACtrller.CM_SetPosition(leftArm, leftPosition);
		// 		rtn = SCACtrller.CM_SetPosition(rightArm, rightPosition);

		// 		jointGroup.clear();
		// 		jointGroupPos.clear();
		// 		for (i = 5; i < 11; i++)
		// 		{
		// 			jointGroup.push_back(i);
		// 			jointGroupPos.push_back(0.0);
		// 		}
		// 		rtn = SCACtrller.CM_SetPosition(jointGroup, jointGroupPos);
		// 		jointGroup.clear();
		// 		jointGroupPos.clear();
		// 		for (i = 25; i < 30; i++)
		// 		{
		// 			jointGroup.push_back(i);
		// 			jointGroupPos.push_back(0.0);
		// 		}
		// 		rtn = SCACtrller.CM_SetPosition(jointGroup, jointGroupPos);
		// 		jointGroup.clear();
		// 		jointGroupPos.clear();
		// 		for (i = 30; i < 35; i++)
		// 		{
		// 			jointGroup.push_back(i);
		// 			jointGroupPos.push_back(0.0);
		// 		}
		// 		rtn = SCACtrller.CM_SetPosition(jointGroup, jointGroupPos);

		// 		cnt1 += 0.01;

		// 		gettimeofday(&timeEnd, NULL);
		// 		TimeVal = (timeEnd.tv_sec - timeStart.tv_sec) * 1000000 + (double)(timeEnd.tv_usec - timeStart.tv_usec);

		// 		if (TimeVal < 5000 && cnt1 != 0.0)
		// 		{
		// 			usleep(5000 - TimeVal);
		// 		}
		// 		//test
		// 		gettimeofday(&timeEnd1, NULL);
		// 		TimeVal = (timeEnd1.tv_sec - timeStart.tv_sec) * 1000000 + (double)(timeEnd1.tv_usec - timeStart.tv_usec);
		// 		sleepTime = TimeVal - Interval;
		// 		if (sleepTime > 0 && TimeVal > 6000)
		// 		{
		// 			nCount++;
		// 			cout << "**********************************************" << endl;
		// 			cout << "No. " << nCount << ", TimeVal = " << TimeVal << endl;
		// 			cout << "**********************************************" << endl;
		// 		}
		// 	}
		// }

		//////////////////////////////////////////////////////////////////////////////

	
		{
			for (i = 2; i < 4; i++)
			{
				rtn = SCACtrller.CM_SetPosition(i, 0.00);
			}

			usleep(5000);
		}

		for (i = 0; i < Axis.size(); i++)
		{
			rtn = SCACtrller.CM_SetProfilePositionMode(Axis.at(i));
		}

		sleep(1);

		for (i = 0; i < Axis.size(); i++)
		{
			rtn = SCACtrller.CM_SetPositionMode(Axis.at(i));
		}

		// rtn = SCACtrller.CM_SetPosition(19, (double)-0.5);
		// cout << "SetPosition = " << rtn << endl;
		// if (0 != rtn)
		// {
		// 	cout << RED << "ERR SetPosition!!!" << RESET << endl;
		// }

		//////////////////////////////////////////////////////////////////////////////

		// 设置Homing的流程如下：
		{
				//cout  <<RED<< "the value = " << value << endl;
			rtn = SCACtrller.CM_SetHomingMode(Axis.at(1));
			rtn = SCACtrller.CM_GetProfilePosition(Axis.at(1), value);

			// rtn = SCACtrller.CM_SetHomingMode(Axis.at(1));
			// rtn = SCACtrller.CM_SetProfilePositionMode(9);
			// rtn = SCACtrller.CM_SetPosition(9, 0.0);
			// sleep(1);

			// rtn = SCACtrller.CM_GetProfilePosition(9, value);

			// rtn = SCACtrller.CM_SetSoftLimitValue(9, -125.5, 1.5);
			// rtn = SCACtrller.CM_SaveParm(9);

			double NSoftLimit, PSoftLimit;
			rtn = SCACtrller.CM_GetSoftLimitValue(Axis.at(1), NSoftLimit, PSoftLimit);

			rtn = SCACtrller.CM_SetHomingMode(Axis.at(1), 2);
			if (0 != rtn)
			{
				cout << RED << "ERR CM_SetHomingMode!!!" << RESET << endl;
			}

			rtn = SCACtrller.CM_GetSoftLimitValue(Axis.at(1), NSoftLimit, PSoftLimit);

			rtn = SCACtrller.CM_GetProfilePosition(Axis.at(1), value);
			if (0 != rtn)
			{
				cout << RED << "ERR CM_GetProfilePosition!!!" << RESET << endl;
			}
				cout <<  " the set zeros value = " << value << endl;
			rtn = SCACtrller.CM_Zeros(Axis.at(1), value);
			if (0 != rtn)
			{
				cout << RED << "ERR CM_Zeros!!!" << RESET << endl;
			}

			rtn = SCACtrller.CM_SetProfilePositionMode(Axis.at(1));
			if (0 != rtn)
			{
				cout << RED << "ERR CM_SetProfilePositionMode!!!" << RESET << endl;
			}

			rtn = SCACtrller.CM_GetProfilePosition(Axis.at(1), value);
			if (0 != rtn)
			{
				cout << RED << "ERR CM_GetProfilePosition!!!" << RESET << endl;
			}

			cout << "value = " << value << endl;
		}

		//////////////////////////////////////////////////////////////////////////////

		rtn = SCACtrller.CM_SetPosition(Axis.at(1), (double)0.5729);
		//rtn = SCACtrller.CM_SetPosition(Axis.at(0), (double)0);
		cout << "SetPosition = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR SetPosition!!!" << RESET << endl;
		}

		sleep(2);

		rtn = SCACtrller.CM_GetProfilePVC(Axis.at(0), pos1, vel1, cur1);

		cout << "SetPosition = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR SetPosition!!!" << RESET << endl;
		}

		// 2.a
		// test_CM_GetProfilePVC(SCACtrller, Axis.at(1));

		//
//		test_CircleGetPVC(SCACtrller, Axis);

		rtn = SCACtrller.CM_InitAxis(Axis);
		cout << "InitAxis = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR InitAxis!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_GetHWVersion(2, HwVersion);
		cout << "GetHWVersion = " << rtn << ", HwVersion = " << HwVersion << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR GetHWVersion!!!" << RESET << endl;
		}

		//softlimit
		rtn = SCACtrller.CM_SetSoftLimitStatus(Axis.at(0), 1);
		cout << "SetSoftLimitStatus = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR SetSoftLimitStatus!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_SaveParm(Axis.at(0));
		cout << "SaveParm = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR SaveParm!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_SetSoftLimitStatus(Axis.at(1), 1);
		cout << "SetSoftLimitStatus = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR SetSoftLimitStatus!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_SaveParm(Axis.at(1));
		cout << "SaveParm = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR SaveParm!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_GetSoftLimitStatus(Axis.at(1), val);
		cout << "GetSoftLimitStatus = " << rtn << ", val = " << val << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR GetSoftLimitStatus!!!" << RESET << endl;
		}

		// 2.a
		//
		// test_CircleGetPVC(SCACtrller, Axis);

		//test_CM_GetProfilePVC(SCACtrller, Axis.at(1));

		//ConfigParm
		rtn = SCACtrller.CM_GetConfigParm(Axis.at(1), &Cparm);
		cout << "GetConfigParm = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR GetConfigParm!!!" << RESET << endl;
		}
	Cparm.CurInteg = 0;
	Cparm.CurProp =0 ;
	Cparm.FilterCStatus =true;
	Cparm.VelInteg = 0;
	Cparm.VelProp =0;
	Cparm.PosInteg =0;
	Cparm.PosProp =0 ;
	Cparm.FilterVStatus =false;
	Cparm.FilterPStatus = false;
	Cparm.FilterCValue =0;
	Cparm.FilterPValue =0;
	Cparm.FilterVValue =0;
		rtn = SCACtrller.CM_SetConfigParm(Axis.at(1), &Cparm);
		cout << "SetConfigParm = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR SetConfigParm!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_SaveParm(Axis.at(1));
		cout << "SaveParm = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR SaveParm!!!" << RESET << endl;
		}

		if (rtn == 0)
		{
			rtn = SCACtrller.CM_GetSafeParm(Axis.at(1), &Sparm);
			cout << "GetSafeParm = " << rtn << endl;
			if (0 != rtn)
			{
				cout << RED << "ERR GetSafeParm!!!" << RESET << endl;
			}

			rtn = SCACtrller.CM_SetSafeParm(Axis.at(1), &Sparm);
			cout << "SetSafeParm = " << rtn << endl;
			if (0 != rtn)
			{
				cout << RED << "ERR SetSafeParm!!!" << RESET << endl;
			}

			rtn = SCACtrller.CM_SaveParm(Axis.at(1));
			cout << "SaveParm = " << rtn << endl;
			if (0 != rtn)
			{
				cout << RED << "ERR SaveParm!!!" << RESET << endl;
			}

			rtn = SCACtrller.CM_SetPositionMode(Axis.at(1));
			cout << "SetPositionMode = " << rtn << endl;
			if (0 != rtn)
			{
				cout << RED << "ERR SetPositionMode!!!" << RESET << endl;
			}

			rtn = SCACtrller.CM_SetPositionMode(Axis.at(1));
			cout << "SetPositionMode = " << rtn << endl;
			if (0 != rtn)
			{
				cout << RED << "ERR SetPositionMode!!!" << RESET << endl;
			}
		}

		rtn = SCACtrller.CM_GetActuatorT(Axis.at(1), value);
		cout << "GetActuatorT = " << rtn << ", ActuatorT = " << value << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR GetActuatorT!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_GetDriverT(Axis.at(1), value);
		cout << "GetActuatorT = " << rtn << ", DriverT = " << value << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR GetActuatorT!!!" << RESET << endl;
		}

		//profile pos mode
		rtn = SCACtrller.CM_SetProfilePositionAcc(Axis.at(1), 1200);
		cout << "SetProfilePositionAcc = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR SetProfilePositionAcc!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_SetProfilePositionVel(Axis.at(1), 1000);
		cout << "SetProfilePositionVel = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR SetProfilePositionVel!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_SetProfilePositionDec(Axis.at(1), -1200);
		cout << "SetProfilePositionDec = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR SetProfilePositionDec!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_SaveParm(Axis.at(1));
		cout << "SaveParm = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR SaveParm!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_SetProfilePositionAcc(Axis.at(1), 1200);
		cout << "SetProfilePositionAcc = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR SetProfilePositionAcc!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_SetProfilePositionVel(Axis.at(1), 1000);
		cout << "SetProfilePositionVel = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR SetProfilePositionVel!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_SetProfilePositionDec(Axis.at(1), -1200);
		cout << "SetProfilePositionDec = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR SetProfilePositionDec!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_SaveParm(Axis.at(1));
		cout << "SaveParm = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR SaveParm!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_GetProfilePositionAcc(Axis.at(1), value);
		cout << "GetProfilePositionAcc = " << rtn << ", Acc = " << value << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR GetProfilePositionAcc!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_GetProfilePositionVel(Axis.at(1), value);
		cout << "GetProfilePositionVel = " << rtn << ", Vel = " << value << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR GetProfilePositionVel!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_GetProfilePositionDec(Axis.at(1), value);
		cout << "GetProfilePositionDec = " << rtn << ", Dec = " << value << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR GetProfilePositionDec!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_GetStatus(Axis.at(1), val);
		cout << "GetStatus = " << rtn << ", Status = " << val << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR GetStatus!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_SetProfilePositionMode(Axis.at(1));
		cout << "SetProfilePositionMode = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR SetProfilePositionMode!!!" << RESET << endl;
		}

		// //test homing
		// rtn = SCACtrller.CM_SetProfilePositionMode(2);
		// cout << "SetProfilePositionMode = " << rtn << endl;
		// if(0 != rtn)
		// {
		// 	cout << RED << "ERR SetProfilePositionMode!!!" << RESET << endl;
		// }
		// rtn = SCACtrller.CM_GetProfilePosition(2, value);
		// cout << "GetProfilePosition = " << rtn << ", Pos = " << value << endl;
		// if(0 != rtn)
		// {
		// 	cout << RED << "ERR GetProfilePosition!!!" << RESET << endl;
		// }
		// rtn = SCACtrller.CM_SetPosition(2, 1.0);
		// cout << "SetPosition = " << rtn << endl;
		// if(0 != rtn)
		// {
		// 	cout << RED << "ERR SetPosition!!!" << RESET << endl;
		// }
		// sleep(2);
		// rtn = SCACtrller.CM_GetProfilePosition(2, value);
		// cout << "GetProfilePosition = " << rtn << ", Pos = " << value << endl;
		// if(0 != rtn)
		// {
		// 	cout << RED << "ERR GetProfilePosition!!!" << RESET << endl;
		// }
		// rtn = SCACtrller.CM_SetHomingMode(2);
		// cout << "SetHomingMode = " << rtn << endl;
		// if(0 != rtn)
		// {
		// 	cout << RED << "ERR SetHomingMode!!!" << RESET << endl;
		// }
		// rtn = SCACtrller.CM_GetProfileMode(2, val);
		// cout << "GetProfileMode = " << rtn << ", Mode = " << val << endl;
		// if(0 != rtn)
		// {
		// 	cout << RED << "ERR GetProfileMode!!!" << RESET << endl;
		// }
		// rtn = SCACtrller.CM_Zeros(2);
		// cout << "Zeros = " << rtn << endl;
		// if(0 != rtn)
		// {
		// 	cout << RED << "ERR Zeros!!!" << RESET << endl;
		// }
		// rtn = SCACtrller.CM_SaveParm(2);
		// cout << "SaveParm = " << rtn << endl;
		// if(0 != rtn)
		// {
		// 	cout << RED << "ERR SaveParm!!!" << RESET << endl;
		// }
		// rtn = SCACtrller.CM_GetProfilePosition(2, value);
		// cout << "GetProfilePosition = " << rtn << ", Pos = " << value << endl;
		// if(0 != rtn)
		// {
		// 	cout << RED << "ERR GetProfilePosition!!!" << RESET << endl;
		// }
		// rtn = SCACtrller.CM_GetSafeParm(2, &Sparm);
		// cout << "GetSafeParm = " << rtn << endl;
		// if(0 != rtn)
		// {
		// 	cout << RED << "ERR GetSafeParm!!!" << RESET << endl;
		// }
		// rtn = SCACtrller.CM_SetProfilePositionMode(2);
		// cout << "SetProfilePositionMode = " << rtn << endl;
		// if(0 != rtn)
		// {
		// 	cout << RED << "ERR SetProfilePositionMode!!!" << RESET << endl;
		// }

		rtn = SCACtrller.CM_SetProfilePositionMode(Axis.at(1));
		cout << "SetProfilePositionMode = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR SetProfilePositionMode!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_GetProfileMode(Axis.at(1), val);
		cout << "GetProfileMode = " << rtn << ", Mode = " << val << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR GetProfileMode!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_GetProfilePosition(Axis.at(1), value);
		cout << "GetProfilePosition = " << rtn << ", Pos = " << value << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR GetProfilePosition!!!" << RESET << endl;
		}

		for (i = 0; i < 5; i++)
		{
			rtn = SCACtrller.CM_SetPosition(Axis.at(1), (double)0);
			cout << "SetPosition = " << rtn << endl;
			if (0 != rtn)
			{
				cout << RED << "ERR SetPosition!!!" << RESET << endl;
			}
			rtn = SCACtrller.CM_SetPosition(Axis.at(1), (long)0);
			cout << "SetPosition = " << rtn << endl;
			if (0 != rtn)
			{
				cout << RED << "ERR SetPosition!!!" << RESET << endl;
			}
			sleep(2);

			rtn = SCACtrller.CM_SetPosition(Axis.at(1), (double)(-9));
			cout << "SetPosition = " << rtn << endl;
			if (0 != rtn)
			{
				cout << RED << "ERR SetPosition!!!" << RESET << endl;
			}
			rtn = SCACtrller.CM_SetPosition(Axis.at(1), (long)(-90000));
			cout << "SetPosition = " << rtn << endl;
			if (0 != rtn)
			{
				cout << RED << "ERR SetPosition!!!" << RESET << endl;
			}
			sleep(2);
		}

		rtn = SCACtrller.CM_SetPosition(Axis.at(1), (double)0);
		cout << "SetPosition = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR SetPosition!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_GetProfilePosition(Axis.at(1), value);
		cout << "GetProfilePosition = " << rtn << ", Pos = " << value << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR GetProfilePosition!!!" << RESET << endl;
		}

		usleep(300000);

		rtn = SCACtrller.CM_Stop(Axis.at(1), 1);
		cout << "Stop = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR Stop!!!" << RESET << endl;
		}
		sleep(3);
		rtn = SCACtrller.CM_GetProfilePosition(Axis.at(1), value);
		cout << "GetProfilePosition = " << rtn << ", Pos = " << value << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR GetProfilePosition!!!" << RESET << endl;
		}

		time = 1000;
		pos.clear();
		pos.push_back(0);
		pos.push_back(-5);
		rtn = SCACtrller.CM_SynMultiAxisMotion(Axis, pos, time);
		cout << "SynMultiAxisMotion = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR SynMultiAxisMotion!!!" << RESET << endl;
		}
		sleep(2);
		rtn = SCACtrller.CM_GetProfilePosition(Axis.at(1), value);
		cout << "GetProfilePosition = " << rtn << ", Pos = " << value << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR GetProfilePosition!!!" << RESET << endl;
		}
		rtn = SCACtrller.CM_GetProfilePosition(Axis.at(1), value);
		cout << "GetProfilePosition = " << rtn << ", Pos = " << value << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR GetProfilePosition!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_SetPosition(Axis.at(1), (long)0);
		cout << "SetPosition = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR SetPosition!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_SetPosition(Axis.at(1), (long)0);
		cout << "SetPosition = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR SetPosition!!!" << RESET << endl;
		}

		// rtn = SCACtrller.CM_GetPosition(Axis.at(0), value);
		// cout << "GetPosition = " << rtn << ", Pos = " << value << endl;
		// if(0 != rtn)
		// {
		// 	cout << RED << "ERR GetPosition!!!" << RESET << endl;
		// }

		sleep(3);

		rtn = SCACtrller.CM_GetProfilePosition(Axis.at(0), value);
		cout << "GetProfilePosition = " << rtn << ", Pos = " << value << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR GetProfilePosition!!!" << RESET << endl;
		}

		//pos mode
		rtn = SCACtrller.CM_SetPositionMode(Axis.at(0));
		cout << "SetPositionMode = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR SetPositionMode!!!" << RESET << endl;
		}
		rtn = SCACtrller.CM_SetPositionMode(Axis.at(1));
		cout << "SetPositionMode = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR SetPositionMode!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_GetProfileMode(Axis.at(0), val);
		cout << "GetProfileMode = " << rtn << ", Mode = " << val << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR GetProfileMode!!!" << RESET << endl;
		}

		//for(j=0; j<2; j++)
		double cnt1 = 0.0;
		double pos = 0.0;
		double k = 1.0;
		// FILE *fp;
		// fp = fopen("/home/derek/XR1_WS/src/src/XR1_Controller/pos.txt", "w+");
		// while (1)
		// {
		// 	//pos = sin(cnt1);
		// 	pos += 0.01 * k;
		// 	if (pos >= 1.0 || pos <= 0.0)
		// 	{
		// 		k = -k;
		// 	}
		// 	rtn = SCACtrller.CM_SetPosition(Axis.at(0), pos);
		// 	//cout << "SetPosition = " << rtn << endl;
		// 	if (0 != rtn)
		// 	{
		// 		cout << RED << "ERR SetPosition!!!" << RESET << endl;
		// 	}
		// 	rtn = SCACtrller.CM_SetPosition(Axis.at(1), pos);
		// 	//cout << "SetPosition = " << rtn << endl;
		// 	if (0 != rtn)
		// 	{
		// 		cout << RED << "ERR SetPosition!!!" << RESET << endl;
		// 	}
		// 	rtn = SCACtrller.CM_GetProfilePosition(Axis.at(1), value);
		// 	cout << "GetProfilePosition = " << rtn << ", setPos = " << pos << ", getPos = " << value << endl;
		// 	if (0 != rtn)
		// 	{
		// 		cout << RED << "ERR GetProfilePosition!!!" << RESET << endl;
		// 	}

		// 	fprintf(fp, "%f %f\n", pos, value);
		// 	usleep(1000);

		// 	cnt1 += 0.01;
		// }

		rtn = SCACtrller.CM_GetProfilePosition(Axis.at(0), value);
		cout << "GetProfilePosition = " << rtn << ", Pos = " << value << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR GetProfilePosition!!!" << RESET << endl;
		}

		sleep(2);

		//vel mode
		rtn = SCACtrller.CM_SetVelocityMode(Axis.at(1));
		cout << "SetVelocityMode = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR SetVelocityMode!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_GetProfileMode(Axis.at(1), val);
		cout << "GetProfileMode = " << rtn << ", Mode = " << val << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR GetProfileMode!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_SetVelocity(Axis.at(1), -100.0);
		cout << "SetVelocity = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR SetVelocity!!!" << RESET << endl;
		}

		usleep(50000);

		rtn = SCACtrller.CM_Stop(Axis.at(1), 0);
		cout << "Stop = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR Stop!!!" << RESET << endl;
		}

		// rtn = SCACtrller.CM_GetVelocity(Axis.at(1), value);
		// cout << "GetVelocity = " << rtn << ", Vel = " << value << endl;
		// if(0 != rtn)
		// {
		// 	cout << RED << "ERR GetVelocity!!!" << RESET << endl;
		// }

		rtn = SCACtrller.CM_GetProfileVelocity(Axis.at(1), value);
		cout << "GetProfileVelocity = " << rtn << ", Vel = " << value << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR GetProfileVelocity!!!" << RESET << endl;
		}

		sleep(3);

		rtn = SCACtrller.CM_SetVelocity(Axis.at(1), (long)0);
		cout << "SetVelocity = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR SetVelocity!!!" << RESET << endl;
		}

		sleep(1);

		rtn = SCACtrller.CM_GetStatus(Axis.at(1), val);
		cout << "GetStatus = " << rtn << ", Status = " << val << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR GetStatus!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_GetAlarmInfo(Axis.at(0), val);
		cout << "GetAlarmInfo = " << rtn << ", Alarm = " << val << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR GetAlarmInfo!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_ClearAlarm(Axis.at(0));
		cout << "ClearAlarm = " << rtn << endl;
		if (0 < rtn)
		{
			cout << RED << "ERR ClearAlarm!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_GetStatus(Axis.at(0), val);
		cout << "GetStatus = " << rtn << ", Status = " << val << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR GetStatus!!!" << RESET << endl;
		}

		//profile vel mode
		rtn = SCACtrller.CM_GetProfilePosition(Axis.at(1), value);
		cout << "GetProfilePosition = " << rtn << ", Pos = " << value << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR GetProfilePosition!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_GetProfileMode(Axis.at(1), val);
		cout << "GetProfileMode = " << rtn << ", Mode = " << val << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR GetProfileMode!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_SetVelocity(Axis.at(1), (double)300);
		cout << "SetVelocity = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR SetVelocity!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_GetProfileVelocity(Axis.at(1), value);
		cout << "GetProfileVelocity = " << rtn << ", Vel = " << value << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR GetProfileVelocity!!!" << RESET << endl;
		}

		sleep(2);

		rtn = SCACtrller.CM_SetVelocity(Axis.at(1), (double)0);
		cout << "SetVelocity = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR SetVelocity!!!" << RESET << endl;
		}

		sleep(1);

		rtn = SCACtrller.CM_ClearAlarm(Axis.at(1));
		cout << "ClearAlarm = " << rtn << endl;
		if (0 < rtn)
		{
			cout << RED << "ERR ClearAlarm!!!" << RESET << endl;
		}

		//current mode
		rtn = SCACtrller.CM_GetProfilePosition(Axis.at(0), value);
		cout << "GetProfilePosition = " << rtn << ", Pos = " << value << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR GetProfilePosition!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_SetCurrentMode(Axis.at(0));
		cout << "SetCurrentMode = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR SetCurrentMode!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_SetCurrentMode(Axis.at(1));
		cout << "SetCurrentMode = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR SetCurrentMode!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_GetProfileMode(Axis.at(0), val);
		cout << "GetProfileMode = " << rtn << ", Mode = " << val << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR GetProfileMode!!!" << RESET << endl;
		}

		// //test current loop
		// rtn = SCACtrller.CM_SetSoftLimitStatus(Axis.at(0), 0);
		// cout << "SetSoftLimitStatus = " << rtn << endl;
		// if(0 != rtn)
		// {
		// 	cout << RED << "ERR SetSoftLimitStatus!!!" << RESET << endl;
		// }
		// rtn = SCACtrller.CM_GetSoftLimitStatus(Axis.at(0), val);
		// cout << "GetSoftLimitStatus = " << rtn << ", val = " << val << endl;
		// if(0 != rtn)
		// {
		// 	cout << RED << "ERR GetSoftLimitStatus!!!" << RESET << endl;
		// }

		// rtn = SCACtrller.CM_SaveParm(Axis.at(0));
		// cout << "SaveParm = " << rtn << endl;
		// if(0 != rtn)
		// {
		// 	cout << RED << "ERR SaveParm!!!" << RESET << endl;
		// }

		// FILE *fp;
		// double q = 0.0, sendC;
		// int cnt1;
		// cnt1=0;
		// q=0;
		// fp = fopen("currentTest5.txt", "w+");
		// while(cnt1 < 2000)
		// {
		// 	rtn = SCACtrller.CM_GetProfileVelocity(Axis.at(0), value);
		// 	cout << "GetProfileVelocity = " << rtn << ", Vel = " << value << endl;
		// 	if(0 != rtn)
		// 	{
		// 		cout << RED << "ERR GetProfileVelocity!!!" << RESET << endl;
		// 	}
		// 	sendC = 5*sin(q);
		// 	rtn = SCACtrller.CM_SetCurrent(Axis.at(0), sendC);
		// 	rtn = SCACtrller.CM_GetCurrent(Axis.at(0), value);
		// 	//cout << "CM_GetCurrent = " << rtn << ", Cur = " << value << endl;
		// 	if(0 != rtn)
		// 	{
		// 		cout << RED << "ERR CM_GetCurrent!!!" << RESET << endl;
		// 	}

		// 	cout << sendC - value << " " << cnt1 << endl;
		// 	fprintf(fp, "%f %f\n", sendC, value);
		// 	q += 0.01;
		// 	usleep(5000);
		// 	cnt1++;
		// }
		// fclose(fp);

		// rtn = SCACtrller.CM_Stop(Axis.at(0), 1);
		// cout << "Stop = " << rtn << endl;
		// if(0 != rtn)
		// {
		// 	cout << RED << "ERR Stop!!!" << RESET << endl;
		// }

		// cnt1=0;
		// q=0;
		// fp = fopen("currentTest6.txt", "w+");
		// while(cnt1 < 2000)
		// {
		// 	sendC = 10*sin(q);
		// 	rtn = SCACtrller.CM_SetCurrent(Axis.at(0), sendC);
		// 	rtn = SCACtrller.CM_GetCurrent(Axis.at(0), value);
		// 	//cout << "CM_GetCurrent = " << rtn << ", Cur = " << value << endl;
		// 	if(0 != rtn)
		// 	{
		// 		cout << RED << "ERR CM_GetCurrent!!!" << RESET << endl;
		// 	}
		// 	cout << sendC - value << " " << cnt1 << endl;
		// 	fprintf(fp, "%f %f\n", sendC, value);
		// 	q += 0.01;
		// 	usleep(5000);
		// 	cnt1++;
		// }
		// fclose(fp);

		// rtn = SCACtrller.CM_Stop(Axis.at(0), 1);
		// cout << "Stop = " << rtn << endl;
		// if(0 != rtn)
		// {
		// 	cout << RED << "ERR Stop!!!" << RESET << endl;
		// }

		// rtn = SCACtrller.CM_Stop(Axis.at(0), 1);
		// cout << "Stop = " << rtn << endl;
		// if(0 != rtn)
		// {
		// 	cout << RED << "ERR Stop!!!" << RESET << endl;
		// }

		rtn = SCACtrller.CM_SetCurrent(Axis.at(0), -0.3);
		cout << "SetCurrent = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR SetCurrent!!!" << RESET << endl;
		}
		rtn = SCACtrller.CM_GetCurrent(Axis.at(0), value);
		cout << "CM_GetCurrent = " << rtn << ", Cur = " << value << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR CM_GetCurrent!!!" << RESET << endl;
		}

		usleep(400000);

		rtn = SCACtrller.CM_Stop(Axis.at(0), 1);
		cout << "Stop = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR Stop!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_GetCurrent(Axis.at(0), value);
		cout << "GetProfileCurrent = " << rtn << ", Cur = " << value << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR GetProfileCurrent!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_SetCurrent(Axis.at(0), 0);
		cout << "SetCurrent = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR SetCurrent!!!" << RESET << endl;
		}

		sleep(1);

		// rtn = SCACtrller.CM_GetCurrent(Axis.at(0), value);
		// cout << "GetCurrent = " << rtn << ", Cur = " << value << endl;
		// if(0 != rtn)
		// {
		// 	cout << RED << "ERR GetCurrent!!!" << RESET << endl;
		// }

		rtn = SCACtrller.CM_GetProfilePosition(Axis.at(0), value);
		cout << "GetProfilePosition = " << rtn << ", Pos = " << value << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR GetProfilePosition!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_GetStatus(Axis.at(0), val);
		cout << "GetStatus = " << rtn << ", Status = " << val << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR GetStatus!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_ResetAxis(Axis);
		cout << "ResetAxis = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR ResetAxis!!!" << RESET << endl;
		}
		rtn = SCACtrller.CM_ResetAll();
		cout << "ResetAll = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR ResetAll!!!" << RESET << endl;
		}

		rtn = SCACtrller.CM_CloseAxis(Axis);
		cout << "CloseAxis = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR CloseAxis!!!" << RESET << endl;
		}
	}

	Axis.clear();
	// free(pVersion);

	return 0;
}

int test_CircleGetPVC(CM_SCA_Controller &SCACtrller, vector<short> Axis)
{
	short rtn = 0;
	int i = 0;
	double dPos = 0.0, dVel = 0.0, dCur = 0.0;
	string LOG_NAME = "/home/john/tmp/pvc_log.txt";
	char line[255] = {0};

	FILE *fd = NULL;

	fd = fopen(LOG_NAME.c_str(), "wb");
	if (fd == NULL)
	{
		cout << "open LOG_NAME failue..." << endl;
	}

	for (i = 0; i < Axis.size(); i++)
	{
		rtn = SCACtrller.CM_GetProfilePVC(Axis.at(i), dPos, dVel, dCur);
		sprintf(line, "Axis = %d, pos = %.6lf, vel = %.6lf, cur = %.6lf", Axis.at(i), dPos, dVel, dCur);
		fwrite(line, 1, strlen(line), fd);
	}

	fclose(fd);

	return rtn;
}

/*
 * test the CM_GetProfilePVC function
 */
int test_CM_GetProfilePVC(CM_SCA_Controller &SCACtrller, short axis)
{
	short rtn;
	int i = 0;
	double dPos, dVel, dCur;
	double value;
	struct timeval tv1, tv2;

	rtn = SCACtrller.CM_SetSoftLimitStatus(axis, 0);
	cout << "CM_SetSoftLimitStatus = " << rtn << endl;
	if (0 != rtn)
	{
		cout << RED << "ERR GetSoftLimitStatus!!!" << RESET << endl;
	}

	rtn = SCACtrller.CM_SetVelocityMode(axis);
	cout << "CM_SetVelocityMode = " << rtn << endl;
	if (0 != rtn)
	{
		cout << RED << "ERR CM_SetVelocityMode!!!" << RESET << endl;
	}

	// test range [-2000, 2000]
	rtn = SCACtrller.CM_SetVelocity(axis, 300.00);
	cout << "CM_SetVelocity = " << rtn << endl;
	if (0 != rtn)
	{
		cout << RED << "ERR SetVelocity!!!" << RESET << endl;
	}
	sleep(1);

	// // test the running time of function CM_GetProfilePVC
	// for (i=0; i<10; i++)
	// {
	// 	gettimeofday(&tv1, NULL);
	// 	cout << "*** time 1: sec= " << tv1.tv_sec << " usec = " << tv1.tv_usec << endl;

	// 	rtn = SCACtrller.CM_GetProfilePVC(axis, dPos, dVel, dCur);

	// 	gettimeofday(&tv2, NULL);
	// 	cout << "*** time 2: sec= " << tv2.tv_sec << " usec = " << tv2.tv_usec << endl;
	// 	cout << "*** time 2 - time 1 = " <<  tv2.tv_usec-tv1.tv_usec << endl;
	// }

	rtn = SCACtrller.CM_GetProfilePVC(axis, dPos, dVel, dCur);
	cout << "GetProfilePVC = " << rtn << ", pos = " << dPos << ", vel = " << dVel << ", cur = " << dCur << endl;
	if (0 != rtn)
	{
		cout << RED << "ERR GetProfilePVC!!!" << RESET << endl;
	}

	rtn = SCACtrller.CM_GetProfilePosition(axis, value);
	cout << "GetProfilePosition = " << rtn << ", Pos = " << value << endl;
	if (0 != rtn)
	{
		cout << RED << "ERR GetProfilePosition!!!" << RESET << endl;
	}

	rtn = SCACtrller.CM_GetProfileVelocity(axis, value);
	cout << "GetProfileVelocity = " << rtn << ", Vel = " << value << endl;
	if (0 != rtn)
	{
		cout << RED << "ERR GetProfileVelocity!!!" << RESET << endl;
	}

	rtn = SCACtrller.CM_GetCurrent(axis, value);
	cout << "GetProfileCurrent = " << rtn << ", Cur = " << value << endl;
	if (0 != rtn)
	{
		cout << RED << "ERR CM_GetCurrent!!!" << RESET << endl;
	}
}
