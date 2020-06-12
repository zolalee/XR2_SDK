#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <iostream>
#include <sys/time.h>
#include "CM_SCA_Controller.h"
#include "CM_XR1_Interface.h"

#define RED			"\033[31m"
#define RESET		"\033[0m"
#define Pi          3.14151926535

CM_SCA_Controller Ctrller;
CM_XR1_Interface XR1;

// wxyz
void Quat2EulerZYX(double quat[4], double eul[3])
{
	double qx, qy, qz, qw;
	double aSinInput;
	double norm = 0.0;

	norm = sqrt(quat[0] * quat[0] + quat[1] * quat[1] + quat[2] * quat[2] +
				quat[3] * quat[3]);
	qw = quat[0] / norm;
	qx = quat[1] / norm;
	qy = quat[2] / norm;
	qz = quat[3] / norm;

	aSinInput = -2 * (qx * qz - qw * qy);
	if (aSinInput > 1.0) {
		aSinInput = 1.0;
	} else if (aSinInput < -1.0) {
		aSinInput = -1.0;
	}
	eul[0] =
		atan2(2 * (qx * qy + qw * qz), qw * qw + qx * qx - qy * qy - qz * qz);
	eul[1] = asin(aSinInput);
	eul[2] =
		atan2(2 * (qy * qz + qw * qx), qw * qw - qx * qx - qy * qy + qz * qz);
}

void getLimit(short axis, double vel = 0.5)
{
	int i, j;
	short rtn;
	bool status = false;
	double initPos = 0.0;
	double getPos, getVel, getCur;
	double lastPos;
	double softLimit[2] = {0.0};

	// rtn = XR1.CM_SetJointPos(axis, 0.0);
	if(0 != rtn)
	{
		cout << RED << "ERR CM_SetJointPos!!!" << RESET << endl;
	}
	usleep(3000*1000);

	rtn = XR1.CM_SetJointCtrlMode(axis, VelCtrlMode);
	cout << "CM_SetJointCtrlMode = " << rtn << endl;
	if(0 != rtn)
	{
		cout << RED << "ERR CM_SetJointCtrlMode!!!" << RESET << endl;
	}

	rtn = XR1.CM_GetJointPos(axis, getPos);
	if(0 != rtn)
	{
		cout << RED << "ERR CM_GetJointPos!!!" << RESET << endl;
	}
	initPos = getPos;
	lastPos = getPos;

	rtn = XR1.CM_SetJointVel(axis, fabs(vel));
	if(0 != rtn)
	{
		cout << RED << "ERR CM_SetJointVel!!!" << RESET << endl;
	}
	usleep(500*1000);

	while (1)
	{
		rtn = XR1.CM_GetJointPos(axis, getPos);
		if(0 != rtn)
		{
			cout << RED << "ERR CM_GetJointPos!!!" << RESET << endl;
		}
		rtn = XR1.CM_GetJointVel(axis, getVel);
		if(0 != rtn)
		{
			cout << RED << "ERR CM_GetJointVel!!!" << RESET << endl;
		}
		rtn = XR1.CM_GetJointCur(axis, getCur);
		if(0 != rtn)
		{
			cout << RED << "ERR CM_GetJointCur!!!" << RESET << endl;
		}
		
		if(fabs(getVel) < 0.0001 || fabs(getCur) > 6)
		{
			if(fabs(getVel) < 0.001)
			{
				cout << RED << "check vel touch limit" << endl;
			}
			if(fabs(getCur) > 3)
			{
				cout << RED << "check cur touch limit" << endl;
			}
			softLimit[0] = getPos;
			cout << "getpos = " << getPos << endl;
			rtn = XR1.CM_SetJointCtrlMode(axis, PrfPosCtrlMode);
			cout << "CM_SetJointCtrlMode = " << rtn << endl;
			if(0 != rtn)
			{
				cout << RED << "ERR CM_SetJointCtrlMode!!!" << RESET << endl;
			}
			// todo calculate limit, and back to zero
			rtn = XR1.CM_SetJointPos(axis, initPos);
			usleep(3000*1000);
			break;
		}
		lastPos = getPos;
		usleep(5*1000);
	}


	rtn = XR1.CM_SetJointCtrlMode(axis, VelCtrlMode);
	cout << "CM_SetJointCtrlMode = " << rtn << endl;
	if(0 != rtn)
	{
		cout << RED << "ERR CM_SetJointCtrlMode!!!" << RESET << endl;
	}

	rtn = XR1.CM_GetJointPos(axis, getPos);
	if(0 != rtn)
	{
		cout << RED << "ERR CM_GetJointPos!!!" << RESET << endl;
	}
	lastPos = getPos;

	rtn = XR1.CM_SetJointVel(axis, -fabs(vel));
	if(0 != rtn)
	{
		cout << RED << "ERR CM_SetJointVel!!!" << RESET << endl;
	}
	usleep(500*1000);

	while (1)
	{
		rtn = XR1.CM_GetJointPos(axis, getPos);
		if(0 != rtn)
		{
			cout << RED << "ERR CM_GetJointPos!!!" << RESET << endl;
		}
		rtn = XR1.CM_GetJointVel(axis, getVel);
		if(0 != rtn)
		{
			cout << RED << "ERR CM_GetJointPos!!!" << RESET << endl;
		}
		rtn = XR1.CM_GetJointCur(axis, getCur);
		if(0 != rtn)
		{
			cout << RED << "ERR CM_GetJointPos!!!" << RESET << endl;
		}
		
		if(fabs(getVel) < 0.0001 || fabs(getCur) > 6)
		{
			if(fabs(getVel) < 0.001)
			{
				cout << RED << "check vel touch limit" << endl;
			}
			if(fabs(getCur) > 3)
			{
				cout << RED << "check cur touch limit" << endl;
			}
			softLimit[1] = getPos;
			cout << "getpos = " << getPos << endl;
			rtn = XR1.CM_SetJointCtrlMode(axis, PrfPosCtrlMode);
			cout << "CM_SetJointCtrlMode = " << rtn << endl;
			if(0 != rtn)
			{
				cout << RED << "ERR CM_SetJointCtrlMode!!!" << RESET << endl;
			}
			// todo calculate limit, and back to zero
			rtn = XR1.CM_SetJointPos(axis, initPos);
			usleep(1000*1000);
			break;
		}
		lastPos = getPos;
		usleep(5*1000);
	}
	usleep(1000*1000);
	cout  << "limit = " << softLimit[0] << " " << softLimit[1] << endl;
}

void get6Limit()
{
	int i, j;
	short rtn, value;
	long val;
	double softLimit[2] = {0.0};
	double pos;
	int pres;
	double IMULinearData[3], IMUOrientation[4];
	double eul[3];
	double threshold = 0.001;
	int cnt = 0;

	rtn = Ctrller.CM_SetProfilePositionMode(6);
	usleep(100*1000);
	while(1)
	{
		rtn = Ctrller.CM_GetImuData(0, IMUOrientation[0], IMUOrientation[1], IMUOrientation[2], 
								IMUOrientation[3], IMULinearData[0], IMULinearData[1], IMULinearData[2], pres);
		std::cout << RESET << IMUOrientation[0] << " " << IMUOrientation[1] << " " << IMUOrientation[2] << " " << IMUOrientation[3] << endl;
		// Quat2EulerZYX(IMUOrientation, eul);
		// cout << RESET << eul[0] << " " << eul[1] << " " << eul[2] << endl;
		rtn = Ctrller.CM_GetProfilePosition(6, pos);
		std::cout << RESET << "joint6 pos = " << pos << std::endl;
		if(IMUOrientation[0] > 1.0 || IMUOrientation[1] > 1.0 || IMUOrientation[2] > 1.0 || IMUOrientation[3] > 1.0)
		{
			cnt = 0;
			std::cout << RED << "imu data err" << RESET << std::endl;
			continue;
		}
		else if(IMUOrientation[0] > (sqrt(2.0)/2.0) + threshold)
		{
			cnt = 0;
			std::cout << "decrease pos" << std::endl;
			rtn = Ctrller.CM_SetPosition(6, pos-0.03);
		}
		else if(IMUOrientation[0] < (sqrt(2.0)/2.0) - threshold)
		{
			cnt = 0;
			std::cout << "increase pos" << std::endl;
			rtn = Ctrller.CM_SetPosition(6, pos+0.03);
		}
		else if(IMUOrientation[0] < (sqrt(2.0)/2.0)+threshold && IMUOrientation[0] > (sqrt(2.0)/2.0)-threshold)
		{
			cnt++;
			if(cnt > 10)
			{
				usleep(1000*1000);
				// todo calculate limit, and back to zero
				break;
			}
		}

		usleep(5*1000);
	}
}

void get7Limit()
{
	int i, j;
	short rtn, value;
	long val;
	double softLimit[2] = {0.0};
	double pos;
	int pres;
	double IMULinearData[3], IMUOrientation[4];
	double eul[3], initEul, aveEul;
	double threshold = 0.01;
	int cnt = 0;
	bool corrDir = true;
	int tryCnt = 0;

	rtn = Ctrller.CM_SetProfilePositionMode(7);
	usleep(100*1000);
	aveEul = 0.0;
	for(i=0; i<10;i++)
	{
		rtn = Ctrller.CM_GetImuData(0, IMUOrientation[0], IMUOrientation[1], IMUOrientation[2], 
					IMUOrientation[3], IMULinearData[0], IMULinearData[1], IMULinearData[2], pres);
		if(IMUOrientation[0] > 1.0 || IMUOrientation[1] > 1.0 || IMUOrientation[2] > 1.0 || IMUOrientation[3] > 1.0)
		{
			i--;
		}
		Quat2EulerZYX(IMUOrientation, eul);
		aveEul += eul[1];
	}
	aveEul /= 10.0;
	initEul = aveEul;
	while(1)
	{
		rtn = Ctrller.CM_GetImuData(0, IMUOrientation[0], IMUOrientation[1], IMUOrientation[2], 
								IMUOrientation[3], IMULinearData[0], IMULinearData[1], IMULinearData[2], pres);
		// std::cout << RESET << IMUOrientation[0] << " " << IMUOrientation[1] << " " << IMUOrientation[2] << " " << IMUOrientation[3] << endl;
		Quat2EulerZYX(IMUOrientation, eul);
		// std::cout << RESET << eul[0] << " " << eul[1] << " " << eul[2] << std::endl;
		rtn = Ctrller.CM_GetProfilePosition(7, pos);
		// std::cout << RESET << "joint7 pos = " << pos << std::endl;
		if(IMUOrientation[0] > 1.0 || IMUOrientation[1] > 1.0 || IMUOrientation[2] > 1.0 || IMUOrientation[3] > 1.0)
		{
			cnt = 0;
			std::cout << RED << "imu data err" << RESET << std::endl;
			continue;
		}
		else if(eul[1] < (Pi/2) - threshold)
		{
			cnt = 0;
			if(corrDir)
			{
				tryCnt++;
				std::cout << "decrease pos" << std::endl;
				rtn = Ctrller.CM_SetPosition(7, pos-0.02);
				aveEul = 0.0;
				for(i=0; i<10;i++)
				{
					rtn = Ctrller.CM_GetImuData(0, IMUOrientation[0], IMUOrientation[1], IMUOrientation[2], 
								IMUOrientation[3], IMULinearData[0], IMULinearData[1], IMULinearData[2], pres);
					Quat2EulerZYX(IMUOrientation, eul);
					aveEul += eul[1];
				}
				aveEul /= 10.0;
				if(tryCnt >= 100 && aveEul < initEul)
				{
					std::cout << RED << "wrong dir" << RESET << std::endl;
					tryCnt = 0;
					initEul = aveEul;
					corrDir = false;
					usleep(1000*1000);
				}
			}
			else
			{
				tryCnt++;
				std::cout << "increase pos" << std::endl;
				rtn = Ctrller.CM_SetPosition(7, pos+0.02);
				aveEul = 0.0;
				for(i=0; i<10;i++)
				{
					rtn = Ctrller.CM_GetImuData(0, IMUOrientation[0], IMUOrientation[1], IMUOrientation[2], 
								IMUOrientation[3], IMULinearData[0], IMULinearData[1], IMULinearData[2], pres);
					Quat2EulerZYX(IMUOrientation, eul);
					aveEul += eul[1];
				}
				aveEul /= 10.0;
				if(tryCnt >= 100 && aveEul < initEul)
				{
					std::cout << RED << "wrong dir" << RESET << std::endl;
					tryCnt = 0;
					initEul = aveEul;
					corrDir = true;
					usleep(1000*1000);
				}
			}
		}
		else if(aveEul > 1.55)
		{
			cnt++;
			if(cnt > 10)
			{
				cnt = 0;
				usleep(500*1000);
				// todo calculate limit, and back to zero
				break;
			}
		}
		usleep(50*1000);
	}
}

void get12Limit()
{
	int i, j;
	short rtn;
	bool status = false;
	double getPos, getVel, getCur;
	double lastPos, initPos;
	double softLimit[2] = {0.0};
	
	rtn = XR1.CM_SetJointCtrlMode(12, PrfVelCtrlMode);
	cout << "CM_SetJointCtrlMode = " << rtn << endl;
	if(0 != rtn)
	{
		cout << RED << "ERR CM_SetJointCtrlMode!!!" << RESET << endl;
	}

	rtn = XR1.CM_GetJointPos(12, getPos);
	if(0 != rtn)
	{
		cout << RED << "ERR CM_GetJointPos!!!" << RESET << endl;
	}
	lastPos = getPos;
	initPos = getPos;
	rtn = XR1.CM_SetJointVel(12, 0.5);
	if(0 != rtn)
	{
		cout << RED << "ERR CM_SetJointVel!!!" << RESET << endl;
	}
	usleep(10*1000);
	while (1)
	{
		rtn = XR1.CM_GetJointPos(12, getPos);
		if(0 != rtn)
		{
			cout << RED << "ERR CM_GetJointPos!!!" << RESET << endl;
		}
		// cout << RESET << "getpos = " << getPos << endl;
		// cout << RESET << "fabs(getPos - lastPos) = " << fabs(getPos - lastPos) << endl;
		rtn = XR1.CM_GetJointVel(12, getVel);
		if(0 != rtn)
		{
			cout << RED << "ERR CM_GetJointPos!!!" << RESET << endl;
		}
		rtn = XR1.CM_GetJointCur(12, getCur);
		if(0 != rtn)
		{
			cout << RED << "ERR CM_GetJointPos!!!" << RESET << endl;
		}
		
		// if(fabs(getPos - lastPos) < 0.00005 || fabs(getVel) < 0.05 || fabs(getCur) > 3)
		if(fabs(getVel) < 0.0001 || fabs(getCur) > 6)
		{
			// if(fabs(getPos - lastPos) < 0.0001)
			// {
			// 	cout << RED << "check pos touch limit" << endl;
			// }
			if(fabs(getVel) < 0.001)
			{
				cout << RED << "check vel touch limit" << endl;
			}
			if(fabs(getCur) > 3)
			{
				cout << RED << "check cur touch limit" << endl;
			}
			softLimit[1] = getPos;
			cout << "getpos = " << getPos << endl;
			rtn = XR1.CM_SetJointCtrlMode(12, PrfPosCtrlMode);
			cout << "CM_SetJointCtrlMode = " << rtn << endl;
			if(0 != rtn)
			{
				cout << RED << "ERR CM_SetJointCtrlMode!!!" << RESET << endl;
			}
			// todo calculate limit, and back to zero
			rtn = XR1.CM_SetJointPos(12, initPos);
			usleep(1000*1000);
			break;
		}
		lastPos = getPos;
		usleep(5*1000);
	}
	usleep(1000*1000);
	cout  << "limit = " << softLimit[0] << " " << softLimit[1] << endl;
}

void get19Limit()
{
	int i, j;
	short rtn;
	bool status = false;
	double getPos, getVel, getCur;
	double lastPos, initPos;
	double softLimit[2] = {0.0};

	rtn = XR1.CM_SetJointCtrlMode(19, PrfVelCtrlMode);
	cout << "CM_SetJointCtrlMode = " << rtn << endl;
	if(0 != rtn)
	{
		cout << RED << "ERR CM_SetJointCtrlMode!!!" << RESET << endl;
	}

	rtn = XR1.CM_GetJointPos(19, getPos);
	if(0 != rtn)
	{
		cout << RED << "ERR CM_GetJointPos!!!" << RESET << endl;
	}
	lastPos = getPos;
	initPos = getPos;
	rtn = XR1.CM_SetJointVel(19, -0.5);
	if(0 != rtn)
	{
		cout << RED << "ERR CM_SetJointVel!!!" << RESET << endl;
	}
	usleep(10*1000);
	while (1)
	{
		rtn = XR1.CM_GetJointPos(19, getPos);
		if(0 != rtn)
		{
			cout << RED << "ERR CM_GetJointPos!!!" << RESET << endl;
		}
		// cout << RESET << "getpos = " << getPos << endl;
		// cout << RESET << "fabs(getPos - lastPos) = " << fabs(getPos - lastPos) << endl;
		rtn = XR1.CM_GetJointVel(19, getVel);
		if(0 != rtn)
		{
			cout << RED << "ERR CM_GetJointPos!!!" << RESET << endl;
		}
		rtn = XR1.CM_GetJointCur(19, getCur);
		if(0 != rtn)
		{
			cout << RED << "ERR CM_GetJointPos!!!" << RESET << endl;
		}
		
		// if(fabs(getPos - lastPos) < 0.00005 || fabs(getVel) < 0.05 || fabs(getCur) > 3)
		if(fabs(getVel) < 0.0001 || fabs(getCur) > 6)
		{
			// if(fabs(getPos - lastPos) < 0.0001)
			// {
			// 	cout << RED << "check pos touch limit" << endl;
			// }
			if(fabs(getVel) < 0.001)
			{
				cout << RED << "check vel touch limit" << endl;
			}
			if(fabs(getCur) > 3)
			{
				cout << RED << "check cur touch limit" << endl;
			}
			softLimit[1] = getPos;
			cout << "getpos = " << getPos << endl;
			rtn = XR1.CM_SetJointCtrlMode(19, PrfPosCtrlMode);
			cout << "CM_SetJointCtrlMode = " << rtn << endl;
			if(0 != rtn)
			{
				cout << RED << "ERR CM_SetJointCtrlMode!!!" << RESET << endl;
			}
			// todo calculate limit, and back to zero
			rtn = XR1.CM_SetJointPos(19, initPos);
			usleep(1000*1000);
			break;
		}
		lastPos = getPos;
		usleep(5*1000);
	}
	usleep(1000*1000);
	cout  << "limit = " << softLimit[0] << " " << softLimit[1] << endl;
}





int main()
{
    int i, j;
	short rtn, value;
	bool status = false;
	double getPos, getVel, getCur;
	double softLimit[2] = {0.0};
	long val;
	//char *pVersion;
    char HwVersion[2] = {0};
	vector<short> Axis;
	ConfigParm Cparm;
	SafeParm Sparm;

	//rtn = XR1.CM_ConnectXR1();
    rtn = Ctrller.CM_Connect(false);
	cout << "CM_ConnectRobot = " << rtn << endl;
	if(0 != rtn)
	{
		cout << RED << "ERR Connect!!!" << RESET << endl;
	}

    rtn = Ctrller.CM_GetAllAxisID(Axis);
    if(0 != rtn)
	{
		cout << RED << "ERR CM_GetAllAxisID!!!" << RESET << endl;
	}
    for(i=0; i<Axis.size(); i++)
    {
        cout << Axis.at(i) << " ";
    }
    cout << endl;

    for(i=0; i<Axis.size(); i++)
    {
        rtn = Ctrller.CM_GetStatus(Axis.at(i), val);
        cout << "CM_GetStatus = " << rtn << " " << val << endl;
        if(0 != rtn)
        {
            cout << RED << "ERR CM_InitAllJoints!!!" << RESET << endl;
        }
    }

	rtn = Ctrller.CM_InitAll();
	cout << "CM_InitAllJoints = " << rtn << endl;
	if(0 != rtn)
	{
		cout << RED << "ERR CM_InitAllJoints!!!" << RESET << endl;
	}
	
	
	Ctrller.CM_StartGetPVCTimer(true);

    rtn = XR1.CM_SetXR1SoftLimitStatus(1);
	cout << "CM_SetXR1SoftLimitStatus = " << rtn << endl;
	if(0 != rtn)
	{
		cout << RED << "ERR CM_SetXR1SoftLimitStatus!!!" << RESET << endl;
	}
	for (i=9; i<24; i++) 
	{
		rtn = Ctrller.CM_SetSoftLimitStatus(i, 0);
		if(0 != rtn)
		{
			cout << RED << "ERR CM_SetSoftLimitStatus!!!" << RESET << endl;
		}
	}

    rtn = XR1.CM_SetAllCtrlMode(PrfPosCtrlMode);
    cout << "CM_SetAllCtrlMode = " << rtn << endl;
	if(0 != rtn)
	{
		cout << RED << "ERR CM_SetAllCtrlMode!!!" << RESET << endl;
	}

	rtn = Ctrller.CM_SetBrakeData(1);
	if(0 != rtn)
	{
		cout << RED << " ERR CM_SetBrakeState!!!" << RESET << endl;
	}
	usleep(500*1000);
	rtn = Ctrller.CM_GetBrakeData(value);
	

	// for test
	// rtn = Ctrller.CM_SetPosition(6, -2.0);
	getPos = 0;
	rtn = Ctrller.CM_SetPosition(6, 1.0);
	// usleep(500*1000);
	sleep(1);
	rtn = Ctrller.CM_GetProfilePosition(6, getPos);

	double pos, vel, cur;
	rtn = Ctrller.CM_GetProfilePVC(6, pos, vel, cur);


	getPos = 0;
	sleep(1);
	rtn = Ctrller.CM_GetProfilePosition(6, getPos);

	getPos = 0;
	sleep(1);
	rtn = Ctrller.CM_GetProfilePosition(6, getPos);

	getPos = 0;
	rtn = Ctrller.CM_SetPosition(4, 0.5);
	usleep(500*1000);
	rtn = Ctrller.CM_GetProfilePosition(4, getPos);



	rtn = Ctrller.CM_SetPosition(7, 2.0);
	usleep(500*1000);
	rtn = Ctrller.CM_GetProfilePosition(7, getPos);


	rtn = Ctrller.CM_SetPosition(5, 2.0);
	rtn = Ctrller.CM_SetPosition(13, 5.0);
	rtn = Ctrller.CM_SetPosition(14, -2.0);
	rtn = Ctrller.CM_SetPosition(20, -2.0);
	rtn = Ctrller.CM_SetPosition(21, 2.0);

	// end
	rtn = Ctrller.CM_GetProfilePosition(6, getPos);
	printf("INIT POS0 = %f", getPos);

	// rtn = XR1.CM_GetJointPos(12, getPos);
	// rtn = XR1.CM_SetJointPos(12, getPos+0.5);
	rtn = XR1.CM_SetJointPos(12, 0+0.5);
	// rtn = XR1.CM_GetJointPos(19, getPos);
	// rtn = XR1.CM_SetJointPos(19, getPos-0.5);
	rtn = XR1.CM_SetJointPos(19, 0-0.5);
	usleep(5000*1000);
	getLimit(5);
	get6Limit();
	get7Limit();
	// rtn = XR1.CM_SetJointPos(12, 0.0);
	// rtn = XR1.CM_SetJointPos(19, 0.0);
	getLimit(9);
	getLimit(10);

    get12Limit();
    getLimit(13);
	getLimit(14);
	getLimit(15);
	getLimit(16);
	getLimit(17);

	get19Limit();
	getLimit(20);
	getLimit(21);
	getLimit(22);
	getLimit(23);
	getLimit(24);

	usleep(500*1000);

	rtn = Ctrller.CM_SetPosition(5, 0.0);
	rtn = Ctrller.CM_SetPosition(13, 0.0);
	rtn = Ctrller.CM_SetPosition(14, 0.0);
	rtn = Ctrller.CM_SetPosition(20, 0.0);
	rtn = Ctrller.CM_SetPosition(21, 0.0);
	rtn = XR1.CM_SetJointPos(12, 0.0);
	rtn = XR1.CM_SetJointPos(19, 0.0);

}
