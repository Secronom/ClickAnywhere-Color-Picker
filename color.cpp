#include <windows.h>
#include <iostream>
#include <iomanip>

LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam);
HHOOK mouseHook;

int main() {
    HINSTANCE hInstance = GetModuleHandle(NULL);
    mouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseHookProc, hInstance, 0);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(mouseHook);
    return 0;
}

LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        if (wParam == WM_LBUTTONDOWN) {
            POINT cursorPos;
            GetCursorPos(&cursorPos);

            HDC hdc = GetDC(NULL);
            COLORREF color = GetPixel(hdc, cursorPos.x, cursorPos.y);
            ReleaseDC(NULL, hdc);

            int r = GetRValue(color);
            int g = GetGValue(color);
            int b = GetBValue(color);

            // Convert RGB to hex
            std::cout << "RGB: (" << r << ", " << g << ", " << b << ")" << std::endl;
            std::cout << "Hex: #" << std::hex << std::setfill('0') << std::setw(2) << r << std::setw(2) << g << std::setw(2) << b << std::dec << std::endl;
        }
    }

    return CallNextHookEx(mouseHook, nCode, wParam, lParam);
}
