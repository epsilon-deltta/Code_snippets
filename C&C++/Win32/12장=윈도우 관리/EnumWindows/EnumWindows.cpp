#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("EnumWindows");

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

// ���� ����
#define ID_LISTBOX 100
HWND hList;

// �ݹ� �Լ�. EnumWindows�Լ��� �����츦 ã�� ������ �� ������ �Ѱ��ش�.
// ������ �ڵ��� �޾� �� ������ ĸ���� �����ϰų� ������ ���� �ִ�.
BOOL CALLBACK MyEnumWindowsProc(HWND hwnd,LPARAM lParam)
{
	TCHAR str[300];
	TCHAR Cap[255];
	RECT rt;

	// �ڵ�κ��� ĸ��, ��ǥ�� �����Ͽ� ����Ʈ �ڽ��� ����Ѵ�.
	GetWindowText(hwnd,Cap,255);
	GetWindowRect(hwnd, &rt);
	wsprintf(str,TEXT("�ڵ�=0x%x(%d), ĸ��=%s, ��ǥ=(%d,%d,%d,%d)"), 
		hwnd, hwnd, Cap, rt.left, rt.top, rt.right, rt.bottom);
	SendMessage(hList,LB_ADDSTRING,0,(LPARAM)str);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	TCHAR *Mes=TEXT("������ �ٴ��� ���� ���콺 ��ư���� Ŭ���ϸ� ������")
		TEXT(" ����� ���� �帱����");

	switch (iMessage) {
	case WM_CREATE:
		// ������ ����� �����ֱ� ���� ����Ʈ �ڽ��� �ϳ� �����ߴ�.
		hList=CreateWindow(TEXT("listbox"),NULL,WS_CHILD | WS_VISIBLE | WS_BORDER |
			LBS_NOTIFY | LBS_NOINTEGRALHEIGHT | WS_VSCROLL,
			10,10,100,200,hWnd,(HMENU)ID_LISTBOX,g_hInst,NULL);
		return 0;
	case WM_LBUTTONDOWN:
		// ����Ʈ �ڽ��� ���� ������ ����� �����Ѵ�.
		SendMessage(hList, LB_RESETCONTENT,0,0);
		EnumWindows(MyEnumWindowsProc, NULL);
	case WM_PAINT:
		hdc=BeginPaint(hWnd, &ps);
		TextOut(hdc,5,5,Mes,lstrlen(Mes));
		EndPaint(hWnd, &ps);
		return 0;
	case WM_SIZE:
		// ����Ʈ �ڽ��� �׻� �����츦 ���� ä�쵵��...
		MoveWindow(hList,0,50,LOWORD(lParam), HIWORD(lParam)-50, TRUE);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
