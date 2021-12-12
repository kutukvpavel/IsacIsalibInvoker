#pragma once

#include "stdafx.h"

enum exit_codes
{
	EXIT_OK,
	EXIT_FAILED_TO_LOAD_LIBRARY,
	EXIT_FAILED_TO_INIT_LIBRARY,
	EXIT_FAILED_TO_SEND_CMD,
	EXIT_CMD_TIMED_OUT,
	EXIT_ABORTED,
	EXIT_UNKNOWN_ERROR,
	EXIT_PAYLOAD_ERROR
};

bool get_confirmation(const char* prompt);
exit_codes payload(_TCHAR* args[]);
bool load_lib();
bool init_lib();