/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Keyboard.h																			  *
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
#pragma once
#include <queue>
#include <bitset>

class Keyboard {
    friend class MainWindow;
public:
    class Event {
    public:
        enum class Type {
            Press,
            Release,
            Invalid
        };
    private:
        Type type;
        unsigned char code;
    public:
        Event()
            :
            type(Type::Invalid),
            code(0u) {}
        Event(Type type, unsigned char code)
            :
            type(type),
            code(code) {}
        bool isPress() const {
            return type == Type::Press;
        }
        bool isRelease() const {
            return type == Type::Release;
        }
        bool isValid() const {
            return type != Type::Invalid;
        }
        unsigned char getCode() const {
            return code;
        }
    };
public:
    Keyboard() = default;
    Keyboard(const Keyboard&) = delete;
    Keyboard& operator=(const Keyboard&) = delete;
    bool keyIsPressed(unsigned char keycode) const;
    Event readKey();
    bool keyIsEmpty() const;
    char readChar();
    bool charIsEmpty() const;
    void flushKey();
    void flushChar();
    void flush();
    void enableAutorepeat();
    void disableAutorepeat();
    bool autorepeatIsEnabled() const;
private:
    void onKeyPressed(unsigned char keycode);
    void onKeyReleased(unsigned char keycode);
    void onChar(char character);
    void clearState();
    template<typename T>
    void trimBuffer(std::queue<T>& buffer);
private:
    static constexpr unsigned int nKeys = 256u;
    static constexpr unsigned int bufferSize = 4u;
    bool autorepeatEnabled = false;
    std::bitset<nKeys> keystates;
    std::queue<Event> keybuffer;
    std::queue<char> charbuffer;
};
