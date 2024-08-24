// dllmain.cpp : DLL 애플리케이션의 진입점을 정의합니다.
#include "framework.h"
//===============================================================================================//
// This is a stub for the actuall functionality of the DLL.
//===============================================================================================//
#include "ReflectiveLoader.h"

// Note: REFLECTIVEDLLINJECTION_VIA_LOADREMOTELIBRARYR and REFLECTIVEDLLINJECTION_CUSTOM_DLLMAIN are
// defined in the project properties (Properties->C++->Preprocessor) so as we can specify our own 
// DllMain and use the LoadRemoteLibraryR() API to inject this DLL.



//===============================================================================================//
/*
* ReflectiveLoader 사용 방법
* hModule = LoadRemoteLibraryR(GetCurrentProcess(), lpBuffer, dwLength, NULL);
* // 상세한 사항은 inject.cpp 참고
*/
//===============================================================================================//
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD dwReason, LPVOID lpReserved)
{
	OutputDebugString(TEXT("HELLO WORLD !!!"));

	BOOL bReturnValue = TRUE;
	switch (dwReason)
	{
	case DLL_QUERY_HMODULE:
		if (lpReserved != NULL)
			*(HMODULE*)lpReserved = hAppInstance;
		break;

	case DLL_PROCESS_ATTACH:
		hAppInstance = hinstDLL;
		break;

	case DLL_PROCESS_DETACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return bReturnValue;
}