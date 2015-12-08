#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <list>
#include <array>
#include "Button.h"
#include "Controller.h"

Button::Button() {
}

//Constructeur complet, avec définition d'un texte
Button::Button(sf::Color colorFB, sf::Vector2f positionB, sf::Vector2f sizeB, sf::Font *fontT, std::string stringT, sf::Color colorT)
{
	setFillColor(colorFB); //Couleur de fond
	setPosition(positionB); 
	setSize(sizeB);
	Texte = LinkedTexte(fontT, stringT, colorT);
	Sizing(); //Resizer le Texte
	Centering(); //Centrer le texte
	Button::colorF = colorFB;
	Button::colorT = colorT; //Couleur de texte
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
	float Sx = Texte.getCharacterSize()*Texte.getString().getSize() / 4.7; //Coefficients choisis par méthode expérimentale, on calcule les dimensions du bloc texte.
	float Sy = Texte.getCharacterSize() / 1.6;

	x = x + getSize().x / 2 - Sx; //Position du coin supérieur gauche + moitié de la taille du boutton - moitié de la taille du bloc texte
	y = y + getSize().y / 2 - Sy;

	Texte.setPosition(x,y);

}

void Button::Sizing() { //Adapte le text à la taille du Boutton
	float Rx = 6.3; //Coefficients choisis par méthode expérimentale
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

void Button::AddHandler(std::function<void()> const &func) //On définit le Handler
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

