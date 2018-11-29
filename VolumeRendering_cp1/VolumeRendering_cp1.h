
// VolumeRendering_cp1.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CVolumeRenderingApp:
// See VolumeRendering_cp1.cpp for the implementation of this class
//

class CVolumeRenderingApp : public CWinApp
{
public:
	CVolumeRenderingApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CVolumeRenderingApp theApp;