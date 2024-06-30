#include <stdio.h>
#include <windows.h>

HHOOK _hook;

int SetHook(void) {
    static HMODULE dll;
    static HOOKPROC hookProc;

    dll = LoadLibrary("dark.dll");

    if (!dll) {
        MessageBox(NULL, "Could not load dark.dll.", "Paint it Black 32", MB_ICONERROR);
        return 1;
    }

    hookProc = (HOOKPROC)GetProcAddress(dll, "HookCallback");

    if (!hookProc) {
        MessageBox(NULL, "Could not get proc address.", "Paint it Black 32", MB_ICONERROR);
        return 1;
    }

    if (!(_hook = SetWindowsHookEx(WH_CALLWNDPROCRET, hookProc, dll, 0))) {
        MessageBox(NULL, "Failed to install hook!", "Paint it Black 32", MB_ICONERROR);
        return 1;
    }

    return 0;
}

void ReleaseHook(void) {
    UnhookWindowsHookEx(_hook);
}

int main(void) {
    MSG msg;

    if (SetHook()) {
        return 1;
    }

    while (GetMessage(&msg, NULL, 0, 0));
}
