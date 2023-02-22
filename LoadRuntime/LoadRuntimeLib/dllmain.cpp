// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <string>
#include "LoadRuntimeLib.h"

struct Data {
  std::wstring Name;
} data;

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD ul_reason_for_call,
                      LPVOID lpReserved) {
  switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH: {
      data.Name = L"LoadRuntimeLib dll";
      break;
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
      break;
  }
  return TRUE;
}

// We could return the std::wstring instead,
// but then it wouldn't be callable by c-lang.
EXPORT const wchar_t* GetName() {
  return data.Name.c_str();
}
