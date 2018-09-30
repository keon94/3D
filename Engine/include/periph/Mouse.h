/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Mouse.h																				  *
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
#include <queue>

class Mouse {
    friend class MainWindow;
public:
    class Event {
    public:
        enum class Type {
            LPress,
            LRelease,
            RPress,
            RRelease,
            WheelUp,
            WheelDown,
            Move,
            Invalid
        };
    private:
        Type type;
        bool m_leftIsPressed;
        bool m_rightIsPressed;
        int x;
        int y;
    public:
        Event()
            :
            type(Type::Invalid),
            m_leftIsPressed(false),
            m_rightIsPressed(false),
            x(0),
            y(0) {}
        Event(Type type, const Mouse& parent)
            :
            type(type),
            m_leftIsPressed(parent.m_leftIsPressed),
            m_rightIsPressed(parent.m_rightIsPressed),
            x(parent.x),
            y(parent.y) {}
        bool isValid() const {
            return type != Type::Invalid;
        }
        Type getType() const {
            return type;
        }
        std::pair<int, int> getPos() const {
            return{x,y};
        }
        int getPosX() const {
            return x;
        }
        int getPosY() const {
            return y;
        }
        bool leftIsPressed() const {
            return m_leftIsPressed;
        }
        bool rightIsPressed() const {
            return m_rightIsPressed;
        }
    };
public:
    Mouse() = default;
    Mouse(const Mouse&) = delete;
    Mouse& operator=(const Mouse&) = delete;
    std::pair<int, int> getPos() const;
    int getPosX() const;
    int getPosY() const;
    bool leftIsPressed() const;
    bool rightIsPressed() const;
    bool isInWindow() const;
    Mouse::Event read();
    bool isEmpty() const {
        return buffer.empty();
    }
    void flush();
private:
    void onMouseMove(int x, int y);
    void onMouseLeave();
    void onMouseEnter();
    void onLeftPressed(int x, int y);
    void onLeftReleased(int x, int y);
    void onRightPressed(int x, int y);
    void onRightReleased(int x, int y);
    void onWheelUp(int x, int y);
    void onWheelDown(int x, int y);
    void trimBuffer();
private:
    static constexpr unsigned int bufferSize = 4u;
    int x;
    int y;
    bool m_leftIsPressed = false;
    bool m_rightIsPressed = false;
    bool m_isInWindow = false;
    std::queue<Event> buffer;
};