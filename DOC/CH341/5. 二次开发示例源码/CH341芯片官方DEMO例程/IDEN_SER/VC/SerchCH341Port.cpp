// SerchCH341Port.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include <stdio.h>
#include "CH341PT.H"
#pragma comment (lib,"CH341PT")



char ch341sername[10]="";   //存储监测到的已插入的串口名
HANDLE serhandle=NULL;      
HWND afxwndhwnd;
// Foward declarations of functions included in this code module:
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
PCHAR searchch341port(PLONG count);  
void CH341SerNotifyFunc(LONG iDevIndexAndEvent);

void CALLBACK CH341PT_NOTIFY_ROUTINE(LONG iDevIndexAndEvent);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	return DialogBox(hInstance, (LPCTSTR)IDD_main, 0, (DLGPROC)WndProc);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	CHAR tem[100]="";
	LONG index=0,j=0;
	PCHAR str=NULL;
	UCHAR portname[10]="";
    UCHAR fullportname[10]="";
    afxwndhwnd=hWnd;
	LONG iDevIndexAndEvent;
	switch (message) 
	{
		case WM_INITDIALOG:
			ltoa(CH341PtGetVersion(),tem,10);
			SetDlgItemText(hWnd,IDC_dllver,tem);
			break;
		case WM_COMMAND:
			wmId    = LOWORD(wParam);
			wmEvent = HIWORD(wParam);	
			// Parse the menu selections:
			switch (wmId)
			{
			    //串口全名格式为"////.//COMxx",大于com9的串口号必须要用串口全名,否则打不开"
				case IDC_CH341PtHandleIsCH341:  //通过串口特征数据来识别CH341串口
					HANDLE porthandle;
					SendDlgItemMessage(hWnd,IDC_show,LB_ADDSTRING,0,(LONG)"通过名称找到CH341串口为");
					 for (j=1;j<21;j++) {
						sprintf((CHAR *)portname,"COM%d\0",j);                 //设备名
						sprintf((CHAR *)fullportname,"\\\\.\\%s\0",portname);  //完整的设备名
						porthandle=CreateFile((CHAR *)fullportname,
							        GENERIC_READ | GENERIC_WRITE,              // 打开设备,支持重叠操作
									FILE_SHARE_READ | FILE_SHARE_WRITE,
									NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL );
						if ( porthandle != INVALID_HANDLE_VALUE ){
							if(CH341PtHandleIsCH341(porthandle))
								SendDlgItemMessage(hWnd,IDC_show,LB_ADDSTRING,0,(LONG)portname);
							CloseHandle(porthandle);
						}
					 }
				   break;
				case IDC_CH341PtNameIsCH341:
					SendDlgItemMessage(hWnd,IDC_show,LB_ADDSTRING,0,(LONG)"通过句柄找到CH341串口为:");	
                    for (j=1;j<21;j++) {
						sprintf((CHAR *)portname,"COM%d\0",j);                 //设备名
						sprintf((CHAR *)fullportname,"\\\\.\\%s\0",portname);  //完整的设备名
						if(CH341PtNameIsCH341(fullportname)){							
							SendDlgItemMessage(hWnd,IDC_show,LB_ADDSTRING,0,(LONG)portname);	
						}
					}
                    break;

				case IDC_beginmonitor:
					if(CH341PtSetDevNotify(NULL,CH341PT_NOTIFY_ROUTINE))
						SendDlgItemMessage(hWnd,IDC_show,LB_ADDSTRING,0,(LONG)"开始监视CH341串口插拔");	
					else
						SendDlgItemMessage(hWnd,IDC_show,LB_ADDSTRING,0,(LONG)"设置CH341串口监视失败");	
					break;
				case IDC_stopmonitor:
					if(CH341PtSetDevNotify(NULL,NULL))
						SendDlgItemMessage(hWnd,IDC_show,LB_ADDSTRING,0,(LONG)"停止监视CH341串口插拔");	
					break;
				case IDC_clear:
					SendDlgItemMessage(hWnd,IDC_show,LB_RESETCONTENT,0,0);				
					break;
				case WM_DESTROY:
					CH341PtSetDevNotify(NULL,NULL);   //防止在关闭前没有取消串口插拔监视
					PostQuitMessage(0);
					break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_KEYUP: //模拟设备插拔事件
			iDevIndexAndEvent=wParam;  //从中断程序中传来的串口号
			CH341SerNotifyFunc(iDevIndexAndEvent); //调用插拔事件处理程序
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
   }
   return 0;
}


void CALLBACK CH341PT_NOTIFY_ROUTINE(LONG iDevIndexAndEvent)
{  
	//在中断回调函数中,不能对系统资源操作过多.通过窗体WM_KEYUP事件来模拟插拔事件
	PostMessage(afxwndhwnd,WM_KEYUP,iDevIndexAndEvent,0); 
}

void  CH341SerNotifyFunc(LONG iDevIndexAndEvent) {
	char fullportname[10]="";
	char tem[50]="";
	char portname[10]="";
	if(iDevIndexAndEvent>0){  //ch341串口已插上
		sprintf(portname,"COM%d\0",iDevIndexAndEvent); //端口名
		sprintf(fullportname,"\\\\.\\%s",portname); //完整的端口号(大于COM9的要用此名)
		if(CH341PtNameIsCH341((UCHAR *)fullportname)){
			strcpy(ch341sername,portname);    //作为设备拔出时CH341串口判别的依据
			sprintf(tem,"CH341串口 %s 已插入",ch341sername);
			SendDlgItemMessage(afxwndhwnd,IDC_show,LB_ADDSTRING,0,(LONG)tem);
		}
		else{
			sprintf(tem,"串口 %s 已插入",portname);
			SendDlgItemMessage(afxwndhwnd,IDC_show,LB_ADDSTRING,0,(LONG)tem);
		}
	}
	else if(iDevIndexAndEvent<0){  //ch341串口已拔出
		sprintf(portname,"COM%d\0",-iDevIndexAndEvent); //中断传来的端口号为负值
		if(!_tcscmp(ch341sername,portname)) {//与是先前监测到的插入的341串口名比较			
			sprintf(tem,"CH341串口 %s 已拔出",portname);
			SendDlgItemMessage(afxwndhwnd,IDC_show,LB_ADDSTRING,0,(LONG)tem);	
			strcpy(ch341sername,"");
		}
		else {
			sprintf(tem,"串口 %s 已拔出",portname);
			SendDlgItemMessage(afxwndhwnd,IDC_show,LB_ADDSTRING,0,(LONG)tem);
		}		
	}
	return;
}
