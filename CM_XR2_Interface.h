/*
***************************************************************************************************
                                    Cloudminds (Shenzhen) Ltd.

                        (c) Coyright 2019, Cloudminds Ltd.,

* All rights reserved. Cloudminds's  source code is an unpublished work and the use of a copyright
* notice does not imply otherwise. This source code contains confidential, trade secret material of
* Cloudminds Ltd. Any attempt or participation in deciphering, decoding, reverse engineering
* or in any way altering the source code is strictly prohibited, unless the prior written consent
* of Cloudminds Ltd. is obtained.
*
* Filename:       	CM_XR2_Interface.h
* Programmer:       Li Zola
* Created:        	june 9th, 2020
* Description:		SCA controller interface based on SCA SDK
*
* Note:				June 9th, 2020, version: 1.0
*
***************************************************************************************************
*/

#ifndef CM_XR2_INTERFACE_H
#define CM_XR2_INTERFACE_H

/*---------------------------------------------------------------------------------------
------
------	Includes
------
---------------------------------------------------------------------------------------*/
#include "CM_SCA_Controller.h"

/*---------------------------------------------------------------------------------------
------
------	Macro definitions
------
---------------------------------------------------------------------------------------*/
#define XR2MinJointID                       1
#define XR2JointNum                         12

/*---------------------------------------------------------------------------------------
------
------	Enum
------
---------------------------------------------------------------------------------------*/
enum Xr2JointDefine
{
    MainBody = 1,
};

enum CtrlGroup
{
    MainBodyCtrlGroup=1,
};

enum CtrlMode
{
    CurCtrlMode = 1,
    VelCtrlMode,
    PrfVelCtrlMode,
    PosCtrlMode,
    PrfPosCtrlMode,
};


/*---------------------------------------------------------------------------------------
------
------	Class
------
---------------------------------------------------------------------------------------*/
class CM_XR2_Interface
{
public:
    
 
     /*
     * 函数说明: 设置机器人PID参数 
     * 注意事项: 开始时执行
     * 参数说明: 无
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
short CM_SetPIDParm(short joint, ConfigParm *parm);
     /*
     * 函数说明: 读取机器人PID参数 
     * 注意事项: 无
     * 参数说明: 无
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
short CM_GetPIDParm(short joint, ConfigParm *parm);
    /*
     * 函数说明: 初始化机器人
     * 注意事项: 程序最开始时执行
     * 参数说明: 无
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_ConnectXR2();
     
    
    /*
     * 函数说明: 重置单独关节
     * 注意事项: 需重新开关机时执行，自动清楚执行器报警
     * 参数说明: joint：     ————设定的关节号
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_ResetJoint(short joint);
    
    /*
     * 函数说明: 关闭所有关节
     * 注意事项: 开机后执行
     * 参数说明: 无
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_CloseAllJoints();
    
    /*
     * 函数说明: 设置除轮子外的关节的限位是否生效
     * 注意事项: 初始化后执行
     * 参数说明: status:     ————0为关闭限位，1为开启限位
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_SetXR2SoftLimitStatus(long status);
     /*
     * 函数说明：获取软限位
     * 注意事项：需在轴初始化后执行，安全起见
     * 参数说明：axis: 设定的轴号
     *         NSoftLimit: 负限位
     *         PSoftLimit: 正限位
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */   
   short  CM_GetSoftLimitValue(short axis, double &NSoftLimit, double &PSoftLimit);
    /*
     * 函数说明：设置软限位
     * 注意事项：需在轴初始化后执行，安全起见，每次开机后需执行一次，
     *         不会自动保存，需调用CM_SaveParm函数
     * 参数说明：axis: 设定的轴号
     *         NSoftLimit: 负限位
     *         PSoftLimit: 正限位
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
   short  CM_SetSoftLimitValue(short axis, double NSoftLimit, double PSoftLimit);  
    /*
     * 函数说明: 清楚所有关节的报警
     * 注意事项: 初始化后执行
     * 参数说明: 无
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_ClearAllAlarm();
           
    /*
     * 函数说明: 获取关节控制模式
     * 注意事项: 初始化后执行
     * 参数说明: group: 要获取的关节
              Ctrlmode：   ————获取的控制模式
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetJointCtrlMode(short joint, long &CtrlMode);
    /*
     * 函数说明: 获取关节的控制模式
     * 注意事项: 初始化后执行，运动中不可执行
     * 参数说明: joint: 要设置的关节
               mode: 设置的控制模式
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_SetJointCtrlMode(short joint, CtrlMode mode);
     /*
     * 函数说明：设置关节的homing
     * 注意事项：需在轴初始化后执行，运动中不可执行
     * 参数说明：axis： 设置的轴号
     * 返回说明：0: 成功
     **         其他: 参照错误代码
     * Note: 之前是单个axis设置，现在是通过Group的方式一把设置
     */
    short CM_SetHoming(short joint);
    /*
     * 函数说明：设置所有关节的目标位置
     * 注意事项：初始化后，设置位置模式或prf位置模式后执行，单位：弧度
     * 参数说明：value： 目标位置
     * 返回说明：0: 成功
     **         其他: 参照错误代码
     * Note: 之前是单个axis设置，现在是通过Group的方式一把设置
     */
    short CM_SetAllPos(vector<double> value);

    /*
     * 函数说明: 设置关节的目标位置
     * 注意事项: 初始化后，设置位置模式或prf位置模式后执行，单位：弧度
     * 参数说明: joint: 要设置的规划组
     *         value: 目标位置
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_SetJointPos(short joint, double value);

    /*
     * 函数说明: 获取所有关节的当前位置
     * 注意事项: 初始化后执行，单位：弧度
     *        value: 当前位置
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetAllPos(vector<double> &value);
     
    /*
     * 函数说明: 获取关节的当前位置
     * 注意事项: 初始化后执行，单位：弧度
     * 参数说明: joint: 要获取的关节
     *         value: 当前位置
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetJointPos(short joint, double &value);

    /*
     * 函数说明：设置所有关节的目标速度
     * 注意事项：初始化后，设置速度模式或prf速度模式后执行，单位：弧度/s
     *         value: 目标速度
     * 返回说明：0: 成功
     *         其他: 参照错误代码
     * Note: 之前是单个axis设置，现在是通过Group的方式一把设置
     */
    short CM_SetAllVel(vector<double> value);
    
 
    /*
     * 函数说明: 设置关节的目标速度
     * 注意事项: 初始化后，设置速度模式或prf速度模式后执行，单位：弧度/s
     * 参数说明: joint: 要设置的关节
     *        value: 目标速度
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_SetJointVel(short joint, double value);

    /*
     * 函数说明: 获取所有关节的当前速度
     * 注意事项: 初始化后执行，单位：弧度/s
     *        value: 当前速度
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetAllVel(vector<double> &value);
    
  
    /*
     * 函数说明: 获取关节的当前速度
     * 注意事项: 初始化后执行，单位：弧度/s
     * 参数说明: joint: 要获取的关节
     *         value: 当前速度
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetJointVel(short joint, double &value);
    
    /*
     * 函数说明：设置所有关节的目标电流
     * 注意事项：初始化后，设置电流模式后执行，单位：A
     * 参数说明：value: 目标电流
     * 返回说明：0: 成功
     *        其他: 参照错误代码
     * Note: 之前是单个axis设置，现在是通过Group的方式一把设置
     */
    short CM_SetAllCur(vector<double> value);

    
    /*
     * 函数说明: 设置关节的目标电流
     * 注意事项: 初始化后，设置电流模式后执行，单位：A
     * 参数说明: joint: 要设置的关节
     *         value: 目标电流
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_SetJointCur(short joint, double value);
    
    /*
     * 函数说明: 获取所有关节的当前电流
     * 注意事项: 初始化后，获取电流模式后执行，单位：A
     * 参数说明: value: 当前电流
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetAllCur(vector<double> &value);

    
    /*
     * 函数说明: 获取关节的当前电流
     * 注意事项: 初始化后，获取电流模式后执行，单位：A
     * 参数说明: joint: 要获取的关节
     *         value: 当前电流
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetJointCur(short joint, double &value);
    
    /*
     * 函数说明: 获取所有关节的当前：位置、速度和电流
     * 参数说明: pos: 位置, 单位：弧度
     *          vel: 速度, 单位：弧度/s
     *          cur: 电流, 单位：A
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetAllPVC(vector<double> &pos, vector<double> &vel, vector<double> &cur);

    /*
     * 函数说明: 获取关节的当前：位置、速度和电流
     * 参数说明: joint: 要获取的关节
     *          pos: 位置, 单位：弧度
     *          vel: 速度, 单位：弧度/s
     *          cur: 电流, 单位：A
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetJointPVC(short joint, double &pos, double &vel, double &cur);
    
    short CM_joint_Zeros(short joint,double value);

    short CM_Save_joint_Parm(short joint);
    //rad -> circle
    double XR1Pos2SCAPos(double rad, double ratio);
    //circle -> rad
    double SCAPos2XR1Pos(double circle, double ratio);
    //rad/s -> rpm
    double XR1Vel2SCAVel(double rad_s, double ratio);
    //rpm -> rad/s 
    double SCAVel2XR1Vel(double rpm, double ratio);
    //none
    ~CM_XR2_Interface();

private:
    //get num of group joints


    // joint is invalid
    bool JointIsInvalid(short joint);

};



#endif