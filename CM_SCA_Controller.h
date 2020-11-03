/*
***************************************************************************************************
                                    Cloudminds (Shenzhen) Ltd.

                        (c) Coyright 2018, Cloudminds Ltd.,

* All rights reserved. Cloudminds's  source code is an unpublished work and the use of a copyright
* notice does not imply otherwise. This source code contains confidential, trade secret material of
* Cloudminds Ltd. Any attempt or participation in deciphering, decoding, reverse engineering
* or in any way altering the source code is strictly prohibited, unless the prior written consent
* of Cloudminds Ltd. is obtained.
*
* Filename:       	CM_SCA_Controller.h
* Programmer:       Tianhao Wang, John Liu
* Created:        	December 30th, 2019
* Description:		SCA controller interface based on ethernet protocol of innfos
*
* Note:				
* 1. Jun 15th, 2019 version 1.0, Tianhao Wang.
* 2. Sep 15th, 2019 version 1.1, John Liu.
*
***************************************************************************************************
*/

#ifndef CM_SCA_CONTROLLER_H
#define CM_SCA_CONTROLLER_H

/*---------------------------------------------------------------------------------------
------
------	Includes
------
---------------------------------------------------------------------------------------*/
#include <vector>
using namespace std;

enum ERR_CODE
{
    ERR_NONE = 0, //0无错误

    // 系统级错误
    ERR_SYS_BASE = 0,
    ERR_MALLOC_MEMORY = ERR_SYS_BASE - 1,          // 申请内存失败
    ERR_CREATE_THREAD = ERR_SYS_BASE - 2,          // 创建Thread失败
    ERR_THREAD_MUTEX_INIT = ERR_SYS_BASE - 3,      // 线程mutex初始化失败
    ERR_CREATE_SOCKET = ERR_SYS_BASE - 4,          // 创建Socket失败
    ERR_WAITTING_TIMEOUT = ERR_SYS_BASE - 5,       // 通讯超时
    ERR_COMMUNICATION_FAILED = ERR_SYS_BASE - 6,   // 通讯失败
    ERR_COMMUNICATION_SENDTO = ERR_SYS_BASE - 7,   // 通讯sendto失败
    ERR_COMMUNICATION_RECVFROM = ERR_SYS_BASE - 8, // 通讯recvfrom失败

    // 应用级错误
    ERR_APP_BASE = -100,
    ERR_INPUT_PARM1 = ERR_APP_BASE - 1,                  // 输入参数1错误
    ERR_INPUT_PARM2 = ERR_APP_BASE - 2,                  // 输入参数2错误
    ERR_INPUT_PARM3 = ERR_APP_BASE - 3,                  // 输入参数3错误
    ERR_INPUT_PARM4 = ERR_APP_BASE - 4,                  // 输入参数4错误
    ERR_INPUT_PARM = ERR_APP_BASE - 5,                   // 输入参数错误
    ERR_RTN_PARM = ERR_APP_BASE - 6,                     // 错误返回参数
    ERR_RTN_PARM_AXIS = ERR_APP_BASE - 7,                // 错误返回参数Axis不对
    ERR_RTN_PARM_CRC = ERR_APP_BASE - 8,                 // 错误返回参数CRC不对
    ERR_RTN_PARM_DATA_LEN = ERR_APP_BASE - 9,            // 错误返回数据长度不对
    ERR_NO_RESPONSE = ERR_APP_BASE - 10,                 // 执行器无应答
    ERR_STATUS = ERR_APP_BASE - 11,                      // 当前状态无法执行
    ERR_SAFEPARM = ERR_APP_BASE - 12,                    // 错误设置或未设置安全参数
    ERR_POSITIONTIME_MODE = ERR_APP_BASE - 13,           // PT模式错误
    ERR_EXECT = ERR_APP_BASE - 14,                       // 函数执行错误
    ERR_ACTUATOR_ALARM = ERR_APP_BASE - 15,              // 执行器报警
    ERR_NO_LIMITS = ERR_APP_BASE - 16,                   // 限位取消，不可运动
    ERR_VEL_STAGE_PROP = ERR_APP_BASE - 17,              // 梯形规划速度阶段比例错误
    ERR_ACC_STAGE_PROP = ERR_APP_BASE - 18,              // 梯形规划加速度阶段比例错误
    ERR_AXIS_NUM_IS_ZERO = ERR_APP_BASE - 19,            // 执行器个数为0
    ERR_AXIS_NO_FOUND = ERR_APP_BASE - 20,               // 没有找到对应的Axis
    ERR_AXIS_IS_OPENING = ERR_APP_BASE - 21,             // Axis正在opening
    ERR_AXIS_IS_RUNNING = ERR_APP_BASE - 22,             // Axis正在运行
    ERR_AXIS_IS_CLOSED = ERR_APP_BASE - 23,              // Axis已经关闭
    ERR_AXIS_ISNOT_POSITION_MODE = ERR_APP_BASE - 24,    // 当前不是Position模式
    ERR_AXIS_ISNOT_VELLOCITY_MODE = ERR_APP_BASE - 25,   // 当前不是Vellocity模式
    ERR_AXIS_ISNOT_CURRENT_MODE = ERR_APP_BASE - 26,     // 当前不是Current模式
    ERR_AXIS_ISNOT_HOMING_MODE = ERR_APP_BASE - 27,      // 当前不是Homing模式
    ERR_AXIS_LIMIT_STATUS_IS_FALSE = ERR_APP_BASE - 28,  // 当前LimitStatus为假
    ERR_AXIS_POSITION_IS_INCORRECT = ERR_APP_BASE - 29,  // Position的值不正确
    ERR_AXIS_VELLOCITY_IS_INCORRECT = ERR_APP_BASE - 30, // Vellocity的值不正确
    ERR_AXIS_MODE_IS_INCORRECT = ERR_APP_BASE - 31,      // 模式不正确

    // 未知错误
    ERR_UNKOWN = -10000,
    // ERR_UNKOWN = 0xffff, //0xffff未知错误
};

enum WARNING_CODE
{
    ALERT_STATUS = 1, // 状态警告
};

/*---------------------------------------------------------------------------------------
------
------	Structs
------
---------------------------------------------------------------------------------------*/
struct ConfigParm
{
    double CurProp;      //电流环P值
    double CurInteg;     //电流环I值
    double VelProp;      //速度环P值
    double VelInteg;     //速度环I值
    double PosProp;      //位置环P值
    double PosInteg;     //速度环I值
    bool FilterCStatus;  //电流环滤波器状态
    double FilterCValue; //电流环滤波器值
    bool FilterVStatus;  //速度环滤波器状态
    double FilterVValue; //速度环滤波器值
    bool FilterPStatus;  //位置环滤波器状态
    double FilterPValue; //位置环滤波器值
};

struct SafeParm
{
    double NegativeSoftLimit; //负限位
    double PositiveSoftLimit; //正限位
    //double MaxOutputCur;				    //最大输出电流（前沿驱动未提供）
    //double MinOutputCur;		    		//最小输出电流（前沿驱动未提供）
    //double MaxOutputAcc;				    //最大输出加速度（前沿驱动未提供）
    //double MinOutputAcc;				    //最小输出加速度（前沿驱动未提供）
    double MaxOutputVel; //最大输出速度
    double MinOutputVel; //最小输出速度
    double MaxOutputPos; //最大输出位置
    double MinOutputPos; //最小输出位置
    //double SmoothDec;					    //平滑减速度（前沿驱动未提供）
    //double AbruptDec;					    //急停减速度（前沿驱动未提供）
};

struct CommunicationData
{
    unsigned char SendAxis;     //发送的轴号
    unsigned char SendCmd;      //发送的指令
    unsigned char SendDataLen;  //发送的指令长度
    unsigned char SendData[5];  //发送的数据
    //unsigned char SendCrc[2];   //发送的crc校验
    unsigned char SendChar[32]; //发送的字符串
    unsigned int SendCharLen;

    unsigned char RtnAxis;    //返回的轴号
    unsigned char RtnCmd;     //返回的指令
    unsigned char RtnDataLen; //返回的数据长度

    // unsigned char RtnData[8];  //返回的数据
    // unsigned char RtnCrc[2];   //返回的crc校验
    // unsigned char RtnChar[32]; //返回的字符串

    unsigned char RtnData[32];  //返回的数据
    //unsigned char RtnCrc[2];   //返回的crc校验
    unsigned char RtnChar[64]; //返回的字符串

    unsigned int RtnCharLen;
};

/*---------------------------------------------------------------------------------------
------
------	Class
------
---------------------------------------------------------------------------------------*/
class CM_SCA_Controller
{
public:
    /*
     * System Configuration
     * /


    /*
     * 函数说明：设置系统参数
     * 注意事项：需在轴初始化后执行，不会自动保存，需调用CM_SaveParm函数
     * 参数说明：axis: 设定的轴号
     *         *parm: 设定的参数
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_SetConfigParm(short axis, ConfigParm *parm);

    /*
     * 函数说明：获取系统参数
     * 注意事项：需在轴初始化后执行
     * 参数说明：axis: 获取的轴号
     *         *parm: 获取的参数
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetConfigParm(short axis, ConfigParm *parm);

    /*
     * 函数说明：获取执行器温度
     * 注意事项：需在轴初始化后执行
     * 参数说明：axis: 获取的轴号
     *         T: 获取的温度
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetActuatorT(short axis, double &T);

    /*
     * 函数说明：获取驱动器温度
     * 注意事项：需在轴初始化后执行
     * 参数说明：axis: 获取的轴号
     *         T: 获取的温度
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetDriverT(short axis, double &T);

    /*
     * Security Configuration
     * /


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
    short CM_SetSoftLimitValue(short axis, double NSoftLimit, double PSoftLimit);

    /*
     * 函数说明：获取软限位
     * 注意事项：需在轴初始化后执行，安全起见
     * 参数说明：axis: 设定的轴号
     *         NSoftLimit: 负限位
     *         PSoftLimit: 正限位
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetSoftLimitValue(short axis, double &NSoftLimit, double &PSoftLimit);

    /*
     * 函数说明：设置安全参数
     * 注意事项：需在轴初始化后执行，安全起见，每次开机后需执行一次，
     *         不会自动保存，需调用CM_SaveParm函数
     * 参数说明：axis: 设定的轴号
     *         *parm: 设定的参数
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_SetSafeParm(short axis, SafeParm *parm);

    /*
     * 函数说明：获取系统参数
     * 注意事项：需在轴初始化后执行
     * 参数说明：axis: 设定的轴号
     *        *parm: 设定的参数
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetSafeParm(short axis, SafeParm *parm);

    /*
     * 函数说明：设置软限位是否生效
     * 注意事项：需在轴初始化后执行，不会自动保存，需调用CM_SaveParm函数
     * 参数说明：axis: 设定的轴号
     *         status: 0为关闭限位，1为开启限位
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_SetSoftLimitStatus(short axis, long status);

    /*
     * 函数说明：设置所有关节软限位是否生效
     * 注意事项：需在轴初始化后执行，不会自动保存，需调用CM_SaveParm函数
     * 参数说明：status: 0为关闭限位，1为开启限位
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_SetAllSoftLimitStatus(long status);

    /*
     * 函数说明：读取软限位是否生效
     * 注意事项：需在轴初始化后执行
     * 参数说明：axis: 设定的轴号
     *         status: 0为关闭限位，1为开启限位
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetSoftLimitStatus(short axis, long &status);

    /*
     * Motion Mode
     * /


    /*
     * 函数说明：设置为位置模式
     * 注意事项：需在轴初始化后执行，运动中不可执行
     * 参数说明：axis: 设置的轴号
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_SetPositionMode(short axis);

    /*
     * 函数说明：设置为profile位置模式
     * 注意事项：需在轴初始化后执行，运动中不可执行
     * 参数说明：axis: 设置的轴号
     * 返回说明：0 - 成功
               其他 - 参照错误代码
     */
    short CM_SetProfilePositionMode(short axis);

    /*
     * 函数说明：设置profile位置模式的加速度
     * 注意事项：需在轴初始化后执行，运动中不可执行，
     *         不会自动保存，需调用CM_SaveParm函数
     * 参数说明：axis: 设置的轴号
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_SetProfilePositionAcc(short axis, double acc);

    /*
     * 函数说明：设置profile位置模式的速度
     * 注意事项：需在轴初始化后执行，运动中不可执行，
     *         不会自动保存，需调用CM_SaveParm函数
     * 参数说明：axis: 设置的轴号
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_SetProfilePositionVel(short axis, double vel);

    /*
     * 函数说明：设置profile位置模式的减速度
     * 注意事项：需在轴初始化后执行，运动中不可执行，
     *         不会自动保存，需调用CM_SaveParm函数
     * 参数说明：axis: 设置的轴号
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_SetProfilePositionDec(short axis, double dec);

    /*
     * 函数说明：读取profile位置模式的加速度
     * 注意事项：需在轴初始化后执行，运动中不可执行
     * 参数说明：axis: 设置的轴号
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetProfilePositionAcc(short axis, double &acc);

    /*
     * 函数说明：读取profile位置模式的速度
     * 注意事项：需在轴初始化后执行，运动中不可执行
     * 参数说明：axis: 设置的轴号
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetProfilePositionVel(short axis, double &vel);

    /*
     * 函数说明：读取profile位置模式的减速度
     * 注意事项：需在轴初始化后执行，运动中不可执行
     * 参数说明：axis: 设置的轴号
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetProfilePositionDec(short axis, double &dec);

    /*
     * 函数说明：设置指定轴的目标位置，单位：圈
     * 注意事项：需在设置为位置模式或profile位置模式后使用，运动中不可执行
     * 参数说明: axis: 设置的轴号
     *         pos: 设置的目标位置
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */

    // 单个axis，单位double类型
    short CM_SetPosition(short axis, double pos);

    // 一组axis（同一个ECU下），单位double类型
    short CM_SetPosition(vector<short> axis, vector<double> pos);

    // 单个axis，单位long类型
    short CM_SetPosition(short axis, long pos);

    /*
     * 函数说明：单轴带时间约束的梯型运动规划
     * 注意事项：需在轴设置为profile位置模式后执行，运动中不可执行
     * 参数说明：axis: 设置的轴号
     *         pos: 目标位置，单位：圈
     *         t: 运行的时间，单位：ms
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_AxisTrapMotion(short axis, double pos, long t);

    /*
     * 函数说明：单轴带时间约束的梯型运动规划
     * 注意事项：需在轴设置为profile位置模式后执行，运动中不可执行
     * 参数说明：axis: 设置的轴号
     *         pos: 目标位置，单位：pulse
     *         t: 运行的时间，单位：ms
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_AxisTrapMotion(short axis, long pos, long t);

    /*
     * 函数说明：多轴同步启动停止梯型运动规划
     * 注意事项：需在轴设置为profile位置模式后执行，运动中不可执行
     * 参数说明：axis: 设置的轴号
     *         pos: 目标位置，单位：圈
     *         t: 运行的时间，单位：ms
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_SynMultiAxisMotion(vector<short> axis, vector<double> pos, long t);

    /*
     * 函数说明：多轴同步启动停止梯型运动规划
     * 注意事项：需在轴设置为profile位置模式后执行，运动中不可执行
     * 参数说明：axis: 设置的轴号
     *         pos: 目标位置，单位：pulse
     *         t: 运行的时间，单位：ms
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_SynMultiAxisMotion(vector<short> axis, vector<long> pos, long t);

    /*
     * 函数说明：设置为速度模式
     * 注意事项：需在轴初始化后执行，运动中不可执行
     * 参数说明：axis: 设置的轴号
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_SetVelocityMode(short axis);

    /*
     * 函数说明：设置为profile速度模式
     * 注意事项：需在轴初始化后执行，运动中不可执行，
     *         不会自动保存，需调用CM_SaveParm函数
     * 参数说明：axis: 设置的轴号
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_SetProfileVelocityMode(short axis);

    /*
     * 函数说明：设置profile速度模式的加速度
     * 注意事项：需在轴初始化后执行，运动中不可执行，
     *         不会自动保存，需调用CM_SaveParm函数
     * 参数说明：axis: 设置的轴号
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_SetProfileVelocityAcc(short axis, double acc);

    /*
     * 函数说明：设置profile速度模式的速度
     * 注意事项：需在轴初始化后执行，运动中不可执行，
     *         不会自动保存，需调用CM_SaveParm函数
     * 参数说明：axis: 设置的轴号
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_SetProfileVelocityVel(short axis, double vel);

    /*
     * 函数说明：设置profile速度模式的减速度
     * 注意事项：需在轴初始化后执行，运动中不可执行，
     *         不会自动保存，需调用CM_SaveParm函数
     * 参数说明：axis: 设置的轴号
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_SetProfileVelocityDec(short axis, double dec);

    /*
     * 函数说明：读取profile速度模式的加速度
     * 注意事项：需在轴初始化后执行，运动中不可执行
     * 参数说明：axis: 设置的轴号
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetProfileVelocityAcc(short axis, double &acc);

    /*
     * 函数说明：读取profile速度模式的速度
     * 注意事项：需在轴初始化后执行，运动中不可执行
     * 参数说明：axis: 设置的轴号
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetProfileVelocityVel(short axis, double &vel);

    /*
     * 函数说明：读取profile速度模式的减速度
     * 注意事项：需在轴初始化后执行，运动中不可执行
     * 参数说明：axis: 设置的轴号
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetProfileVelocityDec(short axis, double &dec);

    /*
     * 函数说明：设置指定轴的目标速度，单位：转/分
     * 注意事项：需要在设置为速度模式或profile速度模式后执行，运动中不可执行
     * 参数说明：axis： 设置的轴号
     *         vel: 设置的目标速度
     * 返回说明：0: 成功
     *         其他: 参照错误代码
     */

    // 单个axis，单位double类型
    short CM_SetVelocity(short axis, double vel);

    // 一组axis（同一个ECU下），单位double类型
    short CM_SetVelocity(vector<short> axis, vector<double> pos);

    // 单个axis，单位long类型
    short CM_SetVelocity(short axis, long vel);

    /*
     * 函数说明：设置为电流模式
     * 注意事项：需在轴初始化后执行，运动中不可执行
     * 参数说明：axis: 设置的轴号
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_SetCurrentMode(short axis);

    /*
     * 函数说明：设置指定轴的的目标电流
     * 注意事项：需在设置为电流模式后执行，运动中不可执行
     * 参数说明：axis：设置的轴号
     *         cur: 设置的目标电流值
     * 返回说明：0: 成功
     *         其他: 参照错误代码
     */

    // 单个axis，单位double类型
    short CM_SetCurrent(short axis, double cur);

    // 一组axis（同一个ECU下），单位double类型
    short CM_SetCurrent(vector<short> axis, vector<double> cur);

    /*
     * 函数说明：设置为homing模式
     * 注意事项：需在轴初始化后执行，运动中不可执行
     * 参数说明：axis： 设置的轴号
     *         operateMode: 1为手动，2为自动
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_SetHomingMode(short axis, int operateMode = 1);

    // PT mode

    /*
     * 函数说明：将指定轴设置为位置时间模式（预留）
     * 注意事项：需在轴初始化后执行，运动中不可执行
     * 参数说明：axis: 设置的轴号
     *         mode: 动态（1）或静态模式（0）
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_SetPositionTimeMode(short axis, short mode);

    /*
     * 函数说明：查询位置时间模式缓存区剩余大小（预留）
     * 注意事项：需在轴设置为位置时间模式设置缓存区后执行
     * 参数说明：axis: 设置的轴号
     *         space: 剩余的缓存区大小
     *         fifo: 缓存区的代号（0或1）
     * 返回说明：0 - 成功
     *        其他 - 参照错误代码
     */
    short CM_GetPositionTimeSpace(short axis, short &Space, short fifo);

    /*
     * 函数说明：将位置时间模式的数据压入缓存区（预留）
     * 注意事项：需在轴设置为位置时间模式设置了缓存区大小后执行，运动中不可执行
     * 参数说明：axis: 设置的轴号
     *         pos: 运动的目标位置
     *         time: 运动的目标时间
     *         type: 运动的类型（起始段、匀速段、停止段）
     *         fifo: 压入的缓存区代号（0或1）
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_PositionTimeData(short axis, double pos, long time, short type, short fifo);

    /*
     * 函数说明：清除位置时间模式缓存区中的数据（预留）
     * 注意事项：需在轴设置为位置时间模式设置了缓存区大小后执行，运动中不可执行
     * 参数说明：axis: 设置的轴号
     *         fifo: 压入的缓存区代号（0或1）
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_PositionTimeClear(short axis, short fifo);

    /*
     * 函数说明：设置位置时间模式循环次数（预留）
     * 注意事项：需在轴设置为位置时间模式压送了缓存区数据后执行，运动中不可执行
     * 参数说明：axis: 设置的轴号
     *         loop: 循环次数（0为无限循环）
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_SetPositionTimeLoop(short axis, long loop);

    /*
     * 函数说明：获取位置时间模式循环次数（预留）
     * 注意事项：需在轴设置为位置时间模式下执行
     * 参数说明：axis: 设置的轴号
     *         loop: 循环次数（0为无限循环）
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetPositionTimeLoop(short axis, long &loop);

    /*
     * 函数说明：启动指定轴号的位置时间模式运动（预留）
     * 注意事项：需在轴设置为位置时间模式压入数据后执行
     * 参数说明：mask: 设置的轴号
     *         option: 动态（1）或静态模式（0）
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_PositionTimeStart(long mask, long option);

    /*
     * 函数说明：设置指定轴位置时间模式的缓存区大小（预留）
     * 注意事项：需在轴设置为位置时间模式后执行，运动中不可执行
     * 参数说明：axis: 设置的轴号
     *         memory: 缓存区的大小
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_SetPositionTimeMemory(short axis, short memory);

    /*
     * 函数说明：设置指定轴位置时间模式的缓存区大小（预留）
     * 注意事项：需在轴设置为位置时间模式设置缓存区后执行
     * 参数说明：axis: 设置的轴号
     *         memory: 获取的缓存区的大小
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetPositionTimeMemory(short axis, short &memory);

    // Motion state detection

    /*
     * 函数说明：获取指定轴的状态
     * 注意事项：需在轴初始化后执行，运动中不可执行
     * 参数说明：axis: 获取的起始轴号
     *         sts: 获取的状态
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetStatus(short axis, long &sts);

    /*
     * 函数说明：查询执行器报警信息
     * 注意事项：轴初始化后报警可执行
     * 参数说明：AlarmInfo: 获取的报警代码
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetAlarmInfo(short axis, long &AlarmInfo);

    /*
     * 函数说明：清除指定轴的报警
     * 注意事项：需在轴初始化后执行，运动中不可执行
     * 参数说明：axis: 清除的起始轴号
     * 返回说明：0 - 成功
     *        其他 - 参照错误代码
     */
    short CM_ClearAlarm(short axis);

    /*
     * 函数说明：获取指定轴的模式
     * 注意事项：需在轴初始化后执行，运动中不可执行
     * 参数说明：axis: 获取的起始轴号
     *        Value: 获取的模式
     * 返回说明：0 - 成功
     *        其他 - 参照错误代码
     */
    short CM_GetProfileMode(short axis, long &value);

    /*
     * 函数说明：获取指定轴的三环数值
     * 注意事项：需在轴初始化后执行
     * 参数说明：axis: 获取的轴号
     *         pos: 获取的位置：单位：圈
     *         vel: 获取的速度：rpm
     *         cur: 获取的电流：A
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetProfilePVC(short axis, double &pos, double &vel, double &cur);

    /*
     * 函数说明：获取指定轴的三环数值
     * 注意事项：需在轴初始化后执行
     * 参数说明：axis: 获取的轴号
               pos: 获取的位置：单位：pulse
               vel: 获取的速度：pulse/ms
               cur: 获取的电流：A
     * 返回说明：0 - 成功
               其他 - 参照错误代码
     */
    short CM_GetProfilePVC(short axis, long &pos, long &vel, long &cur);

    /*
     * 函数说明：获取指定轴的当前位置，单位：圈
     * 注意事项：需在轴初始化后执行，运动中不可执行
     * 参数说明：axis: 获取的起始轴号
     *         value:  获取的位置
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetProfilePosition(short axis, double &value);

    /*
     * 函数说明：获取指定轴的当前位置，单位：pulse
     * 注意事项：需在轴初始化后执行，运动中不可执行
     * 参数说明：axis: 获取的起始轴号
     *         value:  获取的位置
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetProfilePosition(short axis, long &value);

    /*
     * 函数说明：获取指定轴的当前速度，单位：转/分
     * 注意事项：需在轴初始化后执行，运动中不可执行
     * 参数说明：axis: 获取的起始轴号
     *         value: 获取的速度
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetProfileVelocity(short axis, double &value);

    /*
     * 函数说明：获取指定轴的当前速度，单位：pulse/ms
     * 注意事项：需在轴初始化后执行，运动中不可执行
     * 参数说明：axis: 获取的起始轴号
     *         value: 获取的速度
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetProfileVelocity(short axis, long &value);

    /*
     * 函数说明：暂未实现
     */
    short CM_GetProfileAcc(short axis, double &value);

    /*
     * 函数说明：获取指定轴的当前电流
     * 注意事项：需在轴初始化后执行，运动中不可执行
     * 参数说明：axis: 获取的起始轴号
     *         value: 获取的电流
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetCurrent(short axis, double &value);

    /*
     * 函数说明：获取指定轴的抱闸状态
     * 注意事项：需在轴初始化后执行，运动中不可执行
     * 参数说明：axis: 获取的起始轴号
     *         state: 抱闸状态（0为松开，1为抱上）
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetBrakeState(short axis, short &state);

    /*
     * 函数说明：设置指定轴的抱闸状态
     * 注意事项：需在轴初始化后执行，运动中不可执行
     * 参数说明：axis: 获取的起始轴号
     *         state: 抱闸状态（0为松开，1为抱上）
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_SetBrakeState(short axis, short state);

    /*
     * 函数说明: 获取指定轴的当前电压
     * 参数说明: axis: 获取的起始轴号
     *         value: 获取的电压
     * 返回说明: 0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetProfileVoltage(short axis, double &value);

    /*
     * 函数说明：设置到位误差带（预留）
     * 注意事项：需在位置模式下执行，运动中不可执行
     * 参数说明：axis: 获取的起始轴号
     *         band: 误差带的值：pulse
     *         time: 在误差带中的最大时间
     * 返回说明：0 - 成功
     *        其他 - 参照错误代码
     */
    short CM_SetAxisBand(short axis, long band, long time);

    /*
     * 函数说明：获取到位误差带（预留）
     * 注意事项：运动中不可执行
     * 参数说明：axis: 获取的起始轴号
     *        band: 获取的误差带的值：pulse
     *        time: 获取的在误差带中的最大时间
     * 返回说明：0 - 成功
     *        其他 - 参照错误代码
     */
    short CM_GetAxisBand(short axis, long &Band, long &time);

    /*
     * 函数说明：轴停止（目前只能停一个轴），isRunning判断暂时取消
     * 注意事项：运动中调用生效
     * 参数说明：mask: 设定停止的轴号（按位）
     *        option:     ————急停缓停选项
     * 返回说明：0 - 成功
     *        其他 - 参照错误代码
     */
    short CM_Stop(short axis, long option);

    /*
     * 函数说明：得到IMU数据
     * 注意事项：
     * 参数说明：mask: 设定停止的轴号（按位）
     * 返回说明：0 - 成功
     *        其他 - 参照错误代码
     */
    short CM_GetImuData(double &w, double &x, double &y, double &z,
                        double &xa, double &ya, double &za, int &pres);

        // Other functions

        static short CM_InitController();

    short CM_Init();
    short CM_Release();

    /*
     * 函数说明：建立连接
     * 注意事项：在程序最开始执行
     * 参数说明：无
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_Connect();

    /*
     * 函数说明：断开连接，释放资源
     * 注意事项：需要断开连接时调用
     * 参数说明：无
     * 返回说明：0 成功
     *         其他 参照错误代码
     */
    short CM_Disconnect();

    /*
     * 函数说明：初始化所有轴
     * 注意事项：建立连接后执行，若部分轴已初始化，则返回错误
     * 参数说明：无
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_InitAll();

    /*
     * 函数说明：初始化指定轴
     * 注意事项：建立连接后执行，若已初始化，则返回-1警告，自动清除轴报警
     * 参数说明：axis: 初始化的轴号
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_InitAxis(vector<short> axis);

    /*
     * 函数说明：初始化指定轴
     * 注意事项：建立连接后执行，若已初始化，则返回-1警告，自动清除轴报警
     * 参数说明：axis: 初始化的轴号
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_InitAxis(short axis);

    /*
     * 函数说明：关闭所有轴（预留）
     * 注意事项：在程序最后执行，若部分轴未开启，则关闭所有已开启轴
     * 参数说明：无
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_CloseAll();

    /*
     * 函数说明：关闭指定轴
     * 注意事项：在程序最后执行，若已关闭，则返回警告代码
     * 参数说明：axis: 关闭的轴号
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_CloseAxis(vector<short> axis);

    /*
     * 函数说明：关闭指定轴
     * 注意事项：在程序最后执行，若已关闭，则返回警告代码
     * 参数说明：axis: 关闭的轴号
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_CloseAxis(short axis);

    /*
     * 函数说明：复位所有轴（预留）
     * 注意事项：初始化后可执行，恢复至初始化状态，运动中不可执行
     * 参数说明：无
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_ResetAll();

    /*
     * 函数说明：复位指定轴
     * 注意事项：初始化后可执行，恢复至初始化状态，运动中不可执行
     * 参数说明：axis: 复位的轴号
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_ResetAxis(vector<short> axis);

    /*
     * 函数说明：复位指定轴
     * 注意事项：初始化后可执行，恢复至初始化状态，运动中不可执行
     * 参数说明：axis: 复位的轴号
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_ResetAxis(short axis);

    /*
     * 函数说明：获取所有轴的ID
     * 注意事项：初始化所有轴后可执行，自动清除报警
     * 参数说明：vector：    ————获取的所有轴的ID
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetAllAxisID(vector<short> &ID);

    /*
     * 函数说明：修改轴的ID
     * 注意事项：初始化轴后可执行
     * 参数说明：ID1: 要修改的轴的ID
     *         ID2: 修改后的ID
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_ChangeAxisID(short ID1, short ID2);

    /*
     * 函数说明：保存指定轴的参数
     * 注意事项：初始化后可执行,执行一下几个函数后若需保存在执行器中，请调用该函数
              1. CM_SetConfigParm
              2. CM_SetSafeParm
              3. CM_SetSoftLimitStatus
              4. CM_SetProfilePositionAcc
              5. CM_SetProfilePositionVel
              6. CM_SetProfilePositionDec
              7. CM_SetProfileVelocityAcc
              8. CM_SetProfileVelocityVel
              9. CM_SetProfileVelocityDec
              10.CM_Zeros
              11.CM_ChangeAxisID
     * 参数说明：axis: 保存参数的轴号
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_SaveParm(short axis);

    /*
     * 函数说明：将当前位置设置成零位
     * 注意事项：初始化后可执行,会自动将限位设置成以改动后为基础的值
     * 参数说明：axis: 设置的轴号
     *         value:  零位的值
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_Zeros(short axis, double value);

    /*
     * 函数说明：获取控制器软件的版本号
     * 注意事项：初始化后可执行
     * 参数说明：Version: 获取的版本号
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetSWVersion(char *version);

    /*
     * 函数说明：获取执行器固件的版本号
     * 注意事项：初始化后可执行，version的空间需要>=12
     * 参数说明：version: 获取的版本号
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_GetHWVersion(short axis, char *version);

    /*
     * 函数说明：开始GetPVCTimer标志
     * 注意事项：connect以及init完成后，才能设置为true
     * 参数说明：flag: true启动定时器， false关闭定时器
     * 返回说明：0 - 成功
     *         其他 - 参照错误代码
     */
    short CM_StartGetPVCTimer(bool flag);

    //
    short SendBrakeTrue();
    short SendBrakeFalse();

    // pay no attentent about these
    CM_SCA_Controller();

    ~CM_SCA_Controller();

    static CM_SCA_Controller *getInstance();

private:
    // pay no attention about these functions

    // 从缓存中读取信息
    bool m_bReadInfoFromBuff;

    // 数据类型转换
    long IQ8(double value);
    double InvIQ8(long value);

    long IQ10(double value);
    double InvIQ10(long value);

    long IQ14(double value);
    double InvIQ14(long value);

    long IQ24(double value);
    double InvIQ24(long value);

    double InvIQ30(int value);
    double InvIQ16(int value);

    void Fix2Double(CommunicationData *CommData, double &value);

    void Double2Fix(CommunicationData *CommData, double &value);

    void Fix2Double1(CommunicationData *CommData, double &value);

    void Double2Fix1(CommunicationData *CommData, double &value);

    // 通讯相关函数
    // 未封装: setConfig, setPos/Vel/Cur, GetStatus->AlarmInfo, AlarmInfo, ClearAlarm, ChangeAxisID, PreWork, GetHWVersion
    // these functions also have thread lock
    short CommSend(CommunicationData *CommData);
    short CommRtn(CommunicationData *CommData);
    short CommProsses(CommunicationData *CommData);
     short CommProsses_pvc(CommunicationData *CommData);   

    short CommSend(short ip, CommunicationData *CommData);
    short CommRtn(short ip, CommunicationData *CommData);
    short CommProsses(short ip, CommunicationData *CommData);

    // 打包CommSend数据
    short PackageCommSendData(CommunicationData *CommData);

    // 清空socket缓存, 每次调用sendto之前调用
    void CleanSocketBuff(int sock);

    short RtnCheck(CommunicationData *CommData);
    void CRC16_1(unsigned char *pchMsg, short wDataLen, unsigned char *crc);

    // 根据指定axis的ip传输数据
    short TransCommData(short axis, short cmd, short DataLen, double data);

    // 通过指定ip传输数据
    short TransCommDataThruIP(short ip, short axis, short cmd, short DataLen, double data);
    short TransCommData1(short axis, short cmd, short DataLen, double data);

    // 通用的通讯数据处理
    short TransCommData(short axis, short cmd, short DataLen, double *data);

    // 特殊的通讯数据处理1
    short TransCommData1(short axis, short cmd, short DataLen, short stage, double *data);

    // 特殊的通讯数据处理2(当前是0x45读取电压，返回的真实值是2^10倍)
    short TransCommData2(short axis, short cmd, short DataLen, double *data);

    // 其他内部使用函数

    // 连接时的准备工作（这个时候只能通过ip，不能通过axis）
    short PrepareWork(short ip, vector<short> &axis);

    short GetCurrentRange(short axis, double &value);

    short IsOpened(short axis, bool &status);

    short Open(vector<short> axis);

    short Close(vector<short> axis);

    // 查找当前Axis的id在g_MotionInfo中的索引
    short AxisID2Index(short axis);

    // 初始化ECU相关信息
    short InitEcuRelatedInfo();

    // 去初始化ECU相关信息
    short DeinitEcuRelatedInfo();

    // 初始化得到PVC的Timer
    short InitPVCTimer();

    // 得到PVC的Timer函數
    static void *TimerGetPVC(void *parm);

    // 得到当前所有Axis的PVC
    short GetAllAxisPVC();

    // 得到指定ECU下面的所有Axis的PVC(以打包的方式发送)
    short GetEcuAxisPVC(unsigned short ip);
    short GetEcuAxisPVC2(unsigned short ip, unsigned char cmd);

    // 判断当前position值是否正确，并且修正pos的值
    bool PositionIsIncorrect(short index, double &pos);

    // 发送和接收打包数据（一次打包发送，recvCount个数接收，并且不对返回数据做处理）
    short SendAndRecvPackData(short ip, unsigned char *sendBuff, int sendLength, int recvCount);
};

#endif
