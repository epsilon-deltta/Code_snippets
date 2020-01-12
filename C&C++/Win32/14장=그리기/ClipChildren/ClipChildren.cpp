#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("ClipChildren");

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

	hWnd=CreateWindow(lpszClass,lpszClass,WS_OVERLAPPEDWINDOW,// | WS_CLIPCHILDREN,
		CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
		NULL,(HMENU)NULL,hInstance,NULL);
	ShowWindow(hWnd,nCmdShow);
	
	while (GetMessage(&Message,NULL,0,0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN hPen,OldPen;
	HBRUSH OldBrush;

	switch (iMessage) {
	case WM_CREATE:
		CreateWindow(TEXT("button"),TEXT("Child Button"),WS_CHILD | WS_VISIBLE | 
			BS_PUSHBUTTON,50,50,200,100,hWnd,(HMENU)0,g_hInst,NULL);
		CreateWindow(TEXT("listbox"),NULL,WS_CHILD | WS_VISIBLE | WS_BORDER |
			LBS_NOTIFY,50,200,200,100,hWnd,(HMENU)1,g_hInst,NULL);
		CreateWindow(TEXT("edit"),TEXT("����Ʈ ��Ʈ���Դϴ�"),WS_CHILD | WS_VISIBLE | 
			WS_BORDER,300,120,200,80,hWnd,(HMENU)2,g_hInst,NULL);
		hWndMain=hWnd;
		return 0;
	case WM_LBUTTONDOWN:
		hdc=GetDC(hWnd);
		OldBrush=(HBRUSH)SelectObject(hdc,GetStockObject(NULL_BRUSH));
		hPen=CreatePen(PS_SOLID,4,RGB(255,0,0));
		OldPen=(HPEN)SelectObject(hdc,hPen);

		Ellipse(hdc,LOWORD(lParam)-50,HIWORD(lParam)-40,LOWORD(lParam)+50,
			HIWORD(lParam)+40);

		DeleteObject(SelectObject(hdc,OldPen));
		SelectObject(hdc,OldBrush);
		ReleaseDC(hWnd,hdc);
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
