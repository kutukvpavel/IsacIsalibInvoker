#include "stdafx.h"
#include "Globals.h"
#include "LibraryProviders.h"

exit_codes manual_steps()
{
	exit_codes res;
	if (get_confirmation("Press Y to reload FILLAV.TAB..."))
	{
		if (res = send_ctasto(CTASTO_REINIT_CUSTOM_MEM)) return res;
	}
	if (get_confirmation("Press Y to RESET the CNC..."))
	{
		if (res = send_ctasto(CTASTO_RESET)) return res;
	}
	if (get_confirmation("Press Y to START current part-program..."))
	{
		if (res = send_ctasto(CTASTO_START)) return res;
	}
	if (get_confirmation("Press Y to HOLD current part-program..."))
	{
		if (res = send_ctasto(CTASTO_HOLD)) return res;
	}
	return EXIT_OK;
}

exit_codes payload(int argc, char* args[])
{
	exit_codes res;
	if (argc > 0)
	{
		if (args[0][0] == 'm')
		{
			res = manual_steps();
		}
		else
		{
			res = send_ctasto(static_cast<cnc_ctasto_keys>(atoi(args[0])), argc > 1 ? args[1] : NULL);
		}
	}
	else
	{
		std::cout << "Enter 'CTASTO_KEY_INT [CTASTO_PARAM_STR]': ";
		unsigned int key;
		char param[16];
		int input = scanf_s("%u %s", &key, param, sizeof(param));
		if (input > 0)
		{
			res = send_ctasto(static_cast<cnc_ctasto_keys>(key), input > 1 ? param : NULL);
		}
		else
		{
			res = EXIT_WRONG_USER_INPUT;
		}
	}
	return res;
}