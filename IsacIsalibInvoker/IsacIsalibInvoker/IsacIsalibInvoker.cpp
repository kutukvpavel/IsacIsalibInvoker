// IsacIsalibInvoker.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "Globals.h"

bool get_confirmation(const char* prompt)
{
	std::cout << prompt << std::endl;
	char c = 'N';
	std::cin.get(c);
	std::cin.clear();
	std::cin.ignore(10000, '\n');
	//std::cout << std::endl;
	return (c == 'Y' || c == 'y');
}

int _tmain(int argc, _TCHAR* argv[])
{
	//if (!get_confirmation("Press Y to load the library...")) return EXIT_ABORTED;
	if (load_lib())
	{
		int res = EXIT_UNKNOWN_ERROR;
		try
		{
			//if (!get_confirmation("Press Y to init the library...")) return EXIT_ABORTED;
			if (!init_lib()) return EXIT_FAILED_TO_INIT_LIBRARY;
			//res = EXIT_ABORTED;
			/*if (get_confirmation("IsalibVB.dll has been initialized. Press Y to execute payload..."))*/ 
			res = payload(argv);
		}
		catch (std::exception ex)
		{
			std::cout << ex.what() << std::endl;
		}
		std::cout << "Payload executed. Exiting." << std::endl;
		return res;
	}
	get_confirmation("Press any key to exit...");
	return EXIT_FAILED_TO_LOAD_LIBRARY;
}