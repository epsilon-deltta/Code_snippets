#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("MemShare2");

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
		10,400,600,300,
		NULL,(HMENU)NULL,hInstance,NULL);
	ShowWindow(hWnd,nCmdShow);

	while (GetMessage(&Message,NULL,0,0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

#define WM_SYNCSHAREMEMORY WM_USER+1
#define MAXSHAREMEMORY 1024
#define ID_EDIT 100
HWND hEdit;
HANDLE hFMap;
TCHAR *PtrInFile;
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HWND hTarget;
	TCHAR *Mes="�޸� �� ������ ����Ͽ� �� ���μ����� �޸𸮸� �����ϴ� ����";

	switch (iMessage) {
	case WM_CREATE:
		hEdit=CreateWindow("edit",NULL,WS_CHILD | WS_VISIBLE | WS_BORDER | 
			WS_VSCROLL | ES_MULTILINE,10,10,500,200,hWnd,(HMENU)ID_EDIT,g_hInst,NULL);
		SendMessage(hEdit,EM_LIMITTEXT,MAXSHAREMEMORY,0);
		hFMap=CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 
			0, MAXSHAREMEMORY, "MEMSHAREMAPPING");
		PtrInFile=(TCHAR *)MapViewOfFile(hFMap, FILE_MAP_ALL_ACCESS,0,0,MAXSHAREMEMORY);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_EDIT:
			switch (HIWORD(wParam)) {
			case EN_CHANGE:
				GetWindowText(hEdit,PtrInFile,MAXSHAREMEMORY);
				hTarget=FindWindow(NULL,"MemShare1");
				if (hTarget)
					SendMessage(hTarget,WM_SYNCSHAREMEMORY,0,0);
				break;
			}
		}
		return 0;
	case WM_SYNCSHAREMEMORY:
		SetWindowText(hEdit,PtrInFile);
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd, &ps);
		TextOut(hdc,10,220,Mes,lstrlen(Mes));
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		UnmapViewOfFile(PtrInFile);
		CloseHandle(hFMap);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
