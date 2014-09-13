#ifndef CEXCEL_H_
#define CEXCEL_H_

#include "stdafx.h"
#include "ColumnColorListCtrl.h"
#include "CApplication.h"
#include "CRange.h"
#include "CWorkbook.h"
#include "CWorksheet.h"
#include "CWorkbooks.h"
#include "CWorksheets.h"
#include "Cnterior.h"

#define VT(x)   _variant_t(x)

class CExcel
{
public:
    CExcel();
    BOOL init();
    void SetPath(CString arg);
    BOOL CreateExcel();
    void AddRow(CStringArray *plist);
    void AddColumn(CStringList *plist);
    void ConvertGBKToUtf8(CString& strGBK);
    void UnicodeToUTF_8(char* pOut, WCHAR* pText);
private:
    BOOL isInit;
    CString cStrFile;
    CApplication app; //Excel程序  
    CWorkbooks books; //工作簿集合  
    CWorkbook book;  //工作表  
    CWorksheets sheets;  //工作簿集合  
    CWorksheet sheet; //工作表集合  
    CRange range; //使用区域 
    Cnterior interior;
    int m_row_count;
    int m_column_count;
};

#endif