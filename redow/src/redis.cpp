#include <WinSock2.h>
#include "redis.h"

const char RedisSaveCommand[] = "SAVE\r\n";

BOOL RedisSave() {
	WSADATA wsad;
	WSAStartup(MAKEWORD(2, 2), &wsad);

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(6379);
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	int flag = connect(client, (sockaddr*)&addr, sizeof(addr));
	if (flag < 0) {
		return flag;
	}

	send(client, RedisSaveCommand, sizeof(RedisSaveCommand), 0);
	char buffer[128];
	ZeroMemory(buffer, sizeof(buffer));
	int rc = recv(client, buffer, sizeof(buffer), 0);
	if (rc > 0) {
		OutputDebugStringW(L"Redis Save Result:");
		OutputDebugStringA(buffer);
	}

	closesocket(client);
	WSACleanup();
	return TRUE;
}