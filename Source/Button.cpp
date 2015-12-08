#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <list>
#include <array>
#include "Button.h"
#include "Controller.h"

Button::Button() {

}

//Constructeur complet, avec d�finition d'un texte
Button::Button(sf::Color colorFB, sf::Vector2f positionB, sf::Vector2f sizeB, sf::Font *fontT, std::string stringT, sf::Color colorT)
{
	setFillColor(colorFB);
	setPosition(positionB);
	setSize(sizeB);
	Texte = LinkedTexte(fontT, stringT, colorT);
	Centering();
	Sizing();
	Button::colorF = colorFB;
	Button::colorT = colorT;
}

sf::Text Button::LinkedTexte(sf::Font *font, std::string str, sf::Color color) {  //Retourne un texte avec ces attributs (Police, String de texte et couleur)
	sf::Text texte;
	texte.setFont(*font);
	texte.setString(str);
	texte.setCharacterSize(getSize().y*0.7);
	texte.setColor(color);

	return texte;
}

void Button::Centering() { //Centre le Texte du Boutton par rrapport au Boutton
	float x = getPosition().x; 
	float y = getPosition().y;
	float Sx = Texte.getCharacterSize()*Texte.getString().getSize() / 4.7; //Coefficients choisis par m�thode exp�rimentale, on calcule les dimensions du bloc texte.
	float Sy = Texte.getCharacterSize() / 1.6;

	x = x + getSize().x / 2 - Sx; //Position du coin sup�rieur gauche + moiti� de la taille du boutton - moiti� de la taille du bloc texte
	y = y + getSize().y / 2 - Sy;

	Texte.setPosition(x,y);

}

void Button::Sizing() { //Adapte le text � la taille du Boutton
	float Rx = 6.3; //Coefficients choisis par m�thode exp�rimentale
	float Ry = 0.6;
	float Sx = Rx * getSize().x / (Texte.getString().getSize());
	float Sy = Ry * getSize().y;

	if (Sx < Sy) {//On choisit la dimension la plus contraigniante
		Texte.setCharacterSize(Sx);//On l'assigne au Texte
	}
	else {
		Texte.setCharacterSize(Sy);
	}
}

void Button::AddHandler(std::function<void()> const &func) //On d�finit le Handler
{
	handler = func;
}

void Button::CallHandler() //Appel du Handler
{
	handler();
}

//Switche entre la couleur du texte et celle du fond
void Button::EnfonceurButton() {
	sf::Color tempColor = getFillColor();
	setFillColor(Texte.getColor());
	Texte.setColor(tempColor);
	
}

