#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <list>
#include <array>
#include "Button.h"
#include "Controller.h"

Button::Button() {
	CODE = "NUL";
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



void Button::execute()
{
	if (CODE == "CEL") {
		//Selection d'une cellule
	}
	else if (CODE == "SOL") {
		//Boutton "solution"
	}
	else if (CODE == "DEF") {
		//définir la valeur d'une case
		//Controller.setActiveCell(NULL);
	}
	else if (CODE == "CAN") {
		//On cancel la définition d'une cellule
	}
	else if (CODE == "SOL") {
		//Boutton "solution"
	}
	else if (CODE == "SOL") {
		//Boutton "solution"
	}
	else if (CODE == "SOL") {
		//Boutton "solution"
	}
	else{
		//code non connu, ne rien faire
	}

}


