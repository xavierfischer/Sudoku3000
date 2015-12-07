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

float Button::Sizing(sf::Text text) {
	float x = getSize().x;
	float y = getSize().y;
	float Rx = 0.8; //coefficients de remplissage max vertical et horizontal
	float Ry = 0.9;
	float Sx = Ry * getSize().y / 0.4 * text.getString().getSize();
	float Sy = Ry * getSize().y;

	if (Sx < Sy) {
		return Sx;
	}
	else {
		return Sy;
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

