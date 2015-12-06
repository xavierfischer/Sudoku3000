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






static void ActiverCell(int i, int j, int* activeCell) {
	if (i >= 10) {
		activeCell[0] = 0;
	}
	else {
		activeCell[0] = 1;
		activeCell[1] = i;
		activeCell[2] = j;
	}
}

static void ChangeCell(int i, int j, int* activeCell) {
	if (i >= 10) {
		activeCell[0] = 0;
	}
	else {
		activeCell[0] = 1;
		activeCell[1] = i;
		activeCell[2] = j;
	}
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

	sf::Vector2i Position; //Position de la souris
	Grille CurrentGrille;
	std::cout << (*CurrentGrille.getCell(1, 2)).value << std::endl;
	for (int i = 0; i <= 2;++i) {
		ActiveCell[i] = 0;
	}
	
	sf::Font font;
	if (!font.loadFromFile("arial_narrow_7.ttf"))
	{
		// error... 
	}

	sf::Text Temoin;
	Temoin.setPosition(sf::Vector2f(300, 15));
	Temoin.setFont(font);
	Temoin.setString(std::to_string(Controller::CellToPosition(2,3).x)+ " " + std::to_string(Controller::CellToPosition(2, 3).y));
	Temoin.setCharacterSize(20);
	Temoin.setColor(sf::Color::Black);

	//Definition des dessin FIXES
	//Dessin grille

	

	//Grille
	Button RectGrille=Button::Button("GRI",CellColor);
	RectGrille.setSize(sf::Vector2f(274, 274));
	RectGrille.setOutlineThickness(0);
	RectGrille.setPosition(sf::Vector2f(15, 15));

	Button ButtonCell[9][9];
	void(*Activerij)();
	//Activerij = &(ActiverCell(0,0,0));
	
	//ButtonCells
	for (int i = 0; i <= 8; ++i) {
		for (int j = 0; j <= 8; ++j) {
			
			//ButtonCell[i][j].setFillColor(sf::Color::Transparent);
			//ButtonCell[i][j].setSize(sf::Vector2f(30, 30));
			/*auto f = [=]() { 
				ButtonCell[i][j].setFillColor(HighlightColor);
				ActiveCell[0] = 1;
				ActiveCell[1] = i;
				ActiveCell[2] = j;
			};
			ButtonCell[i][j].setAction(f);*/
			ButtonCell[i][j] = Button(sf::Color::Transparent,
				sf::Vector2f(CellToPosition(i, j).x, CellToPosition(i, j).y),
				sf::Vector2f(30, 30),
				&font,
				" ",
				sf::Color::Black
				);
			//ButtonCell[i][j].setPosition(CellToPosition(i, j).x, CellToPosition(i, j).y);
			//ButtonCell[i][j].Texte.setCharacterSize(15);
			//ButtonCell[i][j].Texte = ButtonCell[i][j].LinkedTexte(&font, " ", sf::Color::Black);
			//à mettre dans la boucle ! ça change !
		}
	}

	Button CancelButton = Button(
		HighlightColor, 
		sf::Vector2f(304, 183),
		sf::Vector2f(124, 40),
		&font,
		"Annuler",
		BackColor);
	/*CancelButton.setFillColor(ButtonColor);
	CancelButton.setSize(sf::Vector2f(100,30));
	CancelButton.CODE = "CAN";
	CancelButton.setPosition(sf::Vector2f(310,100));
	CancelButton.Texte=LinkedTexte(CancelButton, &font,  "Annuler", sf::Color::Black);*/
	
	Button SolveButton = Button(
		sf::Color(0,230,0,255),
		sf::Vector2f(15, 304),
		sf::Vector2f(274, 50),
		&font,
		"Solve",
		BackColor);


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
		//ButtonVal[i].setFillColor(ButtonColor);
		//ButtonVal[i].setSize(sf::Vector2f(20,20));
		//ButtonVal[i].CODE = "VAL";
		//ButtonVal[i].i = i;
		//ButtonVal[i].setPosition(sf::Vector2f(310+i*22,15));
		//ButtonVal[i].Texte = ButtonVal[i].LinkedTexte(&font, std::to_string(i), sf::Color::Black);
		//ButtonVal[i].Texte.setString(std::to_string(i));
		//ButtonVal[i].Texte.setCharacterSize(20);
		//ButtonVal[i].Texte.setColor(sf::Color::Black);
		//ButtonVal[i].Texte.setPosition(Controller::Centering(TextVal[i],ButtonVal[i]));
		
	
	
	

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
						Temoin.setString("Inbound");
						for (int i = 0; i <= 8; ++i) {
							for (int j = 0; j <= 8; ++j) {
								if (ButtonCell[i][j].getGlobalBounds().contains((float)Position.x, (float)Position.y)) {
									

									//ButtonCell[i][j].setFillColor(ButtonColor);
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
									ButtonCell[ActiveCell[1]][ActiveCell[2]].setFillColor(sf::Color::Transparent);
									ActiveCell[0] = 1;
									ActiveCell[1] = i;
									ActiveCell[2] = j;
									ButtonCell[i][j].setFillColor(HighlightColor);
								}
								
							}
						}
					}
					//Verification pour le Cancel
					else if (ActiveCell[0] == 1 & CancelButton.getGlobalBounds().contains((float)Position.x, (float)Position.y)) {
						ActiveCell[0] = 0;
						ButtonCell[ActiveCell[1]][ActiveCell[2]].setFillColor(sf::Color::Transparent);
					}
					// ButtonVal
					else if (SolveButton.getGlobalBounds().contains((float)Position.x, (float)Position.y)) {
						window.close();
					}
					else {
						for (int i = 0; i <= 9; ++i) {
							if (ButtonVal[i].getGlobalBounds().contains((float)Position.x, (float)Position.y)) {
								//action d'un buttonval
								(*CurrentGrille.getCell(ActiveCell[1], ActiveCell[2])).setValue(i);
							}
						}
					}
					
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
				if ((*CurrentGrille.getCell(i, j)).value == 0) {
					ButtonCell[i][j].Texte.setString(" ");
				}
				else {
					ButtonCell[i][j].Texte.setString(std::to_string((*CurrentGrille.getCell(i, j)).value));
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
