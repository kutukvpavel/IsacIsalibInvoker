#pragma once

#include "stdafx.h"

#define CNC_CMD_TIMEOUT 60000 //mS, ~1min
#define CONNSTAT_ALL_PRESENT (CONNSTAT_HWPRESENT | CONNSTAT_CNCPRESENT | CONNSTAT_INITDONE)

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

enum cnc_conn_status //Bitfield
{
	CONNSTAT_HWPRESENT = 0x01,
	CONNSTAT_CNCPRESENT = 0x02,
	CONNSTAT_INITDONE = 0x04
};

struct isalib_interop_t
{
	HMODULE handle;
	short (*dirnav)();
	short (*send_cnc)(short cmd, short dat, char* pbuf);
	short (*test_last_cmd)();
};
extern isalib_interop_t isalib;

bool get_confirmation(const char* prompt);
exit_codes payload();
bool init_lib();