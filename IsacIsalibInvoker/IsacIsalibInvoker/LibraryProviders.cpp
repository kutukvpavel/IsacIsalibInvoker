#include "stdafx.h"
#include "Globals.h"

isalib_interop_t isalib;

bool init_lib()
{
	try
	{
		isalib.handle = LoadLibraryA("IsalibVB.dll");
		if (isalib.handle)
		{
			isalib.send_cnc = reinterpret_cast<short (*)(short, short, char*)>(GetProcAddress(isalib.handle, "SendCnc"));
			if (!isalib.send_cnc) return false;
			isalib.test_last_cmd = reinterpret_cast<short (*)()>(GetProcAddress(isalib.handle, "TestCmdCnc"));
			if (!isalib.test_last_cmd) return false;
			return true;
		}
	}
	catch (std::exception ex)
	{
		std::cout << ex.what() << std::endl;
	}
	std::cout << "Last error: " << GetLastError() << std::endl;
	return false;
}