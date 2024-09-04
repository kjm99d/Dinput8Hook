// dllmain.cpp : DLL 애플리케이션의 진입점을 정의합니다.
#include "framework.h"

#include <Unknwn.h>

#ifdef DINPUT8_EXPORTS
#define DINPUT8_EXPORT __declspec(dllexport) 
#else
#define DINPUT8_EXPORT __declspec(dllimport) 
#endif

typedef HRESULT(WINAPI* FP_DirectInput8Create)(HINSTANCE, DWORD, const IID&, LPVOID*, LPUNKNOWN);
FP_DirectInput8Create g_fpDirectInput8Create = NULL;
EXTERN_C DINPUT8_EXPORT HRESULT WINAPI DirectInput8Create(HINSTANCE inst_handle, DWORD version, const IID& r_iid, LPVOID* out_wrapper, LPUNKNOWN p_unk);
VOID dinput8_Initialize();

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		dinput8_Initialize();
		break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

HRESULT WINAPI DirectInput8Create(HINSTANCE inst_handle, DWORD version, const IID& r_iid, LPVOID* out_wrapper, LPUNKNOWN p_unk)
{
	if (g_fpDirectInput8Create)
	{
		return g_fpDirectInput8Create(inst_handle, version, r_iid, out_wrapper, p_unk);
	}

	return S_OK;
}

VOID dinput8_Initialize()
{
	CHAR szSystemPath[MAX_PATH] = { 0, };
	HMODULE hModule = NULL;

	if (NULL == g_fpDirectInput8Create)
	{
		GetSystemDirectoryA(szSystemPath, MAX_PATH);
		StringCchCatA(szSystemPath, _countof(szSystemPath), "\\dinput8.dll");
		hModule = LoadLibraryA(szSystemPath);

		if (hModule > (HMODULE)31)
		{
			g_fpDirectInput8Create = (FP_DirectInput8Create)GetProcAddress(hModule, "DirectInput8Create");
		}
	}
}