// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <memory>
#include "inc/strlib.h"

// shared memory section (requires /SECTION:shared,RWS in link options)
#pragma data_seg("shared")
int iTotal = 0;
WCHAR szStrings[MAX_STRINGS][MAX_LENGTH + 1] = {'\0'};
#pragma data_seg()
#pragma comment(linker, "/SECTION:shared,RWS")

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD ul_reason_for_call,
                      LPVOID lpReserved) {
  switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
      break;
  }
  return TRUE;
}

EXPORT BOOL CALLBACK AddString(PCWSTR pStringIn) {
  PWSTR pString;
  int i, iLength;

  if (iTotal == MAX_STRINGS - 1)
    return FALSE;
  if ((iLength = (int)wcslen(pStringIn)) == 0)
    return FALSE;

  // Allocate memory for storing string, copy it, convert to upper case
  pString = (PWSTR)malloc(sizeof(WCHAR) * (1 + iLength));
  if (!pString)
    return FALSE;
  wcscpy(pString, pStringIn);
  _wcsupr(pString);

  // Alphabetize the strings.
  // Starts from the end, and keeps moving strings back by 1 position,
  // until it finds where it needs to go.
  for (i = iTotal; i > 0; i--) {
    if (wcscmp(pString, szStrings[i - 1]) >= 0)
      break;
    wcscpy(szStrings[i], szStrings[i - 1]);
  }
  wcscpy(szStrings[i], pString);
  iTotal++;
  free(pString);

  return TRUE;
}

EXPORT BOOL CALLBACK DeleteString(PCWSTR pStringIn) {
  int i, j;

  if (0 == wcslen(pStringIn))
    return FALSE;

  for (i = 0; i < iTotal; i++) {
    if (_wcsicmp(szStrings[i], pStringIn) == 0)
      break;
  }

  // If given string not in list, return without taking action
  if (i == iTotal)
    return FALSE;

  // Else adjust list downward
  for (j = i; j < iTotal; j++)
    wcscpy(szStrings[j], szStrings[j + 1]);
  szStrings[iTotal--][0] = '\0';

  return TRUE;
}

EXPORT int CALLBACK GetStringsW(GETSTRCB pfnGetStrCallBack, PVOID pParam) {
  BOOL bReturn;
  int i;

  for (i = 0; i < iTotal; i++) {
    bReturn = pfnGetStrCallBack(szStrings[i], pParam);
    if (bReturn == FALSE)
      return i + 1;
  }

  return iTotal;
}
