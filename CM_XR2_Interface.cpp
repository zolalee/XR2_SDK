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
* Filename:       	CM_XR2_Interface.cpp
* Programmer:       Li Zola
* Created:        	june 9th, 2020
* Description:		SCA controller interface based on SCA SDK
*
* Note:				June 9th, 2020, version: 1.0
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
#include "CM_XR2_Interface.h"

#define Pi 3.14159265359
/*---------------------------------------------------------------------------------------
------
------	Global variables
------
---------------------------------------------------------------------------------------*/


double g_ReductionRatio[] = {
6,6,180/19,
6,6,180/19,
6,6,180/19,
6,6,180/19};

extern CM_SCA_Controller SCACtrller;

/*---------------------------------------------------------------------------------------
------
------	Class
------
---------------------------------------------------------------------------------------*/
short CM_XR2_Interface::CM_ConnectXR2()
{
    return SCACtrller.CM_InitController();
}


short CM_XR2_Interface::CM_ResetJoint(short joint)
{
    vector<short> axis;
    axis.push_back(joint);
    return SCACtrller.CM_ResetAxis(axis);
}

short CM_XR2_Interface::CM_CloseAllJoints()
{
    return SCACtrller.CM_CloseAll();
}

short CM_XR2_Interface::CM_SetXR2SoftLimitStatus(long status)
{
    int i;
    short rtn = ERR_NONE;
    short tempRtn = ERR_NONE;

    for (i = MainBody; i <= XR2JointNum; i++)
    {
        tempRtn = SCACtrller.CM_SetSoftLimitStatus(i, status);
        if (tempRtn != 0)
        {
            rtn = tempRtn;
        }
    }
    return rtn;
}

short CM_XR2_Interface::CM_ClearAllAlarm()
{
    int i;
    short rtn = ERR_NONE;
    short tempRtn = ERR_NONE;

    for (i = 1; i <= XR2JointNum; i++)
    {
        tempRtn = SCACtrller.CM_ClearAlarm(i);
        if (tempRtn != 0)
        {
            rtn = tempRtn;
        }
    }
    return rtn;
}


short CM_XR2_Interface::CM_SetJointCtrlMode(short joint, CtrlMode mode)
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



short CM_XR2_Interface::CM_GetJointCtrlMode(short joint, long &CtrlMode)
{
    if (JointIsInvalid(joint))
    {
        return ERR_INPUT_PARM;
    }
    return SCACtrller.CM_GetProfileMode(joint, CtrlMode);
}

// short CM_XR2_Interface::CM_SetAllPos(vector<double> value)
// {
//     int i;
//     short rtn = ERR_NONE;
//     short tempRtn = ERR_NONE;

//     vector<double> pos;

//     if (XR2JointNum != value.size())
//     {
//         return ERR_INPUT_PARM;
//     }
//     for (i = 0; i < XR2JointNum; i++)
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

short CM_XR2_Interface::CM_SetAllPos(vector<double> value)
{
    int i = 0, j = 0;
    short rtn = ERR_NONE;
    short tempRtn = ERR_NONE;
    double pos;
    vector<double> val1, val2, val3, val4, val5, val6, val7;

    if (XR2JointNum != value.size())
    {
        return ERR_INPUT_PARM;
    }

    for (i = 0; i < XR2JointNum; i++)
    {
        pos= (XR1Pos2SCAPos(value.at(i), g_ReductionRatio[i]));
        rtn = SCACtrller.CM_SetPosition(i+1, pos);
    }
  
    return rtn;
}

// short CM_XR2_Interface::CM_SetGroupPos(CtrlGroup group, vector<double> value)
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


short CM_XR2_Interface::CM_SetJointPos(short joint, double value)
{
    double pos;

    cout << "CM_XR2_Interface::CM_SetJointPos, joint = " << joint << ", value = " << value << endl;

    if (JointIsInvalid(joint))
    {
        cout << "CM_XR2_Interface::CM_SetJointPos - 1" << endl;
        return ERR_INPUT_PARM;
    }
    pos = XR1Pos2SCAPos(value, g_ReductionRatio[joint - 1]);
    return SCACtrller.CM_SetPosition(joint, pos);
}

short CM_XR2_Interface::CM_GetAllPos(vector<double> &value)
{
    int i;
    short rtn = ERR_NONE;
    short tempRtn = ERR_NONE;

    vector<double> pos;

    value.resize(XR2JointNum);
    pos.resize(XR2JointNum);
    for (i = 0; i < XR2JointNum; i++)
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

short CM_XR2_Interface::CM_GetJointPos(short joint, double &value)
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

// short CM_XR2_Interface::CM_SetAllVel(vector<double> value)
// {
//     int i;
//     short rtn = ERR_NONE;
//     short tempRtn = ERR_NONE;

//     vector<double> vel;

//     if (XR2JointNum != value.size())
//     {
//         return ERR_INPUT_PARM;
//     }
//     for (i = 0; i < XR2JointNum; i++)
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

short CM_XR2_Interface::CM_SetAllVel(vector<double> value)
{
    int i = 0, j = 0;
    short rtn = ERR_NONE;
    short tempRtn = ERR_NONE;
    double  vel;
    vector<double> val1, val2, val3, val4, val5, val6, val7;

    if (XR2JointNum != value.size())
    {
        return ERR_INPUT_PARM;
    }

    for (i = 0; i < XR2JointNum; i++)
    {
        vel= XR1Vel2SCAVel(value.at(i), g_ReductionRatio[i]);
        rtn = SCACtrller.CM_SetVelocity(i+1, vel);
    }

    // Note: 当前以组的方式发送数据

    return rtn;
}

// short CM_XR2_Interface::CM_SetGroupVel(CtrlGroup group, vector<double> value)
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


short CM_XR2_Interface::CM_SetJointVel(short joint, double value)
{
    double vel;

    if (JointIsInvalid(joint))
    {
        return ERR_INPUT_PARM;
    }
    vel = XR1Vel2SCAVel(value, g_ReductionRatio[joint - 1]);
    return SCACtrller.CM_SetVelocity(joint, vel);
}

short CM_XR2_Interface::CM_GetAllVel(vector<double> &value)
{
    int i;
    short rtn = ERR_NONE;
    short tempRtn = ERR_NONE;

    vector<double> vel;

    value.resize(XR2JointNum);
    vel.resize(XR2JointNum);
    for (i = 0; i < XR2JointNum; i++)
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

short CM_XR2_Interface::CM_GetJointVel(short joint, double &value)
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

short CM_XR2_Interface::CM_SetAllCur(vector<double> value)
{
    int i;
    short rtn = ERR_NONE;
    short tempRtn = ERR_NONE;

    if (XR2JointNum != value.size())
    {
        return ERR_INPUT_PARM;
    }
    for (i = 0; i < XR2JointNum; i++)
    {
        tempRtn = SCACtrller.CM_SetCurrent(i + 1, value.at(i));
        if (0 != tempRtn)
        {
            rtn = tempRtn;
        }
    }
    return rtn;
}


// short CM_XR2_Interface::CM_SetGroupCur(CtrlGroup group, vector<double> value)
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


short CM_XR2_Interface::CM_SetJointCur(short joint, double value)
{
    if (JointIsInvalid(joint))
    {
        return ERR_INPUT_PARM;
    }
    return SCACtrller.CM_SetCurrent(joint, value);
}

short CM_XR2_Interface::CM_GetAllCur(vector<double> &value)
{
    int i;
    short rtn = ERR_NONE;
    short tempRtn = ERR_NONE;

    value.resize(XR2JointNum);
    for (i = 0; i < XR2JointNum; i++)
    {
        tempRtn = SCACtrller.CM_GetCurrent(i + 1, value.at(i));
        if (0 != tempRtn)
        {
            rtn = tempRtn;
        }
    }
    return rtn;
}


short CM_XR2_Interface::CM_GetJointCur(short joint, double &value)
{
    if (JointIsInvalid(joint))
    {
        return ERR_INPUT_PARM;
    }
    return SCACtrller.CM_GetCurrent(joint, value);
}

short CM_XR2_Interface::CM_GetAllPVC(vector<double> &pos, vector<double> &vel, vector<double> &cur)
{
    int i;
    short rtn = ERR_NONE;
    short tempRtn = ERR_NONE;
    vector<double> pValue, vVel, cVel;

    pos.resize(XR2JointNum);
    vel.resize(XR2JointNum);
    cur.resize(XR2JointNum);
    pValue.resize(XR2JointNum);
    vVel.resize(XR2JointNum);
    cVel.resize(XR2JointNum);

    for (i = 0; i < XR2JointNum; i++)
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

short CM_XR2_Interface::CM_GetJointPVC(short joint, double &pos, double &vel, double &cur)
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


CM_XR2_Interface::~CM_XR2_Interface()
{
}

double CM_XR2_Interface::XR1Pos2SCAPos(double rad, double ratio)
{
    return ratio * rad / (2 * Pi);
}

double CM_XR2_Interface::SCAPos2XR1Pos(double circle, double ratio)
{
    return 2 * Pi * circle / ratio;
}

double CM_XR2_Interface::XR1Vel2SCAVel(double rad_s, double ratio)
{
    return ratio * rad_s * 60 / (2 * Pi);
}

double CM_XR2_Interface::SCAVel2XR1Vel(double rpm, double ratio)
{
    return 2 * Pi * rpm / (ratio * 60);
}



bool CM_XR2_Interface::JointIsInvalid(short joint)
{
    return (joint < XR2MinJointID || joint > XR2JointNum);
}
