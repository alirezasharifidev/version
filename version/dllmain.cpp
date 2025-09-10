#include "version.h"
#include "version.cpp"


DWORD WINAPI Load(LPVOID lpParam) {
    load_version();
    if (!version_dll)
        return 0;

    MessageBox(NULL, L"Hellow", L"My Version DLL", MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL);


    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Load, hModule, NULL, NULL);
        break;
    case DLL_PROCESS_DETACH:
        FreeLibrary(version_dll);
        break;
    }
    return TRUE;
}
