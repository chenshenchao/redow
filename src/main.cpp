#include <Windows.h>
#include "redow.h"

TCHAR SERVICE_NAME[] = TEXT("Redow");
SERVICE_STATUS ServiceStatus;
SERVICE_STATUS_HANDLE ServiceStatusHandle;

/// <summary>
/// 控制流程
/// </summary>
/// <param name="command"></param>
/// <returns></returns>
VOID WINAPI ServiceControl(DWORD command)
{
	OutputDebugString(TEXT("redow service control."));

	switch (command)
	{
	case SERVICE_CONTROL_PAUSE: // TODO
		RedowStopRedis();
		OutputDebugString(TEXT("redow service pause."));
		break;
	case SERVICE_CONTROL_CONTINUE: // TODO
		RedowStartRedis();
		OutputDebugString(TEXT("redow service continue."));
		break;
	case SERVICE_CONTROL_STOP:
	case SERVICE_CONTROL_SHUTDOWN:
		RedowStopRedis();
		OutputDebugString(TEXT("redow service stop."));
		ServiceStatus.dwCurrentState = SERVICE_STOPPED;
		if (!SetServiceStatus(ServiceStatusHandle, &ServiceStatus))
		{
			OutputDebugString(TEXT("redow service close failed."));
		}
		break;
	default:
		break;
	}
}

/// <summary>
/// 服务处理程序
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
VOID WINAPI ServiceProcess(DWORD argc, LPTSTR *argv)
{
	OutputDebugString(TEXT("redow service start."));

	ServiceStatus.dwServiceType = SERVICE_WIN32;
	ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_PAUSE_CONTINUE | SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
	ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
	ServiceStatus.dwWin32ExitCode = 0;
	ServiceStatus.dwCheckPoint = 0;
	ServiceStatus.dwWaitHint = 0;
	ServiceStatus.dwServiceSpecificExitCode = 0;
	ServiceStatusHandle = RegisterServiceCtrlHandler(SERVICE_NAME, &ServiceControl);

	if (ServiceStatusHandle == 0)
	{
		DWORD error = GetLastError();
		OutputDebugString(TEXT("redow service register control handler failed."));
		return;
	}

	ServiceStatus.dwCurrentState = SERVICE_RUNNING;
	if (!SetServiceStatus(ServiceStatusHandle, &ServiceStatus))
	{
		OutputDebugString(TEXT("redow service set running failed."));
		return;
	}

	RedowStartRedis();
	RedowKeepRedis();
}

/// <summary>
/// 主程序入口
/// </summary>
/// <param name="argc"></param>
/// <param name="args"></param>
/// <returns></returns>
int main(int argc, char *[])
{
	if (!RedowInit())
	{
		OutputDebugString(TEXT("redow init failed."));
	}
	OutputDebugString(TEXT("redow init."));

	// 进入服务调度
	SERVICE_TABLE_ENTRY ste[2];
	ste[0].lpServiceName = SERVICE_NAME;
	ste[0].lpServiceProc = ServiceProcess;
	ste[1].lpServiceName = NULL;
	ste[1].lpServiceProc = NULL;
	StartServiceCtrlDispatcher(ste);
	return 0;
}