//http://www.coderonline.net/programming-windows-series-first-the-basic-framework-for-the-windows-sdk-programming.html

#include <windows.h>
#include <tchar.h>

static TCHAR szAppName[] = TEXT("Textout");
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
     
     hWnd = CreateWindow(szAppName,            // window class name
                          szAppName,           // window caption
                          WS_OVERLAPPEDWINDOW, // window style
                          CW_USEDEFAULT,       // initial x position
                          CW_USEDEFAULT,       // initial y position
                          400,                 // initial x size
                          300,                 // initial y size
                          NULL,                // parent window handle
                          NULL,                // window menu handle
                          hInstance,           // program instance handle
                          NULL);               // creation parameters
     
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
	HDC         hDC;
	PAINTSTRUCT ps;

	switch (message)
	{
	case WM_CREATE:
		return 0;
	case WM_PAINT:
		{
			RECT rect = {10, 30, 100, 50};
			TCHAR str[] = TEXT("English and 中文");

			hDC = BeginPaint(hWnd, &ps);
			TextOut(hDC, 10, 10, str, _tcslen(str));

			SetTextColor(hDC, RGB(255,0,0));
			DrawText(hDC, str, -1, &rect, DT_LEFT|DT_VCENTER);

			SetTextColor(hDC, RGB(0,255,0));
			INT dx[] = {8,8,8,8,16,8,8,8,16,8,8,8,10};
			ExtTextOut(hDC, 10, 50, 0, &rect, str, _tcslen(str), dx);

			SetTextColor(hDC, RGB(0,0,255));
			rect.right = 110;
			rect.top = 70;
			rect.bottom = 82;
			ExtTextOut(hDC, 10, rect.top, ETO_CLIPPED, &rect, str, _tcslen(str), dx);
			HFONT hFont = CreateFont(96,         // nHeight, 所创建字体的字符高度
						0,           // nWidth,       字体的字符平均宽度
						200,          // nEscapement,  字符输出方向与水平向右的方向所成角度,以0.1度为单位
						0,             // nOrientation, 字符与基线的角度，以0.1度为单位
						FW_BOLD,        // nWeight,      字符颜色的深浅度
						TRUE,            // bItalic,      斜体属性标志(FALSE:正常字体，TRUE:斜体)
						FALSE,            // bUnderline,   下划线属性标志(FALSE:无下划线，TRUE:有下划线)
						FALSE,             // cStrikeOut,   删除线属性标志(FALSE:无删除线，TRUE:有删除线)
						ANSI_CHARSET,       // nCharSet,        字符集标识0:ANSI字符集，1:系统缺省字符集
						OUT_DEFAULT_PRECIS,  // nOutPrecision,   输出精度
						CLIP_DEFAULT_PRECIS, // nClipPrecision,  剪切精度
						DEFAULT_QUALITY,      // nQuality,        输出品质
						DEFAULT_PITCH|FF_SWISS, // nPitchAndFamily, 字符间距
						TEXT("Arial"));          // lpszFacename,    现有系统TrueType字体名称
			HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);
			SetBkMode(hDC, TRANSPARENT);
			SetTextColor(hDC, RGB(0x00, 0xFF, 0xFF));
			TextOut(hDC, 0, 150, TEXT("创建Font"), 6);
			DeleteObject(hFont);
			EndPaint(hWnd, &ps);
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0 ;
	}
	return DefWindowProc (hWnd, message, wParam, lParam);
}









