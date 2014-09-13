#include "R823_TVolQuery.h"

CR823_TVolQuery::CR823_TVolQuery(CWnd* pParent)
    : CR823_TQuery(pParent)
{

}

BOOL CR823_TVolQuery::OnInitDialog()
{
    CR823_TQuery::OnInitDialog();

    //m_select.SetWindowText(ID_STATIC_QUERY_SELECT_ITEM);
    //m_static_content.SetWindowText(ID_STATIC_QUERY_SELECT_RECORD);

    int j = 0;
    CRect rect;
    m_table_content.GetClientRect(&rect);
    m_table_content.InsertColumn(j++, ID_TABLE_SEQID, LVCFMT_CENTER, ID_TABLE_SEQID_WIDTH*rect.Width());
    m_table_content.InsertColumn(j++, ID_TABLE_TINY_DEFICIENCY, LVCFMT_CENTER, ID_TABLE_OTHERS_WIDTH*rect.Width());
    m_table_content.InsertColumn(j++, ID_TABLE_MID_DEFICIENCY, LVCFMT_CENTER, ID_TABLE_OTHERS_WIDTH*rect.Width()); 
    m_table_content.InsertColumn(j++, ID_TABLE_HUGE_DEFICIENCY, LVCFMT_CENTER, ID_TABLE_OTHERS_WIDTH*rect.Width());
    m_table_content.InsertColumn(j++, ID_TABLE_IRON_TRAMP, LVCFMT_CENTER, ID_TABLE_OTHERS_WIDTH*rect.Width());
    //m_table_content.InsertColumn(j++, ID_TABLE_RANGE, LVCFMT_CENTER, ID_TABLE_OTHERS_WIDTH*rect.Width());
    m_table_content.InsertColumn(j++, ID_TABLE_VOL_IDENTIFICATION, LVCFMT_CENTER, ID_TABLE_OTHERS_WIDTH*rect.Width());
    m_table_content.SetColumnCount(j);

    m_static_content.ModifyStyle(0, WS_CHILD|SS_BITMAP|SS_NOTIFY);
    m_entry.ModifyStyle(0, WS_CHILD|CBS_AUTOHSCROLL|CBS_DROPDOWNLIST);

    this->SetWindowText(ID_BUTTON_VOL_INQ_CAP);

    wchar_t wchpath[MAX_PATH] = {0};
    char chpath[MAX_PATH] = {0};
    char chconf[MAX_PATH] = {0};
    GetCurrentDirectory(MAX_PATH, wchpath);
    WideCharToMultiByte(CP_ACP, 0, wchpath, -1, chpath, sizeof(chpath), NULL, NULL);
    FindFiles(wchpath);
    strcpy(chconf, chpath);
    strcat(chpath, ID_SOURCE);
    //strcat(chconf, ID_SOURCE_CONFIG);
    if (access(chpath, 0) != 0)
    {
        mkdir(chpath);
    }
    //updateRecord();
    return TRUE;
}

void CR823_TVolQuery::updateRecord(char* arg)
{
    m_table_content.DeleteAllItems();
    currentItem = 0;
    GSFile wtarget(arg, GSFile::ReadOnly);

    record_item_header tmp_item;
    record_item tmp_record;
    memset(&tmp_item, 0, sizeof(record_item_header));
    wtarget.ReadRecordHeader(&tmp_item, sizeof(record_item_header));
    int len = tmp_item.sum_count;
    int subvol = tmp_item.sum_subvol;
    record_item *buf = (record_item *)malloc(subvol*sizeof(record_item));
    memset(buf, 0, subvol*sizeof(record_item));
    char tmpbuf[MAX_PATH];
    memset(tmpbuf, 0, MAX_PATH);
    memcpy(tmpbuf, mConfigure.getProjectName().GetBuffer(), mConfigure.getProjectName().GetLength()*sizeof(TCHAR));
    m_table_content.SetRowCount(0);
    for (int i = 0; i < len; i++)
    {
        memset(&tmp_record, 0, sizeof(record_item));
        wtarget.ReadRecord(&tmp_record, sizeof(record_item));
        buf[tmp_record.subVolum - 1].tiny_deficency += tmp_record.tiny_deficency;
        buf[tmp_record.subVolum - 1].huge_deficency += tmp_record.huge_deficency;
        buf[tmp_record.subVolum - 1].iron_tramp += tmp_record.iron_tramp;
        buf[tmp_record.subVolum - 1].mid_deficency += tmp_record.mid_deficency;
    }
    for (int i = 0; i < subvol; i++)
    {
        buf[i].subVolum = i +1;
        bool am = (buf[i].subVolum == mConfigure.current_subvol);
        bool bm = (memcmp(tmpbuf, tmp_item.volume, 100) == 0);
        if (am  && bm)
        {
        
        }
        else
        {
            AddItem(buf[i]);
        }
    }
    free(buf);
    wtarget.Done();
}

void CR823_TVolQuery::AddItem(record_item arg)
{
    CString str;
    int iItem = 0;
	line = m_table_content.InsertItem(currentItem++, ID_TABLE_EMPTY);
    str.Format(_T("%d"),currentItem-1);
    m_table_content.SetItemText(line, iItem++, str);
    str.Format(_T("%d"),arg.tiny_deficency);
    m_table_content.SetItemText(line, iItem++, str);
    str.Format(_T("%d"),arg.mid_deficency);
    m_table_content.SetItemText(line, iItem++, str);
    str.Format(_T("%d"),arg.huge_deficency);
    m_table_content.SetItemText(line, iItem++, str);
    str.Format(_T("%d"),arg.iron_tramp);
    m_table_content.SetItemText(line, iItem++, str);
    str.Format(_T("%d"),arg.subVolum);
    m_table_content.SetItemText(line, iItem++, str);
    //m_table_content.SetRowCount(1);
    m_table_content.AddRowCount();
    CheckRange(arg);
}

void CR823_TVolQuery::CheckRange(record_item arg)
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
    else if (arg.huge_deficency < mConfigure.getHugeDeficiency())
    {
        huge_priority = 1;
        m_table_content.SetEntyColor(arg.line, ID_TABLE_CONTENT_COLUMN_HUGE, ID_COLOR_TEXT, ID_COLOR_BASIC_LEVER);
    }
    else if (arg.huge_deficency < mConfigure.getHugeDeficiencyB())
    {
        huge_priority = 2;
        m_table_content.SetEntyColor(arg.line, ID_TABLE_CONTENT_COLUMN_HUGE, ID_COLOR_TEXT, ID_COLOR_A_LEVER);
    }
    else if (arg.huge_deficency < mConfigure.getHugeDeficiencyC())
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
    else if (arg.mid_deficency < mConfigure.getMidDeficiency())
    {
        mid_priority = 1;
        m_table_content.SetEntyColor(arg.line, ID_TABLE_CONTENT_COLUMN_MID, ID_COLOR_TEXT, ID_COLOR_BASIC_LEVER);
    }
    else if (arg.mid_deficency < mConfigure.getMidDeficiencyB())
    {
        mid_priority = 2;
        m_table_content.SetEntyColor(arg.line, ID_TABLE_CONTENT_COLUMN_MID, ID_COLOR_TEXT, ID_COLOR_A_LEVER);
    }
    else if (arg.mid_deficency < mConfigure.getMidDeficiencyC())
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
    else if (arg.tiny_deficency < mConfigure.getTinyDeficiency())
    {
        tiny_priority = 1;
        m_table_content.SetEntyColor(arg.line, ID_TABLE_CONTENT_COLUMN_TINY, ID_COLOR_TEXT, ID_COLOR_BASIC_LEVER);
    }
    else if (arg.tiny_deficency < mConfigure.getTinyDeficiencyB())
    {
        tiny_priority = 2;
        m_table_content.SetEntyColor(arg.line, ID_TABLE_CONTENT_COLUMN_TINY, ID_COLOR_TEXT, ID_COLOR_A_LEVER);
    }
    else if (arg.tiny_deficency < mConfigure.getTinyDeficiencyC())
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
    else if (arg.iron_tramp < mConfigure.getIronTramp())
    {
        iron_priority = 1;
        m_table_content.SetEntyColor(arg.line, ID_TABLE_CONTENT_COLUMN_IRON, ID_COLOR_TEXT, ID_COLOR_BASIC_LEVER);
    }
    else if (arg.iron_tramp < mConfigure.getIronTrampB())
    {
        iron_priority = 2;
        m_table_content.SetEntyColor(arg.line, ID_TABLE_CONTENT_COLUMN_IRON, ID_COLOR_TEXT, ID_COLOR_A_LEVER);
    }
    else if (arg.iron_tramp < mConfigure.getIronTrampC())
    {
        iron_priority = 3;
        m_table_content.SetEntyColor(arg.line, ID_TABLE_CONTENT_COLUMN_IRON, ID_COLOR_TEXT, ID_COLOR_B_LEVER);
    }
    else
    {
        iron_priority = 4;
        m_table_content.SetEntyColor(arg.line, ID_TABLE_CONTENT_COLUMN_IRON, ID_COLOR_TEXT, ID_COLOR_C_LEVER);
    }
}

void CR823_TVolQuery::SetRangeColor(record_item arg, int arg_priority)
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

void CR823_TVolQuery::onSelect()
{
    int i;
}


void CR823_TVolQuery::onFirstSelect()
{
    char chconf[MAX_PATH] = {0};
    int cul = m_record.GetCurSel();
    POSITION Tailpos = list.GetHeadPosition();
    for (int i = 0;i<cul;i++)
    {
        list.GetNext(Tailpos);
    }
    CString str = list.GetNext(Tailpos);
    WideCharToMultiByte(CP_ACP, 0,  str.GetBuffer(), -1, chconf, sizeof(chconf), NULL, NULL);
    updateRecord(chconf);
}

void CR823_TVolQuery::onExport()
{
    mExcel.init();
    mExcel.SetPath(m_spath);
    CStringArray list;
    if (m_ExportSetting & ID_EXPORT_ID_CHECKED)
    {
        list.Add(ID_TABLE_SEQID);
    }

    if (m_ExportSetting & ID_EXPORT_TINY_CHECKED)
    {
        list.Add(ID_TABLE_TINY_DEFICIENCY);
    }

    if (m_ExportSetting & ID_EXPORT_MID_CHECKED)
    {
        list.Add(ID_TABLE_MID_DEFICIENCY);
    }

    if (m_ExportSetting & ID_EXPORT_HUGE_CHECKED)
    {
        list.Add(ID_TABLE_HUGE_DEFICIENCY);
    }

    if (m_ExportSetting & ID_EXPORT_IRON_CHECKED)
    {
        list.Add(ID_TABLE_IRON_TRAMP);
    }

    if (m_ExportSetting & ID_EXPORT_RANGE_CHECKED)
    {
        list.Add(ID_TABLE_VOL_IDENTIFICATION);
    }
    mExcel.AddRow(&list);
    list.RemoveAll();
    for (int i = 0; i < m_table_content.GetRowCount(); i++)
    {
        for (int j = 0;j < m_table_content.GetColumnCount(); j++)
        {
            if ((j == 0) && (m_ExportSetting & ID_EXPORT_ID_CHECKED))
            {
                list.Add(m_table_content.GetItemText(i, j));
                
            }

            if ((j == 1) && (m_ExportSetting & ID_EXPORT_TINY_CHECKED))
            {
                list.Add(m_table_content.GetItemText(i, j));
            }

            if ((j == 2) && (m_ExportSetting & ID_EXPORT_MID_CHECKED))
            {
                list.Add(m_table_content.GetItemText(i, j));
            }

            if ((j == 3) && (m_ExportSetting & ID_EXPORT_HUGE_CHECKED))
            {
                list.Add(m_table_content.GetItemText(i, j));
            }

            if ((j == 4) && (m_ExportSetting & ID_EXPORT_IRON_CHECKED))
            {
                list.Add(m_table_content.GetItemText(i, j));
            }

            if ((j == 5) && (m_ExportSetting & ID_EXPORT_RANGE_CHECKED))
            {
                list.Add(m_table_content.GetItemText(i, j));
            }
        }
		mExcel.AddRow(&list);
        list.RemoveAll();
    }
    mExcel.CreateExcel();
}