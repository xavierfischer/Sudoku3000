#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <array>
#include <thread>



class Controller 

{
public:

	
	Controller();
	static int * CellToPosition(int x, int y);
	void run();
	
};
