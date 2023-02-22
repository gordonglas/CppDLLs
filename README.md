# Windows C++ DLL related projects for learning/testing

This repo contains various Visual Studio 2022 solutions that demonstrate DLL related usage for Windows in C/C++.  
My intention is to learn how to create a simple plugin system for my game engine.  
Even though it was written in 1998, [Programming Windows, 5th Edition](https://www.charlespetzold.com/pw5/) by Charles Petzold is still a great resource for info on how DLLs work.  

## Contents

* `LoadRuntime` - Demonstrates loading a dll at runtime using the LoadLibrary function.
* `ProgWin5Book` - Parent folder for DLL projects related to Programming Windows, 5th Edition, by Charles Petzold.
    * `ProgWin5Book/EDRTEST` - EDRTEST code from the book. An EXE calls a function in a DLL to display text in the center of the window's client area.
    * `ProgWin5Book/STRPROG` - STRPROG code from the book. Demonstrates using shared memory across multiple processes within a DLL.
