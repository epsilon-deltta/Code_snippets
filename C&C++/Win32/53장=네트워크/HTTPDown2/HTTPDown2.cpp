#include <windows.h>
#include <wininet.h>
#include "resource.h"

BOOL CALLBACK MainDlgProc(HWND hDlg,UINT iMessage,WPARAM wParam,LPARAM lParam);
HINSTANCE g_hInst;
HWND hDlgMain;

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
         ,LPSTR lpszCmdParam,int nCmdShow)
{
    g_hInst=hInstance;
    DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), HWND_DESKTOP, MainDlgProc);
    return 0;
}

// URL���� ������ �ٿ�ε�޾� Path ���Ϸ� �����Ѵ�.
BOOL bStopHttpDownLoad, bDownLoading=FALSE;
BOOL HTTPDown(HWND hWnd,TCHAR *URL, TCHAR *Path)
{
	HINTERNET hInternet, hURL;
	HANDLE hFile;
	DWORD Size;
	DWORD dwRead,dwWritten,Recv=0;
	TCHAR buf[100000];
	MSG Message;

	// ���ͳ� ����
	hInternet=InternetOpen("HTTPTEST", INTERNET_OPEN_TYPE_PRECONFIG,
		NULL, NULL, 0);
	if (hInternet == NULL) {
		return FALSE;
	}

	// URL�� ����
	hURL=InternetOpenUrl(hInternet,URL,NULL,0,INTERNET_FLAG_RELOAD,0);
	if (hURL==NULL) {
		InternetCloseHandle(hInternet);
		return FALSE;
	}

	// �ٿ�ε����Ӱ� ��Ҵ� ���� ������ ���������� ����Ѵ�.
	bStopHttpDownLoad=FALSE;
	bDownLoading=TRUE;

	// ���� ������ �����Ѵ�.
	hFile=CreateFile(Path,GENERIC_WRITE,0,NULL,
		CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

	do {
		// �ٿ�ε�޾� ���� ���Ͽ� ����Ѵ�.
		InternetQueryDataAvailable(hURL,&Size,0,0);
		InternetReadFile(hURL,buf,Size,&dwRead);
		WriteFile(hFile,buf,dwRead,&dwWritten,NULL);

		// �ٿ�ε���� ���� �޽����� ����
		Recv+=dwWritten;
		SendMessage(hWnd,WM_USER+10,0,(LPARAM)Recv);

		// �θ� �������� �޽��� ó��
		if (PeekMessage(&Message,NULL,0,0,PM_REMOVE)) {
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		// ��� ó��
		if (bStopHttpDownLoad == TRUE) {
			SendMessage(hWnd,WM_USER+12,0,(LPARAM)Recv);
			break;
		}
	} while (dwRead != 0);

	InternetCloseHandle(hURL);
	InternetCloseHandle(hInternet);
	CloseHandle(hFile);
	bDownLoading=FALSE;

	// �ٿ�ε� �Ϸ� ó��(����� ���� ����)
	if (bStopHttpDownLoad == FALSE)
		SendMessage(hWnd,WM_USER+11,0,(LPARAM)Recv);
	return TRUE;
}

BOOL CALLBACK MainDlgProc(HWND hDlg,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	TCHAR szURL[MAX_PATH];
	TCHAR szLocal[MAX_PATH];
	TCHAR szTmp[100];

    switch (iMessage) {
    case WM_INITDIALOG:
		SetDlgItemText(hDlg,IDC_URL,"http://www.winapi.co.kr/images/logo.jpg");
		SetDlgItemText(hDlg,IDC_LOCAL,"c:\\logo.jpg");
        hDlgMain = hDlg;
        return TRUE;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDOK:
			if (bDownLoading==FALSE)
	            EndDialog(hDlgMain,0);
            return TRUE;
		case IDC_BTNDOWN:
			if (bDownLoading==FALSE) {
				GetDlgItemText(hDlg,IDC_URL,szURL,MAX_PATH);
				GetDlgItemText(hDlg,IDC_LOCAL,szLocal,MAX_PATH);
				if (HTTPDown(hDlg,szURL,szLocal)==FALSE) {
					MessageBox(hDlg,"���ͳ� ������ ���� �ʾҰų� "
						"URL�� ã�� �� �����ϴ�","����",MB_OK);
				}
			}
			return TRUE;
		case IDC_BTNCANCEL:
			bStopHttpDownLoad=TRUE;
			return TRUE;
        }
        return FALSE;
	case WM_USER+10:
		wsprintf(szTmp,"%d ����Ʈ �ް� �ֽ��ϴ�",lParam);
		SetDlgItemText(hDlg,IDC_STATUS,szTmp);
		return TRUE;
	case WM_USER+11:
		SetDlgItemText(hDlg,IDC_STATUS,"�ٿ�ε� �Ϸ�");
		return TRUE;
	case WM_USER+12:
		SetDlgItemText(hDlg,IDC_STATUS,"�ٿ�ε� ���");
		return TRUE;
    }
    return FALSE;
}

