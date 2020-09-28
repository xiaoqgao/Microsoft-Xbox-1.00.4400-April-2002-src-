///////////////////////////////////////////////////////////////////////////
//
//  Copyright (C) 1999 - 2001 Microsoft Corporation.  All Rights Reserved.
//
//  File:       d3dx8core.h
//  Content:    D3DX core types and functions
//
///////////////////////////////////////////////////////////////////////////

#include "d3dx8.h"

#ifndef __D3DX8CORE_H__
#define __D3DX8CORE_H__

#undef INTERFACE
#define INTERFACE VOID

///////////////////////////////////////////////////////////////////////////
// ID3DXBuffer:
// ------------
// The buffer object is used to return arbitrary lenght data.
///////////////////////////////////////////////////////////////////////////

typedef interface ID3DXBuffer ID3DXBuffer;
typedef interface ID3DXBuffer *LPD3DXBUFFER;

// {932E6A7E-C68E-45dd-A7BF-53D19C86DB1F}
DEFINE_GUID(IID_ID3DXBuffer,
0x932e6a7e, 0xc68e, 0x45dd, 0xa7, 0xbf, 0x53, 0xd1, 0x9c, 0x86, 0xdb, 0x1f);

DECLARE_INTERFACE_(ID3DXBuffer, IUnknown)
{
    // IUnknown
    STDMETHOD(QueryInterface)(THIS_ REFIID iid, LPVOID *ppv) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // ID3DXBuffer
    STDMETHOD_(LPVOID, GetBufferPointer)(THIS) PURE;
    STDMETHOD_(DWORD, GetBufferSize)(THIS) PURE;
};






///////////////////////////////////////////////////////////////////////////
// ID3DXSprite:
// ------------
// This object intends to provide an easy way to drawing sprites using D3D.
//
// Begin -
//    Prepares device for drawing sprites
//
// Draw, DrawAffine, DrawTransform
//    Draws a sprite in screen-space.  Before transformation, the sprite is
//    the size of SrcRect, with its top-left corner at the origin (0,0).
//    The color and alpha channels are modulated by Color.
//
// End -
//     Restores device state to how it was when Begin was called.
///////////////////////////////////////////////////////////////////////////

typedef interface ID3DXSprite ID3DXSprite;
typedef interface ID3DXSprite *LPD3DXSPRITE;


// {E8691849-87B8-4929-9050-1B0542D5538C}
DEFINE_GUID( IID_ID3DXSprite,
0xe8691849, 0x87b8, 0x4929, 0x90, 0x50, 0x1b, 0x5, 0x42, 0xd5, 0x53, 0x8c);


DECLARE_INTERFACE_(ID3DXSprite, IUnknown)
{
    // IUnknown
    STDMETHOD(QueryInterface)(THIS_ REFIID iid, LPVOID *ppv) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // ID3DXSprite
    STDMETHOD(GetDevice)(THIS_ LPDIRECT3DDEVICE8* ppDevice) PURE;

    STDMETHOD(Begin)(THIS) PURE;

    STDMETHOD(Draw)(THIS_ LPDIRECT3DTEXTURE8  pSrcTexture,
        CONST RECT* pSrcRect, CONST D3DXVECTOR2* pScaling,
        CONST D3DXVECTOR2* pRotationCenter, FLOAT Rotation,
        CONST D3DXVECTOR2* pTranslation, D3DCOLOR Color) PURE;

    STDMETHOD(DrawTransform)(THIS_ LPDIRECT3DTEXTURE8 pSrcTexture,
        CONST RECT* pSrcRect, CONST D3DXMATRIX* pTransform,
        D3DCOLOR Color) PURE;

    STDMETHOD(End)(THIS) PURE;
};


#ifdef __cplusplus
extern "C" {
#endif //__cplusplus


HRESULT WINAPI
    D3DXCreateSprite(
        LPDIRECT3DDEVICE8   pDevice,
        LPD3DXSPRITE*       ppSprite);

#ifdef __cplusplus
}
#endif //__cplusplus





///////////////////////////////////////////////////////////////////////////
// ID3DXRenderToSurface:
// ---------------------
// This object abstracts rendering to surfaces.  These surfaces do not
// necessarily need to be render targets.  If they are not, a compatible
// render target is used, and the result copied into surface at end scene.
///////////////////////////////////////////////////////////////////////////

typedef struct _D3DXRTS_DESC
{
    UINT                Width;
    UINT                Height;
    D3DFORMAT           Format;
    BOOL                DepthStencil;
    D3DFORMAT           DepthStencilFormat;

} D3DXRTS_DESC;


typedef interface ID3DXRenderToSurface ID3DXRenderToSurface;
typedef interface ID3DXRenderToSurface *LPD3DXRENDERTOSURFACE;


// {69CC587C-E40C-458d-B5D3-B029E18EB60A}
DEFINE_GUID( IID_ID3DXRenderToSurface,
0x69cc587c, 0xe40c, 0x458d, 0xb5, 0xd3, 0xb0, 0x29, 0xe1, 0x8e, 0xb6, 0xa);


DECLARE_INTERFACE_(ID3DXRenderToSurface, IUnknown)
{
    // IUnknown
    STDMETHOD(QueryInterface)(THIS_ REFIID iid, LPVOID *ppv) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // ID3DXRenderToSurface
    STDMETHOD(GetDevice)(THIS_ LPDIRECT3DDEVICE8* ppDevice) PURE;
    STDMETHOD(GetDesc)(THIS_ D3DXRTS_DESC* pDesc) PURE;

    STDMETHOD(BeginScene)(THIS_ LPDIRECT3DSURFACE8 pSurface, CONST D3DVIEWPORT8* pViewport) PURE;
    STDMETHOD(EndScene)(THIS) PURE;
};


#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

HRESULT WINAPI
    D3DXCreateRenderToSurface(
        LPDIRECT3DDEVICE8       pDevice,
        UINT                    Width,
        UINT                    Height,
        D3DFORMAT               Format,
        BOOL                    DepthStencil,
        D3DFORMAT               DepthStencilFormat,
        LPD3DXRENDERTOSURFACE*  ppRenderToSurface);

#ifdef __cplusplus
}
#endif //__cplusplus



///////////////////////////////////////////////////////////////////////////
// ID3DXRenderToEnvMap:
// --------------------
///////////////////////////////////////////////////////////////////////////

typedef struct _D3DXRTE_DESC
{
    UINT        Size;
    D3DFORMAT   Format;
    BOOL        DepthStencil;
    D3DFORMAT   DepthStencilFormat;
} D3DXRTE_DESC;


typedef interface ID3DXRenderToEnvMap ID3DXRenderToEnvMap;
typedef interface ID3DXRenderToEnvMap *LPD3DXRenderToEnvMap;

// {9F6779E5-60A9-4d8b-AEE4-32770F405DBA}
DEFINE_GUID( IID_ID3DXRenderToEnvMap,
0x9f6779e5, 0x60a9, 0x4d8b, 0xae, 0xe4, 0x32, 0x77, 0xf, 0x40, 0x5d, 0xba);


DECLARE_INTERFACE_(ID3DXRenderToEnvMap, IUnknown)
{
    // IUnknown
    STDMETHOD(QueryInterface)(THIS_ REFIID iid, LPVOID *ppv) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // ID3DXRenderToEnvMap
    STDMETHOD(GetDevice)(THIS_ LPDIRECT3DDEVICE8* ppDevice) PURE;
    STDMETHOD(GetDesc)(THIS_ D3DXRTE_DESC* pDesc) PURE;

    STDMETHOD(BeginCube)(THIS_
        LPDIRECT3DCUBETEXTURE8 pCubeTex) PURE;

    STDMETHOD(BeginSphere)(THIS_
        LPDIRECT3DTEXTURE8 pTex) PURE;

    STDMETHOD(BeginHemisphere)(THIS_
        LPDIRECT3DTEXTURE8 pTexZPos,
        LPDIRECT3DTEXTURE8 pTexZNeg) PURE;

    STDMETHOD(BeginParabolic)(THIS_
        LPDIRECT3DTEXTURE8 pTexZPos,
        LPDIRECT3DTEXTURE8 pTexZNeg) PURE;

    STDMETHOD(Face)(THIS_ D3DCUBEMAP_FACES Face) PURE;
    STDMETHOD(End)(THIS) PURE;
};


#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

HRESULT WINAPI
    D3DXCreateRenderToEnvMap(
        LPDIRECT3DDEVICE8       pDevice,
        UINT                    Size,
        D3DFORMAT               Format,
        BOOL                    DepthStencil,
        D3DFORMAT               DepthStencilFormat,
        LPD3DXRenderToEnvMap*   ppRenderToEnvMap);

#ifdef __cplusplus
}
#endif //__cplusplus

///////////////////////////////////////////////////////////////////////////
// Misc APIs:
///////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus


//-------------------------------------------------------------------------
// D3DXGetFVFVertexSize:
// ---------------------
// Returns the size (in bytes) of a vertex for a given FVF.
//-------------------------------------------------------------------------

UINT WINAPI
    D3DXGetFVFVertexSize(DWORD FVF);


//-------------------------------------------------------------------------
// D3DXGetErrorString:
// ------------------
// Returns the error string for given an hresult.  Interprets all D3DX and
// D3D hresults.
//
// Parameters:
//  hr
//      The error code to be deciphered.
//  pBuffer
//      Pointer to the buffer to be filled in.
//  BufferLen
//      Count of characters in buffer.  Any error message longer than this
//      length will be truncated to fit.
//-------------------------------------------------------------------------
HRESULT WINAPI
    D3DXGetErrorStringA(
        HRESULT             hr,
        LPSTR               pBuffer,
        UINT                BufferLen);

HRESULT WINAPI
    D3DXGetErrorStringW(
        HRESULT             hr,
        LPWSTR              pBuffer,
        UINT                BufferLen);

#ifdef UNICODE
#define D3DXGetErrorString D3DXGetErrorStringW
#else
#define D3DXGetErrorString D3DXGetErrorStringA
#endif



#ifdef __cplusplus
}
#endif //__cplusplus


#endif //__D3DX8CORE_H__
