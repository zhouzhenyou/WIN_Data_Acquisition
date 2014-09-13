#ifndef _CNUMEDIT_H_
#define _CNUMEDIT_H_

#include "stdafx.h"

class CNumEdit :public CEdit
{
public:
    //CNumEdit(CWnd* pParent);
    
private:
    int m_nLength;
    int m_nDec;
   
protected:
    //{{AFX_MSG(CNumEdit)
        afx_msg void OnChar( UINT nChar, UINT nRepCnt, UINT nFlags );
    //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
};

#endif 