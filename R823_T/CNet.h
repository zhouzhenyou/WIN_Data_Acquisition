#ifndef CNET_H_
#define CNET_H_

#include "stdafx.h"
#include "CDlgconfigure.h"
#include "CDevice.h"

/* This structure corespond with the setting in the net dialog */
typedef struct _net_config {
    CString ip;
    CString username;
    CString passward;
    CString folder;
} NetConfig;

class CNet
{
public:
    CNet(CWnd* pParent);
    BOOL OpenPort();
    BOOL ClosePort();
    void SetConfig(NetConfig arg);

private:
    MSXML2::IXMLDOMDocumentPtr m_ptrDomDocument;
    MSXML2::IXMLDOMElementPtr m_pDocRoot;
    MSXML2::IXMLDOMElementPtr m_pElement;
    MSXML2::IXMLDOMNodeListPtr m_pXmlNodes;
    MSXML2::IXMLDOMNamedNodeMapPtr m_pXmlNodeAtts;
    MSXML2::IXMLDOMNodePtr m_pXmlNode;
    MSXML2::IXMLDOMNodePtr m_pXmlNextNode;
    WIN32_FIND_DATA mlastFile;
    NetConfig mConfig; //The object which stores the configurations of the net
    NETRESOURCE nr;
	typedef void * Timer_HANDLE;
	Timer_HANDLE Timer_Handle;

    CWnd* pWnd;
    CWinThread *m_counter_thread;// Update the lastest modified file
    static void findnode(MSXML2::IXMLDOMNodeListPtr nodes,LPVOID pParam);  
    static BOOL FindFile(LPVOID pParam);
    static void CounterThread(LPVOID pParam);
};

#endif
