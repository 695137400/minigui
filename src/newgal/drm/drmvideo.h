///////////////////////////////////////////////////////////////////////////////
//
//                          IMPORTANT NOTICE
//
// The following open source license statement does not apply to any
// entity in the Exception List published by FMSoft.
//
// For more information, please visit:
//
// https://www.fmsoft.cn/exception-list
//
//////////////////////////////////////////////////////////////////////////////
/*
 *   This file is part of MiniGUI, a mature cross-platform windowing
 *   and Graphics User Interface (GUI) support system for embedded systems
 *   and smart IoT devices.
 *
 *   Copyright (C) 2019, Beijing FMSoft Technologies Co., Ltd.
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *   Or,
 *
 *   As this program is a library, any link to this program must follow
 *   GNU General Public License version 3 (GPLv3). If you cannot accept
 *   GPLv3, you need to be licensed from FMSoft.
 *
 *   If you have got a commercial license of this program, please use it
 *   under the terms and conditions of the commercial license.
 *
 *   For more information about the commercial license, please refer to
 *   <http://www.minigui.com/blog/minigui-licensing-policy/>.
 */

#ifndef _NEWGAL_DRIVIDEO_H
#define _NEWGAL_DRIVIDEO_H

#include <stdint.h>

#include "sysvideo.h"

/* Hidden "this" pointer for the video functions */
#define _THIS   GAL_VideoDevice *this

/* Private display data */

typedef struct drm_mode_info DrmModeInfo;

typedef struct GAL_PrivateVideoData {
    /* For compositing schema, we force to use double buffering */
#ifdef _MGSCHEMA_COMPOSITING
    /* start of header for shadow screen */
    int magic, version;
    GAL_Surface *real_screen, *shadow_screen;
    RECT dirty_rc;

    /* Used to simulate the hardware cursor. */
    GAL_Surface *cursor;
    int csr_x, csr_y;
    int hot_x, hot_y;
    /* end of header for shadow screen */
#else   /* defined _MGSCHEMA_COMPOSITING */
    /* When double buffering supported, the real surface represents the ultimate
     * scan-out frame buffer, and the shadow screen represents the rendering
     * surface. When double buffering disabled, both are NULL. */
    GAL_Surface *real_screen, *shadow_screen;

    /* the global name of the surface buffer */
    uint32_t    buff_name;
#endif  /* not defined _MGSCHEMA_COMPOSITING */

    char            dev_name[LEN_DEVICE_NAME + 1];
    int             dev_fd;

    /* capabilities */
    uint32_t        cap_cursor_width:10;
    uint32_t        cap_cursor_height:10;
    uint32_t        cap_dumb:1;

    void*           exdrv_handle;
    DrmDriverOps*   driver_ops;
    DrmDriver*      driver;

    DrmModeInfo*    mode_list;
    GAL_Rect**      modes;

    int             bpp;
    uint32_t        width;
    uint32_t        height;
    uint32_t        pitch;
    uint32_t        size;

    uint32_t        scanout_buff_id;
    uint8_t*        scanout_fb;

    DrmModeInfo*    saved_info;
    drmModeCrtc*    saved_crtc;

    /* only valid when using DUMB frame buffer */
    uint32_t        handle;

    /* only valid when using DRM driver */
    uint32_t        console_buff_id;

} DrmVideoData;

#endif /* _NEWGAL_DRIVIDEO_H */

