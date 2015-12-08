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
#include "Solver.h"


Controller::Controller(){}

void MiseAJourCurrentPossibilities(int i, int j) {}

sf::Vector2i Controller::CellToPosition(int i, int j)//Renvoie la position sur la fenetre de la cellule (i,j)
{
	int x = 15 + i * 30 + (i / 3) * 2;// 15 pour la marge, i*30 pour la position de la cellule, décalée de 2 pixels à chaque fois qu'on passe dans la région suivante
	int y = 15 + j * 30 + (j / 3) * 2;//idem
	return sf::Vector2i(x,y);
}

void Controller::MaJHighlights(int i , int j) { //Recentre les rectangles de surlignage sur la cellule (i,j)
	
	HighHorizontal.setPosition(sf::Vector2f(15, CellToPosition(i, j).y)); //La ligne de surlignage se décale à l'ordonnée de la cellule
	HighVertical.setPosition(sf::Vector2f(CellToPosition(i, j).x, 15)); //La colonne de surlignage se décale à l'abscisse de la cellule
	HighRegion.setPosition(sf::Vector2f(CellToPosition(3 * (i / 3), 0).x, CellToPosition(0, 3 * (j / 3)).y)); //Région, se décale à la case supérieure gauche de la région de 9 concernée
}


void PoliceDesCellules(Grille *grid, Button(*buttonCell)[9][9], int I, int J, bool clear=false) 
{//Pour une cellule (I,J) donnée, colore en rouge les celluiles directement en conflit avec elle, et elle meme si elle genere du conflit

	for (int i = 0; i <= 8; ++i) { //On remet toutes les cellules en noir, pour peu que des cases soient en rouge d'une précédente PoliceDesCellules
		for (int j = 0; j <= 8; ++j) {
			(*buttonCell)[i][j].setOutlineColor(sf::Color::White); //On reset le carré qui entoure une cellule en blanc
			(*buttonCell)[i][j].Texte.setColor((*buttonCell)[i][j].colorT); //On reset le texte dans sa couleur normale (bleu ou noir suivant le type isFixed)
		}
	}
	if (!clear) { //Si clear==true, on a donc une fonction qu nettoye seulement de toute coloration rouge d'une PoliceDesCellules

		list<list<int>> Errors = (*grid).getUnconsistentCells(I, J); //On parcours la list des indices de cellules en conflit

		for (std::list<list<int>>::iterator it = Errors.begin(); it != Errors.end(); it++) {
			//Si il y a entrée dans la boucle, il y a au moins une erreur donc on colore la cellule concernée
			(*buttonCell)[I][J].setOutlineColor(sf::Color::Red); // Carré
			(*buttonCell)[I][J].Texte.setColor(sf::Color::Red); //Texte
			//Puis on colore la cellule tierce en conflit
			(*buttonCell)[(*it).front()][(*it).back()].Texte.setColor(sf::Color::Red);
		}
	}
	
}


void Controller::run(){
	//Definition de la fenètre
	sf::RenderWindow window(sf::VideoMode(419, 344), "SudokuSolver", sf::Style::Close);
	//Définition des couleurs
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
	Grille CurrentGrille = Grille::createTemplateEmpty(); //Initialisatio d'une grille vide
	Solver currentSolver(&CurrentGrille); //Initialisation
	currentSolver.initiate();

	phaseDeJeu = false; // On est dans la phase de définition, d'abord.
	
	//ActiveCell, de base désactivé et dans la cellule en haut a gauche.
	ActiveCell[0] = 0;
	ActiveCell[1] = 0;
	ActiveCell[2] = 0;

	//Le surlignage est désactivé
	bool HighlightsGrid = false;
	//Booléen d'aide
	HighlightsGrid = false;
	ConsistencyHelp = true;
	ValuesHelp = true;
	
	//Chargement d'une police
	sf::Font font;
	if (!font.loadFromFile("arial_narrow_7.ttf"))
	{
		throw 0;
	}


	//______Definition des Boutons____

	//___Grille___: Boutons qui couvre l'ensemble de la grille de sudoku, 
	//sert à activer le surlignage quand a souris est dessus,
	//et à entrer dans les boucles des boutons de cellules pour les différentes actions
	Button RectGrille=Button::Button(CellColor,sf::Vector2f(15,15),sf::Vector2f(273,273), &font,"" , sf::Color(255,255,255,100));

	//___ButtonCell___: Boutons définit pour chaque cellule, avvec la valeur de cellule en texte
	//sert à déclencher le changement de cellule active
	//et afficher les différentes couleurs de valeurs (rouge "en conflit", noir "fixé" et bleu "rentré par l'utilisateur")
	Button ButtonCell[9][9];
	//Parcours de la grille
	for (int i = 0; i <= 8; ++i) {
		for (int j = 0; j <= 8; ++j) {
			//Constructeur de ButtonCells
			if ((*CurrentGrille.getCell(i, j)).isFixed) { //La cellule est de valeur fixée, on définit alors avec la couleur noire
				ButtonCell[i][j] = Button(sf::Color::Transparent,
					sf::Vector2f(CellToPosition(i, j).x + 1, CellToPosition(i, j).y + 1), 
					sf::Vector2f(27, 27), 
					&font, " ",
					sf::Color::Black
					);
			}
			else { //La cellule est modifiable -> bleu
				ButtonCell[i][j] = Button(sf::Color::Transparent,
					sf::Vector2f(CellToPosition(i, j).x + 1, CellToPosition(i, j).y + 1), 
					sf::Vector2f(27, 27), 
					&font, " ",
					sf::Color::Blue
					);
			}
			//Définition du carré de selection blanc
			ButtonCell[i][j].setOutlineColor(sf::Color::White);

			//Fonction du ButtonCell[i][j]
			ButtonCell[i][j].AddHandler([&, i , j ]() {

				ButtonCell[ActiveCell[1]][ActiveCell[2]].setFillColor(sf::Color::Transparent); //L'ancienne ActiveCell reprend sa forme ancienne, comme les autres
				ButtonCell[ActiveCell[1]][ActiveCell[2]].setOutlineThickness(0); //idem, retrait du carré de selection

				ActiveCell[0] = 1;//On redéfinit ActiveCell
				ActiveCell[1] = i;
				ActiveCell[2] = j;
				ButtonCell[i][j].setFillColor(CancelColor);//Mise en forme de la nouvelle ActiveCell
				ButtonCell[i][j].setOutlineThickness(1);

				MaJHighlights(i, j); //On replace les carrés, car on a pu changer d'endroit à cause du déclenchement clavier
				HighlightsGrid = true; //On affiche le surlignage lors d'une selection

				if (ConsistencyHelp) { //Si on à l'aide à la consistence, on affiche les conflits (PoliceDesCellules)
					PoliceDesCellules(&CurrentGrille, &ButtonCell, ActiveCell[1], ActiveCell[2]);
				}
				//Mise à jour des valeurs possibles
				for (int k = 0; k <= 8; ++k) {
					//On redefinit les possibilités de valeurs dans (i,j), car elles ont pu changer
					currentPossibilities.setPossibility(k, (*(*CurrentGrille.getCell(i, j)).getPossibilities()).getPossibility(k));
				}
				if (CurrentGrille.isCellConsistent(i, j) && !(*CurrentGrille.getCell(i,j)).isEmpty()) {
					//Si la cellule n'est pas en conflit, la valeur actuelle est aussi possible. l'Algo "getPossibilities l'exclus.
					currentPossibilities.setPossibility((*CurrentGrille.getCell(i, j)).getValue()-1, true);
				}
			});
		}
	}


	//___VictoryButton___: Bouton de victoire pour quitter la fenetre à la finde la partie
	Button VictoryButton = Button::Button(
		BackColor, 
		sf::Vector2f(15, 294),
		sf::Vector2f(389, 35), 
		&font, "You won ! Click to end", 
		GreenColor);
	VictoryButton.Texte.setCharacterSize(VictoryButton.Texte.getCharacterSize() * 2); //Paramètre arbitraire, pris sur un texte fixe pour un meilleur rendu particulier
	VictoryButton.Centering(); //On recentre après resizing


	//___CancelButton___: Bouton d'annulation : déselectionne la cellule en cours
	Button CancelButton = Button(
		CancelColor, 
		sf::Vector2f(304, 151),
		sf::Vector2f(100,32),
		&font,
		"Cancel",
		BackColor);

	//Définition de la fonction Cancel
	CancelButton.AddHandler([&]() {
		ActiveCell[0] = 0; //Il n'y a plus d'ActiveCell
		ButtonCell[ActiveCell[1]][ActiveCell[2]].setFillColor(sf::Color::Transparent);//ActiveCell retrouve sa forme normale
		ButtonCell[ActiveCell[1]][ActiveCell[2]].setOutlineThickness(0);

		if ( ! (RectGrille.getGlobalBounds().contains((float)Position.x, (float)Position.y))) { 
			//Si la souris n'est pas dans la grille à ce moment (c'est possible grace au bouton "entrée" du clavier), on désactive le surlignage
			HighlightsGrid = false;
		}
		else { //Si la souris est dans la grille, le surlignage, alors fixé pour l'activeCell, se met sur la souris
			for (int i = 0; i <= 8; ++i) {
				for (int j = 0; j <= 8; ++j) {
					if (ButtonCell[i][j].getGlobalBounds().contains((float)Position.x, (float)Position.y)) { //si la souris est sur cette cellule
						MaJHighlights(i, j); //On met à jour le surlignage sur la cellule en question
						HighlightsGrid = true; //On active le surlignage
					}
				}
			}
			
		}
	});

	//___ResetButton__ : revient au problème initial
	Button ResetButton = Button(
		GridColor,
		sf::Vector2f(15, 294),
		sf::Vector2f(89, 35),
		&font,
		"Reset",
		BackColor);
	//Fonction "Reset"
	ResetButton.AddHandler([&]() { 
		for (int i = 0; i <= 8; ++i) {
			for (int j = 0; j <= 8; ++j) {
				if (!(*CurrentGrille.getCell(i, j)).isFixed) {//Toutes les cellules non fixées (donc devinées par l'utilisateur) sont...
					(*CurrentGrille.getCell(i, j)).setValue(0); //Remise à 0
					currentSolver.initiate();
					PoliceDesCellules(&CurrentGrille, &ButtonCell, ActiveCell[1], ActiveCell[2]); 
				}
			}
		}
		CancelButton.CallHandler();
	});
/*
	//---comLine1
	Button comLine1 = Button(
		GreenColor,
		sf::Vector2f(15, 329),
		sf::Vector2f(389, 40),
		&font,
		"Sudoku Solver !",
		BackColor);
	//---comLine2
	Button comLine2 = Button(
		GreenColor,
		sf::Vector2f(15, 369),
		sf::Vector2f(389, 40),
		&font,
		"Creez une grille ou charger un template aléatoire",
		BackColor);
*/


	//---SolveButton
	Button SolveButton = Button(
		GreenColor,
		sf::Vector2f(107, 294),
		sf::Vector2f(89, 35),
		&font,
		"Solve",
		BackColor);
	SolveButton.AddHandler([&]() {
		MasterSolve master(&CurrentGrille);
		master.solve();
	});
	//---HintButton
	Button HintButton = Button(
		GreenColor,
		sf::Vector2f(199, 294),
		sf::Vector2f(89, 35),
		&font,
		"Hint",
		BackColor);
	HintButton.AddHandler([&]() {
		MasterSolve master(&CurrentGrille);
		master.solveUnit();


		for (int i = 0; i <= 8; ++i) {
			for (int j = 0; j <= 8; ++j) {
				//Si la valeur est differente du texte, on l'active
				if (std::to_string((*CurrentGrille.getCell(i, j)).getValue()) != ButtonCell[i][j].Texte.getString() &
					(*CurrentGrille.getCell(i, j)).getValue() !=0) {
					ButtonCell[i][j].CallHandler();
					break;
				}
			}
		}
	});
	

	//---Help Menu
	Button HelpMenu = Button(
		CancelColor,
		sf::Vector2f(306, 187),
		sf::Vector2f(96, 30),
		&font,
		"Help",
		BackColor);
	HelpMenu.setOutlineThickness(2);
	HelpMenu.setOutlineColor(CancelColor);

	//---ConsistencyHelpButton
	Button CHelpButton = Button(
		CancelColor,
		sf::Vector2f(306, 220),
		sf::Vector2f(96, 32),
		&font,
		"Check (on)", //En début de programme : l'aide est activée pour aider à la conception d'une grille
		BackColor);
	CHelpButton.setOutlineThickness(2);
	CHelpButton.setOutlineColor(CHelpButton.colorF);
	CHelpButton.Sizing();
	CHelpButton.Centering();
	CHelpButton.EnfonceurButton(); //le bouton est également activé

	CHelpButton.AddHandler([&]() {
		if (ConsistencyHelp) {

			ConsistencyHelp = false;
			CHelpButton.Texte.setString("Check (off)");
			CHelpButton.Sizing();
			CHelpButton.Centering();
			if (ActiveCell[0] == 1) {
				PoliceDesCellules(&CurrentGrille, &ButtonCell, ActiveCell[1], ActiveCell[2], true);
			}

		}
		else {
			ConsistencyHelp = true;
			CHelpButton.Texte.setString("Check (on)");
			CHelpButton.Sizing();
			CHelpButton.Centering();

			if (ActiveCell[0] == 1) {

			PoliceDesCellules(&CurrentGrille, &ButtonCell, ActiveCell[1], ActiveCell[2]);
			}
		}
		CHelpButton.EnfonceurButton();
	});

	//---PossibleValuesHelpButton
	Button HelpValuesButton = Button(
		CancelColor,
		sf::Vector2f(306, 254),
		sf::Vector2f(96, 32),
		&font,
		"Values (on)",//En début de programme : l'aide est activée pour aider à la conception d'une grille
		BackColor);
	HelpValuesButton.setOutlineThickness(2);
	HelpValuesButton.setOutlineColor(HelpValuesButton.colorF);
	HelpValuesButton.Sizing();
	HelpValuesButton.Centering();
	HelpValuesButton.EnfonceurButton(); //le bouton est également activé
	HelpValuesButton.AddHandler([&]() {
		if (ValuesHelp) {
			ValuesHelp = false;
			HelpValuesButton.Texte.setString("Values (off)");
			HelpValuesButton.Sizing();
			HelpValuesButton.Centering();
			
		}
		else {
			ValuesHelp = true;
			HelpValuesButton.Texte.setString("Values (on)");
			}
			if (ActiveCell[0] == 1) {
				//MiseAJourCurrentPossibilities
				for (int k = 0; k <= 8; ++k) {
				currentPossibilities.setPossibility(k,
					(*(*CurrentGrille.getCell(ActiveCell[1],ActiveCell[2])).getPossibilities()).getPossibility(k));
			}
		}
		HelpValuesButton.EnfonceurButton();
		});
	

	
	//---FixerButton
	Button FixerButton = Button(
		GreenColor,
		sf::Vector2f(199, 294),
		sf::Vector2f(89, 35),
		&font,
		"Play",
		BackColor);
	FixerButton.AddHandler([&]() {
		if (CurrentGrille.isConsistent()) {
			phaseDeJeu = true;
			for (int i = 0; i <= 8; ++i) {
				for (int j = 0; j <= 8; ++j) {
					
					if ((*CurrentGrille.getCell(i, j)).getValue() != 0) {
						(*CurrentGrille.getCell(i, j)).isFixed = true;
						ButtonCell[i][j].colorT = sf::Color::Black;
						ButtonCell[i][j].Texte.setColor(sf::Color::Black);

						//On reset les fonctions d'aide à "off" pour la phase de jeu
						if (ValuesHelp) {
							ValuesHelp = false;
							HelpValuesButton.Texte.setString("Values (off)");
							HelpValuesButton.EnfonceurButton();
							HelpValuesButton.Sizing();
							HelpValuesButton.Centering();
						}
						if (ConsistencyHelp) {
							ConsistencyHelp = false;
							CHelpButton.Texte.setString("Check (off)");
							CHelpButton.EnfonceurButton();
							CHelpButton.Sizing();
							CHelpButton.Centering();
						}
					}
					currentSolver.initiate();
				}
			}
		}
		else {
			//Message d'erreur
		}
	});

	//---TemplateButton
	Button TemplateButton = Button(
		GridColor,
		sf::Vector2f(15, 294),
		sf::Vector2f(89, 35),
		&font,
		"Model",
		BackColor);
	TemplateButton.AddHandler([&]() {
		CurrentGrille = Grille::createTemplateDiabolique();
	});


	//Buttons de modification des valeurs
	Button ButtonVal[10];
	//--Création boutons
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
		"Delete",
		BackColor
		);
	//--Handlers de modification
	for (int i = 0; i <= 9; ++i) {
		ButtonVal[i].AddHandler([&, i]() {
			if (ActiveCell[0] == 1) {
				if ((*CurrentGrille.getCell(ActiveCell[1], ActiveCell[2])).isFixed == false) {
					(*CurrentGrille.getCell(ActiveCell[1], ActiveCell[2])).setValue(i);
					currentSolver.initiate();
					if (CurrentGrille.isFull() & CurrentGrille.isConsistent()) {
						Victory = true;
					}
				}
				if (ConsistencyHelp) {
					// On review si la cellule est consistente
					PoliceDesCellules(&CurrentGrille, &ButtonCell, ActiveCell[1], ActiveCell[2]);
				}
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

				if (ActiveCell[0]==0) { // Sinon ça reste figé
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
					//Cas de victoire
					if (Victory) {
						if (VictoryButton.getGlobalBounds().contains((float)Position.x, (float)Position.y)) {
							window.close();
						}
					}
					else {
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
						//TemplateButton
						else if (!phaseDeJeu & TemplateButton.getGlobalBounds().contains((float)Position.x, (float)Position.y)) {
							TemplateButton.CallHandler();
						}
						//FixerButton
						else if (!phaseDeJeu & FixerButton.getGlobalBounds().contains((float)Position.x, (float)Position.y)) {
							FixerButton.CallHandler();
						}
						//ResetButton
						else if (phaseDeJeu & ResetButton.getGlobalBounds().contains((float)Position.x, (float)Position.y)) {
							ResetButton.CallHandler();
						}
						//SolveButton
						else if (phaseDeJeu & SolveButton.getGlobalBounds().contains((float)Position.x, (float)Position.y)) {
							SolveButton.CallHandler();
						}
						//HintButton
						else if (phaseDeJeu & HintButton.getGlobalBounds().contains((float)Position.x, (float)Position.y)) {
							HintButton.CallHandler();
						}
						//ConsistencyButton
						else if (CHelpButton.getGlobalBounds().contains((float)Position.x, (float)Position.y)) {

							CHelpButton.CallHandler();
						}
						//HelpValuesButton
						else if (HelpValuesButton.getGlobalBounds().contains((float)Position.x, (float)Position.y)) {
							HelpValuesButton.CallHandler();
						}
						// ButtonVal
						else {
							for (int i = 0; i <= 9; ++i) {
								if (ButtonVal[i].getGlobalBounds().contains((float)Position.x, (float)Position.y) &
									ActiveCell[0] == 1
									) {
									if (ValuesHelp & (i > 0) & !(currentPossibilities.getPossibility(i - 1))) {
										//La valeur n'est pas prise en compte
									}
									else {
										ButtonVal[i].CallHandler();
									}

								}
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
							ButtonCell[ActiveCell[1]][ActiveCell[2]].CallHandler(); //On reselectionne la dernière
						}
							
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

				//Textes des cases - Mise à jour
				if ((*CurrentGrille.getCell(i, j)).getValue() == 0) { //Si value=0, on n'écrit rien
					ButtonCell[i][j].Texte.setString(" ");
				}
				else { //Sinon on écrit la value
					ButtonCell[i][j].Texte.setString(std::to_string((*CurrentGrille.getCell(i, j)).getValue()));
				}
				//On rend le texte une fois mis à jour
				window.draw(ButtonCell[i][j].Texte);
			}
		}

		//Si une cellule est activée, on rend le clavier virtuel
		if (ActiveCell[0] == 1) {
			window.draw(CancelButton);
			window.draw(CancelButton.Texte);
			for (int i = 0; i <= 9; ++i) {
				window.draw(ButtonVal[i]);
				if (i > 0 & ValuesHelp & !(currentPossibilities.getPossibility(i - 1))) {
				}
				else {
				window.draw(ButtonVal[i].Texte);
				}
			}
		}


		//--Bouton Solve
		if (phaseDeJeu & !Victory) {
			window.draw(SolveButton);
			window.draw(SolveButton.Texte);
			window.draw(HintButton);
			window.draw(HintButton.Texte);
			window.draw(ResetButton);
			window.draw(ResetButton.Texte);
		}
		else if (Victory) {
			window.draw(VictoryButton.Texte);

		}
		else {
			window.draw(TemplateButton);
			window.draw(TemplateButton.Texte);
			window.draw(FixerButton);
			window.draw(FixerButton.Texte);
		}
		


		window.draw(HelpMenu);
		window.draw(HelpMenu.Texte);

		if (ConsistencyHelp & !ValuesHelp) {
			window.draw(HelpValuesButton);
			window.draw(HelpValuesButton.Texte);
			window.draw(CHelpButton);
			window.draw(CHelpButton.Texte);
		}
		else {
			window.draw(CHelpButton);
			window.draw(CHelpButton.Texte);
			window.draw(HelpValuesButton);
			window.draw(HelpValuesButton.Texte);
		}
		

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

		if (Victory) {

		}

		/*window.draw(comLine1);
		window.draw(comLine2);
		window.draw(comLine1.Texte);
		window.draw(comLine2.Texte);*/

		/*if (ActiveCell[0] == 1) {
			window.draw(ButtonCell[ActiveCell[1]][ActiveCell[2]]);
			window.draw(ButtonCell[ActiveCell[1]][ActiveCell[2]].Texte);
		}*/
		
		//Display
		window.display();
	}


}




