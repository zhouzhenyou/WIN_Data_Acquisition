// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif


#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <atlimage.h>

#include <afxdisp.h>        // MFC Automation classes
#include <afxpriv.h>
#include <io.h>
#include <string.h>
#include <winnetwk.h>
#include <windows.h>
#include <stdio.h>   
#include <stdlib.h>
#include<direct.h>

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "MPR.lib")

#import   "C:\Program Files\Common Files\System\ado\msado27.tlb"    no_namespace   rename("EOF", "adoEOF")
#import   <msxml3.dll> named_guids
using namespace MSXML2;

#define    ID_IMAGE_VENDOR                  0x0001
#define    ID_IMAGE_SUBSCRIBER              0x0002

#define    ID_IMAGE                         "\\IMG"
#define    ID_SOURCE                        "\\SRC"
#define    ID_IMAGE_CONFIG                  "\\img.rsv"
#define    ID_IMAGE_CONFIGS                 "\\imgs.rsv"
#define    ID_VENDOR_LOGO                   "\\logoV.bmp"
#define    ID_SUBSCRIBER_LOGO               "\\logoS.bmp"
#define    ID_SOURCE_CONFIG                 "\\index.rsf"
#define    ID_FIND_SUFFIX                   "\\*.rsf"
#define    ID_NET_FILE_SUFFIX               "\\*.xml"
#define    ID_NET_FILE_FOLDER               "\\*.*"
#define    ID_PREFERENCE                    "\\preference.rsP"

#define    ID_COLOR_HUGE_DEFICIENCY             RGB(255, 153, 102)
#define    ID_COLOR_MID_DEFICIENCY              RGB(51,102, 255)
#define    ID_COLOR_TINY_DEFICIENCY             RGB(255, 255, 102)
#define    ID_COLOR_IRON_TRAMP                  RGB(255, 0, 102)
#define    ID_COLOR_TEXT                        RGB(0, 0, 0)
#define    ID_COLOR_BLANK                       RGB(255, 255, 255)
#define    ID_COLOR_BASIC_LEVER                 RGB(50, 200, 50)
#define    ID_COLOR_A_LEVER                     RGB(255, 255, 0)
#define    ID_COLOR_B_LEVER                     RGB(0, 110, 190)
#define    ID_COLOR_C_LEVER                     RGB(255, 0, 0)

#define    ID_STORAGE_PROJECTNAME               0x0001
#define    ID_STORAGE_VELOCITY                  0x0002
#define    ID_STORAGE_MATERIAL                  0x0003
#define    ID_STORAGE_FREQUENCY                 0x0004
#define    ID_STORAGE_SENISOR                   0x0005
#define    ID_STORAGE_WAVEFILTER                0x0006
#define    ID_STORAGE_TINY_DEFICIENCY           0x0007
#define    ID_STORAGE_TINY_DEFICIENCYB          0x0008
#define    ID_STORAGE_TINY_DEFICIENCYC          0x0009
#define    ID_STORAGE_MID_DEFICIENCY            0x000A
#define    ID_STORAGE_MID_DEFICIENCYB           0x000B
#define    ID_STORAGE_MID_DEFICIENCYC           0x000C
#define    ID_STORAGE_HUGE_DEFICIENCY           0x000D
#define    ID_STORAGE_HUGE_DEFICIENCYB          0x000E
#define    ID_STORAGE_HUGE_DEFICIENCYC          0x000F
#define    ID_STORAGE_IRON_TRAMP                0x0010
#define    ID_STORAGE_IRON_TRAMPB               0x0011
#define    ID_STORAGE_IRON_TRAMPC               0x0012
#define    ID_STORAGE_DISTANCE                  0x0013
#define    ID_STORAGE_SIZE                      0x0014
#define    ID_STORAGE_EXPORT_SETTING            0x0015
#define    ID_STORAGE_EXPORT_PATH               0x0016

#define    ID_EXPORT_ID_CHECKED                 0x0001
#define    ID_EXPORT_VOL_CHECKED                ID_EXPORT_ID_CHECKED<<1
#define    ID_EXPORT_TINY_CHECKED               ID_EXPORT_VOL_CHECKED<<1
#define    ID_EXPORT_MID_CHECKED                ID_EXPORT_TINY_CHECKED<<1
#define    ID_EXPORT_HUGE_CHECKED               ID_EXPORT_MID_CHECKED<<1
#define    ID_EXPORT_IRON_CHECKED               ID_EXPORT_HUGE_CHECKED<<1
#define    ID_EXPORT_RANGE_CHECKED              ID_EXPORT_IRON_CHECKED<<1

#define ID_TABLE_CONTENT_COLUMN_ID              0
#define ID_TABLE_CONTENT_COLUMN_TINY            ID_TABLE_CONTENT_COLUMN_ID+1
#define ID_TABLE_CONTENT_COLUMN_MID             ID_TABLE_CONTENT_COLUMN_TINY+1
#define ID_TABLE_CONTENT_COLUMN_HUGE            ID_TABLE_CONTENT_COLUMN_MID+1
#define ID_TABLE_CONTENT_COLUMN_IRON            ID_TABLE_CONTENT_COLUMN_HUGE+1
#define ID_TABLE_CONTENT_COLUMN_RANGE           ID_TABLE_CONTENT_COLUMN_IRON+1

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


