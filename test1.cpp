#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <iostream>
#include <sys/time.h>
#include "CM_SCA_Controller.h"
#include "CM_XR2_Interface.h"

#define RED			"\033[31m"
#define RESET		"\033[0m"
#define Pi          3.1415926535

int main()
{
    int i, j;
	short rtn;
	bool status = false;
	double value;
	long val;
	//char *pVersion;
    char HwVersion[2] = {0};
	vector<short> Axis;
	vector<double> pos;
	long time;
	CM_SCA_Controller Ctrller;
    CM_XR2_Interface XR2;
	ConfigParm Cparm;
	SafeParm Sparm;

	rtn = XR2.CM_ConnectXR2();
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

    rtn = XR2.CM_SetJointCtrlMode(1,CurCtrlMode);
    //rtn = XR2.CM_SetXR2SoftLimitStatus(1);
cout << " the  1 sca CM_SetJointCtrlMode = " << rtn << endl;
        if(0 != rtn)
        {
            cout << RED << "1 sca CM_SetJointCtrlMode!!!" << RESET << endl;
        }

    return 0;
}