#include "lib.h"

HMODULE hLib = nullptr;

// signatures of functions exported by the dll
typedef const wchar_t* (*PFN_GETNAME)();
PFN_GETNAME pfnGetName;

namespace LoadRuntimeLib {

bool LoadDll() {
  hLib = ::LoadLibraryW(L"LoadRuntimeLib.dll");
  if (!hLib) {
    return false;
  }

  pfnGetName = (PFN_GETNAME)::GetProcAddress(hLib, "GetName");
  if (!pfnGetName) {
    return false;
  }

  return true;
}

bool UnloadDll() {
  if (!hLib) {
    return false;
  }

  BOOL ret = FreeLibrary(hLib);
  hLib = nullptr;
  return ret == TRUE;
}

const wchar_t* GetName() {
  return pfnGetName();
}

}
