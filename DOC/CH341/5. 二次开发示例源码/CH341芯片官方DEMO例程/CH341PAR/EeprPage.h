#if !defined(AFX_EEPRPAGE_H__BC66D2D0_60AA_476E_803B_ECC4EF2373E8__INCLUDED_)
#define AFX_EEPRPAGE_H__BC66D2D0_60AA_476E_803B_ECC4EF2373E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EeprPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEeprPage dialog

class CEeprPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CEeprPage)

// Construction
public:
	CEeprPage();
	~CEeprPage();
    ULONG mIndex;
	CCH341PARDlg * p_Dlg;
	BOOL m_open;
	_EEPROM_TYPE CEeprPage::etype(int EppSelId);
// Dialog Data
	//{{AFX_DATA(CEeprPage)
	enum { IDD = IDD_EEPROMRW };
	CString	m_rddataaddr;
	CString	m_rddatabuf;
	CString	m_rddatalen;
	CString	m_wrdataaddr;
	CString	m_wrdatabuf;
	CString	m_wrdatalen;
	int		m_eepsel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CEeprPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CEeprPage)
	afx_msg void OnWrDate();
	afx_msg void OnRdDate();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EEPRPAGE_H__BC66D2D0_60AA_476E_803B_ECC4EF2373E8__INCLUDED_)
