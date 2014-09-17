
#include "CNet.h"

CNet::CNet(CWnd* pParent)
{
    pWnd = pParent;
    Timer_Handle = NULL;
}

BOOL CNet::OpenPort()
{
    DWORD res;
    DWORD dwFlags;
    TCHAR *szRemoteName = (TCHAR*)mConfig.ip.AllocSysString(),
          *szUserName = (TCHAR*)mConfig.username.AllocSysString(),
          *szPassword = (TCHAR*)mConfig.passward.AllocSysString(),
          *szLocalName = _T("Q:");
    /*
    TCHAR szUserName[32] = _T("Administrator"),
          szPassword[32] = _T(""),
          szLocalName[32] = _T("Q:"),
          szRemoteName[MAX_PATH] = _T("\\\\192.168.0.27\\SharedDocs");*/
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
    
    if ((res == NO_ERROR) || (res == ERROR_ALREADY_ASSIGNED))
    {
        m_counter_thread = AfxBeginThread((AFX_THREADPROC)CounterThread,this);
        m_counter_thread->ResumeThread();
    }
    return ((res == NO_ERROR) || (res == ERROR_ALREADY_ASSIGNED))?TRUE:FALSE;
}

void CNet::findnode(MSXML2::IXMLDOMNodeListPtr nodes)
{
    if (nodes == NULL) return;
    long xmlNodesNum, attsNum, xmltargetNum,xmlValue;
    MSXML2::IXMLDOMNamedNodeMapPtr atts;
    MSXML2::IXMLDOMNodePtr node,nodeAttr,nodetarget, nodeprt;
    MSXML2::IXMLDOMNodeListPtr subNodes,targetNodes;
    nodes->get_length(&xmlNodesNum);
    if (xmlNodesNum == 0)
    {
        return;
    }

    while (xmlNodesNum > 0) 
    {
        nodes->get_item(--xmlNodesNum, &node);
        TCHAR *nodeName = (TCHAR*)(_bstr_t)node->nodeName;
        if (wcscmp(nodeName,_T("DeviceValuation")) == 0)
        {
            node->get_childNodes(&targetNodes);
            targetNodes->get_length(&xmlValue);
            while (xmlValue > 0)
            {
                targetNodes->get_item(--xmlValue, &nodeprt);
                TCHAR *nodeName = (TCHAR*)(_bstr_t)nodeprt->nodeName;
                if (wcscmp(nodeName,_T("ChannelStatistics")) == 0)
                {
                    int DS = 0,
                        DM = 0,
                        DB = 0;
                    nodeprt->get_childNodes(&subNodes);
                    subNodes->get_length(&xmltargetNum);
                    while(xmltargetNum > 0)
                    {
                        subNodes->get_item(--xmltargetNum, &nodetarget);
                        TCHAR *channelNodeName = (TCHAR*)(_bstr_t)nodetarget->nodeName;
                        if (wcscmp(channelNodeName,_T("DefectCounter")) == 0)
                        {
                            TCHAR *value = (TCHAR*)(_bstr_t)nodetarget->text;
                            int tmp = _wtoi(value);
                            nodetarget->get_attributes(&atts);
                            atts->get_length(&attsNum);
                            atts->get_item(--attsNum, &nodeAttr);
                            TCHAR *name = (TCHAR*)(_bstr_t)nodeAttr->nodeName;
                            TCHAR *text = (TCHAR*)(_bstr_t)nodeAttr->text;
                            if (wcscmp(name,_T("F1")) == 0)
                            {
                                DS = tmp;
                            } 
                            else if (wcscmp(name,_T("F2")) == 0)
                            {
                                DM = tmp;
                            }
                            else if (wcscmp(name,_T("F3")) == 0)
                            {
                                DB = tmp;
                            }                        
                            nodeAttr.Release();
                            atts.Release();
                        }
                        nodetarget.Release();
                    }
                    pWnd->SendMessage(MSG_TINY_DEFICIENCY, DS);
                    pWnd->SendMessage(MSG_MID_DEFICIENCY, DM);
                    pWnd->SendMessage(MSG_HUGE_DEFICIENCY, DB);
                    pWnd->SendMessage(MSG_DISTANCE_BOUNDARY);
                    subNodes.Release();
                }
                nodeprt.Release();
            }
            node.Release();
            break;
        }
        else
        {
            node->get_childNodes(&subNodes);
            findnode(subNodes);
            subNodes.Release();
            node.Release();
        }

    }
}

BOOL CNet::FindFile()
{
    //CString strFilePath = _T("Q:\\Tencent\\QQ\\*.ini");
    HRESULT hr = m_ptrDomDocument.CreateInstance(_uuidof(MSXML2::DOMDocument30));
    if (FAILED(hr))
    {
        return FALSE;
    }

    CString strFilePath = _T("Q:");
    strFilePath += (TCHAR*)mConfig.folder.AllocSysString();
    strFilePath += ID_NET_FILE_SUFFIX;
    HANDLE file, lastfile; 
    WIN32_FIND_DATA fileData, lastfileData;
    file = FindFirstFile(strFilePath, &fileData);
    lastfileData = fileData;
    lastfile = file;
    BOOL ret = ((signed int)file > 0)? TRUE: FALSE;
    BOOL bWorking = ret;
    while (bWorking)
    {
        bWorking = FindNextFile(file, &fileData);
        if (bWorking)
        {
            if (fileData.ftLastWriteTime.dwHighDateTime > lastfileData.ftLastWriteTime.dwHighDateTime)
            {
                lastfileData = fileData;
                lastfile = file;
            } 
            else if (fileData.ftLastWriteTime.dwHighDateTime == lastfileData.ftLastWriteTime.dwHighDateTime)
            {
                if (fileData.ftLastWriteTime.dwLowDateTime > lastfileData.ftLastWriteTime.dwLowDateTime)
                {
                    lastfileData = fileData;
                    lastfile = file;
                }
            }
        }

        if (!ret)
        {
            ret = ((signed int)file > 0)? TRUE: FALSE;
        }
    }

    if ((signed int)lastfile > 0)
    {
        pWnd->SendMessage(MSG_NEW_ITEM);
        CString target = _T("Q:");
        target += (TCHAR*)mConfig.folder.AllocSysString();
        target += _T("\\");
        target += lastfileData.cFileName;
        m_ptrDomDocument->load((TCHAR*)target.AllocSysString());
        m_pDocRoot = m_ptrDomDocument->GetdocumentElement();
        m_pDocRoot->get_childNodes(&m_pXmlNodes);
        findnode(m_pXmlNodes);
        m_pXmlNodes.Release();
        m_pDocRoot.Release();
        m_ptrDomDocument.Release();
    }
    return ret;
}

BOOL CNet::ClosePort()
{
    //m_counter_thread->SuspendThread();
    return TRUE;
}

void CNet::CounterThread(LPVOID pParam)
{
    //FindFile();
}

void CNet::SetConfig(NetConfig arg)
{
    mConfig = arg;
}