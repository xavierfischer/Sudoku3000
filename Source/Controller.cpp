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
#include "Cellule.h"
#include "Grille.h"



Controller::Controller()
{
	
	
}

sf::Vector2i Controller::CellToPosition(int i, int j)
{
	int P[2];
	

	P[0] = 15 + i * 30 + (i / 3) * 2;// 15 pour la marge, i*30 pour la position de la cellule, décalée de 2 pixels à chaque fois qu'on passe dans la région suivante
	P[1] = 15 + j * 30 + (j / 3) * 2; //idem
	return sf::Vector2i(P[0], P[1]);
}

void Controller::run(){
	sf::RenderWindow window(sf::VideoMode(443, 450), "SudokuSolver", sf::Style::Close);
	//Couleurs
	sf::Color CellColor = sf::Color(220, 220, 220, 255);
	sf::Color GridColor= sf::Color(170, 170, 170, 255);
	sf::Color BackColor= sf::Color(70, 70, 70, 255);
	sf::Color HighlightColor = sf::Color(37, 190, 177, 255);
	sf::Color ButtonColor = sf::Color(255, 127, 102, 255);
	sf::Color GreenColor = sf::Color(45,193,109, 255);
	sf::Color TransparentGreenColor = sf::Color(45, 193, 109, 100);

	sf::Vector2i Position; //Position de la souris
	Grille CurrentGrille;
	std::cout << (*CurrentGrille.getCell(1, 2)).getValue() << std::endl;
	for (int i = 0; i <= 2;++i) {
		ActiveCell[i] = 0;
	}
	
	sf::Font font;
	if (!font.loadFromFile("arial_narrow_7.ttf"))
	{
		// error... 
	}


	//Definition des dessin FIXES
	//Dessin grille

	

	//Grille
	Button RectGrille=Button::Button(CellColor,sf::Vector2f(15,15),sf::Vector2f(274,274), &font,"" , sf::Color(255,255,255,100));
	RectGrille.setSize(sf::Vector2f(274, 274));
	RectGrille.setOutlineThickness(0);
	RectGrille.setPosition(sf::Vector2f(15, 15));

	Button ButtonCell[9][9];
	//ButtonCells
	for (int i = 0; i <= 8; ++i) {
		for (int j = 0; j <= 8; ++j) {
			//Constructeur de ButtonCells
			ButtonCell[i][j] = Button(sf::Color::Transparent,
				sf::Vector2f(CellToPosition(i, j).x, CellToPosition(i, j).y),
				sf::Vector2f(30, 30),
				&font,
				" ",
				sf::Color::Black
				);
			//Fonction du bouton
			ButtonCell[i][j].AddHandler([&, i , j ]() {
				ButtonCell[ActiveCell[1]][ActiveCell[2]].setFillColor(sf::Color::Transparent);
				ActiveCell[0] = 1;
				ActiveCell[1] = i;
				ActiveCell[2] = j;
				ButtonCell[i][j].setFillColor(HighlightColor);
			});
		}
	}

	Button CancelButton = Button(
		HighlightColor, 
		sf::Vector2f(304, 183),
		sf::Vector2f(124, 40),
		&font,
		"Annuler",
		BackColor);
	CancelButton.AddHandler([&]() {
		ActiveCell[0] = 0;
		ButtonCell[ActiveCell[1]][ActiveCell[2]].setFillColor(sf::Color::Transparent);
	});



	/*CancelButton.setFillColor(ButtonColor);
	CancelButton.setSize(sf::Vector2f(100,30));
	CancelButton.CODE = "CAN";
	CancelButton.setPosition(sf::Vector2f(310,100));
	CancelButton.Texte=LinkedTexte(CancelButton, &font,  "Annuler", sf::Color::Black);*/
	
	Button SolveButton = Button(
		GreenColor,
		sf::Vector2f(15, 304),
		sf::Vector2f(274, 50),
		&font,
		"Solve",
		BackColor);

	//Button de modification des valeurs
	Button ButtonVal[10];
	for (int i = 1; i <= 9; ++i) {
		ButtonVal[i] = Button(
			ButtonColor,
			sf::Vector2f(304 + ((i-1)%3) * 42, 15+ ((i - 1) / 3)*42),
			sf::Vector2f(40, 40),
			&font,
			std::to_string(i),
			BackColor
			);
	}
	ButtonVal[0] = Button(
		ButtonColor,
		sf::Vector2f(304 , 141),
		sf::Vector2f(124, 40),
		&font,
		"Effacer",
		BackColor
		);
	for (int i = 0; i <= 9; ++i) {
		ButtonVal[i].AddHandler([&, i]() {
			(*CurrentGrille.getCell(ActiveCell[1], ActiveCell[2])).setValue(i);
		});
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

		if (window.pollEvent(event))
		{
			// check the type of the event...
			switch (event.type)
			{
				// Si on ferme, on ferme \o/
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::MouseMoved:
				Position = sf::Mouse::getPosition();
				
				if (RectGrille.getGlobalBounds().contains((float)Position.x, (float)Position.y)) {
						for (int i = 0; i <= 8; ++i) {
							for (int j = 0; j <= 8; ++j) {
								if (ButtonCell[i][j].getGlobalBounds().contains((float)Position.x, (float)Position.y)) {
									
									//Highlights
									
								}
							}
						}
					}
				
				continue;

			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left) {
					Position = sf::Mouse::getPosition(window);
					//Verification pour ButtonCell
					if (RectGrille.getGlobalBounds().contains((float)Position.x, (float)Position.y)) {
						for (int i = 0; i <= 8; ++i) {
							for (int j = 0; j <= 8; ++j) {
								if (ButtonCell[i][j].getGlobalBounds().contains((float)Position.x, (float)Position.y)) {
									ButtonCell[i][j].CallHandler();
								}
								
							}
						}
					}
					//Verification pour le Cancel
					else if (ActiveCell[0] == 1 & CancelButton.getGlobalBounds().contains((float)Position.x, (float)Position.y)) {
						//ActiveCell[0] = 0;
						//ButtonCell[ActiveCell[1]][ActiveCell[2]].setFillColor(sf::Color::Transparent);
						CancelButton.CallHandler();
					}
					//SolveButton
					else if (SolveButton.getGlobalBounds().contains((float)Position.x, (float)Position.y)) {
						window.close();
					}
					// ButtonVal
					else {
						for (int i = 0; i <= 9; ++i) {
							if (ButtonVal[i].getGlobalBounds().contains((float)Position.x, (float)Position.y) & ActiveCell[0]==1) {
								ButtonVal[i].CallHandler();
							}
						}
					}
					
				}



				// Cas clavier
			case sf::Event::KeyPressed:
				
				switch (event.key.code) {
				/*

				//---Si espace, fermer---
				case sf::Keyboard::Space:
					window.close();
					break;*/

				//Valeurs de suppression
				case sf::Keyboard::Numpad0 :
					ButtonVal[0].CallHandler();
					break;
				case sf::Keyboard::BackSpace:
					ButtonVal[0].CallHandler();
					break;
				case sf::Keyboard::Delete:
					ButtonVal[0].CallHandler();
					break;
				//Valeurs de modification
				case sf::Keyboard::Numpad1:
					ButtonVal[1].CallHandler();
					break;
				case sf::Keyboard::Numpad2:
					ButtonVal[2].CallHandler();
					break;
				case sf::Keyboard::Numpad3:
					ButtonVal[3].CallHandler();
					break;
				case sf::Keyboard::Numpad4:
					ButtonVal[4].CallHandler();
					break;
				case sf::Keyboard::Numpad5:
					ButtonVal[5].CallHandler();
					break;
				case sf::Keyboard::Numpad6:
					ButtonVal[6].CallHandler();
					break;
				case sf::Keyboard::Numpad7:
					ButtonVal[7].CallHandler();
					break;
				case sf::Keyboard::Numpad8:
					ButtonVal[8].CallHandler();
					break;
				case sf::Keyboard::Numpad9:
					ButtonVal[9].CallHandler();
					break;

				//Selection / Déselection
				case sf::Keyboard::Return:
					if (ActiveCell[0] == 1) {
						CancelButton.CallHandler(); // On déselectionne
					}
					else {
						ButtonCell[ActiveCell[1]][ActiveCell[2]].CallHandler(); //On reselectionne la dernière
					}
						
					break;

				//Parcours avec les fleches
					
				case sf::Keyboard::Left:
					if (ActiveCell[0] == 1 & ActiveCell[1] > 0 ) { 
						//Si une cellule est active + si on n'est pas dans la colonne tout à gauche
						ButtonCell[ActiveCell[1]-1][ActiveCell[2]].CallHandler();
						break;
					}
					break;
				case sf::Keyboard::Right:
					if (ActiveCell[0] == 1 & ActiveCell[1] < 8) {
						ButtonCell[ActiveCell[1]+1][ActiveCell[2]].CallHandler();
						break;
					}
					break;
				case sf::Keyboard::Up:
					if (ActiveCell[0] == 1 & ActiveCell[2] > 0) {
						ButtonCell[ActiveCell[1]][ActiveCell[2]-1].CallHandler();
						break;
					}
						break;
				case sf::Keyboard::Down:
					if (ActiveCell[0] == 1 & ActiveCell[2] <8) {
						std::cout << "D" << std::endl;
						ButtonCell[ActiveCell[1]][ActiveCell[2]+1].CallHandler();
						break;
					}
					break;

				default:
					continue;
				}
				
			default:
				continue;
			}
		}



		/*for (int i = 0; i <= 8; ++i) {
			for (int j = 0; j <= 8; ++j) {
				if (CurrentGrille.getCell(i, j) == ActiveCell) {
					//Changer la couleur si la cellule est "active"
				}
				

			}
		}*/


		//Drawing
		window.clear(BackColor);
		
		window.draw(RectGrille);
		for (int i = 0; i <= 8; ++i) {
			for (int j = 0; j <= 8; ++j) {
				window.draw(ButtonCell[i][j]);
				if ((*CurrentGrille.getCell(i, j)).getValue() == 0) {
					ButtonCell[i][j].Texte.setString(" ");
				}
				else {
					ButtonCell[i][j].Texte.setString(std::to_string((*CurrentGrille.getCell(i, j)).getValue()));
				}
				window.draw(ButtonCell[i][j].Texte);
			}
		}
		if (ActiveCell[0] == 1) {
			window.draw(CancelButton);
			window.draw(CancelButton.Texte);
			for (int i = 0; i <= 9; ++i) {
				window.draw(ButtonVal[i]);
				window.draw(ButtonVal[i].Texte);

			}
		}
		window.draw(SolveButton);
		window.draw(SolveButton.Texte);
		//Mettre le highlight ici
		window.draw(Plinev, 12, sf::Lines);
		window.draw(Plineh, 12, sf::Lines);
		window.draw(Glinev1);
		window.draw(Glinev2);
		window.draw(Glineh1);
		window.draw(Glineh2);
		
		//window.draw(Temoin);
		


		//window.draw(shape);

		window.display();
	}


}
