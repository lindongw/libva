/*
 * Copyright (c) 2009 Intel Corporation. All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
 * IN NO EVENT SHALL PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef VA_TRACE_H
#define VA_TRACE_H

#ifdef __cplusplus
extern "C" {
#endif

extern int va_trace_flag;

#define VA_TRACE_FLAG_LOG             0x1
#define VA_TRACE_FLAG_BUFDATA         0x2
#define VA_TRACE_FLAG_CODEDBUF        0x4
#define VA_TRACE_FLAG_SURFACE_DECODE  0x8
#define VA_TRACE_FLAG_SURFACE_ENCODE  0x10
#define VA_TRACE_FLAG_SURFACE_JPEG    0x20
#define VA_TRACE_FLAG_SURFACE         (VA_TRACE_FLAG_SURFACE_DECODE | \
                                       VA_TRACE_FLAG_SURFACE_ENCODE | \
                                       VA_TRACE_FLAG_SURFACE_JPEG)
#define VA_TRACE_FLAG_FTRACE          0x40


#define VA_TRACE_LOG(trace_func,...)            \
    if (va_trace_flag & VA_TRACE_FLAG_LOG) {    \
        trace_func(__VA_ARGS__);                \
    }
#define VA_TRACE_ALL(trace_func,...)            \
    if (va_trace_flag) {                        \
        trace_func(__VA_ARGS__);                \
    }
#define VA_TRACE_RET(dpy,ret)                   \
    if (va_trace_flag){                         \
        va_TraceStatus(dpy, __func__, ret);     \
    }

enum {
    INVALIDE_ID = 0,
    CREATE_CONFIG = 1,
    DESTROY_CONFIG,
    CREATE_CONTEXT,
    DESTROY_CONTEXT,
    CREATE_BUFFER,
    DESTROY_BUFFER,
    CREATE_SURFACE,
    DESTROY_SURFACE,
    BEGIN_PICTURE,
    RENDER_PICTURE,
    END_PICTURE,
    BUFFER_DATA,
    SYNC_SURFACE,
    SYNC_SURFACE2,
    QUERY_SURFACE_ATTR,
    CREATE_BUFFER2,
    MAP_BUFFER,
    UNMAP_BUFFER,
};

#define TRACE_INFO  0
#define TRACE_BEGIN 1
#define TRACE_END   2
#define TRACE_DATA  3

struct event_data {
    void *buf;
    unsigned int size;
};

#define VA_TRACE(dpy,id,op)                     \
    if (va_trace_flag & VA_TRACE_FLAG_FTRACE) {  \
        va_TraceEvent(dpy, id, op, NULL, 0);   \
    }
#define VA_TRACE_V1(dpy,id,op,v1)               \
    if (va_trace_flag & VA_TRACE_FLAG_FTRACE) {  \
        struct event_data desc[1] = {{&v1, sizeof(v1)}};                  \
        va_TraceEvent(dpy, id, op, desc, 1);   \
    }
#define VA_TRACE_P1V1(dpy,id,op,p1,v1)               \
    if (va_trace_flag & VA_TRACE_FLAG_FTRACE) {  \
        struct event_data desc[2] = {{p1, sizeof(*p1)}, {&v1, sizeof(v1)}};\
        va_TraceEvent(dpy, id, op, desc, 2);   \
    }
#define VA_TRACE_V2(dpy,id,op,v1,v2)               \
    if (va_trace_flag & VA_TRACE_FLAG_FTRACE) {  \
        struct event_data desc[2] = {{&v1, sizeof(v1)}, {&v2, sizeof(v2)}}; \
        va_TraceEvent(dpy, id, op, desc, 2);   \
    }
#define VA_TRACE_V3(dpy,id,op,v1,v2,v3)               \
    if (va_trace_flag & VA_TRACE_FLAG_FTRACE) {  \
        struct event_data desc[3] = {{&v1, sizeof(v1)}, {&v2, sizeof(v2)}, {&v3, sizeof(v3)}}; \
        va_TraceEvent(dpy, id, op, desc, 3);   \
    }
#define VA_TRACE_V4(dpy,id,op,v1,v2,v3,v4)               \
    if (va_trace_flag & VA_TRACE_FLAG_FTRACE) {  \
        struct event_data desc[4] = {{&v1, sizeof(v1)}, {&v2, sizeof(v2)}, {&v3, sizeof(v3)}, {&v4, sizeof(v4)}}; \
        va_TraceEvent(dpy, id, op, desc, 4);   \
    }
#define VA_TRACE_V4P2(dpy,id,op,v1,v2,v3,v4,p1,p2)               \
    if (va_trace_flag & VA_TRACE_FLAG_FTRACE) {  \
        struct event_data desc[6] = {{&v1, sizeof(v1)}, {&v2, sizeof(v2)}, {&v3, sizeof(v3)}, {&v4, sizeof(v4)}, {p1, sizeof(*p1)}, {p2, sizeof(*p2)}}; \
        va_TraceEvent(dpy, id, op, desc, 6);   \
    }
#define VA_TRACE_PD1(dpy,id,op,pn,pb)               \
    if (va_trace_flag & VA_TRACE_FLAG_FTRACE) {  \
        int data = sizeof(*pb) << 16;\
        struct event_data desc[2] = {{&data, sizeof(data)}, {pb, 0}}; \
        if (pn) { \
            data |= *pn; \
            desc[1].size = *pn * sizeof(*pb);\
        }\
        va_TraceEvent(dpy, id, op, desc, 2);   \
    }
#define VA_TRACE_V1VD1(dpy,id,op,v1,vn,pb)               \
    if (va_trace_flag & VA_TRACE_FLAG_FTRACE) {  \
        int data[2] = {v1, vn | (sizeof(*pb) << 16)};\
        struct event_data desc[2] = {{&data, sizeof(data)}, {pb, vn*sizeof(*pb)}}; \
        va_TraceEvent(dpy, id, op, desc, 2);   \
    }
#define VA_TRACE_V2PD1(dpy,id,op,v1,v2,pn,pb)               \
    if (va_trace_flag & VA_TRACE_FLAG_FTRACE) {  \
        int data[3] = {v1, v2, sizeof(*pb) << 16};\
        struct event_data desc[2] = {{&data, sizeof(data)}, {pb, 0}}; \
        if (pn) { \
            data[2] |= *pn; \
            desc[1].size = *pn * sizeof(*pb);\
        }\
        va_TraceEvent(dpy, id, op, desc, 2);   \
    }
#define VA_TRACE_V2VD1(dpy,id,op,v1,v2,vn,p)               \
    if (va_trace_flag & VA_TRACE_FLAG_FTRACE) {  \
        int data[3] = {v1, v2, vn | (sizeof(*p) << 16)};\
        struct event_data desc[2] = {{&data, sizeof(data)}, {p, vn*sizeof(*p)}}; \
        va_TraceEvent(dpy, id, op, desc, 2);   \
    }
#define VA_TRACE_V3VD1(dpy,id,op,v1,v2,v3,vn,p)               \
    if (va_trace_flag & VA_TRACE_FLAG_FTRACE) {  \
        int data[4] = {v1, v2, v3, vn | (sizeof(*p) << 16)};\
        struct event_data desc[2] = {{&data, sizeof(data)}, {p, vn*sizeof(*p)}}; \
        va_TraceEvent(dpy, id, op, desc, 2);   \
    }
#define VA_TRACE_V4VD1(dpy,id,op,v1,v2,v3,v4,vn,p)               \
    if (va_trace_flag & VA_TRACE_FLAG_FTRACE) {  \
        int data[5] = {v1, v2, v3, v4, vn | (sizeof(*p) << 16)};\
        struct event_data desc[2] = {{&data, sizeof(data)}, {p, vn*sizeof(*p)}}; \
        va_TraceEvent(dpy, id, op, desc, 2);   \
    }
#define VA_TRACE_BUFFERS(dpy,ctx,num,buffers)               \
    if (va_trace_flag & (VA_TRACE_FLAG_FTRACE | VA_TRACE_FLAG_BUFDATA) == (VA_TRACE_FLAG_FTRACE | VA_TRACE_FLAG_BUFDATA)) {  \
        va_TraceEventBuffers(dpy, ctx, num, buffers);\
    }

DLL_HIDDEN
void va_TraceInit(VADisplay dpy);
DLL_HIDDEN
void va_TraceEnd(VADisplay dpy);

DLL_HIDDEN
void va_TraceInitialize(
    VADisplay dpy,
    int *major_version,  /* out */
    int *minor_version   /* out */
);

DLL_HIDDEN
void va_TraceTerminate(
    VADisplay dpy
);

DLL_HIDDEN
void va_TraceCreateConfig(
    VADisplay dpy,
    VAProfile profile,
    VAEntrypoint entrypoint,
    VAConfigAttrib *attrib_list,
    int num_attribs,
    VAConfigID *config_id /* out */
);

DLL_HIDDEN
void va_TraceDestroyConfig(
    VADisplay dpy,
    VAConfigID config_id
);

DLL_HIDDEN
void va_TraceCreateSurfaces(
    VADisplay dpy,
    int width,
    int height,
    int format,
    int num_surfaces,
    VASurfaceID *surfaces,  /* out */
    VASurfaceAttrib    *attrib_list,
    unsigned int        num_attribs
);

DLL_HIDDEN
void va_TraceDestroySurfaces(
    VADisplay dpy,
    VASurfaceID *surface_list,
    int num_surfaces
);

DLL_HIDDEN
void va_TraceCreateContext(
    VADisplay dpy,
    VAConfigID config_id,
    int picture_width,
    int picture_height,
    int flag,
    VASurfaceID *render_targets,
    int num_render_targets,
    VAContextID *context        /* out */
);

DLL_HIDDEN
void va_TraceDestroyContext(
    VADisplay dpy,
    VAContextID context
);

DLL_HIDDEN
void va_TraceCreateMFContext(
    VADisplay dpy,
    VAContextID *mf_context /* out */
);

DLL_HIDDEN
void va_TraceMFAddContext(
    VADisplay dpy,
    VAMFContextID mf_context,
    VAContextID context
);

DLL_HIDDEN
void va_TraceMFReleaseContext(
    VADisplay dpy,
    VAMFContextID mf_context,
    VAContextID context
);

DLL_HIDDEN
void va_TraceMFSubmit(
    VADisplay dpy,
    VAMFContextID mf_context,
    VAContextID *contexts,
    int num_contexts
);

DLL_HIDDEN
void va_TraceCreateBuffer(
    VADisplay dpy,
    VAContextID context,    /* in */
    VABufferType type,      /* in */
    unsigned int size,      /* in */
    unsigned int num_elements,  /* in */
    void *data,         /* in */
    VABufferID *buf_id      /* out */
);

DLL_HIDDEN
void va_TraceDestroyBuffer(
    VADisplay dpy,
    VABufferID buf_id    /* in */
);

DLL_HIDDEN
void va_TraceMapBuffer(
    VADisplay dpy,
    VABufferID buf_id,  /* in */
    void **pbuf     /* out */
);


DLL_HIDDEN
void va_TraceBeginPicture(
    VADisplay dpy,
    VAContextID context,
    VASurfaceID render_target
);

DLL_HIDDEN
void va_TraceRenderPicture(
    VADisplay dpy,
    VAContextID context,
    VABufferID *buffers,
    int num_buffers
);

DLL_HIDDEN
void va_TraceEndPicture(
    VADisplay dpy,
    VAContextID context,
    int endpic_done
);

DLL_HIDDEN
void va_TraceEndPictureExt(
    VADisplay dpy,
    VAContextID context,
    int endpic_done
);

DLL_HIDDEN
void va_TraceSyncSurface(
    VADisplay dpy,
    VASurfaceID render_target
);

DLL_HIDDEN
void va_TraceSyncSurface2(
    VADisplay dpy,
    VASurfaceID surface,
    uint64_t timeout_ns
);

DLL_HIDDEN
void va_TraceQuerySurfaceAttributes(
    VADisplay           dpy,
    VAConfigID          config,
    VASurfaceAttrib    *attrib_list,
    unsigned int       *num_attribs
);

DLL_HIDDEN
void va_TraceQuerySurfaceStatus(
    VADisplay dpy,
    VASurfaceID render_target,
    VASurfaceStatus *status /* out */
);

DLL_HIDDEN
void va_TraceQuerySurfaceError(
    VADisplay dpy,
    VASurfaceID surface,
    VAStatus error_status,
    void **error_info /*out*/
);

DLL_HIDDEN
void va_TraceSyncBuffer(
    VADisplay dpy,
    VABufferID buf_id,
    uint64_t timeout_ns
);

DLL_HIDDEN
void va_TraceMaxNumDisplayAttributes(
    VADisplay dpy,
    int number
);

DLL_HIDDEN
void va_TraceQueryDisplayAttributes(
    VADisplay dpy,
    VADisplayAttribute *attr_list,  /* out */
    int *num_attributes         /* out */
);

DLL_HIDDEN
void va_TraceGetDisplayAttributes(
    VADisplay dpy,
    VADisplayAttribute *attr_list,
    int num_attributes
);

DLL_HIDDEN
void va_TraceSetDisplayAttributes(
    VADisplay dpy,
    VADisplayAttribute *attr_list,
    int num_attributes
);

/* extern function called by display side */
void va_TracePutSurface(
    VADisplay dpy,
    VASurfaceID surface,
    void *draw, /* the target Drawable */
    short srcx,
    short srcy,
    unsigned short srcw,
    unsigned short srch,
    short destx,
    short desty,
    unsigned short destw,
    unsigned short desth,
    VARectangle *cliprects, /* client supplied clip list */
    unsigned int number_cliprects, /* number of clip rects in the clip list */
    unsigned int flags /* de-interlacing flags */
);

void va_TraceStatus(VADisplay dpy, const char * funcName, VAStatus status);

void va_TraceEvent(
    VADisplay dpy,
    unsigned short id,
    unsigned short opcode,
    struct event_data *desc,
    unsigned int num);

void va_TraceEventBuffers(
    VADisplay dpy,
    VAContextID context,
    int num_buffers,
    VABufferID *buffers);

#ifdef __cplusplus
}
#endif


#endif /* VA_TRACE_H */
