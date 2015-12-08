#ifndef __Sudoku__BUTTON
#define __Sudoku__BUTTON

#include <SFML/Graphics.hpp>
#include <string>
#include "Controller.h"
#include <stdio.h>

//La class Button d�finit un Rectangle associ� � un texte et une action,
//la plupart du temps, c'est pour etre cliqu�

class Button : public sf::RectangleShape
{
public:

	
	void AddHandler(std::function<void()> const &func); //Ajouter la fonction de d�finition de l'action associ�e
	void CallHandler(); //Appel de l'action ainsi d�finie

	Button();
	Button(//Constructeur complet, avec d�finition d'un texte
		sf::Color colorFB, //Couleur du boutton
		sf::Vector2f positionB, //Position du rectangle
		sf::Vector2f sizeB, //Taille du boutton
		sf::Font *fontT, //Police de caracteres du texte
		std::string stringT, //Texte
		sf::Color colorT); //Couleur du Texte

	sf::Color colorF; //Couleur de fond du boutton (stock�e pour activation/d�sactivation d'un boutton)
	sf::Color colorT; //Couleur de texte (idem)
	void EnfonceurButton(); //Switche entre la couleur du texte et celle du fond
	sf::Text Texte; //Texte du boutton
	sf::Text LinkedTexte(sf::Font *font, std::string str, sf::Color color); //Retourne un texte avec ces attributs (Police, String de texte et couleur)
	void Centering(); //Centre le Texte du Boutton par rrapport au Boutton
	void Sizing(); //Adapte le text � la taille du Boutton

private:
	std::function<void()> handler; //Action du boutton



};
#endif