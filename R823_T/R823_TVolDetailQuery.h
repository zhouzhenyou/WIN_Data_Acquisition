// R823_TPreferenceDlg.h : header file
//

#pragma once

#include "R823_TQuery.h"

// CR823_TDlg dialog
class CR823_TVolDetailQuery : public CR823_TQuery
{
// Construction
public:
	CR823_TVolDetailQuery(CWnd* pParent = NULL);	// standard constructor
// Active on the Dialog
private:
// Implementation
    void SetRangeColor(record_item arg, int arg_priority);
    char chconf[MAX_PATH];
protected:

	// Generated message map functions
	virtual BOOL OnInitDialog();
    virtual void onSelect();
    virtual void onExport();
    virtual void onFirstSelect();
public:
    void updateRecord(char* arg);
    void AddItem(record_item arg);
    void CheckRange(record_item arg);

};
