// LEDBTDisp.cpp : implementation file
//

#include "stdafx.h"
#include "Total.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLEDBTDisp property page

IMPLEMENT_DYNCREATE(CLEDBTDisp, CPropertyPage)

CLEDBTDisp::CLEDBTDisp() : CPropertyPage(CLEDBTDisp::IDD)
{
	//{{AFX_DATA_INIT(CLEDBTDisp)
	m_add0 = 0;
	m_nbt1val = FALSE;
	m_nbt2val = FALSE;
	m_nbt3val = FALSE;
	m_nbt4val = FALSE;
	m_nbt5val = FALSE;
	m_nbt6val = FALSE;
	m_nbt7val = FALSE;
	m_nbt8val = FALSE;
	m_led1val = FALSE;
	m_led2val = FALSE;
	m_led3val = FALSE;
	m_led4val = FALSE;
	m_led5val = FALSE;
	m_led6val = FALSE;
	m_led7val = FALSE;
	m_led8val = FALSE;
	formshow=FALSE;
	//}}AFX_DATA_INIT
}

CLEDBTDisp::~CLEDBTDisp()
{
}

void CLEDBTDisp::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLEDBTDisp)
	DDX_Radio(pDX, IDC_ADD0, m_add0);
	DDX_Check(pDX, IDC_CHECK9, m_nbt1val);
	DDX_Check(pDX, IDC_CHECK10, m_nbt2val);
	DDX_Check(pDX, IDC_CHECK11, m_nbt3val);
	DDX_Check(pDX, IDC_CHECK12, m_nbt4val);
	DDX_Check(pDX, IDC_CHECK13, m_nbt5val);
	DDX_Check(pDX, IDC_CHECK14, m_nbt6val);
	DDX_Check(pDX, IDC_CHECK15, m_nbt7val);
	DDX_Check(pDX, IDC_CHECK16, m_nbt8val);
	DDX_Check(pDX, IDC_CHECK1, m_led1val);
	DDX_Check(pDX, IDC_CHECK2, m_led2val);
	DDX_Check(pDX, IDC_CHECK3, m_led3val);
	DDX_Check(pDX, IDC_CHECK4, m_led4val);
	DDX_Check(pDX, IDC_CHECK5, m_led5val);
	DDX_Check(pDX, IDC_CHECK6, m_led6val);
	DDX_Check(pDX, IDC_CHECK7, m_led7val);
	DDX_Check(pDX, IDC_CHECK8, m_led8val);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLEDBTDisp, CPropertyPage)
	//{{AFX_MSG_MAP(CLEDBTDisp)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck4)
	ON_BN_CLICKED(IDC_CHECK5, OnCheck5)
	ON_BN_CLICKED(IDC_CHECK6, OnCheck6)
	ON_BN_CLICKED(IDC_CHECK7, OnCheck7)
	ON_BN_CLICKED(IDC_BtRefresh, OnBtRefresh)
	ON_BN_CLICKED(IDC_CHECK8, OnCheck8)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLEDBTDisp message handlers
bool CLEDBTDisp::MemWriteDate(void)
{ 
    UCHAR mBuf[1]="";
	UpdateData(true);
	mBuf[0]=(m_led1val<<7)|(m_led2val<<6)|(m_led3val<<5)|(m_led4val<<4)|
		    (m_led5val<<3)|(m_led6val<<2)|(m_led7val<<1)|(m_led8val<<0); //组合按钮键值;
	ULONG mLen=1;  //数据长度
	if(p_Dlg->m_open)
	{
		try
		{
			if (m_add0==0)  //用地址0方式发送数据
			{
				if(!CH341MemWriteAddr0( p_Dlg->mIndex, mBuf, &mLen ) )
				{
					//MessageBox("MEM写数据块0失败！","CH341",MB_OK|MB_ICONSTOP);
					return(false);
				}
			}
			else if(m_add0==1)  //用地址1方式发送数据
			{
				if(!CH341MemWriteAddr1( p_Dlg->mIndex, mBuf, &mLen ) )
				{
					//MessageBox("MEM写数据块1失败！","CH341",MB_OK|MB_ICONSTOP);
					return(false);
				}
			}
		}
			catch( CException * )
		{
			TRACE("Error: %d",GetLastError());
			return(false);
		}
	}
	else
	{
		MessageBox("设备未打开！","CH341",MB_OK|MB_ICONSTOP);
		return(false);
	}
    return(true);
}



void CLEDBTDisp::OnBtRefresh()
{   UCHAR mBuf[1]="";
	ULONG mLen=0;
	mLen =1;
	UpdateData(true);
	if(p_Dlg->m_open)
	{
		if (m_add0==0)
		{
			if(!CH341MemReadAddr0(p_Dlg->mIndex, &mBuf[0], &mLen ))
			{
				MessageBox("MEM地址方式0读组合按钮失败！ ","CH341",MB_OK|MB_ICONSTOP);
				return;
			}
		}
		else if(m_add0=1)
		{
			if(!CH341MemReadAddr1(p_Dlg->mIndex, &mBuf[0], &mLen ))
			{
				MessageBox("MEM地址方式1读组合按钮失败！ ","CH341",MB_OK|MB_ICONSTOP);
				return;
			}
		}
		//按钮状态显示
        if (!(mBuf[0]&1))
			m_nbt1val=TRUE;
		else
			m_nbt1val=FALSE;
		if (!(mBuf[0]& 2))
			m_nbt2val=TRUE;
		else
			m_nbt2val=FALSE;
		if (!(mBuf[0]& 4))
			m_nbt3val=TRUE;
		else
			m_nbt3val=FALSE;
		if (!(mBuf[0] &8))
			m_nbt4val=TRUE;
		else
			m_nbt4val=FALSE;
		if (!(mBuf[0]& 16))
			m_nbt5val=TRUE;
		else
			m_nbt5val=FALSE;
		if (!(mBuf[0]& 32))
			m_nbt6val=TRUE;
		else
			m_nbt6val=FALSE;
		if (!(mBuf[0]&64))
			m_nbt7val=TRUE;
		else
			m_nbt7val=FALSE;
		if (!(mBuf[0]&128))
			m_nbt8val=TRUE;
		else
			m_nbt8val=FALSE;
		UpdateData(false);		
	}
	else
	{
	//	MessageBox("设备未打开！","CH341",MB_OK|MB_ICONSTOP);
	}

}


BOOL CLEDBTDisp::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	p_Dlg->enablebtn(p_Dlg->m_open );  //初始化按钮

	formshow=TRUE;
	return TRUE;  
}

BOOL CLEDBTDisp::OnSetActive() 
{
  	if(p_Dlg->m_open)  //设备打开,在当前页被激活时刷新LED,按钮状态
	{
		CLEDBTDisp::OnCheck8(); 
		CLEDBTDisp::OnBtRefresh();
	}

	return CPropertyPage::OnSetActive();
}



void CLEDBTDisp::OnCheck1() 
{
if(p_Dlg->m_open)
{
if (MemWriteDate()==false)  //发LED状态
		MessageBox("发送LED状态值失败！","CH341",MB_OK|MB_ICONSTOP);
  
}
}

void CLEDBTDisp::OnCheck2() 
{
if(p_Dlg->m_open)
{
if (MemWriteDate()==false)  //发LED状态
		MessageBox("发送LED状态值失败！","CH341",MB_OK|MB_ICONSTOP);
  
}
}

void CLEDBTDisp::OnCheck3() 
{
if(p_Dlg->m_open)
{
if (MemWriteDate()==false)  //发LED状态
		MessageBox("发送LED状态值失败！","CH341",MB_OK|MB_ICONSTOP);
  
}
}

void CLEDBTDisp::OnCheck4() 
{
if(p_Dlg->m_open)
{
if (MemWriteDate()==false)  //发LED状态
		MessageBox("发送LED状态值失败！","CH341",MB_OK|MB_ICONSTOP);
  
}
	
}

void CLEDBTDisp::OnCheck5() 
{
if(p_Dlg->m_open)
{
if (MemWriteDate()==false)  //发LED状态
		MessageBox("发送LED状态值失败！","CH341",MB_OK|MB_ICONSTOP);
  
}
	
}

void CLEDBTDisp::OnCheck6() 
{
if(p_Dlg->m_open)
{
if (MemWriteDate()==false)  //发LED状态
		MessageBox("发送LED状态值失败！","CH341",MB_OK|MB_ICONSTOP);
  
}
	
}

void CLEDBTDisp::OnCheck7() 
{
if(p_Dlg->m_open)
{
if (MemWriteDate()==false)  //发LED状态
		MessageBox("发送LED状态值失败！","CH341",MB_OK|MB_ICONSTOP);
}
	
}

void CLEDBTDisp::OnCheck8() 
{
if(p_Dlg->m_open)
{
if (MemWriteDate()==false)  //发LED状态
		MessageBox("发送LED状态值失败！","CH341",MB_OK|MB_ICONSTOP);
 
}	
}

