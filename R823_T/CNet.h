#ifndef CNET_H_
#define CNET_H_

#include "stdafx.h"
#include "CDlgconfigure.h"

class CNet
{
public:
    CNet(CWnd* pParent);
    BOOL init();
    BOOL OpenPort();
    BOOL ClosePort();
    int ReadPort();
    BOOL SetTimerMode();
    BOOL InitTimer();
    void SetDeviceConfig(CDlgconfigure arg);

private:
    CDlgconfigure mConfig;
    NETRESOURCE nr;
	typedef void * Timer_HANDLE;
	Timer_HANDLE Timer_Handle;

    CWnd* pWnd;
    CWinThread *m_counter_thread;

    static void CounterThread(LPVOID pParam);
};

#endif
