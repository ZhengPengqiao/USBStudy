// MemPage.cpp : implementation file
//

#include "stdafx.h"
#include "Total.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMemPage property page

IMPLEMENT_DYNCREATE(CMemPage, CPropertyPage)

CMemPage::CMemPage() : CPropertyPage(CMemPage::IDD)
{
	//{{AFX_DATA_INIT(CMemPage)
	m_memdata0 = _T("");
	m_memdata1 = _T("");
	m_memlen0 = _T("");
	m_memlen1 = _T("");
	//}}AFX_DATA_INIT
}

CMemPage::~CMemPage()
{
}

void CMemPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMemPage)
	DDX_Text(pDX, IDC_EDIT_MEMDATA0, m_memdata0);
	DDX_Text(pDX, IDC_EDIT_MEMDATA1, m_memdata1);
	DDX_Text(pDX, IDC_EDIT_MEMLEN0, m_memlen0);
	DDX_Text(pDX, IDC_EDIT_MEMLEN1, m_memlen1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMemPage, CPropertyPage)
	//{{AFX_MSG_MAP(CMemPage)
	ON_BN_CLICKED(IDC_BUTTON_MEMREAD0, OnButtonMemread0)
	ON_BN_CLICKED(IDC_BUTTON_MEMWRITE0, OnButtonMemwrite0)
	ON_BN_CLICKED(IDC_BUTTON_MEMREAD1, OnButtonMemread1)
	ON_BN_CLICKED(IDC_BUTTON_MEMWRITE1, OnButtonMemwrite1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMemPage message handlers

void CMemPage::OnButtonMemread0()   //MEM��ʽ����ַ0
{
	UCHAR mBuf[mMAX_BUFFER_LENGTH]="";
	ULONG mLen=0;
	UpdateData(TRUE);
	mLen = p_Dlg->mStrToBcd(m_memlen0);
	if(mLen <= 0)
	{
		MessageBox("����������ݳ���","CH341",MB_OK);
		return;
	}
	if(p_Dlg->m_open)
	{
		try
		{
			if(!CH341MemReadAddr0(p_Dlg->mIndex, &mBuf[0], &mLen ))
			{   m_memlen0.Format("%x",  0);
				MessageBox("MEM��ʽ����ַ0ʧ�ܣ� ","CH341",MB_OK|MB_ICONSTOP);
			}
			else
			{
				CHAR buffer[mMAX_BUFFER_LENGTH * 3]="";
				ULONG i,j=0;
				for(i=0; i<mLen;i++)
				{
					sprintf(&buffer[j],"%2x ",mBuf[i]);    //��λʮ����������һ���ո�
					if (mBuf[i]<16 )                      //һλʮ�������ַ�ǰ���0
						buffer[j]=48;    				
					if (buffer[j]>=97 && buffer[j]<=122) //Сд��ĸתΪ��д��ĸ
                        buffer[j]=buffer[j]-32;
					if (buffer[j+1]>=97 && buffer[j+1]<=122) //Сд��ĸתΪ��д��ĸ
						buffer[j+1]=buffer[j+1]-32;
					j += 3;	
				}
				buffer[j] = '\0';
				m_memdata0 = _T(buffer);
				m_memlen0.Format("%x",  mLen);
				
			}
		}
		catch( CException * )
		{
			TRACE("Error: %d",GetLastError());
		}
	}
	else
	{
		MessageBox("�豸δ�򿪣�","CH341",MB_OK|MB_ICONSTOP);
	}
	UpdateData(FALSE);
}

void CMemPage::OnButtonMemwrite0()		//MEM��ʽд��ַ0
{
	UCHAR mBuf[mMAX_BUFFER_LENGTH*2]="";
	UCHAR buffer[mMAX_BUFFER_LENGTH]="";
	ULONG mLen=0;
	UpdateData(TRUE);
	mLen =p_Dlg->mStrToBcd(m_memlen0);
	

	if(mLen <= 0 || strlen(m_memdata0) == 0)
	{
		MessageBox("������д���ݺͳ���","CH341",MB_OK);
		return;
	}
	if(mLen > strlen(m_memdata0)/2)
		mLen = strlen(m_memdata0)/2;
	memcpy(mBuf,m_memdata0,mLen*2);
	memcpy(buffer, p_Dlg->mStrtoVal(&mBuf[0],mLen*2),mLen);
	if(p_Dlg->m_open)
	{
		try
		{
			if(!CH341MemWriteAddr0( p_Dlg->mIndex, &buffer[0], &mLen ) )
			{   m_memlen0.Format("%x", 0);
				MessageBox("MEM��ʽд��ַ0ʧ�ܣ�","CH341",MB_OK|MB_ICONSTOP);
			}
			else
			{
				m_memlen0.Format("%x",  mLen);
				
			}
		}
		catch( CException * )
		{
			TRACE("Error: %d",GetLastError());
		}
	}
	else
	{
		MessageBox("�豸δ�򿪣�","CH341",MB_OK|MB_ICONSTOP);
	}
	UpdateData(FALSE);
}

void CMemPage::OnButtonMemread1()		//MEM��ʽ����ַ1
{
	UCHAR mBuf[mMAX_BUFFER_LENGTH]="";
	ULONG mLen=0;
	UpdateData(TRUE);
	mLen =p_Dlg->mStrToBcd(m_memlen1);
	
	if(mLen <= 0)
	{
		MessageBox("����������ݳ���","CH341",MB_OK);
		return;
	}

	if(p_Dlg->m_open)
	{
		if(!CH341MemReadAddr1(p_Dlg->mIndex, &mBuf[0], &mLen ))
		{   m_memlen1.Format("%x", 0);
			MessageBox("MEM��ʽ����ַ1ʧ�ܣ� ","CH341",MB_OK|MB_ICONSTOP);
		}
		else
		{
			CHAR buffer[mMAX_BUFFER_LENGTH * 3];
			ULONG i,j=0;
			for(i=0; i<mLen;i++)
			{
				sprintf(&buffer[j],"%2x ",mBuf[i]);    //��λʮ����������һ���ո�
				if (mBuf[i]<16 )                     //һλʮ�������ַ�ǰ���0
					buffer[j]=48;    			
				if (buffer[j]>=97 && buffer[j]<=122) //Сд��ĸתΪ��д��ĸ
					buffer[j]=buffer[j]-32;
				if (buffer[j+1]>=97 && buffer[j+1]<=122) //Сд��ĸתΪ��д��ĸ
					buffer[j+1]=buffer[j+1]-32;
				j += 3;	
			}
			buffer[j] = '\0';
			m_memdata1 = _T(buffer);
			m_memlen1.Format("%x",  mLen);
			
		}
	}
	else
	{
		MessageBox("�豸δ�򿪣�","CH341",MB_OK|MB_ICONSTOP);
	}UpdateData(FALSE);
}

void CMemPage::OnButtonMemwrite1()		//MEM��ʽд��ַ1
{
	UCHAR mBuf[mMAX_BUFFER_LENGTH*2]="";
	UCHAR buffer[mMAX_BUFFER_LENGTH]="";
	ULONG mLen=0;
	UpdateData(TRUE);
	mLen =p_Dlg->mStrToBcd(m_memlen1);	
	if(mLen <= 0 || strlen(m_memdata1) == 0)
	{
		MessageBox("������д���ݺͳ���","CH341",MB_OK);
		return;
	}
	
	if(mLen > strlen(m_memdata1)/2)
		mLen = strlen(m_memdata1)/2;
    memcpy(mBuf,m_memdata1,mLen*2);
	memcpy(buffer, p_Dlg->mStrtoVal(&mBuf[0],mLen*2),mLen);
	if(p_Dlg->m_open)
	{
		if(!CH341MemWriteAddr1( p_Dlg->mIndex, &buffer[0], &mLen ) )
		{   m_memlen1.Format("%x",  0);
			MessageBox("MEM��ʽд��ַ1ʧ�ܣ�","CH341",MB_OK|MB_ICONSTOP);
		}
		else
		{
			m_memlen1.Format("%x",  mLen);
			
		}
	}
	else
	{
		MessageBox("�豸δ�򿪣�","CH341",MB_OK|MB_ICONSTOP);
	}	UpdateData(FALSE);
}

BOOL CMemPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	p_Dlg->enablebtn(p_Dlg->m_open );  //��ʼ����ť

	return TRUE; 
}
