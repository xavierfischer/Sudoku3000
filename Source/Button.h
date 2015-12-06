#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Controller.h"
#include <stdio.h>


class Button : public sf::RectangleShape
{
public:

	
	void setAction(void(*ActionPtr)(int i, int j, int* activeCell));
	void callAction();
	void execute();
	Button(int I, int J, sf::Color color);
	Button(std::string code, sf::Color color);
	Button();
	Button(sf::Color colorFB,
		sf::Vector2f positionB,
		sf::Vector2f sizeB,
		sf::Font *fontT,
		std::string stringT,
		sf::Color colorT);
	std::string CODE;
	int i;
	int j;
	sf::Text Texte;
	sf::Text LinkedTexte(sf::Font *font, std::string str, sf::Color color);
	sf::Vector2f Centering(sf::Text text);
private:
	void(*fcnPtr)(int i, int j, int* activeCell);


};
