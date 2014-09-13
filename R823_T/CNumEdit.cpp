#include "CNumEdit.h"
/*
CNumEdit::CNumEdit(CWnd* pParent)
{

}*/

BEGIN_MESSAGE_MAP(CNumEdit, CEdit)
    //{{AFX_MSG_MAP(CNumEdit)
    ON_WM_CHAR()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CNumEdit::OnChar( UINT nChar, UINT nRepCnt, UINT nFlags )
{
    // TODO: Add your message handler code here and/or call default
    CString ss;
    char ch = char(nChar);
    GetWindowText(ss);

    if(!isdigit(ch))
    {
        if(ch == '.')
        {
            if(ss.Find('.') != -1)
            return;
        }
        else
        {
            if(ch == '/b')
            {
            ; 
            }
            else if (ch == 0x08)
            {
                ss.Delete(ss.GetLength()-1);
            }
            else
                return;
        }
    }
    CEdit::OnChar(nChar, nRepCnt, nFlags);
}