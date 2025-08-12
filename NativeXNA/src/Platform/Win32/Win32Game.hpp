#pragma once

#include "NativeXNA/Game.hpp"
#include "Win32Include.hpp"

namespace NativeXNA {

    using Win32GameWindow = GameWindow;

    static LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

}