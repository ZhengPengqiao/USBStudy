// CH341PAR.h : main header file for the CH341PAR application
//

#if !defined(AFX_CH341PAR_H__BA8EDDAD_99F0_4548_AAF9_5CFF36B45429__INCLUDED_)
#define AFX_CH341PAR_H__BA8EDDAD_99F0_4548_AAF9_5CFF36B45429__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCH341PARApp:
// See CH341PAR.cpp for the implementation of this class
//

class CCH341PARApp : public CWinApp
{
public:
	CCH341PARApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCH341PARApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCH341PARApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CH341PAR_H__BA8EDDAD_99F0_4548_AAF9_5CFF36B45429__INCLUDED_)
