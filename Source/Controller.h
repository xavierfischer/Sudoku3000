#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <array>
#include <thread>
#include "Cellule.h"
#include "Button.h"
#include "Controller.h"


class Controller 

{
public:
	int ActiveCell[3];
	sf::RectangleShape HighVertical;
	sf::RectangleShape HighHorizontal ;
	sf::RectangleShape HighRegion;
	Controller();
	sf::Vector2i CellToPosition(int x, int y);
	void run();
	void Controller::PoliceDesCellules(Grille *grid);
	void MaJHighlights(int i, int j);
};
