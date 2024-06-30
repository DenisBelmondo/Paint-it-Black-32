#include <stdio.h>
#include <windows.h>

/* variable to store the HANDLE to the hook. Don't declare it anywhere else then globally */
/* or you will get problems since every function uses this variable. */
HHOOK _hook;

/* This struct contains the data received by the hook callback. As you see in the callback function */
/* it contains the thing you will need: vkCode = virtual key code. */
KBDLLHOOKSTRUCT kbdStruct;

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

    /* Set the hook and set it to use the callback function above */
    /* WH_KEYBOARD_LL means it will set a low level keyboard hook. More information about it at MSDN. */
    /* The last 2 parameters are NULL, 0 because the callback function is in the same thread and window as the */
    /* function that sets and releases the hook. If you create a hack you will not need the callback function */
    /* in another place then your own code file anyway. Read more about it at MSDN. */
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

    /* Set the hook */
    if (SetHook()) {
        return 1;
    }

    /* Don't mind this, it is a meaningless loop to keep a console application running. */
    /* I used this to test the keyboard hook functionality. If you want to test it, keep it in ;) */

    while (GetMessage(&msg, NULL, 0, 0));
}
