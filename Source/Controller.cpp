#include "Controller.h"
#include <SFML/Graphics.hpp>
#include <string>
#include "Button.h"
#include <iostream>
#include <list>
#include <array>
#include <SFML/Window.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>



Controller::Controller()
{
	
	
}

int * Controller::CellToPosition(int i, int j)
{
	int P[2];
	

	P[0] = 15 + i * 30 + (i % 3) * 2;// 15 pour la marge, i*30 pour la position de la cellule, décalée de 2 pixels à chaque fois qu'on passe dans la région suivante
	P[1] = 15 + j * 30 + (j % 3) * 2; //idem
	return P;
}



void Controller::run(){
	sf::RenderWindow window(sf::VideoMode(600, 450), "SudokuSolver", sf::Style::Close);
	//Couleurs
	sf::Color CellColor = sf::Color(220, 220, 220, 255);
	sf::Color GridColor= sf::Color(170, 170, 170, 255);
	sf::Color BackColor= sf::Color(70, 70, 70, 255);
	sf::Color HighlightColor = sf::Color(37, 190, 177, 255);
	sf::Color ButtonColor = sf::Color(255, 127, 102, 255);

	

	sf::Font font;
	if (!font.loadFromFile("arial_narrow_7.ttf"))
	{
		// error... 
	}

	//Definition des dessin FIXES
	//Dessin grille

	

	//Grille
	Button ButtonGrille=Button::Button("GRI",CellColor);
	ButtonGrille.setSize(sf::Vector2f(274, 274));
	ButtonGrille.setOutlineColor(sf::Color::Transparent);
	ButtonGrille.setOutlineThickness(0);
	ButtonGrille.setPosition(15, 15);

	Button ButtonCell[9][9]{};
	for (int i = 1; i <= 9; ++i) {
		for (int j = 1; j <= 9; ++j) {
			//ButtonCell[i][j].setFillColor(sf::Color::Transparent);
			//ButtonCell[i][j].setSize(sf::Vector2f(30, 30));
			//ButtonCell[i][j].setOutlineColor(sf::Color::Transparent);
			//ButtonCell[i][j].CODE = std::string("CEL");
			//ButtonCell[i][j].setPosition(sf::Vector2f(CellToPosition(i, j)[0], CellToPosition(i, j)[1]));
		}
	}


	//grille par dessus le reste
	sf::RectangleShape Glinev1;
	Glinev1.setSize(sf::Vector2f(3, 274));
	Glinev1.setOutlineColor(sf::Color::Transparent);
	Glinev1.setOutlineThickness(0);
	Glinev1.setPosition(105, 15);
	Glinev1.setFillColor(BackColor);

	sf::RectangleShape Glinev2;
	Glinev2.setSize(sf::Vector2f(3, 274));
	Glinev2.setOutlineColor(sf::Color::Transparent);
	Glinev2.setOutlineThickness(0);
	Glinev2.setPosition(197, 15);
	Glinev2.setFillColor(BackColor);

	sf::RectangleShape Glineh1;
	Glineh1.setSize(sf::Vector2f(274, 3));
	Glineh1.setOutlineColor(sf::Color::Transparent);
	Glineh1.setOutlineThickness(0);
	Glineh1.setPosition(15, 105);
	Glineh1.setFillColor(BackColor);

	sf::RectangleShape Glineh2;
	Glineh2.setSize(sf::Vector2f(274, 3));
	Glineh2.setOutlineColor(sf::Color::Transparent);
	Glineh2.setOutlineThickness(0);
	Glineh2.setPosition(15, 197);
	Glineh2.setFillColor(BackColor);


	sf::Vertex Plinev[] = //Petites Line Verticales
	{
		sf::Vertex(sf::Vector2f(45, 15),GridColor),
		sf::Vertex(sf::Vector2f(45, 289),GridColor),

		sf::Vertex(sf::Vector2f(75, 15),GridColor),
		sf::Vertex(sf::Vector2f(75, 289),GridColor),

		sf::Vertex(sf::Vector2f(137, 15),GridColor),
		sf::Vertex(sf::Vector2f(137, 289),GridColor),

		sf::Vertex(sf::Vector2f(167, 15),GridColor),
		sf::Vertex(sf::Vector2f(167, 289),GridColor),

		sf::Vertex(sf::Vector2f(229, 15),GridColor),
		sf::Vertex(sf::Vector2f(229, 289),GridColor),

		sf::Vertex(sf::Vector2f(259, 15),GridColor),
		sf::Vertex(sf::Vector2f(259, 289),GridColor),
	};
	sf::Vertex Plineh[] = //Petites Line Horizontales
	{
		sf::Vertex(sf::Vector2f(15,45),GridColor),
		sf::Vertex(sf::Vector2f(289,45),GridColor),

		sf::Vertex(sf::Vector2f(15,75),GridColor),
		sf::Vertex(sf::Vector2f(289,75),GridColor),

		sf::Vertex(sf::Vector2f(15,137),GridColor),
		sf::Vertex(sf::Vector2f(289,137),GridColor),

		sf::Vertex(sf::Vector2f(15,167),GridColor),
		sf::Vertex(sf::Vector2f(289,167),GridColor),

		sf::Vertex(sf::Vector2f(15,229),GridColor),
		sf::Vertex(sf::Vector2f(289,229),GridColor),

		sf::Vertex(sf::Vector2f(15,259),GridColor),
		sf::Vertex(sf::Vector2f(289,259),GridColor),

	};

	while (window.isOpen())
	{
		//Gestion des events
		sf::Event event;

		while (window.pollEvent(event))
		{
			// check the type of the event...
			switch (event.type)
			{
				// Si on ferme, on ferme \o/
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::MouseMoved:
				//TODO Highlights
				continue;

			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left) {
					//TODO event action
					





				}



				// Si Espace, on ferme
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Space) //espace, tapé
				{
					window.close();
					break;
				}
				else //autre key tapée
				{
					continue;
				}
			default:
				continue;
			}
		}






		//Drawing
		window.clear(BackColor);
		//window.draw(sprite);
		window.draw(ButtonGrille);

		//Mettre le highlight ici
		window.draw(Plinev, 12, sf::Lines);
		window.draw(Plineh, 12, sf::Lines);
		window.draw(Glinev1);
		window.draw(Glinev2);
		window.draw(Glineh1);
		window.draw(Glineh2);


		//window.draw(shape);

		window.display();
	}


}
