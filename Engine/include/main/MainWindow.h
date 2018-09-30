/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	MainWindow.h																		  *
*	Copyright 2016 PlanetChili <http://www.planetchili.net>								  *
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
#pragma once
#include "ChiliWin.h"
#include "Graphics.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "ChiliException.h"
#include <string>

// for granting special access to hWnd only for Graphics constructor
class HWNDKey {
    friend Graphics::Graphics(HWNDKey&);
public:
    HWNDKey(const HWNDKey&) = delete;
    HWNDKey& operator=(HWNDKey&) = delete;
protected:
    HWNDKey() = default;
protected:
    HWND hWnd = nullptr;
};

class MainWindow : public HWNDKey {
public:
    class Exception : public ChiliException {
    public:
        using ChiliException::ChiliException;
        virtual std::wstring getFullMessage() const override {
            return getNote() + L"\nAt: " + getLocation();
        }
        virtual std::wstring getExceptionType() const override {
            return L"Windows Exception";
        }
    };
public:
    MainWindow(HINSTANCE hInst, wchar_t* pArgs);
    MainWindow(const MainWindow&) = delete;
    MainWindow& operator=(const MainWindow&) = delete;
    ~MainWindow();
    bool isActive() const;
    bool isMinimized() const;
    void showMessageBox(const std::wstring& title, const std::wstring& message, UINT type = MB_OK) const;
    void kill() {
        PostQuitMessage(0);
    }
    // returns false if quitting
    bool processMessage();
    const std::wstring& GetArgs() const {
        return args;
    }
private:
    static LRESULT WINAPI _handleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    static LRESULT WINAPI _handleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    LRESULT handleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
public:
    Keyboard kbd;
    Mouse mouse;
private:
    static constexpr wchar_t* wndClassName = L"Chili DirectX Framework Window";
    HINSTANCE hInst = nullptr;
    std::wstring args;
};