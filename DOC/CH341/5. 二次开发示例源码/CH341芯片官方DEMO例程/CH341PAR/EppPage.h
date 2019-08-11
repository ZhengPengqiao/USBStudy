#if !defined(AFX_EPPPAGE_H__7431B9C5_C72E_4E12_9808_CFEA4DB6F14F__INCLUDED_)
#define AFX_EPPPAGE_H__7431B9C5_C72E_4E12_9808_CFEA4DB6F14F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EppPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEppPage dialog

class CEppPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CEppPage)

// Construction
public:
	ULONG mIndex;
	CCH341PARDlg * p_Dlg;
	BOOL m_open;
	CEppPage();
	~CEppPage();

// Dialog Data
	//{{AFX_DATA(CEppPage)
	enum { IDD = IDD_DLGEPP };
	CString	m_eppdata0;
	CString	m_eppdata1;
	CString	m_epplen0;
	CString	m_epplen1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CEppPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CEppPage)
	afx_msg void OnButtonEppread0();
	afx_msg void OnButtonEppwrite0();
	afx_msg void OnButtonEppread1();
	afx_msg void OnButtonEppwrite1();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EPPPAGE_H__7431B9C5_C72E_4E12_9808_CFEA4DB6F14F__INCLUDED_)
