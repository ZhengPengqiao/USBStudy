#if !defined(AFX_I2CSPAGE_H__946D91A9_79D2_4CAE_9C09_D143E71BA1FC__INCLUDED_)
#define AFX_I2CSPAGE_H__946D91A9_79D2_4CAE_9C09_D143E71BA1FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// I2CSPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CI2CSPage dialog

class CI2CSPage : public CPropertyPage
{
DECLARE_DYNCREATE(CI2CSPage)
// Construction
public:
	ULONG mIndex;
	CCH341PARDlg * p_Dlg;
	BOOL m_open;
	CI2CSPage();
	~CI2CSPage();
// Dialog Data
	//{{AFX_DATA(CI2CSPage)
	enum { IDD = IDD_DLGI2C2 };
	CString	m_srddatabuf;
	CString	m_swrdatabuf;
	CString	m_srddatalen;
	CString	m_swrdatalen;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CI2CSPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CI2CSPage)
	afx_msg void OnSend();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_I2CSPAGE_H__946D91A9_79D2_4CAE_9C09_D143E71BA1FC__INCLUDED_)
