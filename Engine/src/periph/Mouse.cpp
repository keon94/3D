/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Mouse.cpp																			  *
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
#include "Mouse.h"


std::pair<int, int> Mouse::getPos() const {
    return {x,y};
}

int Mouse::getPosX() const {
    return x;
}

int Mouse::getPosY() const {
    return y;
}

bool Mouse::leftIsPressed() const {
    return m_leftIsPressed;
}

bool Mouse::rightIsPressed() const {
    return m_rightIsPressed;
}

bool Mouse::isInWindow() const {
    return m_isInWindow;
}

Mouse::Event Mouse::read() {
    if (buffer.size() > 0u) {
        Mouse::Event e = buffer.front();
        buffer.pop();
        return e;
    }
    else {
        return Mouse::Event();
    }
}

void Mouse::flush() {
    buffer = std::queue<Event>();
}

void Mouse::onMouseLeave() {
    m_isInWindow = false;
}

void Mouse::onMouseEnter() {
    m_isInWindow = true;
}

void Mouse::onMouseMove(int newx, int newy) {
    x = newx;
    y = newy;

    buffer.push(Mouse::Event(Mouse::Event::Type::Move, *this));
    trimBuffer();
}

void Mouse::onLeftPressed(int x, int y) {
    m_leftIsPressed = true;

    buffer.push(Mouse::Event(Mouse::Event::Type::LPress, *this));
    trimBuffer();
}

void Mouse::onLeftReleased(int x, int y) {
    m_leftIsPressed = false;

    buffer.push(Mouse::Event(Mouse::Event::Type::LRelease, *this));
    trimBuffer();
}

void Mouse::onRightPressed(int x, int y) {
    m_rightIsPressed = true;

    buffer.push(Mouse::Event(Mouse::Event::Type::RPress, *this));
    trimBuffer();
}

void Mouse::onRightReleased(int x, int y) {
    m_rightIsPressed = false;

    buffer.push(Mouse::Event(Mouse::Event::Type::RRelease, *this));
    trimBuffer();
}

void Mouse::onWheelUp(int x, int y) {
    buffer.push(Mouse::Event(Mouse::Event::Type::WheelUp, *this));
    trimBuffer();
}

void Mouse::onWheelDown(int x, int y) {
    buffer.push(Mouse::Event(Mouse::Event::Type::WheelDown, *this));
    trimBuffer();
}

void Mouse::trimBuffer() {
    while (buffer.size() > bufferSize) {
        buffer.pop();
    }
}