// R823_TPreferenceDlg.h : header file
//

#pragma once

#include "stdafx.h"
#include "Resource.h"
#include "Resource_Strings.h"
#include "CDlgconfigure.h"
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

//#define ID_EXPORT_TABLE_SEQID_WIDTH             0.1
//#define ID_EXPORT_TABLE_OTHERS_WIDTH            0.9/5

#define ID_TABLE_SUM_WIDTH                      0.25
#define ID_TABLE_SUM_COLUMN_COUNT               2

// CR823_TDlg dialog
class CR823_TExport : public CDialog
{
// Construction
public:
	CR823_TExport(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
    CDlgconfigure mConfigure;

	enum { IDD = IDD_R823_T_DIALOG_EXPORT };
    void InitExcel();

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Active on the Dialog
private:
    CStatic m_export_group;
    CStatic m_path;
    CButton m_browser;
    CButton m_serial;
    CButton m_tiny_def;
    CButton m_mid_def;
    CButton m_huge_def;
    CButton m_range;
    CButton m_vol;
    CButton m_iron;

    CString m_spath;
    CString mVelocity;
    CString mProjectName;
    CString mSize;
    CString mSensior;
    CString mID;
    CString mFilter;
    
    CExcel mExcel;
    DWORD mExportSetting;
    CString m_ExportPath;
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
    virtual void OnOK();
    virtual void OnCancel();
    afx_msg void OnBnClickedBrowser();
    DWORD GetExportSetting();
    CString GetExportPath();
    void SetExportSetting(DWORD arg);
    void SetExportPath(CString arg);
};
