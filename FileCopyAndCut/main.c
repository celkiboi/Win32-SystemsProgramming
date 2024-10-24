#include <Windows.h>
#include <tchar.h>
#include "Errors.h"
#include <stdlib.h>

BOOL Copy(HANDLE origin, HANDLE destination);

int _tmain(DWORD argc, LPTSTR argv[])
{
	if (argc < 4)
		return NOT_ENOUGH_ARGUMENTS;

	if (_tcscmp(argv[1], _T("-cut")) && _tcscmp(argv[1], _T("-copy")))
		return INVALID_OPERATION_ARGUMENT;

	_tprintf(_T("%s"), argv[2]);

	if (!_tcscmp(argv[1], _T("-copy")))
	{
		HANDLE origin = CreateFile(
			argv[2],
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		if (origin == INVALID_HANDLE_VALUE)
			return INVALID_ORIGIN_FILE_ARGUMENT;

		HANDLE destination = CreateFile(
			argv[3],
			GENERIC_WRITE,
			0,
			NULL,
			CREATE_NEW,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		if (destination == INVALID_HANDLE_VALUE)
			return INVALID_DESTINATION_FILE_ARGUMENT;

		if (!Copy(origin, destination))
			return INVALID_COPY_OPERATION;
		CloseHandle(origin);
		CloseHandle(destination);
	}
	else
	{
		HANDLE origin = CreateFile(
			argv[2],
			GENERIC_READ | GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			FILE_FLAG_DELETE_ON_CLOSE, // important difference
			NULL);
		if (origin == INVALID_HANDLE_VALUE)
			return INVALID_ORIGIN_FILE_ARGUMENT;

		HANDLE destination = CreateFile(
			argv[3],
			GENERIC_WRITE,
			0,
			NULL,
			CREATE_NEW,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		if (destination == INVALID_HANDLE_VALUE)
			return INVALID_DESTINATION_FILE_ARGUMENT;

		if (!Copy(origin, destination))
			return INVALID_CUT_OPERATION;

		CloseHandle(origin);
		CloseHandle(destination);
	}
}

#define BUFFER_SIZE 1024

BOOL Copy(HANDLE origin, HANDLE destination)
{
	BYTE buffer[BUFFER_SIZE] = { '\0' };
	DWORD numberOfBytesRead = 0;
	DWORD numberOfBytesWritten = 0;

	if (ReadFile(origin, buffer, BUFFER_SIZE, &numberOfBytesRead, NULL) && numberOfBytesRead == 0)
		return FALSE;
	do
	{
		_tprintf(_T("Doing it\n"));
		if (!WriteFile(destination, buffer, numberOfBytesRead, &numberOfBytesWritten, NULL)
			|| (numberOfBytesRead != numberOfBytesWritten))
			return FALSE;
	} while (ReadFile(origin, buffer, BUFFER_SIZE, &numberOfBytesRead, NULL) && numberOfBytesRead);

	return TRUE;
}