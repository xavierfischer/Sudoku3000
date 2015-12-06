#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <array>
#include <thread>



class Controller 

{
public:

	static Cell ActiveCell;
	Controller();
	sf::Vector2i CellToPosition(int x, int y);
	void run();
	
};

