#include "R823_TQuery.h"

CR823_TQuery::CR823_TQuery(CWnd* pParent /*=NULL*/)
: CDialog(CR823_TQuery::IDD, pParent)
{
    line = 0;
    currentItem = 0;
}

CR823_TQuery::~CR823_TQuery()
{

}

BEGIN_MESSAGE_MAP(CR823_TQuery, CDialog)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(ID_QUERY_OK, &CR823_TQuery::OnOK)
    ON_BN_CLICKED(ID_QUERY_FAILED, &CR823_TQuery::OnCancel)
    ON_CBN_SELCHANGE(IDC_COMBO_RECORD, &CR823_TQuery::OnCbnSelchangeComboRecord)
    ON_CBN_SELENDOK(IDC_COMBO_CONTENT, &CR823_TQuery::OnCbnSelendokComboContent)
    ON_BN_CLICKED(ID_BUTTON_EXPORT, &CR823_TQuery::OnBnClickedButtonExport)
END_MESSAGE_MAP()


void CR823_TQuery::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    
    DDX_Control(pDX, IDC_STATIC_SELECT, m_select);
    DDX_Control(pDX, IDC_STATIC_RECORD, m_static_content);
    DDX_Control(pDX, IDC_LIST_CONTENT, m_table_content);
    DDX_Control(pDX, IDC_COMBO_RECORD, m_record);
    DDX_Control(pDX, IDC_COMBO_CONTENT, m_entry);
    DDX_Control(pDX, ID_BUTTON_EXPORT, m_export);

    DDX_Text(pDX, IDC_COMBO_RECORD, mSelectEntry);
    /*
    DDX_Text(pDX, IDC_SIZE_INPUT, mSize);
    DDX_Text(pDX, IDC_FREQUENCE_INPUT, mFrequence);
    DDX_Text(pDX, IDC_VELOCITY_INPUT, mVelocity);
    DDX_Text(pDX, IDC_SENSIOR_INPUT, mSensior);
    DDX_Text(pDX, IDC_FILTER_INPUT, mFilter);
    */
}

BOOL CR823_TQuery::OnInitDialog()
{ 
    CDialog::OnInitDialog();


    m_export.SetWindowText(ID_EXPORT_BUTTON);
    m_select.SetWindowText(ID_STATIC_QUERY_SELECT_ITEM);
    m_static_content.SetWindowText(ID_STATIC_QUERY_SELECT_RECORD);
    return TRUE;
}

void CR823_TQuery::OnOK()
{
    // TODO: Add your control notification handler code here
    /*
    UpdateData(TRUE);
    mConfigure.setFilter(mFilter);
    mConfigure.setFrequency(_tstof(mFrequence));
    mConfigure.setProjectName(mProjectName);
    mConfigure.setSensior(mSensior);
    mConfigure.setVelocity(_tstof(mFrequence));*/
    CDialog::OnOK();
    //wtarget.Done();
    //PostQuitMessage(0);

}

void CR823_TQuery::OnCancel()
{
    // TODO: Add your control notification handler code here
    CDialog::OnCancel();
}

void CR823_TQuery::SetVisible(BOOL isVisible)
{
}

void CR823_TQuery::OnCbnSelchangeComboRecord()
{
    // TODO: Add your control notification handler code here
    
    //m_record.GetWindowText(mSelectEntry);
    //m_static_content.SetWindowText(mSelectEntry);

    onFirstSelect();
}


void CR823_TQuery::AddCurrentProject(CList<record_item,record_item&> arg)
{    
    POSITION pos = arg.GetTailPosition();
    record_item tmp = arg.GetAt(pos);
    CString target;
    target.Format(_T("%s"), tmp.volume);
    m_record.AddString(target);
}

void CR823_TQuery::setConfig(CDlgconfigure arg)
{
    mConfigure = arg;
}

void CR823_TQuery::OnCbnSelendokComboContent()
{
    // TODO: Add your control notification handler code here
    onSelect();
}

void CR823_TQuery::onSelect()
{
    
}

void CR823_TQuery::onFirstSelect()
{

}

void CR823_TQuery::onExport()
{
    
}

void CR823_TQuery::SetExportPath(CString arg)
{
    m_spath = arg;
}

void CR823_TQuery::SetExportSetting(int arg)
{
    m_ExportSetting = arg;
}

void CR823_TQuery::OnBnClickedButtonExport()
{
    // TODO: Add your control notification handler code here
    onExport();
}

void CR823_TQuery::FindFiles(wchar_t* arg)
{ 
    HANDLE file; 
    CString strTmp, strFilePath, targetFilePath;
    CTime tm;
    tm = CTime::GetCurrentTime();
    strTmp.Empty();
    strFilePath.Empty();
    targetFilePath.Empty();
    strTmp = arg;
    strFilePath = arg;
    targetFilePath = arg;
    strFilePath += ID_FIND_SUFFIX;
    WIN32_FIND_DATA fileData;
    CString str;
    file = FindFirstFile(strFilePath, &fileData);
    BOOL res = TRUE;
    char tmppath[MAX_PATH];
    char tmpbuf[MAX_PATH];
    m_record.Clear();
    memset(tmpbuf, 0, MAX_PATH);
    memcpy(tmpbuf, mConfigure.getProjectName().GetBuffer(), mConfigure.getProjectName().GetLength()*sizeof(TCHAR));
    while(res)
    {
        memset(tmppath, 0, MAX_PATH);
        memset(tmpbuf, 0, MAX_PATH);
        strTmp.Empty();
        strTmp = arg;
        strTmp += _T("\\");
        strTmp += fileData.cFileName;
        WideCharToMultiByte(CP_ACP, 0, strTmp, -1, tmppath, sizeof(tmppath), NULL, NULL);
        GSFile tmpTarget(tmppath, GSFile::ReadOnly);
        if (tmpTarget.GetFileVersion() == FILE_SOURCE_TYPE)
        {
            record_item_header inner_header;
            memset(&inner_header, 0, sizeof(record_item_header));
            tmpTarget.ReadRecordHeader(&inner_header, sizeof(record_item_header));
            if ((memcmp(inner_header.volume, tmpbuf, MAX_PATH ) == 0) && (mConfigure.current_subvol == 1))
            {
                continue;
            }
            CString combox_tmp;
            combox_tmp.Format(_T("%s"), inner_header.volume);
            m_record.AddString(combox_tmp);
            list.AddTail(strTmp);
        }
        tmpTarget.Done();
        res = FindNextFile(file, &fileData);
    }
    m_record.SetCurSel(0);
}