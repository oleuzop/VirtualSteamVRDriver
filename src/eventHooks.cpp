#include "eventHooks.h"

#include "driverlog.h"

#define POS_FACTOR  0.001f
#define ROT_FACTOR  0.1f

HHOOK hKeyboardHook;
HHOOK hMouseHook;
float lastPoseX, lastPoseY;
Headpose pose;
bool isControlActive = false;
bool isRightButtonActive = false;


LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* pKeyBoard = (KBDLLHOOKSTRUCT*)lParam;

        switch (pKeyBoard->vkCode) {

//        case VK_RETURN:
//            std::cout << "ENTER key pressed\n";
//            break;
//        case VK_ESCAPE:
//            std::cout << "ESC key pressed\n";
//            break;
//        case 'A':
//            std::cout << "A key pressed\n";
//            break;

        case VK_LCONTROL:
            if (!isControlActive && (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)) {
                isControlActive = true;
                DriverLog("DOWN\n");
            }
            if (isControlActive && (wParam == WM_KEYUP || wParam == WM_SYSKEYUP)) {
                isControlActive = false;
                DriverLog("UP\n");
            }
            break;

        default:
            break;
        }
    }

    return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
}

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        MSLLHOOKSTRUCT* pMouseStruct = (MSLLHOOKSTRUCT*)lParam;
        if (pMouseStruct != NULL) {
            switch (wParam) {

            case WM_RBUTTONDOWN:
                isRightButtonActive = true;
                break;
            case WM_RBUTTONUP:
                isRightButtonActive = false;
                break;

            case WM_MOUSEMOVE:
                if (isControlActive) {
                    if (isRightButtonActive) {
                        pose.pos.x += float(pMouseStruct->pt.x - lastPoseX) * POS_FACTOR;
                        pose.pos.y += float(pMouseStruct->pt.y - lastPoseY) * POS_FACTOR;
                        //DriverLog("Pose move %f, %f\n", pose.pos.x, pose.pos.y);
                    }
                    else {
                        pose.angles.h += float(pMouseStruct->pt.x - lastPoseX) * ROT_FACTOR;
                        pose.angles.p += float(pMouseStruct->pt.y - lastPoseY) * ROT_FACTOR;
                        //DriverLog("Angles move %f, %f\n", pose.angles.h, pose.angles.p);
                    }
                }
                lastPoseX = float(pMouseStruct->pt.x);
                lastPoseY = float(pMouseStruct->pt.y);
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

const float EvenHooks::getPoseX() { return pose.pos.x; }
const float EvenHooks::getPoseY() { return pose.pos.y; }

const float EvenHooks::getHeading() { return -pose.angles.h; }
const float EvenHooks::getPitch() { return -pose.angles.p; }

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