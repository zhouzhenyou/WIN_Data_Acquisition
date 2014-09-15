// R823_TDlg.h : header file
//

#pragma once

#include "ColumnColorListCtrl.h"
#include "CDevice.h"
#include "R823_TPreferenceDlg.h"
#include "R823_TVolQuery.h"
#include "R823_TVolDetailQuery.h"
#include "R823_TExport.h"
#include "R832File.h"
#include "CNet.h"

#define ID_BUTTON_BORDER_PERCENT                0.04
#define ID_BUTTON_WIDTH_GAP_PERCENT             0.025
#define ID_BUTTON_HEIGHT_GAP_PERCENT            0.05
#define ID_BUTTON_WIDTH_PERCENT                 0.2
#define ID_BUTTON_HEIGHT_PERCENT                0.7
#define ID_BUTTON_ROW_COUNT                     5
#define ID_BUTTON_INNER_GAP_PERCENT             0.09

#define ID_LOGO_WIDTH_PERCENT                   0.19
#define ID_LOGO_WIDTH_GAP_PERCENT               0.05

#define ID_TABLE_SEQID_WIDTH                    0.1
#define ID_TABLE_OTHERS_NUMBER                  6
#define ID_TABLE_OTHERS_WIDTH                   0.9/ID_TABLE_OTHERS_NUMBER

#define ID_TABLE_SUM_WIDTH                      0.25
#define ID_TABLE_SUM_COLUMN_COUNT               2

#define ID_TABLE_SUM_COLUMN_A                   1
#define ID_TABLE_SUM_COLUMN_B                   ID_TABLE_SUM_COLUMN_A+2
#define ID_TABLE_SUM_ROW_COUNT                  6

#define ID_TABLE_CONTENT_NUMBER                 13
#define ID_TABLE_CONTENT_FONT_SIZE              8


#define ID_MAX_LINE                             100
#define WM_USERMESSAGE                          WM_USER+30

#define ID_EMPTY                                0
#define ID_TINY_DEFICIENCY                      1
#define ID_MID_DEFICIENCY                       2
#define ID_HIGH_DEFICIENCY                      3

#define ID_FONT_SIZE                            5
// CR823_TDlg dialog
class CR823_TDlg : public CDialog
{
// Construction
public:
	CR823_TDlg(CWnd* pParent = NULL);	// standard constructor
    ~CR823_TDlg();

// Dialog Data
	enum { IDD = IDD_R823_T_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Active on the Dialog
private:
    CButton m_preferences;
    CButton m_volInq;
    CButton m_export;
    CButton m_volDetailInq;
    CButton m_quit;
    CLineColorListCtrl m_table_content;
    CLineColorListCtrl m_table_sum;
    CStatic m_test;

    int m_iClientWidth;
    int m_iClientHeight;
    int m_iClientWidthGap;
    int m_iClientHeightGap;

    CRect m_button_zone;
    CRect m_own_logo;
    CRect m_subscriber_logo;
    CRect m_list_upper;
    CRect m_list_low;
    CRect rectClient;

    int lineF;
    int lineS;
    int lineth;
    int linefou;
    int linefive;
    int linesix;

    CList<record_item, record_item&> CDWORDList;
    CDevice *m_pDevice;
    CNet *m_pNet;
    
    CR823_TPreferenceDlg m_setting_dlg;
    CR823_TVolQuery m_query_dlg;
    CR823_TVolDetailQuery m_query_detail_dlg;
    CR823_TExport m_export_dlg;

    int currentItem;
    int subvol;
    int sum_count_old;
    int line;
    int m_DlgItem[100];
    int mDlgItemCount;
    
    wchar_t wchpath[MAX_PATH];
    char chpath[MAX_PATH];
    char chconf[MAX_PATH];
    char chperference[MAX_PATH];
    char imgVendorPath[MAX_PATH];
    wchar_t wImgVendorPath[MAX_PATH];
    char imgSubPath[MAX_PATH];
    wchar_t wImgSubPath[MAX_PATH];

    GSFile *m_backup;;
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
    afx_msg void OnSize(UINT nType, int cx, int cy); 
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButton1();
    afx_msg void OnBnClickedButtonBasicSetting();
    afx_msg void OnBnClickedButtonVolInq();
    afx_msg void OnBnClickedExport();
    afx_msg void OnBnClickedVolDetail();
    afx_msg void OnBnClickedQuit();
    afx_msg void OnClose();
    afx_msg void OnLvnItemchangedTableSum(NMHDR *pNMHDR, LRESULT *pResult);
    
    afx_msg LRESULT OnTinyDeficiency(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnMidDeficiency(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnHugeyDeficiency(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnIronDeficiency(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnEntireDeficiency(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT onStoreClear(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT onDeviceError(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT onAddItem(WPARAM wParam, LPARAM lParam);

    void AddItem(int tiny, int huge, int mid, int iron, int range);
    void addIronDeficiency(int arg);
    void addMidDeficiency(int arg);
    void addTinyDeficiency(int arg);
    void addHugeDeficiency(int arg);
    void SetSummaryText(int row,int column,CString arg);
    void CheckRange(record_item arg);
    void test();
    void StorePreference();
    void RestorePreference();
    void ChartoWchar(char* src, wchar_t* des);
    void FindFiles(wchar_t* arg);

private:
    void SetImageSection(int arg, void* wParam);
    void SetRangeColor(record_item arg, int arg_priority);
    void SetPreferenceFromFile(void* para);
    void RefreshSummaryTable();
};
