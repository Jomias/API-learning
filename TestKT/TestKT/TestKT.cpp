// TestKT.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "TestKT.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                   // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
HPEN hPen;
HBRUSH hBrush;
static int Hinh = 0;
static int Nen = 0;
static int Vien = 0;
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
    LoadStringW(hInstance, IDC_TESTKT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TESTKT));

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

    return (int) msg.wParam;
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

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TESTKT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TESTKT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

   HWND hWnd = CreateWindowW(szWindowClass, L"Vẽ Hình", WS_OVERLAPPEDWINDOW,
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
        hdc = GetDC(hWnd);

        hPen = CreatePen(PS_SOLID, 1, Vien == 0 ? RGB(255, 0, 0) : RGB(0, 255, 255));
        hBrush = CreateSolidBrush(Nen == 0 ? RGB(0, 255, 0) : RGB(0, 0, 255));
        hdc = GetDC(hWnd);
        SelectObject(hdc, hPen); // áp dụng bút vẽ
        SelectObject(hdc, hBrush); // màu nền

        Rectangle(hdc, 500, 600, 700, 800);

        // tam giác cân
        //POINT test2[3] = { {x1, y2}, {(x1 + x2) / 2, y1}, {x2, y2}};
        //Polygon(hdc, test2, 3);

        switch (Hinh)
        {
            case 0:
            {
                Rectangle(hdc, x1, y1, x2, y2);
                break;
            }
            case 1:
            {
                int difx = (x2 - x1) * 3 / 8;
                int dify = (y2 - y1) * 3 / 8;
                POINT test3[8] = { {x1 + difx, y1 + dify}, {(x1 + x2) / 2, y1},
                    {x2 - difx, y1 + dify}, {x2, (y1 + y2) / 2},
                    {x2 - difx, y2 - dify}, {(x1 + x2) / 2, y2},
                    {x1 + difx, y2 - dify} ,{x1, (y1 + y2) / 2} };
                Polygon(hdc, test3, 8);
                break;
            }
            case 2:
            {
                Ellipse(hdc, x1, y1, x2, y2);
                break;
            }
            default:
                break;
        }
        ReleaseDC(hWnd, hdc);
        break;
    }
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case ID_H32771:
            {
                Hinh = 0;
                break;
            }
            case ID_H32772:
            {
                Hinh = 1;
                break;
            }
            case ID_H32773:
            {
                Hinh = 2;
                break;
            }
            case ID_M32774:
            {
                Nen = 0;
                break;
            }
            case ID_M32775:
            {
                Nen = 1;
                break;
            }
            case ID_32775:
            {
                Vien = 0;
                break;
            }
            case ID_32776:
            {
                Vien = 1;
                break;
            }
            case IDM_EXIT:
                if (MessageBox(hWnd, TEXT("Bạn có muốn thoát không ?"), TEXT("HỎI"), MB_ICONQUESTION | MB_YESNO) == IDYES)
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
    static int x1, y1, x2, y2;
    static HDC hdc;
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
