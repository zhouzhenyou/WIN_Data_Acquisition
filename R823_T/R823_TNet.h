#include "stdafx.h"

// CR823_TDlg dialog
class CR823_TNet : public CDialog
{
// Construction
public:
	CR823_TNet(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
    CDlgconfigure mConfigure;

	enum { IDD = IDD_DIALOG_NET };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Active on the Dialog
private:
    void OnOK();
    void OnCancel();
}