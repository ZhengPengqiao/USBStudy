#if !defined(AFX_MEMPAGE_H__0DBAC116_A791_46F4_9896_8CABF04797D6__INCLUDED_)
#define AFX_MEMPAGE_H__0DBAC116_A791_46F4_9896_8CABF04797D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MemPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMemPage dialog

class CMemPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CMemPage)

// Construction
public:
	ULONG mIndex;
	CCH341PARDlg * p_Dlg;
	BOOL m_open;
	CMemPage();
	~CMemPage();

// Dialog Data
	//{{AFX_DATA(CMemPage)
	enum { IDD = IDD_DLGMEM };
	CString	m_memdata0;
	CString	m_memdata1;
	CString	m_memlen0;
	CString	m_memlen1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMemPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMemPage)
	afx_msg void OnButtonMemread0();
	afx_msg void OnButtonMemwrite0();
	afx_msg void OnButtonMemread1();
	afx_msg void OnButtonMemwrite1();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEMPAGE_H__0DBAC116_A791_46F4_9896_8CABF04797D6__INCLUDED_)
