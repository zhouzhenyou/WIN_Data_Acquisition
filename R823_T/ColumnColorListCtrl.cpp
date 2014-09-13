
#include "ColumnColorListCtrl.h"


CLineColorListCtrl::CLineColorListCtrl()  
{
    isItemRedraw = TRUE;
    m_itemHeight = 15;

    m_Column_count = 0;
    m_Row_colunt = 0;
}  
  
CLineColorListCtrl::~CLineColorListCtrl()  
{  
}  
  
  
BEGIN_MESSAGE_MAP(CLineColorListCtrl, CListCtrl)  
    //{{AFX_MSG_MAP(CLineColorListCtrl)  
        // NOTE - the ClassWizard will add and remove mapping macros here.  
    //}}AFX_MSG_MAP  
    ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnNMCustomdraw) 
    ON_WM_MEASUREITEM_REFLECT()
    ON_WM_MEASUREITEM()
    ON_WM_DRAWITEM()
END_MESSAGE_MAP()  
  
/////////////////////////////////////////////////////////////////////////////  
// CLineColorListCtrl message handlers  
 
// Assemble the row and column into a hash key
DWORD accurateHashKey(DWORD nItem,DWORD nSubItem)
{
    DWORD ret = 0;
    ret = ret | (nItem << 16) | nSubItem; 
    return ret;
}
  
void CLineColorListCtrl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)    
{    
    // TODO: Add your control notification handler code here
    *pResult = CDRF_DODEFAULT;    
    NMLVCUSTOMDRAW * lplvdr=(NMLVCUSTOMDRAW*)pNMHDR;    
    NMCUSTOMDRAW &nmcd = lplvdr->nmcd;    
    switch(lplvdr->nmcd.dwDrawStage)//判断状态     
    {    
    case CDDS_PREPAINT:    
        {    
            *pResult = CDRF_NOTIFYITEMDRAW;    
            break;    
        }    
    case CDDS_ITEMPREPAINT://如果为画ITEM之前就要进行颜色的改变     
        {     
            TEXT_BK tb;
            if (!isItemRedraw)
            {
                *pResult = CDRF_NOTIFYSUBITEMDRAW;
            }
            else
            {
                if (MapItemColor.Lookup(nmcd.dwItemSpec,tb))
                {
                    lplvdr->clrTextBk = tb.colTextBk;
                    lplvdr->clrText = tb.colText;                
                }
                *pResult = CDRF_DODEFAULT;
            }
        }
        break;
    case CDDS_ITEMPREPAINT | CDDS_SUBITEM:
        {
            TEXT_BK tb;
            //if (MapColumnColor.Lookup((DWORD_PTR)&(lplvdr->iSubItem),tb))
            DWORD iColumn = lplvdr->iSubItem;
            DWORD iItem = nmcd.dwItemSpec;
            DWORD key_target = (iItem << 16)| iColumn;
            if (MapColumnColor.Lookup(key_target, tb))
            {
                lplvdr->clrTextBk = tb.colTextBk;
                lplvdr->clrText = tb.colText;
            }
            else
            {
                if (MapColumnColor.Lookup(iColumn, tb))
                {
                    lplvdr->clrTextBk = tb.colTextBk;
                    lplvdr->clrText = tb.colText;
                }
                else
                {
                    lplvdr->clrTextBk = RGB(255,255,255);
                    lplvdr->clrText = RGB(0,0,0);            
                }
            }
            *pResult = CDRF_DODEFAULT;
            break;
        }
    }  
}    
  
void CLineColorListCtrl::ClearColor()  
{  
    MapItemColor.RemoveAll();  
}  
  
void CLineColorListCtrl::SetItemColor(DWORD iItem, COLORREF TextColor, COLORREF TextBkColor)  
{    
    TEXT_BK tb;  
    tb.colText = TextColor;  
    tb.colTextBk = TextBkColor;  
    isItemRedraw = TRUE;

    MapItemColor.SetAt(iItem, tb);//设置某行的颜色。     
    this->RedrawItems(iItem, iItem);//重新染色 
    //this->SetCheck(iItem,1);     
    this->SetFocus();    //设置焦点     
    //UpdateWindow();      
}    
  
void CLineColorListCtrl::SetColumnColor(DWORD iColumn,  COLORREF TextColor, COLORREF TextBkColor)
{
    TEXT_BK tb;  
    tb.colText = TextColor;  
    tb.colTextBk = TextBkColor;
    isItemRedraw = FALSE;

    MapColumnColor.SetAt(iColumn, tb);
    this->RedrawItems(0, 0);//GetItemCount()
    this->SetFocus();
    //UpdateWindow();
}

void CLineColorListCtrl::SetEntyColor(DWORD iItem, DWORD iColumn,  COLORREF TextColor, COLORREF TextBkColor)
{
    TEXT_BK tb;  
    tb.colText = TextColor;  
    tb.colTextBk = TextBkColor;
    isItemRedraw = FALSE;

    DWORD key = (iItem << 16) | iColumn;
    MapColumnColor.SetAt(key, tb);
    this->RedrawItems(0, 0);//GetItemCount()
    this->SetFocus();
    //UpdateWindow();
}

void CLineColorListCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
    // Get the LOGFONT for the current font.
    lpMeasureItemStruct->itemHeight = m_itemHeight;
}

void CLineColorListCtrl::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
 
    CListCtrl::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

void CLineColorListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
    //CListCtrl::DrawItem(lpDrawItemStruct)
    TCHAR  lpBuffer[256];
 
    LV_ITEM lvi;
 
    lvi.mask = LVIF_TEXT | LVIF_PARAM ;
    lvi.iItem = lpDrawItemStruct->itemID ;     
    lvi.iSubItem = 0;
    lvi.pszText = lpBuffer ;
    lvi.cchTextMax = sizeof(lpBuffer);
    VERIFY(GetItem(&lvi));
 
    LV_COLUMN lvc, lvcprev ;
    ::ZeroMemory(&lvc, sizeof(lvc));
    ::ZeroMemory(&lvcprev, sizeof(lvcprev));
    lvc.mask = LVCF_WIDTH | LVCF_FMT;
    lvcprev.mask = LVCF_WIDTH | LVCF_FMT;

    for ( int nCol=0; GetColumn(nCol, &lvc); nCol++)
    {
        if ( nCol > 0 ) 
        {
            // Get Previous Column Width in order to move the next display item
            GetColumn(nCol-1, &lvcprev) ;
            lpDrawItemStruct->rcItem.left += lvcprev.cx ;
            lpDrawItemStruct->rcItem.right += lpDrawItemStruct->rcItem.left ;    
        }
 
        // Get the text 
        ::ZeroMemory(&lvi, sizeof(lvi));
        lvi.iItem = lpDrawItemStruct->itemID;
        lvi.mask = LVIF_TEXT | LVIF_PARAM;
        lvi.iSubItem = nCol;
        lvi.pszText = lpBuffer;
        lvi.cchTextMax = sizeof(lpBuffer);
        VERIFY(GetItem(&lvi));
 
        CDC* pDC;
        pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
 
        if ( lpDrawItemStruct->itemState & ODS_SELECTED )
        {
            pDC->FillSolidRect(&lpDrawItemStruct->rcItem, GetSysColor(COLOR_HIGHLIGHT)) ; 
            pDC->SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT)) ;
        }
        else
        {
            pDC->FillSolidRect(&lpDrawItemStruct->rcItem, GetSysColor(COLOR_WINDOW)) ;
            pDC->SetTextColor(GetSysColor(COLOR_WINDOWTEXT)) ; 
        }
         
        pDC->SelectObject(GetStockObject(DEFAULT_GUI_FONT));
 
        UINT        uFormat    = DT_LEFT ;
 
        ::DrawText(lpDrawItemStruct->hDC, lpBuffer, _tcslen(lpBuffer), 
             &lpDrawItemStruct->rcItem, uFormat) ;
 
        pDC->SelectStockObject(SYSTEM_FONT) ;
    }
}

void CLineColorListCtrl::SetItemHeight(DWORD arg)
{
    m_itemHeight = arg;
    CRect rcWin;
    GetWindowRect(&rcWin);
    WINDOWPOS wp;
    wp.hwnd = m_hWnd;
    wp.cx = rcWin.Width();
    wp.cy = rcWin.Height();
    wp.flags = SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER;
    SendMessage(WM_WINDOWPOSCHANGED, 0, (LPARAM)&wp);
}

int CLineColorListCtrl::GetColumnCount()
{
    return m_Column_count;
}

void CLineColorListCtrl::SetColumnCount(int arg)
{
    m_Column_count = arg;
}

int CLineColorListCtrl::GetRowCount()
{
    return m_Row_colunt;
}

void CLineColorListCtrl::SetRowCount(int arg)
{
    m_Row_colunt = arg;
}

void CLineColorListCtrl::AddColumnCount()
{
    m_Column_count++;
}

void CLineColorListCtrl::AddRowCount()
{
    m_Row_colunt++;
}