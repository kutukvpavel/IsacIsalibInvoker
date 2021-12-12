========================================================================
    CONSOLE APPLICATION : IsacIsalibInvoker Project Overview
========================================================================

AppWizard has created this IsacIsalibInvoker application for you.

This file contains a summary of what you will find in each of the files that
make up your IsacIsalibInvoker application.


IsacIsalibInvoker.vcproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

IsacIsalibInvoker.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named IsacIsalibInvoker.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
USAGE INSTRUCTIONS:

There're 3 modes:
	- No CLI arguments, user input expected in the following format: CTASTO_KEY_INT [CTASTO_PARAMS_STR]
	- Option 'm' (lower case, no prefix): go through a predefined ("manual") sequence with confirmation for each step:
		* reload FILLAV
		* RESET CNC
		* START current part-program
		* HOLD current part-program
	- 1 [or 2] CLI arguments, corresponding to CTASTO_KEY_INT [and CTASTO_PARAM_STR]
