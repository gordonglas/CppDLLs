# EDRTEST code from the book Programming Windows, 5th Edition

This is sample code from the book Programming Windows, 5th Edition, by Charles Petzold.  
It has been updated to work on Visual Studio 2022. Some code is a little different than the book's sample, but it accomplishes the same thing.  
That is, to have an EXE call a function in a DLL.  
This function paints GDI text in the center of the client window.  
The DLL is loaded automatically by Windows when the EXE is launched. That is, this code does NOT demonstrate the [LoadLibrary](https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-loadlibraryw) or [LoadLibraryEx](https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-loadlibraryexw) functions.  

## Solution/Project setup details

Two projects are in the same VStudio solution:
* EDRLIB - the Dynamic Link Library project. This produces the DLL and LIB files used by the EDRTEST project.
* EDRTEST - the Windows Desktop Application project. This produces the EXE that requires the DLL at runtime, and the LIB at build time.

Some additional setup was necessary in order to build:

For EDRTEST project,
* in project properties -> C/C++ -> in `Additional Include Directories`, I had to add the path to the "edrlib.h" file. This is required for the EDRTEST code to see the header.
* in project properties -> Linker -> General -> in `Additional Library Directories`, I had to add the path to the EDRLIB project's output folder, which is `$(SolutionDir)$(Platform)\$(Configuration)\`. This is required so EDRTEST can find the lib file during the LINK step of the build.
* in project properties -> Linker -> Input -> in `Additional Dependencies`, I had to add `EDRLIB.lib`. This is required so EDRTEST will use the lib file during the LINK step of the build.

* Note that the output folders in BOTH projects need to be same, so when the EXE is run, it can find the DLL in the same folder at runtime. Both output folders were the same by default.
