// wow64hook.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <Windows.h>

DWORD WOW32Reserved = 0;

void __stdcall sysfilter(DWORD idx)
{
	// �ڡ�wow64 �� printf ò�Ʋ���Ҫ���� �ں�
	printf("catch 0x%08X \n",idx);
}


__declspec(naked) void syshook()
{
	__asm
	{
		pushad
		pushfd
		push eax
		call sysfilter
		popfd
		popad
		push WOW32Reserved
		retn
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	__asm
	{
		mov eax, DWORD ptr fs:[0xc0]
		mov WOW32Reserved, eax
		mov eax, offset syshook
		mov DWORD ptr fs : [0xc0],eax
	}
	printf("get addr 0x%08X \n", WOW32Reserved);
	Sleep(1000);
	system("calc");
	return 0;
}
