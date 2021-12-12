#include "stdafx.h"
#include "Globals.h"
#include "LibraryProviders.h"

exit_codes payload(_TCHAR* args[])
{
	exit_codes res;
	if (get_confirmation("Press Y to reload FILLAV.TAB..."))
	{
		if (res = send_cnc_cmd(CNC_CTASTO, CTASTO_REINIT_CUSTOM_MEM, NULL)) return res;
	}
	if (get_confirmation("Press Y to RESET the CNC..."))
	{
		if (res = send_cnc_cmd(CNC_CTASTO, CTASTO_RESET, NULL)) return res;
	}
	if (get_confirmation("Press Y to START current part-program..."))
	{
		if (res = send_cnc_cmd(CNC_CTASTO, CTASTO_START, NULL)) return res;
	}
	if (get_confirmation("Press Y to HOLD current part-program..."))
	{
		if (res = send_cnc_cmd(CNC_CTASTO, CTASTO_HOLD, NULL)) return res;
	}
	return EXIT_OK;
}