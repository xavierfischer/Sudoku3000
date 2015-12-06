#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <list>
#include <array>
#include "Button.h"
#include "Controller.h"

Button::Button() {

}



Button::Button(sf::Color colorFB, sf::Vector2f positionB, sf::Vector2f sizeB, sf::Font *fontT, std::string stringT, sf::Color colorT)
{
	setFillColor(colorFB);
	setPosition(positionB);
	setSize(sizeB);
	Texte = LinkedTexte(fontT, stringT, colorT);
	
}

sf::Text Button::LinkedTexte(sf::Font *font, std::string str, sf::Color color) {
	sf::Text texte;
	texte.setFont(*font);
	texte.setString(str);
	texte.setCharacterSize(getSize().y*0.7);
	texte.setColor(color);
	texte.setPosition(Button::Centering(texte));
	return texte;
}

sf::Vector2f Button::Centering(sf::Text text) {
	float x = getPosition().x;
	float y = getPosition().y;
	float Sx = text.getCharacterSize()*text.getString().getSize() / 5;
	float Sy = text.getCharacterSize() / 1.6;

	x = x + getSize().x / 2 - Sx;
	y = y + getSize().y / 2 - Sy;
	return sf::Vector2f(x, y);

}

Button::Button(int I, int J, sf::Color color)
{
	CODE = "CEL";
	i = I;
	j = J;
	setFillColor(color);
}

Button::Button(std::string code, sf::Color color)
{
	CODE = code;
	i = 0;
	j = 0;
	setFillColor(color);

}
void Button::AddHandler(std::function<void()> const &func)
{
	handler = func;
}

void Button::CallHandler()
{
	handler();
}



void Button::execute()
{
	if (CODE.compare("CEL") ==0 ) {
		std::cout << "Bite" << std::endl;
		//ContainingController.ActiveCell[0] = 1;
		//ContainingController.ActiveCell[1] = i;
		//ContainingController.ActiveCell[2] = j;
	}
	else if (CODE.compare("SOL") != 0) {
		//Boutton "solution"
	}
	else if (CODE.compare("VAL") != 0) {
		//définir la valeur d'une case
		//Controller.setActiveCell(NULL);
	}
	else if (CODE.compare("CAN") != 0) {
		//On cancel la définition d'une cellule
	}
	else{
		//code non connu, ne rien faire
	}

}


