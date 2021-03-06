// R823_TDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CExcel.h"
#include "R823_T.h"
#include "R823_TDlg.h"
#include "R832ImgFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CR823_TDlg dialog

CR823_TDlg::CR823_TDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CR823_TDlg::IDD, pParent)
{
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
    currentItem = 0;
    subvol = 0;
    sum_count_old = 0;
	line = 0;
    mDlgItemCount = 0;
    m_backup = NULL;
    m_DlgItem[mDlgItemCount++] = IDC_PIC_LEFT;
    m_DlgItem[mDlgItemCount++] = IDC_PIC_RIGHT;
    m_DlgItem[mDlgItemCount++] = IDC_TABLE_SUM;
    m_DlgItem[mDlgItemCount++] = IDC_TABLE_CONTENT;
    m_DlgItem[mDlgItemCount++] = IDC_BUTTON_BASIC_SETTING;
    m_DlgItem[mDlgItemCount++] = IDC_BUTTON_VOL_INQ;
    m_DlgItem[mDlgItemCount++] = ID_EXPORT;
    m_DlgItem[mDlgItemCount++] = ID_VOL_DETAIL;
    m_DlgItem[mDlgItemCount++] = ID_QUIT;
    memset(imgVendorPath, 0, MAX_PATH);
    memset(imgSubPath, 0, MAX_PATH);
    memset(wImgVendorPath, 0, MAX_PATH*sizeof(wchar_t));
    memset(wImgSubPath, 0, MAX_PATH*sizeof(wchar_t));
}

CR823_TDlg::~CR823_TDlg()
{
    if (m_pDevice != NULL)
    {
        m_pDevice->ClosePort();
    }
}

void CR823_TDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_BUTTON_BASIC_SETTING, m_preferences);
    DDX_Control(pDX, IDC_BUTTON_VOL_INQ, m_volInq);
    DDX_Control(pDX, ID_EXPORT, m_export);
    DDX_Control(pDX, ID_VOL_DETAIL, m_volDetailInq);
    DDX_Control(pDX, ID_QUIT, m_quit);
    DDX_Control(pDX, ID_VOL_DETAIL, m_volDetailInq);
    DDX_Control(pDX, ID_QUIT, m_quit);
    DDX_Control(pDX, IDC_BUTTON_NET, m_net);
    DDX_Control(pDX, IDC_TABLE_CONTENT, m_table_content);
    DDX_Control(pDX, IDC_TABLE_SUM, m_table_sum);
}

BEGIN_MESSAGE_MAP(CR823_TDlg, CDialog)
	ON_WM_PAINT()
    ON_WM_SIZE()
    ON_WM_CLOSE()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BUTTON_BASIC_SETTING, &CR823_TDlg::OnBnClickedButtonBasicSetting)
    ON_BN_CLICKED(IDC_BUTTON_VOL_INQ, &CR823_TDlg::OnBnClickedButtonVolInq)
    ON_BN_CLICKED(ID_EXPORT, &CR823_TDlg::OnBnClickedExport)
    ON_BN_CLICKED(ID_VOL_DETAIL, &CR823_TDlg::OnBnClickedVolDetail)
    ON_BN_CLICKED(ID_QUIT, &CR823_TDlg::OnBnClickedQuit)
    ON_MESSAGE(MSG_DISTANCE_BOUNDARY, OnEntireDeficiency)
    ON_MESSAGE(MSG_TINY_DEFICIENCY, OnTinyDeficiency)
    ON_MESSAGE(MSG_MID_DEFICIENCY, OnMidDeficiency)
    ON_MESSAGE(MSG_HUGE_DEFICIENCY, OnHugeyDeficiency)
    ON_MESSAGE(MSG_IRON_TRAMP, OnIronDeficiency)
	ON_MESSAGE(MSG_STORE_CLEAR, onStoreClear)
    ON_MESSAGE(MSG_DEVICE_NOT_FOUND, onDeviceError)
    ON_MESSAGE(MSG_NEW_ITEM, onAddItem)
    ON_BN_CLICKED(IDC_BUTTON_NET, &CR823_TDlg::OnBnClickedButtonNet)
END_MESSAGE_MAP()


// CR823_TDlg message handlers

BOOL CR823_TDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
    
	//SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
    SetWindowText(ID_APP_NAME);

    GetClientRect(rectClient);
    m_iClientWidth = rectClient.Width();
    m_iClientHeight = rectClient.Height();

    m_button_zone.SetRect(m_iClientWidth - ID_BUTTON_BORDER_PERCENT*m_iClientWidth - ID_BUTTON_WIDTH_PERCENT*m_iClientWidth*(1 - 2*ID_BUTTON_BORDER_PERCENT -ID_BUTTON_WIDTH_GAP_PERCENT),
        m_iClientHeight - ID_BUTTON_BORDER_PERCENT*m_iClientHeight - ID_BUTTON_HEIGHT_PERCENT*m_iClientHeight*(1 - 2*ID_BUTTON_BORDER_PERCENT -ID_BUTTON_HEIGHT_GAP_PERCENT),
        m_iClientWidth - ID_BUTTON_BORDER_PERCENT*m_iClientWidth,
        m_iClientHeight - ID_BUTTON_BORDER_PERCENT*m_iClientHeight
        );
    m_own_logo.SetRect(ID_BUTTON_BORDER_PERCENT*m_iClientWidth,
        ID_BUTTON_BORDER_PERCENT*m_iClientHeight,
        ID_BUTTON_BORDER_PERCENT*m_iClientWidth + ID_LOGO_WIDTH_PERCENT*m_iClientWidth*(1 - 2*ID_BUTTON_BORDER_PERCENT - ID_LOGO_WIDTH_GAP_PERCENT*2),
        ID_BUTTON_BORDER_PERCENT*m_iClientHeight + (1 - ID_BUTTON_HEIGHT_PERCENT)*m_iClientHeight*(1 - 2*ID_BUTTON_BORDER_PERCENT -ID_BUTTON_HEIGHT_GAP_PERCENT)
        );
    m_subscriber_logo.SetRect(m_iClientWidth - ID_BUTTON_BORDER_PERCENT*m_iClientWidth - ID_LOGO_WIDTH_PERCENT*m_iClientWidth*(1 - 2*ID_BUTTON_BORDER_PERCENT - ID_LOGO_WIDTH_GAP_PERCENT*2),
        ID_BUTTON_BORDER_PERCENT*m_iClientHeight,
        (1-ID_BUTTON_BORDER_PERCENT)*m_iClientWidth,
        ID_BUTTON_BORDER_PERCENT*m_iClientHeight + (1 - ID_BUTTON_HEIGHT_PERCENT)*m_iClientHeight*(1 - 2*ID_BUTTON_BORDER_PERCENT -ID_BUTTON_HEIGHT_GAP_PERCENT)
        );
    m_list_upper.SetRect(ID_BUTTON_BORDER_PERCENT*m_iClientWidth +  ID_LOGO_WIDTH_PERCENT*m_iClientWidth*(1 - 2*ID_BUTTON_BORDER_PERCENT - ID_LOGO_WIDTH_GAP_PERCENT*2) + ID_LOGO_WIDTH_GAP_PERCENT*m_iClientWidth,
        ID_BUTTON_BORDER_PERCENT*m_iClientHeight,
        (1-ID_BUTTON_BORDER_PERCENT)*m_iClientWidth - ID_LOGO_WIDTH_PERCENT*m_iClientWidth*(1 - 2*ID_BUTTON_BORDER_PERCENT - ID_LOGO_WIDTH_GAP_PERCENT*2) - ID_LOGO_WIDTH_GAP_PERCENT*m_iClientWidth,
        ID_BUTTON_BORDER_PERCENT*m_iClientHeight + (1 - ID_BUTTON_HEIGHT_PERCENT)*m_iClientHeight*(1 - 2*ID_BUTTON_BORDER_PERCENT -ID_BUTTON_HEIGHT_GAP_PERCENT)
        );
    m_list_low.SetRect(ID_BUTTON_BORDER_PERCENT*m_iClientWidth,
        m_iClientHeight - ID_BUTTON_BORDER_PERCENT*m_iClientHeight - ID_BUTTON_HEIGHT_PERCENT*m_iClientHeight*(1 - 2*ID_BUTTON_BORDER_PERCENT -ID_BUTTON_HEIGHT_GAP_PERCENT),
        ID_BUTTON_BORDER_PERCENT*m_iClientWidth +(1 - ID_BUTTON_WIDTH_PERCENT)*m_iClientWidth*(1 - 2*ID_BUTTON_BORDER_PERCENT -ID_BUTTON_WIDTH_GAP_PERCENT),
        m_iClientHeight - ID_BUTTON_BORDER_PERCENT*m_iClientHeight
        );

    m_net.SetWindowText((LPCTSTR)ID_BUTTON_NET_CAP);
    m_preferences.SetWindowText((LPCTSTR)ID_BUTTON_BASIC_SETTING_CAP);
    m_volInq.SetWindowText((LPCTSTR)ID_BUTTON_VOL_INQ_CAP);
    m_export.SetWindowText((LPCTSTR)ID_EXPORT_CAP);
    m_volDetailInq.SetWindowText((LPCTSTR)ID_VOL_DETAIL_CAP);
    m_quit.SetWindowText((LPCTSTR)ID_QUIT_CAP);

    int i = 0;
    int tmp_button_gap_height = ID_BUTTON_INNER_GAP_PERCENT*m_button_zone.Height();
    int tm_button_height = (m_button_zone.Height() - (ID_BUTTON_ROW_COUNT - 1)*tmp_button_gap_height)/ID_BUTTON_ROW_COUNT;
    m_net.MoveWindow(m_button_zone.left, m_button_zone.top + (i++)*(tm_button_height + tmp_button_gap_height), m_button_zone.Width(), tm_button_height);
    m_preferences.MoveWindow(m_button_zone.left, m_button_zone.top + (i++)*(tm_button_height + tmp_button_gap_height), m_button_zone.Width(), tm_button_height);
    m_volInq.MoveWindow(m_button_zone.left, m_button_zone.top + (i++)*(tm_button_height + tmp_button_gap_height), m_button_zone.Width(), tm_button_height);                 
	m_export.MoveWindow(m_button_zone.left, m_button_zone.top + (i++)*(tm_button_height + tmp_button_gap_height), m_button_zone.Width(), tm_button_height);
    m_volDetailInq.MoveWindow(m_button_zone.left, m_button_zone.top + (i++)*(tm_button_height + tmp_button_gap_height), m_button_zone.Width(), tm_button_height);
    m_quit.MoveWindow(m_button_zone.left, m_button_zone.top + (i++)*(tm_button_height + tmp_button_gap_height), m_button_zone.Width(), tm_button_height);
    m_table_sum.MoveWindow(m_list_upper);
    m_table_content.MoveWindow(m_list_low);

    LONG lStyle;
    lStyle=GetWindowLong(m_table_content.m_hWnd, GWL_STYLE);
    lStyle &= ~LVS_TYPEMASK;
    lStyle |= LVS_REPORT;
    SetWindowLong(m_table_content.m_hWnd, GWL_STYLE, lStyle);

    DWORD dwStyle = m_table_content.GetExtendedStyle();
    dwStyle |= LVS_EX_FULLROWSELECT;
    dwStyle |= LVS_EX_GRIDLINES;
    dwStyle |= LVS_OWNERDRAWFIXED;
    m_table_content.SetExtendedStyle(dwStyle);

    lStyle=GetWindowLong(m_table_sum.m_hWnd, GWL_STYLE);
    lStyle &= ~LVS_TYPEMASK;
    lStyle |= LVS_REPORT;
    SetWindowLong(m_table_sum.m_hWnd, GWL_STYLE, lStyle);

    dwStyle = m_table_sum.GetExtendedStyle();
    dwStyle |= LVS_EX_FULLROWSELECT;
    dwStyle |= LVS_EX_GRIDLINES;
    m_table_sum.SetExtendedStyle(dwStyle);

    int j = 0;
    m_table_content.InsertColumn(j++, ID_TABLE_SEQID, LVCFMT_CENTER, ID_TABLE_SEQID_WIDTH*m_list_low.Width());
    m_table_content.InsertColumn(j++, ID_TABLE_TINY_DEFICIENCY, LVCFMT_CENTER, ID_TABLE_OTHERS_WIDTH*m_list_low.Width());
    m_table_content.InsertColumn(j++, ID_TABLE_MID_DEFICIENCY, LVCFMT_CENTER, ID_TABLE_OTHERS_WIDTH*m_list_low.Width()); 
    m_table_content.InsertColumn(j++, ID_TABLE_HUGE_DEFICIENCY, LVCFMT_CENTER, ID_TABLE_OTHERS_WIDTH*m_list_low.Width());
    m_table_content.InsertColumn(j++, ID_TABLE_IRON_TRAMP, LVCFMT_CENTER, ID_TABLE_OTHERS_WIDTH*m_list_low.Width());
    m_table_content.InsertColumn(j++, ID_TABLE_RANGE, LVCFMT_CENTER, ID_TABLE_OTHERS_WIDTH*m_list_low.Width());
    m_table_content.InsertColumn(j++, ID_TABLE_VOL_IDENTIFICATION, LVCFMT_CENTER, ID_TABLE_OTHERS_WIDTH*m_list_low.Width());

    int l = 0;
    m_table_sum.InsertColumn(l++, ID_TABLE_EMPTY, LVCFMT_CENTER, ID_TABLE_SUM_WIDTH*m_list_upper.Width()); 
    m_table_sum.InsertColumn(l++, ID_TABLE_EMPTY, LVCFMT_CENTER, ID_TABLE_SUM_WIDTH*m_list_upper.Width());
    m_table_sum.InsertColumn(l++, ID_TABLE_EMPTY, LVCFMT_CENTER, ID_TABLE_SUM_WIDTH*m_list_upper.Width());
    m_table_sum.InsertColumn(l++, ID_TABLE_EMPTY, LVCFMT_CENTER, ID_TABLE_SUM_WIDTH*m_list_upper.Width());

    int k = 0;
    wchar_t title[ID_MAX_LINE] = {0};
    lineF = m_table_sum.InsertItem(k++, ID_TABLE_PROJECT_NAME);
    memset(title, 0, ID_MAX_LINE*sizeof(wchar_t));
    wcscpy(title, ID_TABLE_MATERIAL_SIZE);
    wcscat(title, ID_TABLE_SIZE_ITEM);
    lineS = m_table_sum.InsertItem(k++, title);
    lineth = m_table_sum.InsertItem(k++, ID_TABLE_MATERIAL_IDENTIFICATION);
    memset(title, 0, ID_MAX_LINE*sizeof(wchar_t));
    wcscpy(title, ID_TABLE_VELOCITY);
    wcscat(title, ID_TABLE_VELOCITY_ITEM);
    linefou = m_table_sum.InsertItem(k++, title);
    m_table_sum.SetItemCount(ID_TABLE_SUM_COLUMN_COUNT);

    memset(title, 0, ID_MAX_LINE*sizeof(wchar_t));
    wcscpy(title, ID_TABLE_FREQUENCE);
    wcscat(title, ID_TABLE_FREQUENCY_ITEM);
    m_table_sum.SetItemText(lineF, 2, title);
    memset(title, 0, ID_MAX_LINE*sizeof(wchar_t));
    wcscpy(title, ID_TABLE_SENSOR);
    wcscat(title, ID_TABLE_SENSOR_ITEM);
    m_table_sum.SetItemText(lineS, 2, title);
    m_table_sum.SetItemText(lineth, 2, ID_TABLE_WAVEFILTER);
    m_table_sum.SetItemText(linefou, 2, ID_TINY_DEFICIENCY_CAP);
    linefive = m_table_sum.InsertItem(k++, ID_MID_DEFIENCY_CAP);
    m_table_sum.SetItemText(linefive, 2, ID_HUGE_DEFIENCY_CAP);
    linesix = m_table_sum.InsertItem(k++, ID_MID_DEFIENCY_CAP);
    m_table_sum.SetItemText(linesix, 0, ID_IRON_TRAMP_CAP);
    m_table_sum.SetItemText(linesix, 2, ID_DISTANCE_CAP);
    
    CStatic *pStatic = (CStatic *)GetDlgItem(IDC_PIC_LEFT);
    pStatic->ModifyStyle(0xF, SS_BITMAP|SS_CENTERIMAGE);
    pStatic->MoveWindow(m_own_logo);

    CStatic *pStaticR = (CStatic *)GetDlgItem(IDC_PIC_RIGHT);
    pStaticR->ModifyStyle(0xF, SS_BITMAP|SS_CENTERIMAGE);
    pStaticR->MoveWindow(m_subscriber_logo);

    
    memset(wchpath, 0, sizeof(wchar_t)*MAX_PATH);
    memset(chpath, 0, MAX_PATH);
    memset(chconf, 0, MAX_PATH);
    GetCurrentDirectory(MAX_PATH, wchpath);
    WideCharToMultiByte(CP_ACP, 0, wchpath, -1, chpath, sizeof(chpath), NULL, NULL);
    strcpy(chconf, chpath);
    strcat(chpath, ID_IMAGE);
    strcat(chconf, ID_IMAGE_CONFIG);
    img_record_item tmp_item;
    unsigned char byte[FILE_MAX_BYTE] = {0};
    
    if (access(chpath, 0) != 0)
    {
        mkdir(chpath);
    }
    else
    {
        
        memset(&tmp_item, 0, sizeof(img_record_item));
        ImgFile wtarget(chconf, GSFile::ReadOnly);
        wtarget.ReadRecordHeader(&tmp_item, sizeof(img_record_item));
        int len = tmp_item.record_len;
        if (tmp_item.img_id == ID_IMAGE_VENDOR)
        {
            strcat(chpath, ID_VENDOR_LOGO);
            memcpy(imgVendorPath, chpath, MAX_PATH);
        } 
        else if (tmp_item.img_id == ID_IMAGE_SUBSCRIBER)
        {
            strcat(chpath, ID_SUBSCRIBER_LOGO);
            memcpy(imgSubPath, chpath, MAX_PATH);
        }
        
        // Create the BMP files with the bmp buffer from the stored files
        FILE *wfp = fopen(chpath,"wb+");
        int count = len/FILE_MAX_BYTE;
        count += (len%FILE_MAX_BYTE)?1:0;
        int byte_count = 0;
        for (int i = 0; i < count; i++)
        {
            byte_count = wtarget.ReadRecord(byte, FILE_MAX_BYTE);
            fwrite(byte, 1, byte_count, wfp);
        }
        if (wfp != NULL) {
            fclose(wfp);
        }
        memset(wchpath, 0, sizeof(wchar_t)*MAX_PATH);
        int trans_len = MultiByteToWideChar(CP_ACP, 0, chpath, -1, NULL, 0);
        MultiByteToWideChar(CP_ACP, 0, chpath, -1, wchpath, trans_len);
        HBITMAP hBitmap;
            hBitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(),wchpath, 
                IMAGE_BITMAP, m_own_logo.Width(), m_own_logo.Height(), LR_LOADFROMFILE);
        SetImageSection(tmp_item.img_id, hBitmap);
        wtarget.Done();
    }

    memset(wchpath, 0, sizeof(wchar_t)*MAX_PATH);
    memset(chpath, 0, MAX_PATH);
    memset(chconf, 0, MAX_PATH);
    GetCurrentDirectory(MAX_PATH, wchpath);
    WideCharToMultiByte(CP_ACP, 0, wchpath, -1, chpath, sizeof(chpath), NULL, NULL);
    strcpy(chconf, chpath);
    strcat(chpath, ID_IMAGE);
    strcat(chconf, ID_IMAGE_CONFIGS);
    if (access(chconf, 0) != 0)
    {
        //mkdir(chpath);
    }
    else
    {
        memset(&tmp_item, 0, sizeof(img_record_item));
        ImgFile wstarget(chconf, GSFile::ReadOnly);
        wstarget.ReadRecordHeader(&tmp_item, sizeof(img_record_item));
        int len = tmp_item.record_len;
        if (tmp_item.img_id == ID_IMAGE_VENDOR)
        {
            strcat(chpath, ID_VENDOR_LOGO);
            memcpy(imgVendorPath, chpath, MAX_PATH);
        } 
        else if (tmp_item.img_id == ID_IMAGE_SUBSCRIBER)
        {
            strcat(chpath, ID_SUBSCRIBER_LOGO);
            memcpy(imgSubPath, chpath, MAX_PATH);
        }

        // Create the BMP files with the bmp buffer from the stored files
        FILE *wfp = fopen(chpath,"wb+");
        int count = len/FILE_MAX_BYTE;
        count += (len%FILE_MAX_BYTE)?1:0;
        memset(byte, 0, FILE_MAX_BYTE);
        int byte_count = 0;
        for (int i = 0; i < count; i++)
        {
            byte_count = wstarget.ReadRecord(byte, FILE_MAX_BYTE);
            fwrite(byte, 1, byte_count, wfp);
        }
        fclose(wfp);

        memset(wchpath, 0, sizeof(wchar_t)*MAX_PATH);
        int trans_len = MultiByteToWideChar(CP_ACP, 0, chpath, -1, NULL, 0);
        MultiByteToWideChar(CP_ACP, 0, chpath, -1, wchpath, trans_len);
        HBITMAP hBitmap;
            hBitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(),wchpath, 
                IMAGE_BITMAP, m_own_logo.Width(), m_own_logo.Height(), LR_LOADFROMFILE);
        SetImageSection(tmp_item.img_id, hBitmap);
        wstarget.Done();
    }

    
    m_pDevice = new CDevice(this, 0);
    m_pNet = new CNet(this);
    if (m_pDevice == NULL)
    {
        AfxMessageBox(_T("Device Error"));
    }
    
    if (m_pDevice->init() == FALSE)
    {
        //AfxMessageBox(_T("Device Error"));
    }

    //if (m_pNet->OpenPort() == TRUE) ;
    //RefreshSummaryTable();
    
    RestorePreference();

    memset(wchpath, 0, sizeof(wchar_t)*MAX_PATH);
    memset(chpath, 0, MAX_PATH);
    memset(chconf, 0, MAX_PATH);
    GetCurrentDirectory(MAX_PATH, wchpath);
    WideCharToMultiByte(CP_ACP, 0, wchpath, -1, chpath, sizeof(chpath), NULL, NULL);
    strcat(chpath, ID_SOURCE);
    FindFiles(wchpath);
    if (access(chpath, 0) != 0)
    {
        mkdir(chpath);
    }
    WideCharToMultiByte(CP_ACP, 0, wchpath, -1, chconf, sizeof(chconf), NULL, NULL);

    if (access(chconf, 0) == 0)
    {
        m_backup = new GSFile(chconf, GSFile::Add);
    }
    else
    {
        m_backup = new GSFile(chconf, GSFile::Write);
        record_item_header inner_header;
        memset(&inner_header, 0, sizeof(record_item_header));
        m_backup->WriteRecordHeader(&inner_header, sizeof(record_item_header));    
    }

    m_pDevice->OpenPort();
    return TRUE;
}

void CR823_TDlg::OnClose()
{
    CDialog::OnClose();
    m_backup->Done();
}

void CR823_TDlg::SetImageSection(int arg, void* wParam)
{
    if (wParam != NULL)
    {
        HBITMAP hBitmap = (HBITMAP)(wParam);
        if (arg == ID_IMAGE_VENDOR)
        {
            CStatic *pStatic = (CStatic *)GetDlgItem(IDC_PIC_LEFT);
            pStatic->SetBitmap(hBitmap);
        }
        else if (arg == ID_IMAGE_SUBSCRIBER)
        {
            CStatic *pStaticR = (CStatic *)GetDlgItem(IDC_PIC_RIGHT);
            pStaticR->SetBitmap(hBitmap); 
        }
    }
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CR823_TDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
        // Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
	}
	else
	{
		CDialog::OnPaint();
	}
}

void CR823_TDlg::OnSize(UINT nType, int cx, int cy) 
{
    CDialog::OnSize(nType, cx, cy);
    // TODO: Add your message handler code here

    GetClientRect(&rectClient);
    m_iClientWidth = rectClient.Width();
    m_iClientHeight = rectClient.Height();

    m_button_zone.SetRect(m_iClientWidth - ID_BUTTON_BORDER_PERCENT*m_iClientWidth - ID_BUTTON_WIDTH_PERCENT*m_iClientWidth*(1 - 2*ID_BUTTON_BORDER_PERCENT -ID_BUTTON_WIDTH_GAP_PERCENT),
        m_iClientHeight - ID_BUTTON_BORDER_PERCENT*m_iClientHeight - ID_BUTTON_HEIGHT_PERCENT*m_iClientHeight*(1 - 2*ID_BUTTON_BORDER_PERCENT -ID_BUTTON_HEIGHT_GAP_PERCENT),
        m_iClientWidth - ID_BUTTON_BORDER_PERCENT*m_iClientWidth,
        m_iClientHeight - ID_BUTTON_BORDER_PERCENT*m_iClientHeight
        );
    m_own_logo.SetRect(ID_BUTTON_BORDER_PERCENT*m_iClientWidth,
        ID_BUTTON_BORDER_PERCENT*m_iClientHeight,
        ID_BUTTON_BORDER_PERCENT*m_iClientWidth + ID_LOGO_WIDTH_PERCENT*m_iClientWidth*(1 - 2*ID_BUTTON_BORDER_PERCENT - ID_LOGO_WIDTH_GAP_PERCENT*2),
        ID_BUTTON_BORDER_PERCENT*m_iClientHeight + (1 - ID_BUTTON_HEIGHT_PERCENT)*m_iClientHeight*(1 - 2*ID_BUTTON_BORDER_PERCENT -ID_BUTTON_HEIGHT_GAP_PERCENT)
        );
    m_subscriber_logo.SetRect(m_iClientWidth - ID_BUTTON_BORDER_PERCENT*m_iClientWidth - ID_LOGO_WIDTH_PERCENT*m_iClientWidth*(1 - 2*ID_BUTTON_BORDER_PERCENT - ID_LOGO_WIDTH_GAP_PERCENT*2),
        ID_BUTTON_BORDER_PERCENT*m_iClientHeight,
        (1-ID_BUTTON_BORDER_PERCENT)*m_iClientWidth,
        ID_BUTTON_BORDER_PERCENT*m_iClientHeight + (1 - ID_BUTTON_HEIGHT_PERCENT)*m_iClientHeight*(1 - 2*ID_BUTTON_BORDER_PERCENT -ID_BUTTON_HEIGHT_GAP_PERCENT)
        );
    m_list_upper.SetRect(ID_BUTTON_BORDER_PERCENT*m_iClientWidth +  ID_LOGO_WIDTH_PERCENT*m_iClientWidth*(1 - 2*ID_BUTTON_BORDER_PERCENT - ID_LOGO_WIDTH_GAP_PERCENT*2) + ID_LOGO_WIDTH_GAP_PERCENT*m_iClientWidth,
        ID_BUTTON_BORDER_PERCENT*m_iClientHeight,
        (1-ID_BUTTON_BORDER_PERCENT)*m_iClientWidth - ID_LOGO_WIDTH_PERCENT*m_iClientWidth*(1 - 2*ID_BUTTON_BORDER_PERCENT - ID_LOGO_WIDTH_GAP_PERCENT*2) - ID_LOGO_WIDTH_GAP_PERCENT*m_iClientWidth,
        ID_BUTTON_BORDER_PERCENT*m_iClientHeight + (1 - ID_BUTTON_HEIGHT_PERCENT)*m_iClientHeight*(1 - 2*ID_BUTTON_BORDER_PERCENT -ID_BUTTON_HEIGHT_GAP_PERCENT)
        );
    m_list_low.SetRect(ID_BUTTON_BORDER_PERCENT*m_iClientWidth,
        m_iClientHeight - ID_BUTTON_BORDER_PERCENT*m_iClientHeight - ID_BUTTON_HEIGHT_PERCENT*m_iClientHeight*(1 - 2*ID_BUTTON_BORDER_PERCENT -ID_BUTTON_HEIGHT_GAP_PERCENT),
        ID_BUTTON_BORDER_PERCENT*m_iClientWidth +(1 - ID_BUTTON_WIDTH_PERCENT)*m_iClientWidth*(1 - 2*ID_BUTTON_BORDER_PERCENT -ID_BUTTON_WIDTH_GAP_PERCENT),
        m_iClientHeight - ID_BUTTON_BORDER_PERCENT*m_iClientHeight
        );

    int j = 0;
    int tmp_button_gap_height = ID_BUTTON_INNER_GAP_PERCENT*m_button_zone.Height();
    int tm_button_height = (m_button_zone.Height() - (ID_BUTTON_ROW_COUNT - 1)*tmp_button_gap_height)/ID_BUTTON_ROW_COUNT;

    for (int i = 0;i < mDlgItemCount;i++)
    {
        CWnd *pWnd; 
        pWnd = GetDlgItem(m_DlgItem[i]);
        if(pWnd)
        {
            if (m_DlgItem[i] == IDC_PIC_LEFT)
            {
                pWnd->MoveWindow(m_own_logo);
                memset(wImgVendorPath, 0, MAX_PATH*sizeof(wchar_t));
                int trans_len = MultiByteToWideChar(CP_ACP, 0, imgVendorPath, -1, NULL, 0);
                MultiByteToWideChar(CP_ACP, 0, imgVendorPath, -1, wImgVendorPath, trans_len);
                HBITMAP hBitmap;
                hBitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(), wImgVendorPath, IMAGE_BITMAP, m_own_logo.Width(), m_own_logo.Height(), LR_LOADFROMFILE);
                ((CStatic *)pWnd)->SetBitmap(hBitmap);
            }
            else if (m_DlgItem[i] == IDC_PIC_RIGHT)
            {
                pWnd->MoveWindow(m_subscriber_logo);
                memset(wImgSubPath, 0, MAX_PATH*sizeof(wchar_t));
                int trans_len = MultiByteToWideChar(CP_ACP, 0, imgSubPath, -1, NULL, 0);
                MultiByteToWideChar(CP_ACP, 0, imgSubPath, -1, wImgSubPath, trans_len);
                HBITMAP hBitmap;
                hBitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(), wImgSubPath, IMAGE_BITMAP, m_subscriber_logo.Width(), m_subscriber_logo.Height(), LR_LOADFROMFILE);
                ((CStatic *)pWnd)->SetBitmap(hBitmap);
            }
            else if (m_DlgItem[i] == IDC_TABLE_SUM)
            {
                int j = 0;
                ((CLineColorListCtrl *)pWnd)->SetColumnWidth(j++, ID_TABLE_SUM_WIDTH*m_list_upper.Width());
                ((CLineColorListCtrl *)pWnd)->SetColumnWidth(j++, ID_TABLE_SUM_WIDTH*m_list_upper.Width());
                ((CLineColorListCtrl *)pWnd)->SetColumnWidth(j++, ID_TABLE_SUM_WIDTH*m_list_upper.Width());
                ((CLineColorListCtrl *)pWnd)->SetColumnWidth(j++, ID_TABLE_SUM_WIDTH*m_list_upper.Width());
                CFont *font = new CFont;
                font->CreatePointFont(m_list_upper.Height()*0.75, _T("Arial"));
                ((CLineColorListCtrl *)pWnd)->SetFont(font);
                font->Detach();
                delete font;
                pWnd->MoveWindow(m_list_upper);
            }
            else if (m_DlgItem[i] == IDC_TABLE_CONTENT)
            {
                int j = 0;
                ((CLineColorListCtrl *)pWnd)->SetColumnWidth(j++, ID_TABLE_SEQID_WIDTH*m_list_low.Width());
                ((CLineColorListCtrl *)pWnd)->SetColumnWidth(j++, ID_TABLE_OTHERS_WIDTH*m_list_low.Width());
                ((CLineColorListCtrl *)pWnd)->SetColumnWidth(j++, ID_TABLE_OTHERS_WIDTH*m_list_low.Width());
                ((CLineColorListCtrl *)pWnd)->SetColumnWidth(j++, ID_TABLE_OTHERS_WIDTH*m_list_low.Width());
                ((CLineColorListCtrl *)pWnd)->SetColumnWidth(j++, ID_TABLE_OTHERS_WIDTH*m_list_low.Width());
                ((CLineColorListCtrl *)pWnd)->SetColumnWidth(j++, ID_TABLE_OTHERS_WIDTH*m_list_low.Width());
                ((CLineColorListCtrl *)pWnd)->SetColumnWidth(j++, ID_TABLE_OTHERS_WIDTH*m_list_low.Width());

                CFont *font;
                font = new CFont;
                font->CreatePointFont(m_list_low.Height()/3, _T("Arial"));
                ((CLineColorListCtrl *)pWnd)->SetFont(font);
                font->Detach();
                delete font;
                pWnd->MoveWindow(m_list_low);
            }
            else if (m_DlgItem[i] == IDC_BUTTON_BASIC_SETTING)
            {
                pWnd->MoveWindow(m_button_zone.left, m_button_zone.top + (j++)*(tm_button_height + tmp_button_gap_height), m_button_zone.Width(), tm_button_height);
            }
            else if (m_DlgItem[i] == IDC_BUTTON_VOL_INQ)
            {
                pWnd->MoveWindow(m_button_zone.left, m_button_zone.top + (j++)*(tm_button_height + tmp_button_gap_height), m_button_zone.Width(), tm_button_height);
            }
            else if (m_DlgItem[i] == ID_EXPORT)
            {
                pWnd->MoveWindow(m_button_zone.left, m_button_zone.top + (j++)*(tm_button_height + tmp_button_gap_height), m_button_zone.Width(), tm_button_height);
            }
            else if (m_DlgItem[i] == ID_VOL_DETAIL)
            {
                pWnd->MoveWindow(m_button_zone.left, m_button_zone.top + (j++)*(tm_button_height + tmp_button_gap_height), m_button_zone.Width(), tm_button_height);
            }
            else if (m_DlgItem[i] == ID_QUIT)
            {
                pWnd->MoveWindow(m_button_zone.left, m_button_zone.top + (j++)*(tm_button_height + tmp_button_gap_height), m_button_zone.Width(), tm_button_height);
            }
        }
    }
    //GetClientRect(&rectClient);
}


// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CR823_TDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CR823_TDlg::ChartoWchar(char* src, wchar_t* des)
{
    int trans_len = MultiByteToWideChar(CP_ACP, 0, src, -1, NULL, 0);
    MultiByteToWideChar(CP_ACP, 0, src, -1, des, trans_len);
}


void CR823_TDlg::OnBnClickedButtonBasicSetting()
{
    char tmpbuf[MAX_PATH];
    test();
    // TODO: Add your control notification handler code here
    if (m_setting_dlg.DoModal() == IDOK)
    {
        record_item targ_record;
        POSITION pos = CDWORDList.GetHeadPosition();
        for (int i = 0; i < CDWORDList.GetCount(); i++)
        {
            targ_record = CDWORDList.GetNext(pos);
            CheckRange(targ_record);
        }
        StorePreference();
        RefreshSummaryTable();   
        memset(tmpbuf, 0, MAX_PATH);
        memcpy(tmpbuf, m_setting_dlg.mConfigure.getProjectName().GetBuffer(), m_setting_dlg.mConfigure.getProjectName().GetLength()*sizeof(TCHAR));
        if (CDWORDList.IsEmpty() == false)
        {
            POSITION Tailpos = CDWORDList.GetTailPosition();
            record_item volume_item = CDWORDList.GetAt(Tailpos);
            if (memcmp((char *)volume_item.volume, tmpbuf, 100) != 0)
            {
                //test();
                m_backup->Done();
                CDWORDList.RemoveAll();
                m_table_content.DeleteAllItems();
                currentItem = 0;
                subvol = 0;
                sum_count_old = 0;
                memset(wchpath, 0, sizeof(wchar_t)*MAX_PATH);
                memset(chpath, 0, MAX_PATH);
                memset(chconf, 0, MAX_PATH);
                GetCurrentDirectory(MAX_PATH, wchpath);
                WideCharToMultiByte(CP_ACP, 0, wchpath, -1, chpath, sizeof(chpath), NULL, NULL);
                strcat(chpath, ID_SOURCE);
                FindFiles(wchpath);
                if (access(chpath, 0) != 0)
                {
                    mkdir(chpath);
                }
                WideCharToMultiByte(CP_ACP, 0, wchpath, -1, chconf, sizeof(chconf), NULL, NULL);

                if (access(chconf, 0) == 0)
                {
                    m_backup = new GSFile(chconf, GSFile::Add);
                }
                else
                {
                    m_backup = new GSFile(chconf, GSFile::Write);
                    record_item_header inner_header;
                    memset(&inner_header, 0, sizeof(record_item_header));
                    m_backup->WriteRecordHeader(&inner_header, sizeof(record_item_header));    
                }
            }
        }
        
    }
}

void CR823_TDlg::RefreshSummaryTable()
{
    SetSummaryText(lineF, ID_TABLE_SUM_COLUMN_A, m_setting_dlg.mConfigure.getProjectName());
    SetSummaryText(lineS, ID_TABLE_SUM_COLUMN_A, m_setting_dlg.mConfigure.getSize());
    SetSummaryText(lineth, ID_TABLE_SUM_COLUMN_A, m_setting_dlg.mConfigure.getMaterial());
    char target[MAX_LINE] = {0};
    wchar_t wchpath[MAX_LINE];
    sprintf(target,"%.2f",m_setting_dlg.mConfigure.getVelocity());     
    ChartoWchar(target, wchpath);
    memset(target, 0, MAX_LINE);
    SetSummaryText(linefou, ID_TABLE_SUM_COLUMN_A, wchpath);
    memset(wchpath, 0, MAX_LINE*sizeof(wchar_t));

    sprintf(target,"%d",m_setting_dlg.mConfigure.getMidDeficiency());     
    ChartoWchar(target, wchpath);
    memset(target, 0, MAX_LINE);
    SetSummaryText(linefive,ID_TABLE_SUM_COLUMN_A, wchpath);
    memset(wchpath, 0, MAX_LINE*sizeof(wchar_t));
    
    sprintf(target,"%.2f",m_setting_dlg.mConfigure.getFrequency());     
    ChartoWchar(target, wchpath);
    memset(target, 0, MAX_LINE);
    SetSummaryText(lineF, ID_TABLE_SUM_COLUMN_B, wchpath);
    memset(wchpath, 0, MAX_LINE*sizeof(wchar_t));

    SetSummaryText(lineS, ID_TABLE_SUM_COLUMN_B, m_setting_dlg.mConfigure.getSensior());
    SetSummaryText(lineth, ID_TABLE_SUM_COLUMN_B, m_setting_dlg.mConfigure.getFilter());
    
    sprintf(target,"%d/%d/%d",m_setting_dlg.mConfigure.getTinyDeficiency(),
        m_setting_dlg.mConfigure.getTinyDeficiencyB(),
        m_setting_dlg.mConfigure.getTinyDeficiencyC());     
    ChartoWchar(target, wchpath);
    memset(target, 0, MAX_LINE);
    SetSummaryText(linefou, ID_TABLE_SUM_COLUMN_B, wchpath);
    memset(wchpath, 0, MAX_LINE*sizeof(wchar_t));

    sprintf(target,"%d/%d/%d",m_setting_dlg.mConfigure.getHugeDeficiency(),
        m_setting_dlg.mConfigure.getHugeDeficiencyB(),
        m_setting_dlg.mConfigure.getHugeDeficiencyC());     
    ChartoWchar(target, wchpath);
    memset(target, 0, MAX_LINE);
    SetSummaryText(linefive, ID_TABLE_SUM_COLUMN_B, wchpath);
    memset(wchpath, 0, MAX_LINE*sizeof(wchar_t));

    sprintf(target,"%d/%d/%d",m_setting_dlg.mConfigure.getMidDeficiency(),
        m_setting_dlg.mConfigure.getMidDeficiencyB(),
        m_setting_dlg.mConfigure.getMidDeficiencyC());     
    ChartoWchar(target, wchpath);
    memset(target, 0, MAX_LINE);
    SetSummaryText(linefive, ID_TABLE_SUM_COLUMN_A, wchpath);
    memset(wchpath, 0, MAX_LINE*sizeof(wchar_t));

    sprintf(target,"%d/%d/%d",m_setting_dlg.mConfigure.getIronTramp(),
        m_setting_dlg.mConfigure.getIronTrampB(),
        m_setting_dlg.mConfigure.getIronTrampC());     
    ChartoWchar(target, wchpath);
    memset(target, 0, MAX_LINE);
    SetSummaryText(linesix, ID_TABLE_SUM_COLUMN_A, wchpath);
    memset(wchpath, 0, MAX_LINE*sizeof(wchar_t));

    sprintf(target,"%d",m_setting_dlg.mConfigure.getDistance());     
    ChartoWchar(target, wchpath);
    memset(target, 0, MAX_LINE);
    SetSummaryText(linesix, ID_TABLE_SUM_COLUMN_B, wchpath);
    memset(wchpath, 0, MAX_LINE*sizeof(wchar_t));

    m_pDevice->SetDeviceConfig(m_setting_dlg.mConfigure);
}

void CR823_TDlg::OnBnClickedButtonVolInq()
{
    // TODO: Add your control notification handler code here
    test();
    m_query_dlg.setConfig(m_setting_dlg.mConfigure);
    m_query_dlg.SetExportPath(m_export_dlg.GetExportPath());
    m_query_dlg.SetExportSetting(m_export_dlg.GetExportSetting());
    if (m_query_dlg.DoModal() == IDOK)
    {

    }
}

void CR823_TDlg::OnBnClickedExport()
{
    // TODO: Add your control notification handler code here
    if (m_export_dlg.DoModal() == IDOK)
    {
        StorePreference();
    }
}

void CR823_TDlg::OnBnClickedVolDetail()
{
    // TODO: Add your control notification handler code here
    test();
    m_query_detail_dlg.setConfig(m_setting_dlg.mConfigure);
    m_query_dlg.SetExportPath(m_export_dlg.GetExportPath());
    m_query_dlg.SetExportSetting(m_export_dlg.GetExportSetting());
    if (m_query_detail_dlg.DoModal() == IDOK)
    {
    }
}

void CR823_TDlg::OnBnClickedQuit()
{
    // TODO: Add your control notification handler code here
    if (MessageBox(ID_MESSAGEBOX_EXIT_CAP, ID_MESSAGEBOX_TIP, MB_YESNO) == IDYES)
    {
        test();
        //m_backup->Done();
        PostQuitMessage(0);
    }
}

void CR823_TDlg::AddItem(int tiny, int huge, int mid, int iron, int range)
{
    line = currentItem;
	/*
    if (line > ID_TABLE_CONTENT_NUMBER)
    {
        
    }*/
	line = m_table_content.InsertItem(currentItem, ID_TABLE_EMPTY);
    record_item tmp_record;
    memset(&tmp_record, 0, sizeof(record_item));
    tmp_record.iron_tramp = tiny;
    tmp_record.huge_deficency = huge;
    tmp_record.mid_deficency = mid;
    tmp_record.tiny_deficency = tiny;
    tmp_record.range = range;
    tmp_record.serial = currentItem + 1;
    tmp_record.subVolum = subvol + 1;
    tmp_record.line = line;
    m_backup->WriteRecord(&tmp_record , sizeof(record_item));
    CString projectName = m_setting_dlg.mConfigure.getProjectName();
    memcpy(tmp_record.volume, projectName.GetBuffer(), projectName.GetLength()*sizeof(TCHAR));
    //WideCharToMultiByte(CP_ACP, 0,  projectName.GetBuffer(), -1, (char *)tmp_record.volume, sizeof(tmp_record.volume), NULL, NULL);

    CDWORDList.AddTail(tmp_record);

    if (CDWORDList.IsEmpty() == false)
    {
        POSITION Tailpos = CDWORDList.GetTailPosition();
        record_item_header tmp_header;
        record_item inner_item;
        memset(&inner_item, 0, sizeof(record_item));
        memset(&tmp_header, 0, sizeof(record_item_header));
        record_item volume_item = CDWORDList.GetAt(Tailpos);
        tmp_header.sum_count = CDWORDList.GetCount();
        tmp_header.sum_subvol = subvol+1;
        /*
        Tailpos = CDWORDList.GetHeadPosition();
        for (int i = 0; i < tmp_header.sum_count; i++)
        {
            inner_item = CDWORDList.GetNext(Tailpos);
            tmp_header.sum_tiny += inner_item.tiny_deficency; 
            tmp_header.sum_mid += inner_item.mid_deficency;
            tmp_header.sum_huge += inner_item.huge_deficency;
            tmp_header.sum_iron += inner_item.iron_tramp;
        }*/
        memcpy(tmp_header.volume, volume_item.volume, MAX_LINE);
        tmp_header.sum_count += sum_count_old;
        m_backup->updateRecordHeader(&tmp_header, sizeof(record_item_header));
    }

    CString str;
    int iItem = 0;
    str.Format(_T("%d"),tmp_record.serial);
    m_table_content.SetItemText(line, iItem++, str);
    str.Format(_T("%d"),tmp_record.tiny_deficency);
    m_table_content.SetItemText(line, iItem++, str);
    str.Format(_T("%d"),tmp_record.mid_deficency);
    m_table_content.SetItemText(line, iItem++, str);
    str.Format(_T("%d"),tmp_record.huge_deficency);
    m_table_content.SetItemText(line, iItem++, str);
    str.Format(_T("%d"),tmp_record.iron_tramp);
    m_table_content.SetItemText(line, iItem++, str);
    str.Format(_T("%s-%d"),tmp_record.volume,tmp_record.subVolum);
    m_table_content.SetItemText(line, ++iItem, str);
	currentItem++;
    CheckRange(tmp_record);
}

void CR823_TDlg::addTinyDeficiency(int arg)
{
    POSITION pos = CDWORDList.GetTailPosition();
    record_item tmp = CDWORDList.GetAt(pos);
    tmp.tiny_deficency += arg;
    CDWORDList.SetAt(pos, tmp);
    CString str;
    str.Format(_T("%d"),tmp.tiny_deficency);
    m_table_content.SetItemText(line, 1, str);
    m_backup->updateRecord(&tmp , sizeof(tmp));
    CheckRange(tmp);
}

void CR823_TDlg::addHugeDeficiency(int arg)
{
    POSITION pos = CDWORDList.GetTailPosition();
    record_item tmp = CDWORDList.GetAt(pos);
    tmp.huge_deficency += arg;
    CDWORDList.SetAt(pos, tmp);
    CString str;
    str.Format(_T("%d"),tmp.huge_deficency);
    m_table_content.SetItemText(line, 3, str);
    m_backup->updateRecord(&tmp , sizeof(tmp));
    CheckRange(tmp);
}

void CR823_TDlg::addMidDeficiency(int arg)
{
    POSITION pos = CDWORDList.GetTailPosition();
    record_item tmp = CDWORDList.GetAt(pos);
    tmp.mid_deficency += arg;
    CDWORDList.SetAt(pos, tmp);
    CString str;
    str.Format(_T("%d"),tmp.mid_deficency);
    m_table_content.SetItemText(line, 2, str);
    m_backup->updateRecord(&tmp , sizeof(tmp));
    CheckRange(tmp);
}

void CR823_TDlg::addIronDeficiency(int arg)
{
    POSITION pos = CDWORDList.GetTailPosition();
    record_item tmp = CDWORDList.GetAt(pos);
    tmp.iron_tramp += arg;
    CDWORDList.SetAt(pos, tmp);
    CString str;
    str.Format(_T("%d"),tmp.iron_tramp);
    m_table_content.SetItemText(line, 4, str);
    m_backup->updateRecord(&tmp , sizeof(tmp));
	CheckRange(tmp);
}

void CR823_TDlg::SetSummaryText(int row,int column,CString arg)
{
    m_table_sum.SetItemText(row, column, arg);
}

void CR823_TDlg::CheckRange(record_item arg)
{
    int tiny_priority = 0;
    int mid_priority = 0;
    int huge_priority = 0;
    int iron_priority = 0;
    // Handle the huge deficiency color
    if (arg.huge_deficency <= 0)
    {
        m_table_content.SetEntyColor(arg.line, ID_TABLE_CONTENT_COLUMN_HUGE, ID_COLOR_TEXT, ID_COLOR_BLANK);
    }
    else if (arg.huge_deficency < m_setting_dlg.mConfigure.getHugeDeficiency())
    {
        huge_priority = 1;
        m_table_content.SetEntyColor(arg.line, ID_TABLE_CONTENT_COLUMN_HUGE, ID_COLOR_TEXT, ID_COLOR_BASIC_LEVER);
    }
    else if (arg.huge_deficency < m_setting_dlg.mConfigure.getHugeDeficiencyB())
    {
        huge_priority = 2;
        m_table_content.SetEntyColor(arg.line, ID_TABLE_CONTENT_COLUMN_HUGE, ID_COLOR_TEXT, ID_COLOR_A_LEVER);
    }
    else if (arg.huge_deficency < m_setting_dlg.mConfigure.getHugeDeficiencyC())
    {
        huge_priority = 3;
        m_table_content.SetEntyColor(arg.line, ID_TABLE_CONTENT_COLUMN_HUGE, ID_COLOR_TEXT, ID_COLOR_B_LEVER);
    }
    else
    {
        huge_priority = 4;
        m_table_content.SetEntyColor(arg.line, ID_TABLE_CONTENT_COLUMN_HUGE, ID_COLOR_TEXT, ID_COLOR_C_LEVER);
    }

    // Handle the mid deficiency color
    if (arg.mid_deficency <= 0)
    {
        m_table_content.SetEntyColor(arg.line, ID_TABLE_CONTENT_COLUMN_MID, ID_COLOR_TEXT, ID_COLOR_BLANK);
    }
    else if (arg.mid_deficency < m_setting_dlg.mConfigure.getMidDeficiency())
    {
        mid_priority = 1;
        m_table_content.SetEntyColor(arg.line, ID_TABLE_CONTENT_COLUMN_MID, ID_COLOR_TEXT, ID_COLOR_BASIC_LEVER);
    }
    else if (arg.mid_deficency < m_setting_dlg.mConfigure.getMidDeficiencyB())
    {
        mid_priority = 2;
        m_table_content.SetEntyColor(arg.line, ID_TABLE_CONTENT_COLUMN_MID, ID_COLOR_TEXT, ID_COLOR_A_LEVER);
    }
    else if (arg.mid_deficency < m_setting_dlg.mConfigure.getMidDeficiencyC())
    {
        mid_priority = 3;
        m_table_content.SetEntyColor(arg.line, ID_TABLE_CONTENT_COLUMN_MID, ID_COLOR_TEXT, ID_COLOR_B_LEVER);
    }
    else
    {
        mid_priority = 4;
        m_table_content.SetEntyColor(arg.line, ID_TABLE_CONTENT_COLUMN_MID, ID_COLOR_TEXT, ID_COLOR_C_LEVER);
    }

    // Handle the tiny deficiency color
    if (arg.tiny_deficency <= 0)
    {
        m_table_content.SetEntyColor(arg.line, ID_TABLE_CONTENT_COLUMN_TINY, ID_COLOR_TEXT, ID_COLOR_BLANK);
    }
    else if (arg.tiny_deficency < m_setting_dlg.mConfigure.getTinyDeficiency())
    {
        tiny_priority = 1;
        m_table_content.SetEntyColor(arg.line, ID_TABLE_CONTENT_COLUMN_TINY, ID_COLOR_TEXT, ID_COLOR_BASIC_LEVER);
    }
    else if (arg.tiny_deficency < m_setting_dlg.mConfigure.getTinyDeficiencyB())
    {
        tiny_priority = 2;
        m_table_content.SetEntyColor(arg.line, ID_TABLE_CONTENT_COLUMN_TINY, ID_COLOR_TEXT, ID_COLOR_A_LEVER);
    }
    else if (arg.tiny_deficency < m_setting_dlg.mConfigure.getTinyDeficiencyC())
    {
        tiny_priority = 3;
        m_table_content.SetEntyColor(arg.line, ID_TABLE_CONTENT_COLUMN_TINY, ID_COLOR_TEXT, ID_COLOR_B_LEVER);
    }
    else
    {
        tiny_priority = 4;
        m_table_content.SetEntyColor(arg.line, ID_TABLE_CONTENT_COLUMN_TINY, ID_COLOR_TEXT, ID_COLOR_C_LEVER);
    }

    // Handle the iron tramp color
    if (arg.iron_tramp <= 0)
    {
        m_table_content.SetEntyColor(arg.line, ID_TABLE_CONTENT_COLUMN_IRON, ID_COLOR_TEXT, ID_COLOR_BLANK);
    }
    else if (arg.iron_tramp < m_setting_dlg.mConfigure.getIronTramp())
    {
        iron_priority = 1;
        m_table_content.SetEntyColor(arg.line, ID_TABLE_CONTENT_COLUMN_IRON, ID_COLOR_TEXT, ID_COLOR_BASIC_LEVER);
    }
    else if (arg.iron_tramp < m_setting_dlg.mConfigure.getIronTrampB())
    {
        iron_priority = 2;
        m_table_content.SetEntyColor(arg.line, ID_TABLE_CONTENT_COLUMN_IRON, ID_COLOR_TEXT, ID_COLOR_A_LEVER);
    }
    else if (arg.iron_tramp < m_setting_dlg.mConfigure.getIronTrampC())
    {
        iron_priority = 3;
        m_table_content.SetEntyColor(arg.line, ID_TABLE_CONTENT_COLUMN_IRON, ID_COLOR_TEXT, ID_COLOR_B_LEVER);
    }
    else
    {
        iron_priority = 4;
        m_table_content.SetEntyColor(arg.line, ID_TABLE_CONTENT_COLUMN_IRON, ID_COLOR_TEXT, ID_COLOR_C_LEVER);
    }

    if ((iron_priority >= mid_priority) && (iron_priority >= huge_priority) && (iron_priority >= tiny_priority) && (iron_priority != 0))
    {
        m_table_content.SetItemText(arg.line, ID_TABLE_CONTENT_COLUMN_RANGE, ID_TABLE_IRON_TRAMP);
        SetRangeColor(arg, iron_priority);
    }
    else if ((huge_priority >= mid_priority) && (huge_priority >= tiny_priority) && (huge_priority > iron_priority) && (huge_priority != 0))
    {
        m_table_content.SetItemText(arg.line, ID_TABLE_CONTENT_COLUMN_RANGE, ID_TABLE_HUGE_DEFICIENCY);
        SetRangeColor(arg, huge_priority);
    }
    else if ((mid_priority >= tiny_priority) && (mid_priority > huge_priority) && (mid_priority > iron_priority) && (mid_priority != 0))
    {
        m_table_content.SetItemText(arg.line, ID_TABLE_CONTENT_COLUMN_RANGE, ID_TABLE_MID_DEFICIENCY);
        SetRangeColor(arg, mid_priority);
    }
    else if ((tiny_priority > mid_priority) && (tiny_priority > huge_priority) && (tiny_priority > iron_priority) && (tiny_priority != 0))
    {
        m_table_content.SetItemText(arg.line, ID_TABLE_CONTENT_COLUMN_RANGE, ID_TABLE_TINY_DEFICIENCY);
        SetRangeColor(arg, tiny_priority);
    }
    else
    {
        m_table_content.SetItemText(arg.line, ID_TABLE_CONTENT_COLUMN_RANGE, ID_TABLE_EMPTY);
        SetRangeColor(arg, 0);    
    }
}

void CR823_TDlg::SetRangeColor(record_item arg, int arg_priority)
{
    if (arg_priority == 0)
    {
        m_table_content.SetEntyColor(arg.line, ID_TABLE_CONTENT_COLUMN_RANGE, ID_COLOR_TEXT, ID_COLOR_BLANK);
    }
    else if (arg_priority == 1)
    {
        m_table_content.SetEntyColor(arg.line, ID_TABLE_CONTENT_COLUMN_RANGE, ID_COLOR_TEXT, ID_COLOR_BASIC_LEVER);
    }
    else if (arg_priority == 2)
    {
        m_table_content.SetEntyColor(arg.line, ID_TABLE_CONTENT_COLUMN_RANGE, ID_COLOR_TEXT, ID_COLOR_A_LEVER);
    }
    else if (arg_priority == 3)
    {
        m_table_content.SetEntyColor(arg.line, ID_TABLE_CONTENT_COLUMN_RANGE, ID_COLOR_TEXT, ID_COLOR_B_LEVER);
    }
    else if (arg_priority == 4)
    {
        m_table_content.SetEntyColor(arg.line, ID_TABLE_CONTENT_COLUMN_RANGE, ID_COLOR_TEXT, ID_COLOR_C_LEVER);
    }
}

void CR823_TDlg::test()
{
    char tmpbuf[MAX_PATH];
    memset(tmpbuf, 0, MAX_PATH);
    //memcpy(tmpbuf, m_setting_dlg.mConfigure.getProjectName().GetBuffer(), m_setting_dlg.mConfigure.getProjectName().GetLength()*sizeof(TCHAR));

    if (CDWORDList.IsEmpty() == false)
    {
        POSITION Tailpos = CDWORDList.GetTailPosition();
        record_item_header tmp_header;
        record_item inner_item;
        memset(&inner_item, 0, sizeof(record_item));
        memset(&tmp_header, 0, sizeof(record_item_header));
        record_item volume_item = CDWORDList.GetAt(Tailpos);
        tmp_header.sum_count = CDWORDList.GetCount();
        tmp_header.sum_subvol = subvol+1;
        
        Tailpos = CDWORDList.GetHeadPosition();
        //for (int i = 0; i < CDWORDList.GetCount(); i++)
        {
            inner_item = CDWORDList.GetNext(Tailpos);
        }
        memcpy(tmp_header.volume, volume_item.volume, MAX_LINE);
        tmp_header.sum_count += sum_count_old;
        m_backup->updateRecordHeader(&tmp_header, sizeof(record_item_header));
    }
    //m_backup->Done();
}

/**
    Store the configuration of the project
*/
void CR823_TDlg::StorePreference()
{
    memset(wchpath, 0, sizeof(wchar_t)*MAX_PATH);
    memset(chpath, 0, MAX_PATH);
    memset(chperference, 0, MAX_PATH);
    GetCurrentDirectory(MAX_PATH, wchpath);
    WideCharToMultiByte(CP_ACP, 0, wchpath, -1, chpath, sizeof(chpath), NULL, NULL);
    strcpy(chperference, chpath);
    strcat(chpath, ID_SOURCE);
    strcat(chperference, ID_PREFERENCE);
    if (access(chpath, 0) != 0)
    {
        mkdir(chpath);
    }

    GSFile target(chperference, GSFile::Write);
    record_preference_header tmp_item; 
    record_preference_item tmp;
    memset(&tmp_item, 0, sizeof(record_preference_header));
    tmp_item.count = ID_STORAGE_NET_PATH;
    target.WriteRecordHeader(&tmp_item, sizeof(record_preference_header));
    memset(&tmp, 0, sizeof(record_preference_item));

    tmp.id = ID_STORAGE_PROJECTNAME;
    memcpy(tmp.buffer, m_setting_dlg.mConfigure.getProjectName().GetBuffer(), m_setting_dlg.mConfigure.getProjectName().GetLength()*sizeof(TCHAR));
    target.WriteRecord(&tmp , sizeof(tmp));
    memset(&tmp, 0, sizeof(record_preference_item));

    tmp.id = ID_STORAGE_SIZE;
    memcpy(tmp.buffer, m_setting_dlg.mConfigure.getSize().GetBuffer(), m_setting_dlg.mConfigure.getSize().GetLength()*sizeof(TCHAR));
    target.WriteRecord(&tmp , sizeof(tmp));
    memset(&tmp, 0, sizeof(record_preference_item));

    tmp.id = ID_STORAGE_MATERIAL;
    memcpy(tmp.buffer, m_setting_dlg.mConfigure.getMaterial().GetBuffer(), m_setting_dlg.mConfigure.getMaterial().GetLength()*sizeof(TCHAR));
    target.WriteRecord(&tmp , sizeof(tmp));
    memset(&tmp, 0, sizeof(record_preference_item));
   
    tmp.id = ID_STORAGE_VELOCITY;
    float tmp_float = 0.0;
    tmp_float = m_setting_dlg.mConfigure.getVelocity();
    memcpy(tmp.buffer, &tmp_float, sizeof(float));
    target.WriteRecord(&tmp , sizeof(tmp));
    memset(&tmp, 0, sizeof(record_preference_item));
 
    tmp.id = ID_STORAGE_FREQUENCY;
    tmp_float = m_setting_dlg.mConfigure.getFrequency();
    memcpy(tmp.buffer, &tmp_float, sizeof(float));
    target.WriteRecord(&tmp , sizeof(tmp));
    memset(&tmp, 0, sizeof(record_preference_item));

    tmp.id = ID_STORAGE_SENISOR;
    memcpy(tmp.buffer,m_setting_dlg.mConfigure.getSensior().GetBuffer(), m_setting_dlg.mConfigure.getSensior().GetLength()*sizeof(TCHAR));
    target.WriteRecord(&tmp , sizeof(tmp));
    memset(&tmp, 0, sizeof(record_preference_item));

    tmp.id = ID_STORAGE_WAVEFILTER;
    memcpy(tmp.buffer, m_setting_dlg.mConfigure.getFilter().GetBuffer(), m_setting_dlg.mConfigure.getFilter().GetLength()*sizeof(TCHAR));
    target.WriteRecord(&tmp , sizeof(tmp));
    memset(&tmp, 0, sizeof(record_preference_item));
      
    tmp.id = ID_STORAGE_TINY_DEFICIENCY;
    int tmp_int = 0;
    tmp_int = m_setting_dlg.mConfigure.getTinyDeficiency();
    memcpy(tmp.buffer, &tmp_int, sizeof(int));
    target.WriteRecord(&tmp , sizeof(tmp));
    memset(&tmp, 0, sizeof(record_preference_item));
    
    tmp.id = ID_STORAGE_TINY_DEFICIENCYB;
    tmp_int = 0;
    tmp_int = m_setting_dlg.mConfigure.getTinyDeficiencyB();
    memcpy(tmp.buffer, &tmp_int, sizeof(int));
    target.WriteRecord(&tmp , sizeof(tmp));
    memset(&tmp, 0, sizeof(record_preference_item));

    tmp.id = ID_STORAGE_TINY_DEFICIENCYC;
    tmp_int = 0;
    tmp_int = m_setting_dlg.mConfigure.getTinyDeficiencyC();
    memcpy(tmp.buffer, &tmp_int, sizeof(int));
    target.WriteRecord(&tmp , sizeof(tmp));
    memset(&tmp, 0, sizeof(record_preference_item));

    tmp.id = ID_STORAGE_MID_DEFICIENCY;
    tmp_int = m_setting_dlg.mConfigure.getMidDeficiency();
    memcpy(tmp.buffer, &tmp_int, sizeof(int));
    target.WriteRecord(&tmp , sizeof(tmp));
    memset(&tmp, 0, sizeof(record_preference_item));
  
    tmp.id = ID_STORAGE_MID_DEFICIENCYB;
    tmp_int = m_setting_dlg.mConfigure.getMidDeficiencyB();
    memcpy(tmp.buffer, &tmp_int, sizeof(int));
    target.WriteRecord(&tmp , sizeof(tmp));
    memset(&tmp, 0, sizeof(record_preference_item));

    tmp.id = ID_STORAGE_MID_DEFICIENCYC;
    tmp_int = m_setting_dlg.mConfigure.getMidDeficiencyC();
    memcpy(tmp.buffer, &tmp_int, sizeof(int));
    target.WriteRecord(&tmp , sizeof(tmp));
    memset(&tmp, 0, sizeof(record_preference_item));

    tmp.id = ID_STORAGE_HUGE_DEFICIENCY;
    tmp_int = m_setting_dlg.mConfigure.getHugeDeficiency();
    memcpy(tmp.buffer, &tmp_int, sizeof(int));
    target.WriteRecord(&tmp , sizeof(tmp));
    memset(&tmp, 0, sizeof(record_preference_item));
  
    tmp.id = ID_STORAGE_HUGE_DEFICIENCYB;
    tmp_int = m_setting_dlg.mConfigure.getHugeDeficiencyB();
    memcpy(tmp.buffer, &tmp_int, sizeof(int));
    target.WriteRecord(&tmp , sizeof(tmp));
    memset(&tmp, 0, sizeof(record_preference_item));

    tmp.id = ID_STORAGE_HUGE_DEFICIENCYC;
    tmp_int = m_setting_dlg.mConfigure.getHugeDeficiencyC();
    memcpy(tmp.buffer, &tmp_int, sizeof(int));
    target.WriteRecord(&tmp , sizeof(tmp));
    memset(&tmp, 0, sizeof(record_preference_item));

    tmp.id = ID_STORAGE_IRON_TRAMP;
    tmp_int = m_setting_dlg.mConfigure.getIronTramp();
    memcpy(tmp.buffer, &tmp_int, sizeof(int));
    target.WriteRecord(&tmp , sizeof(tmp));
    memset(&tmp, 0, sizeof(record_preference_item));

    tmp.id = ID_STORAGE_IRON_TRAMPB;
    tmp_int = m_setting_dlg.mConfigure.getIronTrampB();
    memcpy(tmp.buffer, &tmp_int, sizeof(int));
    target.WriteRecord(&tmp , sizeof(tmp));
    memset(&tmp, 0, sizeof(record_preference_item));

    tmp.id = ID_STORAGE_IRON_TRAMPC;
    tmp_int = m_setting_dlg.mConfigure.getIronTrampC();
    memcpy(tmp.buffer, &tmp_int, sizeof(int));
    target.WriteRecord(&tmp , sizeof(tmp));
    memset(&tmp, 0, sizeof(record_preference_item));

    tmp.id = ID_STORAGE_DISTANCE;
    tmp_int = m_setting_dlg.mConfigure.getDistance();
    memcpy(tmp.buffer, &tmp_int, sizeof(int));
    target.WriteRecord(&tmp , sizeof(tmp));
    memset(&tmp, 0, sizeof(record_preference_item));

    tmp.id = ID_STORAGE_EXPORT_SETTING;
    tmp_int = m_export_dlg.GetExportSetting();
    memcpy(tmp.buffer, &tmp_int, sizeof(int));
    target.WriteRecord(&tmp , sizeof(tmp));
    memset(&tmp, 0, sizeof(record_preference_item));

    tmp.id = ID_STORAGE_EXPORT_PATH;
    memcpy(tmp.buffer, m_export_dlg.GetExportPath().GetBuffer(),m_export_dlg.GetExportPath().GetLength()*sizeof(TCHAR));
    target.WriteRecord(&tmp , sizeof(tmp));
    memset(&tmp, 0, sizeof(record_preference_item));

    tmp.id = ID_STORAGE_NET_IP;
    memcpy(tmp.buffer, m_net_dlg.mIp.GetBuffer(), m_net_dlg.mIp.GetLength()*sizeof(TCHAR));
    target.WriteRecord(&tmp , sizeof(tmp));
    memset(&tmp, 0, sizeof(record_preference_item));

    tmp.id = ID_STORAGE_NET_USERNAME;
    memcpy(tmp.buffer, m_net_dlg.mUsername.GetBuffer(),m_net_dlg.mUsername.GetLength()*sizeof(TCHAR));
    target.WriteRecord(&tmp , sizeof(tmp));
    memset(&tmp, 0, sizeof(record_preference_item));

    tmp.id = ID_STORAGE_NET_PASSWORD;
    memcpy(tmp.buffer, m_net_dlg.mPassword.GetBuffer(),m_net_dlg.mPassword.GetLength()*sizeof(TCHAR));
    target.WriteRecord(&tmp , sizeof(tmp));
    memset(&tmp, 0, sizeof(record_preference_item));

    tmp.id = ID_STORAGE_NET_PATH;
    memcpy(tmp.buffer, m_net_dlg.mFolder.GetBuffer(),m_net_dlg.mFolder.GetLength()*sizeof(TCHAR));
    target.WriteRecord(&tmp , sizeof(tmp));
    memset(&tmp, 0, sizeof(record_preference_item));
    target.Done();
}

void CR823_TDlg::RestorePreference()
{
    memset(wchpath, 0, sizeof(wchar_t)*MAX_PATH);
    memset(chpath, 0, MAX_PATH);
    memset(chperference, 0, MAX_PATH);
    GetCurrentDirectory(MAX_PATH, wchpath);
    WideCharToMultiByte(CP_ACP, 0, wchpath, -1, chpath, sizeof(chpath), NULL, NULL);
    strcpy(chperference, chpath);
    strcat(chpath, ID_SOURCE);
    strcat(chperference, ID_PREFERENCE);
    
    if (access(chperference, 0) == 0)
    {
        GSFile target(chperference, GSFile::ReadOnly);
        record_preference_header tmp_item; 
        record_preference_item tmp;
        memset(&tmp_item, 0, sizeof(record_preference_header));
        target.ReadRecordHeader(&tmp_item, sizeof(record_preference_header));

        for (int i = 0; i < tmp_item.count; i++)
        {
            memset(&tmp, 0, sizeof(record_preference_item));
            target.ReadRecord(&tmp , sizeof(tmp));
            SetPreferenceFromFile(&tmp);
        }
        target.Done();
        RefreshSummaryTable();
    }
}

void CR823_TDlg::SetPreferenceFromFile(void* para)
{
    record_preference_item* arg = (record_preference_item*)para;
    CString str;
    int tmp_int = 0;
    float tmp_float = 0.0;
    switch (arg->id)
    {
    case ID_STORAGE_NET_IP:
        {
            str.Empty();
            str.Format(_T("%s"), arg->buffer);
            m_net_dlg.mIp = str;       
        }
        break;
    case ID_STORAGE_NET_USERNAME:
        {
            str.Empty();
            str.Format(_T("%s"), arg->buffer);
            m_net_dlg.mUsername = str;       
        }
        break;
    case ID_STORAGE_NET_PASSWORD:
        {
            str.Empty();
            str.Format(_T("%s"), arg->buffer);
            m_net_dlg.mPassword = str;     
        }
        break;
    case ID_STORAGE_NET_PATH:
        {
            str.Empty();
            str.Format(_T("%s"), arg->buffer);
            m_net_dlg.mFolder = str;
        }
        break;
    case ID_STORAGE_EXPORT_SETTING:
        {
            memcpy(&tmp_int, arg->buffer, sizeof(int));
            m_export_dlg.SetExportSetting(tmp_int) ;       
        }
        break;
    case ID_STORAGE_EXPORT_PATH:
        {
            str.Empty();
            str.Format(_T("%s"), arg->buffer);
            m_export_dlg.SetExportPath(str); 
        }
        break;
    case ID_STORAGE_PROJECTNAME:
        {
            str.Empty();
            str.Format(_T("%s"), arg->buffer);
            m_setting_dlg.mConfigure.setProjectName(str);
        }
        break;
    case ID_STORAGE_VELOCITY:
        {
            memcpy(&tmp_float, arg->buffer, sizeof(float));
            m_setting_dlg.mConfigure.setVelocity(tmp_float);
        }
        break;
    case ID_STORAGE_MATERIAL:
        {
            str.Empty();
            str.Format(_T("%s"), arg->buffer);
            m_setting_dlg.mConfigure.setMaterial(str);
        }
        break;
    case ID_STORAGE_FREQUENCY:
        {
            memcpy(&tmp_float, arg->buffer, sizeof(float));
            m_setting_dlg.mConfigure.setFrequency(tmp_float);
        }
        break;
    case ID_STORAGE_SENISOR:
        {
            str.Empty();
            str.Format(_T("%s"), arg->buffer);
            m_setting_dlg.mConfigure.setSensior(str);
        }
        break;
    case ID_STORAGE_WAVEFILTER:
        {
            str.Empty();
            str.Format(_T("%s"), arg->buffer);
            m_setting_dlg.mConfigure.setFilter(str);
        }
        break;
    case ID_STORAGE_TINY_DEFICIENCY:
        {
            memcpy(&tmp_int, arg->buffer, sizeof(int));
            m_setting_dlg.mConfigure.setTinyDeficiency(tmp_int);
        }
        break;
    case ID_STORAGE_TINY_DEFICIENCYB:
        {
            memcpy(&tmp_int, arg->buffer, sizeof(int));
            m_setting_dlg.mConfigure.setTinyDeficiencyB(tmp_int);
        }
        break;
    case ID_STORAGE_TINY_DEFICIENCYC:
        {
            memcpy(&tmp_int, arg->buffer, sizeof(int));
            m_setting_dlg.mConfigure.setTinyDeficiencyC(tmp_int);
        }
        break;
    case ID_STORAGE_MID_DEFICIENCY:
        {
            memcpy(&tmp_int, arg->buffer, sizeof(int));
            m_setting_dlg.mConfigure.setMidDeficiency(tmp_int);
        }
        break;
    case ID_STORAGE_MID_DEFICIENCYB:
        {
            memcpy(&tmp_int, arg->buffer, sizeof(int));
            m_setting_dlg.mConfigure.setMidDeficiencyB(tmp_int);
        }
        break;
    case ID_STORAGE_MID_DEFICIENCYC:
        {
            memcpy(&tmp_int, arg->buffer, sizeof(int));
            m_setting_dlg.mConfigure.setMidDeficiencyC(tmp_int);
        }
        break;
    case ID_STORAGE_HUGE_DEFICIENCY:
        {
            memcpy(&tmp_int, arg->buffer, sizeof(int));
            m_setting_dlg.mConfigure.setHugeDeficiency(tmp_int);
        }
        break;
    case ID_STORAGE_HUGE_DEFICIENCYB:
        {
            memcpy(&tmp_int, arg->buffer, sizeof(int));
            m_setting_dlg.mConfigure.setHugeDeficiencyB(tmp_int);
        }
        break;
    case ID_STORAGE_HUGE_DEFICIENCYC:
        {
            memcpy(&tmp_int, arg->buffer, sizeof(int));
            m_setting_dlg.mConfigure.setHugeDeficiencyC(tmp_int);
        }
        break;
    case ID_STORAGE_IRON_TRAMP:
        {
            memcpy(&tmp_int, arg->buffer, sizeof(int));
            m_setting_dlg.mConfigure.setIronTramp(tmp_int);
        }
        break;
    case ID_STORAGE_IRON_TRAMPB:
        {
            memcpy(&tmp_int, arg->buffer, sizeof(int));
            m_setting_dlg.mConfigure.setIronTrampB(tmp_int);
        }
        break;
    case ID_STORAGE_IRON_TRAMPC:
        {
            memcpy(&tmp_int, arg->buffer, sizeof(int));
            m_setting_dlg.mConfigure.setIronTrampC(tmp_int);
        }
        break;
    case ID_STORAGE_DISTANCE:
        {
            memcpy(&tmp_int, arg->buffer, sizeof(int));
            m_setting_dlg.mConfigure.setDistance(tmp_int);
        }
        break;
    case ID_STORAGE_SIZE:
        {
            str.Empty();
            str.Format(_T("%s"), arg->buffer);
            m_setting_dlg.mConfigure.setSize(str);
        }
        break;
    }
}

LRESULT CR823_TDlg::OnTinyDeficiency(WPARAM wParam, LPARAM lParam)
{
    addTinyDeficiency((int)wParam);
    return 0;
}

LRESULT CR823_TDlg::OnMidDeficiency(WPARAM wParam, LPARAM lParam)
{
    addMidDeficiency((int)wParam);
    return 0;
}

LRESULT CR823_TDlg::OnHugeyDeficiency(WPARAM wParam, LPARAM lParam)
{
    addHugeDeficiency((int)wParam);
    return 0;
}

LRESULT CR823_TDlg::OnIronDeficiency(WPARAM wParam, LPARAM lParam)
{
    addIronDeficiency((int)wParam);
    return 0;
}

LRESULT CR823_TDlg::OnEntireDeficiency(WPARAM wParam, LPARAM lParam)
{
    AddItem(0, 0, 0, 0, 0);
    return 0;
}

LRESULT CR823_TDlg::onStoreClear(WPARAM wParam, LPARAM lParam)
{
	//test();
    subvol++;
    currentItem = 0;
	m_table_content.DeleteAllItems();
    m_setting_dlg.mConfigure.current_subvol = -1;
    //AddItem(0, 0, 0, 0, 0);
	return 0;
}

LRESULT CR823_TDlg::onDeviceError(WPARAM wParam, LPARAM lParam)
{
    //AfxMessageBox(ID_DEVICE_NOT_FOUND);
    return 0;
}

LRESULT CR823_TDlg::onAddItem(WPARAM wParam, LPARAM lParam)
{
    AddItem(0, 0, 0, 0, 0);
    m_setting_dlg.mConfigure.current_subvol = subvol +1;
    return 0;
}

void CR823_TDlg::FindFiles(wchar_t* arg)
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
    while(res)
    {
        memset(tmppath, 0, MAX_PATH);
        memset(tmpbuf, 0, MAX_PATH);
        strTmp.Empty();
        strTmp = arg;
        strTmp += _T("\\");
        strTmp += fileData.cFileName;
        WideCharToMultiByte(CP_ACP, 0, strTmp, -1, tmppath, sizeof(tmppath), NULL, NULL);
        if (access(tmppath, 0) < 0)
        {
            break;
        }
        GSFile tmpTarget(tmppath, GSFile::ReadOnly);
        if (tmpTarget.GetFileVersion() == FILE_SOURCE_TYPE)
        {
            record_item_header inner_header;
            memset(&inner_header, 0, sizeof(record_item_header));
            tmpTarget.ReadRecordHeader(&inner_header, sizeof(record_item_header));
            memcpy(tmpbuf, m_setting_dlg.mConfigure.getProjectName().GetBuffer(), m_setting_dlg.mConfigure.getProjectName().GetLength()*sizeof(TCHAR));
            //WideCharToMultiByte(CP_ACP, 0,  m_setting_dlg.mConfigure.getProjectName().GetBuffer(), -1, tmpbuf, sizeof(tmpbuf), NULL, NULL);
            if (memcmp((char*)inner_header.volume, tmpbuf, 100) == 0)
            {
                memset(arg ,0, MAX_PATH *sizeof(wchar_t));
                wcscpy(arg, strTmp.GetBuffer());
                subvol = inner_header.sum_subvol;
                sum_count_old = inner_header.sum_count;
                return;
            }
        }
        tmpTarget.Done();
        res = FindNextFile(file, &fileData);
    }
    targetFilePath += _T("\\");
    targetFilePath += tm.Format("%Y%m%d%H%M%S");
    targetFilePath += _T(".rsf");
    memset(arg ,0, MAX_PATH *sizeof(wchar_t));
    wcscpy(arg, targetFilePath.GetBuffer());
    //MultiByteToWideChar( CP_ACP , 0 , targetFilePath , targetFilePath.GetLength() , arg, MAX_PATH);
}
void CR823_TDlg::OnBnClickedButtonNet()
{
    // TODO: Add your control notification handler code here
    if (m_net_dlg.DoModal() == IDOK)
    {
        StorePreference();
        NetConfig config;
        config.ip = m_net_dlg.mIp;
        config.username = m_net_dlg.mUsername;
        config.passward = m_net_dlg.mPassword;
        config.folder = m_net_dlg.mFolder;
        m_pNet->SetConfig(config);
        if (m_pNet->OpenPort() == FALSE)
        {
            //AfxMessageBox(_T("Connection Failed"));
        } 
        else 
        {
        }
    }
}
