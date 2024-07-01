#include <dwmapi.h>
#include <stdio.h>
#include <windows.h>

LRESULT HookCallback(int nCode, WPARAM wParam, LPARAM lParam) {
    CWPRETSTRUCT *args = (CWPRETSTRUCT *)lParam;

    if (nCode == HC_ACTION) {
        static BOOL myTrue = TRUE;

        if (args->message == WM_CREATE) {
            DwmSetWindowAttribute(args->hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &myTrue, sizeof myTrue);
            UpdateWindow(args->hwnd);
        }
    }

    return CallNextHookEx(NULL, nCode, wParam, lParam);
}
