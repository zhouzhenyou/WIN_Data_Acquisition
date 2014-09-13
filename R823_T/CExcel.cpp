#include "CExcel.h"

CExcel::CExcel()
{
    isInit = FALSE;
    m_row_count = 0;
    m_column_count = 0;
}

BOOL CExcel::init()
{
    m_row_count = 0;
    isInit = app.CreateDispatch(_T("Excel.Application"));
    COleVariant covTrue((short)TRUE),covFalse((short)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND,VT_ERROR);

    books = app.get_Workbooks();
    book = books.Add(covOptional);
    sheets = book.get_Worksheets();

    return  isInit;
}

void CExcel::SetPath(CString arg)
{
    cStrFile = arg;
}

BOOL CExcel::CreateExcel()
{
    book.SaveCopyAs(COleVariant(cStrFile)); //保存到cStrFile文件  
    book.put_Saved(true);
    //book.ReleaseDispatch();
    //books.ReleaseDispatch();
    app.ReleaseDispatch();  
    app.Quit();
    return TRUE;
}

void CExcel::AddRow(CStringArray *plist)
{
    //USES_CONVERSION;
    sheet = sheets.get_Item(COleVariant((short)1));  //得到第一个工作表
    CString start,end;
    for (int iItem = 0; iItem < plist->GetCount(); iItem++)
    {
        start.Format(_T("%c%d"),65+iItem, m_row_count+1);
        end.Format(_T("%c%d"),65+iItem, m_row_count+1);
        range = sheet.get_Range(COleVariant(start),COleVariant(end));
        //COleVariant var;
        CString str = plist->GetAt(iItem);
        //char* pOut = new char[2*strlen(str.GetBuffer())];
        //WideCharToMultiByte(CP_ACP,NULL,&str,1,pOut,sizeof(WCHAR),NULL,NULL);
        //ConvertGBKToUtf8(str);
        //var.SetString(str, VT_BSTR);
        //_bstr_t bs=str;
        //COleVariant var(bs);
        //var.SetString(str, VT_BSTR);
        range.put_Value2(COleVariant(str)); //将得到的数据的saRet数组值放入表格_T(plist->GetAt(iItem)
        range.put_HorizontalAlignment(COleVariant((long)-4108));
        //interior = range.get_Interior();
        //interior.put_Color(VT(ID_COLOR_A_LEVER));
        //interior.ReleaseDispatch();
    }
    m_row_count++;
}

void CExcel::AddColumn(CStringList *plist)
{
    sheet = sheets.get_Item(COleVariant((short)1));  //得到第一个工作表 
    for (int iItem = 0; iItem < plist->GetCount(); iItem++)
    {
        range = sheet.get_Range(COleVariant(_T("A1")),COleVariant(_T("AD1")));
        range.put_Value2(COleVariant(_T("hanhan"))); //将得到的数据的saRet数组值放入表格
    }
    plist->GetCount();  
}

void CExcel::ConvertGBKToUtf8(CString& strGBK) 
{

} 

void UnicodeToUTF_8(char* pOut, WCHAR* pText)
{
    // 注意 WCHAR高低字的顺序,低字节在前，高字节在后
    char* pchar = (char *)pText;

    pOut[0] = (0xE0 | ((pchar[1] & 0xF0) >> 4));
    pOut[1] = (0x80 | ((pchar[1] & 0x0F) << 2)) + ((pchar[0] & 0xC0) >> 6);
    pOut[2] = (0x80 | (pchar[0] & 0x3F));

    return;
}

char* UnicodeToGB2312(const wchar_t* szUnicodeString)
{
    UINT nCodePage = 936; //GB2312
    int nLength=WideCharToMultiByte(nCodePage,0,szUnicodeString,-1,NULL,0,NULL,NULL);
    char* pBuffer=new char[nLength+1];
    WideCharToMultiByte(nCodePage,0,szUnicodeString,-1,pBuffer,nLength,NULL,NULL);
    pBuffer[nLength]=0;
    return pBuffer;
}