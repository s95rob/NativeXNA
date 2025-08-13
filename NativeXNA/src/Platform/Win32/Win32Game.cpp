#include "Platform/Win32/Win32Game.hpp"

namespace NativeXNA {

    Win32GameWindow::GameWindow(Game* pGame, std::string_view title, int width, int height) 
        : GameChild(pGame) {
        static bool isWindowClassRegistered = false;

        WNDCLASS wc = {};
        wc.lpszClassName = "NativeXNAWindow";
        wc.hInstance = GetModuleHandle(nullptr);
        wc.lpfnWndProc = WndProc;

        if (!isWindowClassRegistered) {
            RegisterClass(&wc);
            isWindowClassRegistered = true;
        }

        m_Handle = (IntPtr)CreateWindow(wc.lpszClassName, title.data(), WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, width, height, nullptr, nullptr,
            wc.hInstance, nullptr);

        // Link the GameWindow class
        SetWindowLongPtr((HWND)m_Handle, GWLP_USERDATA, (LONG_PTR)this);

        ShowWindow((HWND)m_Handle, SW_SHOW);
    }

    Win32GameWindow::~GameWindow() {
        DestroyWindow((HWND)m_Handle);
    }

    void Win32GameWindow::SetTitle(std::string_view title) {
        SetWindowText((HWND)m_Handle, title.data());
    }

    std::string Win32GameWindow::GetTitle() const {
        std::string title;
        title.reserve(0x100);
        GetWindowText((HWND)m_Handle, title.data(), 0xff);
        return title;
    }

    Rectangle Win32GameWindow::GetClientBounds() const {
        RECT rect;
        GetClientRect((HWND)m_Handle, &rect);
        return { rect.left, rect.top, rect.right, rect.bottom };
    }

    
    LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        Win32GameWindow* gameWindow = (Win32GameWindow*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

        switch (uMsg) {
        case WM_CLOSE:
            gameWindow->Closed.Invoke();
            gameWindow->GetGame()->Exit();
            return 0;
        case WM_SIZE:
            gameWindow->ClientSizeChanged.Invoke();
            return 0;
        case WM_ACTIVATE:
            if (wParam == WA_ACTIVE || wParam == WA_CLICKACTIVE)
                gameWindow->GetGame()->Activated.Invoke();
            else
                gameWindow->GetGame()->Deactivated.Invoke();
            return 0;
        }

        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    
    namespace Platform {

        void ProcessWindowMessages(IntPtr handle) {
            MSG msg;
            while (PeekMessage(&msg, (HWND)handle, 0, 0, PM_REMOVE) > 0) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

    }

}