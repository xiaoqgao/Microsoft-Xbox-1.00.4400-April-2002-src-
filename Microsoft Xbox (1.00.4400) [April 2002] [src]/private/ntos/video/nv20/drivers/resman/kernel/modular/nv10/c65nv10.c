 /***************************************************************************\
|*                                                                           *|
|*        Copyright (c) 1993-2000 NVIDIA, Corp.  All rights reserved.        *|
|*                                                                           *|
|*     NOTICE TO USER:   The source code  is copyrighted under  U.S. and     *|
|*     international laws.   NVIDIA, Corp. of Sunnyvale, California owns     *|
|*     the copyright  and as design patents  pending  on the design  and     *|
|*     interface  of the NV chips.   Users and possessors of this source     *|
|*     code are hereby granted  a nonexclusive,  royalty-free  copyright     *|
|*     and  design  patent license  to use this code  in individual  and     *|
|*     commercial software.                                                  *|
|*                                                                           *|
|*     Any use of this source code must include,  in the user documenta-     *|
|*     tion and  internal comments to the code,  notices to the end user     *|
|*     as follows:                                                           *|
|*                                                                           *|
|*     Copyright (c) 1993-2000  NVIDIA, Corp.    NVIDIA  design  patents     *|
|*     pending in the U.S. and foreign countries.                            *|
|*                                                                           *|
|*     NVIDIA, CORP.  MAKES  NO REPRESENTATION ABOUT  THE SUITABILITY OF     *|
|*     THIS SOURCE CODE FOR ANY PURPOSE.  IT IS PROVIDED "AS IS" WITHOUT     *|
|*     EXPRESS OR IMPLIED WARRANTY OF ANY KIND.  NVIDIA, CORP. DISCLAIMS     *|
|*     ALL WARRANTIES  WITH REGARD  TO THIS SOURCE CODE,  INCLUDING  ALL     *|
|*     IMPLIED   WARRANTIES  OF  MERCHANTABILITY  AND   FITNESS   FOR  A     *|
|*     PARTICULAR  PURPOSE.   IN NO EVENT SHALL NVIDIA, CORP.  BE LIABLE     *|
|*     FOR ANY SPECIAL, INDIRECT, INCIDENTAL,  OR CONSEQUENTIAL DAMAGES,     *|
|*     OR ANY DAMAGES  WHATSOEVER  RESULTING  FROM LOSS OF USE,  DATA OR     *|
|*     PROFITS,  WHETHER IN AN ACTION  OF CONTRACT,  NEGLIGENCE OR OTHER     *|
|*     TORTIOUS ACTION, ARISING OUT  OF OR IN CONNECTION WITH THE USE OR     *|
|*     PERFORMANCE OF THIS SOURCE CODE.                                      *|
|*                                                                           *|
 \***************************************************************************/

/******************************* Video Manager *****************************\
*                                                                           *
* Module: VIDCLRKY.C                                                        *
*   This module implements the NV_VIDEO_COLOR_KEY object class and its      *
*   corresponding methods.                                                  *
*                                                                           *
*****************************************************************************
*                                                                           *
* History:                                                                  *
*                                                                           *
\***************************************************************************/

#include <nv_ref.h>
#include <nv10_ref.h>
#include <nvrm.h>
#include <nv10_hal.h>
#include "nvhw.h"
#include "nvhalcpp.h"

//
// The following routines are used by the HAL video engine
// manager in kernel/video/vidnv10.c.
//
RM_STATUS class65Method_NV10(PVIDEOMETHODARG_000);

//---------------------------------------------------------------------------
//
//  Create/Destroy object routines.
//
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//
//  Miscellaneous class support routines.
//
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//
//  Class method routines.
//
//---------------------------------------------------------------------------

//
// class65Method
//
// This routine performs any chip-specific handling for all class64
// methods.
//
RM_STATUS class65Method_NV10(PVIDEOMETHODARG_000 pVideoMethodArg)
{
    PVIDEOCOLORKEYHALOBJECT pVidColorKeyHalObj;
    PHALHWINFO pHalHwInfo;
    U032 offset, data;

    pVidColorKeyHalObj = (PVIDEOCOLORKEYHALOBJECT)pVideoMethodArg->pHalObjInfo;
    offset = pVideoMethodArg->offset;
    data = pVideoMethodArg->data;
    pHalHwInfo = pVideoMethodArg->pHalHwInfo;

    switch (offset)
    {
        case NVFF6_SET_COLOR_FORMAT(0):
            pVidColorKeyHalObj->ColorFormat = data;
            pHalHwInfo->pVideoHalInfo->VideoColorFormat = data;
            break;
        case NVFF6_SET_COLOR_KEY(0):
            pVidColorKeyHalObj->Color = data;
            pHalHwInfo->pVideoHalInfo->VideoColor = data;
            if (data)
            {
                switch (pVidColorKeyHalObj->ColorFormat)
                {
                    case NVFF6_SET_COLOR_FORMAT_LE_X16A8Y8:
                    case NVFF6_SET_COLOR_FORMAT_LE_X24Y8:
                        REG_WR32(NV_PVIDEO_COLOR_KEY, data & 0xFF);
                        break;
                    case NVFF6_SET_COLOR_FORMAT_LE_X16A1R5G5B5:
                    case NVFF6_SET_COLOR_FORMAT_LE_X17R5G5B5:
                        REG_WR32(NV_PVIDEO_COLOR_KEY, data & 0x7FFF);
                        break;
                    case NVFF6_SET_COLOR_FORMAT_LE_A16R5G6B5:
                    case NVFF6_SET_COLOR_FORMAT_LE_A16Y16:
                    case NVFF6_SET_COLOR_FORMAT_LE_X16Y16:
                        REG_WR32(NV_PVIDEO_COLOR_KEY, data & 0xFFFF);
                        break;
                    case NVFF6_SET_COLOR_FORMAT_LE_A8R8G8B8:
                    case NVFF6_SET_COLOR_FORMAT_LE_X8R8G8B8:                
                        REG_WR32(NV_PVIDEO_COLOR_KEY, data & 0xFFFFFF);
                        break;
                    default:
                        REG_WR32(NV_PVIDEO_COLOR_KEY, data);
                        break;
                }
            }
            break;
        case NVFF6_SET_POINT(0):
            pVidColorKeyHalObj->xClipMin = data & 0x0000FFFF;
            pVidColorKeyHalObj->yClipMin = data >> 16;
            pHalHwInfo->pVideoHalInfo->VideoStart =
                DRF_NUM(_PVIDEO, _POINT_OUT, _X, pVidColorKeyHalObj->xClipMin) |
                DRF_NUM(_PVIDEO, _POINT_OUT, _Y, pVidColorKeyHalObj->yClipMin);
            break;
        case NVFF6_SET_SIZE(0):
            pVidColorKeyHalObj->xClipMax = data & 0x0000FFFF;
            pVidColorKeyHalObj->yClipMax = data >> 16;
            pHalHwInfo->pVideoHalInfo->VideoSize =
                DRF_NUM(_PVIDEO, _POINT_OUT, _X, pVidColorKeyHalObj->xClipMax) |
                DRF_NUM(_PVIDEO, _POINT_OUT, _Y, pVidColorKeyHalObj->yClipMax);
            break;
        default:
            // HAL doesn't have anything to do for this particular method
            ;
    }

    return NVFF6_NOTIFICATION_STATUS_DONE_SUCCESS;
}
