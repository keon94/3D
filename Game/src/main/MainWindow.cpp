/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	MainWindow.cpp																		  *
*	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#include "main/MainWindow.h"
#include "utils/Resource.h"
#include "utils/ChiliException.h"
#include "Game.h"
#include <assert.h>

MainWindow::MainWindow(HINSTANCE hInst, wchar_t * pArgs)
    :
    args(pArgs),
    hInst(hInst) {
    // register window class
    WNDCLASSEX wc = {sizeof(WNDCLASSEX),CS_CLASSDC,_handleMsgSetup,0,0,
        hInst,nullptr,nullptr,nullptr,nullptr,
        wndClassName,nullptr};
    wc.hIconSm = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_APPICON), IMAGE_ICON, 16, 16, 0);
    wc.hIcon = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDI_APPICON), IMAGE_ICON, 32, 32, 0);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    RegisterClassEx(&wc);

    // create window & get hWnd
    RECT wr;
    wr.left = 350;
    wr.right = Graphics::ScreenWidth + wr.left;
    wr.top = 100;
    wr.bottom = Graphics::ScreenHeight + wr.top;
    AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);
    hWnd = CreateWindow(wndClassName, L"Chili DirectX Framework",
                        WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
                        wr.left, wr.top, wr.right - wr.left, wr.bottom - wr.top,
                        nullptr, nullptr, hInst, this);

    // throw exception if something went terribly wrong
    if (hWnd == nullptr) {
        throw Exception(_CRT_WIDE(__FILE__), __LINE__,
                        L"Failed to get valid window handle.");
    }

    // show and update
    ShowWindow(hWnd, SW_SHOWDEFAULT);
    UpdateWindow(hWnd);
}

MainWindow::~MainWindow() {
    // unregister window class
    UnregisterClass(wndClassName, hInst);
}

bool MainWindow::isActive() const {
    return GetActiveWindow() == hWnd;
}

bool MainWindow::isMinimized() const {
    return IsIconic(hWnd) != 0;
}

void MainWindow::showMessageBox(const std::wstring& title, const std::wstring& message, UINT type) const {
    MessageBox(hWnd, message.c_str(), title.c_str(), type);
}

bool MainWindow::processMessage() {
    MSG msg;
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        if (msg.message == WM_QUIT) {
            return false;
        }
    }
    return true;
}

LRESULT WINAPI MainWindow::_handleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    // use create parameter passed in from CreateWindow() to store window class pointer at WinAPI side
    if (msg == WM_NCCREATE) {
        // extract ptr to window class from creation data
        const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
        MainWindow* const pWnd = reinterpret_cast<MainWindow*>(pCreate->lpCreateParams);
        // sanity check
        assert(pWnd != nullptr);
        // set WinAPI-managed user data to store ptr to window class
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
        // set message proc to normal (non-setup) handler now that setup is finished
        SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&MainWindow::_handleMsgThunk));
        // forward message to window class handler
        return pWnd->handleMsg(hWnd, msg, wParam, lParam);
    }
    // if we get a message before the WM_NCCREATE message, handle with default handler
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT WINAPI MainWindow::_handleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    // retrieve ptr to window class
    MainWindow* const pWnd = reinterpret_cast<MainWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    // forward message to window class handler
    return pWnd->handleMsg(hWnd, msg, wParam, lParam);
}

LRESULT MainWindow::handleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_KILLFOCUS:
            kbd.clearState();
            break;

            // ************ KEYBOARD MESSAGES ************ //
        case WM_KEYDOWN:
            if (!(lParam & 0x40000000) || kbd.autorepeatIsEnabled()) // no thank you on the autorepeat
            {
                kbd.onKeyPressed(static_cast<unsigned char>(wParam));
            }
            break;
        case WM_KEYUP:
            kbd.onKeyReleased(static_cast<unsigned char>(wParam));
            break;
        case WM_CHAR:
            kbd.onChar(static_cast<unsigned char>(wParam));
            break;
            // ************ END KEYBOARD MESSAGES ************ //

            // ************ MOUSE MESSAGES ************ //
        case WM_MOUSEMOVE:
        {
            POINTS pt = MAKEPOINTS(lParam);
            if (pt.x > 0 && pt.x < Graphics::ScreenWidth && pt.y > 0 && pt.y < Graphics::ScreenHeight) {
                mouse.onMouseMove(pt.x, pt.y);
                if (!mouse.isInWindow()) {
                    SetCapture(hWnd);
                    mouse.onMouseEnter();
                }
            }
            else {
                if (wParam & (MK_LBUTTON | MK_RBUTTON)) {
                    pt.x = std::max(short(0), pt.x);
                    pt.x = std::min(short(Graphics::ScreenWidth - 1), pt.x);
                    pt.y = std::max(short(0), pt.y);
                    pt.y = std::min(short(Graphics::ScreenHeight - 1), pt.y);
                    mouse.onMouseMove(pt.x, pt.y);
                }
                else {
                    ReleaseCapture();
                    mouse.onMouseLeave();
                    mouse.onLeftReleased(pt.x, pt.y);
                    mouse.onRightReleased(pt.x, pt.y);
                }
            }
            break;
        }
        case WM_LBUTTONDOWN:
        {
            const POINTS pt = MAKEPOINTS(lParam);
            mouse.onLeftPressed(pt.x, pt.y);
            SetForegroundWindow(hWnd);
            break;
        }
        case WM_RBUTTONDOWN:
        {
            const POINTS pt = MAKEPOINTS(lParam);
            mouse.onRightPressed(pt.x, pt.y);
            break;
        }
        case WM_LBUTTONUP:
        {
            const POINTS pt = MAKEPOINTS(lParam);
            mouse.onLeftReleased(pt.x, pt.y);
            break;
        }
        case WM_RBUTTONUP:
        {
            const POINTS pt = MAKEPOINTS(lParam);
            mouse.onRightReleased(pt.x, pt.y);
            break;
        }
        case WM_MOUSEWHEEL:
        {
            const POINTS pt = MAKEPOINTS(lParam);
            if (GET_WHEEL_DELTA_WPARAM(wParam) > 0) {
                mouse.onWheelUp(pt.x, pt.y);
            }
            else if (GET_WHEEL_DELTA_WPARAM(wParam) < 0) {
                mouse.onWheelDown(pt.x, pt.y);
            }
            break;
        }
        // ************ END MOUSE MESSAGES ************ //
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}