#include <windows.h>
#include <stdio.h>
//http://www.coderonline.net/programming-windows-fourth-series-programming-with-unicode.html
#include <tchar.h>

#include <windows.h>
#include <tchar.h>
#include <stdio.h>

int _tmain(void)
{
	int nwCh;
	char AnsiStr[] = "hello, world!";
	wchar_t wszBuf[20] = {0};

	//获得转换后产生多少Unicode字符，可以作为后面实际转换时传入容纳转换结果的Unicode字符数buffer大小
	nwCh = MultiByteToWideChar(CP_ACP, 0, AnsiStr, -1, NULL, 0);
	//转换并接收结果
	MultiByteToWideChar(CP_ACP, 0, AnsiStr, -1, wszBuf, nwCh);
	wprintf(L"nwCh = %d, %s\n", nwCh, wszBuf);

	int nCh;
	char AnsiBuf[20] = {0};
	//获得转换后产生多少ANSI字符，可以作为后面实际转换时传入容纳转换结果的ANSI字符数buffer大小
	nCh = WideCharToMultiByte(CP_ACP, 0, wszBuf, -1, NULL, 0, NULL, NULL);
	//转换并接收结果
	WideCharToMultiByte(CP_ACP, 0, wszBuf, -1, AnsiBuf, nCh, NULL, NULL);
	printf("nCh = %d, %s\n", nCh, AnsiBuf);
	
	_tsystem(TEXT("pause"));
//----------------------------------------------------
	TCHAR c = TEXT('A');
	TCHAR buf[16];
	TCHAR *str1 = TEXT("hello, world!");

	_tprintf(TEXT("1 --> %c\n"), c);
	_tprintf(TEXT("2 --> %s\n"), str1);

	_tscanf(_T("%s"), buf);
	_tprintf(_T("%s\n"), buf);

	_tsystem(TEXT("pause"));

//----------------------------------------------------
	char c1 = 'A';
	char str[] = "hello, ANSI";

	wchar_t wch = L'A';
	wchar_t wstr[] = L"hello, Unicode";

	printf("1 --> %c\n", c1);
	printf("2 --> %s\n", str);

	printf("3 --> %c\n", wch);
	printf("4 --> %s\n", wstr);

	printf("5 --> %C\n", c1);
	printf("6 --> %S\n", wstr);

	wprintf(L"7 --> %c\n", wch);
	wprintf(L"8 --> %s\n\n", wstr);

	system("pause");
	return 0;
}







