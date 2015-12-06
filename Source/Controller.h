#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <array>
#include <thread>
#include "Cellule.h"



class Controller 

{
public:

	static sf::Vector2f Centering(sf::Text text, sf::RectangleShape Shape);
	Controller();
	sf::Vector2i CellToPosition(int x, int y);
	void run();
	int ActiveCell[3];
	
};
