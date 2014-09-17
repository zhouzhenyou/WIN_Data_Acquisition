#include "R823_TNet.h"

CR823_TNet::CR823_TNet(CWnd* pParent)
 : CDialog(CR823_TNet::IDD, pParent)
{

}

BEGIN_MESSAGE_MAP(CR823_TNet, CDialog)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(ID_NET_OK, &CR823_TNet::OnOK)
    ON_BN_CLICKED(ID_NET_CANCEL, &CR823_TNet::OnCancel)
END_MESSAGE_MAP()

void CR823_TNet::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_ip, mIp);
    DDX_Text(pDX, IDC_EDIT_USERNAME, mUsername);
    DDX_Text(pDX, IDC_EDIT_PASSWORD, mPassword);
    DDX_Text(pDX, IDC_EDIT_FOLDER, mFolder);

    DDX_Control(pDX,IDC_EDIT_ip, m_edit_ip);
    DDX_Control(pDX,IDC_EDIT_USERNAME, m_edit_username);
    DDX_Control(pDX,IDC_EDIT_PASSWORD, m_edit_password);
    DDX_Control(pDX,IDC_EDIT_FOLDER, m_edit_folder);
}

BOOL CR823_TNet::OnInitDialog()
{
    return CDialog::OnInitDialog();;
}

void CR823_TNet::OnOK()
{
    UpdateData(TRUE);
    CDialog::OnOK();
}

void CR823_TNet::OnCancel()
{
    CDialog::OnCancel();
}