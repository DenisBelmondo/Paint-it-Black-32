#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

HHOOK _hook;

static int SetHook(void) {
    static HMODULE dll;
    static HOOKPROC hookProc;

    dll = LoadLibrary("dark" BITS ".dll");

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

static void ReleaseHook(void) {
    UnhookWindowsHookEx(_hook);
}

static void SignalHandler(int signal) {
    if (signal == SIGTERM || signal == SIGABRT || signal == SIGABRT2) {
        ReleaseHook();
    }
}

int main(void) {
    MSG msg;
    int i;

    for (i = 0; i < NSIG; i++) {
        signal(i, SignalHandler);
    }

    atexit(ReleaseHook);

    if (SetHook()) {
        return 1;
    }

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
