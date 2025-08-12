#pragma once

#include "NativeXNA/Game.hpp"

#ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN 1
#endif

#include <Windows.h>

namespace NativeXNA {

    using Win32GameWindow = GameWindow;

    static LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

}