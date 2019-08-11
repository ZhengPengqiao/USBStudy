// OtherPage.cpp : implementation file
//

#include "stdafx.h"
#include "Total.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COtherPage property page

IMPLEMENT_DYNCREATE(COtherPage, CPropertyPage)

COtherPage::COtherPage() : CPropertyPage(COtherPage::IDD)
{
	//{{AFX_DATA_INIT(COtherPage)
	m_data = _T("");
	m_dataaddr = _T("");
	m_devaddr = _T("50");
	//}}AFX_DATA_INIT
}

COtherPage::~COtherPage()
{
}

void COtherPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COtherPage)
	DDX_Text(pDX, IDC_EDIT_I2CDATA, m_data);
	DDV_MaxChars(pDX, m_data, 2);
	DDX_Text(pDX, IDC_EDIT_I2CDATAADD, m_dataaddr);
	DDV_MaxChars(pDX, m_dataaddr, 2);
	DDX_Text(pDX, IDC_EDIT_I2CDEVADD, m_devaddr);
	DDV_MaxChars(pDX, m_devaddr, 2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COtherPage, CPropertyPage)
	//{{AFX_MSG_MAP(COtherPage)
	ON_BN_CLICKED(IDC_BUTTON_I2CREAD, OnButtonI2cread)
	ON_BN_CLICKED(IDC_BUTTON_I2CWRITE, OnButtonI2cwrite)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COtherPage message handlers

void COtherPage::OnButtonI2cread()		//读I2C
{
	UCHAR mData=0;
	UCHAR mDataAddr=0;
	UCHAR mDevAddr=0;
	UpdateData(TRUE);	
	if(strlen(m_dataaddr) == 0 )
	{
		MessageBox("请输入数据单元地址","CH341",MB_OK);
		return;
	}
	else if(strlen(m_devaddr) == 0)
	{
		MessageBox("请输入设备地址","CH341",MB_OK);
		return;
	}
	if(strlen(m_dataaddr) > 2 || strlen(m_devaddr) > 2)
	{
		MessageBox("设备地址和数据单元地址都应不大于十六进制FFH","CH341",MB_OK);
		return;
	}
    
	if(strlen(m_dataaddr) > 1)
	{
		mDataAddr = (p_Dlg->mCharToBcd(m_dataaddr.GetAt(0)) << 4) + (p_Dlg->mCharToBcd(m_dataaddr.GetAt(1)));
	}
	else 
	{
		mDataAddr = p_Dlg->mCharToBcd(m_dataaddr.GetAt(0));
	}
	if(strlen(m_devaddr) > 1)
	{
		mDevAddr = (p_Dlg->mCharToBcd(m_devaddr.GetAt(0)) << 4) + (p_Dlg->mCharToBcd(m_devaddr.GetAt(1)));
	}
	else
	{
		mDevAddr = p_Dlg->mCharToBcd(m_devaddr.GetAt(0));
	}
	if(p_Dlg->m_open)
	{
		if( !CH341ReadI2C( p_Dlg->mIndex, mDevAddr, mDataAddr, &mData ) )
		{
			MessageBox("I2C读数据失败！","CH341",MB_OK|MB_ICONSTOP);
		}
		else
		{
			CHAR mtemp[4]="";		
			sprintf(&mtemp[0],"%2X",mData);    //两位十六进制数加一个空格
			m_data=mtemp;		
			UpdateData(false);		
		}
	}
	else
	{
		MessageBox("设备未打开！","CH341",MB_OK|MB_ICONSTOP);
	}
	UpdateData(false);
}

void COtherPage::OnButtonI2cwrite()			//写I2C
{
	UCHAR mData;
	UCHAR mDataAddr;
	UCHAR mDevAddr;
	UpdateData(TRUE);
	
	if(strlen(m_dataaddr) == 0 || strlen(m_devaddr) == 0 || strlen(m_data) == 0)
	{
		MessageBox("请输入设备地址、数据单元地址和数据","CH341",MB_OK);
		return;
	}
	if(strlen(m_dataaddr) > 2 || strlen(m_devaddr) > 2 || strlen(m_data) > 2)
	{
		MessageBox("设备地址、数据单元地址和待写入数据都应不大于十六进制FFH","CH341",MB_OK);
		return;
	}
	
	if(strlen(m_dataaddr) > 1)
	{
		mDataAddr = (p_Dlg->mCharToBcd(m_dataaddr.GetAt(0)) << 4) + (p_Dlg->mCharToBcd(m_dataaddr.GetAt(1)));
	}
	else
	{
		mDataAddr = p_Dlg->mCharToBcd(m_dataaddr.GetAt(0));
	}
	if(strlen(m_devaddr) > 1)
	{
		mDevAddr = (p_Dlg->mCharToBcd(m_devaddr.GetAt(0)) << 4) + (p_Dlg->mCharToBcd(m_devaddr.GetAt(1)));
	}
	else
	{
		mDevAddr = p_Dlg->mCharToBcd(m_devaddr.GetAt(0));
	}
	if(strlen(m_data) > 1)
	{
		mData = (p_Dlg->mCharToBcd(m_data.GetAt(0)) << 4) + (p_Dlg->mCharToBcd(m_data.GetAt(1)));
	}
	else
	{
		mData = p_Dlg->mCharToBcd(m_data.GetAt(0));
	}
	if(p_Dlg->m_open)
	{
		if(!CH341WriteI2C( p_Dlg->mIndex, mDevAddr, mDataAddr, mData))
		{
			MessageBox("I2C写数据失败！","CH341",MB_OK|MB_ICONSTOP);
		}
		else
		{
			MessageBox("I2C写数据成功！","CH341",MB_OK);			
		} 
	}
	else
	{
		MessageBox("设备未打开！","CH341",MB_OK|MB_ICONSTOP);
	}
}


BOOL COtherPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	p_Dlg->enablebtn(p_Dlg->m_open );    //初始化按钮

	return TRUE;  
}
