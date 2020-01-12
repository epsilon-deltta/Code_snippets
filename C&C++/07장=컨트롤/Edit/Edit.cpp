#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("MyEdit");

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
HDC hdc;
void Mypaint(HWND hWnd, TCHAR* str) {
	hdc = GetDC(hWnd);
	TextOut(hdc, 10, 45, str, strlen(str) );
	ReleaseDC(hWnd, hdc);
}
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	TCHAR str[128];
	switch (iMessage) {
	case WM_CREATE:
		hEdit=CreateWindow(TEXT("edit"),NULL,WS_CHILD | WS_VISIBLE | WS_BORDER | 
			ES_AUTOHSCROLL,10,10,200,25,hWnd,(HMENU)100,g_hInst,NULL);
		CreateWindow(TEXT("button"), TEXT("submit"), WS_CHILD | WS_VISIBLE | WS_BORDER 
		, 220,10 , 75, 25, hWnd, (HMENU)101, g_hInst, NULL);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case 100:
			switch (HIWORD(wParam)) {
			case EN_CHANGE:
				GetWindowText(hEdit, str, 128);
				SetWindowText(hWnd,str);
			}
			break;
		case 101:
				GetWindowText(hEdit, str, 128);
				Mypaint(hWnd, str);
			break;
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
