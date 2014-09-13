// R823_TPreferenceDlg.h : header file
//

#pragma once

#include "stdafx.h"
#include "Resource.h"
#include "Resource_Strings.h"
#include "CDlgconfigure.h"
#include "ColumnColorListCtrl.h"
#include "R832File.h"
#include "CExcel.h"

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
#define ID_TABLE_OTHERS_WIDTH                   0.9/5

#define ID_TABLE_SUM_WIDTH                      0.25
#define ID_TABLE_SUM_COLUMN_COUNT               2

// CR823_TDlg dialog
class CR823_TQuery : public CDialog
{
// Construction
public:
	CR823_TQuery(CWnd* pParent = NULL);	// standard constructor
    ~CR823_TQuery();
// Dialog Data

	enum { IDD = IDD_R823_T_DIALOG_QUERY };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
    void SetVisible(BOOL isVisible);
    void AddCurrentProject(CList<record_item, record_item&> arg);

// Active on the Dialog
private:

    CString mSelectEntry;
    CString mVelocity;
    CString mProjectName;
    CString mSize;
    CString mSensior;
    CString mID;
    CString mFilter;
    CButton m_export;

// Implementation
protected:
	HICON m_hIcon;
    //GSFile wtarget;
    CDlgconfigure mConfigure;
    int line;
    int currentItem;
    int m_ExportSetting;

    CStatic m_select;
    CComboBox  m_record;
    CStatic m_static_content;
    CComboBox m_entry;
    CLineColorListCtrl m_table_content;
    CExcel mExcel;
    CString m_spath;
    CStringList list;

	// Generated message map functions
	virtual BOOL OnInitDialog();
    void OnOK();
    void OnCancel();
    virtual void onSelect();
    virtual void onExport();
    virtual void onFirstSelect();
	DECLARE_MESSAGE_MAP()
public:
    void setConfig(CDlgconfigure arg);
    void SetExportPath(CString arg);
    void SetExportSetting(int arg);
    afx_msg void OnCbnSelchangeComboRecord();
    afx_msg void OnCbnSelendokComboContent();
    afx_msg void OnBnClickedButtonExport();
    void FindFiles(wchar_t* arg);
};
