// IsacIsalibInvoker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define CNC_CMD_TIMEOUT 60000 //mS, ~1min

enum exit_codes
{
	EXIT_OK,
	EXIT_FAILED_TO_INIT_LIBRARY,
	EXIT_FAILED_TO_SEND_CMD,
	EXIT_CMD_TIMED_OUT
};

enum cnc_cmds
{
	CNC_CNUL,
	CNC_CMEN,
	CNC_CSET, //zero axes
	CNC_CORG,
	CNC_CSPP,
	CNC_CSME,
	CNC_CCMAN,
	CNC_CTASTO, //send keystroke
	CNC_CORGM,
	CNC_CINSO,
	CNC_CTASTODK = 13
};

struct isalib_interop_t
{
	HMODULE handle;
	short (*send_cnc)(short cmd, short dat, char* pbuf);
	short (*test_last_cmd)();
} isalibvb;

bool init_lib()
{
	isalibvb.handle = LoadLibraryA("IsalibVB.dll");
	if (isalibvb.handle)
	{
		isalibvb.send_cnc = reinterpret_cast<short (*)(short, short, char*)>(GetProcAddress(isalibvb.handle, "SendCnc"));
		if (!isalibvb.send_cnc) return false;
		isalibvb.test_last_cmd = reinterpret_cast<short (*)()>(GetProcAddress(isalibvb.handle, "TestCmdCnc"));
		if (!isalibvb.test_last_cmd) return false;
		return true;
	}
	printf("Last error: %i", GetLastError());
	return false;
}

exit_codes payload()
{
	short sent = isalibvb.send_cnc(CNC_CSET, 0, "ALL");
	if (sent) return EXIT_FAILED_TO_SEND_CMD;
	int timeout = 0;
	do
	{
		Sleep(1);
		timeout++;
		if (timeout > CNC_CMD_TIMEOUT) return EXIT_CMD_TIMED_OUT;
	} while (isalibvb.test_last_cmd());
	return EXIT_OK;
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (init_lib())
	{
		int res = payload();
		FreeLibrary(isalibvb.handle);
		return res;
	}
	return EXIT_FAILED_TO_INIT_LIBRARY;
}