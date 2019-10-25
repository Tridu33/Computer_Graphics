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
		 
		 //2019.10.13吉林长春
		//原理性的基础性的造轮子基于应该扎实训练，然后乖乖当个api程序员，但是不要害怕出Bug之后深挖进去最低层的调Bug,明晰轮子是怎么造出来的有助于理解技术和调Bug
	   //疯狂挖坑写注释，其实想到一些问题会写在文章注释里，欢迎注释补充PR本仓库
	  //关于文中的内容有什么赐教的麻烦联系2055969978@qq.com
	 // http://www.coderonline.net/programming-windows-series-first-the-basic-framework-for-the-windows-sdk-programming.html
*/

	 //《计算机图形学》第二版 徐长青等编著
	 //原书没有随书代码，这学期刚好学到，写出来随书代码吧，随便做点小笔记。取消对应注释命令就能运行，vs2019析出，向右X轴正方向向下Y轴正方向

#define PI 3.1415926

#include <stack>
#include<atlstr.h>
#include<iostream>
#include <windows.h>
#include <math.h>
#include <vector>




using namespace std;

//注册窗口名称
static TCHAR szAppName[] = TEXT("GDI_Tridu33");

//声明 窗口过程函数
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//窗口入口函数 extern "C" int __stdcall WinMain // int WINAPI WinMain写成这样也行
extern "C" int __stdcall WinMain(HINSTANCE hInstance, 
								HINSTANCE hPrevInstance, 
								PSTR szCmdLine, 
								int iCmdShow)
{
	HWND     hWnd;
	MSG      msg;
	WNDCLASS wndclass;
//构造创建窗口参数
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
//注册窗口类型
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"), szAppName, MB_ICONERROR);
		return 0;
	}
//创建窗口，szAppName一定要是注册过窗口
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

	while (GetMessage(&msg, NULL, 0, 0))// 获取信息，当接收到WM_QIUT消息时，GetMessage函数返回0，结束循环
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);// 派发消息，到WindowPro函数处理
	}

	return msg.wParam;
}


//--------------------------------------------------------------------------------------------------
//华丽的分割线，这部分是图形学算法实现具体方法调用
//--------------------------------------------------------------------------------------------------

//绘制指定属性的直线
static void DrawLine(HDC hDC, int x0, int y0, int x1, int y1, int style, int width, COLORREF color)
{
	HPEN hPen = CreatePen(style, width, color);
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);

	MoveToEx(hDC, x0, y0, NULL);
	LineTo(hDC, x1, y1);

	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);
}

//绘制实心圆
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

//绘制填充矩形
static void DrawRect(HDC hDC, int left, int top, int width, int height, int style, COLORREF color)
{
	HBRUSH hBrush = CreateHatchBrush(style, color);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	Rectangle(hDC, left, top, left + width, top + height);

	SelectObject(hDC, hOldBrush);
	DeleteObject(hOldBrush);
}

//绘制位图填充矩形
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
//全局变量label区分12345678个区间的不同类型，进而仅仅用一个区间的算法画出来所有区间（0<=k<=1和k>1等八个区间）直线，圆等对称结构的图像，甚至是区间段分形对称的图像
//同理可以改成二等分的象限中心对称label2,轴对称label2x,label2y,四等分的图像label4
//八等分的坐标系，正变换篇,通通给我变成第一象限0<=k<=1的情况，算完在mySetPixel处switch(label8)case调用匹配对应象限的逆变换回来
//Ascci码八分区间图像，详情看文末Ascii字符图像

//算法步骤:

//1. 把区间2345678逆变换到1区间

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

//2. 运行适用于1区间的代码，比如画八分之一圆，画使用条件（0<=k<=1 && x>=0 && y>= 0）的直线计算得到结果，里面的SetPixel函数通通换成mySetPixel
//3. 八等份的坐标系，case逆变换mySetPixel篇,详情看文末Ascii图像
//除了八等份对称变换，还能通过旋转矩阵，每次旋转45°得到结果。

static void mySetPixel(HDC hDC, COLORREF color,int x,int y) {
	switch (label8){
	case 1|5: SetPixel(hDC, x, y, color);
	case 2|6: SetPixel(hDC, y, x, color);
	case 7|3: SetPixel(hDC, y, -x, color);
	case 8|4: SetPixel(hDC, x, -y, color);
	default: 
		;// ?怎么输出printf "出错啦！"的结果;
	}
}


//---------------------------------------






//基础直线填充算法
// DDA直线扫描转换算法//斜率不存在，很多线不尽如人意画出来完全不一样的都有！比如e分母很小的时候会导致计算失真，输入的起点终点不正确的话，会变成很陡峭的一条完全不能看的线
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
//中点画线算法
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

//BresenhamLine算法//0<=m<z斜率第一象限下labelMark==1；
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
//BresenhamLine算法8等分第八象限//-1<=m<0斜率第四象限下labelMark==8；
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





// 中点画圆算法
static void MidpointCircle(HDC hDC, int R, COLORREF color) {

	HBRUSH hBrush = CreateSolidBrush(color);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	int x, y;double d;//double d253d+=2x报错
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

// Bresenham画圆算法
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

//第一象限椭圆弧的扫描转换中点算法
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
//填充函数要先画出来连通图，才能填充	
//DrawRect(hDC, 220, 20, 60, 40, HS_BDIAGONAL, RGB(255, 0, 0));在运行填充算法前面加这行，然后种子选一个内点
//本代码约定，边界用RGB(0,0,0)黑色，填充RGB(0,255,0)绿色，oldvalue背景白色RGB(255,255,255),newvalue用RGB(0,0,255)蓝色,COLORREF color闭着眼睛画线用红色RGB(255,0,0)

// 四连通内定义区域的填充算法
//extern int globalCount;//统计判断执行次数？？？？？？？
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

// 四连通边界定义区域的填充算法
static void Boundaryfill(HDC hDC, int x, int y, COLORREF boundaryvalue, COLORREF newvalue) {
	//(x,y)是给出的种子位置，boundary是边界上像素的值，newvalue是区域内象素应该被送入的新值，未填充的区域内不应有值为newvalue的值，有一个封闭图像的话会被挡住里面填充不到
	while (GetPixel(hDC, x, y) != boundaryvalue && (hDC, x, y) != newvalue )//未到达边界像素值，且未被填充过
	{
		SetPixel(hDC, x, y, newvalue);
		Boundaryfill(hDC, x, y - 1, boundaryvalue, newvalue);
		Boundaryfill(hDC, x, y + 1, boundaryvalue, newvalue);
		Boundaryfill(hDC, x - 1, y, boundaryvalue, newvalue);
		Boundaryfill(hDC, x + 1, y, boundaryvalue, newvalue);
//？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？
	}
}



/*


// 扫描直线种子填充算法 P34很长
void ScanlineSeedfill(HDC hDC, int x, int y, COLORREF boundaryvalue, COLORREF newvalue)
{
	using namespace std;
	int x0, x1, xr, y0, xid;
	bool flag;
	int count = 0;
	stack <Point> s;//书上是Point但是明明没有这个标识符
	//???????????????????????????????????????????????????????????????????????

	struct Point {
	int x;
	int y;
	};

Point p;
s.push(Point(x, y));//?????Point是元组？对象Point::Point{}?结构体？

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


//P36多边形扫描转换算法

//P40 边填充算法

//边标志算法























//图案填充 P43

//P72. Cohen-Sutherland算法(直线段裁剪算法)
void Cohen_Sutherland(double x0,y0,x2,y2){
	;
}
// 修改Cohen_Sutherland直线裁剪直线算法，开窗效果，窗口内部舍弃，外部保留
//

*/



//数值分析，计算方法 矩阵乘法，投影矩阵,图形二维三维矩阵变换，矩阵计算，×旋转矩阵，平移矩阵，透视矩阵，裁剪矩阵，球坐标直角坐标柱坐标广义坐标相互映射

vector<vector<int>> matrix_multiply(vector<vector<int>> arrA, vector<vector<int>> arrB)
{
	//矩阵arrA的行数
	int rowA = arrA.size();
	//矩阵arrA的列数
	int colA = arrA[0].size();
	//矩阵arrB的行数
	int rowB = arrB.size();
	//矩阵arrB的列数
	int colB = arrB[0].size();
	//相乘后的结果矩阵
	vector<vector<int>>  res;
	if (colA != rowB)//如果矩阵arrA的列数不等于矩阵arrB的行数。则返回空
	{
		return res;
	}
	else
	{
		//设置结果矩阵的大小，初始化为为0
		res.resize(rowA);
		for (int i = 0; i < rowA; ++i)
		{
			res[i].resize(colB);
		}

		//矩阵相乘
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



/*调用矩阵乘法方法
	vector<vector<int>> arrA = { { 2, 1 }, { 4, 3 } };
	vector<vector<int>> arrB = { { 1, 2 }, { 1, 0 } };
	//vector<vector<int>> arrA = { { 1, 2, 3 }, { 4, 5, 6 } };
	//vector<vector<int>> arrB = { { 1, 4 }, { 2, 5 }, { 3, 6 } };

	vector<vector<int>> res = matrix_multiply(arrA, arrB);

//————————————————
//二维变换，从P(x,y,1)到P'(x',y',1)

	int Tx=1;int Ty=2;
	vector<vector<int>> arrp = { {x,y,1 }};
	vector<vector<int>> arrPan= { { 1, 0,0 }, { 0,1, 0 } ,{Tx,Ty,1}};
	vector<vector<int>> arrp' = matrix_multiply(arrp, arrPan);

	int Sx=2;Sy=2;
	vector<vector<int>> arrp = { {x,y,1 }};
	vector<vector<int>> arrZoom= { {Sx, 0,0 }, { 0,Sy, 0 } ,{0,0,1}};
	vector<vector<int>> arrp' = matrix_multiply(arrp, arrZoom);

	int theta = pi;//double会好很多，但是计算过程Double然后描点必须int
	//最后类型转换什么时候开始合适？？？？？？？？？？？？？？？？？？？？？？？？
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

	//二维视见变换的矩阵形式根据书上同理可得，因为比较复杂，见下：
	vector<vector<int>> arrp = { {x,y,1 }};
	vector<vector<int>> arrView= { {(vxh-vxl)/(wxh-wxl),0,0 }, { 0,(vyh-vyl)/(why-wyl), 0 } ,{vxl-wxl*(vxh-vxl)/(wxh-wxl),vyl-wyl*(vyh-vyl)/(why-wyl),1}};
	vector<vector<int>> arrp' = matrix_multiply(arrp, arrView);
	//????????到底除法会出现Double，用什么合适？？？？？？？？？？？？int？long?Double?



	//三维矩阵变换

	int Dx=1;int Dy=2;int Dz=1;
	vector<vector<int>> arrp = { {x,y,z,1 }};
	vector<vector<int>> arrPan= {{ 1,0, 0,0 }, { 0,1, 0,0 }, { 0,0,1, 0 } ,{Dx,Dy,Dz,1}};
	vector<vector<int>> arrp' = matrix_multiply(arrp, arrPan);

	int Sx=2;Sy=2;
	vector<vector<int>> arrp = { {x,y,z,1 }};
	vector<vector<int>> arrZoom= { {Sx, 0,0 ,0}, { 0,Sy,0, 0 } ,{0,0,Sz,0},{(1-Sx)*x0,(1-Sy)*y0,(1-Sz)*z0,1}};
	vector<vector<int>> arrp' = matrix_multiply(arrp, arrZoom);

	int theta = pi;//double会好很多，但是计算过程Double然后描点必须int
	//最后类型转换什么时候开始合适？？？？？？？？？？？？？？？？？？？？？？？？
	vector<vector<int>> arrp = { {x,y,z,1 }};//Z
	vector<vector<int>> arrRotate= { { cos(theta),sin(theta),0 ,0}, {-sin(theta),cos(theta),0,0 } ,{0,0,1,0},{0,0,0,1}};
	vector<vector<int>> arrp' = matrix_multiply(arrp, arrRotate);

	vector<vector<int>> arrp = { {x,y,z,1 }};//X
	vector<vector<int>> arrRotate= { {1,0,0,0},{ 0,cos(theta),sin(theta),0 }, {0,-sin(theta),cos(theta),0 } ,{0,0,0,1}};
	vector<vector<int>> arrp' = matrix_multiply(arrp, arrRotate);

	vector<vector<int>> arrp = { {x,y,z,1 }};//Y
	vector<vector<int>> arrRotate= { { cos(theta),0,sin(theta),0 }, {0,1,0,0},{-sin(theta),0,cos(theta),0 } ,{0,0,0,1}};
	vector<vector<int>> arrp' = matrix_multiply(arrp, arrRotate);

	//看书各种变换符合起来就能成为很复杂的变换矩阵。P61

	//正交投影
	//正视图
	vector<vector<int>> arrFrontView= {{ 0,0, 0,0 }, { 0,1, 0,0 }, { 0,0,1, 0 } ,{0，0，0,1}};
	//侧视图
	vector<vector<int>> arrSideView= {{ 1,0, 0,0 }, { 0,0, 0,0 }, { 0,0,1, 0 } ,{0，0，0,1}};
	//顶视图
	vector<vector<int>> arrTopView= {{ 1,0, 0,0 }, { 0,1, 0,0 }, { 0,0,0, 0 } ,{0，0，0,1}};
	//斜交投影
	vector<vector<int>> arrTopView= {{ 1,0, 0,0 }, { 0,1, 0,0 }, { l*cos(alpha),l*sin(alpha),0, 0 } ,{0，0，0,1}};
	//单点透视Single point perspective

	//2点透视Two point perspective

	//3点透视Three point perspective


	//透视投影转平行投影矩阵？P???????????


//blog.csdn.net/yang20141109/article/details/51024373

//------------------------------------------------------------------------------脑洞......
//C++复数运算计算二维图形变换，《复分析可视化》
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
	//~Complex();//析构函数

private:
	double _real;
	double _image;
};

Complex::Complex(double r=0.0,double i=0.0)
{
	_real=r;//复数实部
	_image=i;//复数虚部
}
Complex Complex:: operator+(const Complex c)//两复数相加
{
	Complex tmp;
	tmp._real =_real+c._real ;
	tmp._image =_image+c._image ;
	return tmp;
}
Complex Complex::operator-(const Complex &c)//两复数相减                                    c的值在函数内部不需要改变，所以采用常引用
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
	double deno=c._real*c._real+c._image*c._image;//有理化后的分母denominator
	tmp._real=deno*((_real*c._real)+(_image*c._image));
	tmp._image=deno*((_image*c._real )-(_real*c._image));
	return tmp;
}
Complex& Complex ::operator+=(const Complex c)//加上自身
{
	this->_real += c._real ;
	this->_image += c._image ;
	return *this;
}
Complex& Complex::operator-=(const Complex c)//加上自身
{
	this->_real -= c._real ;
	this->_image -= c._image ;
	return *this;
}
bool Complex::operator==(const Complex &c)//判断两个复数是否相等
{
	return(_real==c._real)&&(_image==c._image);
}
Complex Complex::operator++()//前置++
{
	this->_real+=1;
	this->_image+=1;
	return *this;
}
Complex Complex::operator++(int)//后置++
{
	Complex tmp(*this);//拷贝构造用来保存原来的值
	this->_real++;
	this->_image++;
	return tmp;//返回临时变量所以不能以引用作为返回值
}
Complex	Complex::operator--()//前置--
{
	this->_real-=1;
	this->_image-=1;
	return *this;
}
Complex Complex::operator--(int)//后置--
{

	Complex tmp(*this);//拷贝构造用来保存原来的值
	this->_real--;
	this->_image--;
	return tmp;//返回临时变量所以不能以引用作为返回值
}

void Complex::print(Complex &c)
{
	cout<<c._real<<"+ "<<c._image<<"i"<<endl;
}

————————————————
//链接：https://blog.csdn.net/wodeqingtian1234/article/details/51838888

//使用方法举例
	Complex *c=NULL;
	Complex c1(6.0,5.0);
	Complex c2(3.0,4.0);
	Complex ret;
	cout<<(c1==c2)<<endl;//输出c1,c2是否相等
	c->print(c1);//输出c1+c2
	c->print(c2);
	cout<<"c1+c2=";
	ret=c1+c2;
	c->print(ret);
	c->print (c1);//输出c1自加
	ret=++c1;
	c->print(ret);//

*/



//C++四元数运算计算三位矢量图形，量子计算---布洛赫球(Bloch Sphere)表示对应的“量子位---物理量子状态”
//量子力学中， Dirac编码实现运算规则是怎么样的？把对应定理公式，演算规则编程实现“本源量子位”？QPanda？PyPanda？？？

/*
//基础计算 https://download.csdn.net/download/wf20080798/4926593 功能有限的四元数运算
//指路：https://blog.csdn.net/zhuoyueljl/article/details/70789472 四元数、欧拉角、旋转矩阵之间互相转换C++源码
//https://blog.csdn.net/jin_syuct/article/details/49785541 四元数插值
//太多了，链接文件等有空整理再说吧，遥遥无期......
*/



//C++画出Meshgrid等matlab轻而易举地Meshgrid的三维坐标系立体网格图像？怎么做？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？
/*
//？？？？？？？？？？？？？？？
*/

/*
//裁剪算法 第六节
//P72. Cohen-Sutherland算法(直线段裁剪算法)
void Cohen_Sutherland(double x0,y0,x2,y2){
	;
}
// 修改Cohen_Sutherland直线裁剪直线算法，开窗效果，窗口内部舍弃，外部保留
//
//
void Cohen_Sutherland(double x0,y0,x2,y2){
	;
}//P 73

//P82




//梁友栋-Barsky裁剪算法
//P75. 二维梁友栋算法
void L_Barsky(double x0,y0,x2,y2){
	double t0,t1,deltax,deltay;
	t0=0.0;t1=1.0;
	deltax==x2-x1;
	if(!cansee(-deltax,x0-x1,t0,t1))return;
	if(!cansee(deltax,));
}


//P82. 三维梁友栋算法
Double zh,zy;
void T_Barsky(double x0,y0,x2,y2,z2){
	;
}

*/


//曲线曲面章节，常用曲线，贝塞尔，B样条，各种插值算法
/*
//拉格朗日插值




//三次Hermite插值



//规范化三次Hermite插值


//Coons曲面

//Bezier曲线几何作图算法 P 107
void bez_to_points(Point P[] ,int n ,Point pts[],int npoints){
	;
}
//分裂过程算法 P110
void split_Bezier(Point P[]){
	;
}

void new_split_Bezier(Point P[]){
	;
}
//Bezier曲面







//B样条线           de Boor算法
//输入参数CP为控制点坐标
//控制点P的个数为n+1；
//输入参数k是B样条线参数
//输入参数knot为节点向量，长度n+k+1
//输出参数采用deBoor算法生成B样条线的离散点序列pts
//整条离散点序列pts的个数npoints+1
static void bspline_to_points(){
	;
}

//B样条线曲面


*/

//第五章图形运算,布尔运算交并补，求直线交点，凸包计算几何，几何关系代数判断，椭圆双曲线焦点内积，直线裁剪，交点
/*

//线段交点
int jiaodian_line(){

return 1;
}

//多条线段交点

int jioadian_lines(){


return 1;
}



//平面的凸壳Graham算法
int Polygon_Polygon(POINT P[],int n,POINT Q[],int m){

}

//155
void Graham(POINT S[],int n)
{

}

void Javis(POINT S[],int n){

}

//简单多边形的包含算法
//158
void inner(POINT X[],int n,POINT P){


}


凸多边形的包含算法
//160
void inner1(){
}







//凸多边形重叠算法
void Advance(POINT P[],int n ,POINT Q[],int m){



}
void Output(POINT P[],int 1,POINT Q[],int m){


}
void Convex_polygon_intersection(POINT P[],int 1,POINT Q[],int m){

}


//简单多边形的三角剖分算法
//164
void Simple_polygon_triangulation(POINT *P,int n){

}











*/

//邓俊辉Mooc---计算几何相关章节
/*





*/

/*
//形体的表示以及数据结构
//曲线：折现法

//曲线：带树法 P171
BINARY *Create(float *P,int i ,int j,float W){
	;
}
//不同分辨率显示带树表示的曲线
void Display(){
	;
}
//规则四叉树

//线性四叉树

//一对四时四叉树


//三维实体

//几何信息+拓扑信息
//点->线->环->面->外壳->形体->体素：1单元实体2扫描体3代数半空间定义的形体{（x,y,z）|f(x,y,z)<=0}

//1.CSG是实体几何构造法，CSG树::=<>|<><><>|<><><> BNF范式的定义
//2.特征表示：形状精度技术要求材料......

//3.边界表示!!!简单易行！
//八叉树
TREE *tree_8(cube c,graph g){
	;
}


*/


//------------------------------分形章节分界线----------------------------------------------------


//分形章节，有趣的图形，心形等，参考孙博文的《分形算法与程序设计：Visual C++实现》，这段不是我亲手打的代码，推荐链接和书本把
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

//代码参考孙博文的《分形算法与程序设计:Visual C++实现》
//————————————————
//版权声明：本文为CSDN博主「夜行歌」的原创文章，遵循 CC 4.0 BY - SA 版权协议，转载请附上原文出处链接及本声明。
//原文链接：https ://blog.csdn.net/qaz2549066580/article/details/41290877



//这部分可能和前面矩阵的复数重复定义，不要两个取消注释就行，因为网上已经很多了，
//比如这个 https://www.cnblogs.com/easymind223/archive/2012/07/05/2578231.html
//比如这里 https://blog.csdn.net/xizhibei/article/details/6664184
//就不重复抄上代码啦，把一个代表性的分形调通代码如下：
//————————————————
//版权声明：本文为CSDN博主「十觞亦不醉」的原创文章，遵循 CC 4.0 BY - SA 版权协议，转载请附上原文出处链接及本声明。
//原文链接：https ://blog.csdn.net/zhangpiu/article/details/49511107



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

//颜色设置// = 137.0  = 30.0 
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

//https://www.zhihu.com/question/20187195 参考
//https://www.cnblogs.com/easymind223/archive/2012/07/05/2578231.html 分形
*/

//--------------------------------分形分界线--------------------------------------------------


//第七章 消除隐藏线和隐藏面算法
//十节都是不同详细的算法描述......
//第八章真实感图形的绘制也是如此，算法描述
//撸不动代码了，剩下的书上连伪代码都不给，
//而且有轮子做个api程序员也很重要，基础算法，学会数学推导建模，能用计算机实现自己思路就够了
//是时候学习《Windows核心编程》，《OpenGL编程精粹》《Three.js开发指南》等等WebGL,OpenGL，美术审美了。
//nehe openGl的教程很棒。




//--------------------------------------------------------------------------------------------------
//华丽的分割线，取消注释就能画图，向右X轴正方向向下Y轴正方向
//--------------------------------------------------------------------------------------------------


//详细定义 窗口过程函数
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
			SetPixel(hDC, i, 10, RGB(0, 0, 0)); //绘制像素点
		}
//--------------------------------------------------------------------------------------------------
//华丽的分割线,这部分取消想看的部分算法的对应调用注释，就能看见算法图形学画图效果
//--------------------------------------------------------------------------------------------------

		//DDALine算法
		//DDALine(hDC,RGB(0,255,0),0.0,0.0,90.0,50.0);

		//MidpointLine算法
		//MidpointLine(hDC, RGB(0, 255, 0), 0, 0, 90, 50);
		
		//BresenhamLine算法
		//先画出来一个定位用矩形		//DDALine(hDC, RGB(0,0,0), 0, 0, 200, 200);//基准对角线
		DrawLine(hDC, 0, 0, 0, 200, PS_DASHDOT, 1, RGB(100, 250, 100));//官方自带万能画线DrawLine
		DrawLine(hDC, 0, 0, 200, 0, PS_SOLID, 2, RGB(0, 0, 0));
		DrawLine(hDC, 200,200, 0, 200, PS_DASH, 1, RGB(100, 0, 200));
		DrawLine(hDC, 200, 200, 200,0, PS_DASH, 1, RGB(100, 0, 200));
		//对比正确的直线作为参考看BresenhamLine算法使用范围
		DrawLine(hDC, 100 - 50, 100 - 50, 100 + 50, 100 + 50, PS_DASHDOT, 1, RGB(100, 250, 100));
		DrawLine(hDC, 100 - 50, 100 + 50, 100 + 50, 100 - 50, PS_DASHDOT, 1, RGB(100, 250, 100));
		//然后就是画线判断适用范围内用哪个BresenhamLine
		BresenhamLine1(hDC, RGB(255, 0, 0), 100, 100, 100+50, 100+40);//八等份第一个象限
		BresenhamLine1(hDC, RGB(255, 0, 0), 100-50, 100-40, 100, 100);//BresenhamLine5八等份第五个象限和八等份第一个象限相同代码，可以只写右边一般的代码，因为也适用关于Y轴对称的另一半
		//不适用另外的八等分象限比如这个：BresenhamLine1(hDC, RGB(255, 0, 0), 100, 100, 100 + 50, 100 + 60);
		//BresenhamLine8(hDC, RGB(255, 0, 255), 100, 100, 100+50, 100-40);//八等份第八个象限可用
		//BresenhamLine8(hDC, RGB(255, 0, 255), 100-50, 100+40, 100, 100);//BresenhamLine4八等份第四个象限和八等份第八个象限相同代码


		// 中点画圆算法
		//MidpointCircle2(hDC,200,RGB(0,0,255));

		//BresenhamCircle算法
		//BresenhamCircle(hDC, 150, RGB(0, 0, 255));

		//看成功的填充例子
		//绘制不同填充模式的矩形？windows api自己找函数定义调用约定的意义就行。
		//DrawRect(hDC, 220, 20, 60, 40, HS_BDIAGONAL, RGB(255, 0, 0));
		//DrawRect(hDC, 220, 80, 60, 40, HS_CROSS, RGB(0, 255, 0));
		//DrawRect(hDC, 290, 20, 60, 40, HS_DIAGCROSS, RGB(0, 0, 255));
		//DrawRect(hDC, 290, 80, 60, 40, HS_VERTICAL, RGB(0, 0, 0));

/*
		//本文约定，边界用RGB(0,0,0)黑色，填充RGB(0,255,0)绿色，oldvalue背景白色RGB(255,255,255),newvalue用RGB(0,0,255)蓝色填充,COLORREF color闭着眼睛画线瞎用时可以选择红色RGB(255,0,0)
		// 四连通内定义区域的填充算法
		//不用DrawRect(hDC, 10, 10, 20, 20, HS_BDIAGONAL, RGB(0, 0, 0));//x1,y1,x2,y2在运行填充算法前面加这行画个矩形形状，然后选一个内点(150,150)作为种子
		//会不会是矩阵自动填充之后渲染出来不能在改？？上一行不能用
		double i = 30.0;//20不行的原因是什么？20/2=10整除？？？？？？？？
		double time = 0;
		double counts = 0;
		LARGE_INTEGER nFreq;
		LARGE_INTEGER nBeginTime;
		LARGE_INTEGER nEndTime;
		QueryPerformanceFrequency(&nFreq);
		QueryPerformanceCounter(&nBeginTime);//开始计时  
		DDALine(hDC, RGB(0, 0, 0), 0.0, 0.0, 0.0, i);
		DDALine(hDC, RGB(0, 0, 0), i, 0.0, 0.0, 0.0);
		DDALine(hDC, RGB(0, 0, 0), i, i, i, 0.0);
		DDALine(hDC, RGB(0, 0, 0), i, i, 0.0, i);
		Floodfill(hDC, floor(i/2), floor(i/2), RGB(255, 255,255), RGB(0, 0, 255));
		QueryPerformanceCounter(&nEndTime);//停止计时  
		time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位为s 
		CString txt_Res;
		txt_Res.Format(_T("%lf"),time*1000);
		//CString txt;
		//txt.Format(_T("%d"), globalCount);
		//CString str;
		//str.Format(_T("运行时间是：%lu ms"),dwEnd - dwStart);//DWORD是什么格式？https://stackoverflow.com/questions/3209909/how-to-printf-unsigned-long-in-c
		//sprintf_s(str, "时间是%DWORD",dwEnd-dwStart);
		//MessageBox(NULL, txt,TEXT("title"),MB_OK);
		MessageBox(NULL, "running time is:"+ txt_Res +"ms", TEXT("标题"), MB_OK);//MessageBox用法https://blog.csdn.net/weixin_37605770/article/details/79049986
		/*2种办法：
		1、
		CString s;
		s.Format(_T("%d"), posX);
		MessageBox(..., s,...);
		2、
		LPTSTR lpsz = new TCHAR[100];
		_itot(posX, lpsz, 10);
		MessageBox(..., lpsz,...);		//搞成100肉眼可见的栈溢出和延迟
		delete lpsz;
		*/
		

		// 四连通边界定义区域的填充算法
		//DDALine(hDC, RGB(0, 0, 0), 0.0, 0.0, 0.0, 3.0);
		//DDALine(hDC, RGB(0, 0, 0), 3.0,0.0, 0.0, 0.0);
		//DDALine(hDC, RGB(0, 0, 0), 3.0, 3.0, 3.0, 0.0);
		//DDALine(hDC, RGB(0, 0, 0), 3.0, 3.0, 0.0, 3.0);
		//不用DrawRect(hDC, 10, 10, 20, 20, HS_BDIAGONAL, RGB(0, 0, 0));//x1,y1,x2,y2在运行填充算法前面加这行，然后选一个内点(150,150)作为种子
		//会不会是矩阵自动填充之后渲染出来不能在改？上一行不能用？
		//Boundaryfill(hDC, 2, 2, RGB(0, 0, 0), RGB(0, 0, 255));
		//DrawRect(hDC, 100, 100, 200, 200...Boundaryfill(hDC, 150, 150, RGB(0, 0, 0), RGB(0, 0, 255));
		//是不是递归深度太深调用失败？？？？？？？报错内容：0x00115379 处有未经处理的异常(在 winddowsApi_GDI.exe 中): 0xC000041D: An unhandled exception was encountered during a user callback。 出现了 
		//不是，根本就是递归调用的时候就会出错，问老师问题在哪儿？？申请内存过大？递归调用过多？栈溢出？
		//？1，手动更改系统的栈空间大小。此种方法的缺点是，自己电脑设置完了之后，到别人电脑上还是会出现此异常；
		//2，减少函数中递归的次数；
		//3，检查代码中是否出现有死循环。？？？？？？？？？？？？？？？？？？？？？？？？？？？
		//

		//



		//	分形	Fractal 雪花曲线
		//system("color 2f");//还能这样操作。
		//Fractal(hDC,80, 40, 240, 360);
		//Fractal(hDC,240, 360, 420, 100);
		//Fractal(hDC,420, 100, 80, 40);

//	分形 F（z）=Z^2+C 在z = 0处，对复平面上每一点c进行迭代计算，若每一个 |f(z)| 小于2，则其属于集合内 	
//mandelbrot-set https://solarianprogrammer.com/2013/02/28/mandelbrot-set-cpp-11/


//	分形	Julia Set则是对于设定的一个常数c(其模假定小于2)，对复平面内的每一点z进行迭代计算，若满足模小于2则属于集合
//Julia-set




/*
 //这个注释块整个运行结果很明晰，功能比较齐全
		/*
		//详细调用函数约定Windows官方教程自己找更多api调用约定
		//绘制不同模式的直线
		DrawLine(hDC, 120, 30, 200, 30, PS_SOLID, 2, RGB(0, 0, 0));
		DrawLine(hDC, 120, 50, 200, 50, PS_DASH, 1, RGB(100, 0, 200));
		DrawLine(hDC, 120, 70, 200, 70, PS_DASHDOT, 1, RGB(100, 250, 100));
		//绘制弧线、弦割线、饼图
		Arc(hDC, 10, 30, 40, 50, 40, 30, 10, 40);
		Chord(hDC, 10, 60, 40, 80, 40, 60, 10, 70);
		Pie(hDC, 10, 90, 40, 110, 40, 90, 10, 100);

		POINT pt[4] = { {90,130},{60,40},{140,150},{160,80} };
		//绘制椭圆、矩形
		Ellipse(hDC, pt[0].x, pt[0].y, pt[1].x, pt[1].y);
		Rectangle(hDC, pt[2].x, pt[2].y, pt[3].x, pt[3].y);

		//绘制贝塞尔曲线
		PolyBezier(hDC, pt, 4);
		//标出贝塞尔曲线的四个锚点
		DrawCircle(hDC, pt[0].x, pt[0].y, 8, RGB(0, 255, 0));
		DrawCircle(hDC, pt[1].x, pt[1].y, 8, RGB(0, 0, 255));
		DrawCircle(hDC, pt[2].x, pt[2].y, 8, RGB(0, 0, 0));
		DrawCircle(hDC, pt[3].x, pt[3].y, 8, RGB(255, 0, 0));
		//绘制圆
		DrawCircle(hDC, 100, 180, 60, RGB(0, 250, 250));
		//绘制不同填充模式的矩形
		DrawRect(hDC, 220, 20, 60, 40, HS_BDIAGONAL, RGB(255, 0, 0));
		DrawRect(hDC, 220, 80, 60, 40, HS_CROSS, RGB(0, 255, 0));
		DrawRect(hDC, 290, 20, 60, 40, HS_DIAGCROSS, RGB(0, 0, 255));
		DrawRect(hDC, 290, 80, 60, 40, HS_VERTICAL, RGB(0, 0, 0));
		//绘制位图
		DrawBmpRect(hDC, 180, 140, 180, 100, TEXT("chenggong.bmp"));
		//绘制文本
		TextOut(hDC, 20, 220, TEXT("GDI画图输出测试程序"), 11);
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

//作坐标轴八等份图象有点大，缩小编辑器预览，即可看见区间划分形式

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
//                                                                                                                                                                                                                                                /+@@@@*`                                ,、/@@@@`****                                            **=@@^**                                                    `]@@@@,]                        *,**`,@@@\,*                                                                                                                                                                                                                                               
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
																