/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Keyboard.cpp																		  *
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
#include "Keyboard.h"

bool Keyboard::keyIsPressed(unsigned char keycode) const {
    return keystates[keycode];
}

Keyboard::Event Keyboard::readKey() {
    if (keybuffer.size() > 0u) {
        Keyboard::Event e = keybuffer.front();
        keybuffer.pop();
        return e;
    }
    else {
        return Keyboard::Event();
    }
}

bool Keyboard::keyIsEmpty() const {
    return keybuffer.empty();
}

char Keyboard::readChar() {
    if (charbuffer.size() > 0u) {
        unsigned char charcode = charbuffer.front();
        charbuffer.pop();
        return charcode;
    }
    else {
        return 0;
    }
}

bool Keyboard::charIsEmpty() const {
    return charbuffer.empty();
}

void Keyboard::flushKey() {
    keybuffer = std::queue<Event>();
}

void Keyboard::flushChar() {
    charbuffer = std::queue<char>();
}

void Keyboard::flush() {
    flushKey();
    flushChar();
}

void Keyboard::enableAutorepeat() {
    autorepeatEnabled = true;
}

void Keyboard::disableAutorepeat() {
    autorepeatEnabled = false;
}

bool Keyboard::autorepeatIsEnabled() const {
    return autorepeatEnabled;
}

void Keyboard::onKeyPressed(unsigned char keycode) {
    keystates[keycode] = true;
    keybuffer.push(Keyboard::Event(Keyboard::Event::Type::Press, keycode));
    trimBuffer(keybuffer);
}

void Keyboard::onKeyReleased(unsigned char keycode) {
    keystates[keycode] = false;
    keybuffer.push(Keyboard::Event(Keyboard::Event::Type::Release, keycode));
    trimBuffer(keybuffer);
}

void Keyboard::onChar(char character) {
    charbuffer.push(character);
    trimBuffer(charbuffer);
}

void Keyboard::clearState() {
    keystates.reset();
}

template<typename T>
void Keyboard::trimBuffer(std::queue<T>& buffer) {
    while (buffer.size() > bufferSize) {
        buffer.pop();
    }
}

