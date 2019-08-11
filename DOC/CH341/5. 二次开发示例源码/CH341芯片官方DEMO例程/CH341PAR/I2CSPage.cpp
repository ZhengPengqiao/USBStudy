// I2CSPage.cpp : implementation file
//

#include "stdafx.h"
#include "Total.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CI2CSPage property page

IMPLEMENT_DYNCREATE(CI2CSPage, CPropertyPage)

CI2CSPage::CI2CSPage() : CPropertyPage(CI2CSPage::IDD)
{
	//{{AFX_DATA_INIT(CI2CSPage)
	m_srddatabuf = _T("");
	m_swrdatabuf = _T("");
	m_srddatalen = _T("");
	m_swrdatalen = _T("");
	//}}AFX_DATA_INIT
}

CI2CSPage::~CI2CSPage()
{
}

void CI2CSPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CI2CSPage)
	DDX_Text(pDX, IDC_EDIT_I2CSRDDATA, m_srddatabuf);
	DDX_Text(pDX, IDC_EDIT_I2CSWRDATA, m_swrdatabuf);
	DDX_Text(pDX, IDC_EDIT_I2CSRDLEN, m_srddatalen);
	DDX_Text(pDX, IDC_EDIT_I2CSWRLEN, m_swrdatalen);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CI2CSPage, CPropertyPage)
	//{{AFX_MSG_MAP(CI2CSPage)
	ON_BN_CLICKED(IDC_SEND, OnSend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CI2CSPage message handlers

void CI2CSPage::OnSend() 
{   
	UCHAR mwBuf[mMAX_BUFFER_LENGTH*2]="";
	char tembuf[mMAX_BUFFER_LENGTH*3]="";
	UCHAR wbuffer[mMAX_BUFFER_LENGTH]="";
	UCHAR rbuffer[mMAX_BUFFER_LENGTH]="";
	ULONG mwlen=0,mrlen=0;
	UpdateData(TRUE);
	mwlen = p_Dlg->mStrToBcd(m_swrdatalen);
	mrlen=p_Dlg->mStrToBcd(m_srddatalen);
	if (mwlen==0 && mrlen==0)
	{
		MessageBox("请输入长度","CH341",MB_OK);
		return;
	}
	
	else if(strlen(m_swrdatabuf) == 0 && (mwlen>0))
	{
		MessageBox("请输入要写入的数据","CH341",MB_OK);
		return;
	}
	else if(mrlen < 0 )
	{
		MessageBox("请输入读数据的长度","CH341",MB_OK);
		return;
	}	
	
	if (mwlen > strlen(m_swrdatabuf)/2)
		mwlen = strlen(m_swrdatabuf)/2;
	memcpy(mwBuf,m_swrdatabuf,mwlen*2);
	memcpy(wbuffer, p_Dlg->mStrtoVal(mwBuf,mwlen*2),mwlen);
	
	if(p_Dlg->m_open)
	{
		try
		{
			if(!CH341StreamI2C (p_Dlg->mIndex, mwlen, &wbuffer[0], mrlen, &rbuffer[0] ))
			{   
				m_swrdatalen.Format("%x", 0);
				m_srddatalen.Format("%x", 0);     //返回已读写的数据个数
				MessageBox("流模式读写数据失败！","CH341",MB_OK|MB_ICONSTOP);
			}
			else   //发送成功
			{
				m_swrdatalen.Format("%x", mwlen);
				m_srddatalen.Format("%x", mrlen);     //返回已读写的数据个数
				UINT i=0,j=0;
				for(i=0; i<mrlen;i++)
				{   
					sprintf(&tembuf[j],"%2x ",rbuffer[i]);    //两位十六进制数加一个空格
					if (rbuffer[i]<16 )                      //一位十六进制字符前面加0
						tembuf[j]=48;    
					if (tembuf[j]>=97 && tembuf[j]<=122) //小写字母转为大写字母
                        tembuf[j]=tembuf[j]-32;
					if (tembuf[j+1]>=97 && tembuf[j+1]<=122) //小写字母转为大写字母
						tembuf[j+1]=tembuf[j+1]-32;
					j += 3;
				}
				m_srddatabuf=tembuf;
				
			}UpdateData(FALSE);
		}
		catch( CException * )
		{
			TRACE("Error: %d",GetLastError());
		}
	}
	else
	{
		MessageBox("设备未打开！","CH341",MB_OK|MB_ICONSTOP);
	}

}

BOOL CI2CSPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	p_Dlg->enablebtn(p_Dlg->m_open );   //初始化按钮

	return TRUE;
}