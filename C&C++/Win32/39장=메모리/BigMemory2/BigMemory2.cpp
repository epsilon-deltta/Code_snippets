#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("BigMemory2");

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
		free(stptr);
		stptr=NULL;
	}
	wsprintf(Status,"�Ҵ���� �ʾҽ��ϴ�");
	InvalidateRect(hWndMain,NULL,TRUE);
}

// �� ���� ������ �ʿ��ϴ�. realloc�� ���� ���̽��� �ٲ� �� �����Ƿ� �����ʹ� �ȵ�
// stptr:���� �Ҵ�� �޸� ������ ���� �ּ�
// AllocSize : ���� �Ҵ�� ũ��
// RemainSize : �Ҵ�� ������ ���� ����.
void ReadRecords()
{
	int i, c;
	int RecSize;
	int AllocSize;
	int RemainSize;

	FreeRecords();

	// ���� 2M�� �Ҵ��Ѵ�.
	AllocSize=RemainSize=2*MEGA;
	stptr=(PBYTE)malloc(AllocSize);
	if (stptr == NULL) {
		MessageBox(hWndMain, "�޸� �Ҵ� ����","����",MB_OK);
		return;
	}

	// �ִ� 100���� ���ڵ带 �о���δ�.
	c=rand() % 91 + 10;
	for (i=0;i<c;i++) {
		// ���� �޸𸮰� 1M �̸��̸� 1M�� �� �Ҵ��Ѵ�.
		if (RemainSize < MEGA) {
			AllocSize+=MEGA;
			RemainSize+=MEGA;
			stptr=(PBYTE)realloc(stptr,AllocSize);
		}

		// 10K~1M ������ ���ڵ带 �о���δ�.
		RecSize=((rand() % 100)+1)*10240;
		memset(stptr+AllocSize-RemainSize,i,RecSize);
		RemainSize-=RecSize;
	}

	wsprintf(Status,"�� �Ҵ緮:%d �ް�, ���:%d �ް�", 
		AllocSize/MEGA,(AllocSize-RemainSize)/MEGA);
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
