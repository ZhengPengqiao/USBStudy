#if !defined(AFX_OTHERPAGE_H__DDA810B7_F37F_47EB_8D2E_3FB5F0100165__INCLUDED_)
#define AFX_OTHERPAGE_H__DDA810B7_F37F_47EB_8D2E_3FB5F0100165__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OtherPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COtherPage dialog

class COtherPage : public CPropertyPage
{
	DECLARE_DYNCREATE(COtherPage)

// Construction
public:
	ULONG mIndex;
	CCH341PARDlg * p_Dlg;
	BOOL m_open;
	COtherPage();
	~COtherPage();

// Dialog Data
	//{{AFX_DATA(COtherPage)
	enum { IDD = IDD_DLGOTHER };
	CString	m_data;
	CString	m_dataaddr;
	CString	m_devaddr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(COtherPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(COtherPage)
	afx_msg void OnButtonI2cread();
	afx_msg void OnButtonI2cwrite();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OTHERPAGE_H__DDA810B7_F37F_47EB_8D2E_3FB5F0100165__INCLUDED_)
