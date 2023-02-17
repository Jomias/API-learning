// TestKT2.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "TestKT2.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
HPEN hPen;
static HMENU hMenu;
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_TESTKT2, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TESTKT2));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TESTKT2));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_TESTKT2);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable
	HWND hWnd = CreateWindowW(szWindowClass, L"Trần Công Thành - 201240331", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int m = 0, s = 0;
	static TCHAR text[30];
	static int hinh = 0;
	static COLORREF mau = RGB(0, 0, 0);
	static int x1, y1, x2, y2;
	static HDC hdc;
	switch (message)
	{
	case WM_TIMER:
		if (s >= 0 && s < 59) {
			s++;
		}
		else {
			if (s == 59) {
				m++;
				s = 0;
			}
		}
		wsprintf(text, L"Thời gian: %02d:%02d", m, s);
		hdc = GetDC(hWnd);
		TextOut(hdc, 900, 550, text, 30);
		ReleaseDC(hWnd, hdc);
		break;
	case WM_LBUTTONDOWN:
	{
		x1 = LOWORD(lParam);
		y1 = HIWORD(lParam);
		break;
	}
	case WM_LBUTTONUP:
	{
		x2 = LOWORD(lParam);
		y2 = HIWORD(lParam);
		hdc = GetDC(hWnd);
		hPen = CreatePen(PS_SOLID, 3, mau);
		hdc = GetDC(hWnd);
		SelectObject(hdc, hPen); // áp dụng bút vẽ

		switch (hinh)
		{
		case 1:
		{
			RoundRect(hdc, x1, y1, x2, y2, (x2 - x1) / 8, (y2 - y1) / 8);
			break;
		}
		case 2:
		{
			POINT temp[2] = { {x1, y1}, {x2, y2} };
			Polyline(hdc, temp, 2);
			break;
		}
		default:
			break;
		}
		ReleaseDC(hWnd, hdc);
		break;
	}
	break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case ID_HCN:
			hinh = 1;
			break;
		case ID_DT:
			hinh = 2;
			break;
		case ID_Do:
			mau = RGB(255, 0, 0);
			break;
		case ID_XanhNgoc:
			mau = RGB(0, 255, 255);
			break;
		case ID_BAT:
			m = 0; s = 0;
			SetTimer(hWnd, 9999, 1000, NULL);
			break;
		case ID_TAT:
			KillTimer(hWnd, 9999);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_RBUTTONDOWN:
		static HMENU hMenu;
		POINT point;
		hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU1));
		hMenu = GetSubMenu(hMenu, 0);
		point.x = LOWORD(lParam);
		point.y = HIWORD(lParam);
		ClientToScreen(hWnd, &point);
		TrackPopupMenu(hMenu, TPM_RIGHTBUTTON, point.x, point.y, 0, hWnd, NULL);
		break;
	case WM_CLOSE:
		if (MessageBox(hWnd, TEXT("Bạn có muốn thoát không ?"), TEXT("HỎI"), MB_ICONQUESTION | MB_YESNO) == IDYES)
			DestroyWindow(hWnd);
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
