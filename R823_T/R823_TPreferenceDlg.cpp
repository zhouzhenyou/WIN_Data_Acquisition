#include "R823_TPreferenceDlg.h"

CR823_TPreferenceDlg::CR823_TPreferenceDlg(CWnd* pParent /*=NULL*/)
: CDialog(CR823_TPreferenceDlg::IDD, pParent)
{

}


BEGIN_MESSAGE_MAP(CR823_TPreferenceDlg, CDialog)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(ID_SETTING_OK, &CR823_TPreferenceDlg::OnOK)
    ON_BN_CLICKED(ID_SETTING_CANCEL, &CR823_TPreferenceDlg::OnCancel)
END_MESSAGE_MAP()


void CR823_TPreferenceDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_PROJECT_STATIC, m_project_cap);
    DDX_Control(pDX, IDC_FREQUENCE_STATIC, m_frequence_cap);
    DDX_Control(pDX, IDC_SIZE_STATIC, m_size);
    DDX_Control(pDX, IDC_SENSIOR_STATIC, m_sensior);
    DDX_Control(pDX, IDC_ID_STATIC, m_id);
    DDX_Control(pDX, IDC_FILTER_STATIC, m_filter);
    DDX_Control(pDX, IDC_VELOCITY_STATIC, m_velocity_cap);
    DDX_Control(pDX, IDC_STATIC_TINY_DEFICIENCY, m_tiny_cap);
    DDX_Control(pDX, IDC_STATIC_MID_DEFICIENCY, m_mid_cap);
    DDX_Control(pDX, IDC_STATIC_HUGE_DEFICIENCY, m_huge_cap);
    DDX_Control(pDX, IDC_STATIC_TINY_DEFICIENCY2, m_tiny_II_cap);
    DDX_Control(pDX, IDC_STATIC_MID_DEFICIENCY2, m_mid_II_cap);
    DDX_Control(pDX, IDC_STATIC_HUGE_DEFICIENCY2, m_huge_II_cap);
    DDX_Control(pDX, IDC_STATIC_TINY_DEFICIENCY3, m_tiny_III_cap);
    DDX_Control(pDX, IDC_STATIC_MID_DEFICIENCY3, m_mid_III_cap);
    DDX_Control(pDX, IDC_STATIC_HUGE_DEFICIENCY3, m_huge_III_cap);
    DDX_Control(pDX, IDC_STATIC_IRON_TRAMP1, m_iron_tramp_I_cap);
    DDX_Control(pDX, IDC_STATIC_IRON_TRAMP2, m_iron_tramp_II_cap);
    DDX_Control(pDX, IDC_STATIC_IRON_TRAMP3, m_iron_tramp_III_cap);
    DDX_Control(pDX, IDC_STATIC_DISTANCE, m_distance_cap);

    DDX_Control(pDX, IDC_PROJECT_STATIC_ITEM, m_project_item);
    DDX_Control(pDX, IDC_FREQUENCE_STATIC_ITEM, m_frequence_item);
    DDX_Control(pDX, IDC_SIZE_STATIC_ITEM, m_size_item);
    DDX_Control(pDX, IDC_SENSIOR_STATIC_ITEM, m_sensior_item);
    DDX_Control(pDX, IDC_ID_STATIC_ITEM, m_id_item);
    DDX_Control(pDX, IDC_FILTER_STATIC_ITEM, m_filter_item);
    DDX_Control(pDX, IDC_VELOCITY_STATIC_ITEM, m_velocity_item);
    DDX_Control(pDX, IDC_DISTANCE_STATIC_ITEM, m_dis_item);
    DDX_Control(pDX, IDC_SETTING_GROUP, m_group);
    DDX_Control(pDX, IDC_STATIC_GROUP_TINY, m_group_tiny);
    DDX_Control(pDX, IDC_STATIC_GROUP_MID, m_group_mid);
    DDX_Control(pDX, IDC_STATIC_GROUP_HUGE, m_group_huge);
    DDX_Control(pDX, IDC_STATIC_GROUP_IRON_TRAMP, m_group_iron);

    DDX_Control(pDX, IDC_VELOCITY_INPUT, mVelocityInput);
    DDX_Control(pDX, IDC_FREQUENCE_INPUT, mFrequencyInput);
    DDX_Control(pDX, IDC_TINY_DEFICIENCY_INPUT, mTinyInput);
    DDX_Control(pDX, IDC_MID_DEFICIENCY_INPUT, mMidInput);
    DDX_Control(pDX, IDC_HUGE_DEFICIENCY_INPUT, mHugeInput);
    DDX_Control(pDX, IDC_TINY_DEFICIENCY_INPUT2, mTinyInput2);
    DDX_Control(pDX, IDC_MID_DEFICIENCY_INPUT2, mMidInput2);
    DDX_Control(pDX, IDC_HUGE_DEFICIENCY_INPUT2, mHugeInput2);
    DDX_Control(pDX, IDC_TINY_DEFICIENCY_INPUT3, mTinyInput3);
    DDX_Control(pDX, IDC_MID_DEFICIENCY_INPUT3, mMidInput3);
    DDX_Control(pDX, IDC_HUGE_DEFICIENCY_INPUT3, mHugeInput3);
    DDX_Control(pDX, IDC_SENSIOR_INPUT, mSeniorInput);
    DDX_Control(pDX, IDC_DISTANCE_INPUT, mDistanceInput);

    DDX_Text(pDX, IDC_PROJECTNAME_INPUT, mProjectName);
    DDX_Text(pDX, IDC_SIZE_INPUT, mSize);
    DDX_Text(pDX, IDC_FREQUENCE_INPUT, mFrequence);
    DDX_Text(pDX, IDC_VELOCITY_INPUT, mVelocity);
    DDX_Text(pDX, IDC_SENSIOR_INPUT, mSensior);
    DDX_Text(pDX, IDC_FILTER_INPUT, mFilter);
    DDX_Text(pDX, IDC_IDENTIFICATION_INPUT, mID);
    DDX_Text(pDX, IDC_TINY_DEFICIENCY_INPUT, mTinyDeficiency);
    DDX_Text(pDX, IDC_TINY_DEFICIENCY_INPUT2, mTinyDeficiencyB);
    DDX_Text(pDX, IDC_TINY_DEFICIENCY_INPUT3, mTinyDeficiencyC);
    DDX_Text(pDX, IDC_MID_DEFICIENCY_INPUT, mMidDeficiency);
    DDX_Text(pDX, IDC_MID_DEFICIENCY_INPUT2, mMidDeficiencyB);
    DDX_Text(pDX, IDC_MID_DEFICIENCY_INPUT3, mMidDeficiencyC);
    DDX_Text(pDX, IDC_HUGE_DEFICIENCY_INPUT, mHugeDeficiency);
    DDX_Text(pDX, IDC_HUGE_DEFICIENCY_INPUT2, mHugeDeficiencyB);
    DDX_Text(pDX, IDC_HUGE_DEFICIENCY_INPUT3, mHugeDeficiencyC);
    DDX_Text(pDX, IDC_IRON_TRAMP_INPUT, mIronTramp);
    DDX_Text(pDX, IDC_IRON_TRAMP_INPUT2, mIronTrampB);
    DDX_Text(pDX, IDC_IRON_TRAMP_INPUT3, mIronTrampC);

    DDX_Text(pDX, IDC_DISTANCE_INPUT, mDistance);
}

BOOL CR823_TPreferenceDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_project_cap.SetWindowText(ID_TABLE_PROJECT_NAME);
    m_frequence_cap.SetWindowText(ID_TABLE_FREQUENCE);
    m_size.SetWindowText(ID_TABLE_MATERIAL_SIZE);
    m_sensior.SetWindowText(ID_TABLE_SENSOR);
    m_id.SetWindowText(ID_TABLE_MATERIAL_IDENTIFICATION);
    m_filter.SetWindowText(ID_TABLE_WAVEFILTER);
    m_velocity_cap.SetWindowText(ID_TABLE_VELOCITY);
    m_tiny_cap.SetWindowText(ID_DEFIENCY_LEVER_A_CAP);
    m_mid_cap.SetWindowText(ID_DEFIENCY_LEVER_A_CAP);
    m_huge_cap.SetWindowText(ID_DEFIENCY_LEVER_A_CAP);
    m_distance_cap.SetWindowText(ID_DISTANCE_CAP);
    m_group_tiny.SetWindowText(ID_TINY_DEFICIENCY_CAP);
    m_group_mid.SetWindowText(ID_MID_DEFIENCY_CAP);
    m_group_huge.SetWindowText(ID_HUGE_DEFIENCY_CAP);
    m_group_iron.SetWindowText(ID_IRON_TRAMP_CAP);
    m_tiny_II_cap.SetWindowText(ID_DEFIENCY_LEVER_B_CAP);
    m_huge_II_cap.SetWindowText(ID_DEFIENCY_LEVER_B_CAP);
    m_mid_II_cap.SetWindowText(ID_DEFIENCY_LEVER_B_CAP);
    m_tiny_III_cap.SetWindowText(ID_DEFIENCY_LEVER_C_CAP);
    m_huge_III_cap.SetWindowText(ID_DEFIENCY_LEVER_C_CAP);
    m_mid_III_cap.SetWindowText(ID_DEFIENCY_LEVER_C_CAP);
    m_iron_tramp_I_cap.SetWindowText(ID_DEFIENCY_LEVER_A_CAP);
    m_iron_tramp_II_cap.SetWindowText(ID_DEFIENCY_LEVER_B_CAP);
    m_iron_tramp_III_cap.SetWindowText(ID_DEFIENCY_LEVER_C_CAP);

    m_project_item.SetWindowText(ID_TABLE_EMPTY);
    m_frequence_item.SetWindowText(ID_TABLE_FREQUENCY_ITEM);
    m_size_item.SetWindowText(ID_TABLE_SIZE_ITEM);
    m_sensior_item.SetWindowText(ID_TABLE_SENSOR_ITEM);
    m_id_item.SetWindowText(ID_TABLE_EMPTY);
    m_filter_item.SetWindowText(ID_TABLE_EMPTY);
    m_velocity_item.SetWindowText(ID_TABLE_VELOCITY_ITEM);
    m_dis_item.SetWindowText(ID_TABLE_DISTANCE_ITEM);
    m_group.SetWindowText(ID_BASIC_SETTING_CAP);

    this->SetWindowText(ID_BUTTON_BASIC_SETTING_CAP);

    mProjectName = mConfigure.getProjectName();
    mFrequence.Format(_T("%f"), mConfigure.getFrequency());
    mVelocity.Format(_T("%f"), mConfigure.getVelocity());
    mSize = mConfigure.getSize();
    mSensior = mConfigure.getSensior();
    mID = mConfigure.getMaterial();
    mFilter = mConfigure.getFilter();
    mTinyDeficiency.Format(_T("%d"), mConfigure.getTinyDeficiency());
    mTinyDeficiencyB.Format(_T("%d"), mConfigure.getTinyDeficiencyB());
    mTinyDeficiencyC.Format(_T("%d"), mConfigure.getTinyDeficiencyC());
    mMidDeficiency.Format(_T("%d"), mConfigure.getMidDeficiency());
    mMidDeficiencyB.Format(_T("%d"), mConfigure.getMidDeficiencyB());
    mMidDeficiencyC.Format(_T("%d"), mConfigure.getMidDeficiencyC());
    mHugeDeficiency.Format(_T("%d"), mConfigure.getHugeDeficiency());
    mHugeDeficiencyB.Format(_T("%d"), mConfigure.getHugeDeficiencyB());
    mHugeDeficiencyC.Format(_T("%d"), mConfigure.getHugeDeficiencyC());
    mIronTramp.Format(_T("%d"), mConfigure.getIronTramp());
    mIronTrampB.Format(_T("%d"), mConfigure.getIronTrampB());
    mIronTrampC.Format(_T("%d"), mConfigure.getIronTrampC());

    mDistance.Format(_T("%d"), mConfigure.getDistance());
    UpdateData(FALSE);
    return TRUE;
}

void CR823_TPreferenceDlg::OnOK()
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    mConfigure.setFilter(mFilter);
    mConfigure.setFrequency(_tstof(mFrequence));
    mConfigure.setProjectName(mProjectName);
    mConfigure.setSensior(mSensior);
    mConfigure.setVelocity(_tstof(mVelocity));
    mConfigure.setMaterial(mID);
    mConfigure.setSize(mSize);
    mConfigure.setTinyDeficiency(_tstoi(mTinyDeficiency));
    mConfigure.setTinyDeficiencyB(_tstoi(mTinyDeficiencyB));
    mConfigure.setTinyDeficiencyC(_tstoi(mTinyDeficiencyC));
    mConfigure.setMidDeficiency(_tstoi(mMidDeficiency));
    mConfigure.setMidDeficiencyB(_tstoi(mMidDeficiencyB));
    mConfigure.setMidDeficiencyC(_tstoi(mMidDeficiencyC));
    mConfigure.setHugeDeficiency(_tstoi(mHugeDeficiency));
    mConfigure.setHugeDeficiencyB(_tstoi(mHugeDeficiencyB));
    mConfigure.setHugeDeficiencyC(_tstoi(mHugeDeficiencyC));
    mConfigure.setIronTramp(_tstoi(mIronTramp));
    mConfigure.setIronTrampB(_tstoi(mIronTrampB));
    mConfigure.setIronTrampC(_tstoi(mIronTrampC));
    mConfigure.setDistance(_tstoi(mDistance));
    CDialog::OnOK();
    //PostQuitMessage(0);

}

void CR823_TPreferenceDlg::OnCancel()
{
    // TODO: Add your control notification handler code here
    CDialog::OnCancel();
}
