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

/*---------------------------------------------------------------------------------------
------
------	Includes
------
---------------------------------------------------------------------------------------*/
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <vector>
#include "CM_XR1_Interface.h"

#define Pi 3.14159265359
/*---------------------------------------------------------------------------------------
------
------	Global variables
------
---------------------------------------------------------------------------------------*/
vector<short> g_OmniWheelCtrlGroup;
vector<short> g_MainBodyCtrlGroup;
vector<short> g_HeadCtrlGroup;
vector<short> g_LeftArmCtrlGroup;
vector<short> g_RightArmCtrlGroup;
vector<short> g_LeftTrunkArmCtrlGroup;
vector<short> g_RightTrunkArmCtrlGroup;
vector<short> g_LeftHandCtrlGroup;
vector<short> g_RightHandCtrlGroup;

double g_ReductionRatio[] = {
    24.0, 24.0, 24.0,
    121.0, 81.0, 81.0, 81.0, 36.0, 36.0, 36.0,
    36.0, 36.0, 36.0, 36.0, 36.0, 39.015, 39.015,
    36.0, 36.0, 36.0, 36.0, 36.0, 39.015, 39.015,
    1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0};

extern CM_SCA_Controller SCACtrller;

/*---------------------------------------------------------------------------------------
------
------	Class
------
---------------------------------------------------------------------------------------*/
short CM_XR1_Interface::CM_ConnectXR1()
{
    return SCACtrller.CM_Connect();
}

short CM_XR1_Interface::CM_InitAllJoints()
{
    return SCACtrller.CM_InitAll();
}

short CM_XR1_Interface::CM_ResetAllJoints()
{
    return SCACtrller.CM_ResetAll();
}

short CM_XR1_Interface::CM_ResetGroup(CtrlGroup group)
{
    vector<short> GroupJoints;

    GroupJoints = GetGroupJointNum(group);
    return SCACtrller.CM_ResetAxis(GroupJoints);
}

short CM_XR1_Interface::CM_ResetJoint(short joint)
{
    vector<short> axis;
    axis.push_back(joint);
    return SCACtrller.CM_ResetAxis(axis);
}

short CM_XR1_Interface::CM_CloseAllJoints()
{
    return SCACtrller.CM_CloseAll();
}

short CM_XR1_Interface::CM_SetXR1SoftLimitStatus(long status)
{
    int i;
    short rtn = ERR_NONE;
    short tempRtn = ERR_NONE;

    for (i = MainBody; i <= XR1JointNum; i++)
    {
        tempRtn = SCACtrller.CM_SetSoftLimitStatus(i, status);
        if (tempRtn != 0)
        {
            rtn = tempRtn;
        }
    }
    return rtn;
}

short CM_XR1_Interface::CM_ClearAllAlarm()
{
    int i;
    short rtn = ERR_NONE;
    short tempRtn = ERR_NONE;

    for (i = OmniWheel; i <= XR1JointNum; i++)
    {
        tempRtn = SCACtrller.CM_ClearAlarm(i);
        if (tempRtn != 0)
        {
            rtn = tempRtn;
        }
    }
    return rtn;
}

short CM_XR1_Interface::CM_GetGroupAlarm(CtrlGroup group, vector<long> &alarm)
{
    int i;
    short rtn = ERR_NONE;
    short tempRtn = ERR_NONE;

    vector<short> GroupJoints;
    GroupJoints = GetGroupJointNum(group);
    alarm.resize(GroupJoints.size());
    for (i = 0; i < GroupJoints.size(); i++)
    {
        alarm.at(i) = 0;
        tempRtn = SCACtrller.CM_GetAlarmInfo(GroupJoints.at(i), alarm.at(i));
        if (0 != tempRtn)
        {
            rtn = tempRtn;
        }
    }
    return rtn;
}

short CM_XR1_Interface::CM_GetJointAlarm(short joint, long &alarm)
{
    alarm = 0;
    if (JointIsInvalid(joint))
    {
        return ERR_INPUT_PARM;
    }
    return SCACtrller.CM_GetAlarmInfo(joint, alarm);
}

short CM_XR1_Interface::CM_SetXR1ProfilePositionAcc(double acc)
{
    int i;
    short rtn = ERR_NONE;
    short tempRtn = ERR_NONE;

    for (i = MainBody; i < XR1JointNum; i++)
    {
        tempRtn = SCACtrller.CM_SetProfilePositionAcc(i, acc);
        if (tempRtn != 0)
        {
            rtn = tempRtn;
        }
    }
    return rtn;
}

short CM_XR1_Interface::CM_SetXR1ProfilePositionVel(double vel)
{
    int i;
    short rtn = ERR_NONE;
    short tempRtn = ERR_NONE;

    for (i = MainBody; i < XR1JointNum; i++)
    {
        tempRtn = SCACtrller.CM_SetProfilePositionVel(i, vel);
        if (tempRtn != 0)
        {
            rtn = tempRtn;
        }
    }
    return rtn;
}

short CM_XR1_Interface::CM_SetXR1ProfilePositionDec(double dec)
{
    int i;
    short rtn = ERR_NONE;
    short tempRtn = ERR_NONE;

    for (i = MainBody; i < XR1JointNum; i++)
    {
        tempRtn = SCACtrller.CM_SetProfilePositionDec(i, dec);
        if (tempRtn != 0)
        {
            rtn = tempRtn;
        }
    }
    return rtn;
}

short CM_XR1_Interface::CM_GetGroupStatus(CtrlGroup group, vector<long> &status)
{
    int i;
    short rtn = ERR_NONE;
    short tempRtn = ERR_NONE;

    vector<short> GroupJoints;

    GroupJoints = GetGroupJointNum(group);
    status.resize(GroupJoints.size());
    for (i = 0; i < GroupJoints.size(); i++)
    {
        status.at(i) = 0;
        tempRtn = SCACtrller.CM_GetStatus(GroupJoints.at(i), status.at(i));
        if (0 != tempRtn)
        {
            rtn = tempRtn;
        }
    }
    return rtn;
}

short CM_XR1_Interface::CM_GetJointStatus(short joint, long &status)
{
    status = 0;
    if (JointIsInvalid(joint))
    {
        return ERR_INPUT_PARM;
    }
    return SCACtrller.CM_GetStatus(joint, status);
}

short CM_XR1_Interface::CM_SetAllCtrlMode(CtrlMode mode)
{
    int i;
    short rtn = ERR_NONE;
    short tempRtn = ERR_NONE;

    switch (mode)
    {
    case CurCtrlMode:
        for (i = 1; i <= XR1JointNum; i++)
        {
            tempRtn = SCACtrller.CM_SetCurrentMode(i);
            if (0 != tempRtn)
            {
                rtn = tempRtn;
            }
        }
        break;
    case VelCtrlMode:
        for (i = 1; i <= XR1JointNum; i++)
        {
            tempRtn = SCACtrller.CM_SetVelocityMode(i);
            if (0 != tempRtn)
            {
                rtn = tempRtn;
            }
        }
        break;
    case PrfVelCtrlMode:
        for (i = 1; i <= XR1JointNum; i++)
        {
            tempRtn = SCACtrller.CM_SetProfileVelocityMode(i);
            if (0 != tempRtn)
            {
                rtn = tempRtn;
            }
        }
        break;
    case PosCtrlMode:
        for (i = 1; i <= XR1JointNum; i++)
        {
            tempRtn = SCACtrller.CM_SetPositionMode(i);
            if (0 != tempRtn)
            {
                rtn = tempRtn;
            }
        }
        break;
    case PrfPosCtrlMode:
        for (i = 1; i <= XR1JointNum; i++)
        {
            tempRtn = SCACtrller.CM_SetProfilePositionMode(i);
            if (0 != tempRtn)
            {
                rtn = tempRtn;
            }
        }
        break;
    default:
        break;
    }
    return rtn;
}

short CM_XR1_Interface::CM_SetGroupCtrlMode(CtrlGroup group, CtrlMode mode)
{
    int i;
    short rtn = ERR_NONE;
    short tempRtn = ERR_NONE;
    vector<short> GroupJoints;

    GroupJoints = GetGroupJointNum(group);
    switch (mode)
    {
    case CurCtrlMode:
        for (i = 0; i < GroupJoints.size(); i++)
        {
            tempRtn = SCACtrller.CM_SetCurrentMode(GroupJoints.at(i));
            if (0 != tempRtn)
            {
                rtn = tempRtn;
            }
        }
        break;
    case VelCtrlMode:
        for (i = 0; i < GroupJoints.size(); i++)
        {
            tempRtn = SCACtrller.CM_SetVelocityMode(GroupJoints.at(i));
            if (0 != tempRtn)
            {
                rtn = tempRtn;
            }
        }
        break;
    case PrfVelCtrlMode:
        for (i = 0; i < GroupJoints.size(); i++)
        {
            tempRtn = SCACtrller.CM_SetProfileVelocityMode(GroupJoints.at(i));
            if (0 != tempRtn)
            {
                rtn = tempRtn;
            }
        }
        break;
    case PosCtrlMode:
        for (i = 0; i < GroupJoints.size(); i++)
        {
            tempRtn = SCACtrller.CM_SetPositionMode(GroupJoints.at(i));
            if (0 != tempRtn)
            {
                rtn = tempRtn;
            }
        }
        break;
    case PrfPosCtrlMode:
        for (i = 0; i < GroupJoints.size(); i++)
        {
            tempRtn = SCACtrller.CM_SetProfilePositionMode(GroupJoints.at(i));
            if (0 != tempRtn)
            {
                rtn = tempRtn;
            }
        }
        break;
    default:
        break;
    }
    return rtn;
}

short CM_XR1_Interface::CM_SetJointCtrlMode(short joint, CtrlMode mode)
{
    short rtn = ERR_NONE;
    if (JointIsInvalid(joint))
    {
        return ERR_INPUT_PARM;
    }
    switch (mode)
    {
    case CurCtrlMode:
        rtn = SCACtrller.CM_SetCurrentMode(joint);
        if (0 != rtn)
        {
            return rtn;
        }
        break;
    case VelCtrlMode:
        rtn = SCACtrller.CM_SetVelocityMode(joint);
        if (0 != rtn)
        {
            return rtn;
        }
        break;
    case PrfVelCtrlMode:
        rtn = SCACtrller.CM_SetProfileVelocityMode(joint);
        if (0 != rtn)
        {
            return rtn;
        }
        break;
    case PosCtrlMode:
        rtn = SCACtrller.CM_SetPositionMode(joint);
        if (0 != rtn)
        {
            return rtn;
        }
        break;
    case PrfPosCtrlMode:
        rtn = SCACtrller.CM_SetProfilePositionMode(joint);
        if (0 != rtn)
        {
            return rtn;
        }
        break;
    default:
        break;
    }
    return rtn;
}

short CM_XR1_Interface::CM_GetAllCtrlMode(vector<long> &CtrlMode)
{
    int i;
    short rtn = ERR_NONE;
    short tempRtn = ERR_NONE;

    CtrlMode.resize(XR1JointNum);
    for (i = 0; i < XR1JointNum; i++)
    {
        tempRtn = SCACtrller.CM_GetProfileMode(i, CtrlMode.at(i));
        if (0 != tempRtn)
        {
            rtn = tempRtn;
        }
    }
    return rtn;
}

short CM_XR1_Interface::CM_GetGroupCtrlMode(CtrlGroup group, vector<long> &CtrlMode)
{
    int i;
    short rtn = ERR_NONE;
    short tempRtn = ERR_NONE;
    vector<short> GroupJoints;

    GroupJoints = GetGroupJointNum(group);
    CtrlMode.resize(GroupJoints.size());
    for (i = 0; i < GroupJoints.size(); i++)
    {
        tempRtn = SCACtrller.CM_GetProfileMode(GroupJoints.at(i), CtrlMode.at(i));
        if (0 != tempRtn)
        {
            rtn = tempRtn;
        }
    }
    return rtn;
}

short CM_XR1_Interface::CM_GetJointCtrlMode(short joint, long &CtrlMode)
{
    if (JointIsInvalid(joint))
    {
        return ERR_INPUT_PARM;
    }
    return SCACtrller.CM_GetProfileMode(joint, CtrlMode);
}

// short CM_XR1_Interface::CM_SetAllPos(vector<double> value)
// {
//     int i;
//     short rtn = ERR_NONE;
//     short tempRtn = ERR_NONE;

//     vector<double> pos;

//     if (XR1JointNum != value.size())
//     {
//         return ERR_INPUT_PARM;
//     }
//     for (i = 0; i < XR1JointNum; i++)
//     {
//         pos.push_back(XR1Pos2SCAPos(value.at(i), g_ReductionRatio[i]));
//         tempRtn = SCACtrller.CM_SetPosition(i + 1, pos.at(i));
//         if (0 != tempRtn)
//         {
//             rtn = tempRtn;
//         }
//     }
//     return rtn;
// }

short CM_XR1_Interface::CM_SetAllPos(vector<double> value)
{
    int i = 0, j = 0;
    short rtn = ERR_NONE;
    short tempRtn = ERR_NONE;
    vector<double> pos;
    vector<double> val1, val2, val3, val4, val5, val6, val7;

    if (XR1JointNum != value.size())
    {
        return ERR_INPUT_PARM;
    }

    for (i = 0; i < XR1JointNum; i++)
    {
        pos.push_back(XR1Pos2SCAPos(value.at(i), g_ReductionRatio[i]));
    }

    // Note: 当前以组的方式发送数据

    // [1,4)
    j = 0;
    for (i = 0; i < g_OmniWheelCtrlGroup.size(); i++)
    {
        val1.push_back(pos.at(i));
    }
    rtn = SCACtrller.CM_SetPosition(g_OmniWheelCtrlGroup, val1);

    // [4,8)
    j += g_OmniWheelCtrlGroup.size();
    for (i = 0; i < g_MainBodyCtrlGroup.size(); i++)
    {
        val2.push_back(pos.at(j + i));
    }
    rtn = SCACtrller.CM_SetPosition(g_MainBodyCtrlGroup, val2);

    // [8,11)
    j += g_MainBodyCtrlGroup.size();
    for (i = 0; i < g_HeadCtrlGroup.size(); i++)
    {
        val3.push_back(pos.at(j + i));
    }
    rtn = SCACtrller.CM_SetPosition(g_HeadCtrlGroup, val3);

    // [11,18)
    j += g_HeadCtrlGroup.size();
    for (i = 0; i < g_LeftArmCtrlGroup.size(); i++)
    {
        val4.push_back(pos.at(j + i));
    }
    rtn = SCACtrller.CM_SetPosition(g_LeftArmCtrlGroup, val4);

    // [18, 25)
    j += g_LeftArmCtrlGroup.size();
    for (i = 0; i < g_RightArmCtrlGroup.size(); i++)
    {
        val5.push_back(pos.at(j + i));
    }
    rtn = SCACtrller.CM_SetPosition(g_RightArmCtrlGroup, val5);

    // [25, 30)
    j += g_RightArmCtrlGroup.size();
    for (i = 0; i < g_LeftHandCtrlGroup.size(); i++)
    {
        val6.push_back(pos.at(j + i));
    }
    rtn = SCACtrller.CM_SetPosition(g_LeftHandCtrlGroup, val6);

    // [30, 34]
    j += g_LeftHandCtrlGroup.size();
    for (i = 0; i < g_RightHandCtrlGroup.size(); i++)
    {
        val7.push_back(pos.at(j + i));
    }
    rtn = SCACtrller.CM_SetPosition(g_RightHandCtrlGroup, val7);

    return rtn;
}

// short CM_XR1_Interface::CM_SetGroupPos(CtrlGroup group, vector<double> value)
// {
//     int i;
//     short rtn = ERR_NONE;
//     short tempRtn = ERR_NONE;
//     vector<short> GroupJoints;
//     vector<double> pos;

//     GroupJoints = GetGroupJointNum(group);
//     if (GroupJoints.size() != value.size())
//     {
//         return ERR_INPUT_PARM;
//     }
//     for (i = 0; i < GroupJoints.size(); i++)
//     {
//         pos.push_back(XR1Pos2SCAPos(value.at(i), g_ReductionRatio[GroupJoints.at(i) - 1]));
//         tempRtn = SCACtrller.CM_SetPosition(GroupJoints.at(i), pos.at(i));
//         if (0 != tempRtn)
//         {
//             rtn = tempRtn;
//         }
//     }
//     return rtn;
// }

short CM_XR1_Interface::CM_SetGroupPos(CtrlGroup group, vector<double> value)
{
    int i;
    short rtn = ERR_NONE;
    short rtn1 = ERR_NONE, rtn2 = ERR_NONE;
    vector<short> GroupJoints;
    vector<double> pos;
    vector<double> pos1, pos2;

    GroupJoints = GetGroupJointNum(group);
    if (GroupJoints.size() != value.size())
    {
        return ERR_INPUT_PARM;
    }

    for (i = 0; i < GroupJoints.size(); i++)
    {
        pos.push_back(XR1Pos2SCAPos(value.at(i), g_ReductionRatio[GroupJoints.at(i) - 1]));
    }

    // Note: LeftTrunkArmCtrlGroup和RightTrunkArmCtrlGroup涉及到2个Group（2个ECU），所以需要分开发送

    if (group == LeftTrunkArmCtrlGroup)
    {
        for (i = 0; i < g_MainBodyCtrlGroup.size(); i++)
        {
            pos1.push_back(pos.at(i));
        }
        rtn1 = SCACtrller.CM_SetPosition(g_MainBodyCtrlGroup, pos1);

        for (i = 0; i < g_LeftArmCtrlGroup.size(); i++)
        {
            pos2.push_back(pos.at(g_MainBodyCtrlGroup.size() + i));
        }
        rtn2 = SCACtrller.CM_SetPosition(g_LeftArmCtrlGroup, pos2);
        rtn = (rtn1 == ERR_NONE ? rtn2 : rtn1);
    }
    else if (group == RightTrunkArmCtrlGroup)
    {
        for (i = 0; i < g_MainBodyCtrlGroup.size(); i++)
        {
            pos1.push_back(pos.at(i));
        }
        rtn1 = SCACtrller.CM_SetPosition(g_MainBodyCtrlGroup, pos1);

        for (i = 0; i < g_RightArmCtrlGroup.size(); i++)
        {
            pos2.push_back(pos.at(g_MainBodyCtrlGroup.size() + i));
        }
        rtn2 = SCACtrller.CM_SetPosition(g_RightArmCtrlGroup, pos2);
        rtn = (rtn1 == ERR_NONE ? rtn2 : rtn1);
    }
    else
    {
        rtn = SCACtrller.CM_SetPosition(GroupJoints, pos);
    }

    return rtn;
}

short CM_XR1_Interface::CM_SetJointPos(short joint, double value)
{
    double pos;

    cout << "CM_XR1_Interface::CM_SetJointPos, joint = " << joint << ", value = " << value << endl;

    if (JointIsInvalid(joint))
    {
        cout << "CM_XR1_Interface::CM_SetJointPos - 1" << endl;
        return ERR_INPUT_PARM;
    }
    pos = XR1Pos2SCAPos(value, g_ReductionRatio[joint - 1]);
    return SCACtrller.CM_SetPosition(joint, pos);
}

short CM_XR1_Interface::CM_GetAllPos(vector<double> &value)
{
    int i;
    short rtn = ERR_NONE;
    short tempRtn = ERR_NONE;

    vector<double> pos;

    value.resize(XR1JointNum);
    pos.resize(XR1JointNum);
    for (i = 0; i < XR1JointNum; i++)
    {
        tempRtn = SCACtrller.CM_GetProfilePosition(i + 1, pos.at(i));
        if (0 != tempRtn)
        {
            rtn = tempRtn;
        }
        value.at(i) = SCAPos2XR1Pos(pos.at(i), g_ReductionRatio[i]);
    }
    return rtn;
}

short CM_XR1_Interface::CM_GetGroupPos(CtrlGroup group, vector<double> &value)
{
    int i;
    short rtn = ERR_NONE;
    short tempRtn = ERR_NONE;
    vector<short> GroupJoints;
    vector<double> pos;

    GroupJoints = GetGroupJointNum(group);
    value.resize(GroupJoints.size());
    pos.resize(GroupJoints.size());
    for (i = 0; i < GroupJoints.size(); i++)
    {
        tempRtn = SCACtrller.CM_GetProfilePosition(GroupJoints.at(i), pos.at(i));
        if (0 != tempRtn)
        {
            rtn = tempRtn;
        }
        value.at(i) = SCAPos2XR1Pos(pos.at(i), g_ReductionRatio[GroupJoints.at(i) - 1]);
    }
    return rtn;
}

short CM_XR1_Interface::CM_GetJointPos(short joint, double &value)
{
    short rtn = ERR_NONE;
    double pos;

    if (JointIsInvalid(joint))
    {
        return ERR_INPUT_PARM;
    }
    rtn = SCACtrller.CM_GetProfilePosition(joint, pos);
    if (0 != rtn)
    {
        return rtn;
    }
    value = SCAPos2XR1Pos(pos, g_ReductionRatio[joint - 1]);
    return rtn;
}

// short CM_XR1_Interface::CM_SetAllVel(vector<double> value)
// {
//     int i;
//     short rtn = ERR_NONE;
//     short tempRtn = ERR_NONE;

//     vector<double> vel;

//     if (XR1JointNum != value.size())
//     {
//         return ERR_INPUT_PARM;
//     }
//     for (i = 0; i < XR1JointNum; i++)
//     {
//         vel.push_back(XR1Vel2SCAVel(value.at(i), g_ReductionRatio[i]));
//         tempRtn = SCACtrller.CM_SetVelocity(i + 1, vel.at(i));
//         if (0 != tempRtn)
//         {
//             rtn = tempRtn;
//         }
//     }
//     return rtn;
// }

short CM_XR1_Interface::CM_SetAllVel(vector<double> value)
{
    int i = 0, j = 0;
    short rtn = ERR_NONE;
    short tempRtn = ERR_NONE;
    vector<double> vel;
    vector<double> val1, val2, val3, val4, val5, val6, val7;

    if (XR1JointNum != value.size())
    {
        return ERR_INPUT_PARM;
    }

    for (i = 0; i < XR1JointNum; i++)
    {
        vel.push_back(XR1Vel2SCAVel(value.at(i), g_ReductionRatio[i]));
    }

    // Note: 当前以组的方式发送数据

    // [1,4)
    j = 0;
    for (i = 0; i < g_OmniWheelCtrlGroup.size(); i++)
    {
        val1.push_back(vel.at(i));
    }
    rtn = SCACtrller.CM_SetVelocity(g_OmniWheelCtrlGroup, val1);

    // [4,8)
    j += g_OmniWheelCtrlGroup.size();
    for (i = 0; i < g_MainBodyCtrlGroup.size(); i++)
    {
        val2.push_back(vel.at(j + i));
    }
    rtn = SCACtrller.CM_SetVelocity(g_MainBodyCtrlGroup, val2);

    // [8,11)
    j += g_MainBodyCtrlGroup.size();
    for (i = 0; i < g_HeadCtrlGroup.size(); i++)
    {
        val3.push_back(vel.at(j + i));
    }
    rtn = SCACtrller.CM_SetVelocity(g_HeadCtrlGroup, val3);

    // [11,18)
    j += g_HeadCtrlGroup.size();
    for (i = 0; i < g_LeftArmCtrlGroup.size(); i++)
    {
        val4.push_back(vel.at(j + i));
    }
    rtn = SCACtrller.CM_SetVelocity(g_LeftArmCtrlGroup, val4);

    // [18, 25)
    j += g_LeftArmCtrlGroup.size();
    for (i = 0; i < g_RightArmCtrlGroup.size(); i++)
    {
        val5.push_back(vel.at(j + i));
    }
    rtn = SCACtrller.CM_SetVelocity(g_RightArmCtrlGroup, val5);

    // [25, 30)
    j += g_RightArmCtrlGroup.size();
    for (i = 0; i < g_LeftHandCtrlGroup.size(); i++)
    {
        val6.push_back(vel.at(j + i));
    }
    rtn = SCACtrller.CM_SetVelocity(g_LeftHandCtrlGroup, val6);

    // [30, 34]
    j += g_LeftHandCtrlGroup.size();
    for (i = 0; i < g_RightHandCtrlGroup.size(); i++)
    {
        val7.push_back(vel.at(j + i));
    }
    rtn = SCACtrller.CM_SetVelocity(g_RightHandCtrlGroup, val7);

    return rtn;
}

// short CM_XR1_Interface::CM_SetGroupVel(CtrlGroup group, vector<double> value)
// {
//     int i;
//     short rtn = ERR_NONE;
//     short tempRtn = ERR_NONE;
//     vector<short> GroupJoints;
//     vector<double> vel;

//     GroupJoints = GetGroupJointNum(group);
//     if (GroupJoints.size() != value.size())
//     {
//         return ERR_INPUT_PARM;
//     }
//     for (i = 0; i < GroupJoints.size(); i++)
//     {
//         vel.push_back(XR1Vel2SCAVel(value.at(i), g_ReductionRatio[GroupJoints.at(i) - 1]));
//         tempRtn = SCACtrller.CM_SetVelocity(GroupJoints.at(i), vel.at(i));
//         if (0 != tempRtn)
//         {
//             rtn = tempRtn;
//         }
//     }
//     return rtn;
// }

short CM_XR1_Interface::CM_SetGroupVel(CtrlGroup group, vector<double> value)
{
    int i;
    short rtn = ERR_NONE;
    short rtn1 = ERR_NONE, rtn2 = ERR_NONE;
    vector<short> GroupJoints;
    vector<double> vel;
    vector<double> vel1, vel2;

    GroupJoints = GetGroupJointNum(group);
    if (GroupJoints.size() != value.size())
    {
        return ERR_INPUT_PARM;
    }

    for (i = 0; i < GroupJoints.size(); i++)
    {
        vel.push_back(XR1Vel2SCAVel(value.at(i), g_ReductionRatio[GroupJoints.at(i) - 1]));
    }

    // Note: LeftTrunkArmCtrlGroup和RightTrunkArmCtrlGroup涉及到2个Group（2个ECU），所以需要分开发送

    if (group == LeftTrunkArmCtrlGroup)
    {
        for (i = 0; i < g_MainBodyCtrlGroup.size(); i++)
        {
            vel1.push_back(vel.at(i));
        }
        rtn1 = SCACtrller.CM_SetVelocity(g_MainBodyCtrlGroup, vel1);

        for (i = 0; i < g_LeftArmCtrlGroup.size(); i++)
        {
            vel2.push_back(vel.at(g_MainBodyCtrlGroup.size() + i));
        }
        rtn2 = SCACtrller.CM_SetVelocity(g_LeftArmCtrlGroup, vel2);
        rtn = (rtn1 == ERR_NONE ? rtn2 : rtn1);
    }
    else if (group == RightTrunkArmCtrlGroup)
    {
        for (i = 0; i < g_MainBodyCtrlGroup.size(); i++)
        {
            vel1.push_back(vel.at(i));
        }
        rtn1 = SCACtrller.CM_SetVelocity(g_MainBodyCtrlGroup, vel1);

        for (i = 0; i < g_RightArmCtrlGroup.size(); i++)
        {
            vel2.push_back(vel.at(g_MainBodyCtrlGroup.size() + i));
        }
        rtn2 = SCACtrller.CM_SetVelocity(g_RightArmCtrlGroup, vel2);
        rtn = (rtn1 == ERR_NONE ? rtn2 : rtn1);
    }
    else
    {
        rtn = SCACtrller.CM_SetVelocity(GroupJoints, vel);
    }

    return rtn;
}

short CM_XR1_Interface::CM_SetJointVel(short joint, double value)
{
    double vel;

    if (JointIsInvalid(joint))
    {
        return ERR_INPUT_PARM;
    }
    vel = XR1Vel2SCAVel(value, g_ReductionRatio[joint - 1]);
    return SCACtrller.CM_SetVelocity(joint, vel);
}

short CM_XR1_Interface::CM_GetAllVel(vector<double> &value)
{
    int i;
    short rtn = ERR_NONE;
    short tempRtn = ERR_NONE;

    vector<double> vel;

    value.resize(XR1JointNum);
    vel.resize(XR1JointNum);
    for (i = 0; i < LeftHand - 1; i++)
    {
        tempRtn = SCACtrller.CM_GetProfileVelocity(i + 1, vel.at(i));
        if (0 != tempRtn)
        {
            rtn = tempRtn;
        }
        value.at(i) = SCAVel2XR1Vel(vel.at(i), g_ReductionRatio[i]);
    }
    return rtn;
}

short CM_XR1_Interface::CM_GetGroupVel(CtrlGroup group, vector<double> &value)
{
    int i;
    short rtn = ERR_NONE;
    short tempRtn = ERR_NONE;
    vector<short> GroupJoints;
    vector<double> vel;

    GroupJoints = GetGroupJointNum(group);
    value.resize(GroupJoints.size());
    vel.resize(GroupJoints.size());
    for (i = 0; i < GroupJoints.size(); i++)
    {
        tempRtn = SCACtrller.CM_GetProfileVelocity(GroupJoints.at(i), vel.at(i));
        if (0 != tempRtn)
        {
            rtn = tempRtn;
        }
        value.at(i) = SCAVel2XR1Vel(vel.at(i), g_ReductionRatio[GroupJoints.at(i) - 1]);
    }
    return rtn;
}

short CM_XR1_Interface::CM_GetJointVel(short joint, double &value)
{
    short rtn = ERR_NONE;
    double vel;

    if (JointIsInvalid(joint))
    {
        return ERR_INPUT_PARM;
    }
    rtn = SCACtrller.CM_GetProfileVelocity(joint, vel);
    if (0 != rtn)
    {
        return rtn;
    }
    value = SCAVel2XR1Vel(vel, g_ReductionRatio[joint - 1]);
    return rtn;
}

// short CM_XR1_Interface::CM_SetAllCur(vector<double> value)
// {
//     int i;
//     short rtn = ERR_NONE;
//     short tempRtn = ERR_NONE;

//     if (XR1JointNum != value.size())
//     {
//         return ERR_INPUT_PARM;
//     }
//     for (i = 0; i < XR1JointNum; i++)
//     {
//         tempRtn = SCACtrller.CM_SetCurrent(i + 1, value.at(i));
//         if (0 != tempRtn)
//         {
//             rtn = tempRtn;
//         }
//     }
//     return rtn;
// }

short CM_XR1_Interface::CM_SetAllCur(vector<double> value)
{
    int i = 0, j = 0;
    short rtn = ERR_NONE;
    short tempRtn = ERR_NONE;
    vector<double> cur;
    vector<double> val1, val2, val3, val4, val5, val6, val7;

    if (XR1JointNum != value.size())
    {
        return ERR_INPUT_PARM;
    }

    for (i = 0; i < XR1JointNum; i++)
    {
        cur.push_back(value.at(i));
    }

    // Note: 当前以组的方式发送数据

    // [1,4)
    j = 0;
    for (i = 0; i < g_OmniWheelCtrlGroup.size(); i++)
    {
        val1.push_back(cur.at(i));
    }
    rtn = SCACtrller.CM_SetCurrent(g_OmniWheelCtrlGroup, val1);

    // [4,8)
    j += g_OmniWheelCtrlGroup.size();
    for (i = 0; i < g_MainBodyCtrlGroup.size(); i++)
    {
        val2.push_back(cur.at(j + i));
    }
    rtn = SCACtrller.CM_SetCurrent(g_MainBodyCtrlGroup, val2);

    // [8,11)
    j += g_MainBodyCtrlGroup.size();
    for (i = 0; i < g_HeadCtrlGroup.size(); i++)
    {
        val3.push_back(cur.at(j + i));
    }
    rtn = SCACtrller.CM_SetCurrent(g_HeadCtrlGroup, val3);

    // [11,18)
    j += g_HeadCtrlGroup.size();
    for (i = 0; i < g_LeftArmCtrlGroup.size(); i++)
    {
        val4.push_back(cur.at(j + i));
    }
    rtn = SCACtrller.CM_SetCurrent(g_LeftArmCtrlGroup, val4);

    // [18, 25)
    j += g_LeftArmCtrlGroup.size();
    for (i = 0; i < g_RightArmCtrlGroup.size(); i++)
    {
        val5.push_back(cur.at(j + i));
    }
    rtn = SCACtrller.CM_SetCurrent(g_RightArmCtrlGroup, val5);

    // [25, 30)
    j += g_RightArmCtrlGroup.size();
    for (i = 0; i < g_LeftHandCtrlGroup.size(); i++)
    {
        val6.push_back(cur.at(j + i));
    }
    rtn = SCACtrller.CM_SetCurrent(g_LeftHandCtrlGroup, val6);

    // [30, 34]
    j += g_LeftHandCtrlGroup.size();
    for (i = 0; i < g_RightHandCtrlGroup.size(); i++)
    {
        val7.push_back(cur.at(j + i));
    }
    rtn = SCACtrller.CM_SetCurrent(g_RightHandCtrlGroup, val7);

    return rtn;
}

// short CM_XR1_Interface::CM_SetGroupCur(CtrlGroup group, vector<double> value)
// {
//     int i;
//     short rtn = ERR_NONE;
//     short tempRtn = ERR_NONE;
//     vector<short> GroupJoints;

//     GroupJoints = GetGroupJointNum(group);
//     if (GroupJoints.size() != value.size())
//     {
//         return ERR_INPUT_PARM;
//     }
//     for (i = 0; i < GroupJoints.size(); i++)
//     {
//         tempRtn = SCACtrller.CM_SetCurrent(GroupJoints.at(i), value.at(i));
//         if (0 != tempRtn)
//         {
//             rtn = tempRtn;
//         }
//     }
//     return rtn;
// }

short CM_XR1_Interface::CM_SetGroupCur(CtrlGroup group, vector<double> value)
{
    int i;
    short rtn = ERR_NONE;
    short rtn1 = ERR_NONE, rtn2 = ERR_NONE;
    vector<short> GroupJoints;
    vector<double> cur;
    vector<double> cur1, cur2;

    GroupJoints = GetGroupJointNum(group);
    if (GroupJoints.size() != value.size())
    {
        return ERR_INPUT_PARM;
    }

    for (i = 0; i < GroupJoints.size(); i++)
    {
        cur.push_back(value.at(i));
    }

    // Note: LeftTrunkArmCtrlGroup和RightTrunkArmCtrlGroup涉及到2个Group（2个ECU），所以需要分开发送

    if (group == LeftTrunkArmCtrlGroup)
    {
        for (i = 0; i < g_MainBodyCtrlGroup.size(); i++)
        {
            cur1.push_back(cur.at(i));
        }
        rtn1 = SCACtrller.CM_SetVelocity(g_MainBodyCtrlGroup, cur1);

        for (i = 0; i < g_LeftArmCtrlGroup.size(); i++)
        {
            cur2.push_back(cur.at(g_MainBodyCtrlGroup.size() + i));
        }
        rtn2 = SCACtrller.CM_SetVelocity(g_LeftArmCtrlGroup, cur2);
        rtn = (rtn1 == ERR_NONE ? rtn2 : rtn1);
    }
    else if (group == RightTrunkArmCtrlGroup)
    {
        for (i = 0; i < g_MainBodyCtrlGroup.size(); i++)
        {
            cur1.push_back(cur.at(i));
        }
        rtn1 = SCACtrller.CM_SetVelocity(g_MainBodyCtrlGroup, cur1);

        for (i = 0; i < g_RightArmCtrlGroup.size(); i++)
        {
            cur2.push_back(cur.at(g_MainBodyCtrlGroup.size() + i));
        }
        rtn2 = SCACtrller.CM_SetVelocity(g_RightArmCtrlGroup, cur2);
        rtn = (rtn1 == ERR_NONE ? rtn2 : rtn1);
    }
    else
    {
        rtn = SCACtrller.CM_SetVelocity(GroupJoints, cur);
    }

    return rtn;
}

short CM_XR1_Interface::CM_SetJointCur(short joint, double value)
{
    if (JointIsInvalid(joint))
    {
        return ERR_INPUT_PARM;
    }
    return SCACtrller.CM_SetCurrent(joint, value);
}

short CM_XR1_Interface::CM_GetAllCur(vector<double> &value)
{
    int i;
    short rtn = ERR_NONE;
    short tempRtn = ERR_NONE;

    value.resize(XR1JointNum);
    for (i = 0; i < XR1JointNum; i++)
    {
        tempRtn = SCACtrller.CM_GetCurrent(i + 1, value.at(i));
        if (0 != tempRtn)
        {
            rtn = tempRtn;
        }
    }
    return rtn;
}

short CM_XR1_Interface::CM_GetGroupCur(CtrlGroup group, vector<double> &value)
{
    int i;
    short rtn = ERR_NONE;
    short tempRtn = ERR_NONE;
    vector<short> GroupJoints;

    GroupJoints = GetGroupJointNum(group);
    value.resize(GroupJoints.size());
    for (i = 0; i < GroupJoints.size(); i++)
    {
        tempRtn = SCACtrller.CM_GetCurrent(GroupJoints.at(i), value.at(i));
        if (0 != tempRtn)
        {
            rtn = tempRtn;
        }
    }
    return rtn;
}

short CM_XR1_Interface::CM_GetJointCur(short joint, double &value)
{
    if (JointIsInvalid(joint))
    {
        return ERR_INPUT_PARM;
    }
    return SCACtrller.CM_GetCurrent(joint, value);
}

short CM_XR1_Interface::CM_JointTrapMotion(short joint, double pos, long time, bool ifBlock)
{
    short rtn = ERR_NONE;
    double vel = 999;
    long val;

    if (JointIsInvalid(joint))
    {
        return ERR_INPUT_PARM;
    }
    rtn = SCACtrller.CM_AxisTrapMotion(joint, pos, time);
    if (0 != rtn)
    {
        return rtn;
    }
    if (ifBlock)
    {
        usleep(200000);
        do
        {
            //rtn = SCACtrller.CM_GetStatus(joint, val);
            SCACtrller.CM_GetProfileVelocity(joint, vel);
            usleep(100);
        } while (vel > 5.0);
        //}while(val == AXIS_RUNNING);
    }
    return rtn;
}

short CM_XR1_Interface::CM_SynGroupMotion(CtrlGroup group, vector<double> &pos, long time, bool ifBlock)
{
    int i;
    short rtn = ERR_NONE;
    vector<double> vel;
    double minVel;
    long val;

    vector<short> GroupJoints;
    GroupJoints = GetGroupJointNum(group);
    rtn = SCACtrller.CM_SynMultiAxisMotion(GroupJoints, pos, time);
    if (0 != rtn)
    {
        return rtn;
    }
    if (ifBlock)
    {
        usleep(200000);
        do
        {
            //rtn = SCACtrller.CM_GetStatus(GroupJoints.at(0), val);
            CM_GetGroupVel(group, vel);
            minVel = vel.at(0);
            for (i = 0; i < vel.size(); i++)
            {
                if (vel.at(i) < minVel)
                {
                    minVel = vel.at(i);
                }
            }
            usleep(100);
        } while (minVel > 5.0);
        //}while(val == AXIS_RUNNING);
    }
    return rtn;
}

short CM_XR1_Interface::CM_GetAllPVC(vector<double> &pos, vector<double> &vel, vector<double> &cur)
{
    int i;
    short rtn = ERR_NONE;
    short tempRtn = ERR_NONE;
    vector<double> pValue, vVel, cVel;

    pos.resize(XR1JointNum);
    vel.resize(XR1JointNum);
    cur.resize(XR1JointNum);
    pValue.resize(XR1JointNum);
    vVel.resize(XR1JointNum);
    cVel.resize(XR1JointNum);

    for (i = 0; i < XR1JointNum; i++)
    {
        tempRtn = SCACtrller.CM_GetProfilePVC(i + 1, pValue.at(i), vVel.at(i), cVel.at(i));
        if (0 != tempRtn)
        {
            rtn = tempRtn;
        }
        pos.at(i) = SCAPos2XR1Pos(pValue.at(i), g_ReductionRatio[i]);
        vel.at(i) = SCAVel2XR1Vel(vVel.at(i), g_ReductionRatio[i]);
        cur.at(i) = cVel.at(i);
    }
    return rtn;
}

short CM_XR1_Interface::CM_GetGroupPVC(CtrlGroup group, vector<double> &pos, vector<double> &vel, vector<double> &cur)
{
    int i;
    short rtn = ERR_NONE;
    short tempRtn = ERR_NONE;
    vector<short> GroupJoints;
    vector<double> pValue, vVel, cVel;

    GroupJoints = GetGroupJointNum(group);

    pos.resize(GroupJoints.size());
    vel.resize(GroupJoints.size());
    cur.resize(GroupJoints.size());

    pValue.resize(GroupJoints.size());
    vVel.resize(GroupJoints.size());
    cVel.resize(GroupJoints.size());

    for (i = 0; i < GroupJoints.size(); i++)
    {
        tempRtn = SCACtrller.CM_GetProfilePVC(GroupJoints.at(i), pValue.at(i), vVel.at(i), cVel.at(i));
        if (0 != tempRtn)
        {
            rtn = tempRtn;
        }

        pos.at(i) = SCAPos2XR1Pos(pValue.at(i), g_ReductionRatio[GroupJoints.at(i) - 1]);
        vel.at(i) = SCAVel2XR1Vel(vVel.at(i), g_ReductionRatio[GroupJoints.at(i) - 1]);
        cur.at(i) = cVel.at(i);
    }
    return rtn;
}

short CM_XR1_Interface::CM_GetJointPVC(short joint, double &pos, double &vel, double &cur)
{
    short rtn = ERR_NONE;
    double dPos = 0.0, dVel = 0.0, dCur = 0.0;

    if (JointIsInvalid(joint))
    {
        return ERR_INPUT_PARM;
    }
    rtn = SCACtrller.CM_GetProfilePVC(joint, dPos, dVel, dCur);
    if (0 != rtn)
    {
        return rtn;
    }
    pos = SCAPos2XR1Pos(dPos, g_ReductionRatio[joint - 1]);
    vel = SCAVel2XR1Vel(dVel, g_ReductionRatio[joint - 1]);
    cur = dCur;

    return rtn;
}

CM_XR1_Interface::CM_XR1_Interface()
{
    int i;
    for (i = OmniWheel; i < MainBody; i++)
    {
        g_OmniWheelCtrlGroup.push_back(i);
    }
    for (i = MainBody; i < Head; i++)
    {
        g_MainBodyCtrlGroup.push_back(i);
    }
    for (i = Head; i < LeftArm; i++)
    {
        g_HeadCtrlGroup.push_back(i);
    }
    for (i = LeftArm; i < RightArm; i++)
    {
        g_LeftArmCtrlGroup.push_back(i);
    }
    for (i = RightArm; i < LeftHand; i++)
    {
        g_RightArmCtrlGroup.push_back(i);
    }
    for (i = MainBody; i < Head; i++)
    {
        g_LeftTrunkArmCtrlGroup.push_back(i);
    }
    for (i = LeftArm; i < RightArm; i++)
    {
        g_LeftTrunkArmCtrlGroup.push_back(i);
    }
    for (i = MainBody; i < Head; i++)
    {
        g_RightTrunkArmCtrlGroup.push_back(i);
    }
    for (i = RightArm; i < LeftHand; i++)
    {
        g_RightTrunkArmCtrlGroup.push_back(i);
    }
    for (i = LeftHand; i < RightHand; i++)
    {
        g_LeftHandCtrlGroup.push_back(i);
    }
    for (i = RightHand; i <= XR1JointNum; i++)
    {
        g_RightHandCtrlGroup.push_back(i);
    }
}

CM_XR1_Interface::~CM_XR1_Interface()
{
}

double CM_XR1_Interface::XR1Pos2SCAPos(double rad, double ratio)
{
    return ratio * rad / (2 * Pi);
}

double CM_XR1_Interface::SCAPos2XR1Pos(double circle, double ratio)
{
    return 2 * Pi * circle / ratio;
}

double CM_XR1_Interface::XR1Vel2SCAVel(double rad_s, double ratio)
{
    return ratio * rad_s * 60 / (2 * Pi);
}

double CM_XR1_Interface::SCAVel2XR1Vel(double rpm, double ratio)
{
    return 2 * Pi * rpm / (ratio * 60);
}

vector<short> CM_XR1_Interface::GetGroupJointNum(CtrlGroup group)
{
    vector<short> GroupJoints;
    switch (group)
    {
    case OmniWheelCtrlGroup:
        GroupJoints = g_OmniWheelCtrlGroup;
        break;
    case MainBodyCtrlGroup:
        GroupJoints = g_MainBodyCtrlGroup;
        break;
    case HeadCtrlGroup:
        GroupJoints = g_HeadCtrlGroup;
        break;
    case LeftArmCtrlGroup:
        GroupJoints = g_LeftArmCtrlGroup;
        break;
    case RightArmCtrlGroup:
        GroupJoints = g_RightArmCtrlGroup;
        break;
    case LeftTrunkArmCtrlGroup:
        GroupJoints = g_LeftTrunkArmCtrlGroup;
        break;
    case RightTrunkArmCtrlGroup:
        GroupJoints = g_RightTrunkArmCtrlGroup;
        break;
    case LeftHandCtrlGroup:
        GroupJoints = g_LeftHandCtrlGroup;
        break;
    case RightHandCtrlGroup:
        GroupJoints = g_RightHandCtrlGroup;
        break;
    default:
        break;
    }
    return GroupJoints;
}

bool CM_XR1_Interface::JointIsInvalid(short joint)
{
    return (joint < XR1MinJointID || joint > XR1JointNum);
}
