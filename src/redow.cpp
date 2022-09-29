#include "redow.h"
#include <Windows.h>
#include <Shlwapi.h>
#include <strsafe.h>

HANDLE pipeIn = NULL;
HANDLE pipeOut = NULL;
PROCESS_INFORMATION process = { 0 };
WCHAR RedowCommand[MAX_PATH];
CONST WCHAR RedisDir[] = L"\\bin\\";
CONST WCHAR RedisExe[] = L"redis-server.exe";
WCHAR WorkDir[MAX_PATH];

BOOL RedowInit()
{
	// 获取命令的目录;
	int count;
	PWSTR* args = CommandLineToArgvW(GetCommandLineW(), &count);
	PathRemoveFileSpecW(args[0]);
	size_t length;
	size_t rlength;
	size_t elength;
	if (
		S_OK == StringCchLengthW(args[0], MAX_PATH, &length) &&
		S_OK == StringCchLengthW(RedisDir, MAX_PATH, &rlength) &&
		S_OK == StringCchLengthW(RedisExe, MAX_PATH, &elength)
	) {
		StringCchCopyW(WorkDir, length + 1, args[0]);
		StringCchCopyW(WorkDir + length, rlength + 1, RedisDir);
		StringCchCopyW(RedowCommand, length + rlength + 1, WorkDir);
		StringCchCopyW(RedowCommand + length + rlength, elength + 1, RedisExe);
		HeapFree(GetProcessHeap(), 0, args);
		OutputDebugStringW(WorkDir);
		OutputDebugStringW(RedowCommand);
		return TRUE;
	}
	else
	{
		OutputDebugStringW(args[0]);
		OutputDebugString(TEXT("redow get workdir failed."));
		HeapFree(GetProcessHeap(), 0, args);
		return FALSE;
	}
}

void RedowClear()
{
	OutputDebugString(TEXT("redow clear start."));
	if (NULL != pipeIn)
	{
		CloseHandle(pipeIn);
		pipeIn = NULL;
		OutputDebugString(TEXT("redow close pipe in."));
	}

	if (NULL != pipeOut)
	{
		CloseHandle(pipeOut);
		pipeOut = NULL;
		OutputDebugString(TEXT("redow close pipe out."));
	}

	if (NULL != process.hThread)
	{
		CloseHandle(process.hThread);
		process.hThread = NULL;
		OutputDebugString(TEXT("redow close close thread."));
	}

	if (NULL != process.hProcess)
	{
		TerminateProcess(process.hProcess, 0);
		CloseHandle(process.hProcess);
		process.hProcess = NULL;
		OutputDebugString(TEXT("redow close close process."));
	}
	OutputDebugString(TEXT("redow clear end."));
}

void RedowStartRedis()
{
	SECURITY_ATTRIBUTES sa = { 0 };
	sa.nLength = sizeof(sa);
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = NULL;

	if (!CreatePipe(&pipeIn, &pipeOut, &sa, 0))
	{
		return RedowClear();
	}
	OutputDebugString(TEXT("redow create pipe."));

	STARTUPINFOW si = { 0 };
	si.cb = sizeof(si);
	si.hStdInput = pipeIn;
	si.hStdOutput = pipeOut;
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;

	if (!CreateProcessW(NULL, RedowCommand, NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, WorkDir, &si, &process))
	{
		TCHAR emsg[400];
		StringCchPrintf(emsg, 40, TEXT("create process error code: %d"), GetLastError());
		OutputDebugString(emsg);
		return RedowClear();
	}

	OutputDebugString(TEXT("redow create process."));
}

void RedowStopRedis()
{
	RedowClear();
}

void RedowRestarRedis()
{

}

void RedowKeepRedis()
{
	OutputDebugString(TEXT("redow keep start."));
	while (NULL != process.hProcess)
	{
		Sleep(1000);
	}
	OutputDebugString(TEXT("redow keep end."));
}