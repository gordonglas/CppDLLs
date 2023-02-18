// STRPROG.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "STRPROG.h"
#include "strlib.h"
#include "resource.h"

typedef struct {
  HDC hdc;
  int xText;
  int yText;
  int xStart;
  int yStart;
  int xIncr;
  int yIncr;
  int xMax;
  int yMax;
} CBPARAM;

TCHAR szString[MAX_LENGTH + 1];

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
    LoadStringW(hInstance, IDC_STRPROG, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_STRPROG));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_STRPROG));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_STRPROG);
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
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
    hInst = hInstance;  // Store instance handle in our global variable

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
                              CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr,
                              nullptr, hInstance, nullptr);

    if (!hWnd) {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

INT_PTR CALLBACK DlgProc(HWND hDlg,
                         UINT message,
                         WPARAM wParam,
                         LPARAM lParam) {
    switch (message) {
        case WM_INITDIALOG:
            SendDlgItemMessage(hDlg, IDC_STRING, EM_LIMITTEXT, MAX_LENGTH, 0);
            return (INT_PTR)TRUE;
        case WM_COMMAND:
            switch (wParam) {
              case IDOK:
                GetDlgItemText(hDlg, IDC_STRING, szString, MAX_LENGTH);
                EndDialog(hDlg, TRUE);
                return (INT_PTR)TRUE;
              case IDCANCEL:
                EndDialog(hDlg, FALSE);
                return (INT_PTR)TRUE;
            }
    }
    return (INT_PTR)FALSE;
}

BOOL CALLBACK GetStrCallBack(PCTSTR pString, PVOID pvoid) {
    CBPARAM* pcbp = (CBPARAM*)pvoid;
    TextOut(pcbp->hdc, pcbp->xText, pcbp->yText, pString, lstrlen(pString));

    if ((pcbp->yText += pcbp->yIncr) > pcbp->yMax) {
        pcbp->yText = pcbp->yStart;
        if ((pcbp->xText += pcbp->xIncr) > pcbp->xMax)
            return FALSE;
    }
    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HINSTANCE hInst;
    static int cxChar, cyChar, cxClient, cyClient;
    static UINT iDataChangeMsg;
    CBPARAM cbparam;
    HDC hdc;
    PAINTSTRUCT ps;
    TEXTMETRIC tm;

    switch (message) {
        case WM_CREATE:
            hInst = ((LPCREATESTRUCT)lParam)->hInstance;
            hdc = GetDC(hWnd);
            GetTextMetrics(hdc, &tm);
            cxChar = (int)tm.tmAveCharWidth;
            cyChar = (int)(tm.tmHeight + tm.tmExternalLeading);
            ReleaseDC(hWnd, hdc);

            // Register message for notifying instances of data changes
            iDataChangeMsg = RegisterWindowMessage(TEXT("StrProgDataChange"));
            return 0;
        case WM_COMMAND: {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId) {
              case IDM_ENTER:
                if (DialogBoxW(hInst, MAKEINTRESOURCE(ENTERDLG), hWnd,
                               DlgProc)) {
                  if (AddString(szString))
                    PostMessage(HWND_BROADCAST, iDataChangeMsg, 0, 0);
                  else
                    MessageBeep(0);
                }
                break;
              case IDM_DELETE:
                if (DialogBoxW(hInst, MAKEINTRESOURCE(DELETEDLG), hWnd,
                               DlgProc)) {
                  if (DeleteString(szString))
                    PostMessage(HWND_BROADCAST, iDataChangeMsg, 0, 0);
                  else
                    MessageBeep(0);
                }
                break;
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
            return 0;
        case WM_SIZE:
            cxClient = (int)LOWORD(lParam);
            cyClient = (int)HIWORD(lParam);
            return 0;
        case WM_PAINT: {
            hdc = BeginPaint(hWnd, &ps);

            cbparam.hdc = hdc;
            cbparam.xText = cbparam.xStart = cxChar;
            cbparam.yText = cbparam.yStart = cyChar;
            cbparam.xIncr = cxChar * MAX_LENGTH;
            cbparam.yIncr = cyChar;
            cbparam.xMax = cbparam.xIncr * (1 + cxClient / cbparam.xIncr);
            cbparam.yMax = cyChar * (cyClient / cyChar - 1);

            GetStringsW((GETSTRCB)GetStrCallBack, (PVOID)&cbparam);

            EndPaint(hWnd, &ps);
            return 0;
        } break;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            if (message == iDataChangeMsg)
              InvalidateRect(hWnd, NULL, TRUE);
            break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
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
