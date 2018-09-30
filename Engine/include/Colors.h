/******************************************************************************************
*	Chili DirectX Framework Version 16.07.20											  *
*	Colors.h																			  *
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

class Color {
public:
    unsigned int dword;
public:
    constexpr Color() : dword() {}
    constexpr Color(const Color& col)
        :
        dword(col.dword) {}
    constexpr Color(unsigned int dw)
        :
        dword(dw) {}
    constexpr Color(unsigned char x, unsigned char r, unsigned char g, unsigned char b)
        :
        dword((x << 24u) | (r << 16u) | (g << 8u) | b) {}
    constexpr Color(unsigned char r, unsigned char g, unsigned char b)
        :
        dword((r << 16u) | (g << 8u) | b) {}
    constexpr Color(Color col, unsigned char x)
        :
        Color((x << 24u) | col.dword) {}
    Color& operator =(Color color) {
        dword = color.dword;
        return *this;
    }
    constexpr unsigned char getX() const {
        return dword >> 24u;
    }
    constexpr unsigned char getA() const {
        return getX();
    }
    constexpr unsigned char getR() const {
        return (dword >> 16u) & 0xFFu;
    }
    constexpr unsigned char getG() const {
        return (dword >> 8u) & 0xFFu;
    }
    constexpr unsigned char getB() const {
        return dword & 0xFFu;
    }
    void setX(unsigned char x) {
        dword = (dword & 0xFFFFFFu) | (x << 24u);
    }
    void SetA(unsigned char a) {
        setX(a);
    }
    void setR(unsigned char r) {
        dword = (dword & 0xFF00FFFFu) | (r << 16u);
    }
    void setG(unsigned char g) {
        dword = (dword & 0xFFFF00FFu) | (g << 8u);
    }
    void setB(unsigned char b) {
        dword = (dword & 0xFFFFFF00u) | b;
    }
};

namespace Colors {
    static constexpr Color makeRGB(unsigned char r, unsigned char g, unsigned char b) {
        return (r << 16) | (g << 8) | b;
    }
    static constexpr Color White = makeRGB(255u, 255u, 255u);
    static constexpr Color Black = makeRGB(0u, 0u, 0u);
    static constexpr Color Gray = makeRGB(0x80u, 0x80u, 0x80u);
    static constexpr Color LightGray = makeRGB(0xD3u, 0xD3u, 0xD3u);
    static constexpr Color Red = makeRGB(255u, 0u, 0u);
    static constexpr Color Green = makeRGB(0u, 255u, 0u);
    static constexpr Color Blue = makeRGB(0u, 0u, 255u);
    static constexpr Color Yellow = makeRGB(255u, 255u, 0u);
    static constexpr Color Cyan = makeRGB(0u, 255u, 255u);
    static constexpr Color Magenta = makeRGB(255u, 0u, 255u);
}