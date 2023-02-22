#pragma once

// The interface for apps to load LoadRuntimeLib.dll and call it's functions.

#include "framework.h"
#include <string>

namespace LoadRuntimeLib {

bool LoadDll();
bool UnloadDll();

const wchar_t* GetName();

}  // namespace LoadRuntimeLib
