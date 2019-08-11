// EeprPage.cpp : implementation file
//

#include "stdafx.h"
#include "Total.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEeprPage property page

IMPLEMENT_DYNCREATE(CEeprPage, CPropertyPage)

CEeprPage::CEeprPage() : CPropertyPage(CEeprPage::IDD)
{
	//{{AFX_DATA_INIT(CEeprPage)
	m_rddataaddr = _T("");
	m_rddatabuf = _T("");
	m_rddatalen = _T("");
	m_wrdataaddr = _T("");
	m_wrdatabuf = _T("");
	m_wrdatalen = _T("");
	m_eepsel = 0;
	//}}AFX_DATA_INIT
}

CEeprPage::~CEeprPage()
{
}

void CEeprPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEeprPage)
	DDX_Text(pDX, IDC_RDateAddr, m_rddataaddr);
	DDV_MaxChars(pDX, m_rddataaddr, 6);
	DDX_Text(pDX, IDC_RDateBuf, m_rddatabuf);
	DDX_Text(pDX, IDC_RDateLen, m_rddatalen);
	DDV_MaxChars(pDX, m_rddatalen, 8);
	DDX_Text(pDX, IDC_WDateAddr, m_wrdataaddr);
	DDV_MaxChars(pDX, m_wrdataaddr, 6);
	DDX_Text(pDX, IDC_WDateBuf, m_wrdatabuf);
	DDX_Text(pDX, IDC_WDateLen, m_wrdatalen);
	DDV_MaxChars(pDX, m_wrdatalen, 8);
	DDX_Radio(pDX, IDC_RADIO1, m_eepsel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEeprPage, CPropertyPage)
	//{{AFX_MSG_MAP(CEeprPage)
	ON_BN_CLICKED(IDC_WrDate, OnWrDate)
	ON_BN_CLICKED(IDC_RdDate, OnRdDate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEeprPage message handlers

void CEeprPage::OnWrDate() 
{ 
	
	UCHAR mData=0;
	ULONG mDataAddr=0;	
	ULONG mLen=0;
	UCHAR mBuff[mMAX_BUFFER_LENGTH*2]="";
	UCHAR buffer[mMAX_BUFFER_LENGTH]="";
	UpdateData(TRUE);   
	mLen=p_Dlg->mStrToBcd(m_wrdatalen);
	if(strlen(m_wrdataaddr) == 0|| strlen(m_wrdatalen)==0)
	{
		MessageBox("请输入数据单元地址,长度","CH341",MB_OK);
		return;
	}	
	if(mLen > strlen(m_wrdatabuf)/2)  //在输入长度和数据长度中取小值
		mLen = strlen(m_wrdatabuf)/2;
	memcpy(mBuff,m_wrdatabuf,mLen*2);
	memcpy(buffer, p_Dlg->mStrtoVal(&mBuff[0],mLen*2),mLen);    ////m
	mDataAddr = p_Dlg->mStrToBcd(m_wrdataaddr);	
	if(p_Dlg->m_open)
	{ 	if( !CH341WriteEEPROM( p_Dlg->mIndex,etype(m_eepsel), mDataAddr,mLen,buffer ) )
	{       mLen=0;
			MessageBox("读E2PROM数据失败！","CH341",MB_OK|MB_ICONSTOP);
		}
		m_wrdatalen.Format("%X", mLen);	
	}
	else
	{
		MessageBox("设备未打开！","CH341",MB_OK|MB_ICONSTOP);
	}
	UpdateData(false);
	
}

void CEeprPage::OnRdDate() 
{   
	UCHAR mData=0;
	ULONG mDataAddr=0;	
	ULONG mlen=0;
	UCHAR mBuff[mMAX_BUFFER_LENGTH]="";
	UpdateData(TRUE);   
	mlen=p_Dlg->mStrToBcd(m_rddatalen);
	if(strlen(m_rddataaddr) == 0 )
	{
		MessageBox("请输入数据单元地址,长度","CH341",MB_OK);
		return;
	}	
		mDataAddr =p_Dlg->mStrToBcd(m_rddataaddr);
	if(p_Dlg->m_open)
	{ 	if( !CH341ReadEEPROM( p_Dlg->mIndex,etype(m_eepsel), mDataAddr,mlen,mBuff ) )
	{       m_rddatalen.Format("%x",0);
			MessageBox("读E2PROM数据失败！","CH341",MB_OK|MB_ICONSTOP);
		}
		else
		{	CHAR buffer[mMAX_BUFFER_LENGTH * 3];
			ULONG i,j=0;
			for(i=0; i<mlen;i++)
			{   
				sprintf(&buffer[j],"%2x ",mBuff[i]);    //两位十六进制数加一个空格
				if (mBuff[i]<16 )                     //一位十六进制字符前面加0
					buffer[j]=48;
				if (buffer[j]>=97 && buffer[j]<=122) //小写字母转为大写字母
					buffer[j]=buffer[j]-32;
				if (buffer[j+1]>=97 && buffer[j+1]<=122) //小写字母转为大写字母
					buffer[j+1]=buffer[j+1]-32;
				j += 3;	
			}
			buffer[j] = '\0';
			m_rddatabuf = _T(buffer);
			m_rddatalen.Format("%x", mlen);
			
		}
	}
	else
	{
		MessageBox("设备未打开！","CH341",MB_OK|MB_ICONSTOP);
	}
	UpdateData(false);
	
}

_EEPROM_TYPE CEeprPage::etype(int EppSelId)  //根据单选按纽,选择E2P器件型号
{
	_EEPROM_TYPE	iEepromID;
    switch(EppSelId)
	{
	case 0:
		iEepromID=ID_24C01;
		break;
	case 1:
		iEepromID=ID_24C02;
		break;
	case 2:
		iEepromID=ID_24C04;
		break;
	case 3:
		iEepromID=ID_24C08;
		break;
	case 4:
		iEepromID=ID_24C16;
		break;
	case 5:
		iEepromID=ID_24C32;
		break;
	case 6:
		iEepromID=ID_24C64;
		break;
	case 7:
		iEepromID=ID_24C128;
		break;
	case 8:
		iEepromID=ID_24C256;
		break;
	case 9:
		iEepromID=ID_24C512;
		break;
	case 10:
		iEepromID=ID_24C1024;
		break;
	case 11:
		iEepromID=ID_24C2048;
		break;
	case 12:
		iEepromID=ID_24C4096;
		break;
	default:
		iEepromID=ID_24C01;
		break;
	}
	return(iEepromID);
}

BOOL CEeprPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	p_Dlg->enablebtn(p_Dlg->m_open );    //初始化按钮

	return TRUE;  
}
