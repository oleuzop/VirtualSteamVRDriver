#include "eventHooks.h"

#include "driverlog.h"

HHOOK hKeyboardHook;
HHOOK hMouseHook;

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* pKeyBoard = (KBDLLHOOKSTRUCT*)lParam;
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            char key = (char)pKeyBoard->vkCode;
            //DriverLog("KEY PRESS:\t%s\n", key);
            DriverLog("KEY PRESS:\n");
        }
    }
    return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
}

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        MSLLHOOKSTRUCT* pMouseStruct = (MSLLHOOKSTRUCT*)lParam;
        if (pMouseStruct != NULL) {
            switch (wParam) {
            case WM_LBUTTONDOWN:
                DriverLog("Left Button Down\n");
                break;
            case WM_RBUTTONDOWN:
                DriverLog("Right Button Down\n");
                break;
            case WM_MOUSEMOVE:
                DriverLog("Mouse move\n");
                //std::cout << "Mouse Move to (" << pMouseStruct->pt.x << ", " << pMouseStruct->pt.y << ")\n";
                break;
            }
            std::cout.flush();
        }
    }
    return CallNextHookEx(hMouseHook, nCode, wParam, lParam);
}

void SetHooks() {
    hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
    if (hKeyboardHook == NULL) {
        DriverLog("Failed to install keyboard hook!\n");
    }

    hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, NULL, 0);
    if (hMouseHook == NULL) {
        DriverLog("Failed to install mouse hook!\n");
    }
}

void Unhook() {
    UnhookWindowsHookEx(hKeyboardHook);
    UnhookWindowsHookEx(hMouseHook);
}

EvenHooks::EvenHooks() {
}

EvenHooks::~EvenHooks() {
    keepRunning_.store(false);
}

void EvenHooks::run() {

    keepRunning_.store(true);
    t_ = std::thread([&]
        {
            SetHooks();

            MSG msg;
            while (keepRunning_.load() && GetMessage(&msg, NULL, 0, 0)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }

            Unhook();

            // Post a dummy message to unblock GetMessage
            PostThreadMessage(GetCurrentThreadId(), WM_QUIT, 0, 0);
        });
}