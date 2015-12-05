#pragma once
#include <SFML/Graphics.hpp>
#include <string>


class Button : public sf::RectangleShape
{
public:

	

	void execute();
	Button(int I, int J, sf::Color color);
	Button(std::string code, sf::Color color);
	Button();
	std::string CODE;
	int i;
	int j;
	sf::Text Texte;


};
