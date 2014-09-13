#include "R823_TExport.h"
#include "R832ImgFile.h"

CR823_TExport::CR823_TExport(CWnd* pParent /*=NULL*/)
: CDialog(CR823_TExport::IDD, pParent)
{
    mExportSetting = 0xFFFF;
    wchar_t tmpWChar[MAX_PATH] = {0};
    char tmpChar[MAX_PATH] = {0};
    GetCurrentDirectory(MAX_PATH, tmpWChar);
    WideCharToMultiByte(CP_ACP, 0, tmpWChar, -1, tmpChar, sizeof(tmpChar), NULL, NULL);
    m_spath.Format(_T("%s"), tmpWChar);
    strcat(tmpChar, ID_IMAGE);
    if (access(tmpChar, 0) != 0)
    {
        mkdir(tmpChar);
    }
    
    /*
    //Store picture
    FILE *fp = fopen("E:\\Workspace\\R823_T\\12.bmp","rb+");
    fseek(fp, 0, SEEK_END);
    int len = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    int count = len/FILE_MAX_BYTE;
    count += (len%FILE_MAX_BYTE)?1:0;
    ImgFile target("E:\\Workspace\\R823_T\\imgs.rsv",GSFile::Write);
    img_record_item tmp_item;
    tmp_item.record_len = len;
    tmp_item.img_id = ID_IMAGE_SUBSCRIBER;//ID_IMAGE_SUBSCRIBER
    tmp_item.record_sum_count = 2;
    target.WriteRecordHeader(&tmp_item, sizeof(img_record_item));
    unsigned char byte[FILE_MAX_BYTE];
    int byte_count = 0; 
    for (int i = 0; i < count; i++)
    {
        byte_count = fread(byte, 1, FILE_MAX_BYTE, fp);
        target.WriteRecord(byte, byte_count);
    }
    fclose(fp);
    target.Done();
    */

}


BEGIN_MESSAGE_MAP(CR823_TExport, CDialog)
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(ID_EXPORT_OK, &CR823_TExport::OnOK)
    ON_BN_CLICKED(ID_EXPORT_FAILED, &CR823_TExport::OnCancel)
    ON_BN_CLICKED(IDC_BROWSER, &CR823_TExport::OnBnClickedBrowser)
END_MESSAGE_MAP()

static void WINAPI FunProc(LPVOID lpParameter)
{
    CR823_TExport *pThis = (CR823_TExport*)lpParameter;
    pThis->InitExcel();
}

void CR823_TExport::InitExcel()
{
    
}

void CR823_TExport::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    
    DDX_Control(pDX, IDC_EXPORT_GROUP, m_export_group);
    DDX_Control(pDX, IDC_CHECK_SERIAL, m_serial);
    DDX_Control(pDX, IDC_CHECK_TINY, m_tiny_def);
    DDX_Control(pDX, IDC_CHECK_MID, m_mid_def);
    DDX_Control(pDX, IDC_CHECK_HUGE, m_huge_def);
    DDX_Control(pDX, IDC_CHECK_RANGE, m_range);
    DDX_Control(pDX, IDC_CHECK_VOL, m_vol);
    DDX_Control(pDX, IDC_BROWSER, m_browser);
    DDX_Control(pDX, IDC_PATH_STATIC, m_path);
    DDX_Control(pDX, IDC_CHECK_IRON, m_iron);
}

BOOL CR823_TExport::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_export_group.SetWindowText(ID_EXPORT_GROUP);
    m_serial.SetWindowText(ID_TABLE_SEQID);
    m_tiny_def.SetWindowText(ID_TABLE_TINY_DEFICIENCY);
    m_mid_def.SetWindowText(ID_TABLE_MID_DEFICIENCY);
    m_huge_def.SetWindowText(ID_TABLE_HUGE_DEFICIENCY);
    m_range.SetWindowText(ID_TABLE_RANGE);
    m_vol.SetWindowText(ID_TABLE_VOL_IDENTIFICATION);
    m_browser.SetWindowText(ID_EXPORT_BROWSER);
    m_iron.SetWindowText(ID_TABLE_IRON_TRAMP);
    m_path.SetWindowText(m_spath);

    m_serial.SetCheck(mExportSetting & ID_EXPORT_ID_CHECKED);
    m_tiny_def.SetCheck(mExportSetting & ID_EXPORT_TINY_CHECKED);
    m_mid_def.SetCheck(mExportSetting & ID_EXPORT_MID_CHECKED);
    m_huge_def.SetCheck(mExportSetting & ID_EXPORT_HUGE_CHECKED);
    m_range.SetCheck(mExportSetting & ID_EXPORT_RANGE_CHECKED);
    m_vol.SetCheck(mExportSetting & ID_EXPORT_VOL_CHECKED);
    m_iron.SetCheck(mExportSetting & ID_EXPORT_IRON_CHECKED);

    this->SetWindowText(ID_EXPORT_CAP);
    m_path.SetWindowText(m_spath);
    //HANDLE hThread;

    // hThread=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)FunProc,(LPVOID)this,0,NULL);
     //CloseHandle(hThread);

    return TRUE;
}

void CR823_TExport::OnOK()
{
    mExportSetting = 0xFFFF;
    if (m_serial.GetCheck() == 0)
    {
        mExportSetting &= (~ID_EXPORT_ID_CHECKED);
    }

    if (m_tiny_def.GetCheck() == 0)
    {
        mExportSetting &= (~ID_EXPORT_TINY_CHECKED);
    }

    if (m_mid_def.GetCheck() == 0)
    {
        mExportSetting &= (~ID_EXPORT_MID_CHECKED);
    }

    if (m_huge_def.GetCheck() == 0)
    {
        mExportSetting &= (~ID_EXPORT_HUGE_CHECKED);
    }

    if (m_range.GetCheck() == 0)
    {
        mExportSetting &= (~ID_EXPORT_RANGE_CHECKED);
    }

    if (m_vol.GetCheck() == 0)
    {
        mExportSetting &= (~ID_EXPORT_VOL_CHECKED);
    }

    if (m_iron.GetCheck() == 0)
    {
        mExportSetting &= (~ID_EXPORT_IRON_CHECKED);
    }

    CDialog::OnOK();

    //PostQuitMessage(0);

}

void CR823_TExport::OnCancel()
{
    // TODO: Add your control notification handler code here
    CDialog::OnCancel();
}

void CR823_TExport::OnBnClickedBrowser()
{  
    CFileDialog FileDialog(FALSE, _T("xls"), NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, _T("Microsoft Excel 2007(*.xls)|*.xls|所有文件(*.*)"), this);   
    if(FileDialog.DoModal() != IDOK)   
    {  
        return;   
    }

    m_spath = FileDialog.GetPathName();
    m_path.SetWindowText(m_spath);
}

DWORD CR823_TExport::GetExportSetting()
{
    return mExportSetting;
}

CString CR823_TExport::GetExportPath()
{
    return m_spath;
}

void CR823_TExport::SetExportSetting(DWORD arg)
{
    mExportSetting = arg;
}

void CR823_TExport::SetExportPath(CString arg)
{
    m_spath = arg;
}