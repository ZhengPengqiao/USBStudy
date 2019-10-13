// SerchCH341Port.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include <stdio.h>
#include "CH341PT.H"
#pragma comment (lib,"CH341PT")



char ch341sername[10]="";   //�洢��⵽���Ѳ���Ĵ�����
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
			    //����ȫ����ʽΪ"////.//COMxx",����com9�Ĵ��ںű���Ҫ�ô���ȫ��,����򲻿�"
				case IDC_CH341PtHandleIsCH341:  //ͨ����������������ʶ��CH341����
					HANDLE porthandle;
					SendDlgItemMessage(hWnd,IDC_show,LB_ADDSTRING,0,(LONG)"ͨ�������ҵ�CH341����Ϊ");
					 for (j=1;j<21;j++) {
						sprintf((CHAR *)portname,"COM%d\0",j);                 //�豸��
						sprintf((CHAR *)fullportname,"\\\\.\\%s\0",portname);  //�������豸��
						porthandle=CreateFile((CHAR *)fullportname,
							        GENERIC_READ | GENERIC_WRITE,              // ���豸,֧���ص�����
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
					SendDlgItemMessage(hWnd,IDC_show,LB_ADDSTRING,0,(LONG)"ͨ������ҵ�CH341����Ϊ:");	
                    for (j=1;j<21;j++) {
						sprintf((CHAR *)portname,"COM%d\0",j);                 //�豸��
						sprintf((CHAR *)fullportname,"\\\\.\\%s\0",portname);  //�������豸��
						if(CH341PtNameIsCH341(fullportname)){							
							SendDlgItemMessage(hWnd,IDC_show,LB_ADDSTRING,0,(LONG)portname);	
						}
					}
                    break;

				case IDC_beginmonitor:
					if(CH341PtSetDevNotify(NULL,CH341PT_NOTIFY_ROUTINE))
						SendDlgItemMessage(hWnd,IDC_show,LB_ADDSTRING,0,(LONG)"��ʼ����CH341���ڲ��");	
					else
						SendDlgItemMessage(hWnd,IDC_show,LB_ADDSTRING,0,(LONG)"����CH341���ڼ���ʧ��");	
					break;
				case IDC_stopmonitor:
					if(CH341PtSetDevNotify(NULL,NULL))
						SendDlgItemMessage(hWnd,IDC_show,LB_ADDSTRING,0,(LONG)"ֹͣ����CH341���ڲ��");	
					break;
				case IDC_clear:
					SendDlgItemMessage(hWnd,IDC_show,LB_RESETCONTENT,0,0);				
					break;
				case WM_DESTROY:
					CH341PtSetDevNotify(NULL,NULL);   //��ֹ�ڹر�ǰû��ȡ�����ڲ�μ���
					PostQuitMessage(0);
					break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_KEYUP: //ģ���豸����¼�
			iDevIndexAndEvent=wParam;  //���жϳ����д����Ĵ��ں�
			CH341SerNotifyFunc(iDevIndexAndEvent); //���ò���¼��������
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
   }
   return 0;
}


void CALLBACK CH341PT_NOTIFY_ROUTINE(LONG iDevIndexAndEvent)
{  
	//���жϻص�������,���ܶ�ϵͳ��Դ��������.ͨ������WM_KEYUP�¼���ģ�����¼�
	PostMessage(afxwndhwnd,WM_KEYUP,iDevIndexAndEvent,0); 
}

void  CH341SerNotifyFunc(LONG iDevIndexAndEvent) {
	char fullportname[10]="";
	char tem[50]="";
	char portname[10]="";
	if(iDevIndexAndEvent>0){  //ch341�����Ѳ���
		sprintf(portname,"COM%d\0",iDevIndexAndEvent); //�˿���
		sprintf(fullportname,"\\\\.\\%s",portname); //�����Ķ˿ں�(����COM9��Ҫ�ô���)
		if(CH341PtNameIsCH341((UCHAR *)fullportname)){
			strcpy(ch341sername,portname);    //��Ϊ�豸�γ�ʱCH341�����б������
			sprintf(tem,"CH341���� %s �Ѳ���",ch341sername);
			SendDlgItemMessage(afxwndhwnd,IDC_show,LB_ADDSTRING,0,(LONG)tem);
		}
		else{
			sprintf(tem,"���� %s �Ѳ���",portname);
			SendDlgItemMessage(afxwndhwnd,IDC_show,LB_ADDSTRING,0,(LONG)tem);
		}
	}
	else if(iDevIndexAndEvent<0){  //ch341�����Ѱγ�
		sprintf(portname,"COM%d\0",-iDevIndexAndEvent); //�жϴ����Ķ˿ں�Ϊ��ֵ
		if(!_tcscmp(ch341sername,portname)) {//������ǰ��⵽�Ĳ����341�������Ƚ�			
			sprintf(tem,"CH341���� %s �Ѱγ�",portname);
			SendDlgItemMessage(afxwndhwnd,IDC_show,LB_ADDSTRING,0,(LONG)tem);	
			strcpy(ch341sername,"");
		}
		else {
			sprintf(tem,"���� %s �Ѱγ�",portname);
			SendDlgItemMessage(afxwndhwnd,IDC_show,LB_ADDSTRING,0,(LONG)tem);
		}		
	}
	return;
}
