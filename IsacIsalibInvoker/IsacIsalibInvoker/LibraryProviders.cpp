#include "stdafx.h"
#include "Globals.h"
#include "LibraryProviders.h"

isalib_interop_t isalib;

void print_last_error(const char* info)
{
	printf("Last error for %s: %i\r\n", info, GetLastError());
}

template<typename T> bool load_function(T& member, const char* name)
{
	member = reinterpret_cast<T>(GetProcAddress(isalib.handle, name));
	if (!member)
	{
		std::cout << "GetProcAddress ";
		print_last_error(name);
	}
	return member != NULL;
}

bool load_lib()
{
	try
	{
		isalib.handle = LoadLibraryA("IsalibVB.dll");
		if (isalib.handle)
		{
			if (!load_function(isalib.dirnav, "dirnav")) return false;
			if (!load_function(isalib.send_cnc, "SendCnc")) return false;
			if (!load_function(isalib.test_last_cmd, "TstCmdCnc")) return false;
			if (!load_function(isalib.dispose, "Terminate")) return false;
			return true;
		}
		else
		{
			print_last_error("LoadLibraryA");
		}
	}
	catch (std::exception ex)
	{
		std::cout << ex.what() << std::endl;
	}
	return false;
}

bool init_lib()
{
	return (isalib.dirnav() & CONNSTAT_ALL_PRESENT) != CONNSTAT_ALL_PRESENT;
}

exit_codes send_cnc_cmd(short cmd, short data, char* pbuf)
{
	try
	{
		short sent = isalib.send_cnc(cmd, data, pbuf);
		if (sent) return EXIT_FAILED_TO_SEND_CMD;
		int timeout = 0;
		do
		{
			Sleep(1);
			timeout++;
			if (timeout > CNC_CMD_TIMEOUT) return EXIT_CMD_TIMED_OUT;
		} while (isalib.test_last_cmd());
		return EXIT_OK;
	}
	catch (std::exception ex)
	{
		std::cout << ex.what() << std::endl;
	}
	return EXIT_PAYLOAD_ERROR;
}

exit_codes send_ctasto(cnc_ctasto_keys key, char* pbuf)
{
	switch (key)
	{
	case CTASTO_REINIT_CUSTOM_MEM:
	case CTASTO_RESET:
	case CTASTO_START:
	case CTASTO_HOLD:
		break;
	default: throw std::exception("Thid CTASTO key is not supported.");
	}
	return send_cnc_cmd(CNC_CTASTO, key, pbuf);
}

void free_lib()
{
	isalib.dispose();
	FreeLibrary(isalib.handle);
}