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
	

	P[0] = 15 + i * 30 + (i / 3) * 2;// 15 pour la marge, i*30 pour la position de la cellule, d�cal�e de 2 pixels � chaque fois qu'on passe dans la r�gion suivante
	P[1] = 15 + j * 30 + (j / 3) * 2; //idem
	return sf::Vector2i(P[0], P[1]);
}

void Controller::MaJHighlights(int i , int j) {
	
	HighHorizontal.setPosition(sf::Vector2f(15, CellToPosition(i, j).y));
	HighVertical.setPosition(sf::Vector2f(CellToPosition(i, j).x, 15));
	HighRegion.setPosition(sf::Vector2f(CellToPosition(3 * (i / 3), 0).x, CellToPosition(0, 3 * (j / 3)).y));
}

/*

void Controller::PoliceDesCellules(Grille *grid)

{
	list<list<int>> Errors=grid.getUnconsistentCells(int i, int j) { ... } Errors = grid.getUnconsistentCells(ActiveCell[1], ActiveCell[2]);

	for (std::list<int[2]>::iterator it = Errors.begin(); it != Errors.end(); it++) {
		//Pour ==0 {

	}

	}

}
*/

void Controller::run(){
	sf::RenderWindow window(sf::VideoMode(419, 419), "SudokuSolver", sf::Style::Close);
	//Couleurs
	sf::Color CellColor = sf::Color(220, 220, 220, 255);
	sf::Color GridColor= sf::Color(170, 170, 170, 255);
	sf::Color BackColor= sf::Color(70, 70, 70, 255);
	sf::Color HighlightColor = sf::Color(37, 190, 177, 100);
	sf::Color HighlightBorderColor = sf::Color(10,178,255, 255);
	sf::Color CancelColor = sf::Color(37, 190, 177, 255);
	sf::Color ButtonColor = sf::Color(255, 127, 102, 255);
	sf::Color GreenColor = sf::Color(45,193,109, 255);
	sf::Color TransparentGreenColor = sf::Color(45, 193, 109, 100);

	sf::Vector2i Position; //Position de la souris
	Grille CurrentGrille = Grille::createTemplateMissing();
	std::cout << (*CurrentGrille.getCell(1, 2)).getValue() << std::endl;
	
	//Elements de controles
	ActiveCell[0] = 0;
	ActiveCell[1] = 4;
	ActiveCell[2] = 4;

	bool HighlightsGrid = false;
	bool HighlightsTheme = true;
	bool ConsistencyHelp = false;
	bool ValuesHelp = false;
	
	sf::Font font;
	if (!font.loadFromFile("arial_narrow_7.ttf"))
	{
		// error... 
	}


	//______Definition des dessin FIXES____

	//---Grille
	Button RectGrille=Button::Button(CellColor,sf::Vector2f(15,15),sf::Vector2f(273,273), &font,"" , sf::Color(255,255,255,100));

	//---ButtonCells
	Button ButtonCell[9][9];
	for (int i = 0; i <= 8; ++i) {
		for (int j = 0; j <= 8; ++j) {
			//Constructeur de ButtonCells
			ButtonCell[i][j] = Button(sf::Color::Transparent,
				sf::Vector2f(CellToPosition(i, j).x+1, CellToPosition(i, j).y+1),
				sf::Vector2f(27, 27),
				&font,
				" ",
				sf::Color::Black
				);
			ButtonCell[i][j].setOutlineColor(sf::Color::White);
			//Fonction du bouton
			ButtonCell[i][j].AddHandler([&, i , j ]() {
				ButtonCell[ActiveCell[1]][ActiveCell[2]].setFillColor(sf::Color::Transparent);
				ButtonCell[ActiveCell[1]][ActiveCell[2]].setOutlineThickness(0);
				ActiveCell[0] = 1;
				ActiveCell[1] = i;
				ActiveCell[2] = j;
				ButtonCell[i][j].setFillColor(CancelColor);
				ButtonCell[i][j].setOutlineThickness(1);
				MaJHighlights(i, j);
				HighlightsGrid = true;
			});
		}
	}

	//---CancelButton
	Button CancelButton = Button(
		CancelColor, 
		sf::Vector2f(304, 151),
		sf::Vector2f(100,32),
		&font,
		"Annuler",
		BackColor);
	//-Fonction Cancel
	CancelButton.AddHandler([&]() {
		ActiveCell[0] = 0;
		ButtonCell[ActiveCell[1]][ActiveCell[2]].setFillColor(sf::Color::Transparent);
		ButtonCell[ActiveCell[1]][ActiveCell[2]].setOutlineThickness(0);
		if ( ! (RectGrille.getGlobalBounds().contains((float)Position.x, (float)Position.y))) {
			HighlightsGrid = false;
		}
		else { //On selectionne celle sous la souris
			for (int i = 0; i <= 8; ++i) {
				for (int j = 0; j <= 8; ++j) {
					if (ButtonCell[i][j].getGlobalBounds().contains((float)Position.x, (float)Position.y)) {
						MaJHighlights(i, j);
						HighlightsGrid = true;
					}
				}
			}
			
		}
	});
	
	//---SolveButton
	Button SolveButton = Button(
		GreenColor,
		sf::Vector2f(15, 294),
		sf::Vector2f(135, 50),
		&font,
		"Solve",
		BackColor);

	//---HintButton
	Button HintButton = Button(
		GreenColor,
		sf::Vector2f(153, 294),
		sf::Vector2f(135, 50),
		&font,
		"Hint",
		BackColor);

	//---Help Menu
	Button HelpMenu = Button(
		sf::Color::Cyan,
		sf::Vector2f(304, 188),
		sf::Vector2f(100, 32),
		&font,
		"Aide",
		BackColor);
	HelpMenu.setOutlineThickness(2);
	HelpMenu.setOutlineColor(sf::Color::Cyan);
	HelpMenu.setOutlineColor(BackColor);

	//---ConsistencyHelpButton
	Button CHelpButton = Button(
		sf::Color::Cyan,
		sf::Vector2f(304, 222),
		sf::Vector2f(100, 32),
		&font,
		"Aide (off)",
		BackColor);
	CHelpButton.setOutlineThickness(2);
	CHelpButton.setOutlineColor(BackColor);

	CHelpButton.AddHandler([&]() {
		if (ConsistencyHelp) {
			ConsistencyHelp = false;
			CHelpButton.Texte.setString("Aide (off)");
			CHelpButton.Texte.setPosition(CHelpButton.Centering(CHelpButton.Texte));
		}
		else {
			ConsistencyHelp = true;
			CHelpButton.Texte.setString("Aide (on)");
			CHelpButton.Texte.setPosition(CHelpButton.Centering(CHelpButton.Texte));
		}
		CHelpButton.EnfonceurButton();
	});

	//---PossibleValuesHelpButton
	Button HelpValuesButton = Button(
		sf::Color::Cyan,
		sf::Vector2f(304, 256),
		sf::Vector2f(100, 32),
		&font,
		"Values (off)",
		BackColor);
	HelpValuesButton.setOutlineThickness(2);
	HelpValuesButton.setOutlineColor(BackColor);
	HelpValuesButton.AddHandler([&]() {
		if (ValuesHelp) {
			ValuesHelp = false;
			HelpValuesButton.Texte.setString("Values (off)");
			HelpValuesButton.Texte.setPosition(HelpValuesButton.Centering(HelpValuesButton.Texte));
			
		}
		else {
			ValuesHelp = true;
			HelpValuesButton.Texte.setString("Values (on)");
			HelpValuesButton.Texte.setPosition(HelpValuesButton.Centering(HelpValuesButton.Texte));
			if (ActiveCell[0] == 1) {
				//PoliceDesCellules(&CurrentGrille);
				
			}
			
		}
		HelpValuesButton.EnfonceurButton();
		});
	

	//Buttons de modification des valeurs
	Button ButtonVal[10];
	//--Cr�ation boutons
	for (int i = 1; i <= 9; ++i) {
		ButtonVal[i] = Button(
			ButtonColor,
			sf::Vector2f(304 + ((i-1)%3) * 34, 15+ ((i - 1) / 3)*34),
			sf::Vector2f(32, 32),
			&font,
			std::to_string(i),
			BackColor
			);
	}
	//--Bouton "supprimer"
	ButtonVal[0] = Button(
		ButtonColor,
		sf::Vector2f(304 , 117),
		sf::Vector2f(100, 32),
		&font,
		"Effacer",
		BackColor
		);
	//--Handlers de modification
	for (int i = 0; i <= 9; ++i) {
		ButtonVal[i].AddHandler([&, i]() {
			ButtonCell[ActiveCell[1]][ActiveCell[2]].Texte.setColor(sf::Color::Black);
			(*CurrentGrille.getCell(ActiveCell[1], ActiveCell[2])).setValue(i);
			std::cout << "Bite1" << std::endl;
			if (ConsistencyHelp ) {
				std::cout << "Bite2" << std::endl;
				if(! (CurrentGrille.isCellConsistent(ActiveCell[1], ActiveCell[2])) ){
					std::cout << "Bite3" << std::endl;
					ButtonCell[ActiveCell[1]][ActiveCell[2]].Texte.setColor(sf::Color::Red);
				}
				//Test de consistence
				
			}

		});
	}

	//Highlighters
	HighVertical = Button(
		HighlightColor,
		sf::Vector2f(15, 15),
		sf::Vector2f(30, 274),
		&font,
		"",
		CellColor);
	HighHorizontal = Button(
		HighlightColor,
		sf::Vector2f(15, 15),
		sf::Vector2f(274,30),
		&font,
		"",
		CellColor);
	HighRegion = Button(
		HighlightColor,
		sf::Vector2f(15, 15),
		sf::Vector2f(90,90),
		&font,
		"",
		CellColor);



	//---Structure de Grille par dessus le reste
	//--Grosses lignes
	sf::RectangleShape Glinev1;
	Glinev1.setSize(sf::Vector2f(3, 274));
	Glinev1.setOutlineColor(sf::Color::Transparent);
	Glinev1.setOutlineThickness(0);
	Glinev1.setPosition(104, 15);
	Glinev1.setFillColor(BackColor);

	sf::RectangleShape Glinev2;
	Glinev2.setSize(sf::Vector2f(3, 274));
	Glinev2.setOutlineColor(sf::Color::Transparent);
	Glinev2.setOutlineThickness(0);
	Glinev2.setPosition(196, 15);
	Glinev2.setFillColor(BackColor);

	sf::RectangleShape Limv;
	Limv.setSize(sf::Vector2f(1, 274));
	Limv.setOutlineColor(sf::Color::Transparent);
	Limv.setOutlineThickness(0);
	Limv.setPosition(288, 15);
	Limv.setFillColor(BackColor);

	sf::RectangleShape Glineh1;
	Glineh1.setSize(sf::Vector2f(274, 3));
	Glineh1.setOutlineColor(sf::Color::Transparent);
	Glineh1.setOutlineThickness(0);
	Glineh1.setPosition(15, 104);
	Glineh1.setFillColor(BackColor);

	sf::RectangleShape Glineh2;
	Glineh2.setSize(sf::Vector2f(274, 3));
	Glineh2.setOutlineColor(sf::Color::Transparent);
	Glineh2.setOutlineThickness(0);
	Glineh2.setPosition(15, 196);
	Glineh2.setFillColor(BackColor);

	sf::RectangleShape Limh;
	Limh.setSize(sf::Vector2f(274, 1));
	Limh.setOutlineColor(sf::Color::Transparent);
	Limh.setOutlineThickness(0);
	Limh.setPosition(15, 288);
	Limh.setFillColor(BackColor);

	sf::Vertex Plinev[] = //Petites Line Verticales
	{
		sf::Vertex(sf::Vector2f(45, 15),GridColor),
		sf::Vertex(sf::Vector2f(45, 288),GridColor),

		sf::Vertex(sf::Vector2f(75, 15),GridColor),
		sf::Vertex(sf::Vector2f(75, 288),GridColor),

		sf::Vertex(sf::Vector2f(137, 15),GridColor),
		sf::Vertex(sf::Vector2f(137, 288),GridColor),

		sf::Vertex(sf::Vector2f(167, 15),GridColor),
		sf::Vertex(sf::Vector2f(167, 288),GridColor),

		sf::Vertex(sf::Vector2f(229, 15),GridColor),
		sf::Vertex(sf::Vector2f(229, 288),GridColor),

		sf::Vertex(sf::Vector2f(259, 15),GridColor),
		sf::Vertex(sf::Vector2f(259, 288),GridColor),
	};
	sf::Vertex Plineh[] = //Petites Line Horizontales
	{
		sf::Vertex(sf::Vector2f(15,45),GridColor),
		sf::Vertex(sf::Vector2f(288,45),GridColor),

		sf::Vertex(sf::Vector2f(15,75),GridColor),
		sf::Vertex(sf::Vector2f(288,75),GridColor),

		sf::Vertex(sf::Vector2f(15,137),GridColor),
		sf::Vertex(sf::Vector2f(288,137),GridColor),

		sf::Vertex(sf::Vector2f(15,167),GridColor),
		sf::Vertex(sf::Vector2f(288,167),GridColor),

		sf::Vertex(sf::Vector2f(15,229),GridColor),
		sf::Vertex(sf::Vector2f(288,229),GridColor),

		sf::Vertex(sf::Vector2f(15,259),GridColor),
		sf::Vertex(sf::Vector2f(288,259),GridColor),

	};



	//____Ouverture Fenetre___

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
			//La souris bouge
			case sf::Event::MouseMoved:
				Position = sf::Mouse::getPosition(window);

				if (ActiveCell[0]==0) { // Sinon �a reste fig�
					if (RectGrille.getGlobalBounds().contains((float)Position.x, (float)Position.y)) {
						HighlightsGrid = true;
						for (int i = 0; i <= 8; ++i) {
							for (int j = 0; j <= 8; ++j) {
								if (ButtonCell[i][j].getGlobalBounds().contains((float)Position.x, (float)Position.y)) {
									MaJHighlights(i, j);

								}
							}
						}
					}
					else {
						HighlightsGrid = false;
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
					//HelpButton
					else if (CHelpButton.getGlobalBounds().contains((float)Position.x, (float)Position.y)) {
						CHelpButton.CallHandler();
					}
					// ButtonVal
					else {
						for (int i = 1; i <= 9; ++i) {
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

				//Selection / D�selection
				case sf::Keyboard::Return:
					if (ActiveCell[0] == 1) {
						CancelButton.CallHandler(); // On d�selectionne
					}
					else {//On selectionne

						if (RectGrille.getGlobalBounds().contains((float)Position.x, (float)Position.y)) {
							//La souris est dans la grille, on selectionne la cellule dessous

							HighlightsGrid = true;
							for (int i = 0; i <= 8; ++i) {
								for (int j = 0; j <= 8; ++j) {
									if (ButtonCell[i][j].getGlobalBounds().contains((float)Position.x, (float)Position.y)) {
										ButtonCell[i][j].CallHandler();
									}
								}
							}
						}
						else {
							ButtonCell[ActiveCell[1]][ActiveCell[2]].CallHandler(); //On reselectionne la derni�re
						}
							
					}
						
					break;

				//Parcours avec les fleches
					
				case sf::Keyboard::Left:
					if (ActiveCell[0] == 1 & ActiveCell[1] > 0 ) { 
						//Si une cellule est active + si on n'est pas dans la colonne tout � gauche
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

		//__Drawing__

		//---Clear
		window.clear(BackColor);
		
		//---Fond de Grille
		window.draw(RectGrille);

		//Highlights
		if (HighlightsGrid) {
			window.draw(HighHorizontal);
			window.draw(HighVertical);
			window.draw(HighRegion);
		}
		

		//--Dessin des Cellules
		for (int i = 0; i <= 8; ++i) {
			for (int j = 0; j <= 8; ++j) {
				//--Dessin des buttons
				window.draw(ButtonCell[i][j]);

				//Textes des cases - Mise � jour
				if ((*CurrentGrille.getCell(i, j)).getValue() == 0) { //Si value=0, on n'�crit rien
					ButtonCell[i][j].Texte.setString(" ");
				}
				else { //Sinon on �crit la value
					ButtonCell[i][j].Texte.setString(std::to_string((*CurrentGrille.getCell(i, j)).getValue()));
				}
				//On rend le texte une fois mis � jour
				window.draw(ButtonCell[i][j].Texte);
			}
		}

		//Si une cellule est activ�e, on rend le clavier virtuel
		if (ActiveCell[0] == 1) {
			window.draw(CancelButton);
			window.draw(CancelButton.Texte);
			for (int i = 0; i <= 9; ++i) {
				window.draw(ButtonVal[i]);
				window.draw(ButtonVal[i].Texte);
			}
		}

		//--Bouton Solve
		window.draw(SolveButton);
		window.draw(SolveButton.Texte);
		window.draw(HintButton);
		window.draw(HintButton.Texte);
		window.draw(HelpMenu);
		window.draw(HelpMenu.Texte);
		window.draw(CHelpButton);
		window.draw(CHelpButton.Texte);
		window.draw(HelpValuesButton);
		window.draw(HelpValuesButton.Texte);

		

		//Higlights

		//On met la grille par dessus le reste
		window.draw(Plinev, 12, sf::Lines);
		window.draw(Plineh, 12, sf::Lines);
		window.draw(Glinev1);
		window.draw(Glinev2);
		window.draw(Limv);
		window.draw(Glineh1);
		window.draw(Glineh2);
		window.draw(Limh);

		if (ActiveCell[0] == 1) {
			window.draw(ButtonCell[ActiveCell[1]][ActiveCell[2]]);
			window.draw(ButtonCell[ActiveCell[1]][ActiveCell[2]].Texte);
		}
		
		//Display
		window.display();
	}


}




