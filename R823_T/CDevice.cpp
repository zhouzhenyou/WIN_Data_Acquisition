
#include "CDevice.h"

CDevice::CDevice(CWnd* pParent, DWORD cardID)
{
    mCardID = cardID;
    pWnd = pParent;
    Timer_Handle = NULL;
    
    KP832_LocateAndOpen = NULL;
    KP832_8254_CTRL_Write = NULL;
    KP832_Write_TCWCT = NULL;
    KP832_8254_Value_Write = NULL;
    KP832_Write_TCWCAS = NULL;
	KP832_Input = NULL;
	KP832_8254_Value_Read = NULL;
	KP832_Close = NULL;
}

BOOL CDevice::init()
{
    DLL_Handle=NULL;
	CString m_dlldir;
	TCHAR *aaa;
	GetFullPathName(_T("IODLL.dll"), 256, m_dlldir.GetBuffer(256),&aaa);
	m_dlldir.Replace(_T("\\"),_T("/"));
    DLL_Handle = LoadLibrary(m_dlldir);
    if (DLL_Handle == NULL)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

BOOL CDevice::OpenPort()
{
    int tcwct = 0;
    tcwct = tcwct + 1;
    tcwct = tcwct + 2;
    tcwct = tcwct + 4;
    tcwct = tcwct + 8; 
    if (DLL_Handle != NULL) 
    {
	    KP832_LocateAndOpen = (KP832_LOCATEANDOPEN)GetProcAddress(DLL_Handle,"KP832_LocateAndOpen");
        Timer_Handle = KP832_LocateAndOpen(0);
        KP832_Write_TCWCT = (KP832_WRITE_TCWCT)GetProcAddress(DLL_Handle,"KP832_Write_TCWCT");
        KP832_Write_TCWCT(Timer_Handle,tcwct);
        KP832_Write_TCWCAS = (KP832_WRITE_TCWCAS)GetProcAddress(DLL_Handle,"KP832_Write_TCWCAS");
        KP832_Write_TCWCAS(Timer_Handle, 0);   

        KP832_8254_CTRL_Write = (KP832_8254_CTRL_WRITE)GetProcAddress(DLL_Handle,"KP832_8254_CTRL_Write");
        KP832_8254_CTRL_Write(Timer_Handle, 16, 0, VALUE_CARD_START);
		KP832_8254_Value_Write=(KP832_8254_VALUE_WRITE)GetProcAddress(DLL_Handle,"KP832_8254_Value_Write");
        KP832_8254_Value_Write(Timer_Handle, 16, 0, VALUE_INIT_TIMER);
        
        KP832_8254_CTRL_Write = (KP832_8254_CTRL_WRITE)GetProcAddress(DLL_Handle,"KP832_8254_CTRL_Write");
        KP832_8254_CTRL_Write(Timer_Handle, 16, 1, VALUE_CARD_START);
        KP832_8254_Value_Write=(KP832_8254_VALUE_WRITE)GetProcAddress(DLL_Handle,"KP832_8254_Value_Write");
        KP832_8254_Value_Write(Timer_Handle, 16, 1, VALUE_INIT_TIMER);

        //KP832_8254_CTRL_Write = (KP832_8254_CTRL_WRITE)GetProcAddress(DLL_Handle,"KP832_8254_CTRL_Write");
        KP832_8254_CTRL_Write(Timer_Handle, 16, 2, VALUE_CARD_START);
        //KP832_8254_Value_Write=(KP832_8254_VALUE_WRITE)GetProcAddress(DLL_Handle,"KP832_8254_Value_Write");
        KP832_8254_Value_Write(Timer_Handle, 16, 2, VALUE_INIT_TIMER);

        KP832_8254_CTRL_Write = (KP832_8254_CTRL_WRITE)GetProcAddress(DLL_Handle,"KP832_8254_CTRL_Write");
        KP832_8254_CTRL_Write(Timer_Handle, 32, 0, VALUE_CARD_START);
        KP832_8254_Value_Write=(KP832_8254_VALUE_WRITE)GetProcAddress(DLL_Handle,"KP832_8254_Value_Write");
        KP832_8254_Value_Write(Timer_Handle, 32, 0, VALUE_INIT_TIMER);
        
    }

	if (Timer_Handle == 0)
    {
        this->pWnd->PostMessage(MSG_DEVICE_NOT_FOUND);
    }

    m_counter_thread = AfxBeginThread((AFX_THREADPROC)CounterThread,this);
    m_counter_thread->ResumeThread();
    return TRUE;
}

BOOL CDevice::ClosePort()
{
    //m_counter_thread->SuspendThread();
    if(DLL_Handle != NULL)
    {
	    KP832_Close = (KP832_CLOSE)GetProcAddress(DLL_Handle,"KP832_Close");
        KP832_Close(Timer_Handle);
        return TRUE;
    }
    return FALSE;
}

BOOL CDevice::SetTimerMode()
{
	//BYTE modeword=(2<<2)+0+0;

    if (DLL_Handle != NULL)
    {
        KP832_8254_CTRL_Write = (KP832_8254_CTRL_WRITE)GetProcAddress(DLL_Handle,"KP832_8254_CTRL_Write");
        KP832_8254_CTRL_Write(Timer_Handle, 16, 0, (2<<1) + 16 + 32);
        KP832_8254_CTRL_Write = (KP832_8254_CTRL_WRITE)GetProcAddress(DLL_Handle,"KP832_8254_CTRL_Write");
        KP832_8254_CTRL_Write(Timer_Handle, 16, 1, (2<<1) + 16 + 32);
        KP832_8254_CTRL_Write = (KP832_8254_CTRL_WRITE)GetProcAddress(DLL_Handle,"KP832_8254_CTRL_Write");
        KP832_8254_CTRL_Write(Timer_Handle, 16, 2, (2<<1) + 16 + 32);
        KP832_8254_CTRL_Write = (KP832_8254_CTRL_WRITE)GetProcAddress(DLL_Handle,"KP832_8254_CTRL_Write");
        KP832_8254_CTRL_Write(Timer_Handle, 32, 0, (2<<1) + 16 + 32);
    }
    InitTimer();
    return FALSE;
}

BOOL CDevice::InitTimer()
{
    if (DLL_Handle != NULL)
    {
        KP832_8254_Value_Write=(KP832_8254_VALUE_WRITE)GetProcAddress(DLL_Handle,"KP832_8254_Value_Write");
        KP832_8254_Value_Write(Timer_Handle, 16, 0, 65535);
        KP832_8254_Value_Write=(KP832_8254_VALUE_WRITE)GetProcAddress(DLL_Handle,"KP832_8254_Value_Write");
        KP832_8254_Value_Write(Timer_Handle, 16, 1, 65535);
        KP832_8254_Value_Write=(KP832_8254_VALUE_WRITE)GetProcAddress(DLL_Handle,"KP832_8254_Value_Write");
        KP832_8254_Value_Write(Timer_Handle, 16, 2, 65535);
        KP832_8254_Value_Write=(KP832_8254_VALUE_WRITE)GetProcAddress(DLL_Handle,"KP832_8254_Value_Write");
        KP832_8254_Value_Write(Timer_Handle, 32, 0, 65535);
        return TRUE;
    }

    return FALSE;
}

int CDevice::ReadPort()
{
    if (DLL_Handle != NULL) 
	{
		KP832_8254_Value_Read=(KP832_8254_VALUE_READ)GetProcAddress(DLL_Handle,"KP832_8254_Value_Read");
        WORD ret = KP832_8254_Value_Read(Timer_Handle, 16, 0);
        ret = 65535 - ret;
        return ret;
	}
    return 0;
}

void CDevice::CounterThread(LPVOID pParam)
{
    CDevice *p = (CDevice *)pParam;
    
    bool tiny_once = true;
    bool mid_once = true;
    bool huge_once = true;
    bool iron_once = true;
    int tiny_count = 65535;
    int mid_count = 65535;
    int huge_count = 65535;
    int iron_count = 65535;
    int tmp_tiny = 0;
    int tmp_mid = 0;
    int tmp_huge = 0;
    int tmp_iron = 0;
    int msg_count_tiny = 0;
    int msg_count_mid = 0;
    int msg_count_huge = 0;
    int msg_count_iron = 0;
    double cycle_count = 0;
    WORD current_data = 0;
	float velocity = 0.0;
	float distance_tmp = 0.0;
	bool islow = true;
    int testop = 1;
    int ts = 1;
    while(1)
    {
        /////////////////////////////////////////////////////////////////////////
        /*
		p->pWnd->PostMessage(MSG_NEW_ITEM);
        if (testop%3 == 1)
        {
            p->pWnd->PostMessage(MSG_TINY_DEFICIENCY, 1);
        }
        if (testop%3 == 2)
        {
            p->pWnd->PostMessage(MSG_MID_DEFICIENCY, 1);
        }

        if (testop%4 == 1)
        {
            p->pWnd->PostMessage(MSG_HUGE_DEFICIENCY, 1);
        }

        if (testop%4 == 2)
        {
            p->pWnd->PostMessage(MSG_IRON_TRAMP, 1);
        }

		velocity = p->mConfig.getVelocity();
		distance_tmp = ((testop) * SLEEP_GAP * velocity)/MILLIONSECONDPERSECOND;
        if (distance_tmp >= p->mConfig.getDistance()  && (distance_tmp > 0))
        {
            p->pWnd->PostMessage(MSG_DISTANCE_BOUNDARY);
            testop = 0;
            ts++;
        }
        else
        {
            testop++;
        }

        if (ts >= 8)
        {
            ts = 0;
            p->pWnd->PostMessage(MSG_STORE_CLEAR);
        }*/
		
        //////////////////////////////////////////////////////////////////////
        if (p->DLL_Handle != NULL) 
        {
            p->KP832_8254_Value_Read=(KP832_8254_VALUE_READ)GetProcAddress(p->DLL_Handle,"KP832_8254_Value_Read");
			p->KP832_Input=(KP832_INPUT)GetProcAddress(p->DLL_Handle,"KP832_Input");
            
            
            current_data = p->KP832_Input(p->Timer_Handle);
            current_data = current_data & 0x01;
            
            if (current_data == 1)
            {
				if (islow)
				{

					islow = false;
                    p->pWnd->PostMessage(MSG_NEW_ITEM);
					p->KP832_8254_CTRL_Write = (KP832_8254_CTRL_WRITE)GetProcAddress(p->DLL_Handle,"KP832_8254_CTRL_Write");
					p->KP832_8254_CTRL_Write(p->Timer_Handle, 16, 0, 8);
					p->KP832_8254_Value_Read=(KP832_8254_VALUE_READ)GetProcAddress(p->DLL_Handle,"KP832_8254_Value_Read");
					tiny_count = p->KP832_8254_Value_Read(p->Timer_Handle, 16, 0);

					p->KP832_8254_CTRL_Write = (KP832_8254_CTRL_WRITE)GetProcAddress(p->DLL_Handle,"KP832_8254_CTRL_Write");
					p->KP832_8254_CTRL_Write(p->Timer_Handle, 16, 1, 8);
					p->KP832_8254_Value_Read=(KP832_8254_VALUE_READ)GetProcAddress(p->DLL_Handle,"KP832_8254_Value_Read");
					mid_count = p->KP832_8254_Value_Read(p->Timer_Handle, 16, 1);

					p->KP832_8254_CTRL_Write = (KP832_8254_CTRL_WRITE)GetProcAddress(p->DLL_Handle,"KP832_8254_CTRL_Write");
					p->KP832_8254_CTRL_Write(p->Timer_Handle, 16, 2, 8);
					p->KP832_8254_Value_Read=(KP832_8254_VALUE_READ)GetProcAddress(p->DLL_Handle,"KP832_8254_Value_Read");
					huge_count = p->KP832_8254_Value_Read(p->Timer_Handle, 16, 2);

					p->KP832_8254_CTRL_Write = (KP832_8254_CTRL_WRITE)GetProcAddress(p->DLL_Handle,"KP832_8254_CTRL_Write");
					p->KP832_8254_CTRL_Write(p->Timer_Handle, 32, 0, 8);
					p->KP832_8254_Value_Read=(KP832_8254_VALUE_READ)GetProcAddress(p->DLL_Handle,"KP832_8254_Value_Read");
					iron_count = p->KP832_8254_Value_Read(p->Timer_Handle, 32, 0);
                    
				}

				p->KP832_8254_CTRL_Write = (KP832_8254_CTRL_WRITE)GetProcAddress(p->DLL_Handle,"KP832_8254_CTRL_Write");
				p->KP832_8254_CTRL_Write(p->Timer_Handle, 16, 0, 8);
				p->KP832_8254_Value_Read=(KP832_8254_VALUE_READ)GetProcAddress(p->DLL_Handle,"KP832_8254_Value_Read");
                tmp_tiny = p->KP832_8254_Value_Read(p->Timer_Handle, 16, 0);
                msg_count_tiny = tiny_count - tmp_tiny;

                if ((msg_count_tiny != 0) && tiny_once )
                {
                    tiny_once = false;
                    p->pWnd->PostMessage(MSG_TINY_DEFICIENCY, 1);
                }

                if (msg_count_tiny > 0)
                {
                    p->pWnd->PostMessage(MSG_TINY_DEFICIENCY, msg_count_tiny);
                    tiny_count = tmp_tiny;
                }
                else if (msg_count_tiny < 0)
                {
                    if (abs(msg_count_tiny) > COUNT_THRESTHOLD)
                    {
                        msg_count_tiny += 65535;
                        p->pWnd->PostMessage(MSG_TINY_DEFICIENCY, msg_count_tiny);
					}
					tiny_count = tmp_tiny;
                }

				p->KP832_8254_CTRL_Write = (KP832_8254_CTRL_WRITE)GetProcAddress(p->DLL_Handle,"KP832_8254_CTRL_Write");
				p->KP832_8254_CTRL_Write(p->Timer_Handle, 16, 1, 8);
				p->KP832_8254_Value_Read=(KP832_8254_VALUE_READ)GetProcAddress(p->DLL_Handle,"KP832_8254_Value_Read");
                tmp_mid = p->KP832_8254_Value_Read(p->Timer_Handle, 16, 1);
                msg_count_mid = mid_count - tmp_mid;

                if ((msg_count_mid != 0) && mid_once)
                {
                    mid_once = false;
                    p->pWnd->PostMessage(MSG_MID_DEFICIENCY, 1);
                }

                if (msg_count_mid > 0)
                {
                    p->pWnd->PostMessage(MSG_MID_DEFICIENCY, msg_count_mid);
                    mid_count = tmp_mid;
                }
                else if (msg_count_mid < 0)
                {
                    if (abs(msg_count_mid) > COUNT_THRESTHOLD)
                    {
                        msg_count_mid += 65535;
                        p->pWnd->PostMessage(MSG_MID_DEFICIENCY, msg_count_mid);
					}
					mid_count = tmp_mid;
                }

		        p->KP832_8254_CTRL_Write = (KP832_8254_CTRL_WRITE)GetProcAddress(p->DLL_Handle,"KP832_8254_CTRL_Write");
				p->KP832_8254_CTRL_Write(p->Timer_Handle, 16, 2, 8);
				p->KP832_8254_Value_Read=(KP832_8254_VALUE_READ)GetProcAddress(p->DLL_Handle,"KP832_8254_Value_Read");
                tmp_huge = p->KP832_8254_Value_Read(p->Timer_Handle, 16, 2);
                msg_count_huge = huge_count - tmp_huge;

                if ((msg_count_huge != 0) && huge_once)
                {
                    huge_once = false;
                    p->pWnd->PostMessage(MSG_HUGE_DEFICIENCY, 1);
                }
                
                if (msg_count_huge > 0)
                {
                    if (msg_count_huge > 10)
                    {
                        p->pWnd->PostMessage(MSG_HUGE_DEFICIENCY, msg_count_huge/255);
                    }
                    else
                    {
                        p->pWnd->PostMessage(MSG_HUGE_DEFICIENCY, msg_count_huge);
                    }
                    huge_count = tmp_huge;

                }
                else if (msg_count_huge < 0)
                {
                    if (abs(msg_count_huge) > COUNT_THRESTHOLD)
                    {
                        msg_count_huge += 65535;
                        if (msg_count_huge > 10)
                        {
                            p->pWnd->PostMessage(MSG_HUGE_DEFICIENCY, msg_count_huge/255);
                        }
                        else
                        {
                            p->pWnd->PostMessage(MSG_HUGE_DEFICIENCY, msg_count_huge);
                        }
					}
					huge_count = tmp_huge;
                }

				p->KP832_8254_CTRL_Write = (KP832_8254_CTRL_WRITE)GetProcAddress(p->DLL_Handle,"KP832_8254_CTRL_Write");
				p->KP832_8254_CTRL_Write(p->Timer_Handle, 32, 0, 8);
				p->KP832_8254_Value_Read=(KP832_8254_VALUE_READ)GetProcAddress(p->DLL_Handle,"KP832_8254_Value_Read");
                tmp_iron = p->KP832_8254_Value_Read(p->Timer_Handle, 32, 0);
				msg_count_iron = iron_count - tmp_iron;

                if ((msg_count_iron != 0) && iron_once)
                {
                    iron_once = false;
                    p->pWnd->PostMessage(MSG_IRON_TRAMP, 1);
                }

                if (msg_count_iron > 0)
                {
                    p->pWnd->PostMessage(MSG_IRON_TRAMP, msg_count_iron);
                    iron_count = tmp_iron;
                }
                else if (msg_count_iron < 0)
                {
                    if (abs(msg_count_iron) > COUNT_THRESTHOLD)
                    {
                        msg_count_iron += 65535;
                        p->pWnd->PostMessage(MSG_IRON_TRAMP, msg_count_iron);
                        
                    }
					iron_count = tmp_iron;
                }
				
				velocity = p->mConfig.getVelocity();
				distance_tmp = ((cycle_count++) * SLEEP_GAP * velocity)/MILLIONSECONDPERSECOND;
                if (distance_tmp >= p->mConfig.getDistance() && (distance_tmp > 0))
                {
                    p->pWnd->PostMessage(MSG_DISTANCE_BOUNDARY);
                    cycle_count = 0;
                }
            }
            else if (current_data == 0)
            {
				if (islow == false)
				{
					islow = true;
                    cycle_count = 0;
					p->pWnd->PostMessage(MSG_STORE_CLEAR);
				}
            }
        }

        Sleep(SLEEP_GAP);
    }
}

void CDevice::SetDeviceConfig(CDlgconfigure arg)
{
    mConfig = arg;
}