/*
															  dddddddd
TTTTTTTTTTTTTTTTTTTTTTT                     iiii              d::::::d                   333333333333333    333333333333333
T:::::::::::::::::::::T                    i::::i             d::::::d                  3:::::::::::::::33 3:::::::::::::::33
T:::::::::::::::::::::T                     iiii              d::::::d                  3::::::33333::::::33::::::33333::::::3
T:::::TT:::::::TT:::::T                                       d:::::d                   3333333     3:::::33333333     3:::::3
TTTTTT  T:::::T  TTTTTTrrrrr   rrrrrrrrr  iiiiiii     ddddddddd:::::d uuuuuu    uuuuuu              3:::::3            3:::::3
		T:::::T        r::::rrr:::::::::r i:::::i   dd::::::::::::::d u::::u    u::::u              3:::::3            3:::::3
		T:::::T        r:::::::::::::::::r i::::i  d::::::::::::::::d u::::u    u::::u      33333333:::::3     33333333:::::3
		T:::::T        rr::::::rrrrr::::::ri::::i d:::::::ddddd:::::d u::::u    u::::u      3:::::::::::3      3:::::::::::3
		T:::::T         r:::::r     r:::::ri::::i d::::::d    d:::::d u::::u    u::::u      33333333:::::3     33333333:::::3
		T:::::T         r:::::r     rrrrrrri::::i d:::::d     d:::::d u::::u    u::::u              3:::::3            3:::::3
		T:::::T         r:::::r            i::::i d:::::d     d:::::d u::::u    u::::u              3:::::3            3:::::3
		T:::::T         r:::::r            i::::i d:::::d     d:::::d u:::::uuuu:::::u              3:::::3            3:::::3
	  TT:::::::TT       r:::::r           i::::::id::::::ddddd::::::ddu:::::::::::::::uu3333333     3:::::33333333     3:::::3
	  T:::::::::T       r:::::r           i::::::i d:::::::::::::::::d u:::::::::::::::u3::::::33333::::::33::::::33333::::::3
	  T:::::::::T       r:::::r           i::::::i  d:::::::::ddd::::d  uu::::::::uu:::u3:::::::::::::::33 3:::::::::::::::33
	  TTTTTTTTTTT       rrrrrrr           iiiiiiii   ddddddddd   ddddd    uuuuuuuu  uuuu 333333333333333    333333333333333
		 
		 //2019.10.13���ֳ���
		//ԭ���ԵĻ����Ե������ӻ���Ӧ����ʵѵ����Ȼ��ԹԵ���api����Ա�����ǲ�Ҫ���³�Bug֮�����ڽ�ȥ��Ͳ�ĵ�Bug,������������ô���������������⼼���͵�Bug
	   //����ڿ�дע�ͣ���ʵ�뵽һЩ�����д������ע�����ӭע�Ͳ���PR���ֿ�
	  //�������е�������ʲô�ͽ̵��鷳��ϵ2055969978@qq.com
	 // http://www.coderonline.net/programming-windows-series-first-the-basic-framework-for-the-windows-sdk-programming.html
*/

	 //�������ͼ��ѧ���ڶ��� �쳤��ȱ���
	 //ԭ��û��������룬��ѧ�ڸպ�ѧ����д�����������ɣ��������С�ʼǡ�ȡ����Ӧע������������У�vs2019����������X������������Y��������

#define PI 3.1415926

#include <stack>
#include<atlstr.h>
#include<iostream>
#include <windows.h>
#include <math.h>
#include <vector>




using namespace std;

//ע�ᴰ������
static TCHAR szAppName[] = TEXT("GDI_Tridu33");

//���� ���ڹ��̺���
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//������ں��� extern "C" int __stdcall WinMain // int WINAPI WinMainд������Ҳ��
extern "C" int __stdcall WinMain(HINSTANCE hInstance, 
								HINSTANCE hPrevInstance, 
								PSTR szCmdLine, 
								int iCmdShow)
{
	HWND     hWnd;
	MSG      msg;
	WNDCLASS wndclass;
//���촴�����ڲ���
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
//ע�ᴰ������
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"), szAppName, MB_ICONERROR);
		return 0;
	}
//�������ڣ�szAppNameһ��Ҫ��ע�������
	hWnd = CreateWindow(szAppName,            // window class name
		szAppName,           // window caption
		WS_OVERLAPPEDWINDOW, // window style
		CW_USEDEFAULT,       // initial x position
		CW_USEDEFAULT,       // initial y position
		500,                 // initial x size
		500,                 // initial y size
		NULL,                // parent window handle
		NULL,                // window menu handle
		hInstance,           // program instance handle
		NULL);               // creation parameters

	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0))// ��ȡ��Ϣ�������յ�WM_QIUT��Ϣʱ��GetMessage��������0������ѭ��
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);// �ɷ���Ϣ����WindowPro��������
	}

	return msg.wParam;
}


//--------------------------------------------------------------------------------------------------
//�����ķָ��ߣ��ⲿ����ͼ��ѧ�㷨ʵ�־��巽������
//--------------------------------------------------------------------------------------------------

//����ָ�����Ե�ֱ��
static void DrawLine(HDC hDC, int x0, int y0, int x1, int y1, int style, int width, COLORREF color)
{
	HPEN hPen = CreatePen(style, width, color);
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);

	MoveToEx(hDC, x0, y0, NULL);
	LineTo(hDC, x1, y1);

	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);
}

//����ʵ��Բ
static void DrawCircle(HDC hDC, int x, int y, int len, COLORREF color)
{
	HBRUSH hBrush = CreateSolidBrush(color);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	HPEN hPen = CreatePen(PS_SOLID, 1, color);
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);

	Ellipse(hDC, x - len / 2, y - len / 2, x + len / 2, y + len / 2);

	SelectObject(hDC, hOldBrush);
	DeleteObject(hPen);

	SelectObject(hDC, hOldPen);
	DeleteObject(hOldBrush);
}

//����������
static void DrawRect(HDC hDC, int left, int top, int width, int height, int style, COLORREF color)
{
	HBRUSH hBrush = CreateHatchBrush(style, color);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	Rectangle(hDC, left, top, left + width, top + height);

	SelectObject(hDC, hOldBrush);
	DeleteObject(hOldBrush);
}

//����λͼ������
static void DrawBmpRect(HDC hDC, int left, int top, int width, int height, LPCTSTR file)
{
	HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, file, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	HBRUSH hBrush = CreatePatternBrush(hBitmap);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	Rectangle(hDC, left, top, left + width, top + height);

	SelectObject(hDC, hOldBrush);
	DeleteObject(hOldBrush);
	DeleteObject(hBitmap);
}

//-----------------------------------------------------------------

int label8;
//ȫ�ֱ���label����12345678������Ĳ�ͬ���ͣ�����������һ��������㷨�������������䣨0<=k<=1��k>1�Ȱ˸����䣩ֱ�ߣ�Բ�ȶԳƽṹ��ͼ������������η��ζԳƵ�ͼ��
//ͬ����Ըĳɶ��ȷֵ��������ĶԳ�label2,��Գ�label2x,label2y,�ĵȷֵ�ͼ��label4
//�˵ȷֵ�����ϵ�����任ƪ,ͨͨ���ұ�ɵ�һ����0<=k<=1�������������mySetPixel��switch(label8)case����ƥ���Ӧ���޵���任����
//Ascci��˷�����ͼ�����鿴��ĩAscii�ַ�ͼ��

//�㷨����:

//1. ������2345678��任��1����

static int labelMark(int x, int y) {
	int t;
	if (x >= 0)
		if (y >= 0)
			if (fabs(x) >= fabs(y))
			{
				x = x;y = y;label8 = 1;
			}
			else
			{
				t = x;x = y;y = t;label8 = 2;
			}
		else
			if (fabs(x) >= fabs(y))
			{
				x = x;y = -y;label8 = 8;
			}
			else
			{
				t = -x;x = y;y = t;label8 = 7;
			}
	else
		if (y >= 0)
			if (fabs(x) >= fabs(y))
			{
				x = -x;y = y;label8 = 4;
			}
			else
			{
				t = x;x = -y;y = t;label8 = 3;
			}
		else
			if (fabs(x) >= fabs(y))
			{
				x = -x;y = -y;label8 = 5;
			}
			else
			{
				t = -x;x = -y;y = t;label8 = 6;
			}
	return label8;
}

//2. ����������1����Ĵ��룬���续�˷�֮һԲ����ʹ��������0<=k<=1 && x>=0 && y>= 0����ֱ�߼���õ�����������SetPixel����ͨͨ����mySetPixel
//3. �˵ȷݵ�����ϵ��case��任mySetPixelƪ,���鿴��ĩAsciiͼ��
//���˰˵ȷݶԳƱ任������ͨ����ת����ÿ����ת45��õ������

static void mySetPixel(HDC hDC, COLORREF color,int x,int y) {
	switch (label8){
	case 1|5: SetPixel(hDC, x, y, color);
	case 2|6: SetPixel(hDC, y, x, color);
	case 7|3: SetPixel(hDC, y, -x, color);
	case 8|4: SetPixel(hDC, x, -y, color);
	default: 
		;// ?��ô���printf "��������"�Ľ��;
	}
}


//---------------------------------------






//����ֱ������㷨
// DDAֱ��ɨ��ת���㷨//б�ʲ����ڣ��ܶ��߲��������⻭������ȫ��һ���Ķ��У�����e��ĸ��С��ʱ��ᵼ�¼���ʧ�棬���������յ㲻��ȷ�Ļ������ɺܶ��͵�һ����ȫ���ܿ�����
static void DDALine(HDC hDC,COLORREF color, double x1, double y1, double x2, double y2) {
	HBRUSH hBrush = CreateSolidBrush(color);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	double dx, dy, e, x, y;
	dx = x2 - x1;
	dy = y2 - y1;
	e = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);
	dx /= e;dy /= e;
	x = x1;
	y = y1;
	for (int i = 1;i <= e;i++) {
		SetPixel(hDC,(int)(x + 0.5), (int)(y + 0.5),color);
		x += dx;
		y += dy;
	}
	SelectObject(hDC, hOldBrush);
	DeleteObject(hOldBrush);
}
//�е㻭���㷨
static void MidpointLine(HDC hDC, COLORREF color, int x0, int y0, int x1, int y1) {
	int a, b, d, delta1, delta2,x,y;
	a = y0 - y1;
	b = x1 - x0;
	d = 2 * a + b;
	delta1 = 2 * a;
	delta2 = 2 * (a + b);
	x = x0;
	y = y0;
	SetPixel(hDC,x, y,color);
	while (x < x1)
	{
		if (d < 0)
		{
			x++;
			y++;
			d += delta2;
		}
		else {
			x++;
			d += delta1;
		}
		SetPixel(hDC,x, y,color);
	}
}

//BresenhamLine�㷨//0<=m<zб�ʵ�һ������labelMark==1��
static void BresenhamLine1(HDC hDC, COLORREF color, int x1, int y1, int x2, int y2) {
	int x, y, dx, dy,p;
	x = x1;
	y = y1;
	dx = x2 - x1;
	dy = y2 - y1;
	p = 2 * dy - dx;
	for (;x < x2;x++) {
		SetPixel(hDC,x, y,color);
		if (p >= 0)
		{
			y++;
			p += 2 * (dy - dx);
		}
		else
		{
			p += 2 * dy;
		}
	}
}
//BresenhamLine�㷨8�ȷֵڰ�����//-1<=m<0б�ʵ���������labelMark==8��
static void BresenhamLine8(HDC hDC, COLORREF color, int x1, int y1, int x2, int y2) {
	int x, y, dx, dy, p,delta1,delta2;
	x = x1;
	y = y1;
	dx = x2 - x1;
	dy = y2 - y1;
	p = 2 * dy - dx;
	delta1 = 2 * dy;
	delta2 = 2 * (dy+dx);
	for (;x < x2;x++) {
		SetPixel(hDC, x, y, color);
		if (p >= 0)
		{
			p += 2 * delta1;
		}
		else
		{
			y--;
			p += 2 *delta2;
		}
	}
}





// �е㻭Բ�㷨
static void MidpointCircle(HDC hDC, int R, COLORREF color) {

	HBRUSH hBrush = CreateSolidBrush(color);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	int x, y;double d;//double d253d+=2x����
	x = 0;y = R;d = 1.25 - R;
	
	SetPixel(hDC, x, y, RGB(255, 0, 0));
	while (x < y) {
		if (d < 0) {
			d += 2 * x+3;
			x++;
		}
		else {
			d += 2 * (x-y)+5;
			x++;
			y--;
		}SetPixel(hDC, x, y, RGB(255, 0, 0));
	}
	SelectObject(hDC, hOldBrush);
	DeleteObject(hOldBrush);
}

static void MidpointCircle1(HDC hDC, int R, COLORREF color) {

	HBRUSH hBrush = CreateSolidBrush(color);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	int x, y, d;
	x = 0;y = R;d = 1 - R;

	SetPixel(hDC, x, y, RGB(255, 0, 0));
	while (x < y) {
		if (d < 0) {
			d += 2 * x + 3;
			x++;
		}
		else {
			d += 2 * (x - y) + 5;
			x++;
			y--;
		}SetPixel(hDC, x, y, RGB(255, 0, 0));
	}
	SelectObject(hDC, hOldBrush);
	DeleteObject(hOldBrush);
}

static void MidpointCircle2(HDC hDC, int R, COLORREF color) {

	HBRUSH hBrush = CreateSolidBrush(color);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	int x, y, delta1, delta2, d;
	x = 0;y = R;d = 1 - R;
	delta1 = 3;
	delta2 = 5 - R - R;
	SetPixel(hDC, x, y, RGB(255, 0, 0));
	while (x < y) {
		if (d < 0) {
			d += delta1;
			delta1 += 2;
			delta2 += 2;
			x++;
		}
		else {
			d += delta2;
			delta1 += 2;
			delta2 += 4;
			x++;
			y--;
		}SetPixel(hDC, x, y, RGB(255, 0, 0));
	}
	SelectObject(hDC, hOldBrush);
	DeleteObject(hOldBrush);
}

// Bresenham��Բ�㷨
static void BresenhamCircle(HDC hDC, int R, COLORREF color) {
	HBRUSH hBrush = CreateSolidBrush(color);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	int x, y, p;
	x = 0;
	y = R;
	p = 3 - 2 * R;
	for (;x < y;x++) {
		SetPixel(hDC,x, y, color);
		if (p >= 0) {
			p += 4 * (x - y) + 10;y--;
		}
		else {
			p += 4 * x + 6;
		}
	}
	SelectObject(hDC, hOldBrush);
	DeleteObject(hOldBrush);
}

//��һ������Բ����ɨ��ת���е��㷨
static void MidpointEllipse(HDC hDC, COLORREF color,int a,int b) {
	;
}

//Temple
/*  
static void function(HDC hDC,COLORREF color,){
	HBRUSH hBrush = CreateSolidBrush(color);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	SelectObject(hDC, hOldBrush);
	DeleteObject(hOldBrush);
}
*/
//��亯��Ҫ�Ȼ�������ͨͼ���������	
//DrawRect(hDC, 220, 20, 60, 40, HS_BDIAGONAL, RGB(255, 0, 0));����������㷨ǰ������У�Ȼ������ѡһ���ڵ�
//������Լ�����߽���RGB(0,0,0)��ɫ�����RGB(0,255,0)��ɫ��oldvalue������ɫRGB(255,255,255),newvalue��RGB(0,0,255)��ɫ,COLORREF color�����۾������ú�ɫRGB(255,0,0)

// ����ͨ�ڶ������������㷨
//extern int globalCount;//ͳ���ж�ִ�д�����������������
//void Floodfill(HDC hDC, COLORREF color, int x, int y, COLORREF oldvalue, COLORREF newvalue) {
static	void Floodfill(HDC hDC,int x, int y, COLORREF oldvalue, COLORREF newvalue) {
	while (GetPixel(hDC,x, y) == oldvalue) {
		SetPixel(hDC,x, y, newvalue);
		Floodfill(hDC,x, y - 1, oldvalue, newvalue);
		Floodfill(hDC,x, y + 1, oldvalue, newvalue);
		Floodfill(hDC,x - 1, y, oldvalue, newvalue);
		Floodfill(hDC,x + 1, y, oldvalue, newvalue);
	}
}

// ����ͨ�߽綨�����������㷨
static void Boundaryfill(HDC hDC, int x, int y, COLORREF boundaryvalue, COLORREF newvalue) {
	//(x,y)�Ǹ���������λ�ã�boundary�Ǳ߽������ص�ֵ��newvalue������������Ӧ�ñ��������ֵ��δ���������ڲ�Ӧ��ֵΪnewvalue��ֵ����һ�����ͼ��Ļ��ᱻ��ס������䲻��
	while (GetPixel(hDC, x, y) != boundaryvalue && (hDC, x, y) != newvalue )//δ����߽�����ֵ����δ������
	{
		SetPixel(hDC, x, y, newvalue);
		Boundaryfill(hDC, x, y - 1, boundaryvalue, newvalue);
		Boundaryfill(hDC, x, y + 1, boundaryvalue, newvalue);
		Boundaryfill(hDC, x - 1, y, boundaryvalue, newvalue);
		Boundaryfill(hDC, x + 1, y, boundaryvalue, newvalue);
//������������������������������������������������������������������������������������������������
	}
}



/*


// ɨ��ֱ����������㷨 P34�ܳ�
void ScanlineSeedfill(HDC hDC, int x, int y, COLORREF boundaryvalue, COLORREF newvalue)
{
	using namespace std;
	int x0, x1, xr, y0, xid;
	bool flag;
	int count = 0;
	stack <Point> s;//������Point��������û�������ʶ��
	//???????????????????????????????????????????????????????????????????????

	struct Point {
	int x;
	int y;
	};

Point p;
s.push(Point(x, y));//?????Point��Ԫ�飿����Point::Point{}?�ṹ�壿

while (!s.empty()) {
	p = s.top();
	s.pop();
	x = p.x;
	y = p.y;
	SetPixel(hDC, x, y, newvalue);
	x0 = x + 1;
	while (GetPixel(hDC, x0, y) != boundaryvalue && GetPixel(hDC, x0, y) != newvalue) {
		SetPixel(hDC, x0, y, newvalue);
		x0++;
	}
	xr = x0 + 1;//right
	x0 = x - 1;
	while (GetPixel(hDC, x0, y) != boundaryvalue && GetPixel(hDC, x0, y) != newvalue) {
		SetPixel(hDC, x0, y, newvalue);//left
		x0--;
	}
	x1 = x0 + 1;
	y0 = y;
	for (int i = 1;i >= -1;i -= 2) {
		x0 = xr;
		y = y0 + i;
		while (x0 >= x1) {
			flag = false;
			while (GetPixel(hDC, x0, y) != boundaryvalue && GetPixel(hDC, x0, y) != newvalue && x0 >= x1) {
				if (!flag) { flag = true;xid = x0; }
				x0--;
			}
			if (flag) {
				s.push(Point(xid, y));/////??????
				flag = false;

			}
			while (GetPixel(hDC, x0, y) != boundaryvalue && GetPixel(hDC, x0, y) != newvalue && x0 >= x1) {
				x0--;
			}
		}//while (x0>=x1) 	
	}//for (int i = 1;i >= -1;i -= 2)
}//while(!s.empty())






}


//P36�����ɨ��ת���㷨

//P40 ������㷨

//�߱�־�㷨























//ͼ����� P43

//P72. Cohen-Sutherland�㷨(ֱ�߶βü��㷨)
void Cohen_Sutherland(double x0,y0,x2,y2){
	;
}
// �޸�Cohen_Sutherlandֱ�߲ü�ֱ���㷨������Ч���������ڲ��������ⲿ����
//

*/



//��ֵ���������㷽�� ����˷���ͶӰ����,ͼ�ζ�ά��ά����任��������㣬����ת����ƽ�ƾ���͸�Ӿ��󣬲ü�����������ֱ��������������������໥ӳ��

vector<vector<int>> matrix_multiply(vector<vector<int>> arrA, vector<vector<int>> arrB)
{
	//����arrA������
	int rowA = arrA.size();
	//����arrA������
	int colA = arrA[0].size();
	//����arrB������
	int rowB = arrB.size();
	//����arrB������
	int colB = arrB[0].size();
	//��˺�Ľ������
	vector<vector<int>>  res;
	if (colA != rowB)//�������arrA�����������ھ���arrB���������򷵻ؿ�
	{
		return res;
	}
	else
	{
		//���ý������Ĵ�С����ʼ��ΪΪ0
		res.resize(rowA);
		for (int i = 0; i < rowA; ++i)
		{
			res[i].resize(colB);
		}

		//�������
		for (int i = 0; i < rowA; ++i)
		{
			for (int j = 0; j < colB; ++j)
			{
				for (int k = 0; k < colA; ++k)
				{
					res[i][j] += arrA[i][k] * arrB[k][j];
				}
			}
		}
	}
	return res;
}



/*���þ���˷�����
	vector<vector<int>> arrA = { { 2, 1 }, { 4, 3 } };
	vector<vector<int>> arrB = { { 1, 2 }, { 1, 0 } };
	//vector<vector<int>> arrA = { { 1, 2, 3 }, { 4, 5, 6 } };
	//vector<vector<int>> arrB = { { 1, 4 }, { 2, 5 }, { 3, 6 } };

	vector<vector<int>> res = matrix_multiply(arrA, arrB);

//��������������������������������
//��ά�任����P(x,y,1)��P'(x',y',1)

	int Tx=1;int Ty=2;
	vector<vector<int>> arrp = { {x,y,1 }};
	vector<vector<int>> arrPan= { { 1, 0,0 }, { 0,1, 0 } ,{Tx,Ty,1}};
	vector<vector<int>> arrp' = matrix_multiply(arrp, arrPan);

	int Sx=2;Sy=2;
	vector<vector<int>> arrp = { {x,y,1 }};
	vector<vector<int>> arrZoom= { {Sx, 0,0 }, { 0,Sy, 0 } ,{0,0,1}};
	vector<vector<int>> arrp' = matrix_multiply(arrp, arrZoom);

	int theta = pi;//double��úܶ࣬���Ǽ������DoubleȻ��������int
	//�������ת��ʲôʱ��ʼ���ʣ�����������������������������������������������
	vector<vector<int>> arrp = { {x,y,1 }};
	vector<vector<int>> arrRotate= { { cos(theta),sin(theta),0 }, {-sin(theta),cos(theta),0 } ,{0,0,1}};
	vector<vector<int>> arrp' = matrix_multiply(arrp, arrRotate);

	int a=1;int d=2;int b=3;int e=4;
	vector<vector<int>> arrp = { {x,y,1 }};
	vector<vector<int>> arrSymmetry= { {a,d,0 }, {b,e, 0 } ,{0,0,1}};
	vector<vector<int>> arrp' = matrix_multiply(arrp, arrSymmetry);

	int b=1;int d=2;
	vector<vector<int>> arrp = { {x,y,1 }};
	vector<vector<int>> arrMiscut= { {1, d,0 }, { b,1, 0 } ,{0,0,1}};
	vector<vector<int>> arrp' = matrix_multiply(arrp, arrMiscut);

	//��ά�Ӽ��任�ľ�����ʽ��������ͬ��ɵã���Ϊ�Ƚϸ��ӣ����£�
	vector<vector<int>> arrp = { {x,y,1 }};
	vector<vector<int>> arrView= { {(vxh-vxl)/(wxh-wxl),0,0 }, { 0,(vyh-vyl)/(why-wyl), 0 } ,{vxl-wxl*(vxh-vxl)/(wxh-wxl),vyl-wyl*(vyh-vyl)/(why-wyl),1}};
	vector<vector<int>> arrp' = matrix_multiply(arrp, arrView);
	//????????���׳��������Double����ʲô���ʣ�����������������������int��long?Double?



	//��ά����任

	int Dx=1;int Dy=2;int Dz=1;
	vector<vector<int>> arrp = { {x,y,z,1 }};
	vector<vector<int>> arrPan= {{ 1,0, 0,0 }, { 0,1, 0,0 }, { 0,0,1, 0 } ,{Dx,Dy,Dz,1}};
	vector<vector<int>> arrp' = matrix_multiply(arrp, arrPan);

	int Sx=2;Sy=2;
	vector<vector<int>> arrp = { {x,y,z,1 }};
	vector<vector<int>> arrZoom= { {Sx, 0,0 ,0}, { 0,Sy,0, 0 } ,{0,0,Sz,0},{(1-Sx)*x0,(1-Sy)*y0,(1-Sz)*z0,1}};
	vector<vector<int>> arrp' = matrix_multiply(arrp, arrZoom);

	int theta = pi;//double��úܶ࣬���Ǽ������DoubleȻ��������int
	//�������ת��ʲôʱ��ʼ���ʣ�����������������������������������������������
	vector<vector<int>> arrp = { {x,y,z,1 }};//Z
	vector<vector<int>> arrRotate= { { cos(theta),sin(theta),0 ,0}, {-sin(theta),cos(theta),0,0 } ,{0,0,1,0},{0,0,0,1}};
	vector<vector<int>> arrp' = matrix_multiply(arrp, arrRotate);

	vector<vector<int>> arrp = { {x,y,z,1 }};//X
	vector<vector<int>> arrRotate= { {1,0,0,0},{ 0,cos(theta),sin(theta),0 }, {0,-sin(theta),cos(theta),0 } ,{0,0,0,1}};
	vector<vector<int>> arrp' = matrix_multiply(arrp, arrRotate);

	vector<vector<int>> arrp = { {x,y,z,1 }};//Y
	vector<vector<int>> arrRotate= { { cos(theta),0,sin(theta),0 }, {0,1,0,0},{-sin(theta),0,cos(theta),0 } ,{0,0,0,1}};
	vector<vector<int>> arrp' = matrix_multiply(arrp, arrRotate);

	//������ֱ任�����������ܳ�Ϊ�ܸ��ӵı任����P61

	//����ͶӰ
	//����ͼ
	vector<vector<int>> arrFrontView= {{ 0,0, 0,0 }, { 0,1, 0,0 }, { 0,0,1, 0 } ,{0��0��0,1}};
	//����ͼ
	vector<vector<int>> arrSideView= {{ 1,0, 0,0 }, { 0,0, 0,0 }, { 0,0,1, 0 } ,{0��0��0,1}};
	//����ͼ
	vector<vector<int>> arrTopView= {{ 1,0, 0,0 }, { 0,1, 0,0 }, { 0,0,0, 0 } ,{0��0��0,1}};
	//б��ͶӰ
	vector<vector<int>> arrTopView= {{ 1,0, 0,0 }, { 0,1, 0,0 }, { l*cos(alpha),l*sin(alpha),0, 0 } ,{0��0��0,1}};
	//����͸��Single point perspective

	//2��͸��Two point perspective

	//3��͸��Three point perspective


	//͸��ͶӰתƽ��ͶӰ����P???????????


//blog.csdn.net/yang20141109/article/details/51024373

//------------------------------------------------------------------------------�Զ�......
//C++������������άͼ�α任�������������ӻ���
/*

class Complex
{
public:
	Complex(double r,double i);
	Complex operator+(const Complex c);
	Complex operator-(const Complex &c);
	Complex  operator *(const Complex &c);
	Complex operator/(const Complex &c);
	Complex &operator+=(const Complex c);
	Complex &operator-=(const Complex c);
	bool operator==(const Complex &c);
	Complex operator++();
	Complex operator++(int);
	Complex operator--();
	Complex operator--(int);

	void print(Complex &c);
	//~Complex();//��������

private:
	double _real;
	double _image;
};

Complex::Complex(double r=0.0,double i=0.0)
{
	_real=r;//����ʵ��
	_image=i;//�����鲿
}
Complex Complex:: operator+(const Complex c)//���������
{
	Complex tmp;
	tmp._real =_real+c._real ;
	tmp._image =_image+c._image ;
	return tmp;
}
Complex Complex::operator-(const Complex &c)//���������                                    c��ֵ�ں����ڲ�����Ҫ�ı䣬���Բ��ó�����
{
	Complex tmp;
	tmp._real =_real-c._real ;
	tmp._image =_image-c._image ;
	return tmp;
}
Complex Complex::operator*(const Complex &c)//(a+bi)(c+di)=(ac-bd)+(bc+ad)i.
{
	Complex tmp;
	tmp._real=_real*c._real-_image*c._image;
	tmp._image= _image*c._real +_real*c._image;
	return tmp;
}
Complex Complex::operator/(const Complex &c)//(a+bi)(c-di)/(c+di)(c-di)
	////(ac+bd)/(c^2+d^2)+(bc-ad)/(c^2+d^2)i
{
	Complex tmp;
	double deno=c._real*c._real+c._image*c._image;//������ķ�ĸdenominator
	tmp._real=deno*((_real*c._real)+(_image*c._image));
	tmp._image=deno*((_image*c._real )-(_real*c._image));
	return tmp;
}
Complex& Complex ::operator+=(const Complex c)//��������
{
	this->_real += c._real ;
	this->_image += c._image ;
	return *this;
}
Complex& Complex::operator-=(const Complex c)//��������
{
	this->_real -= c._real ;
	this->_image -= c._image ;
	return *this;
}
bool Complex::operator==(const Complex &c)//�ж����������Ƿ����
{
	return(_real==c._real)&&(_image==c._image);
}
Complex Complex::operator++()//ǰ��++
{
	this->_real+=1;
	this->_image+=1;
	return *this;
}
Complex Complex::operator++(int)//����++
{
	Complex tmp(*this);//����������������ԭ����ֵ
	this->_real++;
	this->_image++;
	return tmp;//������ʱ�������Բ�����������Ϊ����ֵ
}
Complex	Complex::operator--()//ǰ��--
{
	this->_real-=1;
	this->_image-=1;
	return *this;
}
Complex Complex::operator--(int)//����--
{

	Complex tmp(*this);//����������������ԭ����ֵ
	this->_real--;
	this->_image--;
	return tmp;//������ʱ�������Բ�����������Ϊ����ֵ
}

void Complex::print(Complex &c)
{
	cout<<c._real<<"+ "<<c._image<<"i"<<endl;
}

��������������������������������
//���ӣ�https://blog.csdn.net/wodeqingtian1234/article/details/51838888

//ʹ�÷�������
	Complex *c=NULL;
	Complex c1(6.0,5.0);
	Complex c2(3.0,4.0);
	Complex ret;
	cout<<(c1==c2)<<endl;//���c1,c2�Ƿ����
	c->print(c1);//���c1+c2
	c->print(c2);
	cout<<"c1+c2=";
	ret=c1+c2;
	c->print(ret);
	c->print (c1);//���c1�Լ�
	ret=++c1;
	c->print(ret);//

*/



//C++��Ԫ�����������λʸ��ͼ�Σ����Ӽ���---�������(Bloch Sphere)��ʾ��Ӧ�ġ�����λ---��������״̬��
//������ѧ�У� Dirac����ʵ�������������ô���ģ��Ѷ�Ӧ����ʽ�����������ʵ�֡���Դ����λ����QPanda��PyPanda������

/*
//�������� https://download.csdn.net/download/wf20080798/4926593 �������޵���Ԫ������
//ָ·��https://blog.csdn.net/zhuoyueljl/article/details/70789472 ��Ԫ����ŷ���ǡ���ת����֮�以��ת��C++Դ��
//https://blog.csdn.net/jin_syuct/article/details/49785541 ��Ԫ����ֵ
//̫���ˣ������ļ����п�������˵�ɣ�ңң����......
*/



//C++����Meshgrid��matlab����׾ٵ�Meshgrid����ά����ϵ��������ͼ����ô����������������������������������������������������������������������
/*
//������������������������������
*/

/*
//�ü��㷨 ������
//P72. Cohen-Sutherland�㷨(ֱ�߶βü��㷨)
void Cohen_Sutherland(double x0,y0,x2,y2){
	;
}
// �޸�Cohen_Sutherlandֱ�߲ü�ֱ���㷨������Ч���������ڲ��������ⲿ����
//
//
void Cohen_Sutherland(double x0,y0,x2,y2){
	;
}//P 73

//P82




//���Ѷ�-Barsky�ü��㷨
//P75. ��ά���Ѷ��㷨
void L_Barsky(double x0,y0,x2,y2){
	double t0,t1,deltax,deltay;
	t0=0.0;t1=1.0;
	deltax==x2-x1;
	if(!cansee(-deltax,x0-x1,t0,t1))return;
	if(!cansee(deltax,));
}


//P82. ��ά���Ѷ��㷨
Double zh,zy;
void T_Barsky(double x0,y0,x2,y2,z2){
	;
}

*/


//���������½ڣ��������ߣ���������B���������ֲ�ֵ�㷨
/*
//�������ղ�ֵ




//����Hermite��ֵ



//�淶������Hermite��ֵ


//Coons����

//Bezier���߼�����ͼ�㷨 P 107
void bez_to_points(Point P[] ,int n ,Point pts[],int npoints){
	;
}
//���ѹ����㷨 P110
void split_Bezier(Point P[]){
	;
}

void new_split_Bezier(Point P[]){
	;
}
//Bezier����







//B������           de Boor�㷨
//�������CPΪ���Ƶ�����
//���Ƶ�P�ĸ���Ϊn+1��
//�������k��B�����߲���
//�������knotΪ�ڵ�����������n+k+1
//�����������deBoor�㷨����B�����ߵ���ɢ������pts
//������ɢ������pts�ĸ���npoints+1
static void bspline_to_points(){
	;
}

//B����������


*/

//������ͼ������,�������㽻��������ֱ�߽��㣬͹�����㼸�Σ����ι�ϵ�����жϣ���Բ˫���߽����ڻ���ֱ�߲ü�������
/*

//�߶ν���
int jiaodian_line(){

return 1;
}

//�����߶ν���

int jioadian_lines(){


return 1;
}



//ƽ���͹��Graham�㷨
int Polygon_Polygon(POINT P[],int n,POINT Q[],int m){

}

//155
void Graham(POINT S[],int n)
{

}

void Javis(POINT S[],int n){

}

//�򵥶���εİ����㷨
//158
void inner(POINT X[],int n,POINT P){


}


͹����εİ����㷨
//160
void inner1(){
}







//͹������ص��㷨
void Advance(POINT P[],int n ,POINT Q[],int m){



}
void Output(POINT P[],int 1,POINT Q[],int m){


}
void Convex_polygon_intersection(POINT P[],int 1,POINT Q[],int m){

}


//�򵥶���ε������ʷ��㷨
//164
void Simple_polygon_triangulation(POINT *P,int n){

}











*/

//�˿���Mooc---���㼸������½�
/*





*/

/*
//����ı�ʾ�Լ����ݽṹ
//���ߣ����ַ�

//���ߣ������� P171
BINARY *Create(float *P,int i ,int j,float W){
	;
}
//��ͬ�ֱ�����ʾ������ʾ������
void Display(){
	;
}
//�����Ĳ���

//�����Ĳ���

//һ����ʱ�Ĳ���


//��άʵ��

//������Ϣ+������Ϣ
//��->��->��->��->���->����->���أ�1��Ԫʵ��2ɨ����3������ռ䶨�������{��x,y,z��|f(x,y,z)<=0}

//1.CSG��ʵ�弸�ι��취��CSG��::=<>|<><><>|<><><> BNF��ʽ�Ķ���
//2.������ʾ����״���ȼ���Ҫ�����......

//3.�߽��ʾ!!!�����У�
//�˲���
TREE *tree_8(cube c,graph g){
	;
}


*/


//------------------------------�����½ڷֽ���----------------------------------------------------


//�����½ڣ���Ȥ��ͼ�Σ����εȣ��ο��ﲩ�ĵġ������㷨�������ƣ�Visual C++ʵ�֡�����β��������ִ�Ĵ��룬�Ƽ����Ӻ��鱾��
static void Fractal(HDC hDC, double ax, double ay, double bx, double by)
{
	int c = 100;
	if (((bx - ax) * (bx - ax) + (by - ay) * (by - ay)) < c)
	{
		MoveToEx(hDC, ax + 50, 360 - ay, NULL);
		LineTo(hDC, bx + 50, 360 - by);
	}
	else
	{
		double cx, cy, dx, dy, ex, ey;
		double l, alfa;
		cx = ax + (bx - ax) / 3;  cy = ay + (by - ay) / 3;
		ex = bx - (bx - ax) / 3;  ey = by - (by - ay) / 3;
		Fractal(hDC,ax, ay, cx, cy);
		Fractal(hDC,ex, ey, bx, by);
		l = sqrt((ex - cx) * (ex - cx) + (ey - cy) * (ey - cy));
		alfa = atan((ey - cy) / (ex - cx));
		if (alfa >= 0 && (ex - cx) < 0 || alfa < 0 && (ex - cx) < 0)
			alfa = alfa + PI;
		dx = cx + cos(alfa + PI / 3) * l;
		dy = cy + sin(alfa + PI / 3) * l;
		Fractal(hDC,cx, cy, dx, dy);
		Fractal(hDC,dx, dy, ex, ey);
	}
}

//����ο��ﲩ�ĵġ������㷨��������:Visual C++ʵ�֡�
//��������������������������������
//��Ȩ����������ΪCSDN������ҹ�и衹��ԭ�����£���ѭ CC 4.0 BY - SA ��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
//ԭ�����ӣ�https ://blog.csdn.net/qaz2549066580/article/details/41290877



//�ⲿ�ֿ��ܺ�ǰ�����ĸ����ظ����壬��Ҫ����ȡ��ע�;��У���Ϊ�����Ѿ��ܶ��ˣ�
//������� https://www.cnblogs.com/easymind223/archive/2012/07/05/2578231.html
//�������� https://blog.csdn.net/xizhibei/article/details/6664184
//�Ͳ��ظ����ϴ���������һ�������Եķ��ε�ͨ�������£�
//��������������������������������
//��Ȩ����������ΪCSDN������ʮ���಻����ԭ�����£���ѭ CC 4.0 BY - SA ��ȨЭ�飬ת���븽��ԭ�ĳ������Ӽ���������
//ԭ�����ӣ�https ://blog.csdn.net/zhangpiu/article/details/49511107



/*
class CComplex
{
public:
	~CComplex() {};

	CComplex(long double real = 0, long double imag = 0)
		: m_real(real)
		, m_imag(imag)
	{}

	CComplex& operator +=(const CComplex& rhs)
	{
		this->m_real += rhs.m_real;
		this->m_imag += rhs.m_imag;

		return *this;
	}

	CComplex& operator -=(const CComplex& rhs)
	{
		this->m_real -= rhs.m_real;
		this->m_imag -= rhs.m_imag;

		return *this;
	}

	friend CComplex operator +(const CComplex& lhs, const CComplex& rhs);
	friend CComplex operator -(const CComplex& lhs, const CComplex& rhs);
	friend CComplex operator *(const CComplex& lhs, const CComplex& rhs);
	friend bool operator == (const CComplex& lhs, const CComplex& rhs);

	inline friend double modulus_square(const CComplex& c)
	{
		return c.m_real * c.m_real + c.m_imag * c.m_imag;
	}

	inline friend CComplex complex_power(const CComplex& c, unsigned int n)
	{
		CComplex result(1);

		for (unsigned int i = 0; i < n; ++i)
			result = result * c;

		return result;
	}


	void setReal(long double real)
	{
		this->m_real = real;
	}

	void setImag(long double imag)
	{
		this->m_imag = imag;
	}


private:
	long double m_real;
	long double m_imag;
};

//��ɫ����// = 137.0  = 30.0 
void CFractal::InitPallette(double h1 , double h2 )   

{
	for (int i = 0; i < MAXCOLOR / 2; ++i)
	{
		m_crPallette[i] = HSL2RGB(h1, 1.0, i * 2.0 / double(MAXCOLOR));
		m_crPallette[MAXCOLOR - 1 - i] = HSL2RGB(h2, 1.0, i * 2.0 / double(MAXCOLOR));
	}
}
COLORREF CFractal::HSL2RGB(double h, double s, double l)
{
	const double C = (1 - fabs(2 * l - 1)) * s; // chroma
	const double H = h / 60;
	const double X = C * (1 - fabs(fmod(H, 2) - 1));
	double rgb1[3] = { 0 };

	if (H > 0 && H < 1)  rgb1[0] = C, rgb1[1] = X, rgb1[2] = 0;
	else if (H >= 1 && H < 2) rgb1[0] = X, rgb1[1] = C, rgb1[2] = 0;
	else if (H >= 2 && H < 3) rgb1[0] = 0, rgb1[1] = C, rgb1[2] = X;
	else if (H >= 3 && H < 4) rgb1[0] = 0, rgb1[1] = X, rgb1[2] = C;
	else if (H >= 4 && H < 5) rgb1[0] = X, rgb1[1] = 0, rgb1[2] = C;
	else if (H >= 5 && H < 6) rgb1[0] = C, rgb1[1] = 0, rgb1[2] = X;
	else                      rgb1[0] = 0, rgb1[1] = 0, rgb1[2] = 0;

	const double m = l - 0.5 * C;

	return RGB((rgb1[0] + m) * 255, (rgb1[1] + m) * 255, (rgb1[2] + m) * 255);
}

//Mandelbrot
void CMandelSet::CalcImagePixel()
{
	if (!m_pxim) return;

	CxImage* pxim = m_pxim;

	int width = pxim->GetWidth();
	int height = pxim->GetHeight();

#ifndef _DEBUG
#pragma omp parallel for
#endif
	for (int i = 0; i < height; ++i)
	{
		CComplex C(0, m_dFromY + (m_dToY - m_dFromY) * i / static_cast<long double>(height));

		for (int j = 0; j < width; ++j)
		{
			C.setReal(m_dFromX + (m_dToX - m_dFromX) * j / static_cast<long double>(width));

			CComplex Z;
			int k = 0;
			for (k = 0; k < m_nIteration; ++k)
			{
				if (modulus_square(Z) > 4.0) break;
				// f(z) = z^n + C;
				Z = complex_power(Z, m_nExponent) + C;
			}

			m_matImageInfo[j][i] = k;
		}
	}
}


//Julia

void CMandelSet::CalcImagePixel()
{
	if (!m_pxim) return;

	CxImage* pxim = m_pxim;

	int width = pxim->GetWidth();
	int height = pxim->GetHeight();

#ifndef _DEBUG
#pragma omp parallel for
#endif
	for (int i = 0; i < height; ++i)
	{
		CComplex C(0, m_dFromY + (m_dToY - m_dFromY) * i / static_cast<long double>(height));

		for (int j = 0; j < width; ++j)
		{
			C.setReal(m_dFromX + (m_dToX - m_dFromX) * j / static_cast<long double>(width));

			CComplex Z;
			int k = 0;
			for (k = 0; k < m_nIteration; ++k)
			{
				if (modulus_square(Z) > 4.0) break;
				// f(z) = z^n + C;
				Z = complex_power(Z, m_nExponent) + C;
			}

			m_matImageInfo[j][i] = k;
		}
	}
}

//https://www.zhihu.com/question/20187195 �ο�
//https://www.cnblogs.com/easymind223/archive/2012/07/05/2578231.html ����
*/

//--------------------------------���ηֽ���--------------------------------------------------


//������ ���������ߺ��������㷨
//ʮ�ڶ��ǲ�ͬ��ϸ���㷨����......
//�ڰ�����ʵ��ͼ�εĻ���Ҳ����ˣ��㷨����
//ߣ���������ˣ�ʣ�µ�������α���붼������
//��������������api����ԱҲ����Ҫ�������㷨��ѧ����ѧ�Ƶ���ģ�����ü����ʵ���Լ�˼·�͹���
//��ʱ��ѧϰ��Windows���ı�̡�����OpenGL��̾��⡷��Three.js����ָ�ϡ��ȵ�WebGL,OpenGL�����������ˡ�
//nehe openGl�Ľ̳̺ܰ���




//--------------------------------------------------------------------------------------------------
//�����ķָ��ߣ�ȡ��ע�;��ܻ�ͼ������X������������Y��������
//--------------------------------------------------------------------------------------------------


//��ϸ���� ���ڹ��̺���
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
		hDC = BeginPaint(hWnd, &ps);
		for (int i = 10; i < 50; i += 4)
		{
			SetPixel(hDC, i, 10, RGB(0, 0, 0)); //�������ص�
		}
//--------------------------------------------------------------------------------------------------
//�����ķָ���,�ⲿ��ȡ���뿴�Ĳ����㷨�Ķ�Ӧ����ע�ͣ����ܿ����㷨ͼ��ѧ��ͼЧ��
//--------------------------------------------------------------------------------------------------

		//DDALine�㷨
		//DDALine(hDC,RGB(0,255,0),0.0,0.0,90.0,50.0);

		//MidpointLine�㷨
		//MidpointLine(hDC, RGB(0, 255, 0), 0, 0, 90, 50);
		
		//BresenhamLine�㷨
		//�Ȼ�����һ����λ�þ���		//DDALine(hDC, RGB(0,0,0), 0, 0, 200, 200);//��׼�Խ���
		DrawLine(hDC, 0, 0, 0, 200, PS_DASHDOT, 1, RGB(100, 250, 100));//�ٷ��Դ����ܻ���DrawLine
		DrawLine(hDC, 0, 0, 200, 0, PS_SOLID, 2, RGB(0, 0, 0));
		DrawLine(hDC, 200,200, 0, 200, PS_DASH, 1, RGB(100, 0, 200));
		DrawLine(hDC, 200, 200, 200,0, PS_DASH, 1, RGB(100, 0, 200));
		//�Ա���ȷ��ֱ����Ϊ�ο���BresenhamLine�㷨ʹ�÷�Χ
		DrawLine(hDC, 100 - 50, 100 - 50, 100 + 50, 100 + 50, PS_DASHDOT, 1, RGB(100, 250, 100));
		DrawLine(hDC, 100 - 50, 100 + 50, 100 + 50, 100 - 50, PS_DASHDOT, 1, RGB(100, 250, 100));
		//Ȼ����ǻ����ж����÷�Χ�����ĸ�BresenhamLine
		BresenhamLine1(hDC, RGB(255, 0, 0), 100, 100, 100+50, 100+40);//�˵ȷݵ�һ������
		BresenhamLine1(hDC, RGB(255, 0, 0), 100-50, 100-40, 100, 100);//BresenhamLine5�˵ȷݵ�������޺Ͱ˵ȷݵ�һ��������ͬ���룬����ֻд�ұ�һ��Ĵ��룬��ΪҲ���ù���Y��ԳƵ���һ��
		//����������İ˵ȷ����ޱ��������BresenhamLine1(hDC, RGB(255, 0, 0), 100, 100, 100 + 50, 100 + 60);
		//BresenhamLine8(hDC, RGB(255, 0, 255), 100, 100, 100+50, 100-40);//�˵ȷݵڰ˸����޿���
		//BresenhamLine8(hDC, RGB(255, 0, 255), 100-50, 100+40, 100, 100);//BresenhamLine4�˵ȷݵ��ĸ����޺Ͱ˵ȷݵڰ˸�������ͬ����


		// �е㻭Բ�㷨
		//MidpointCircle2(hDC,200,RGB(0,0,255));

		//BresenhamCircle�㷨
		//BresenhamCircle(hDC, 150, RGB(0, 0, 255));

		//���ɹ����������
		//���Ʋ�ͬ���ģʽ�ľ��Σ�windows api�Լ��Һ����������Լ����������С�
		//DrawRect(hDC, 220, 20, 60, 40, HS_BDIAGONAL, RGB(255, 0, 0));
		//DrawRect(hDC, 220, 80, 60, 40, HS_CROSS, RGB(0, 255, 0));
		//DrawRect(hDC, 290, 20, 60, 40, HS_DIAGCROSS, RGB(0, 0, 255));
		//DrawRect(hDC, 290, 80, 60, 40, HS_VERTICAL, RGB(0, 0, 0));

/*
		//����Լ�����߽���RGB(0,0,0)��ɫ�����RGB(0,255,0)��ɫ��oldvalue������ɫRGB(255,255,255),newvalue��RGB(0,0,255)��ɫ���,COLORREF color�����۾�����Ϲ��ʱ����ѡ���ɫRGB(255,0,0)
		// ����ͨ�ڶ������������㷨
		//����DrawRect(hDC, 10, 10, 20, 20, HS_BDIAGONAL, RGB(0, 0, 0));//x1,y1,x2,y2����������㷨ǰ������л���������״��Ȼ��ѡһ���ڵ�(150,150)��Ϊ����
		//�᲻���Ǿ����Զ����֮����Ⱦ���������ڸģ�����һ�в�����
		double i = 30.0;//20���е�ԭ����ʲô��20/2=10��������������������
		double time = 0;
		double counts = 0;
		LARGE_INTEGER nFreq;
		LARGE_INTEGER nBeginTime;
		LARGE_INTEGER nEndTime;
		QueryPerformanceFrequency(&nFreq);
		QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ  
		DDALine(hDC, RGB(0, 0, 0), 0.0, 0.0, 0.0, i);
		DDALine(hDC, RGB(0, 0, 0), i, 0.0, 0.0, 0.0);
		DDALine(hDC, RGB(0, 0, 0), i, i, i, 0.0);
		DDALine(hDC, RGB(0, 0, 0), i, i, 0.0, i);
		Floodfill(hDC, floor(i/2), floor(i/2), RGB(255, 255,255), RGB(0, 0, 255));
		QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ  
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs 
		CString txt_Res;
		txt_Res.Format(_T("%lf"),time*1000);
		//CString txt;
		//txt.Format(_T("%d"), globalCount);
		//CString str;
		//str.Format(_T("����ʱ���ǣ�%lu ms"),dwEnd - dwStart);//DWORD��ʲô��ʽ��https://stackoverflow.com/questions/3209909/how-to-printf-unsigned-long-in-c
		//sprintf_s(str, "ʱ����%DWORD",dwEnd-dwStart);
		//MessageBox(NULL, txt,TEXT("title"),MB_OK);
		MessageBox(NULL, "running time is:"+ txt_Res +"ms", TEXT("����"), MB_OK);//MessageBox�÷�https://blog.csdn.net/weixin_37605770/article/details/79049986
		/*2�ְ취��
		1��
		CString s;
		s.Format(_T("%d"), posX);
		MessageBox(..., s,...);
		2��
		LPTSTR lpsz = new TCHAR[100];
		_itot(posX, lpsz, 10);
		MessageBox(..., lpsz,...);		//���100���ۿɼ���ջ������ӳ�
		delete lpsz;
		*/
		

		// ����ͨ�߽綨�����������㷨
		//DDALine(hDC, RGB(0, 0, 0), 0.0, 0.0, 0.0, 3.0);
		//DDALine(hDC, RGB(0, 0, 0), 3.0,0.0, 0.0, 0.0);
		//DDALine(hDC, RGB(0, 0, 0), 3.0, 3.0, 3.0, 0.0);
		//DDALine(hDC, RGB(0, 0, 0), 3.0, 3.0, 0.0, 3.0);
		//����DrawRect(hDC, 10, 10, 20, 20, HS_BDIAGONAL, RGB(0, 0, 0));//x1,y1,x2,y2����������㷨ǰ������У�Ȼ��ѡһ���ڵ�(150,150)��Ϊ����
		//�᲻���Ǿ����Զ����֮����Ⱦ���������ڸģ���һ�в����ã�
		//Boundaryfill(hDC, 2, 2, RGB(0, 0, 0), RGB(0, 0, 255));
		//DrawRect(hDC, 100, 100, 200, 200...Boundaryfill(hDC, 150, 150, RGB(0, 0, 0), RGB(0, 0, 255));
		//�ǲ��ǵݹ����̫�����ʧ�ܣ��������������������ݣ�0x00115379 ����δ��������쳣(�� winddowsApi_GDI.exe ��): 0xC000041D: An unhandled exception was encountered during a user callback�� ������ 
		//���ǣ��������ǵݹ���õ�ʱ��ͻ��������ʦ�������Ķ����������ڴ���󣿵ݹ���ù��ࣿջ�����
		//��1���ֶ�����ϵͳ��ջ�ռ��С�����ַ�����ȱ���ǣ��Լ�������������֮�󣬵����˵����ϻ��ǻ���ִ��쳣��
		//2�����ٺ����еݹ�Ĵ�����
		//3�����������Ƿ��������ѭ����������������������������������������������������������
		//

		//



		//	����	Fractal ѩ������
		//system("color 2f");//��������������
		//Fractal(hDC,80, 40, 240, 360);
		//Fractal(hDC,240, 360, 420, 100);
		//Fractal(hDC,420, 100, 80, 40);

//	���� F��z��=Z^2+C ��z = 0�����Ը�ƽ����ÿһ��c���е������㣬��ÿһ�� |f(z)| С��2���������ڼ����� 	
//mandelbrot-set https://solarianprogrammer.com/2013/02/28/mandelbrot-set-cpp-11/


//	����	Julia Set���Ƕ����趨��һ������c(��ģ�ٶ�С��2)���Ը�ƽ���ڵ�ÿһ��z���е������㣬������ģС��2�����ڼ���
//Julia-set




/*
 //���ע�Ϳ��������н�������������ܱȽ���ȫ
		/*
		//��ϸ���ú���Լ��Windows�ٷ��̳��Լ��Ҹ���api����Լ��
		//���Ʋ�ͬģʽ��ֱ��
		DrawLine(hDC, 120, 30, 200, 30, PS_SOLID, 2, RGB(0, 0, 0));
		DrawLine(hDC, 120, 50, 200, 50, PS_DASH, 1, RGB(100, 0, 200));
		DrawLine(hDC, 120, 70, 200, 70, PS_DASHDOT, 1, RGB(100, 250, 100));
		//���ƻ��ߡ��Ҹ��ߡ���ͼ
		Arc(hDC, 10, 30, 40, 50, 40, 30, 10, 40);
		Chord(hDC, 10, 60, 40, 80, 40, 60, 10, 70);
		Pie(hDC, 10, 90, 40, 110, 40, 90, 10, 100);

		POINT pt[4] = { {90,130},{60,40},{140,150},{160,80} };
		//������Բ������
		Ellipse(hDC, pt[0].x, pt[0].y, pt[1].x, pt[1].y);
		Rectangle(hDC, pt[2].x, pt[2].y, pt[3].x, pt[3].y);

		//���Ʊ���������
		PolyBezier(hDC, pt, 4);
		//������������ߵ��ĸ�ê��
		DrawCircle(hDC, pt[0].x, pt[0].y, 8, RGB(0, 255, 0));
		DrawCircle(hDC, pt[1].x, pt[1].y, 8, RGB(0, 0, 255));
		DrawCircle(hDC, pt[2].x, pt[2].y, 8, RGB(0, 0, 0));
		DrawCircle(hDC, pt[3].x, pt[3].y, 8, RGB(255, 0, 0));
		//����Բ
		DrawCircle(hDC, 100, 180, 60, RGB(0, 250, 250));
		//���Ʋ�ͬ���ģʽ�ľ���
		DrawRect(hDC, 220, 20, 60, 40, HS_BDIAGONAL, RGB(255, 0, 0));
		DrawRect(hDC, 220, 80, 60, 40, HS_CROSS, RGB(0, 255, 0));
		DrawRect(hDC, 290, 20, 60, 40, HS_DIAGCROSS, RGB(0, 0, 255));
		DrawRect(hDC, 290, 80, 60, 40, HS_VERTICAL, RGB(0, 0, 0));
		//����λͼ
		DrawBmpRect(hDC, 180, 140, 180, 100, TEXT("chenggong.bmp"));
		//�����ı�
		TextOut(hDC, 20, 220, TEXT("GDI��ͼ������Գ���"), 11);
		*/
	}
	EndPaint(hWnd, &ps);
	return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

//��������˵ȷ�ͼ���е����С�༭��Ԥ�������ɿ������仮����ʽ

//                                                                                                                                                                                                                                                                                                                                                **,=                                                                                                                                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                                                                                                                ,*`,                                                                                                                                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                                                                                                                *@@@                                                                                                                                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                                                                                                                *@@@                                                                                                                                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                                                                                                                *@@@                                                                                                                                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                                                                                                                *@@@                                                                                                                                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                                                                                                                *@@@                                                                                                                                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                                                                                                                *@@@                                                                                                                                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                                                                                                                *@@@                                                                                                                                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                                                                                                                *@@@                                                                                                                                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                                                                                                                *@@@** *                                                                                                                                                                                                                                                                                                                                               
//                                                                                                                                                                                                                                                                                                                                                *=@@^***                                                                                                                                                                                                                                                                                                                                               
//                                                                                                                                                                                                                                                                                                                                                 =@@^***                                                                                                                                                                                                                                                                                                                                               
//                                                                                                                                                                                                                                                                                                                                                *=@@^**                                                                                                                                                                                                                                                                                                                                                
//                                                                                                                                                                                                                                                                                                                                                *=@@^ **                                                                                                                                                                                                                                                                                                                                               
//                                                                                                                                                                                                                                                                                                                                                *=@@^* *                                                                                                                                                                                                                                                                                                                                               
//                                                                                                                                                                                                                                                                                                                                                 =@@^***                                                                                                                                                                                                                                                                                                                                               
//                                                                                                                                                                                                                                                                                                                                                *=@@^* *                                                                                                                                                                                                                                                                                                                                               
//                                                                                                                                                                                                                                                                                                                                                *=@@^***                                                                                                                                                                                                                                                                                                                                               
//                                                                                                                                                                                                                                                                                                                                                *,@@^***                                                                                                                                                                                                                                                                                                                                               
//                                                                                                                                                                                                                                                                                                                                                **@@@***                                                                                                                                                                                                                                                                                                                                               
//                                                                                                                                                                                                                                                                                                                                                **@@@***                                                                                                                                                                                                                                                                                                                                               
//                                                                                                                                                                                                                                                                                                                                                **@@@***                                                                                                                                                                                                                                                                                                                                               
//                                                                                                                                                                                                                                                                                                                                                **@@@***                                                                                                                                                                                                                                                                                                                                               
//                                                                                                                                                                                                                                                                                                                                                 *@@@***                                                                                                                                                                                                                                                                                                                                               
//                                                                                                                                                                                                                                                                                                                                                **@@@***                                                                                                                                                                                                                                                                                                                                               
//                                                                                                                                                                                                                                                                                                                                                 *@@@***                                                                                                                                                                                                                                                                                                                                               
//                                                                                                                                                                                                                                                                                                                                                **@@@*                                                                                                                                                                                                                                                                                                                                                 
//                                                                                                                                                                                                                                                                                                                                                **=@@***                                                                                                                                                                                                                                                                                                                                               
//                                                                                                                                                                                                                                                                                                                                                **=@@^**                                                                                                                                                                                                                                                                                                                                               
//                                                                                                                                                                                                                                                        *,,*************************,`/*                                                        **=@@^**                                                                                                                                                                                                                                                                                                                                               
//                                                                                                                                                                                                                                                        *,@@@@@@@@@@@@@@@@@@@@@@@@@@@@\`                                                        **=@@^**                                                                                                                                                                                                                                                                                                                                               
//                                                                                                                                                                                                                                                    ,*`\@@@/                        /@@@\`=*                                                    **=@@^*                                                         ***]@@@@@@@@@@@@@@@@@@@@@@@@@@@\,**`                                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                    *,@@@@[`                        *,=@@@\=                                                    **=@@^**                                                        ,,@@@@[/[[[[[[[[[[[[[[[[[[[[\\@@@\/\                                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                /*`]@@@/                                ,@@@\/``****                                            **=@@^**                                                    ,**\@@@/                        **]\@@@\,*\,                                                                                                                                                                                                                                               
//                                                                                                                                                                                                                                                /+@@@@*`                                ,��/@@@@`****                                            **=@@^**                                                    `]@@@@,]                        *,**`,@@@\,*                                                                                                                                                                                                                                               
//                                                                                                                                                                                                                                            \`,/@@@@                                        ,@@@@`*,****                                        **=@@^*                                                 ,*]/@@@/                                **`\@@@@```*                                                                                                                    ****                                                                                                                   
//                                                                                                                                                                                                                                            `/@@@/,*                                        **-/@@@@`****                                        **,@@^**                                                `/@@@/*`                                *****,@@@@/,                                                                                                                    ,***                                                                                                                   
//                                                                                                        **``@`,**,,`                                                                                                                    ``,/@@@/                                                ,@@@@`,,****                                      *@@@**                                            ``-/@@@/                                        ** \@@@@/,**                                                                                                            \`*@@],*                                                                                                                   
//                                                                                                        *`,\@@@/``**                                                                                                                    `/@@@`,                                                 ,**\@@@```**                                    ***@@@**                                            -/@@@/,*                                        ****-=@@@@\=                                                                                                            *@@@@***                                                                                                                   
//                                                                                                            *\@@@```*,`*                                                                                                            *`*-@@@`                                                        *@@@@],\                                     **@@@**                                        ``,/@@@^                                                    \@@@`,*,                                                                                                    \\*/@@@\                                                                                                                       
//                                                                                                            \**/@@@\`]**                                                                                                            ,=@@@`/*                                                        *,*@@@@`                                    ***@@@**                                        `/@@@`**                                                    ``\@@@`/                                                                                                    */@@@``*                                                                                                                       
//                                                                                                                */@@@@`*****                                                                                                        *@@@                                                                =@@^                                    * *@@@**                                    **`/@@@^                                                            \@@@`***                                                                                            ,*`@@@@^                                                                                                                           
//                                                                                                                `*`/@@@\****                                                                                                        =@@^                                                                *@@@                                    * *@@@**                                    **,@@/`*                                                            `,@@@***                                                                                            ,,@@@``*                                                                                                                           
//                                                                                                                    `/@@@\,*`*`*                                                                                                ****@@@*                                                                *=@@^***                                ***@@@**                                    **/@@^**                                                            **@@@`*`                                                                                        **`]@@@/                                                                                                                               
//                                                                                                                    ,*`[\@@@/`\*                                                                                                ***=@@/*                                                                *,@@@***                                ***@@@**                                    *=@@/`**                                                            **=@@\*^                                                                                        *,@@@/*\                                                                                                                               
//                                                                                                                        ,/\@@@`****/                                                                                            ***@@@**                                                                ,*=@@/**                                * `=@@**                                    */@@/ **                                                            **,@@@`*                                                                                    *``]@@@/                                                                                                                                   
//                                                                                                                        `***\@@@`,**                                                                                            *,=@@/**                                                                =*,@@@**                                ***=@@^*                                    ,@@@ ***                                                            *,*O@@\*                                                                                    *`/@@/`\                                                                                                                                   
//                                                                                                                            *,\@@@`**,,`                                                                                        **@@@^*`                                                                ***\@@/,                                * *=@@^*                                ****/@@^                                                                    @@@`                                                                                **, /@@@                                                                                                                                       
//                                                                                                                            ,/``\@@@/*\*                                                                                        *=@@/***                                                                ***,@@@*                                ** =@@^*                                *^,,@@@`                                                                    =@@\                                                                                ,*/@@@``                                                                                                                                       
//                                                                                                                                 `=@@@\,,`\*                                                                                    *@@@/ **                        ,*`\*,,`,*,,`***                            @@@`                                ***=@@^*                                ***/@@^*                            *`**`*******                            ,@@@`` *                                                                        */,*/@@@/***                                                                                                                                       
//                                                                                                                                ***,,@@@\*,*                                                                                    ,@@@****                        `]/@@@@@@@@@@\*`                            ,@@@                                ***=@@^*                                **\@@@`*                            *``[***,****                            *=@@\***                                                                        ,*\@@@/*****                                                                                                                                       
//                                                                                                                                    *,/@@@\``,*^                                                                            *`**/@@^                        ****=@@@/****^\\@@@^                            ,@@@``**                            = *=@@^*                                *`=@@^*`                        ****,/@@@@@@@@]*`**,                        *,@@@`**                                                                    ,*`*,@@@/,*`                                                                                                                                           
//                                                                                                                                    ,,,/[@@@\,`*                                                                            =**,@@/*                        **,=@@/, ***=*,*\@@@                            *,@@\***                            ***=@@^*                                **@@@***                        **=@@@[*,`,`[@@@\*`*                        *,=@@\**                                                                    ,*,@@@\,***,                                                                                                                                           
//                                                                                                                                        ,*/@@@@``**`                                                                        ,*`/@@^*                        **]\[\[*        ,=@@^*,*                        **@@@`**                            ***=@@^*                                */@@/***                        ,=@@^*`*    **@@@^**                        ***@@@`*                                                                *``,=@@@/***                                                                                                                                               
//                                                                                                                                        **`,,\@@@`/*                                                                        **,@@@**                        *,**`,**        ,@@@****                        **=@@\*^                            * * @@\*                                *@@@****                        ,@@@`*,*    *,*@@@*`                        ***/@@^*                                                                ,`]@@@/`***,                                                                                                                                               
//                                                                                                                                            ***@@@@`,,*/                                                                    **/@@^**                                *`**\,`,@@@`                            *`*@@@/*                                @@@*                            ****=@@^                                        *,]@@@,,                            @@@`                                                            *`,*,/@@@***                                                                                                                                                   
//                                                                                                                                            ****,@@@@`/*                                                                    *,@@@***                                ,\]@@@@@@\*`                            ***=@@@*                                @@@*                            ****@@@*                                        **@@@`**                            =@@^                                                            *\\/@@@,****                                                                                                                                                   
//                                                                                                                                                *`\\@@@\****                                                                **@@@`**                                ,@@@@@@@@\`***,*                        ***/@@^*                                @@@*                            ,**/@@\*                                    ,```=@@@/***                            ,@@@**                                                      *****/@@@\`*                                                                                                                                                       
//                                                                                                                                                = *`*,@@@@,`                                                                ,*=@@\**                                *`*`****/@@@`* `                        *`\@@@`*                                @@@*                            *`*=@@^*                                    /*]@@@/* ***                            *@@@                                                        */,/@@@``,*`                                                                                                                                                       
//                                                                                                                                                    , ^\@@@\,*\*                                                            ***@@@``                        ***,**`*        **@@@***                        **/@@^*`                                @@@*                                @@@*                                *\*`,@@@/*,*                            `***=@@^                                                    ***`*/@@@^*`                                                                                                                                                           
//                                                                                                                                                    ****`/@@@\*,                                                            *=*/@@\*                        **,`^`*,        **@@@***                        **@@@***                                @@@                                 =@@^                                ,/@@@@[`,`*,                            ****@@@*                                                    ,*`]@@@`/***                                                                                                                                                           
//                                                                                                                                                          **\@@\`,**                                                            @@@`                        **,@@@*******`***=@@@*`*                        */@@/***                                @@@*                                *@@@,*`*                        *`\*/@@@//=*                                *=*=@@^`                                                ,`*^,,@@@\,`                                                                                                                                                               
//                                                                                                                                                         *  **\@@@/,                                                            =@@^                        ***=@@@^[******,/@@@\*`*                        *@@@***,                                @@@*                                *=@@^***                        *`]@@@\**`*^                                **`@@@**                                                `[=,@@@/*/,`                                                                                                                                                               
//                                                                                                                                                                \@@@]***                                                        *@@@*,**                        *\@@@@@@@@@@@@/*                        ****=@@^                                    =@@^                                * @@@*`*                        *]@@@,**************                        **=@@^ *                                            *]*/,/@@@//*                                                                                                                                                                   
//                                                                                                                                                                ,`\@@@``                                                        *=@@^***                        *,*`,[[[[/\`**/`                        ****@@@*                                    =@@^                                **=@@^,*                        /@@@@@@@@@@@@@@@@@]*                        **@@@**                                             **,,/@@/,,*`                                                                                                                                                                   
//                                                                                                                                                                    @@@@`,`/                                                    *,@@@*`*                                                                ***\@@/*                                    =@@^                                ***@@@**                        ,/[\[[[[[[[[[[[[[\[*                        ,=@@^***                                        ,**`*//@@/*^                                                                                                                                                                       
//                                                                                                                                                                    ``=@@@@,                                                    **=@@^`*                                                                ***@@@**                                    =@@^                                ***=@@^*                        ,**`***************`                        *@@@* **                                        * **/@@@`,**                                                                                                                                                                       
//                                                                                                                                                                        ,@@@\*/,                                                ,**@@@**                                                                *,=@@^**                                    =@@^                                    @@@*                                                                    =@@^                                        `****,/@@@^,                                                                                                                                                                           
//                                                                                                                                                                        , \@@@\*                                                ***/@@^`                                                                **@@@**,                                    =@@^                                    =@@^                                                                *  *@@@*                                        *,,`/@@@`\**                                                                                                                                                                           
//                                                                                                                                                                            ,@@@@`******                                            @@@*                                                                *=@@^***                                    =@@^                                    *@@@* **                                                             **=@@^*                                    ,`***\,@@@[/                                                                                                                                                                               
//                                                                                                                                                                            ,,*\@@@`****                                            =@@^                                                                *@@@,***                                    =@@^                                     =@@^***                                                            ***@@@`*                                    ***`=@@@\\**                                                                                                                                                                               
//                                                                                                                                                                                *\@@@\``,,**                                        *@@@*\/*                                                        ****=@@^                                        =@@^                                    **@@@***                                                            **=@@^**                                * **,`,@@@@*                                                                                                                                                                                   
//                                                                                                                                                                                ***@@@@```**                                        *=@@@/,*                                                        **/]@@@`                                        *@@@                                    * \@@^**                                                            * @@@`**                                ** *=@@@/\``                                                                                                                                                                                   
//                                                                                                                                                                                    *\@@@`***,**                                    *`=@@@\`\,,`                                                ,*`*`,@@@@``                                        *@@@                                    *`*@@@,*****                                                    ***`,\@@^***                                *]*/@@/`                                                                                                                                                                                       
//                                                                                                                                                                                    ]`*/@@@\`]**                                    *,*,[@@@\\**                                                ,,*=@@@/``/,                                        *@@@                                    ***\@@@@`***                                                    ,**]@@@/`***                                */@@@[**                                                                                                                                                                                       
//                                                                                                                                                                                        `,@@@@``***,                                    **,@@@@``***                                        `,*`//@@@/**                                            *@@@                                        */@@@\,`/,/*                                            /``*]=@@@/\*                                ``]/@@@`                                                                                                                                                                                           
//                                                                                                                                                                                        `*`/@@@\*,*`                                    **``,@@@@``*                                        ,``/@@@//,*`                                            *@@@                                        *``/@@@@/``*                                            *,*\@@@/,`/,                                */@@@`**                                                                                                                                                                                           
//                                                                                                                                                                                            ,/@@@\,`/*,*                                    */,@@@@``,`*                                `*,*,/@@@//*                                                *@@@                                            */@@@@``*``*                                    ****//@@@/`*                                ***@@@@`                                                                                                                                                                                               
//                                                                                                                                                                                            ,,`[@@@\/`\,                                    **,,/@@@@//*                                ``*/@@@//`\*                                                *@@@                                            =,`[@@@@`^[`                                    *``/@@@//,``                                *]@@@`**                                                                                                                                                                                               
//                                                                                                                                                                                                ,/\@@@`*`**/                                    *//\@@@``,*`                        ,**`,/@@@\**                                                    *@@@* **                                            ,/@@@@``*`],                            `/,*,/@@@//*                                ``*,@@@`                                                                /,`/                        **]*                                                                                                   
//                                                                                                                                                                                                `***\@@@`\**                                    **\,`\@@@/`\                        `,`@@@@`,,`\                                                    *=@@***                                             ,*`,@@@@`\,,                            ,`*/@@@[,/,`                                ,/@@@/*,                                                                ,*`,************************/,``                                                                                                   
//                                                                                                    ,**`************************,,,\****                                                            ,,\@@@`\,*,*                                    **,@@@@`************************,/@@@^,*                                                        *=@@^ **                                                \/\@@@`*,***                    ,*,,*/@@@\,`                                ,,`,@@@/                                                                ***`*,@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\,**`                                                                                               
//                                                                                                    `//@@@@@@@@@@@@@@@@@@@@@@@@@@@@^``**                                                            ,,*\/@@@/*\*                                    ****,\@@@@@@@@@@@@@@@@@@@@@@@@@@@@@`/***                                                        *=@@^***                                                **`*\@@@]**`                    *,`@@@@[/`,*                                **@@@/*,                                                                ,**]@@@/``*^********************`,@@@\*\                                                                                               
//                                                                                                /`*`/@@@/]**                    ,\@@@`,*,*``                                                            *`/@@@\,,`\,                                                                                                                                *=@@^***                                                    */\@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@^,*                                ,***/@@@                                                                /``*]=@@@/`*                        **^\@@@\*,**                                                                                           
//                                                                                                *`/@@@`*,**,                    ,*`\@@@\\`=*                                                            ***\[@@@\*,*                                                                                                                                *=@@^***                                                    `\,`\[\[[[[[[[[[[[[[[[[[[[[[[[[^/***                                ,,/@@@``                                                                ,,,\@@@/,`/,                        *,***=@@@@/*                                                                                           
//                                                                                            **``/@@@/]**                            ,\@@@]****,*                                                            ]*/@@@\``,,`                                                                                                                             =@@^***                                                                                                                    *`**/@@@/ **                                                            ***``/@@@//`                                ***\@@@@/*`*                                                                                       
//                                                                                            *\@@@@^`**`*                            *,*\@@@\`],*                                                            ,*]/,@@@\\\,                                                                                                                            *=@@^* *                                                                                                                    /,@@@@^,****                                                            *``/@@@//,`*                                ****=,@@@@/*                                                                                       
//                                                                                        ***,@@@@/***                                    \\@@@\***,*`                                                            /*/@@@@/```*                                                                                                                        *=@@^***                                                                                                                ,*`,,@@@/,**                                                            *]*`*/@@@//*                                        ** \@@@@/,**                                                                                   
//                                                                                        ^\@@@@`^****                                    ,/*\@@@\``**                                                            =`\,,\@@@`**                                                                                                                        *=@@^* *                                                                                                                ,,\@@@\`**`*                                                            *``/@@@[//,\                                        ****/,@@@@/,                                                                                   
//                                                                                    ***\@@@@/ **                                            *@@@@\\*****                                                            **`@@@@`,*``                                                                                                                    **@@^***                                                                                                            *`,,,@@@/**,                                                            ,*`,*/@@@\,*                                                    \@@@]**`                                                                               
//                                                                                    ^=@@@@^`****                                            ,*,@@@@\,* *                                                            *****\@@@`[*                                                                                                                    **@@@***                                                                                                            ,`,@@@@`,**,                                                            `\\@@@@[/`**                                                    =`@@@@\`                                                                               
//                                                                                *`/,@@@/                                                        ,,@@@\*`                                                                ***\@@@\*]`*                                                                                                                **@@@**                                                                                                         *`,,,@@@@***                                                                *,@@@^**                                                            @@@^****                                                                           
//                                                                                *`@@@/*,                                                        *`*=@@@\                                                                `*,`*[@@@\,`                                                                                                                **@@@***                                                                                                        **\/@@@,****                                                                *=@@^`**                                                            `@@@****                                                                           
//                                                                                *=@@^***                                                            *@@@****                                                                = ^\@@@\,*,`                                                                                                            **@@@***                                                                                                    ***/*/@@/\``                                                                    *@@@                                                                *=@@^***                                                                           
//                                                                                *@@@` **                                                            *\@@^***                                                                *****,@@@@`\                                                                                                            **@@@***                                                                                                    ,*,/@@@\`/`^                                                                    =@@^                                                                **@@@*`*                                                                           
//                                                                                =@@/                                                                **@@@***                                                                    ***\@@@\``**                                                                                                         *@@@***                                                                                                ,*`*,/@@@`**                                                                    ****@@@*                                                                **=@@/**                                                                           
//                                                                                @@@`                                                                **\@@^`*                                                                    * **=*@@@@/,                                                                                                        **@@@* *                                                                                                ,**O@@@^/`**                                                                    ***=@@^^                                                                ,  @@@**                                                                           
//                                                                            ***=@@@*                                                                **=@@\**                                                                            \@@@][`*                                                                                                    **@@@***                                                                                            ,]*`,=@@@\,`                                                                        ***@@@**                                                                ***=@@^*                                                                           
//                                                                            ***@@@`*                                                                ***\@@^*                                                                            ``\@@@`,                                                                                                    * =@@^ *                                                                                            `[=,@@@/,,`*                                                                        **=@@^**                                                                ** *@@@*                                                                           
//                                                                            ,*,@@@**                                                                ** \@@\*                                                                                \@@@`\,*                                                                                                **=@@^**                                                                                        *\**,,@@@@,\                                                                            **@@@*,*                            ***,****                                =@@^                                                                           
//                                                                            **@@@^**                                                                ****@@@`                                                                                ,*,@@@\,                                                                                                **=@@^**                                                                                        */,\@@@/,,`/                                                                            *=@@^ **                            ^*`]]/\*                                ,@@@                                                                           
//                                                                            *,@@@`**                                *`******                            =@@\*,,*                                                                                ,@@@\,`*                                                                                            * =@@^**                                                                                    *****,/@@@`*                                                                                *@@@                            *,**,@@@@@^*                                *=@@^***                                                                       
//                                                                            */@@\***                                ,,@@@@**                            *\@@`***                                                                                /*\@@@\*                                                                                            **=@@^**                                                                                    ****/@@@`/,*                                                                                =@@^                            `\@@@/[=@@^*                                *,@@@***                                                                       
//                                                                            ,@@@                                **,*=@@@@@**                            *\@@\,**                                                                                    ,@@@@`******                                                                                    **=@@^ *                                                                                \*****/@@@^,                                                                                ****@@@*                            *@/`***=@@^*                                **=@@^**                                                                       
//                                                                            /@@^                                ,,*/@@\@@@**                            *=@@@/**                                                                                    **,\@@@]****                                                                                    **=@@^**                                                                                **,[/@@@`,``                                                                                ***=@@/*                            ,][,***=@@^*                                * ,@@@**                                                                       
//                                                                        **,=@@@`                                ,`/@@**@@@**                            ,*=@@\``                                                                                        *\@@@]/`****                                                                                * =@@^**                                                                            ****`*]@@@\,                                                                                    *,*@@@**                                ***=@@^*                                ***=@@^*                                                                       
//                                                                        ,**/@@^`                                \@@/,`*@@@**                            ***@@@/*                                                                                        */*@@@@```**                                                                                **=@@^**                                                                            ***`,@@@\*,\                                                                                    **=@@/`*                                ***=@@^*                                ***,@@@*                                                                       
//                                                                        ,*,@@@**                            /*,,@@\****@@@**                            **`=@@^*                                                                                            *\@@@``\*,**                                                                             **@@@**                                                                        ****,`,@@@@*                                                                                        **@@@^**                                ***=@@^*                                ****@@@`                                                                       
//                                                                        **/@@^**                            ,*/@@`*/***@@@**                            ****@@@*                                                                                            `,*@@@@]``**                                                                            ***@@@**                                                                        *** =@@@/\[`                                                                                        **,@@@**                                ***=@@^*                                ***=@@/*                                                                       
//                                                                        ,*\@@^,*                        ,*,/*@@@    ***@@@**                            **`*@@@*                                                                                                ,,@@@@`]****                                                                        * *@@@**                                                                        ***@@@/*                                                                                            ***@@@/*                                ***=@@^*                                ***@@@/*                                                                       
//                                                                        ***@@@**                        ***\@@/,    ***@@@**                            ***=@@^*                                                                                                **`,@@@\,,**                                                                        ***@@@**                                                                        ,@@@@`**                                                                                            ***,@@\*                                ***=@@^*                                **,@@/**                                                                       
//                                                                        **`\@@^`                        *,=@@\``    ,,*@@@***``,                        *,,@@@`*                                                                                                    */@@@\*`/,*`                                                                    ***@@@**                                                                    \*]@@@@`                                                                                                    @@@`                                ***=@@^*                                **/@@/**                                                                       
//                                                                        ****@@@*                        *^@@@@@@@@@@@@@@@@@@@@**                        *,=@@^**                                                                                                    ,``,@@@\/*``                                                                    ***@@@**                                                                    ,/@@@\,*                                                                                                    ,@@\                                ***=@@^*                                *,@@/***                                                                       
//                                                                            =@@^****                                ***@@@**                            **@@@**`                                                                                                        *,\@@@/*,***                                                                 **@@@**                                                                ``*@@@@^                                                                                                        `@@@`***                        ]\]]\\]/@@\/]]]]^``*                        */@@/***                                                                       
//                                                                            *@@@****                                ***@@@**                            ,=@@\***                                                                                                        /,*`\@@@`,,,                                                                ***@@@**                                                                ,]@@@[,`                                                                                                        ,=@@\***                        =@@@@@@@@@@@@@@@@***                        ,@@@****                                                                       
//                                                                            *=@@^``*                                ***@@@,*                            *@@@                                                                                                                ,,\@@@]**,``                                                            ***@@@**                                                            *`,,@@@`                                                                                                            **@@@`,*                                                                ****/@@^                                                                           
//                                                                            **@@@***                                *`````,*                            =@@^                                                                                                                ,**\\@@@`*``                                                             **=@@^*                                                            ,]@@@/*,                                                                                                            ,,=@@\,*                                                                ***,@@@`                                                                           
//                                                                            **=@@^**                                                                ***`@@@*                                                                                                                    **/@@@@`,**/                                                        * *=@@^*                                                        **`,@@@/                                                                                                                ,,*@@@``                                                                ***/@@^*                                                                           
//                                                                            **`@@@**                                                                ***=@@^^                                                                                                                    *`\*=@@@\*,*                                                        ***=@@^*                                                        *,@@@/*`                                                                                                                ***=@@\*                                                                **\@@@^*                                                                           
//                                                                            ***=@@^*                                                                ***@@@,                                                                                                                         ,,,@@@\**`*`                                                    * *=@@^*                                                    ,*`*/@@@                                                                                                                        @@@`                                                                *,/@@^*`                                                                           
//                                                                            ** *@@@*                                                                **=@@^**                                                                                                                        **`*,@@@@/*\                                                    ***=@@^*                                                    /,@@@@*^                                                                                                                        =@@^                                                                *`@@@***                                                                           
//                                                                                =@@^                                                                ,*@@@`**                                                                                                                            *//\@@\````*                                                ***=@@^*                                                *`,,/@@@/ **                                                                                                                        *@@@*`**                                                            *=@@^***                                                                           
//                                                                                *@@@                                                                *=@@^***                                                                                                                            `*,,`@@@@^**                                                ***=@@^*                                                ,*@@@@^`****                                                                                                                        *=@@^``*                                                            ,@@@***,                                                                           
//                                                                                *=@@^,**                                                        *`**,@@@                                                                                                                                    ***@@@@],,*`                                            ***\@@^*                                            ,,*//@@@/,**                                                                                                                            *,@@@@*`\*],                                                    `*`\@@@^                                                                               
//                                                                                *,@@@,`*                                                        *^],/@@^                                                                                                                                    ** *,@@@@][*                                            * *,@@^*                                            `,\@@@``**`*                                                                                                                            *,,\@@@\`***                                                    ,,@@@/\*                                                                               
//                                                                                *`=@@@@/`/**                                                *`****]@@@/`                                                                                                                                        ***\@@@]`,*`                                            @@@*                                        *`**,@@@/*=,                                                                                                                                    */@@@\^*`*,*                                            `*`\@@@/                                                                                   
//                                                                                ***\,@@@\\`*                                                *`],/@@@@*`*                                                                                                                                        `*,`*/@@@@`\                                            @@@                                         ,[]@@@@`****                                                                                                                                    *,`/@@@@/`\*                                            `/@@@@ `                                                                                   
//                                                                                    ,,,@@@@``*`*                                        ,*`*`*/@@@/`                                                                                                                                                **^\@@@\*`,`                                        @@@*                                    \\,]\@@@@**`                                                                                                                                            */@@@@``**`*                                    *`,/@@@/                                                                                       
//                                                                                    **],/@@@@/**                                        **],/@@@/*``                                                                                                                                                *,**`[@@@\*`                                        @@@*                                    **//@@@=* **                                                                                                                                            ,,`[@@@@``[`                                    `/@@@/*`                                                                                       
//                                                                                        `//@@@@`**,*                                *****//@@@/*                                                                                                                                                        ** \@@@\,\**                                    @@@*                                *`**,/@@/\*\                                                                                                                                                    ,/@@@@`,***,                            `]`/@@@/                                                                                           
//                                                                                        *,,`/@@@@/``                                * *`/@@@@`*`                                                                                                                                                        *****,\@@@/,                                    @@@                                 ,`//@@@\`,**                                                                                                                                                    ,*^,\@@@`,**                            */@@@/**                                                                                           
//                                                                                            /,/\@@@``,*`                        ****`//@@@^`                                                                                                                                                                    \@@@]**`                                @@@`                            ,,`**/@@@\``                                                                                                                                                            ,,\@@@`,`,*`                    *``/@@@`                                                                                               
//                                                                                            ,*\,`\@@@/`\                        ****@@@@^`,*                                                                                                                                                                    =*@@@@/*                                @@@*                            ,/*\@@@`***`                                                                                                                                                            `*//\@@@][**********************`/@@@`**                                                                                               
//                                                                                                **,@@@@^*`**********************,]/@@@`,                                                                                                                                                                            \@@@`**`                            =@@*                        *,*`*]@@@\,`                                                                                                                                                                    /`\@@@@@@@@@@@@@@@@@@@@@@@@@@@@`                                                                                                   
//                                                                                                ****,@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\,*`                                                                                                                                                                            ,*[@@@\,                            =@@^                        ``/,@@@/`//*                                                                                                                                                                    ***,*************************,`*                                                                                                   
//                                                                                                    `,,\[[[[[[[[[[[[[[[[[[[[[[[[/\[*                                                                                                                                                                                    /@@@@*``                        =@@^                    *`/**\@@@@,*                                                                                                                                                                                                                                                                                                           
//                                                                                                    *,`*****************************                                                                                                                                                                                    **[@@@\*                        =@@^                    */,\@@@/,*`,                                                                                                                                                                                                                                                                                                           
//                                                                                                                                                                                                                                                                                                                            =@@@\`]/****                =@@^                ****,*/@@@**                                                                                                                                                                                                                                                                                                               
//                                                                                                                                                                                                                                                                                                                            *`=@@@\`****                =@@^                ****/@@@`***                                                                                                                                                                                                                                                                                                               
//                                                                                                                                                                                                                                                                                                                                ,@@@@]*`****            =@@^            ,`**=*/@@@^*                                                                                                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                                                                                                ***\@@@`,***            =@@^            **,,/@@@[*`*                                                                                                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                                                                                                    \\@@@``*,*`/        =@@^        ****``@@@@\/                                                                                                                                                                                                                                                                                                                       
//                                                                                                                                                                                                                                                                                                                                    ,=*@@@@```,*        *@@^        **,,\@@@\,*\                                                                                                                                                                                                                                                                                                                       
//                                                                                                                                                                                                                                                                                                                                        \,@@@@*\****    *@@@    ****,`\@@@\*                                                                                                                                                                                                                                                                                                                           
//                                                                                                                                                                                                                                                                                                                                        *`/=@@@\,***    *@@@    *** /@@@@```                                                                                                                                                                                                                                                                                                                           
//                                                                                                                                                                                                                                                                                                                                            *,@@@\**,,``*@@@    **,@@@@,                                                                                                                                            ***** *** ********** ******* *** *******`***************** *********************** ********** ****  *  *****]]]]]]]]]]]]]]]]]/@@@@@@@@@@@@@@@@@*                                   
//                                                                                                                                                                                                                                                                                                                                            ,,`[@@@\/*\`*@@@    ,/@@/`*`                                                                                                                                            **************** ************* ******,]]]]]]]]]]]]]]]]/@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@/@\                                   
//                                                                                                                                                                                                                                                                                                                                                *,\@@@/**@@@**,@@@/`    **  **************** ********** ****`** *************  *****`***`*****************************************,]]]]]]]]]]]]]]]]]/@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@[[[[[[[[[[[[[[[[[[`**                                                                                       
//                                                                                                                                                                                                                                                                                                                                                /]*`\@@@`@@@,@@@@\`,    ************************`***********]]]]]]]]]]]]]]]]]/@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@[[[[[[[[[[[[[[[[[[*************`***************** *********`******************** ******** *                                                                                       
//                                                                                                                                                                                                                        * *********************,***  *** *********  ****`***** *****************`********  ************** *******  **,]]]]]]]]]]]]]]]/@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@/[[[[[[[[[[[[[[[[[                                                                                                                                                                                                                                       
//                                                                                                                                                                                                                        ** ****,****************`*************,]]]]]]]]]]]]]]]]]/@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@[[[[[[[[[[[[[[[[[[**********`******,`***]*******]`******`*******[*******  **************                                                                                                                                                                                                                                       
//                                                                            ***** ************** ******* *** *******]***************** *********************** ******************  *****]]]]]]]]]]]]]]]]]/@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@[[[[[[[[[[[[[[[[[`*                                *`\\@@@@@@`]**`*                                                                                                                                                                                                                                                                                                                                   
//                                                                            ****************************** ******,]]]]]]]]]]]]]]]]/@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@/[[[[[[[[[[[[[[[[[*******,]***********`****** `***************[******************* ***  **                                *=@@@@@@/@@@\*,*                                                                                                                                                                                                                                                                                                                                   
//                                            *,`\]]]]]]]]]]]]/@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@[[[[[[[[[[[[[[[[[[`**                                                                                                                                                                        *\[]@@@/*=@@^`,@@@\*****                                                                                                                                                                                                                                                                                                                               
//                                            **`=@@@@@@@@@@@@@@@@@@@@@@@@@@@@@[[[[[[[[[[[[[[[[[[*************`***********`***** *********`***********  ******* ******** *                                                                                                                                                                        *\@@@/`**=@@\,`^,@@@@/*\                                                                                                                                                                                                                                                                                                                               
//                                                                                                                                                                                                                                                                                                                                            ,**`/@@/    *=@@^`***,/@@@\``*`,                                                                                                                                                                                                                                                                                                                           
//                                                                                                                                                                                                                                                                                                                                            /\/@@/ ^    *=@@^* *=,\,`@@@@/**                                                                                                                                                                                                                                                                                                                           
//                                                                                                                                                                                                                                                                                                                                        ``,*/@@@/***    *=@@^ **    **`@@@@`*\*/                                                                                                                                                                                                                                                                                                                       
//                                                                                                                                                                                                                                                                                                                                        ,*@@@@``**      *=@@^* *    *****\@@@``\                                                                                                                                                                                                                                                                                                                       
//                                                                                                                                                                                                                                                                                                                                    ,,*,/@@@/= ^         =@@^***        ***\@@@]*\**                                                                                                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                                                                                                    ,`,@@@\`****        **@@@**         `*,`*/@@@@``                                                                                                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                                                                                                ,***,@@@/*,*            **@@@***            **]\@@@\****                                                                                                                                                                                                                                                                                                               
//                                                                                                                                                                                                                                                                                                                                ,*]@@@@**]*`            **@@@***            *,***\@@@\,`                                                                                                                                                                                                                                                                                                               
//                                                                                                                *,`*                        ***`                                                                                                                                                                            \`,`\@@@@,**                **@@@***                ***\@@@\*,*,                                                                                                                                                                        ,**,                        `***                                                                                                   
//                                                                                                                *]/]]]]]]]]]]]]]]]]]]]]]]]]]`,**                                                                                                                                                                            *,`/@@/,****                **@@@***                *****,@@@@/,                                                                                                                                                                        ,*`\]]]]]]]]]]]]]]]]]]]]]]]]]]`*                                                                                                   
//                                                                                                            \`,/@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@`*,***                                                                                                                                                                    *,*\,/@@/,*\                    **@@@***                        \@@@/,**                                                                                                                                                                ,*,,,/@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@/,**                                                                                               
//                                                                                                            `/@@@`/\                    =/,\\@@@]**`                                                                                                                                                                    \[*/@@@\`/,*                    **@@@***                        *`\@@@/,                                                                                                                                                                *,`@@@@`*,`,                    ,*\@@@]`                                                                                               
//                                                                                                        *\,/@@@`                            *,\@@@^]*,,`                                                                                                                                                            ,`,*,/@@@`\`                        **@@@* *                            \@@@`,**                                                                                                                                                        **,,\@@@@^,*                            \@@@/,*,                                                                                           
//                                                                                                    *  **/@@@/,`                            `\,`\@@@/```                                                                                                                                                            /],/@@@`*]**                        **@@@***                            / \@@@^*                                                                                                                                                        ,[`/@@@`/***                            ``\@@@\,                                                                                           
//                                                                                                ****,*\/@@@`                                    *,\@@@\\****                                                                                                                                                    ,*`**,@@@^,*                             *=@@^ *                                /@@@\*`*                                                                                                                                                **,,,@@@@\*/                                    \@@@\,**                                                                                       
//                                                                                                *** =@@@@\**                                    ,,`\\@@@\,,*                                                                                                                                                    *`,,@@@/`*`,                            **=@@^ *                                **,@@@\,                                                                                                                                                **]@@@@\*,*^                                    ,*\@@@\`                                                                                       
//                                                                                            ******,@@@@^                                            *\\@@@\`*`,,                                                                                                                                            ``/*,,@@@@`*                                 *=@@^**                                    ,@@@\`/*                                                                                                                                        *,`,,@@@@\,*                                            @@@@\*,,                                                                                   
//                                                                                            ****,@@@@/,*                                            */,\\@@@\`,`                                                                                                                                            */,\@@@/,`\*                                **=@@^**                                    *,/@@@\`*  *                                                                                                                                    *\\@@@@\,/`*                                            *`\@@@\*                                                                                   
//                                                                                            **]@@@@`                                                    *`/@@@\`/```                                                                                                                                    ****,,/@@@**                                    **=@@^**                                        *\@@@]`/**`,                                                                                                                            ***`,@@@/\\*                                                    \@@@\/*,                                                                               
//                                                                                            =@@@/, `                                                    ,,``,@@@\/**                                                                                                                                    ***,/@@@\`/*                                    **=@@^**                                        =*`\@@@``**`                                                                                                                            **,@@@/\`/**                                                    *,,@@@\`                                                                               
//                                                                                        **`*@@@*                                                            ,,=@@^,*                                                                                                                                *`*]=*/@@@^*                                         *=@@^**                                            *\@@@`***``*                                                                                                                        ,,@@@```                                                            =@@\****                                                                           
//                                                                                        ***=@@^`                                                            ,*,@@@**                                                                                                                                *`,,/@@@[`*`                                        **=@@^**                                            ,/*\@@@`\`^*                                                                                                                        *=@@^*,*                                                            *@@@****                                                                           
//                                                                                        `,,@@@`*                                                            **`\@@^*                                                                                                                            **``*`/@@@\*                                            ***@@^`*                                                */@@@\*\****                                                                                                                    ,@@@                                                                *\@@/***                                                                           
//                                                                                        *,=@@^**                                                            ****@@@*                                                                                                                            **,,,@@@\,`*                                            ***@@@**                                                **==@@@\*,*                                                                                                                     =@@^                                                                **@@@*`*                                                                           
//                                                                                        **@@@**`                                                                =@@^***,                                                                                                                    *****`\@@@\*                                                 **@@@*                                                     ,/@@@\//\**,                                                                                                            ***`@@@`                                                                **=@@^`*                                                                           
//                                                                                        ,=@@\***                                                                *@@@****                                                                                                                    ****=@@@@`**                                                ***@@@**                                                    ,*\[@@@\`***                                                                                                            ***=@@^*                                                                `**@@@**                                                                           
//                                                                                        *@@@                                                                    ,=@@/*`*                                                                                                                    ,*,@@@@*                                                    ***@@@**                                                        */\@@@***`]*                                                                                                        *`*@@@`*                                                                ***=@@^*                                                                           
//                                                                                        =@@^                                                                    **@@@***                                                                                                                    ,/@@//,,                                                    ***@@@**                                                        /,*`\@@@`^[`                                                                                                        **=@@^**                                                                ***`@@@*                                                                           
//                                                                                    ***`@@@*                        ,*`\            ,***                        **=@@^**                                                                                                                ,,`@@@/,                                                        ***@@@**                                                            **\@@@/`,***                                                                                                    **@@@**                         `****`,**,**,]*`                            =@@^****                                                                       
//                                                                                    ***=@@^*                        ,,*]]]]]]]]]]]]]]\`,                        **`@@@**                                                                                                                ^/@@@\*/                                                        ***@@@*                                                             ,*`\\@@@]**`                                                                                                    `=@@^***                        **`,]/@@@@@\\,**                            *@@@****                                                                       
//                                                                                    ***@@@,                         ***@@@@@@@@@@@@@@@,*                        ***=@@^*                                                                                                            *\,/@@@\                                                            ** @@@*^                                                                ,\\@@@]*****                                                                                                `@@@                            *,@@@/[\/\\@@@@***,*                        *=@@^**`                                                                       
//                                                                                    **=@@^**                        ***@@@**        ****                        ** *@@@*                                                                                                            //@@@`**                                                            ***=@@**                                                                ,`*`[@@@\,\/                                                                                                =@@^                            =@@^, ,*,`[*`@@@^***                        **@@@`**                                                                       
//                                                                                    ,*@@@`**                        ***@@@**                                        =@@^                                                                                                        ,`,\@@@`                                                                * *=@@^*                                                                    *],@@@\*,*,*                                                                                        ****@@@*                            @@@`        *=@@^**`                        * =@@^**                                                                       
//                                                                                    *=@@^***                        ***@@^**                                        *@@@                                                                                                        ,]@@@^*,                                                                ***=@@^*                                                                    **``,@@@@/*\                                                                                        ***=@@^*                            @@@*        *=@@^***                        * *@@@=                                                                        
//                                                                                    ,@@@                            **,@@\,******,`**,*]                            *=@@^***                                                                                                *`*,@@@/                                                                    ***=@@^*                                                                        ``/@@@\*``**                                                                                    *,*@@@**                            /@@\`\``****,@@@                            *`*=@@^*                                                                       
//                                                                                    =@@^                            **=@@\@@@@@@@@@@][*,                            *,@@@***                                                                                                ,,@@@/`,                                                                    ***=@@^*                                                                        ,,*/*\@@\\*\                                                                                    **=@@/ *                            ,/@@@\\/`,]@@@/*                            ***,@@@`                                                                       
//                                                                                    =@@^                            ``=@@@[/    /,\@@@*\                            **@@@***                                                                                            ,`,`@@@@                                                                        * *=@@^*                                                                            ***@@@@``**/                                                                                , =@@/**                            ,`,\@@@@@@@@@]\`*``*                        ****@@@*                                                                       
//                                                                                    ,@@@                            *`***,`,    ,,*,@@@\                            *=@@/***                                                                                            *`/@@/*^                                                                        ***=@@^*                                                                            ****`\@@@`**                                                                                **,@@@**                            ,@@@``]``*,*[@@@=*``                        ***=@@/*                                                                       
//                                                                                    `=@@^,**                                        @@@/                            *@@@                                                                                            `,*`/@@@**                                                                          * *=@@^*                                                                                ***\@@@`*,*,                                                                            ***=@@^*                        =**]@@@`        **@@@***                        *,*@@@**                                                                       
//                                                                                    *,@@@***                                        \@@^                            =@@/                                                                                            ,*@@@@`,   *                                                                        ***=@@^*                                                                                **,`*@@@@/*`                                                                            ***,@@@*                        *^*=@@^*        **=@@^**                        **=@@/`*                                                                       
//                                                                                    , @@@^**                        *`/]`*,`    *,**@@@*                        ****@@@`                                                                                        \*`,/@@@/,**                                                                                @@^                                                                                     **`\@@@@*,*`                                                                            \@@^                        *`*/@@^/        *,@@@^,*                        **@@@***                                                                       
//                                                                                    * /@@@**                        \`@@@],*    `*//@@^^                        ,**=@@/`                                                                                        **,@@@\*****                                                                                @@@*                                                                                    `*,*`=@@@\\*                                                                            ,@@@                        **/[@@@,        *=@@@***                        *=@@/***                                                                       
//                                                                                    ***@@@^*                        *`*@@@@]****,/@@@\,*                        ***@@@^                                                                                     **`*,@@@^/,,                                                                                    @@@*                                                                                        ** \@@@\,*,,                                                                        ,@@@`***                        =@@@\`*`,*,\@@@/                            *@@@/ **                                                                       
//                                                                                    ***=@@\*                        **,,=\@@@@@@@@@`/,**                        **,@@/**                                                                                    ,*]@@@/,,* ^                                                                                    @@@*                                                                                        ****,,@@@\`*                                                                        *,@@@**                         ,*\@@@@@@@@@@[`*                            ,@@@****                                                                       
//                                                                                        @@@`                                                                    **/@@^**                                                                                ,**,,@@@/*,*                                                                                        @@@*                                                                                                \@@@/*`*                                                                    **@@@]*`                                                                *`**/@@^                                                                           
//                                                                                        ,@@@                                                                    *,@@/`**                                                                                ,,,@@@/`**,*                                                                                        @@@*                                                                                                **\@@@],                                                                    **=@@\*^                                                                =**,@@/*                                                                           
//                                                                                        *@@@`***                                                                */@@/ **                                                                            *`,**/@@@\**                                                                                            @@@*                                                                                                    \@@@`,*`                                                                **,@@@`*                                                                **`/@@^*                                                                           
//                                                                                        ,=@@\***                                                                ,@@@****                                                                            *\`/@@@,`**`                                                                                            @@@*                                                                                                    `*\@@@`,                                                                *,*O@@\*                                                                **,@@@**                                                                           
//                                                                                        **@@@^**                                                            ****/@@^                                                                            /*`*,/@@@`\`                                                                                                @@@*                                                                                                        /@@@\`,*                                                                @@@`                                                                **/@@^**                                                                           
//                                                                                        **=@@\**                                                            *^,,@@@`                                                                            `,*/@@@\*,*\                                                                                                =@@`                                                                                                        ,`,@@@\*                                                                =@@\                                                                ,,@@@`*`                                                                           
//                                                                                        ***@@@]*                                                            ,**/@@^*                                                                        `****/@@@^,*                                                                                                    =@@^                                                                                                            ,@@@\*,/                                                            ,@@@/*`*                                                            *=@@/=**                                                                           
//                                                                                        *,*/@@^*                                                            ,**@@@^*                                                                        *`/,@@@^/*`*                                                                                                    =@@^                                                                                                            *,/@@@\*                                                            *=@@^***                                                            *@@@,***                                                                           
//                                                                                            @@@\,,,,                                                    *`,`]=@@@/*`                                                                    `****,@@@@*`                                                                                                        =@@^                                                                                                                =@@@\`/*****                                                    ,,@@@@,*`,,`                                                    ,,*\@@@^                                                                               
//                                                                                            `[@@@\`,                                                    */*\@@@/=``*                                                                    */,\@@@/,/*`                                                                                                        =@@^                                                                                                                =*^\@@@`****                                                    ,/,[@@@@/``\                                                    `]@@@/,*                                                                               
//                                                                                            ***\@@@@]*,*                                            ****//@@@/`*                                                                    *****//@@@`*                                                                                                            =@@^                                                                                                                    *\@@@/,*,*``                                                    */@@@\`*``**                                            ***/@@@/                                                                                   
//                                                                                            ****,,@@@@]=                                            *``/@@@//,``                                                                    ***,/@@/\***                                                                                                            =@@^                                                                                                                    ,**\@@@/``=*                                                    **,[@@@@/`\*                                            =/@@@/*`                                                                                   
//                                                                                                ** \@@@@/*,*                                    **,**/@@@//*                                                                    ****,*/@@@``                    ,***************************,,]`                                                            =@@^                                                                                                                        *\@@@]`\*,**                                                    ,/@@@@]*\*],                                    ``*/@@@/                                                                                       
//                                                                                                ****/=@@@@/,                                    *`*/@@@//`\*                                                                    `*=*/@@@`**,                    `],@@@@@@@@@@@@@@@@@@@@@@@@@@@\*                                                            =@@^                                                                                                                        \**/@@@\``**                                                    ,,`[@@@@`\,*                                    `/@@@/*`                                                                                       
//                                                                                                      **\@@@]**`                            \**`,/@@@\`,                                                                    ,``*,`/@@@\*                    ,,*`,@@@@\/\[[[[[[[[[[[[[[[[[[[[[@@@\`/*                                                        *@@@                                                        ,*`,,/]]]]]]]]]]]]]]]]]]]]]]/]]]\**`                                */@@@\******                                                    *,\@@@`****,                            ``,/@@@/                                                                                           
//                                                                                                    *   ``\@@@/,                            /,`/@@@[`,`*                                                                    ``,,,@@@\*`*                    ``,@@@/\\`*,********************`,/@@@\,                                                        *@@@                                                        /,\@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\/\                                \**/@@@\`\**                                                    `,*/\@@@]\**                            `/@@@^**                                                                                           
//                                                                                                            \@@@`,**                    `,*`,/@@@^,*                                                                    ****`^\@@@\*                    `*`*/@@@@,**                            ,@@@\,``****                                                *@@@                                                    \,`,,@@@@`**                    **`\@@@\,*,,                                ,,@@@\***``,                                                    ,,@@@@`,`**`                    *``/@@@\                                                                                               
//                                                                                                            ,[@@@@``********************```@@@@[`*`*                                                                    ****,@@@/ **                    `*@@@@/*****                            ,,=@@@@`****                                                *@@@                                                    *`,@@@/`****                    `***`,@@@\**                                `,*`\@@@`^`/                                                    `\,`\@@@][**********************`/@@@`/*                                                                                               
//                                                                                                                \@@@@@@@@@@@@@@@@@@@@@@@@@@@@`]*                                                                        **,@@@@*                    *,*`/@@@/,*,                                    /@@@@`*,****                                            *@@@                                                **`,/@@@@,**                            , ^\@@@@`*,*                                ,`\@@@/*****                                                    /`\@@@@@@@@@@@@@@@@@@@@@@@@@@@@`                                                                                                   
//                                                                                                                `*`,************************,,**                                                                        \@@@//*,                    ,,@@@@@,,**,                                    *,/@@@@`****                                            *@@@                                                =*@@@@/,****                            *****,@@@@]=                                **`*\@@@],**                                                    *,,,*************************,`*                                                                                                   
//                                                                                                                                                                                                                    ``,/@@/`                    ,**`/@@@/***                                            ,@@@@``*****                                        *@@@                                            `*/,/@@@/***                                    ***\@@@@/***                                ,,\@@@`*,,`*                                                                                                                                                                                   
//                                                                                                                                                                                                                    */@@/,*/                    /\/@@@^,,`*,                                            ,**\@@@^``**                                        *@@@                                            [*/@@@/`,`*,                                     ***/=@@@@`=                                ,``*[@@@\,\/                                                                                                                                                                                   
//                                                                                                                                                                                                                `\*/@@@\                    ,*\\@@@@/]**                                                    ,\@@@\,*                                        *@@@****                                    ,**`/@@@/,,*                                                \@@@]***                                *`=@@@\*,*]*                                                                                                                                                                               
//                                                                                                                                                                                                                `/@@@^,*                    **@@@@`,,**,                                                    ,,`\@@@`                                        *=@@^***                                    /\/@@@`[,`*`                                                ``\@@@``                                ***\,@@@\,*`                                                                                                                                                                               
//                                                                                                                                                                                                            ,,`,@@@\                        *=@@@`**                                                            =@@\**,*                                     =@@^***                                **,*/@@@/]**                                                        \@@@\`,*                                \,,@@@\`*,*`                                                                                                                                                                           
//                                                                                                                                                                                                            ,,@@@`,,                        */@@`***                                                            *\@@`***                                    *=@@^***                                ***=@@^,**`*                                                        /`@@@,**                                ,,*/,\@@\,*,                                                                                                                                                                           
//                                                                                                                                                                                                        **`]@@@/                            ,@@@                                                                ,=@@\,*`                                    *=@@^ **                                **,@@@**                                                            ,*\@@^**                                    **,@@@@`**,/                                                                                                                                                                       
//                                                                                                                                                                                                        *,@@@/*,                            @@@^                                                                **@@@`,*                                    *=@@^* *                                *,=@@^`*                                                            ***@@@**                                    *****\@@@/`\                                                                                                                                                                       
//                                                                                                                                                                                                    *`*]@@@/                            ***,@@@*                                                                **=@@\`*                                    *=@@^***                                *,@@@***                                                            ***\@@^*                                        **`\@@@`*,*/                                                                                                                                                                   
//                                                                                                                                                                                                    *[/@@/*\                            ***/@@^`                                                                ***@@@`*                                    *=@@^***                                *=@@\***                                                            *,**@@@*                                        `*,`*\@@@/**                                                                                                                                                                   
//                                                                                                                                                                                                `***/@@/                                **,@@@**                                                                **^\@@\`                                    *=@@^***                                ,@@@                                                                    =@@^****                                        **`\@@@\*,*`                                                                                                                                                               
//                                                                                                                                                                                                ,,/@@@^,                                **/@@^**                                                                ****@@@`                                    *,@@^***                                =@@^                                                                    `@@@***^                                        ,*]**[@@@@,*                                                                                                                                                               
//                                                                                                                                                                                            *``*/@@@/***                                *,@@@***                        `*,*`*/*``****,`                            =@@\***`                                **@@@***                            ****@@@`                                                                    *=@@^=,*                                            ***\@@@\,*,,                                                                                                                                                           
//                                                                                                                                                                                            ,*\@@@`*****                                */@@\*`*                        `/,/,/@@@@@@@@],                            ,@@@`***                                * @@@***                            ***=@@^*                                                                    **@@@***                                            ****`,@@@\,*                                                                                                                                                           
//                                                                                                                                                                                        ,`*`,@@@/,**                                    ,@@@                            *`/@@@@*    @@@@``*\                        *=@@\***                                 *@@@***                            *`*@@@**                        `]]]]]]]]]]]]]\]]]``                        ``=@@^**                                                    \@@@/**`                                                                                                                                                       
//                                                                                                                                                                                        ,*\@@@//*]**                                    =@@^                            ,/@@/*,*    ,,@@/``\                        *=@@@***                                **@@@***                            **=@@^**                        `@@@@@@@@@@@@@@@@@^`                        * ,@@@**                                                    **@@@@`*                                                                                                                                                       
//                                                                                                                                                                                    **/,,@@@/***                                    ****@@@*                            `@@/                                        *`\@@\**                                 *@@@***                            **@@@`**                                    ``]@@@**                        ***=@@/,                                                        \@@@/,*`                                                                                                                                                   
//                                                                                                                                                                                    *`,@@@/*****                                    ***=@@^*                            =@@\                                        **`@@@**                                 *@@@***                            *=@@^***                                    ,=@@^***                        ****@@@*                                                        /*\@@@/,                                                                                                                                                   
//                                                                                                                                                                                *`**,/@@@***                                        ***@@@**                            @@@*/,/@@@@@]*`****,                        **`\@@/,                                 *@@@***                            *@@@                                    *,*,/@@`                                =@@^****                                                        @@@@]\,/                                                                                                                                               
//                                                                                                                                                                                *\\/@@/,****                                        **/@@^**                            @@@/@@//[[/\@@@]****                        ****@@@*                                **@@@*                              =@@^                                    ***@@@^*                                 @@@****                                                        **,@@@\,                                                                                                                                               
//                                                                                                                                                                            /,\`*/@@@`\*                                            **=@@^`*                            @@@@/***    *@@@\*`*                        ***/@@@`                                **=@@* *                        *  *@@@*                                    ``=@@^``                                *=@@^,=*                                                            ,@@@\*/*                                                                                                                                           
//                                                                                                                                                                            */*/@@@\,*``                                            ***@@@**                            @@@\ ***    *,\@@/`*                        **^=@@^*                                **=@@^                            **@@@^                                    *=@@\`*`                                *=@@^ **                                                            ,`/@@@\`                                                                                                                                           
//                                                                                                                                                                        ,[***/@@@^**                                                ***=@@^*                            @@@*        **\@@^,,                        ``*@@@*,                                **=@@^**                            =@@^                                `***]@@^                                    *@@@                                                                    ,\@@@***                                                                                                                                       
//                                                                                                                                                                        *`,]@@@`/***                                                ****@@@*                            \@@`        **=@@^,*                        **=@@^**                                **=@@^**                            *@@@                                ****@@@,                                    =@@^                                                                    /**[``**                                                                                                                                       
//                                                                                                                                                                    ,``*,,@@@//*                                                        =@@^****                        ,@@\*`*,    *`@@@]**                        **@@@`**                                **=@@^*                             *=@@^***                            ,**=@@^*                                ****@@@*                                                                                                                                                                                                                   
//                                                                                                                                                                    `,*\@@@///*`                                                        *@@@ ***                        `/@@\`,*    */@@/``*                        *=@@^`**                                **=@@^**                            *,@@@***                            **=@@@*\                                ***=@@^*                                                                                                                                                                                                                   
//                                                                                                                                                                *****/@@@/*`                                                            *\@@^***                        ,,,@@@\]]]/@@@@\                            *@@@                                    **=@@^**                            , =@@/**                            `*=@@^**                                ***@@@**                                                                                                                                                                                                                   
//                                                                                                                                                                ***,/@@/\*`*                                                             *@@@**^                        ,*,,,[\@@@@@[]*,                            =@@^                                    **=@@^**                            **,@@@**                            **=@@^*,                                *,=@@/**                                                                                                                                                                                                                   
//                                                                                                                                                            ***`,*/@@/`*                                                                ,,=@@^**                                                                ****@@@*                                    **=@@^*                             ***=@@^*                            ,//@@\,,                                **@@@`**                                                                                                                                                                                                                   
//                                                                                                                                                            **=*/@@@`**/                                                                * *@@@**                                                                ***=@@^*                                    **,@@^**                            ***,@@@*                            ``*,`[*                                 *=@@@ **                                                                                                                                                                                                                   
//                                                                                                                                                        `,****/@@@\,                                                                    ***=@@^*                                                                ***@@@**                                    * *@@@**                                \@@^                                                                    *@@@**                                                                                                                                                                                                                     
//                                                                                                                                                        */,[=@@@`**`                                                                    ****@@@*                                                                **=@@^**                                    ***@@@**                                ,@@@                                                                    =@@/ *                                                                                                                                                                                                                     
//                                                                                                                                                    *****\\@@@\*                                                                            \@@^                                                                **@@@**                                       *@@@**                                *@@@^***                                                            *`**@@@`                                                                                                                                                                                                                       
//                                                                                                                                                    ****,@@@/***                                                                            *@@@                                                                *=@@/ **                                    ***@@@**                                *,@@@***                                                            ***=@@/^                                                                                                                                                                                                                       
//                                                                                                                                                    ***=@@/*                                                                                *=@@^,*`                                                        ****\@@@                                        ***@@@**                                **@@@^**                                                            ``*/@@/*                                                                                                                                                                                                                       
//                                                                                                                                                    *`^**,/,                                                                                *,@@@/,*                                                        **,,=@@^                                        * *@@@**                                **,@@@ `                                                            **,@@@**                                                                                                                                                                                                                       
//                                                                                                                                                                                                                                            *`=@@@\`\,,/                                                *,,*,`=@@@/`                                        ***@@@**                                **,@@@`*****                                                    ,*`**`/@@`**                                                                                                                                                                                                                       
//                                                                                                                                                                                                                                            ***,[@@@\\**                                                */,//@@@/,**                                        ***@@@**                                ***=@@@@``**                                                    **,,/@@@/***                                                                                                                                                                                                                       
//                                                                                                                                                                                                                                                **,@@@\,`**`                                        **`*`*\@@@/*                                            * `=@@**                                    */@@@\,*`\,`                                            \,**,*]@@@/*                                                                                                                                                                                                                           
//                                                                                                                                                                                                                                                ,*``/@@@@]`,                                        **],/@@@@**`                                            ***=@@^*                                    **`/@@@@/`\\                                            *`,,,@@@/,**                                                                                                                                                                                                                           
//                                                                                                                                                                                                                                                    */,@@@@^```\                                *****//@@@//                                                * *=@@^*                                        */@@@@]*,*`*                                    ,*`*/,/@@@/*                                                                                                                                                                                                                               
//                                                                                                                                                                                                                                                    **,,/@@@@^,,                                * *`/@@@@*`/                                                ** =@@^*                                        **,[@@@@/`\*                                    **],/@@@/*`,                                                                                                                                                                                                                               
//                                                                                                                                                                                                                                                        ,`/\@@@`*,*`                        ****`/@@@@/*                                                    ***=@@^*                                            ,=@@@@`**`,/                            *****//@@@@*                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                        ,*\,`\@@@^*\                        ****@@@@\**/                                                    ***=@@^*                                            ,,][@@@@`\*,                            * *`/@@@@`*`                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                            **,@@@@`*`**********************`,@@@@[/                                                        = *=@@^*                                                ,=\@@@`*,***                    ****,*/@@@``                                                                                                                                                                                                                                       
//                                                                                                                                                                                                                                                            ****,@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@`,*                                                         ***=@@^*                                                **`,\@@@]**`                    **/,/@@@^`,*                                                                                                                                                                                                                                       
//                                                                                                                                                                                                                                                                `,,\[[[[[[[[[[[[[[[[[[[[[[[[/\[*                                                            ***=@@^*                                                    */\@@@]]]]]]]]]]]]]]]]]]]]]]]]/@@@\*                                                                                                                                                                                                                                           
//                                                                                                                                                                                                                                                                *,`*****************************                                                            * * @@\*                                                    `,*`\@@@@@@@@@@@@@@@@@@@@@@@@@@@\,,,                                                                                                                                                                                                                                           
//                                                                                                                                                                                                                                                                                                                                                                @@@                                                                                                                                                                                                                                                                                                                                    
//                                                                                                                                                                                                                                                                                                                                                                @@@*                                                                                                                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                                                                                                                                @@@*                                                                                                                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                                                                                                                                @@@*                                                                                                                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                                                                                                                                @@@*                                                                                                                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                                                                                                                                @@@                                                                                                                                                                                                                                                                                                                                    
//                                                                                                                                                                                                                                                                                                                                                                @@@*                                                                                                                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                                                                                                                                \@@*                                                                                                                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                                                                                                                                =@@^                                                                                                                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                                                                                                                                =@@^                                                                                                                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                                                                                                                                =@@^                                                                                                                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                                                                                                                                =@@^                                                                                                                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                                                                                                                                =@@^                                                                                                                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                                                                                                                                =@@^                                                                                                                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                                                                                                                                =@@^                                                                                                                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                                                                                                                                =@@^                                                                                                                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                                                                                                                                =@@^                                                                                                                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                                                                                                                                *@@@                                                                                                                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                                                                                                                                *@@@                                                                                                                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                                                                                                                                *@@@                                                                                                                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                                                                                                                                *@@@                                                                                                                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                                                                                                                                *@@@                                                                                                                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                                                                                                                                *@@@                                                                                                                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                                                                                                                                *@@@                                                                                                                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                                                                                                                                *@@@                                                                                                                                                                                                                                                                                                                                   
//                                                                                                                                                                                                                                                                                                                                                                 \@@* **                                                                                                                                                                                                                                                                                                                               
//                                                                                                                                                                                                                                                                                                                                                                *=@@^***                                                                                                                                                                                                                                                                                                                               
//                                                                                                                                                                                                                                                                                                                                                                *=@@^***                                                                                                                                                                                                                                                                                                                               
//                                                                                                                                                                                                                                                                                                                                                                 =@@^***                                                                                                                                                                                                                                                                                                                               
//                                                                                                                                                                                                                                                                                                                                                                *=@@^***                                                                                                                                                                                                                                                                                                                               
//                                                                                                                                                                                                                                                                                                                                                                *=@@^* *                                                                                                                                                                                                                                                                                                                               
																