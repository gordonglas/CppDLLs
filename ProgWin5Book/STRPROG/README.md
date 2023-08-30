# STRPROG code from the book Programming Windows, 5th Edition

Solution that demonstrates shared memory in a DLL.

DLLs get their own memory space inside the process that uses them, so if multiple processes use the same DLL, the memory they work with is separate. This Visual Studio solution demonstrates using shared memory in the DLL (via a pragma linker directive), so multiple processes can work with the same memory within the DLL. You can use menu items to Enter and Delete the strings, while it automatically updates the client area of the window. Since it's shared memory, you should test by adding and deleting strings using multiple instances of the app.

This is sample code from the book Programming Windows, 5th Edition, by Charles Petzold.  
It has been updated to work on Visual Studio 2022. Some code is a little different than the book's sample, but it accomplishes the same thing.

Note: This sample doesn't use thread-safe code around the shared memory. In a real world example, you should wrap access to the shared memory with some thread-safe code, such as a mutex. This would prevent multiple processes from corrupting the shared data.

## Solution/Project setup details

Two projects are in the same VStudio solution:
* STRLIB - the Dynamic Link Library project. This produces the DLL and LIB files used by the STRPROG project. It manages up to 256 strings in shared memory, and has 3 functions to manipulate them:
    * AddString - Adds a string to the shared memory.
    * DeleteString - Deletes a string from the shared memory.
    * GetStrings - Gets the current strings in the shared memory, by passing them one at a time via a callback function.
* STRPPROG - the Windows Desktop Application project. This produces the EXE that requires the DLL at runtime, and the LIB at build time.

Some additional setup was necessary in order to build:

For STRPROG project,
* in project properties -> C/C++ -> in `Additional Include Directories`, I had to add the path to the "strlib.h" file. This is required for the STRPROG code to see the header.
* in project properties -> Linker -> General -> in `Additional Library Directories`, I had to add the path to the STRLIB project's output folder, which is `$(SolutionDir)$(Platform)\$(Configuration)\`. This is required so STRPROG can find the lib file during the LINK step of the build.
* in project properties -> Linker -> Input -> in `Additional Dependencies`, I had to add `STRLIB.lib`. This is required so STRPROG will use the lib file during the LINK step of the build.

* Note that the output folders in BOTH projects need to be same, so when the EXE is run, it can find the DLL in the same folder at runtime. Both output folders were the same by default.
