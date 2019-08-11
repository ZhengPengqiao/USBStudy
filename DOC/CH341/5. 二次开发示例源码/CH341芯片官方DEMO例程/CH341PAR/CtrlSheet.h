#if !defined(AFX_CTRLSHEET_H__E4B21F55_9B55_4BC5_9CFA_6BCD1FAC4F58__INCLUDED_)
#define AFX_CTRLSHEET_H__E4B21F55_9B55_4BC5_9CFA_6BCD1FAC4F58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CtrlSheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCtrlSheet

class CCtrlSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CCtrlSheet)

// Construction
public:
	CCtrlSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CCtrlSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
   
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCtrlSheet)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL
	
// Implementation
public:
	virtual ~CCtrlSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCtrlSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CTRLSHEET_H__E4B21F55_9B55_4BC5_9CFA_6BCD1FAC4F58__INCLUDED_)
