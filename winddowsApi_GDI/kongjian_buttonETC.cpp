// http://www.coderonline.net/programming-windows-series-first-the-basic-framework-for-the-windows-sdk-programming.html

#include <windows.h>

#define IDC_STATIC1  1001
#define IDC_BUTTON1  1002
#define IDC_EDIT1    1003
#define IDC_FRAME1   1004
#define IDC_MALE     2001
#define IDC_FEMALE   2002
#define IDC_LISTBOX1 1005
#define IDC_CB1      1006
#define IDC_CKBRED   1007
#define IDC_CKBGRN   1008
#define IDC_CKBBLU   1009
#define IDC_SCB1     1010
#define IDC_SCB2     1011

static TCHAR szAppName[] = TEXT("HelloWin32");
static LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
   HWND     hWnd;
   MSG      msg;
   WNDCLASS wndclass;

   wndclass.style         = CS_HREDRAW | CS_VREDRAW;
   wndclass.lpfnWndProc   = WndProc;
   wndclass.cbClsExtra    = 0;
   wndclass.cbWndExtra    = 0;
   wndclass.hInstance     = hInstance;
   wndclass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
   wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
   wndclass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
   wndclass.lpszMenuName  = NULL;
   wndclass.lpszClassName = szAppName;

   if (!RegisterClass(&wndclass))
   {
      MessageBox (NULL, TEXT("This program requires Windows NT!"), szAppName, MB_ICONERROR);
      return 0;
   }

   hWnd = CreateWindow(szAppName,                  // window class name
                     szAppName,                 // window caption
                     WS_OVERLAPPEDWINDOW,        // window style
                     CW_USEDEFAULT,              // initial x position
                     CW_USEDEFAULT,              // initial y position
                     400,              // initial x size
                     300,              // initial y size
                     NULL,                       // parent window handle
                     NULL,                       // window menu handle
                     hInstance,                // program instance handle
                     NULL);                     // creation parameters

   ShowWindow(hWnd, iCmdShow);
   UpdateWindow(hWnd);

   while (GetMessage(&msg, NULL, 0, 0))
   {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
   }

   return msg.wParam;
}

static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
   HWND hCtrl;

   switch (message)
   {
   case WM_CREATE:
      CreateWindow(TEXT("STATIC"), TEXT("Test String"), WS_CHILD|WS_VISIBLE, 10, 10, 80, 20, hWnd, (HMENU)IDC_STATIC1, NULL, NULL);

      CreateWindow(TEXT("BUTTON"), TEXT("Click Me"), WS_CHILD|WS_VISIBLE, 10, 40, 80, 20, hWnd, (HMENU)IDC_BUTTON1, NULL, NULL);
      CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), NULL, WS_CHILD|WS_VISIBLE|WS_BORDER,  10, 70, 80, 20, hWnd, (HMENU)IDC_EDIT1, NULL, NULL);

      CreateWindow(TEXT("BUTTON"), TEXT("性别"), WS_CHILD|WS_VISIBLE|BS_GROUPBOX, 120, 10, 130, 50, hWnd, (HMENU)IDC_FRAME1, NULL, NULL);
      CreateWindow(TEXT("BUTTON"), TEXT("男"), WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON, 134, 30, 40, 20, hWnd, (HMENU)IDC_MALE, NULL, NULL);
      CreateWindow(TEXT("BUTTON"), TEXT("女"), WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON, 194, 30, 40, 20, hWnd, (HMENU)IDC_FEMALE, NULL, NULL);

      CreateWindow(TEXT("BUTTON"), TEXT("红色"), WS_CHILD|WS_VISIBLE|BS_CHECKBOX|BS_AUTOCHECKBOX, 120, 70, 54, 20, hWnd, (HMENU)IDC_CKBRED, NULL, NULL);
      CreateWindow(TEXT("BUTTON"), TEXT("绿色"), WS_CHILD|WS_VISIBLE|BS_CHECKBOX|BS_AUTOCHECKBOX, 180, 70, 54, 20, hWnd, (HMENU)IDC_CKBGRN, NULL, NULL);
      CreateWindow(TEXT("BUTTON"), TEXT("蓝色"), WS_CHILD|WS_VISIBLE|BS_CHECKBOX|BS_AUTOCHECKBOX, 240, 70, 54, 20, hWnd, (HMENU)IDC_CKBBLU, NULL, NULL);

      hCtrl = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("LISTBOX"), NULL, WS_CHILD|WS_VISIBLE|LBS_STANDARD, 10, 100, 80, 90, hWnd, (HMENU)IDC_LISTBOX1, NULL, NULL);
      SendMessage(hCtrl, LB_ADDSTRING, 0, (LPARAM)TEXT("list str1"));
      SendMessage(hCtrl, LB_ADDSTRING, 0, (LPARAM)TEXT("list str2"));
      SendMessage(hCtrl, LB_ADDSTRING, 0, (LPARAM)TEXT("list str3"));
      SendMessage(hCtrl, LB_ADDSTRING, 0, (LPARAM)TEXT("list str4"));

      hCtrl = CreateWindow(TEXT("COMBOBOX"), NULL, WS_CHILD|WS_VISIBLE|WS_VSCROLL|CBS_AUTOHSCROLL|CBS_DROPDOWNLIST, 120, 100, 100, 90, hWnd, (HMENU)IDC_CB1, NULL, NULL);
      SendMessage(hCtrl, CB_ADDSTRING, 0, (LPARAM)TEXT("comb str1"));
      SendMessage(hCtrl, CB_ADDSTRING, 0, (LPARAM)TEXT("comb str2"));
      SendMessage(hCtrl, CB_ADDSTRING, 0, (LPARAM)TEXT("comb str3"));
      SendMessage(hCtrl, CB_ADDSTRING, 0, (LPARAM)TEXT("comb str4"));
      SendMessage(hCtrl, CB_SETCURSEL, 1, 0);

      CreateWindow(TEXT("SCROLLBAR"), NULL, WS_CHILD|WS_VISIBLE|SBS_HORZ, 10, 200, 200, 20, hWnd, (HMENU)IDC_SCB1, NULL, NULL);
      CreateWindow(TEXT("SCROLLBAR"), NULL, WS_CHILD|WS_VISIBLE|SBS_VERT, 240, 100, 20, 120, hWnd, (HMENU)IDC_SCB2, NULL, NULL);
      return 0;

   case WM_COMMAND:
   {
      HWND hwndTmp;
      int wmId = LOWORD(wParam);
      switch (wmId)
      {
         case IDC_BUTTON1:
         hwndTmp = GetDlgItem(hWnd, IDC_STATIC1);
         SetWindowText(hwndTmp, TEXT("New Text"));
         MessageBox(hWnd, TEXT("Text Changed!"), TEXT("info"), MB_OK);
         break;
      }
   }
   return 0;

   case WM_CTLCOLORSTATIC:
   {
      HDC hdc = (HDC)wParam;
      SetTextColor(hdc, RGB(0xFF, 0x00, 0x00));
   }
   return (BOOL)((HBRUSH)GetStockObject(NULL_BRUSH));

   case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
   }

   return DefWindowProc (hWnd, message, wParam, lParam);
}











