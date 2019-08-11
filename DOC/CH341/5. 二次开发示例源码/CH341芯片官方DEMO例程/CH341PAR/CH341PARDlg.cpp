// CH341PARDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Total.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


   CCtrlSheet * m_sheet;
	CEppPage m_epp;
	CMemPage m_mem;
	COtherPage m_other;
    CI2CSPage m_i2cs;
    CLEDBTDisp m_btdis;
	CEeprPage m_eeppromwr;
    ULONG inde;
	HWND mainhwnd;
	void CALLBACK CH341_NOTIFY_ROUTINE (ULONG	iEventStatus );  // 设备事件通知回调程序

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCH341PARDlg dialog

CCH341PARDlg::CCH341PARDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCH341PARDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCH341PARDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
//	p_Dlg = this;
}

void CCH341PARDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCH341PARDlg)
//	DDX_Control(pDX, IDOK, m_ok);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCH341PARDlg, CDialog)
	//{{AFX_MSG_MAP(CCH341PARDlg)
	ON_WM_DESTROY()
	ON_WM_KEYUP()
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCH341PARDlg message handlers

BOOL CCH341PARDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	mIndex = 0;  //打开的设备序号
	m_open = FALSE;  //设备打开标志

	if(CH341OpenDevice(mIndex) == INVALID_HANDLE_VALUE)
	{
		//MessageBox("请插上设备!","CH341PAR",MB_OK|MB_ICONSTOP);
		m_open = FALSE;		
	}	
	else
		m_open = true;
   
	m_sheet = new CCtrlSheet(_T("CH341EVT"));
	m_epp.p_Dlg = this;
	m_mem.p_Dlg = this;
	m_other.p_Dlg = this;
	m_i2cs.p_Dlg =this;
    m_btdis.p_Dlg =this;
	m_eeppromwr.p_Dlg =this;
	m_sheet->AddPage(&m_epp);
	m_sheet->AddPage(&m_mem);
	m_sheet->AddPage(&m_other);
	m_sheet->AddPage(&m_i2cs);
	m_sheet->AddPage(&m_eeppromwr);
	m_sheet->AddPage(&m_btdis);

	mainhwnd=GetSafeHwnd(); 
	CH341SetDeviceNotify(mIndex,NULL,CH341_NOTIFY_ROUTINE);   //注册监视通知
	
	m_sheet->DoModal();

	this->OnOK();
	return TRUE;  // return TRUE  unless you set the focus to a control
}


BOOL CCH341PARDlg::mClose()  //关闭CH341设备
{
	CH341CloseDevice(mIndex);
	m_open = FALSE;
	return TRUE;
}

void CCH341PARDlg::OnDestroy() 
{
	mClose();
	CH341SetDeviceNotify(mIndex,NULL,NULL);  //注销监视通知
	CDialog::OnDestroy();	
}



void CALLBACK CH341_NOTIFY_ROUTINE (  // 设备事件通知回调程序
	ULONG	iEventStatus)
{	//由于中断程序中不能对系统资源操作过多,所以插拔事件处理过程通过PostMessage()放到 CCH341PARDlg::OnKeyUp()过程中
	::PostMessage(mainhwnd,WM_KEYUP,iEventStatus,0);	
}

void CCH341PARDlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) //插拔事件过程
{	
	ULONG iEventStatus;
	iEventStatus=nChar;  //插拔事件
	
	if(iEventStatus==CH341_DEVICE_ARRIVAL){ // 设备插入事件,已经插入
		if(CH341OpenDevice(mIndex) == INVALID_HANDLE_VALUE)	{
			MessageBox("打开设备失败!","CH341PAR",MB_OK|MB_ICONSTOP);
			m_open = FALSE;
		}		
		else
			m_open = TRUE; //打开成功	
	}
	else if(iEventStatus==CH341_DEVICE_REMOVE){ // 设备拔出事件,已经拔出
		CH341CloseDevice(mIndex);
		m_open = FALSE;	
	}
	enablebtn(m_open); //设备打开,按钮可用,设备没打开,按钮禁用
}
//设置按钮是否可用
void CCH341PARDlg::enablebtn(BOOL bEnable)  //bEnable=true :able ;=false:enable
{
	::EnableWindow(::GetDlgItem(m_mem.GetSafeHwnd(), IDC_BUTTON_MEMREAD1), bEnable);
	::EnableWindow(::GetDlgItem(m_mem.GetSafeHwnd(), IDC_BUTTON_MEMWRITE1), bEnable);
	::EnableWindow(::GetDlgItem(m_mem.GetSafeHwnd(), IDC_BUTTON_MEMREAD0), bEnable);
	::EnableWindow(::GetDlgItem(m_mem.GetSafeHwnd(), IDC_BUTTON_MEMWRITE0), bEnable);
	
	::EnableWindow(::GetDlgItem(m_epp.GetSafeHwnd(), IDC_BUTTON_EPPREAD0), bEnable);
	::EnableWindow(::GetDlgItem(m_epp.GetSafeHwnd(), IDC_BUTTON_EPPWRITE0), bEnable);
	::EnableWindow(::GetDlgItem(m_epp.GetSafeHwnd(), IDC_BUTTON_EPPREAD1), bEnable);
	::EnableWindow(::GetDlgItem(m_epp.GetSafeHwnd(), IDC_BUTTON_EPPWRITE1), bEnable);
	
	::EnableWindow(::GetDlgItem(m_i2cs.GetSafeHwnd(), IDC_SEND), bEnable);

	::EnableWindow(::GetDlgItem(m_btdis.GetSafeHwnd(), IDC_BtRefresh), bEnable);

	::EnableWindow(::GetDlgItem(m_eeppromwr.GetSafeHwnd(), IDC_WrDate), bEnable);
	::EnableWindow(::GetDlgItem(m_eeppromwr.GetSafeHwnd(), IDC_RdDate), bEnable);

	::EnableWindow(::GetDlgItem(m_other.GetSafeHwnd(), IDC_BUTTON_I2CREAD), bEnable);
	::EnableWindow(::GetDlgItem(m_other.GetSafeHwnd(), IDC_BUTTON_I2CWRITE), bEnable);	
   
	if(m_btdis.formshow==TRUE && bEnable)  //数字I/O窗口已初始化,刷新LED,按拔码开关状态
	{
		m_btdis.OnCheck8(); 
		m_btdis.OnBtRefresh();
	}

	if(bEnable)  //窗体标题显示
		m_sheet->SetWindowText("CH341EVT **设备已插上");
	else
		m_sheet->SetWindowText("CH341EVT **设备已拔出");

}

UCHAR CCH341PARDlg::mCharToBcd(UCHAR iChar)
{
	UCHAR	mBCD;
	if ( iChar >= '0' && iChar <= '9' ) mBCD = iChar -'0';
	else if ( iChar >= 'A' && iChar <= 'F' ) mBCD = iChar - 'A' + 0x0a;
	else if ( iChar >= 'a' && iChar <= 'f' ) mBCD = iChar - 'a' + 0x0a;
	else mBCD = 0x00;
	return( mBCD );
}

PUCHAR CCH341PARDlg::mStrtoVal(PUCHAR str, ULONG strlen)
{
	ULONG i,j;
	ULONG len;
	UCHAR strRev[mMAX_BUFFER_LENGTH];
	if( strlen % 2 != 0 )
	{  	str[strlen] = 0;
		strlen += 1;
	}
	len = strlen / 2;
	for(i=0,j=0;j<len;i++,j++)
	{
		strRev[j] = (UCHAR)((mCharToBcd(str[i])<<4) + mCharToBcd(str[i+1]));
		i++;
	}
	strRev[j]='\0';
	memcpy(  str,strRev,len);
	return str;
}
ULONG CCH341PARDlg::mStrToBcd(CString str)
{   char mlen,i=0;
	UCHAR iChar=0,Char[9]="";
	UINT mBCD=0,de=1;
    mlen=strlen(str);
    memcpy(Char,str,mlen);
	for(i=mlen-1;i>=0;i--)
	{	iChar=Char[i];
		if ( iChar >= '0' && iChar <= '9' )
			mBCD = mBCD+(iChar -'0')*de;
		else if ( iChar >= 'A' && iChar <= 'F' ) 
			mBCD =mBCD+ (iChar - 'A' + 0x0a)*de;
		else if ( iChar >= 'a' && iChar <= 'f' )
			mBCD =mBCD+ (iChar - 'a' + 0x0a)*de;
		else return(0);
		de*=16;
	}
	    return(mBCD);
}