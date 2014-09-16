#include "R823_TNet.h"

CR823_TNet::CR823_TNet((CWnd* pParent)
 : CDialog(CR823_TNet::IDD, pParent)
{

}

BEGIN_MESSAGE_MAP(CR823_TExport, CDialog)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(ID_NET_OK, &CR823_TNet::OnOK)
    ON_BN_CLICKED(ID_NET_CANCEL, &CR823_TNet::OnCancel)
END_MESSAGE_MAP()

