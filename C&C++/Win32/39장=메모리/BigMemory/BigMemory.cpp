#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("BigMemory");

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

#define MEGA 1048576
PBYTE stptr=NULL;
TCHAR Status[256]="�Ҵ���� �ʾҽ��ϴ�";

void FreeRecords()
{
	// �Ҵ�Ǿ� �ִ� �޸𸮸� �����Ѵ�.
	if (stptr != NULL) {
		if (VirtualFree(stptr, 100*MEGA, MEM_DECOMMIT)==0) {
			MessageBox(hWndMain, "�޸� Ȯ�� ���� ����","����",MB_OK);
		}
		if (VirtualFree(stptr, 0, MEM_RELEASE)==0) {
			MessageBox(hWndMain, "�޸� ���� ���� ����","����",MB_OK);
		}
		stptr=NULL;
	}
	wsprintf(Status,"�Ҵ���� �ʾҽ��ϴ�");
	InvalidateRect(hWndMain,NULL,TRUE);
}

// �� ���� ������ ������ �ʿ��ϴ�.
// stptr:���� �Ҵ�� �޸� ������ ���� �ּ�
// endptr:������� Ȯ���� �޸� ������ �� �ּ�.
// nowptr:���� ������� �޸��� �ּ�
void ReadRecords()
{
	int i, c;
	int RecSize;
	PBYTE nowptr, endptr;

	FreeRecords();

	// 100M�� �ּ� ������ �����Ѵ�.
	stptr=(PBYTE)VirtualAlloc(NULL, 100*MEGA, MEM_RESERVE, PAGE_READWRITE);
	if (stptr == NULL) {
		MessageBox(hWndMain, "�޸� ���� ����","����",MB_OK);
		return;
	}
	nowptr=stptr;
	endptr=stptr;

	// �ִ� 100���� ���ڵ带 �о���δ�.
	c=rand() % 90 + 10;
	for (i=0;i<c;i++) {
		// Ȯ���� �޸𸮰� 1M �̸��̸� 1M�� �� Ȯ���Ѵ�.
		if (endptr-nowptr < MEGA) {
			VirtualAlloc(endptr,MEGA,MEM_COMMIT,PAGE_READWRITE);
			endptr+=MEGA;
		}

		// 10K~1M ������ ���ڵ带 �о���δ�.
		RecSize=((rand() % 100)+1)*10240;
		memset(nowptr,i,RecSize);
		nowptr+=RecSize;
	}

	wsprintf(Status,"����:100 �ް�, Ȯ��:%d �ް�, ���:%d �ް�", 
		(endptr-stptr)/MEGA,(nowptr-stptr)/MEGA);
	InvalidateRect(hWndMain,NULL,TRUE);
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	TCHAR *Mes="���� ���콺 ��ư:�޸� �Ҵ�, ������ ���콺 ��ư:�޸� ����";
	
	switch (iMessage) {
	case WM_CREATE:
		hWndMain=hWnd;
		srand(GetTickCount());
		return 0;
	case WM_LBUTTONDOWN:
		SetCursor(LoadCursor(NULL,IDC_WAIT));
		ReadRecords();
		SetCursor(LoadCursor(NULL,IDC_ARROW));
		return 0;
	case WM_RBUTTONDOWN:
		FreeRecords();
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd, &ps);
		TextOut(hdc,50,50,Mes,lstrlen(Mes));
		TextOut(hdc,50,80,Status,lstrlen(Status));
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		FreeRecords();
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}

