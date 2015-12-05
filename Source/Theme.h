#pragma once
#include <SFML/Graphics.hpp>

//CLASSE NON UTILISEE (POUR L'INSTANT)

class Theme {
public:
	sf::Color BackColor;
	sf::Color CellColor;
	sf::Color HighlightColor;
	sf::Color ButtonColor;
	sf::Color GridColor;

	static sf::Color LightGreyColor ;
	static sf::Color GreyColor;
	static sf::Color DarkGreyColor;
	static sf::Color TurquoiseColor;
	static sf::Color OrangeColor;

	Theme();
	Theme(sf::Color back, sf::Color cell, sf::Color high, sf::Color button, sf::Color grid);
};
