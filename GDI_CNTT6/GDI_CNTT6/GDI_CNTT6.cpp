// GDI_CNTT6.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "GDI_CNTT6.h"

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
HBRUSH hBrush;

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
	LoadStringW(hInstance, IDC_GDICNTT6, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GDICNTT6));

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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GDICNTT6));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_GDICNTT6);
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

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
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
	static POINT point[3] = { {200, 600}, {500, 400}, {700, 500} };
	static POINT p1[4] = { {100, 200}, {400, 200}, {400, 400} , {100, 400} };
	static POINT p2[4] = { {400, 400}, {600, 600}, {400, 800} , {200, 600} };
	static POINT p3[8] = { {200, 500}, {400, 400}, {500, 200}, {600, 400}, {800, 500}, {600, 600}, {500, 800}, {400, 600} };
	static int x1, y1, x2, y2;
	static HDC hdc;
	switch (message)
	{
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
		hPen = CreatePen(PS_DASH, 1, RGB(0, 0, 255));
		//hBrush = CreateSolidBrush(RGB(50, 200, 250));
		hBrush = CreateHatchBrush(HS_CROSS, RGB(50, 200, 250));
		hdc = GetDC(hWnd);
		SelectObject(hdc, hPen); // áp dụng bút vẽ
		SelectObject(hdc, hBrush); // màu nền
		// hình thoi 
		POINT test[4] = { { (x1 + x2) / 2, y1}, {x2, (y1 + y2) / 2}, {(x1 + x2) / 2, y2}, {x1, (y1 + y2) / 2} };
		Polygon(hdc, test, 4);


		//Rectangle(hdc, x1, y1, x2, y2);

		// tam giác cân
		//POINT test2[3] = { {x1, y2}, {(x1 + x2) / 2, y1}, {x2, y2}};
		//Polygon(hdc, test2, 3);
		
		// sao 4 cánh
		//int difx = (x2 - x1) * 3 / 8;
		//int dify = (y2 - y1) * 3 / 8;
		//POINT test3[8] = { {x1 + difx, y1 + dify}, {(x1 + x2) / 2, y1}, 
		//	{x2 - difx, y1 + dify}, {x2, (y1 + y2) / 2}, 
		//	{x2 - difx, y2 - dify}, {(x1 + x2) / 2, y2}, 
		//	{x1 + difx, y2 - dify} ,{x1, (y1 + y2) / 2}};
		//Polygon(hdc, test3, 8);
		ReleaseDC(hWnd, hdc);
		break;
	}
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// vẽ đoạn thằng bằng điểm ảnh
		/*for (int i = 200; i <= 600; ++i) 
		{
			SetPixel(hdc, i, 200, RGB(255, 0, 0));
		}*/

		// vẽ đoạn thẳng bằng hàm
		//MoveToEx(hdc, 200, 300, NULL);
		//LineTo(hdc, 600, 300);

		//vẽ đường gấp khúc
		//Polyline(hdc, point, 3);

		//vẽ đa giác
		//Polygon(hdc, point, 3);

		// vẽ hình chữ nhật
		// Polygon(hdc, p1, 4);

		// hình thoi
		//Polygon(hdc, p2, 4);

		// hình sao 4 cánh
		//Polygon(hdc, p3, 8);

		// hình chữ nhật bằng hàm
		//Rectangle(hdc, 300, 100, 400, 300);

		// hình chữ nhật bo góc:
		//RoundRect(hdc, 300, 100, 400, 300, 50, 50);

		// Hình elip
		//Ellipse(hdc, 100, 100, 500, 300);

		// hình cung
		//Arc(hdc, 250, 250, 600, 600, 300, 250, 250, 400);

		//Quạt
		//Pie(hdc, 250, 250, 600, 600, 300, 250, 250, 400);

		//Hình bán nguyệt
		//Chord(hdc, 250, 250, 600, 600, 300, 250, 250, 400);

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
