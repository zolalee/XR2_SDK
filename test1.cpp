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
#include <unistd.h>

#define RED			"\033[31m"
#define RESET		"\033[0m"
#define Pi          3.1415926535


double softlimitTalbe[] = {-0.5, 0.5, -1.2, 0.167, -0.263, 4.2,
                                                    -0.5, 0.5, -1.2, 0.167, -0.263, 4.2,
                                                    -0.5, 0.5,  -0.167, 1.2, -4.2, 0.263,                                                   
                                                    -0.5, 0.5,  -0.167, 1.2, -4.2, 0.263};

 double testjoint[] =    {0.0115089, -0.806148, 1.69039, -0.0115089, -0.806148, 1.69039, 0.0115089, 0.806148, -1.69039, -0.0115089, 0.806148, -1.69039,
 0.0115089, -0.806148, 1.69039, -0.0115398, -0.80822, 1.69489, 0.0115398, 0.80822, -1.69489, -0.0115089, 0.806148, -1.69039,
 0.0115089, -0.806148, 1.69039, -0.0116719, -0.816885, 1.71372, 0.0116719, 0.816885, -1.71372, -0.0115089, 0.806148, -1.69039,
 0.0115089, -0.806148, 1.69039, -0.011882, -0.830083, 1.74248, 0.011882, 0.830083, -1.74248, -0.0115089, 0.806148, -1.69039,
 0.0115089, -0.806148, 1.69039, -0.012159, -0.846491, 1.77835, 0.012159, 0.846491, -1.77835, -0.0115089, 0.806148, -1.69039,
 0.0115089, -0.806148, 1.69039, -0.012493, -0.86491, 1.81881, 0.012493, 0.86491, -1.81881, -0.0115089, 0.806148, -1.69039,
 0.0115089, -0.806148, 1.69039, -0.0128889, -0.885016, 1.86321, 0.0128889, 0.885016, -1.86321, -0.0115089, 0.806148, -1.69039,
 0.0115089, -0.806148, 1.69039, -0.0132986, -0.904093, 1.9056, 0.0132986, 0.904093, -1.9056, -0.0115089, 0.806148, -1.69039,
 0.0115089, -0.806148, 1.69039, -0.0137136, -0.921835, 1.94529, 0.0137136, 0.921835, -1.94529, -0.0115089, 0.806148, -1.69039,
 0.0115089, -0.806148, 1.69039, -0.0141115, -0.937521, 1.98062, 0.0141115, 0.937521, -1.98062, -0.0115089, 0.806148, -1.69039,
 0.0115089, -0.806148, 1.69039, -0.0144638, -0.95044, 2.0099, 0.0144638, 0.95044, -2.0099, -0.0115089, 0.806148, -1.69039,
 0.0115089, -0.806148, 1.69039, -0.014743, -0.960091, 2.03189, 0.014743, 0.960091, -2.03189, -0.0115089, 0.806148, -1.69039,
 0.0115089, -0.806148, 1.69039, -0.0148955, -0.965157, 2.04348, 0.0148955, 0.965157, -2.04348, -0.0115089, 0.806148, -1.69039,
 0.0115089, -0.806148, 1.69039, -0.014892, -0.965044, 2.04322, 0.014892, 0.965044, -2.04322, -0.0115089, 0.806148, -1.69039,
 0.0115089, -0.806148, 1.69039, -0.0147355, -0.959838, 2.03131, 0.0147355, 0.959838, -2.03131, -0.0115089, 0.806148, -1.69039,
 0.0115089, -0.806148, 1.69039, -0.01446, -0.950307, 2.00959, 0.01446, 0.950307, -2.00959, -0.0115089, 0.806148, -1.69039,
 0.0115089, -0.806148, 1.69039, -0.0141057, -0.937303, 1.98012, 0.0141057, 0.937303, -1.98012, -0.0115089, 0.806148, -1.69039,
 0.0115089, -0.806148, 1.69039, -0.0137025, -0.921381, 1.94427, 0.0137025, 0.921381, -1.94427, -0.0115089, 0.806148, -1.69039,
 0.0115089, -0.806148, 1.69039, -0.013283, -0.903398, 1.90405, 0.013283, 0.903398, -1.90405, -0.0115089, 0.806148, -1.69039,
 0.0115089, -0.806148, 1.69039, -0.0128727, -0.884228, 1.86146, 0.0128727, 0.884228, -1.86146, -0.0115089, 0.806148, -1.69039,
 0.0115089, -0.806148, 1.69039, -0.0124916, -0.864833, 1.81864, 0.0124916, 0.864833, -1.81864, -0.0115089, 0.806148, -1.69039,
 0.0115089, -0.806148, 1.69039, -0.0121495, -0.845949, 1.77717, 0.0121495, 0.845949, -1.77717, -0.0115089, 0.806148, -1.69039,
 0.0115089, -0.806148, 1.69039, -0.0118685, -0.829257, 1.74067, 0.0118685, 0.829257, -1.74067, -0.0115089, 0.806148, -1.69039,
 0.0115089, -0.806148, 1.69039, -0.011656, -0.815855, 1.71148, 0.011656, 0.815855, -1.71148, -0.0115089, 0.806148, -1.69039,
 0.0115089, -0.806148, 1.69039, -0.0115189, -0.806821, 1.69185, 0.0115189, 0.806821, -1.69185, -0.0115089, 0.806148, -1.69039,
 0.0115089, -0.806148, 1.69039, -0.0115089, -0.806148, 1.69039, 0.0115089, 0.806148, -1.69039, -0.0115089, 0.806148, -1.69039,
 0.0115398, -0.80822, 1.69489, -0.0115089, -0.806148, 1.69039, 0.0115089, 0.806148, -1.69039, -0.0115398, 0.80822, -1.69489,
 0.0116719, -0.816885, 1.71372, -0.0115089, -0.806148, 1.69039, 0.0115089, 0.806148, -1.69039, -0.0116719, 0.816885, -1.71372,
 0.011882, -0.830083, 1.74248, -0.0115089, -0.806148, 1.69039, 0.0115089, 0.806148, -1.69039, -0.011882, 0.830083, -1.74248,
 0.012159, -0.846491, 1.77835, -0.0115089, -0.806148, 1.69039, 0.0115089, 0.806148, -1.69039, -0.012159, 0.846491, -1.77835,
 0.012493, -0.86491, 1.81881, -0.0115089, -0.806148, 1.69039, 0.0115089, 0.806148, -1.69039, -0.012493, 0.86491, -1.81881,
 0.0128889, -0.885016, 1.86321, -0.0115089, -0.806148, 1.69039, 0.0115089, 0.806148, -1.69039, -0.0128889, 0.885016, -1.86321,
 0.0132986, -0.904093, 1.9056, -0.0115089, -0.806148, 1.69039, 0.0115089, 0.806148, -1.69039, -0.0132986, 0.904093, -1.9056,
 0.0137136, -0.921835, 1.94529, -0.0115089, -0.806148, 1.69039, 0.0115089, 0.806148, -1.69039, -0.0137136, 0.921835, -1.94529,
 0.0141115, -0.937521, 1.98062, -0.0115089, -0.806148, 1.69039, 0.0115089, 0.806148, -1.69039, -0.0141115, 0.937521, -1.98062,
 0.0144638, -0.95044, 2.0099, -0.0115089, -0.806148, 1.69039, 0.0115089, 0.806148, -1.69039, -0.0144638, 0.95044, -2.0099,
 0.014743, -0.960091, 2.03189, -0.0115089, -0.806148, 1.69039, 0.0115089, 0.806148, -1.69039, -0.014743, 0.960091, -2.03189,
 0.0148955, -0.965157, 2.04348, -0.0115089, -0.806148, 1.69039, 0.0115089, 0.806148, -1.69039, -0.0148955, 0.965157, -2.04348,
 0.014892, -0.965044, 2.04322, -0.0115089, -0.806148, 1.69039, 0.0115089, 0.806148, -1.69039, -0.014892, 0.965044, -2.04322,
 0.0147355, -0.959838, 2.03131, -0.0115089, -0.806148, 1.69039, 0.0115089, 0.806148, -1.69039, -0.0147355, 0.959838, -2.03131,
 0.01446, -0.950307, 2.00959, -0.0115089, -0.806148, 1.69039, 0.0115089, 0.806148, -1.69039, -0.01446, 0.950307, -2.00959,
 0.0141057, -0.937303, 1.98012, -0.0115089, -0.806148, 1.69039, 0.0115089, 0.806148, -1.69039, -0.0141057, 0.937303, -1.98012,
 0.0137025, -0.921381, 1.94427, -0.0115089, -0.806148, 1.69039, 0.0115089, 0.806148, -1.69039, -0.0137025, 0.921381, -1.94427,
 0.013283, -0.903398, 1.90405, -0.0115089, -0.806148, 1.69039, 0.0115089, 0.806148, -1.69039, -0.013283, 0.903398, -1.90405,
 0.0128727, -0.884228, 1.86146, -0.0115089, -0.806148, 1.69039, 0.0115089, 0.806148, -1.69039, -0.0128727, 0.884228, -1.86146,
 0.0124916, -0.864833, 1.81864, -0.0115089, -0.806148, 1.69039, 0.0115089, 0.806148, -1.69039, -0.0124916, 0.864833, -1.81864,
 0.0121495, -0.845949, 1.77717, -0.0115089, -0.806148, 1.69039, 0.0115089, 0.806148, -1.69039, -0.0121495, 0.845949, -1.77717,
 0.011656, -0.815855, 1.71148, -0.0115089, -0.806148, 1.69039, 0.0115089, 0.806148, -1.69039, -0.011656, 0.815855, -1.71148,
 0.0115189, -0.806821, 1.69185, -0.0115089, -0.806148, 1.69039, 0.0115089, 0.806148, -1.69039, -0.0115189, 0.806821, -1.69185,
 0.0115089, -0.806148, 1.69039, -0.0115089, -0.806148, 1.69039, 0.0115089, 0.806148, -1.69039, -0.0115089, 0.806148, -1.69039};

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
long CtrlMode;
char SwVersion[12] = {0};
int input;
double input_,NSoftLimit_,PSoftLimit_;
double  pos_, vel_, cur_;
	rtn = XR2.CM_ConnectXR2();
	cout << "CM_ConnectRobot = " << rtn << endl;
	if(0 != rtn)
	{
		cout << RED << "ERR Connect!!!" << RESET << endl;
	}

   // rtn = Ctrller.CM_Connect();
    rtn = Ctrller.CM_GetAllAxisID(Axis);
    if(0 != rtn)
	{
		cout << RED << "ERR CM_GetAllAxisID!!!" << RESET << endl;
	}
    		rtn = Ctrller.CM_GetHWVersion(1,SwVersion);
		cout << "GetHWVersion = " << rtn << ", SwVersion = " << SwVersion << endl;
    for(i=0; i<Axis.size(); i++)
    {
        cout << Axis.at(i) << " ";
        rtn = XR2.CM_GetJointPos(i+1,value);
        cout << " the"<<   "sca position  = " << value << endl;
        // rtn = XR2.CM_GetJointCur(i+1,value);
        // cout << " the"<<   "  sca current  = " << value << endl;
        // rtn = XR2.CM_GetJointVel(i+1,value);
        // cout << " the"<<   "  sca velocity  = " << value << endl;
        rtn = XR2.CM_GetSoftLimitValue(i+1,NSoftLimit_,PSoftLimit_); 
 cout << "the   NSoftLimit =  " <<NSoftLimit_  << endl;      
cout << "the  PSoftLimit =  " <<PSoftLimit_ << endl;     
    }
    cout << endl;
rtn = XR2.CM_GetPIDParm(7,&Cparm);
cout << "getConfigParm = " << rtn << endl;

// rtn = XR2.CM_SetPIDParm(7,&Cparm);
// cout << "SetConfigParm = " << rtn << endl;


    // for(i=0; i<Axis.size(); i++)
    // {
    //     rtn = Ctrller.CM_GetStatus(Axis.at(i), val);
    //     cout << "CM_GetStatus = " << rtn << " " << val << endl;
    //     if(0 != rtn)
    //     {
    //         cout << RED << "ERR CM_InitAllJoints!!!" << RESET << endl;
    //     }
    // }

//     rtn = XR2.CM_SetJointCtrlMode(1,CurCtrlMode);
//     rtn = XR2.CM_SetXR2SoftLimitStatus(1);
// cout << " the  1 sca CM_SetJointCtrlMode = " << rtn << endl;
//         if(0 != rtn)
//         {
//             cout << RED << "1 sca CM_SetJointCtrlMode!!!" << RESET << endl;
//         }
//         for(i=0; i<Axis.size(); i++)
// rtn = XR2.CM_SetJointCtrlMode(1,PosCtrlMode);

rtn =XR2.CM_GetJointCtrlMode(2,CtrlMode);
cout << " the control mode for sca  2 = " << CtrlMode << endl;


// rtn =XR2.CM_SetJointCtrlMode(4,PrfPosCtrlMode);
// rtn =XR2.CM_SetJointPos(4,0);

/*------------------------------*/

//     rtn =XR2.CM_SetJointCtrlMode(1,CurCtrlMode);
//     rtn =XR2.CM_SetJointCtrlMode(2,CurCtrlMode);
//     rtn =XR2.CM_SetJointCtrlMode(3,CurCtrlMode);
//     // rtn =XR2.CM_SetJointCtrlMode(7,CurCtrlMode);
//     // rtn =XR2.CM_SetJointCtrlMode(8,CurCtrlMode);
//     // rtn =XR2.CM_SetJointCtrlMode(9,CurCtrlMode);
//     //     rtn =XR2.CM_SetJointCtrlMode(4,CurCtrlMode);
//     // rtn =XR2.CM_SetJointCtrlMode(5,CurCtrlMode);
//     // rtn =XR2.CM_SetJointCtrlMode(6,CurCtrlMode);
//     // rtn =XR2.CM_SetJointCtrlMode(10,CurCtrlMode);
//     // rtn =XR2.CM_SetJointCtrlMode(11,CurCtrlMode);
//     // rtn =XR2.CM_SetJointCtrlMode(12,CurCtrlMode);
//     sleep(1);
//     for(int i =0 ;i<100;i++){
//     //rtn =XR2.CM_SetJointCur(3,0.9); 
//    usleep(5000); 
//     rtn =XR2.CM_SetJointCur(1,0.1); 
//      rtn =XR2.CM_SetJointCur(2,0.1); 
//      rtn =XR2.CM_SetJointCur(3,0.1); 
//     // rtn =XR2.CM_SetJointCur(7,0.1); 
//     // rtn =XR2.CM_SetJointCur(8,0.1); 
//     // rtn =XR2.CM_SetJointCur(9,0.1);     
//     //  rtn =XR2.CM_SetJointCur(4,0.1); 
//     // rtn =XR2.CM_SetJointCur(5,0.1); 
//     // rtn =XR2.CM_SetJointCur(6,0.1); 
//     // rtn =XR2.CM_SetJointCur(10,0.1); 
//     // rtn =XR2.CM_SetJointCur(11,0.1); 
//     // rtn =XR2.CM_SetJointCur(12,0.1);  
    
//     for(int j=0;j<3;j++)
    
//     {   
//         //usleep(1000);
//         rtn=XR2.CM_GetJointPVC(j+1,pos_, vel_, cur_);
        
//         cout<<j+1<<"the pos  real "<<" one circle PVCget ="<<pos_<<endl;

//         // rtn=XR2.CM_GetJointPVC(j+7,pos_, vel_, cur_);
//         // cout<<j+7<<"the pos  real "<<" one circle PVCget ="<<pos_<<endl;
//         // rtn=XR2.CM_GetJointPVC(j+3,pos_, vel_, cur_);
//         // cout<<j+3<<"the pos  real "<<" one circle PVCget ="<<pos_<<endl;
//         // rtn=XR2.CM_GetJointPVC(j+10,pos_, vel_, cur_);
//         // cout<<j+10<<"the pos  real "<<" one circle PVCget ="<<pos_<<endl;

//     }
//     cout<<" the size ="<<i+1<<endl;
//     }



/*---------------------------*/

//rtn=XR2.CM_SetJointCtrlMode(3,PosCtrlMode);
//rtn =XR2.CM_SetJointPos(3,2.03189); 

// for(i=0;i<3;i++)
 //rtn =XR2.CM_SetJointPos(3,1.69039); 

// double pos_, vel_, cur_;

// // // usleep(2500);
// rtn = XR2.CM_GetJointPVC(3, pos_,vel_,cur_);

//  cout<<"the pos "<<3<<" one circle PVCget ="<<pos_<<endl;
//  cout<<"the vel "<< 3 <<" one circle PVCget ="<<vel_<<endl;
//  cout<<"the cul "<< 3 <<"  one circle PVCget ="<<cur_<<endl;


// for(j=0;j<12;j++){

//  rtn=XR2.CM_GetJointPVC(j+1,pos_,vel_,cur_);
//   cout <<j+1<< " joint pos = "<<pos_ << endl;
//  cout <<j+1<<  "joint vel = "<<vel_ << endl;
//   cout <<j+1<<  "joint cul= "<<cur_ << endl;
// }


// clock_t start, end ;
// double pos1,vel1,cur1,sumtime=0;
// for(int b=0;b<100;b++){
//  start =clock();
// // rtn = XR2.CM_GetJointPVC(Axis.at(0), pos_,vel_,cur_);
// // rtn = XR2.CM_GetJointPVC(Axis.at(1), pos_,vel_,cur_);
// // rtn = XR2.CM_GetJointPVC(Axis.at(2), pos_,vel_,cur_);
// // rtn = XR2.CM_GetJointPVC(Axis.at(6), pos_,vel_,cur_);
// // rtn = XR2.CM_GetJointPVC(Axis.at(7), pos_,vel_,cur_);
// // rtn = XR2.CM_GetJointPVC(Axis.at(8), pos_,vel_,cur_);
// rtn = XR2.CM_GetJointPos(Axis.at(8), value);
// rtn = XR2.CM_GetJointPos(Axis.at(7), value);
// rtn = XR2.CM_GetJointPos(Axis.at(6), value);
// rtn = XR2.CM_GetJointPos(Axis.at(2), value);
// rtn = XR2.CM_GetJointPos(Axis.at(1), value);
// rtn = XR2.CM_GetJointPos(Axis.at(0), value);
// cout<<"the position value ="<<value<<endl;
// end =clock();
// cout<<"the start time for one circle PVCget ="<<start<<endl;
// cout<<"the end time for one circle PVCget ="<<end<<endl;
// cout<<"the time for one circle PVCget ="<<end-start<<endl;
// sumtime+=(end-start);
// }
// cout<<"the average  time for one circle PVCget ="<<sumtime/100<<endl;


/*---------------set the zero position -----------------------*/
//////////////////////////////////////////////////////////////////
cout << "enter the set zero position mode"  << endl;

while(1)

{
cout << "set the sca = "  << endl;
cin>>input;
if (input ==0)
{cout << " end the set zero position mode "<< endl;
break;}
cout << "start to set the homingmode for sca "<< endl;
 rtn = XR2.CM_SetHoming(input);

 cout << " set the homingmode for sca  = " << rtn << endl;
        if(0 != rtn)
        {
            cout << RED << " sca set hoimingmode failed!!!" << RESET << endl;
        }
 rtn = XR2.CM_GetJointCtrlMode(input,CtrlMode);
 cout << " the control mode for sca  = " << CtrlMode << endl;


rtn = XR2.CM_GetSoftLimitValue(input,NSoftLimit_,PSoftLimit_); 
 cout << "the   NSoftLimit =  " <<NSoftLimit_  << endl;      
cout << "the  PSoftLimit =  " <<PSoftLimit_  << endl;     
cout << "wait for manual action,  enter 0 to finish"  << endl;
 cin>>NSoftLimit_; 
 rtn = XR2.CM_SetSoftLimitValue(input,softlimitTalbe[(input-1)*2],softlimitTalbe[input*2-1]);
  if(0 != rtn)
        {
            cout << RED << "set softlimit failed!!!" << RESET << endl;
        }
else
{

    cout <<  "set softlimit successful!!!"  << endl;
}
 rtn = XR2.CM_GetJointPos(input,value); 
 cout << " the position for  sca  = " << value << endl;
 
cout << "set the sca  for zero position "  << endl;       

 rtn=Ctrller.CM_Zeros(input,value);
cout << "save the sca  for zero position "  << endl;       
 rtn =Ctrller.CM_SaveParm(input);
  if(0 != rtn)
        {
            cout << RED << "set zero position  failed!!!" << RESET << endl;
        }
        else 
        cout << "set zero position  OK!!!" << endl;
 rtn=XR2.CM_SetJointCtrlMode(input,PosCtrlMode);
}
///////////////////////////////////////////////////////////////
/*-----------------------------------end set zero--------------------------------------*/

/*------------------------------------------cut line ----------------------------------------*/
///////////////////////////////////////////////////////////////////////////////////////////
//  cout << " start to test " << endl;
//  sleep(2);

//  int length =sizeof(testjoint)/sizeof(testjoint[0]);
//  printf("the size of action is %d  \n", length/12);
// for(j=0;j<12;j++){
 //       rtn =XR2.CM_SetJointPos(j+1,testjoint[j]); 
//         sleep(1);
// }
// for(i=0;i<12;i++)
//  {rtn=XR2.CM_SetJointCtrlMode(i+1,PosCtrlMode);}
//  sleep(1);
//  clock_t start, end ;
// double sumtime=0;

// sleep (2);
// for(i=0;i<12;i++)
//  {rtn=XR2.CM_SetJointCtrlMode(i+1,PrfPosCtrlMode);}
//  sleep(1);
// cout << " start to init state" << endl;
//     for(j=0;j<12;j++)
//     {
//         printf("the joint %d is %f  \n", j, testjoint[i*12+j]);
//         rtn =XR2.CM_SetJointPos(j+1,0);
//         usleep(500000);
//     }
///////////////////////////////////////////////////////////////////
/*------------------------------end test-----------------------------*/
    return 0;
}