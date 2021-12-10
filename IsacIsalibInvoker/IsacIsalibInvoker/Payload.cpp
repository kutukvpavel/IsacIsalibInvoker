#include "stdafx.h"
#include "Globals.h"

exit_codes payload()
{
	try
	{
		short sent = isalib.send_cnc(CNC_CSET, 0, "ALL");
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