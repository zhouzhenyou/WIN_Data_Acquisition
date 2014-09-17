#pragma once
#include "stdafx.h"
#include "Resource.h"

// CR823_TDlg dialog
class CR823_TNet : public CDialog
{
// Construction
public:
	CR823_TNet(CWnd* pParent = NULL);	// standard constructor
    CString mIp;
    CString mUsername;
    CString mPassword;
    CString mFolder;
	enum { IDD = IDD_DIALOG_NET };

protected:
    virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
    DECLARE_MESSAGE_MAP()
// Active on the Dialog
private:
    CEdit m_edit_ip;
    CEdit m_edit_username;
    CEdit m_edit_password;
    CEdit m_edit_folder;
    void OnOK();
    void OnCancel();
};