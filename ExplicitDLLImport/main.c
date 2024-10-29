#include <stdio.h>
#include <Windows.h>
#include <tchar.h>
#include "errors.h"

int _tmain(DWORD argc, LPTSTR argv[])
{
	HINSTANCE sampleDLLLibrary = LoadLibrary(_T("sampleDLL.dll"));
	if (sampleDLLLibrary == NULL)
	{
		perror("Cannot load DLL");
		return CANNOT_LOAD_DLL;
	}

	FARPROC fAdd = GetProcAddress(sampleDLLLibrary, "Add");
	if (fAdd == NULL)
	{
		perror("Cannot read DLL function");
		return CANNOT_LOAD_DLL_FUNCTION;
	}
	FARPROC fSubtract = GetProcAddress(sampleDLLLibrary, "Subtract");
	if (fSubtract == NULL)
	{
		perror("Cannot read DLL function");
		return CANNOT_LOAD_DLL_FUNCTION;
	}

	int(*Add)(int, int) = (int (*)(int, int))fAdd;
	int(*Subtract)(int, int) = (int (*)(int, int))fSubtract;

	printf("%d\n%d\n", Add(5, 4), Subtract(5, 4));


	FreeLibrary(sampleDLLLibrary);
	return 0;
}