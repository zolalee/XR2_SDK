#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <iostream>
#include <sys/time.h>
#include<time.h>
#include <pthread.h>
#include "CM_SCA_Controller.h"

#define RED "\033[31m"
#define RESET "\033[0m"
#define Pi 3.1415926535
extern CM_SCA_Controller SCACtrller;
	double pos1 = 0.0, vel1 = 0.0, cur1 = 0.0;
    double pos2 = 0.0, vel2 = 0.0, cur2= 0.0;
	short rtn;

     clock_t start_,end_;
void *pvc_get_1(void *arg){
            clock_t start_,end_;
            start_ =clock();
            for (int i = 1; i < 3; i++)
        {
        rtn = SCACtrller.CM_GetProfilePVC(i, pos1, vel1, cur1);
        }
        end_=clock();
        cout<<"the time for one circle PVC123 get ="<<end_- start_<<endl;
}
void *pvc_get_2(void *arg){
    clock_t start2,end2;
    start2 =clock();
                for (int i = 7; i < 9; i++)
        {
        rtn = SCACtrller.CM_GetProfilePVC(i, pos2, vel2, cur2);
        }
        end2=clock();
cout<<"the time for one circle PVC789 get ="<<end2- start2<<endl;
}
int main()
{
int i, j;

	bool status = false;
	double value;
	long val;
	//char *pVersion;
	char SwVersion[12] = {0};
	char HwVersion[12] = {0}; // 最大的版本号是：255.255.255，so 最大值定为12
	vector<short> Axis;
	vector<double> pos;
	//long time;
	// CM_SCA_Controller SCACtrller;
	ConfigParm Cparm;
	SafeParm Sparm;
     clock_t start, end ;


	while (1)
	{
		rtn = SCACtrller.CM_GetSWVersion(SwVersion);
		cout << "GetSWVersion = " << rtn << ", SwVersion = " << SwVersion << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR GetSWVersion!!!" << RESET << endl;
		}

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
        		
		for (i = 0; i < Axis.size(); i++)
		{
			rtn = SCACtrller.CM_SetProfilePositionMode(Axis.at(i));
		}
sleep(1);


		// rtn = SCACtrller.CM_GetStatus(Axis.at(1), val);
		// cout << "GetStatus = " << rtn << ", Status = " << val << endl;
		// if (0 != rtn)
		// {
		// 	cout << RED << "ERR GetStatus!!!" << RESET << endl;
		// }


		rtn = SCACtrller.CM_GetProfileMode(8, val);
		cout << "GetProfileMode = " << rtn << ", Mode = " << val << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR GetProfileMode!!!" << RESET << endl;
		}

        rtn = SCACtrller.CM_GetProfilePosition(8, value);
		cout << "the 8 sca GetProfilePosition = " << rtn << ", Pos = " << value << endl;
 sleep(0.5);       
        rtn = SCACtrller.CM_SetPosition(8,- 0.10);
        cout << "CM_SetPosition = " << rtn << endl;


		if (0 != rtn)
		{
			cout << RED << "ERR GetProfilePosition!!!" << RESET << endl;
		}

		sleep(2);
        //vel mode
		rtn = SCACtrller.CM_SetVelocityMode(9);
		cout << "the 9 sca SetVelocityMode = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "9 sca ERR SetVelocityMode!!!" << RESET << endl;
		}

        	rtn = SCACtrller.CM_GetProfileMode(9, val);
		cout << "the 9 sca GetProfileMode = " << rtn << ", Mode = " << val << endl;
		if (0 != rtn)
		{
			cout << RED << "9sca ERR GetProfileMode!!!" << RESET << endl;
		}

		// rtn = SCACtrller.CM_SetVelocity(9, double(20));
		// cout << "the sca 9 SetVelocity = " << rtn << endl;
		// if (0 != rtn)
		// {
		// 	cout << RED << " 9 sca ERR SetVelocity!!!" << RESET << endl;
		// }

        rtn = SCACtrller. CM_GetProfileVelocity(9, val);
        cout << "the 9 sca CM_GetProfileVelocity = " << rtn << ", vel = " << val << endl;





        // cur mode
        rtn = SCACtrller.CM_SetCurrentMode(8);
		cout << " the 8 sca SetCurrentMode = " << rtn << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR 8 sca SetCurrentMode!!!" << RESET << endl;
		}

        rtn = SCACtrller.CM_GetCurrent(8, value);
		cout << "the 8 sca CM_GetCurrent = " << rtn << ", Cur = " << value << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR 8 sca CM_GetCurrent!!!" << RESET << endl;
		}
		rtn = SCACtrller.CM_GetProfileMode(8, val);
		cout << "the 8 sca GetProfileMode = " << rtn << ", Mode = " << val << endl;
		if (0 != rtn)
		{
			cout << RED << "ERR 8 sca GetProfileMode!!!" << RESET << endl;
		}


        //get pvc 
       // system("time");
        //system("title %time%");

     start =clock();
        for (i = 0; i < Axis.size(); i++)
        {
        rtn = SCACtrller.CM_GetProfilePVC(Axis.at(0), pos1, vel1, cur1);
        }
       // system("time");
        //system("title %time%");
end =clock();
cout<<"the time for one circle PVCget ="<<end-start<<endl;

pthread_t p1 ,p2;
 pthread_create(&p1, NULL, pvc_get_1, NULL);
  pthread_create(&p2, NULL, pvc_get_2, NULL);
  //pthread_join(p1, NULL);
  //pthread_join(p2, NULL);

    return rtn;
}
}