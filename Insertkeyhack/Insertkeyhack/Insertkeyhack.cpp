#include <windows.h>
#include <tchar.h>
#include <vector>
#include <string>

// Global variables
const wchar_t CLASS_NAME[] = L"Sample Window Class";
const wchar_t WINDOW_TITLE[] = L"On-Screen Insert Key";

HWND hwndComboBox;
HWND hwndButton;
std::vector<HWND> windowHandles;

// Function to enumerate windows and populate the combo box
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam) {
    if (IsWindowVisible(hwnd)) {
        wchar_t windowTitle[256];
        GetWindowText(hwnd, windowTitle, sizeof(windowTitle) / sizeof(wchar_t));
        if (_tcslen(windowTitle) > 0) {
            SendMessage(hwndComboBox, CB_ADDSTRING, 0, (LPARAM)windowTitle);
            windowHandles.push_back(hwnd);
        }
    }
    return TRUE;
}

void PopulateComboBox() {
    SendMessage(hwndComboBox, CB_RESETCONTENT, 0, 0);
    windowHandles.clear();
    EnumWindows(EnumWindowsProc, 0);
}

// Function to send the Insert key to the selected window
void SendInsertKeyToWindow(HWND hwndTarget) {
    // Get the thread ID of the target window
    DWORD dwTargetThreadId = GetWindowThreadProcessId(hwndTarget, NULL);
    DWORD dwCurrentThreadId = GetCurrentThreadId();

    // Attach to the target thread
    AttachThreadInput(dwCurrentThreadId, dwTargetThreadId, TRUE);

    // Bring the target window to the foreground
    SetForegroundWindow(hwndTarget);

    // Send the Insert key
    INPUT inputs[2] = {};

    // Press the key
    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = VK_INSERT;
    inputs[0].ki.dwFlags = 0;

    // Release the key
    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = VK_INSERT;
    inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));

    // Detach from the target thread
    AttachThreadInput(dwCurrentThreadId, dwTargetThreadId, FALSE);
}

// Window procedure
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE: {
        // Create a combo box
        hwndComboBox = CreateWindow(
            L"COMBOBOX", NULL,
            CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
            50, 20, 200, 100,
            hwnd, NULL,
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
        );

        // Create a button
        hwndButton = CreateWindow(
            L"BUTTON", L"Insert",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            50, 60, 100, 50,
            hwnd, (HMENU)1,
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL
        );

        PopulateComboBox();
        return 0;
    }
    case WM_COMMAND: {
        if (LOWORD(wParam) == 1) {
            int selectedIndex = SendMessage(hwndComboBox, CB_GETCURSEL, 0, 0);
            if (selectedIndex != CB_ERR) {
                HWND hwndTarget = windowHandles[selectedIndex];
                SendInsertKeyToWindow(hwndTarget);
            }
        }
        return 0;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// Main entry point
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    // Register the window class
    if (!RegisterClass(&wc)) {
        MessageBox(NULL, L"Window Registration Failed!", L"Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Create the window
    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles
        CLASS_NAME,                     // Window class
        WINDOW_TITLE,                   // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, 300, 200,

        NULL,       // Parent window
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL) {
        MessageBox(NULL, L"Window Creation Failed!", L"Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

