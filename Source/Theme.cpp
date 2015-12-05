
#include <SFML/Graphics.hpp>
#include "Theme.h"

//CLASSE NON UTILISEE (POUR L'INSTANT)

Theme::Theme() {
	
}

Theme::Theme(sf::Color back, sf::Color cell, sf::Color high, sf::Color button, sf::Color grid) {

	Theme::BackColor = back;
	Theme::CellColor = cell;
	Theme::HighlightColor = high;
	Theme::ButtonColor = button;
	Theme::GridColor = grid;
	
}