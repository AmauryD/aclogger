#if defined(_WIN32)
#include <Windows.h>
BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
#define RVEXTENSION __declspec(dllexport) void __stdcall RVExtension(char *output, int outputSize, const char *function)
#else
#define RVEXTENSION void RVExtension(char *output, int outputSize, const char *function)
#endif

#define R_FUNCTION 0
#define R_FILE 1
#define R_CONTENT 2

#include <iostream>
#include <cstring>
#include "Logger.h"
#include "arma3_request.h"

extern "C"
{
   RVEXTENSION;
};
 
using namespace std;

RVEXTENSION
{
	Arma3_request request(function);
	Logger logger;

    outputSize -= 1;
	string A3return("nil");
	string request_function = request.getElement(R_FUNCTION);
	string request_file = request.getElement(R_FILE);
	string request_content = request.getElement(R_CONTENT);

	if (request_function == "version")
        A3return = "1.1";

	if (request_function == "append")
    {
		logger.setFile(request_file);

		if(logger.append(request_content))
            A3return = "true";
		else
			A3return = "false";
    }
	if (request_function == "clear")
    {
		logger.setFile(request_file);
		if(logger.clear())
           A3return = "true";
		else
		   A3return = "false";
    }
	if (request_function == "removeFile")
	{
		logger.setFile(request_file);
		if (logger.removeFile())
			A3return = "true";
		else
			A3return = "false";
	}
	if (request_function == "write")
    {
		logger.setFile(request_file);

		if (logger.write(request_content))
            A3return = "true";
		else
			A3return = "false";
    }
	if (request_function == "log")
	{
		logger.setFile(request_file);
				
		if (logger.log(request_content))
			A3return = "true";
		else
			A3return = "false";
    }
    strncpy(output,A3return.c_str(),outputSize);
    return;
}