#include "../framework.h"

#ifdef __cplusplus
#define EXPORT extern "C" __declspec(dllexport)
#else
#define EXPORT __declspec(dllexport)
#endif

// The maximum number of strings STRLIB will store and their lengths
#define MAX_STRINGS 256
#define MAX_LENGTH 63

// The callback function type definition uses generic strings
typedef BOOL(CALLBACK* GETSTRCB)(PCTSTR, PVOID);

EXPORT BOOL CALLBACK AddString(PCWSTR);
EXPORT BOOL CALLBACK DeleteString(PCWSTR);
EXPORT int CALLBACK GetStringsW(GETSTRCB, PVOID);
