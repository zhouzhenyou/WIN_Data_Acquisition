// R823_T.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "Resource_Strings.h"

// CR823_TApp:
// See R823_T.cpp for the implementation of this class
//

class CR823_TApp : public CWinApp
{
public:
	CR823_TApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CR823_TApp theApp;