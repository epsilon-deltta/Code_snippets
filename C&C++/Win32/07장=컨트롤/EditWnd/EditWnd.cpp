#include <windows.h>
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("EditWnd");

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
	  ,LPSTR lpszCmdParam,int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;
	
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=NULL;
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

#define ID_EDIT 100
HWND hEdit;
int nTop=10;
BOOL bShow=TRUE;
int numOfButton = 10;
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	TCHAR *Mes=TEXT("http header_");
	switch (iMessage) {
	case WM_CREATE:
		hEdit=CreateWindow(TEXT("edit"),NULL,WS_CHILD | WS_VISIBLE | WS_BORDER | 
			ES_AUTOHSCROLL,10,nTop,200,25,hWnd,(HMENU)ID_EDIT,g_hInst,NULL);
		for (int i = 0; i < numOfButton; i++)
		{
			CreateWindow(TEXT("button"), TEXT("button"), WS_CHILD | WS_VISIBLE, 230, nTop +
				35 + (35 * i), 50, 25, hWnd, HMENU(101), g_hInst, NULL);
		}
		SetWindowText(hEdit,TEXT("http_testing"));
		return 0;
	case WM_LBUTTONDOWN:
		nTop+=10;
		MoveWindow(hEdit,10,nTop,200,25,TRUE);
		return 0;
	case WM_RBUTTONDOWN:
		if (bShow) {
			bShow=FALSE;
			ShowWindow(hEdit,SW_HIDE);
		} else {
			bShow=TRUE;
			ShowWindow(hEdit,SW_SHOW);
		}
		return 0;

	case WM_PAINT:
		hdc=BeginPaint(hWnd,&ps);
		for (int i = 0; i < numOfButton; i++)
		{
			TextOut(hdc, 140, nTop +
				35 + (35 * i), Mes, lstrlen(Mes));
		}
		EndPaint(hWnd,&ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
