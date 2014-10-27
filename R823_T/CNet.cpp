
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
    
    //if ((res == NO_ERROR) || (res == ERROR_ALREADY_ASSIGNED))
    {
        HRESULT hr = m_ptrDomDocument.CreateInstance(_uuidof(MSXML2::DOMDocument30));
        if (FAILED(hr))
        {
            //return FALSE;
        }
        m_counter_thread = AfxBeginThread((AFX_THREADPROC)CounterThread,this);
        m_counter_thread->ResumeThread();
    }
    return ((res == NO_ERROR) || (res == ERROR_ALREADY_ASSIGNED))?TRUE:FALSE;
}

void CNet::findnode(MSXML2::IXMLDOMNodeListPtr nodes, LPVOID pParam)
{
    CNet *p = (CNet *)pParam;
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
                    if ((DS+DM+DB)>0)
                    {
                        p->pWnd->PostMessage(MSG_TINY_DEFICIENCY, DS);
                        p->pWnd->PostMessage(MSG_MID_DEFICIENCY, DM);
                        p->pWnd->PostMessage(MSG_HUGE_DEFICIENCY, DB);
                        p->pWnd->PostMessage(MSG_DISTANCE_BOUNDARY);
                    }
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
            findnode(subNodes, pParam);
            subNodes.Release();
            node.Release();
        }

    }
}

BOOL CNet::FindFile(LPVOID pParam)
{
    CNet *p = (CNet *)pParam;
    //CString strFilePath = _T("Q:\\Tencent\\QQ\\*.ini");

    HANDLE file, lastfile, folder, lastfoler; 
    WIN32_FIND_DATA fileData, lastfileData, folderdata, lastfolderdata;

    /*Find the last modified directory from which we can get the last xml file*/
    CString strFolderPath = _T("E:");
    strFolderPath += (TCHAR*)p->mConfig.folder.AllocSysString();
    strFolderPath += ID_NET_FILE_FOLDER;
    folder = FindFirstFile(strFolderPath, &folderdata);
    lastfolderdata = folderdata;
    lastfoler = folder;
    while(TRUE)
    {
        if (folderdata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            if(folderdata.cFileName[0]!='.')
            {
                if (folderdata.ftLastWriteTime.dwHighDateTime > lastfolderdata.ftLastWriteTime.dwHighDateTime)
                {
                    lastfolderdata = folderdata;
                    lastfoler = folder;
                } 
                else if (folderdata.ftLastWriteTime.dwHighDateTime == lastfolderdata.ftLastWriteTime.dwHighDateTime)
                {
                    if (folderdata.ftLastWriteTime.dwLowDateTime > lastfolderdata.ftLastWriteTime.dwLowDateTime)
                    {
                        lastfolderdata = folderdata;
                        lastfoler = folder;
                    }
                }
            }
        }
        if(!FindNextFile(folder,&folderdata))
            break;
    }
    FindClose(folder);

    CString strFilePath = _T("E:");
    strFilePath += (TCHAR*)p->mConfig.folder.AllocSysString();
    strFilePath += lastfolderdata.cFileName;
    strFilePath += ID_NET_FILE_SUFFIX;
    file = FindFirstFile(strFilePath, &fileData);
    lastfileData = fileData;
    lastfile = file;
    BOOL ret = ((signed int)file > 0)? TRUE: FALSE;
    BOOL bWorking = ret;
    /* Find the last modified file in the specified directory */
    while (bWorking)
    {
        bWorking = FindNextFile(file, &fileData);// bWorking indicates whether the file exists or not
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

    if (wcscmp(lastfileData.cFileName, p->mlastFile.cFileName) == 0)
    {
        return ret;
    } 
    else 
    {
        p->mlastFile = lastfileData;
        p->pWnd->PostMessage(MSG_STORE_CLEAR);
    }

    if ((signed int)lastfile > 0)
    {
        p->pWnd->PostMessage(MSG_NEW_ITEM);
        CString target = _T("E:");
        target += (TCHAR*)p->mConfig.folder.AllocSysString();
        target += _T("\\");
        target += lastfileData.cFileName;
        p->m_ptrDomDocument->load((TCHAR*)target.AllocSysString());
        p->m_pDocRoot = p->m_ptrDomDocument->GetdocumentElement();
        p->m_pDocRoot->get_childNodes(&(p->m_pXmlNodes));
        findnode(p->m_pXmlNodes, pParam);
        p->m_pXmlNodes.Release();
        p->m_pDocRoot.Release();
    }
    return ret;
}

BOOL CNet::ClosePort()
{
    m_counter_thread->SuspendThread();
    m_ptrDomDocument.Release();
    return TRUE;
}

void CNet::CounterThread(LPVOID pParam)
{
    while (1)
    {
        FindFile(pParam);
        Sleep(10000);
    }
}

void CNet::SetConfig(NetConfig arg)
{
    mConfig = arg;
}