#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("MemAlloc");

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

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	int i;
	int *ptr;
	TCHAR str[128];
	HANDLE MyHeap;
	HGLOBAL hMem;
	switch (iMessage) {
	case WM_PAINT:
		hdc=BeginPaint(hWnd, &ps);
//* 
		// malloc�� ����� �޸� �Ҵ� 
		ptr=(int *)malloc(sizeof(int)*10);
		for (i=0;i<10;i++) {
			wsprintf(str,"%d",ptr[i]=i*2);
			TextOut(hdc,10,i*20,str,lstrlen(str)); 
		}
		free(ptr);
//*/

/* 
		// new�� ����� �޸� �Ҵ� 
		ptr=new int[10];
		for (i=0;i<10;i++) {
			wsprintf(str,"%d",ptr[i]=i*2);
			TextOut(hdc,10,i*20,str,lstrlen(str)); 
		}
		delete [] ptr;
//*/

/*
		// VirtualAlloc�� ����� �޸� �Ҵ�
		ptr=(int *)VirtualAlloc(NULL, sizeof(int)*10, MEM_RESERVE | MEM_COMMIT, 
			PAGE_READWRITE);

		// ����� Ȯ���� ���� �ϱ�
//		ptr=(int *)VirtualAlloc(NULL,sizeof(int)*10,MEM_RESERVE,PAGE_READWRITE);
//		ptr=(int *)VirtualAlloc(ptr,sizeof(int)*10,MEM_COMMIT,PAGE_READWRITE);
		for (i=0;i<10;i++) {
			wsprintf(str,"%d",ptr[i]=i*2);
			TextOut(hdc,10,i*20,str,lstrlen(str)); 
		}
		VirtualFree(ptr, sizeof(int)*10, MEM_DECOMMIT);
		VirtualFree(ptr, 0, MEM_RELEASE);
//*/

/*
		// Win32 �� �Լ��� ����� �޸� �Ҵ�
		ptr=(int *)HeapAlloc(GetProcessHeap(), 0, sizeof(int)*10);
		for (i=0;i<10;i++) {
			wsprintf(str,"%d",ptr[i]=i*2);
			TextOut(hdc,10,i*20,str,lstrlen(str)); 
		}
		HeapFree(GetProcessHeap(), 0, ptr);
//*/

/*
		// ���ο� �� ����
		MyHeap=HeapCreate(0,4096,1048576);
		ptr=(int *)HeapAlloc(MyHeap, 0, sizeof(int)*10);
		for (i=0;i<10;i++) {
			wsprintf(str,"%d",ptr[i]=i*2);
			TextOut(hdc,10,i*20,str,lstrlen(str)); 
		}
		HeapFree(MyHeap, 0, ptr);
		HeapDestroy(MyHeap);
//*/

/* 
		// GlobalAlloc�� ����� �޸� �Ҵ�
		hMem=GlobalAlloc(GMEM_MOVEABLE,sizeof(int)*10);
		ptr=(int *)GlobalLock(hMem);
		for (i=0;i<10;i++) {
			wsprintf(str,"%d",ptr[i]=i*2);
			TextOut(hdc,10,i*20,str,lstrlen(str)); 
		}
		GlobalUnlock(hMem);
		GlobalFree(hMem); 
//*/

/* 
		// GlobalAlloc�� ����� ���� �޸� �Ҵ�
		ptr=(int *)GlobalAlloc(GMEM_FIXED,sizeof(int)*10);
		for (i=0;i<10;i++) {
			wsprintf(str,"%d",ptr[i]=i*2);
			TextOut(hdc,10,i*20,str,lstrlen(str)); 
		}
		GlobalFree(ptr); 
//*/

		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
