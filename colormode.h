




#ifndef COLORMODE_H
#define COLORMODE_H

#include <iostream>
#include <SFML/Graphics.hpp>

namespace COLORMODE
{
	std::string type = "RGBA";
	
	sf::Color GET(sf::Color color) // CONVERTS default RGBA to the current TYPE
	{
		sf::Uint8 r,g,b,a;
		
		r = color.r;
		g = color.g;
		b = color.b;
		a = color.a;
		
		
		
		if(type == "BGRA")
		{
			return sf::Color(b,g,r,a);
		}
		
		return sf::Color(r,g,b,a);
		
	}
	
	
	
	
	
}




#endif
