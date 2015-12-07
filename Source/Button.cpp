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
	Centering();
	Sizing();
}

sf::Text Button::LinkedTexte(sf::Font *font, std::string str, sf::Color color) {
	sf::Text texte;
	texte.setFont(*font);
	texte.setString(str);
	texte.setCharacterSize(getSize().y*0.7);
	texte.setColor(color);

	return texte;
}

void Button::Centering() {
	float x = getPosition().x;
	float y = getPosition().y;
	float Sx = Texte.getCharacterSize()*Texte.getString().getSize() / 5;
	float Sy = Texte.getCharacterSize() / 1.6;

	x = x + getSize().x / 2 - Sx;
	y = y + getSize().y / 2 - Sy;
	Texte.setPosition(x,y);

}

void Button::Sizing() {
	float x = getSize().x;
	float y = getSize().y;
	float Rx = 6.3; //coefficients de reglage
	float Ry = 0.7;
	float Sx = Rx * getSize().y / (Texte.getString().getSize());
	float Sy = Ry * getSize().y;

	if (Sx < Sy) {
		Texte.setCharacterSize(Sx);
	}
	else {
		Texte.setCharacterSize(Sy);
	}

}

void Button::AddHandler(std::function<void()> const &func)
{
	handler = func;
}

void Button::CallHandler()
{
	handler();
}

void Button::EnfonceurButton() {
	setOutlineColor(Button::getFillColor());
	setFillColor(Button::Texte.getColor());
	Texte.setColor(Button::getOutlineColor());
}

