// CtrlSheet.cpp : implementation file
//

#include "stdafx.h"
#include "Total.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCtrlSheet

IMPLEMENT_DYNAMIC(CCtrlSheet, CPropertySheet)

CCtrlSheet::CCtrlSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{   	
}

CCtrlSheet::CCtrlSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CCtrlSheet::~CCtrlSheet()
{
//	CCH341PARDlg * pDlg ;
//	pDlg = new 
//	pDlg->EndDialog(0);
}


BEGIN_MESSAGE_MAP(CCtrlSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CCtrlSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCtrlSheet message handlers

BOOL CCtrlSheet::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();	
	return bResult;
}
