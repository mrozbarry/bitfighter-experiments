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

#include "color.hpp"
#include "stringutils.hpp"

namespace bitfighter {

	// Constructors
	Color::Color(const Color &c)
	{
	   r = c.r;
	   g = c.g;
	   b = c.b;
	}

	Color::Color(const Color *c)
	{
	   r = c->r;
	   g = c->g;
	   b = c->b;
	}

	Color::Color(float grayScale)
	{
	   r = grayScale;
	   g = grayScale;
	   b = grayScale;
	}

	Color::Color(double grayScale)
	{
	   r = (float)grayScale;
	   g = (float)grayScale;
	   b = (float)grayScale;
	}

	Color::Color(Uint32 rgbInt)
	{
	   r = float(Uint8(rgbInt)) / 255.0f;
	   g = float(Uint8(rgbInt >> 8)) / 255.0f;
	   b = float(Uint8(rgbInt >> 16)) / 255.0f;
	};



	void Color::read(const char **argv) 
	{ 
	   r = (float) std::atof(argv[0]); 
	   g = (float) std::atof(argv[1]); 
	   b = (float) std::atof(argv[2]); 

	}

	void Color::interp(float t, const Color &c1, const Color &c2)
	{
	   float oneMinusT = 1.0f - t;
	   r = c1.r * t + c2.r * oneMinusT;
	   g = c1.g * t + c2.g * oneMinusT;
	   b = c1.b * t + c2.b * oneMinusT;
	}

	//void set(float _r, float _g, float _b) { r = _r; g = _g; b = _b; }
	void Color::set(const Color &c) { r = c.r; g = c.g; b = c.b; }
	void Color::set(const std::string &s)
	{
	   TNL::Vector<std::string> list;
	   parseString(s, list, ' ');

	   if(list.size() < 3)
		  parseString(s, list, ',');

	   if(list.size() >= 3)
	   {
		  r = (float)std::atof(list[0].c_str());
		  g = (float)std::atof(list[1].c_str());
		  b = (float)std::atof(list[2].c_str());
	   }
	}


	std::string Color::toRGBString() const 
	{ 
	   return ftos(r, 3) + " " + ftos(g, 3) + " " + ftos(b, 3); 
	}


	std::string Color::toHexString() const 
	{ 
	   char c[7]; 
	   TNL::dSprintf(c, sizeof(c), "%.6X", Uint32(r * 0xFF) << 24 >> 8 | Uint32(g * 0xFF) << 24 >> 16 | (Uint32(b * 0xFF) & 0xFF));
	   return c; 
	}


	Uint32 Color::toU32() const
	{ 
	   return Uint32(r * 0xFF) | Uint32(g * 0xFF)<<8 | Uint32(b * 0xFF)<<16; 
	}

}
