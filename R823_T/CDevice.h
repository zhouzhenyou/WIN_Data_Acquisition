#ifndef CDEVICE_H_
#define CDEVICE_H_

#include "stdafx.h"
#include "CDlgconfigure.h"

#define SLEEP_GAP						1000
#define DISTANCE                        1000.0
#define MILLIONSECONDPERSECOND          1000
#define COUNT_THRESTHOLD				65300
#define MSG_TINY_DEFICIENCY             WM_USER+1001  
#define MSG_MID_DEFICIENCY              WM_USER+1002
#define MSG_HUGE_DEFICIENCY             WM_USER+1003
#define MSG_IRON_TRAMP                  WM_USER+1004
#define MSG_DISTANCE_BOUNDARY           WM_USER+1005
#define MSG_STORE_CLEAR					WM_USER+1006
#define MSG_DEVICE_NOT_FOUND            WM_USER+1007
#define MSG_NEW_ITEM                    WM_USER+1008

#define VALUE_CARD_START                52
#define VALUE_INIT_TIMER				65535

class CDevice
{
public:
    CDevice(CWnd* pParent, DWORD cardID);
    BOOL init();
    BOOL OpenPort();
    BOOL ClosePort();
    int ReadPort();
    BOOL SetTimerMode();
    BOOL InitTimer();
    void SetDeviceConfig(CDlgconfigure arg);

private:
    CDlgconfigure mConfig;
    DWORD mCardID;
    HINSTANCE DLL_Handle;
	typedef void * Timer_HANDLE;
	Timer_HANDLE Timer_Handle;

    typedef void *(__stdcall *KP832_LOCATEANDOPEN)(DWORD card_no);
	KP832_LOCATEANDOPEN KP832_LocateAndOpen;
	
	typedef int (__stdcall *KP832_CLOSE)(Timer_HANDLE hIO);
	KP832_CLOSE KP832_Close ;
	
	typedef BYTE (__stdcall *KP832_INPUT)(Timer_HANDLE hIO);
	KP832_INPUT KP832_Input;
	
	typedef void (__stdcall *KP832_OUTPUT)(Timer_HANDLE hio,short int channel,bool states,bool initop,long val);
	KP832_OUTPUT KP832_Output;
	
	typedef void (__stdcall *KP832_8254_CTRL_WRITE)(Timer_HANDLE hIO,long t8254csaddr, BYTE timer, BYTE modeword);
	KP832_8254_CTRL_WRITE KP832_8254_CTRL_Write;
	
	typedef void (__stdcall *KP832_8254_VALUE_WRITE)(Timer_HANDLE hIO,long t8254csaddr, BYTE timer, unsigned short timeinitrvale);
	KP832_8254_VALUE_WRITE KP832_8254_Value_Write;
	
	typedef void (__stdcall *KP832_WRITE_TCWCT)(Timer_HANDLE hIO,BYTE tcwct);
	KP832_WRITE_TCWCT KP832_Write_TCWCT;
	
	typedef void (__stdcall *KP832_WRITE_TCWCAS)(Timer_HANDLE hIO,BYTE tcwcas);
	KP832_WRITE_TCWCAS KP832_Write_TCWCAS;
	
	typedef WORD (__stdcall *KP832_8254_VALUE_READ)(Timer_HANDLE hIO, long t8254csaddr, BYTE timer);
	KP832_8254_VALUE_READ KP832_8254_Value_Read;
	
	typedef WORD (__stdcall *KP832_STATE_READ)(Timer_HANDLE hIO);
	KP832_STATE_READ KP832_State_Read;

    CWnd* pWnd;

    CWinThread *m_counter_thread;

    static void CounterThread(LPVOID pParam);
};

#endif
