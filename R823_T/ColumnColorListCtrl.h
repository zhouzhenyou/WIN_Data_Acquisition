#ifndef CCOLORLISTCTRL_H_
#define CCOLORLISTCTRL_H_

#include "stdafx.h"

typedef struct    
{
    COLORREF colText;  
    COLORREF colTextBk;  
}TEXT_BK;

#define FULL_SELECT 0xFFFF0000

/////////////////////////////////////////////////////////////////////////////  
// CLineColorListCtrl window  
  
class CLineColorListCtrl : public CListCtrl  
{  
public:  
    void SetItemColor(DWORD iItem, COLORREF TextColor, COLORREF TextBkColor); 
    void SetColumnColor(DWORD iColumn,  COLORREF TextColor, COLORREF TextBkColor);
    void SetEntyColor(DWORD iItem, DWORD iColumn,  COLORREF TextColor, COLORREF TextBkColor);
    void SetItemHeight(DWORD arg);
    void ClearColor();

    int GetColumnCount();
    void SetColumnCount(int arg);
    void AddColumnCount();
    int GetRowCount();
    void SetRowCount(int arg);
    void AddRowCount();

    void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
    afx_msg void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
  
// Construction  
public:  
    CLineColorListCtrl();  
  
// Attributes  
public:  
    CMap<DWORD, DWORD&, TEXT_BK, TEXT_BK&> MapItemColor, MapColumnColor;

private:
    BOOL isItemRedraw;
    DWORD m_itemHeight;
    int m_Column_count;
    int m_Row_colunt;
  
// Operations  
public:  
  
// Overrides  
    // ClassWizard generated virtual function overrides  
    //{{AFX_VIRTUAL(CLineColorListCtrl)  
    //}}AFX_VIRTUAL  
  
// Implementation  
public:  
    virtual ~CLineColorListCtrl();  
  
    // Generated message map functions  
protected:  
    //{{AFX_MSG(CLineColorListCtrl)  
        // NOTE - the ClassWizard will add and remove member functions here.  
    //}}AFX_MSG  
    void CLineColorListCtrl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
    DECLARE_MESSAGE_MAP()  
};  


#endif
