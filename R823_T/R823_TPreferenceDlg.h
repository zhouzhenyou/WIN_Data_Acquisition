// R823_TPreferenceDlg.h : header file
//

#pragma once

#include "stdafx.h"
#include "Resource.h"
#include "Resource_Strings.h"
#include "CDlgconfigure.h"
#include "CNumEdit.h"

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
class CR823_TPreferenceDlg : public CDialog
{
// Construction
public:
	CR823_TPreferenceDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
    CDlgconfigure mConfigure;

	enum { IDD = IDD_R823_T_DIALOG_PREFERENCE };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Active on the Dialog
private:
    CStatic m_frequence_cap;
    CStatic m_velocity_cap;
    CStatic m_project_cap;
    CStatic m_size;
    CStatic m_sensior;
    CStatic m_id;
    CStatic m_filter;
    CStatic m_tiny_cap;
    CStatic m_huge_cap;
    CStatic m_mid_cap;
    CStatic m_tiny_II_cap;
    CStatic m_huge_II_cap;
    CStatic m_mid_II_cap;
    CStatic m_tiny_III_cap;
    CStatic m_huge_III_cap;
    CStatic m_mid_III_cap;
    CStatic m_iron_tramp_I_cap;
    CStatic m_iron_tramp_II_cap;
    CStatic m_iron_tramp_III_cap;
    CStatic m_distance_cap;

    CStatic m_frequence_item;
    CStatic m_velocity_item;
    CStatic m_project_item;
    CStatic m_size_item;
    CStatic m_sensior_item;
    CStatic m_id_item;
    CStatic m_filter_item;
    CStatic m_dis_item;

    CStatic m_group;
    CStatic m_group_tiny;
    CStatic m_group_mid;
    CStatic m_group_huge;
    CStatic m_group_iron;

    CString mFrequence;
    CString mVelocity;
    CString mProjectName;
    CString mSize;
    CString mSensior;
    CString mID;
    CString mFilter;
    CString mTinyDeficiency;
    CString mMidDeficiency;
    CString mHugeDeficiency;

    CString mTinyDeficiencyB;
    CString mMidDeficiencyB;
    CString mHugeDeficiencyB;

    CString mTinyDeficiencyC;
    CString mMidDeficiencyC;
    CString mHugeDeficiencyC;

    CString mIronTramp;
    CString mIronTrampB;
    CString mIronTrampC;

    CString mDistance;

    int m_iClientWidth;
    int m_iClientHeight;
    int m_iClientWidthGap;
    int m_iClientHeightGap;

    CRect m_button_zone;
    CRect m_own_logo;
    CRect m_subscriber_logo;
    CRect m_list_upper;
    CRect m_list_low;

    CNumEdit mVelocityInput;
    CNumEdit mFrequencyInput;
    CNumEdit mTinyInput;
    CNumEdit mMidInput;
    CNumEdit mHugeInput;
    CNumEdit mTinyInput2;
    CNumEdit mMidInput2;
    CNumEdit mHugeInput2;
    CNumEdit mTinyInput3;
    CNumEdit mMidInput3;
    CNumEdit mHugeInput3;
    CNumEdit mSeniorInput;
    CNumEdit mDistanceInput;
    
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
    virtual void OnOK();
    virtual void OnCancel();
};
