#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<tchar.h>
#include "Resource.h"
#define ID_STDDIALOG 11
INT_PTR CALLBACK Dialog1(HWND, UINT, WPARAM, LPARAM);
TCHAR WinName[] = _T("MainFrame");
HINSTANCE hInst;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HWND hwnd;
	MSG msg;
	WNDCLASSEX wc;
	hInst = hInstance;
	wc.cbSize = sizeof(wc);																															
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WinName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	//Регистрируем класс окна
	if (!RegisterClassEx(&wc)) return 0;
	hwnd = CreateWindow(WinName, _T("Dialog"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		HWND_DESKTOP, NULL, hInstance, NULL);
	//Показываем окно
	ShowWindow(hwnd, nCmdShow);

	//UpdateWindow(hMainWnd);
	//Выполняем цикл обработки сообщений до закрытия окна
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return 0;

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR str[256];
	int i;
	HMENU hMenu, hPopupMenu;
	TCHAR str0[] = _T("Диалог");
	TCHAR str1[] = _T("Открыть");
	switch (uMsg) {
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_STDDIALOG:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Dialog1);
			return 0;
		default: return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
		break;
	case WM_CREATE:
		hMenu = CreateMenu();
		hPopupMenu = CreatePopupMenu();
		AppendMenu(hPopupMenu, MF_STRING, ID_STDDIALOG, str1);
		AppendMenu(hMenu, MF_POPUP, (UINT)hPopupMenu, str0);
		SetMenu(hWnd, hMenu);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

INT_PTR CALLBACK Dialog1(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int i;
	HDC hdc;
	TCHAR buff[256];
	static HWND hStat, hCombo;
	HBRUSH hBrushBlue = CreateSolidBrush(RGB(0, 0, 255));
	switch (uMsg) {
	case WM_INITDIALOG:
		hStat = GetDlgItem(hDlg, IDC_LIST1);
		//hStat = CreateWindow(_T("static"), _T("HEX - DEC"), WS_CHILD | WS_VISIBLE, 265, 5, 70, 15, hDlg, 0, hInst, NULL);
		for (i = 0; i < 256; i++)
		{
			wsprintf(buff, _T("%#02x %03d"), i, i);
			SendMessage(hStat, LB_ADDSTRING, 0, (LPARAM)buff);
		}
		//ShowWindow(hStat, SW_SHOWNORMAL);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		//case IDC_COMBO:


		case IDCANCEL: return EndDialog(hDlg, 0);
		}
		return TRUE;
		
	case WM_CTLCOLORLISTBOX:
		hdc = (HDC)wParam;
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkColor(hdc, RGB(0, 0, 255));
		return (LONG)hBrushBlue;	   
	case WM_ERASEBKGND:
		break;
	default: return FALSE;
	}
	return FALSE;
}
