#if !defined(AFX_LEDBTDISP_H__A6F4744C_ACE0_4FF0_B449_AEED0ED575A4__INCLUDED_)
#define AFX_LEDBTDISP_H__A6F4744C_ACE0_4FF0_B449_AEED0ED575A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LEDBTDisp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLEDBTDisp dialog

class CLEDBTDisp : public CPropertyPage
{
	DECLARE_DYNCREATE(CLEDBTDisp)
     bool CLEDBTDisp::MemWriteDate(void);//向并口用MEM方式发送一个数据
//	 void CLEDBTDisp::OnSendLEDval();    //发送LED状态值
// Construction
public:
	BOOL m_open;
	UINT temx;
	BOOL formshow;
    ULONG mIndex;

	CLEDBTDisp();
	~CLEDBTDisp();
	CCH341PARDlg * p_Dlg;

	void OnCheck8();
	void OnBtRefresh();	
	virtual BOOL OnInitDialog();

// Dialog Data
	//{{AFX_DATA(CLEDBTDisp)
	enum { IDD = IDD_DLGBtDisp };
	int		m_add0;
	BOOL		m_nbt1val;
	BOOL		m_nbt2val;
	BOOL		m_nbt3val;
	BOOL		m_nbt4val;
	BOOL		m_nbt5val;
	BOOL		m_nbt6val;
	BOOL		m_nbt7val;
	BOOL		m_nbt8val;
	BOOL	m_led1val;
	BOOL	m_led2val;
	BOOL	m_led3val;
	BOOL	m_led4val;
	BOOL	m_led5val;
	BOOL	m_led6val;
	BOOL	m_led7val;
	BOOL	m_led8val;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CLEDBTDisp)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CLEDBTDisp)
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	afx_msg void OnCheck3();
	afx_msg void OnCheck4();
	afx_msg void OnCheck5();
	afx_msg void OnCheck6();
	afx_msg void OnCheck7();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEDBTDISP_H__A6F4744C_ACE0_4FF0_B449_AEED0ED575A4__INCLUDED_)
