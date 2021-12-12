#pragma once

#define CNC_CMD_TIMEOUT 60000 // 1 minute
#define CONNSTAT_ALL_PRESENT (CONNSTAT_HWPRESENT | CONNSTAT_CNCPRESENT | CONNSTAT_INITDONE)

enum cnc_conn_status //Bitfield
{
	CONNSTAT_HWPRESENT = 0x01,
	CONNSTAT_CNCPRESENT = 0x02,
	CONNSTAT_INITDONE = 0x04
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

enum cnc_ctasto_keys
{
	CTASTO_REINIT_CUSTOM_MEM = 85,
	CTASTO_RESET = 155,
	CTASTO_START = 178,
	CTASTO_HOLD
};

struct isalib_interop
{
	HMODULE handle;
	void (*dispose)();
	short (*dirnav)();
	short (*send_cnc)(short cmd, short dat, char* pbuf);
	short (*test_last_cmd)();
};
typedef struct isalib_interop isalib_interop_t;

template<typename T> bool load_function(T& member, const char* name);
exit_codes send_cnc_cmd(short cmd, short data, char* pbuf);