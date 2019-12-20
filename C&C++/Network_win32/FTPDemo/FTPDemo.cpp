#include <windows.h>
#include <wininet.h>
#include <commctrl.h>
#include "resource.h"

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
BOOL CALLBACK FtpDlgProc(HWND hDlg,UINT iMessage,WPARAM wParam,LPARAM lParam);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("FTPDemo");

HWND hList, hLabel1, hLabel2;				// ���� ��� ����Ʈ ��
HIMAGELIST hImgSm;							// �̹���
HINTERNET hInternet, hFtp;					// ���ͳ� �ڵ�
TCHAR g_Server[50]="ftp.microsoft.com";		// ���� ����
TCHAR g_User[20]="anonymous";				// ����� ID
TCHAR g_Pass[20]="aaa@bbb.co.kr";			// �н�����

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
	  ,LPSTR lpszCmdParam,int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;

	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)(COLOR_BTNFACE+1);
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=MAKEINTRESOURCE(IDR_MENU1);
	WndClass.style=CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd=CreateWindow(lpszClass,lpszClass,WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
		NULL,(HMENU)NULL,hInstance,NULL);
	ShowWindow(hWnd,nCmdShow);

	while (GetMessage(&Message,NULL,0,0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

// FTP�� �����Ѵ�.
BOOL MyFtpConnect()
{
	hInternet=InternetOpen("FTPTEST", INTERNET_OPEN_TYPE_PRECONFIG,
		NULL, NULL, 0);
	if (hInternet == NULL) {
		return FALSE;
	}

	hFtp=InternetConnect(hInternet,g_Server,INTERNET_DEFAULT_FTP_PORT,
		g_User,g_Pass,INTERNET_SERVICE_FTP,0,0);
	if (hFtp==NULL) {
		InternetCloseHandle(hInternet);
		return FALSE;
	}
	return TRUE;
}

// FTP ������ ���´�.
void MyFtpUnConnect()
{
	InternetCloseHandle(hFtp);
	InternetCloseHandle(hInternet);
	hFtp=NULL;
	hInternet=NULL;
}

// ������ ����Ʈ �信 ����Ѵ�.
void AddFileToList(WIN32_FIND_DATA wfd)
{
	LVITEM LI;
	int idx;
	TCHAR szTmp[50];
	SYSTEMTIME st;

	LI.mask=LVIF_TEXT | LVIF_IMAGE;

	if (lstrcmp(wfd.cFileName,"�Ѵܰ� ����")!=0) {
		if (wfd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
			LI.iImage=0;
		else
			LI.iImage=1;
	} else {
		LI.iImage=2;
	}
	LI.iSubItem=0;
	LI.iItem=10000;
	LI.pszText=wfd.cFileName;
	idx=ListView_InsertItem(hList,&LI);

	if (lstrcmp(wfd.cFileName,"�Ѵܰ� ����")!=0) {
		itoa(wfd.nFileSizeLow,szTmp,10);
		ListView_SetItemText(hList,idx,1,szTmp);
		FileTimeToSystemTime(&wfd.ftLastWriteTime,&st);
		wsprintf(szTmp,"%d�� %d�� %d�� %d�� %d��",st.wYear, st.wMonth, st.wDay, 
			st.wHour, st.wMinute);
		ListView_SetItemText(hList,idx,2,szTmp);
	}
}

// FTP ������ ���� ���丮���� ������ �����Ѵ�.
void MyFtpEnumFiles()
{
	WIN32_FIND_DATA wfd;
	BOOL bResult=TRUE;
	HINTERNET hFind;

	if (hFtp==NULL)
		return;

	// ��� �׸��� ����� �Ѵܰ� ���� �׸��� ����Ʈ�� �����ش�.
	ListView_DeleteAllItems(hList);
	lstrcpy(wfd.cFileName,"�Ѵܰ� ����");
	AddFileToList(wfd);

	// ���� ��� ���
	hFind=FtpFindFirstFile(hFtp,"*.*",&wfd,0,0);
	if (hFind!=NULL) {
		AddFileToList(wfd);
		while (bResult) {
			bResult=InternetFindNextFile(hFind,&wfd);
			if (bResult==TRUE) {
				AddFileToList(wfd);
			}
		}
		InternetCloseHandle(hFind);
	}
}

// FTP�� ���� ���丮���� ������ �ٿ�ε� �޴´�.
BOOL MyFtpDownLoad(TCHAR *Path)
{
	TCHAR NewFile[MAX_PATH];

	wsprintf(NewFile,"c:\\%s",Path);
	return FtpGetFile(hFtp,Path,NewFile,FALSE,FILE_ATTRIBUTE_NORMAL,
		FTP_TRANSFER_TYPE_BINARY | INTERNET_FLAG_RELOAD,0);
}

// ���� ������ �ٿ�ε�
BOOL MyFtpDownLoad2(TCHAR *Path)
{
	HINTERNET hRemote;
	HANDLE hLocal;
	DWORD dwRead,dwWritten,Prog;
	BOOL Result;
	TCHAR NewFile[MAX_PATH];
	TCHAR buf[1000];
	TCHAR str[255];

	// ������ ������ �����Ѵ�.
	hRemote=FtpOpenFile(hFtp,Path,GENERIC_READ,FTP_TRANSFER_TYPE_BINARY,0);
	if (hRemote == NULL)
		return FALSE;

	// ���� ������ �����.
	wsprintf(NewFile,"c:\\%s",Path);
	hLocal=CreateFile(NewFile,GENERIC_WRITE,0,NULL,
		CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

	// 1000����Ʈ�� ������ ���� ���¸� ����Ѵ�.
	Prog=0;
	for (;;) {
		Result=InternetReadFile(hRemote,buf,1000,&dwRead);
		if ((Result==TRUE) && (dwRead==0))
			break;
		WriteFile(hLocal,buf,dwRead,&dwWritten,NULL);
		Prog+=dwWritten;
		wsprintf(str,"%d����Ʈ �޾ҽ��ϴ�",Prog);
		SetWindowText(hLabel2,str);
	}

	CloseHandle(hLocal);
	InternetCloseHandle(hRemote);
	return TRUE;
}

// Path ������ FTP�� ���� ���丮�� ���ε��Ѵ�.
BOOL MyFtpUpLoad(TCHAR *Path)
{
	TCHAR ext[_MAX_EXT];
   	TCHAR Remote[MAX_PATH];

	_splitpath(Path,NULL,NULL,Remote,ext);
	lstrcat(Remote,ext);
	return FtpPutFile(hFtp,Path,Remote,
		FTP_TRANSFER_TYPE_BINARY | INTERNET_FLAG_RELOAD,0);
}

// ���� ������ ���ε�
BOOL MyFtpUpLoad2(TCHAR *Path)
{
	HINTERNET hRemote;
	HANDLE hLocal;
	TCHAR ext[_MAX_EXT];
   	TCHAR Remote[MAX_PATH];
	DWORD dwRead,dwWritten,Prog;
	BOOL Result;
	TCHAR buf[1000];
	TCHAR str[255];

	// ������ ������ �����.
	_splitpath(Path,NULL,NULL,Remote,ext);
	lstrcat(Remote,ext);
	hRemote=FtpOpenFile(hFtp,Remote,GENERIC_WRITE,FTP_TRANSFER_TYPE_BINARY,0);
	if (hRemote == NULL)
		return FALSE;

	// ������ ������ ����
	hLocal=CreateFile(Path,GENERIC_READ,0,NULL,
		OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

	// 1000����Ʈ�� �ø��� ���� ���¸� ����Ѵ�.
	Prog=0;
	for (;;) {
		Result=ReadFile(hLocal,buf,1000,&dwRead,NULL);
		if ((Result==TRUE) && (dwRead==0))
			break;
		InternetWriteFile(hRemote,buf,1000,&dwWritten);
		Prog+=dwWritten;
		wsprintf(str,"%d����Ʈ ���½��ϴ�",Prog);
		SetWindowText(hLabel2,str);
	}

	CloseHandle(hLocal);
	InternetCloseHandle(hRemote);
	return TRUE;
}

// �׸� ����Ŭ�� ó��
void OnDblClick(int iItem)
{
	LVITEM LI;
	TCHAR Path[MAX_PATH];
	BOOL Result;

	if ((hFtp == NULL) || (iItem == -1))
		return;

	// �� �ܰ� ���� �̵�
	if (iItem == 0) {
		if (FtpSetCurrentDirectory(hFtp,"..")==TRUE)
			MyFtpEnumFiles();
		return;
	}

	LI.iItem=iItem;
	LI.iSubItem=0;
	LI.pszText=Path;
	LI.cchTextMax=255;
	LI.mask=LVIF_IMAGE | LVIF_TEXT;
	ListView_GetItem(hList,&LI);

	// ���丮 ����
	if (LI.iImage == 0) {
		if (FtpSetCurrentDirectory(hFtp,Path)==TRUE) {
			MyFtpEnumFiles();
		} else {
			MessageBox(hWndMain,"���丮 ���� ����","�˸�",0);
		}
	// ���� �ٿ� �ε� - ShiftŰ�� ������ ������ 1000����Ʈ�� �޴´�.
	} else {
		if ((GetKeyState(VK_SHIFT) & 0x8000) == 0x8000) {
			Result=MyFtpDownLoad2(Path);
		} else {
			Result=MyFtpDownLoad(Path);
		}
		if (Result==TRUE) {
			MessageBox(hWndMain,"�ٿ�ε� �޾ҽ��ϴ�","�˸�",0);
		} else {
			MessageBox(hWndMain,"�ٿ�ε� �����߽��ϴ�.","�˸�",0);
		}
	}
}

// ���� ���ε�
void OnUpLoad()
{
	OPENFILENAME OFN;
	TCHAR lpstrFile[MAX_PATH]="";

	if (hFtp == NULL) {
		MessageBox(hWndMain,"���� FTP ������ �����Ͻʽÿ�","�˸�",MB_OK);
		return;
	}

	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner=hWndMain;
	OFN.lpstrFilter="Every File(*.*)\0*.*\0";
	OFN.lpstrFile=lpstrFile;
	OFN.nMaxFile=MAX_PATH;
	OFN.lpstrInitialDir="c:\\";
	if (GetOpenFileName(&OFN)!=0) {
		if (MyFtpUpLoad(OFN.lpstrFile)==TRUE) {
			MessageBox(hWndMain,"���ε��߽��ϴ�.","�˸�",0);
			MyFtpEnumFiles();
		} else {
			MessageBox(hWndMain,"���ε忡 �����߽��ϴ�.","�˸�",0);
		}
	}
}

// ������ ���ν���
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	TCHAR szCap[255];
	LV_COLUMN COL;

	switch (iMessage) {
	case WM_CREATE:
		hLabel1=CreateWindow("static","�������:���� ����",WS_CHILD | WS_VISIBLE,
			10,10,500,20,hWnd,(HMENU)1,g_hInst,NULL);
		hLabel2=CreateWindow("static","�ٿ�ε� ����",WS_CHILD | WS_VISIBLE,
			10,30,300,20,hWnd,(HMENU)2,g_hInst,NULL);
		hList=CreateWindow(WC_LISTVIEW,NULL,WS_CHILD | WS_VISIBLE | WS_BORDER |
			LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL,
			10,55,600,400,hWnd,(HMENU)3,g_hInst,NULL);
		hImgSm=ImageList_LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BIT16), 16, 1, 
			RGB(255,255,255));
		ListView_SetImageList(hList, hImgSm, LVSIL_SMALL);
		COL.mask=LVCF_FMT | LVCF_WIDTH | LVCF_TEXT |LVCF_SUBITEM;
		COL.fmt=LVCFMT_LEFT;
		COL.cx=200;
		COL.pszText="����";
		COL.iSubItem=0;
		ListView_InsertColumn(hList,0,&COL);

		COL.pszText="ũ��";
		COL.iSubItem=1;
		ListView_InsertColumn(hList,1,&COL);

		COL.cx=150;
		COL.pszText="��¥";
		COL.iSubItem=2;
		ListView_InsertColumn(hList,2,&COL);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDM_CONNECT:
			if (hFtp != NULL) {
				MessageBox(hWnd,"���� ������ ���� �����ʽÿ�.","�˸�",MB_OK);
				break;
			}
			if (DialogBox(g_hInst,MAKEINTRESOURCE(IDD_DLGFTP),hWnd,FtpDlgProc)==IDCANCEL)
				break;
			wsprintf(szCap,"�������:%s ������ �����ϰ� �ֽ��ϴ�.",g_Server);
			SetWindowText(hLabel1,szCap);
			if (MyFtpConnect()==FALSE) {
				MessageBox(hWnd,"���ῡ �����߽��ϴ�.","�˸�",MB_OK);
				break;
			}
			MyFtpEnumFiles();
			wsprintf(szCap,"�������:%s ������ �����",g_Server);
			SetWindowText(hLabel1,szCap);
			break;
		case IDM_DISCONNECT:
			MyFtpUnConnect();
			ListView_DeleteAllItems(hList);
			SetWindowText(hLabel1,"�������:���� ����");
			break;
		case IDM_UPLOAD:
			OnUpLoad();
			break;
		case IDM_EXIT:
			PostQuitMessage(0);
			break;
		}
		return 0;
	case WM_NOTIFY:
		LPNMHDR hdr;
		LPNMITEMACTIVATE nia;
		hdr=(LPNMHDR)lParam;
		nia=(LPNMITEMACTIVATE)lParam;
		if (hdr->hwndFrom == hList) {
			switch (hdr->code) {
			// ���õ� �׸��� ����Ʈ�� �����ش�.
			case NM_DBLCLK:
				OnDblClick(nia->iItem);
				break;
			}
		}
		break;
	case WM_PAINT:
		hdc=BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		if (hFtp != NULL)
			MyFtpUnConnect();
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}

// FTP ���� ������ �����Ѵ�.
BOOL CALLBACK FtpDlgProc(HWND hDlg,UINT iMessage,WPARAM wParam,LPARAM lParam) 
{
	switch (iMessage) {
	case WM_INITDIALOG:
		SetDlgItemText(hDlg,IDC_EDSERVER,g_Server);
		SetDlgItemText(hDlg,IDC_EDUSER,g_User);
		SetDlgItemText(hDlg,IDC_EDPASS,g_Pass);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			GetDlgItemText(hDlg,IDC_EDSERVER,g_Server,50);
			GetDlgItemText(hDlg,IDC_EDUSER,g_User,20);
			GetDlgItemText(hDlg,IDC_EDPASS,g_Pass,20);
			EndDialog(hDlg,IDOK);
			return TRUE;
		case IDCANCEL:
			EndDialog(hDlg,IDCANCEL);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

