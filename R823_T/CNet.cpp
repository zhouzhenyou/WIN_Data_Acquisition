
#include "CNet.h"

CNet::CNet(CWnd* pParent)
{
    pWnd = pParent;
    Timer_Handle = NULL;
}

BOOL CNet::init()
{
    return TRUE;
}

BOOL CNet::OpenPort()
{
    DWORD res;
    DWORD dwFlags;
    TCHAR szUserName[32] = _T("Administrator"),
          szPassword[32] = _T(""),
          szLocalName[32] = _T("Q:"),
          szRemoteName[MAX_PATH] = _T("\\\\192.168.0.27\\SharedDocs");
    //  
    //   Assign   values   to   the   NETRESOURCE   structure.  
    // 
    memset(&nr, 0, sizeof(NETRESOURCE));
    nr.dwType   =   RESOURCETYPE_ANY;
    nr.lpLocalName   =   szLocalName;
    nr.lpRemoteName   =   szRemoteName;
    nr.lpProvider   =   NULL;
    dwFlags = CONNECT_UPDATE_PROFILE;

    //  
    //   Call   the   WNetAddConnection2   function   to   assign  
    //       a   drive   letter   to   the   share.  
    //  
    WNetCancelConnection2(szLocalName, 0,true);
    res   =   WNetAddConnection2(&nr,   szPassword,   szUserName,   dwFlags);
    //  
    //   If   the   call   succeeds,   inform   the   user;   otherwise,  
    //     print   the   error.  
    // 
    
    /*
    CString Username = "Administrator";
    CString Password = "";
    LPNETRESOURCEW lpNetR = new NETRESOURCEW;
    CString NetConnentName = "\\\\192.168.0.27\\SharedDocs$";
    lpNetR->dwScope = RESOURCE_GLOBALNET;
    lpNetR->dwType = RESOURCETYPE_DISK;
    lpNetR->dwDisplayType = RESOURCEDISPLAYTYPE_SHARE;
    lpNetR->dwUsage = RESOURCEUSAGE_CONNECTABLE;
    lpNetR->lpLocalName = "";
    lpNetR->lpRemoteName = NetConnentName.c_str();
    lpNetR->lpProvider = "";
    WNetCancelConnection2W(lpNetR->lpRemoteName, dwFlages, true);
    res = WNetAddConnection2(lpNetR, Password.c_str(),Username.c_str(), dwFlages)
*/
    //CFileFind finder;
    //CString strPath;
    CString strFilePath = _T("Q:\\Tencent\\QQ\\*.ini");
    HANDLE file; 
    WIN32_FIND_DATA fileData;
    BOOL bWorking = true;//finder.FindFile(_T("Q:\\"))
    file = FindFirstFile(strFilePath, &fileData);
    while (bWorking)
    {
        bWorking = FindNextFile(file, &fileData);
    //strPath就是所要获取Test目录下的文件夹和文件（包括路径）
    }

    return ((res == NO_ERROR) || (res == ERROR_ALREADY_ASSIGNED))?TRUE:FALSE;
}
/*
void FindFiles()
{
    TCHAR tmpWChar[MAX_PATH] = {0};
    GetCurrentDirectory(MAX_PATH, tmpWChar);

    HANDLE file; 
    CString strTmp, strFilePath, targetFilePath;
    CTime tm = CTime::GetCurrentTime();
    strTmp.Empty();
    strFilePath.Empty();
    targetFilePath.Empty();
    strFilePath += ID_NET_FILE_SUFFIX;
    WIN32_FIND_DATA fileData;
    CString str;
    file = FindFirstFile(strFilePath, &fileData);
    BOOL res = TRUE;
    char tmppath[MAX_PATH];
    char tmpbuf[MAX_PATH];
    m_record.Clear();
    memset(tmpbuf, 0, MAX_PATH);
    memcpy(tmpbuf, mConfigure.getProjectName().GetBuffer(), mConfigure.getProjectName().GetLength()*sizeof(TCHAR));
    while(res)
    {
        memset(tmppath, 0, MAX_PATH);
        memset(tmpbuf, 0, MAX_PATH);
        strTmp.Empty();
        strTmp = arg;
        strTmp += _T("\\");
        strTmp += fileData.cFileName;
        WideCharToMultiByte(CP_ACP, 0, strTmp, -1, tmppath, sizeof(tmppath), NULL, NULL);
        GSFile tmpTarget(tmppath, GSFile::ReadOnly);
        if (tmpTarget.GetFileVersion() == FILE_SOURCE_TYPE)
        {
            record_item_header inner_header;
            memset(&inner_header, 0, sizeof(record_item_header));
            tmpTarget.ReadRecordHeader(&inner_header, sizeof(record_item_header));
            if ((memcmp(inner_header.volume, tmpbuf, MAX_PATH ) == 0) && (mConfigure.current_subvol == 1))
            {
                continue;
            }
            CString combox_tmp;
            combox_tmp.Format(_T("%s"), inner_header.volume);
            m_record.AddString(combox_tmp);
            list.AddTail(strTmp);
        }
        tmpTarget.Done();
        res = FindNextFile(file, &fileData);
    }
    m_record.SetCurSel(0);
}*/


BOOL CNet::ClosePort()
{
    //m_counter_thread->SuspendThread();
    return TRUE;
}

BOOL CNet::SetTimerMode()
{

    //InitTimer();
    return FALSE;
}

BOOL CNet::InitTimer()
{

    return TRUE;
}

int CNet::ReadPort()
{
    return 0;
}

void CNet::CounterThread(LPVOID pParam)
{

}

void CNet::SetDeviceConfig(CDlgconfigure arg)
{
    //mConfig = arg;
}