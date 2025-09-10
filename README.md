# DLL Hijacking with Proxying

This project provides a robust and reliable method for DLL hijacking using a proxying technique. This approach is designed to circumvent common security measures that can cause simple DLL forwarding to fail, ensuring that the target application runs smoothly while your code is executed.

### Why This Technique?

Many modern applications are hardened against simple DLL forwarding, which relies on the operating system's loader to redirect function calls. If a program uses specific loading flags or integrity checks, this can lead to immediate crashes.

This project solves that problem by taking manual control:

1.  It explicitly loads the legitimate `version.dll` from a secure system directory (`C:\Windows\System32`).

2.  It uses `GetProcAddress` to dynamically retrieve the memory address of each function it needs.

3.  It creates a wrapper function for each original function. When the target program calls a function, the wrapper simply forwards the call to the real function's address.

This robust process ensures that all API calls are correctly handled by the legitimate DLL, allowing the program to function as expected while your custom code executes.

### How to Use

#### 1. Configure the Project

* Open the project in Visual Studio.

* Ensure the project platform is set to either **x86** (for 32-bit targets) or **x64** (for 64-bit targets) to match the architecture of the application you want to hijack.

#### 2. Build the Project

* Build the solution in Visual Studio. This will compile the C++ code and create a DLL file (e.g., `version.dll`) in your project's `Debug` or `Release` folder.

#### 3. Deploy the DLL

* Rename the compiled DLL to match the name of the target DLL (e.g., `version.dll`).

* Place this malicious DLL in the same directory as the target executable.

#### 4. Run the Target Application

* Run the target application. Your malicious DLL should be loaded first, and your payload (`MessageBox`) will execute before the program proceeds.

### Code Overview

The core of the project is implemented in `dllmain.cpp` using a series of macros and functions to automate the proxying process.

* `load_version()`: This function is the heart of the proxy. It manually loads the real `version.dll` and resolves the addresses for all the functions you intend to proxy.

* `WRAPPER_GENFUNC(name)`: A powerful macro that automatically creates a proxy function for each required API. For 64-bit, it uses a linker directive; for 32-bit, it uses `__asm jmp` for efficient redirection.

* `Load(LPVOID lpParam)`: This function contains your payload. It is designed to be called by `DllMain` on a new thread to avoid potential deadlocks.

Feel free to customize the `Load(LPVOID lpParam)` function to include your own code or payload.

---
This project is provided for educational purposes only.