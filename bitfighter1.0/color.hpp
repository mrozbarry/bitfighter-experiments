//-----------------------------------------------------------------------------------
//
// Bitfighter - A multiplayer vector graphics space game
// Based on Zap demo released for Torque Network Library by GarageGames.com
//
// Derivative work copyright (C) 2008-2009 Chris Eykamp
// Original work copyright (C) 2004 GarageGames.com, Inc.
// Other code copyright as noted
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful (and fun!),
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
//------------------------------------------------------------------------------------

#ifndef bitfighter_color_hpp
#define bitfighter_color_hpp	1

#include <SDL_types.h>
#include <string>

namespace bitfighter {

	class Color {
	public:
	   float r, g, b;

	   Color(const Color &c);
	   Color(const Color *c);

	   template<class T, class U, class V>
		  Color(T in_r, U in_g, V in_b) { r = static_cast<float>(in_r); g = static_cast<float>(in_g); b = static_cast<float>(in_b);}

	   Color(float grayScale = 1);
	   Color(double grayScale);

	   Color(Uint32 rgbInt);

	   void read(const char **argv);

	   void interp(float t, const Color &c1, const Color &c2);

	   // templates must stay in headers
	   template<class T, class U, class V>
		  void set(T in_r, U in_g, V in_b) { r = static_cast<F32>(in_r); g = static_cast<F32>(in_g); b = static_cast<F32>(in_b); }

	   void set(const Color &c);
	   void set(const std::string &s);

	   std::string toRGBString() const;
	   std::string toHexString() const;

	   Uint32 toU32() const;

	   // inlines must stay in headers
	   inline Color operator+(const Color &c) const { return Color (r + c.r, g + c.g, b + c.b); }
	   inline Color operator-(const Color &c) const { return Color (r - c.r, g - c.g, b - c.b); }
	   inline Color operator-() const { return Color(-r, -g, -b); }
	   inline Color& operator+=(const Color &c) { r += c.r; g += c.g; b += c.b; return *this; }
	   inline Color& operator-=(const Color &c) { r -= c.r; g -= c.g; b -= c.b; return *this; }

	   inline Color operator*(const float f) { return Color (r * f, g * f, b * f); }
	   inline Color& operator*=(const float f) { r *= f; g *= f; b *= f; return *this; }

	   inline bool operator==(const Color &col) const { return r == col.r && g == col.g && b == col.b; }
	   inline bool operator!=(const Color &col) const { return r != col.r || g != col.g || b != col.b; }
	};

}

#endif // bitfighter_color_hpp
