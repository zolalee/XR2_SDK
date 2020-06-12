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
* Filename:       	CM_XR1_Interface.h
* Programmer:       Tianhao Wang
* Created:        	April 15th, 2019
* Description:		SCA controller interface based on SCA SDK
*
* Note:				June 15th, 2019, version: 1.0
*
***************************************************************************************************
*/

#ifndef CM_XR1_INTERFACE_H
#define CM_XR1_INTERFACE_H

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
#define XR1MinJointID                       1
#define XR1JointNum                         34

/*---------------------------------------------------------------------------------------
------
------	Enum
------
---------------------------------------------------------------------------------------*/
enum Xr1JointDefine
{
    OmniWheel = 1,
    MainBody = 4,
    Head = 8,
    LeftArm = 11,
    RightArm = 18,
    LeftHand = 25,
    RightHand = 30,
};

enum CtrlGroup
{
    OmniWheelCtrlGroup = 1,
    MainBodyCtrlGroup,
    HeadCtrlGroup,
    LeftArmCtrlGroup,
    RightArmCtrlGroup,
    LeftTrunkArmCtrlGroup,
    RightTrunkArmCtrlGroup,
    LeftHandCtrlGroup,
    RightHandCtrlGroup,
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
class CM_XR1_Interface
{
public:
    
    /*
     * 函数说明: 连接机器人
     * 注意事项: 程序最开始时执行
     * 参数说明: 无
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_ConnectXR1();
    
    /*
     * 函数说明: 初始化所有关节
     * 注意事项: 连接机器人后执行，自动清楚执行器报警
     * 参数说明: 无
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_InitAllJoints();
    
    /*
     * 函数说明: 重置所有关节
     * 注意事项: 需重新开关机时执行，自动清楚执行器报警
     * 参数说明: 无
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    
    short CM_ResetAllJoints();
    
    /*
     * 函数说明: 重置规划组
     * 注意事项: 需重新开关机时执行，自动清楚执行器报警
     * 参数说明: group：     ————规划组
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_ResetGroup(CtrlGroup group);
    
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
    short CM_SetXR1SoftLimitStatus(long status);
    
    /*
     * 函数说明: 清楚所有关节的报警
     * 注意事项: 初始化后执行
     * 参数说明: 无
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_ClearAllAlarm();
    
    /*
     * 函数说明: 获取规划组报警信息
     * 注意事项: 初始化后执行
     * 参数说明: group: 获取的规划组
               alarm: 获取的报警代码
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetGroupAlarm(CtrlGroup group, vector<long> &alarm);
    
    /*
     * 函数说明: 获取关节报警信息
     * 注意事项: 初始化后执行
     * 参数说明: joint: 获取的关节
               alarm: 获取的报警代码
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetJointAlarm(short joint, long &alarm);
    
    /*
     * 函数说明: 设置除轮子外的所有关节profile位置模式的加速度
     * 注意事项: 需在轴初始化后执行，运动中不可执行，
               不会自动保存，需调用CM_SaveParm函数
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_SetXR1ProfilePositionAcc(double acc);
    
    /*
     * 函数说明: 设置除轮子外的所有关节profile位置模式的速度
     * 注意事项: 需在轴初始化后执行，运动中不可执行，
               不会自动保存，需调用CM_SaveParm函数
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_SetXR1ProfilePositionVel(double vel);
    
    /*
     * 函数说明: 设置除轮子外的所有关节profile位置模式的减速度
     * 注意事项: 需在轴初始化后执行，运动中不可执行，
               不会自动保存，需调用CM_SaveParm函数
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_SetXR1ProfilePositionDec(double dec);
    
    /*
     * 函数说明: 获取规划组状态
     * 注意事项: 初始化后执行
     * 参数说明: group: 获取的规划组
              status：     ————获取的状态
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetGroupStatus(CtrlGroup group, vector<long> &status);
    
    /*
     * 函数说明: 获取关节报警信息
     * 注意事项: 初始化后执行
     * 参数说明: joint: 获取的关节
              alarm: 获取的报警代码
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetJointStatus(short joint, long &status);
    
    /*
     * 函数说明: 设置全身控制模式
     * 注意事项: 初始化后执行，运动中不可执行
     * 参数说明: group: 要设置的规划组
               mode: 要设置的控制模式
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_SetAllCtrlMode(CtrlMode mode);
    
    /*
     * 函数说明: 设置规划组控制模式
     * 注意事项: 初始化后执行，运动中不可执行
     * 参数说明: mode: 要设置的控制模式
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_SetGroupCtrlMode(CtrlGroup group, CtrlMode mode);
    
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
     * 函数说明: 获取全身控制模式
     * 注意事项: 初始化后执行
     * 参数说明: Ctrlmode：   ————获取的控制模式
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetAllCtrlMode(vector<long> &CtrlMode);
    
    /*
     * 函数说明: 获取规划组控制模式
     * 注意事项: 初始化后执行
     * 参数说明: group: 要获取的规划组
              Ctrlmode：   ————获取的控制模式
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetGroupCtrlMode(CtrlGroup group, vector<long> &CtrlMode);
    
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
     * 函数说明：设置所有关节的目标位置
     * 注意事项：初始化后，设置位置模式或prf位置模式后执行，单位：弧度
     * 参数说明：value： 目标位置
     * 返回说明：0: 成功
     **         其他: 参照错误代码
     * Note: 之前是单个axis设置，现在是通过Group的方式一把设置
     */
    short CM_SetAllPos(vector<double> value);

    /*
     * 函数说明：设置规划组的目标位置
     * 注意事项：初始化后，设置位置模式或prf位置模式后执行，单位：弧度
     * 参数说明：group: 要设置的规划组
     *         value: 目标位置
     * 返回说明：0: 成功
     *        其他: 参照错误代码
     * Note: 之前是单个axis设置，现在是通过Group的方式一把设置
     */
    short CM_SetGroupPos(CtrlGroup group, vector<double> value);
    
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
     * 函数说明: 获取规划组的当前位置
     * 注意事项: 初始化后执行，单位：弧度
     * 参数说明: group: 要获取的规划组
              value: 当前位置
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetGroupPos(CtrlGroup group, vector<double> &value);
    
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
     * 函数说明：设置规划组的目标速度
     * 注意事项：初始化后，设置速度模式或prf速度模式后执行，单位：弧度/s
     * 参数说明：group: 要设置的规划组
     *         value: 目标速度
     * 返回说明：0: 成功
     *        其他: 参照错误代码
     */
    short CM_SetGroupVel(CtrlGroup group, vector<double> value);
    
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
     * 函数说明: 获取规划组的当前速度
     * 注意事项: 初始化后执行，单位：弧度/s
     * 参数说明: group: 要获取的规划组
     *         value: 当前速度
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetGroupVel(CtrlGroup group, vector<double> &value);
    
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
     * 函数说明：设置规划组的目标电流
     * 注意事项：初始化后，设置电流模式后执行，单位：A
     * 参数说明：group: 要设置的规划组
     *        value: 目标电流
     * 返回说明：0 - 成功
     *        其他 - 参照错误代码
     * Note: 之前是单个axis设置，现在是通过Group的方式一把设置
     */
    short CM_SetGroupCur(CtrlGroup group, vector<double> value);
    
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
     * 函数说明: 获取规划组的当前电流
     * 注意事项: 初始化后，获取电流模式后执行，单位：A
     * 参数说明: group: 要获取的规划组
     *         value: 当前电流
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetGroupCur(CtrlGroup group, vector<double> &value);
    
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
     * 函数说明: 单关节带时间约束的位置梯型运动规划
     * 注意事项: 需在轴设置为profile位置模式后执行，运动中不可执行。
     *         若阻塞，则运动结束返回，若不阻塞，立即返回。
     * 参数说明: joint：设置的关节号
     *         pos：目标位置，单位：圈
     *         time：运行的时间，单位：ms
     *         ifBlock：是否阻塞
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_JointTrapMotion(short joint, double pos, long time, bool ifBlock = false);
    
    /*
     * 函数说明: 规划组同步启动停止位置梯型运动规划
     * 注意事项: 需在轴设置为profile位置模式后执行，运动中不可执行
     *         若阻塞，则运动结束返回，若不阻塞，立即返回。
     * 参数说明: group: 设置的组号
     *         pos: 目标位置，单位：圈
     *         time: 运行的时间，单位：ms
     *         ifBlock: 是否阻塞
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_SynGroupMotion(CtrlGroup group, vector<double> &pos, long time, bool ifBlock = false);

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
     * 函数说明: 获取规划组的当前：位置、速度和电流
     * 参数说明: group: 要获取的规划组
     *          pos: 位置, 单位：弧度
     *          vel: 速度, 单位：弧度/s
     *          cur: 电流, 单位：A
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetGroupPVC(CtrlGroup group, vector<double> &pos, vector<double> &vel, vector<double> &cur);

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

    //rad -> circle
    double XR1Pos2SCAPos(double rad, double ratio);
    //circle -> rad
    double SCAPos2XR1Pos(double circle, double ratio);
    //rad/s -> rpm
    double XR1Vel2SCAVel(double rad_s, double ratio);
    //rpm -> rad/s 
    double SCAVel2XR1Vel(double rpm, double ratio);
    //get vector of group joints
    CM_XR1_Interface();
    //none
    ~CM_XR1_Interface();

private:
    //get num of group joints
    vector<short> GetGroupJointNum(CtrlGroup group);

    // joint is invalid
    bool JointIsInvalid(short joint);

};



#endif