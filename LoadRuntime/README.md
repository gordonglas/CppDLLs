# Loads a dll at runtime using LoadLibrary

The DLL is loaded via the [LoadLibrary](https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-loadlibraryw) function at runtime, then the EXE queries for the address of the DLL's `GetName` function, and calls it to get a string, which it displays in the client area of the window.

Note that the DLL is NOT loaded automatically by Windows when the EXE is launched. This is because the EXE isn't LINK'ed with the DLL's LIB file.

## Solution/Project setup details

Two projects are in the same VStudio solution:
* LoadRuntimeLib - the Dynamic Link Library project. This produces the DLL loaded at runtime by LoadRuntimeApp.
* LoadRuntimeApp - the Windows Desktop Application project. This produces the EXE that requires the DLL at runtime, but doesn't require the LIB file.

There is not really any additional setup needed, because the EXE doesn't need to be LINK'ed to the LIB file. The only requirement is that the EXE must be able to find the DLL (easiest is to have the EXE and DLL in the same folder, which is already the default output folder for both projects.)

Note that the function being called from the DLL must still be exported, else `GetProcAddress` will return nullptr.
