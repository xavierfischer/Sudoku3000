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
	int x = 15 + i * 30 + (i / 3) * 2;// 15 pour la marge, i*30 pour la position de la cellule, d�cal�e de 2 pixels � chaque fois qu'on passe dans la r�gion suivante
	int y = 15 + j * 30 + (j / 3) * 2;//idem
	return sf::Vector2i(x,y);
}

void Controller::MaJHighlights(int i , int j) { //Recentre les rectangles de surlignage sur la cellule (i,j)
	
	HighHorizontal.setPosition(sf::Vector2f(15, CellToPosition(i, j).y)); //La ligne de surlignage se d�cale � l'ordonn�e de la cellule
	HighVertical.setPosition(sf::Vector2f(CellToPosition(i, j).x, 15)); //La colonne de surlignage se d�cale � l'abscisse de la cellule
	HighRegion.setPosition(sf::Vector2f(CellToPosition(3 * (i / 3), 0).x, CellToPosition(0, 3 * (j / 3)).y)); //R�gion, se d�cale � la case sup�rieure gauche de la r�gion de 9 concern�e
}


void PoliceDesCellules(Grille *grid, Button(*buttonCell)[9][9], int I, int J, bool clear=false) 
{//Pour une cellule (I,J) donn�e, colore en rouge les celluiles directement en conflit avec elle, et elle meme si elle genere du conflit

	for (int i = 0; i <= 8; ++i) { //On remet toutes les cellules en noir, pour peu que des cases soient en rouge d'une pr�c�dente PoliceDesCellules
		for (int j = 0; j <= 8; ++j) {
			(*buttonCell)[i][j].setOutlineColor(sf::Color::White); //On reset le carr� qui entoure une cellule en blanc
			(*buttonCell)[i][j].Texte.setColor((*buttonCell)[i][j].colorT); //On reset le texte dans sa couleur normale (bleu ou noir suivant le type isFixed)
		}
	}
	if (!clear) { //Si clear==true, on a donc une fonction qu nettoye seulement de toute coloration rouge d'une PoliceDesCellules

		list<list<int>> Errors = (*grid).getUnconsistentCells(I, J); //On parcours la list des indices de cellules en conflit

		for (std::list<list<int>>::iterator it = Errors.begin(); it != Errors.end(); it++) {
			//Si il y a entr�e dans la boucle, il y a au moins une erreur donc on colore la cellule concern�e
			(*buttonCell)[I][J].setOutlineColor(sf::Color::Red); // Carr�
			(*buttonCell)[I][J].Texte.setColor(sf::Color::Red); //Texte
			//Puis on colore la cellule tierce en conflit
			(*buttonCell)[(*it).front()][(*it).back()].Texte.setColor(sf::Color::Red);
		}
	}
	
}


void Controller::run(){
	//Definition de la fen�tre
	sf::RenderWindow window(sf::VideoMode(419, 344), "SudokuSolver", sf::Style::Close);
	//D�finition des couleurs
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
	Grille CurrentGrille = Grille::createTemplateEmpty(); //Initialisation d'une grille vide
	Solver currentSolver(&CurrentGrille); //Initialisation
	currentSolver.initiate();

	phaseDeJeu = false; // On est dans la phase de d�finition, d'abord.
	
	//ActiveCell, de base d�sactiv� et dans la cellule en haut a gauche.
	ActiveCell[0] = 0;
	ActiveCell[1] = 0;
	ActiveCell[2] = 0;

	//Le surlignage est d�sactiv�
	bool HighlightsGrid = false;
	//Bool�en d'aide
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
	//On va d'abord d�finir tous les bouttons, leur action et les rectangles de mise � jour, 
	//puis on gerera la boucle de rafraichissement de la fenetre 
	//en testant les evenements souris et clavier et en dessinant les formes ainsi mises � jour
	//________________________________



	//___Grille___: Boutons qui couvre l'ensemble de la grille de sudoku, 
	//sert � activer le surlignage quand a souris est dessus,
	//et � entrer dans les boucles des boutons de cellules pour les diff�rentes actions
	Button RectGrille=Button::Button(CellColor,sf::Vector2f(15,15),sf::Vector2f(273,273), &font,"" , sf::Color(255,255,255,100));

	//___ButtonCell___: Boutons d�finit pour chaque cellule, avvec la valeur de cellule en texte
	//sert � d�clencher le changement de cellule active
	//et afficher les diff�rentes couleurs de valeurs (rouge "en conflit", noir "fix�" et bleu "rentr� par l'utilisateur")
	Button ButtonCell[9][9];
	//Parcours de la grille
	for (int i = 0; i <= 8; ++i) {
		for (int j = 0; j <= 8; ++j) {
			//Constructeur de ButtonCells
			if ((*CurrentGrille.getCell(i, j)).isFixed) { //La cellule est de valeur fix�e, on d�finit alors avec la couleur noire
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
			//D�finition du carr� de selection blanc
			ButtonCell[i][j].setOutlineColor(sf::Color::White);

			//Fonction du ButtonCell[i][j]
			ButtonCell[i][j].AddHandler([&, i , j ]() {

				ButtonCell[ActiveCell[1]][ActiveCell[2]].setFillColor(sf::Color::Transparent); //L'ancienne ActiveCell reprend sa forme ancienne, comme les autres
				ButtonCell[ActiveCell[1]][ActiveCell[2]].setOutlineThickness(0); //idem, retrait du carr� de selection

				ActiveCell[0] = 1;//On red�finit ActiveCell
				ActiveCell[1] = i;
				ActiveCell[2] = j;
				ButtonCell[i][j].setFillColor(CancelColor);//Mise en forme de la nouvelle ActiveCell
				ButtonCell[i][j].setOutlineThickness(1);

				MaJHighlights(i, j); //On replace les carr�s, car on a pu changer d'endroit � cause du d�clenchement clavier
				HighlightsGrid = true; //On affiche le surlignage lors d'une selection

				if (ConsistencyHelp) { //Si on � l'aide � la consistence, on affiche les conflits (PoliceDesCellules)
					PoliceDesCellules(&CurrentGrille, &ButtonCell, ActiveCell[1], ActiveCell[2]);
				}
				//Mise � jour des valeurs possibles
				for (int k = 0; k <= 8; ++k) {
					//On redefinit les possibilit�s de valeurs dans (i,j), car elles ont pu changer
					currentPossibilities.setPossibility(k, (*(*CurrentGrille.getCell(i, j)).getPossibilities()).getPossibility(k));
				}
				if (CurrentGrille.isCellConsistent(i, j) && !(*CurrentGrille.getCell(i,j)).isEmpty()) {
					//Si la cellule n'est pas en conflit, la valeur actuelle est aussi possible. l'Algo "getPossibilities l'exclus.
					currentPossibilities.setPossibility((*CurrentGrille.getCell(i, j)).getValue()-1, true);
				}
			});
		}
	}


	//___VictoryButton___: Bouton de victoire pour quitter la fenetre � la finde la partie
	Button VictoryButton = Button::Button(
		BackColor, 
		sf::Vector2f(15, 294),
		sf::Vector2f(389, 35), 
		&font, "You won ! Click to end", 
		GreenColor);
	VictoryButton.Texte.setCharacterSize(VictoryButton.Texte.getCharacterSize() * 2); //Param�tre arbitraire, pris sur un texte fixe pour un meilleur rendu particulier
	VictoryButton.Centering(); //On recentre apr�s resizing


	//___CancelButton___: Bouton d'annulation : d�selectionne la cellule en cours
	Button CancelButton = Button(
		CancelColor, 
		sf::Vector2f(304, 151),
		sf::Vector2f(100,32),
		&font,
		"Cancel",
		BackColor);

	//D�finition de la fonction Cancel
	CancelButton.AddHandler([&]() {
		ActiveCell[0] = 0; //Il n'y a plus d'ActiveCell
		ButtonCell[ActiveCell[1]][ActiveCell[2]].setFillColor(sf::Color::Transparent);//ActiveCell retrouve sa forme normale
		ButtonCell[ActiveCell[1]][ActiveCell[2]].setOutlineThickness(0);

		if ( ! (RectGrille.getGlobalBounds().contains((float)Position.x, (float)Position.y))) { 
			//Si la souris n'est pas dans la grille � ce moment (c'est possible grace au bouton "entr�e" du clavier), on d�sactive le surlignage
			HighlightsGrid = false;
		}
		else { //Si la souris est dans la grille, le surlignage, alors fix� pour l'activeCell, se met sur la souris
			for (int i = 0; i <= 8; ++i) {
				for (int j = 0; j <= 8; ++j) {
					if (ButtonCell[i][j].getGlobalBounds().contains((float)Position.x, (float)Position.y)) { //si la souris est sur cette cellule
						MaJHighlights(i, j); //On met � jour le surlignage sur la cellule en question
						HighlightsGrid = true; //On active le surlignage
					}
				}
			}
			
		}
	});

	//___ResetButton__ : revient au probl�me initial, ie efface les cellules rentr�es par l'utilisateur
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
				if (!(*CurrentGrille.getCell(i, j)).isFixed) {//Toutes les cellules non fix�es (donc devin�es par l'utilisateur) sont...
					(*CurrentGrille.getCell(i, j)).setValue(0); //..remises � 0
					currentSolver.initiate();
					PoliceDesCellules(&CurrentGrille, &ButtonCell, ActiveCell[1], ActiveCell[2]); 
				}
			}
		}
		CancelButton.CallHandler();
	});

	//___Bouton Solve : Appelle l'algorythme de r�solution, apr�s avoir nettoy� les valeurs rentr�s par l'utilisateur (potentiellement fausses).
	Button SolveButton = Button(
		GreenColor,
		sf::Vector2f(107, 294),
		sf::Vector2f(89, 35),
		&font,
		"Solve",
		BackColor);
	SolveButton.AddHandler([&]() {
		ResetButton.CallHandler();//On nettoye les valeurs de l'utilisateur
		MasterSolve master(&CurrentGrille);
		master.solve();

		if (CurrentGrille.isFull() & CurrentGrille.isConsistent()) {
			//Le solver � r�ussi
			VictoryButton.Texte.setString("Was it THAT hard ? Click to end"); //Affichage du message de fin
			VictoryButton.Texte.setCharacterSize(VictoryButton.Texte.getCharacterSize() /1.8 );
			VictoryButton.Centering();
			Victory = 1;
		}

	});
	//Bouton "Hint"
	Button HintButton = Button(
		GreenColor,
		sf::Vector2f(199, 294),
		sf::Vector2f(89, 35),
		&font,
		"Hint",
		BackColor);
	HintButton.AddHandler([&]() {
		MasterSolve master(&CurrentGrille);
		master.solveUnit();// On appelle le resolveur pour une seule cellule
		//On parcours toutes les cellules pour voir laquelle a �t� modif�e, et on la selectionne pour le montrer � l'utilisateur
		for (int i = 0; i <= 8; ++i) {
			for (int j = 0; j <= 8; ++j) {
				//Si la valeur est differente du texte, on l'active
				if (std::to_string((*CurrentGrille.getCell(i, j)).getValue()) != ButtonCell[i][j].Texte.getString() &
					(*CurrentGrille.getCell(i, j)).getValue() !=0) {
					ButtonCell[i][j].CallHandler();//Activation de la cellule
					break;
				}
			}
		}
		//Si c'est la derni�re cellule, on active la victoire
		if (CurrentGrille.isFull() & CurrentGrille.isConsistent()) {
			VictoryButton.Texte.setString("Was it THAT hard ? Click to end"); //Affichage du message de fin
			VictoryButton.Texte.setCharacterSize(VictoryButton.Texte.getCharacterSize() / 1.8);
			VictoryButton.Centering();
			Victory = 1;
		}
	});
	

	//---Help Menu : Rectangle Titre de l'aide
	Button HelpMenu = Button(
		CancelColor,
		sf::Vector2f(306, 187),
		sf::Vector2f(96, 30),
		&font,
		"Help",
		BackColor);
	HelpMenu.setOutlineThickness(2);
	HelpMenu.setOutlineColor(CancelColor);

	//__Boutton pour activer l'aide � la consistence. Quend elle est activ�e, la cellule devient rouge quand on detecte un conflit direct avec une autre.
	Button CHelpButton = Button(
		CancelColor,
		sf::Vector2f(306, 220),
		sf::Vector2f(96, 32),
		&font,
		"Check (on)", //En d�but de programme : l'aide est activ�e pour aider � la conception d'une grille
		BackColor);
	CHelpButton.setOutlineThickness(2);
	CHelpButton.setOutlineColor(CHelpButton.colorF);
	CHelpButton.Sizing();
	CHelpButton.Centering();
	CHelpButton.EnfonceurButton(); //le bouton est �galement activ�, en d�but de programme

	CHelpButton.AddHandler([&]() {
		if (ConsistencyHelp) {
			//D�sactivation
			ConsistencyHelp = false;
			CHelpButton.Texte.setString("Check (off)");
			CHelpButton.Sizing();
			CHelpButton.Centering();
			if (ActiveCell[0] == 1) { //Si une cellule est selectionn�e, ie il peut y avoir des cellules rouges
				PoliceDesCellules(&CurrentGrille, &ButtonCell, ActiveCell[1], ActiveCell[2], true); //On remet tout � 0 (attribut clear=true)
			}
		}
		else {//Activation
			ConsistencyHelp = true;
			CHelpButton.Texte.setString("Check (on)");
			CHelpButton.Sizing();
			CHelpButton.Centering();

			if (ActiveCell[0] == 1) {//Si une cellule est activ�e, on checke si elle est consistente
			PoliceDesCellules(&CurrentGrille, &ButtonCell, ActiveCell[1], ActiveCell[2]);
			}
		}
		CHelpButton.EnfonceurButton(); //Le boutton change de forme
	});

	//___Bouton d'aide au valeurs possibles
	Button HelpValuesButton = Button(
		CancelColor,
		sf::Vector2f(306, 254),
		sf::Vector2f(96, 32),
		&font,
		"Values (on)",//En d�but de programme : l'aide est activ�e pour aider � la conception d'une grille
		BackColor);
	HelpValuesButton.setOutlineThickness(2);
	HelpValuesButton.setOutlineColor(HelpValuesButton.colorF);
	HelpValuesButton.Sizing();
	HelpValuesButton.Centering();
	HelpValuesButton.EnfonceurButton(); //le bouton est �galement activ� au d�but, pendant la phase de d�finition

	HelpValuesButton.AddHandler([&]() { //Action du bouton d'aide des valeurs
		if (ValuesHelp) { //On change la valeur de controle de l'aide
			ValuesHelp = false;
			HelpValuesButton.Texte.setString("Values (off)");
			HelpValuesButton.Sizing();
			HelpValuesButton.Centering(); // On change le Texte donc il faut resizer et recentrer le texte
		}
		else {
			ValuesHelp = true;
			HelpValuesButton.Texte.setString("Values (on)");
			HelpValuesButton.Sizing();
			HelpValuesButton.Centering();
			}
			if (ActiveCell[0] == 1) {
				//MiseAJour CurrentPossibilities
				//On met � jour les valeurs possiblies, car on a pu changer de cellule depuis la d�sactivation de l'aide
				for (int k = 0; k <= 8; ++k) {
				currentPossibilities.setPossibility(k,
					(*(*CurrentGrille.getCell(ActiveCell[1],ActiveCell[2])).getPossibilities()).getPossibility(k)); //On ajoute les possibilit�s sur la case active
			}
		}
		HelpValuesButton.EnfonceurButton();
		});
	
	//___Bouton de Fixation___ "Play" : Fixe le prbl�me, 
	//on passe de la phase de d�finition de la grille � la phase ou le joueur va pouvoir changer seulement les cellules non d�finies par le probleme
	Button FixerButton = Button(
		GreenColor,
		sf::Vector2f(199, 294),
		sf::Vector2f(89, 35),
		&font,
		"Play",
		BackColor);
	FixerButton.AddHandler([&]() {//Action "Passer en mode "Jeu" et Fixer la grille
		if (CurrentGrille.isConsistent()) { //On v�rifie que la grille n'a pas de valeurs en conflit direct
			phaseDeJeu = true; //On passe en phase de jeu
			for (int i = 0; i <= 8; ++i) {
				for (int j = 0; j <= 8; ++j) {
					//Pour chaque cellule...
					if ((*CurrentGrille.getCell(i, j)).getValue() != 0) { //Si l'utilisateur a rentr� une valeur dans cette case...
						(*CurrentGrille.getCell(i, j)).isFixed = true; //On la fixe
						ButtonCell[i][j].colorT = sf::Color::Black; //On fixe la couleur inh�rente au ButtonCell
						ButtonCell[i][j].Texte.setColor(sf::Color::Black); //On update cette couleur
						}
					}
					
				}
			//On reset les fonctions d'aide � "off" pour la phase de jeu
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
			currentSolver.initiate(); //Le solver est r�initialis� pour remettre les bonnes possibleValues dans chaque case en prenant en compte que lees valeurs actuelles sont maintenant fix�es.
									//Car m�me si l'utilisateur rentre une valeur dans une case, on lui indique toujours quelles sont les cases possibles.
		}
		else {
			//Si il y a des cellules en conflit direct, le bouton ne s'active pas.
		}
	});

	//___TemplateButton___ : G�n�rateur de Grille "al�atoire"
	//Renvoie, durant la phase de d�finition de la grille, une des grilles hard-cod�es dans la classe Grille.
	Button TemplateButton = Button(
		GridColor,
		sf::Vector2f(15, 294),
		sf::Vector2f(89, 35),
		&font,
		"Model",
		BackColor);
	TemplateButton.AddHandler([&]() {
		CurrentGrille = Grille::createTemplateDiabolique(); //On cr�� la grille
		//int n = rand() % 10;
		//CurrentGrille = Grille::createTemplate(n);
		FixerButton.CallHandler();//On fixe le probl�me
	});


	//___Clavier num�rique virtuel___ : 10 boutons 
	//ButtonVal[1-9] sont les valeurs qu'on rentre,
	//ButtonVal[0] est le bouton "Delete" pour effacer une cellule (la mettre � value=0)
	//Chacun assigne � la cellule active la valeur correspondante

	Button ButtonVal[10];
	for (int i = 1; i <= 9; ++i) {
		ButtonVal[i] = Button(
			ButtonColor,
			sf::Vector2f(304 + ((i-1)%3) * 34, 15+ ((i - 1) / 3)*34), //Placement en NumPad virtuel pour les valeurs de 1 � 9
			sf::Vector2f(32, 32),
			&font,
			std::to_string(i),
			BackColor
			);
	}
	//Bouton 0, le bouton "Delete"
	ButtonVal[0] = Button(
		ButtonColor,
		sf::Vector2f(304 , 117), //Position et taille diff�rente des 9 autres
		sf::Vector2f(100, 32),
		&font,
		"Delete",//Texte diff�rents des 9 autres
		BackColor
		);
	//---Les fonctions d�clench�es par ces 10 boutons sont identiques, 0 ou pas.
	for (int i = 0; i <= 9; ++i) {
		ButtonVal[i].AddHandler([&, i]() {
			if (ActiveCell[0] == 1) { //On v�rifie qu'une cellule est active
				if ((*CurrentGrille.getCell(ActiveCell[1], ActiveCell[2])).isFixed == false) { //On v�rifie que ladite cellule n'est pas fix�e

					(*CurrentGrille.getCell(ActiveCell[1], ActiveCell[2])).setValue(i); //On lui donne la valeur du bouton
					currentSolver.initiate(); //On met � jour les valeursPossibles alentours avec cette nouvelle information

					if (CurrentGrille.isFull() & CurrentGrille.isConsistent()) {
						Victory = true; //Si la grille est maintenant pleine, et qu'il n'y a pas de conflit, l'utilisateur a gagn�
					}
				}
				if (ConsistencyHelp) {
					// Si on a l'aide � la consistence activ�e, on v�rifie qu'il n'y a pas de conflits
					PoliceDesCellules(&CurrentGrille, &ButtonCell, ActiveCell[1], ActiveCell[2]);
				}
			}
		});
	}

	//___Rectangles de surlignage__ : Rectangles turquoise qui surlignent les lignes colonnes et secteurs de la cellule active.
	//On d�finit des formes fixes, qu'on d�place avec MaJHighlights (ligne 28)
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

	//___Dessin de la grille___ :
	//On d�finit des shapes fixes, qui forment la grille et qui vient se dessiner par dessus le reste pour faire croire � des petits ilots qui constituent les cellules

	//--S�parateurs de secteur
	sf::RectangleShape Glinev1; //1er separateur
	Glinev1.setSize(sf::Vector2f(3, 274));
	Glinev1.setOutlineColor(sf::Color::Transparent);
	Glinev1.setOutlineThickness(0);
	Glinev1.setPosition(104, 15);
	Glinev1.setFillColor(BackColor);

	sf::RectangleShape Glinev2; //2e separateur
	Glinev2.setSize(sf::Vector2f(3, 274));
	Glinev2.setOutlineColor(sf::Color::Transparent);
	Glinev2.setOutlineThickness(0);
	Glinev2.setPosition(196, 15);
	Glinev2.setFillColor(BackColor);

	sf::RectangleShape Limv; //Les 3e separateurs sont mis en bout de grille et servent � cacher le pixel de trop des derni�res cellules, qui sont d'habitude cach� par la ligne de grille suivante
	Limv.setSize(sf::Vector2f(1, 274));
	Limv.setOutlineColor(sf::Color::Transparent);
	Limv.setOutlineThickness(0);
	Limv.setPosition(288, 15);
	Limv.setFillColor(BackColor);

	sf::RectangleShape Glineh1;//idem en horizontal
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

	sf::Vertex Plinev[] = //Petites Line Verticales, s�parateurs de cellules
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

	//--On va recenser ici d'abord tous les evenements et leurs cons�quences, puis on dessine les formes mises � jour (ButtonCells, Numpad, rectangles de surlignage)
	while (window.isOpen())
	{
		//Gestion des Evenements
		sf::Event event;

		if (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			//Cas ou la souris bouge
			case sf::Event::MouseMoved:

				Position = sf::Mouse::getPosition(window); //On update sa position

				//Surlignage
				if (ActiveCell[0]==0) { // Le surlignage reste fix� � la cellule activ�e s'il y en a une

					if (RectGrille.getGlobalBounds().contains((float)Position.x, (float)Position.y)) { //On v�rifie que la souris est bien sur la grille
						HighlightsGrid = true;//On active le surlignage (au cas ou la souris RENTRE dans la grille)

						for (int i = 0; i <= 8; ++i) {//Pour chaque cellule..
							for (int j = 0; j <= 8; ++j) {
								if (ButtonCell[i][j].getGlobalBounds().contains((float)Position.x, (float)Position.y)) { 
									//Si on est dessus, on ramene les rectangles � elle
									MaJHighlights(i, j);
								}
							}
						}
					}
					else {
						HighlightsGrid = false; //Si la souris n'est pas ou plus dans la grille
					}
				}
				continue; //On reboucle

			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left) {
					//Si click, on actualise aussi la position
					Position = sf::Mouse::getPosition(window);

					//Click sur le boutton de victoire de fin
					if (Victory) {
						if (VictoryButton.getGlobalBounds().contains((float)Position.x, (float)Position.y)) {
							window.close();//Fin de partie
						}
					}
					else {
						//Verification pour chaque cellule
						if (RectGrille.getGlobalBounds().contains((float)Position.x, (float)Position.y)) { //On checke si la souris est bien sur la grille, pour �viter 81 it�rations intuiles
							for (int i = 0; i <= 8; ++i) {
								for (int j = 0; j <= 8; ++j) {
									if (ButtonCell[i][j].getGlobalBounds().contains((float)Position.x, (float)Position.y)) {
										ButtonCell[i][j].CallHandler();
									}

								}
							}
						}
						//Bouton Cancel (deselection de celulle)
						else if (ActiveCell[0] == 1 
							& CancelButton.getGlobalBounds().contains((float)Position.x, (float)Position.y)) {
							CancelButton.CallHandler();
						}
						//Bouton G�n�ration de grille
						else if (!phaseDeJeu 
							& TemplateButton.getGlobalBounds().contains((float)Position.x, (float)Position.y)) {
							TemplateButton.CallHandler();
						}
						//Bouton "Play"
						else if (!phaseDeJeu 
							& FixerButton.getGlobalBounds().contains((float)Position.x, (float)Position.y)) {
							FixerButton.CallHandler();
						}
						//Bouton Reset
						else if (phaseDeJeu & 
							ResetButton.getGlobalBounds().contains((float)Position.x, (float)Position.y)) {
							ResetButton.CallHandler();
						}
						//Bouton Solve
						else if (phaseDeJeu & 
							SolveButton.getGlobalBounds().contains((float)Position.x, (float)Position.y)) {
							SolveButton.CallHandler();
						}
						//Bouton Hint
						else if (phaseDeJeu & 
							HintButton.getGlobalBounds().contains((float)Position.x, (float)Position.y)) {
							HintButton.CallHandler();
						}
						//Bouton Aide � la consistence
						else if (CHelpButton.getGlobalBounds().contains((float)Position.x, (float)Position.y)) {

							CHelpButton.CallHandler();
						}
						//Bouton aide aux valeurs possibles
						else if (HelpValuesButton.getGlobalBounds().contains((float)Position.x, (float)Position.y)) {
							HelpValuesButton.CallHandler();
						}
						//Bouton d'assignation de valeur
						else {
							for (int i = 0; i <= 9; ++i) {
								if (ButtonVal[i].getGlobalBounds().contains((float)Position.x, (float)Position.y) &
									ActiveCell[0] == 1
									) {
									if (ValuesHelp & //Si l'aide aux valeurs est activ�e
										(i > 0) & //pour toutes les cellules != "Delete"
										!(currentPossibilities.getPossibility(i - 1))) {//Si la possibilit� de cette valeur est false..
										//..cliquer sur le boutton ne change rien
									}
									else { //Comprtement normal
										ButtonVal[i].CallHandler();
									}
								}
							}
						}
					}	
				}



				// Cas o� le clavier est activ�
			case sf::Event::KeyPressed:
				
				switch (event.key.code) {
				
				//Cas de suppression de la valeur d'une cellule
				case sf::Keyboard::Numpad0 :
					ButtonVal[0].CallHandler();
					break;
				case sf::Keyboard::BackSpace:
					ButtonVal[0].CallHandler();
					break;
				case sf::Keyboard::Delete:
					ButtonVal[0].CallHandler();
					break;
				//Valeurs de modification de la cellule
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
					//Dans ce cas, la touche "Entr�e" deselectionne la cellule active, ou selectionne la case sous la souris. 
					//Si la souris n'est pas sur la grille, elle selectionne la derni�re cellule active

					if (ActiveCell[0] == 1) { //Une cellule est activ�e, on d�selectionne
						CancelButton.CallHandler();
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
						else {//La souris n'est pas dans la grille, on reselectionne la derni�re
							ButtonCell[ActiveCell[1]][ActiveCell[2]].CallHandler(); 
						}	
					}
					break;

				//Parcours avec les fleches de la grille
					
				case sf::Keyboard::Left:
					if (ActiveCell[0] == 1 & ActiveCell[1] > 0 ) { 
						//Si une cellule est active et si on n'est pas dans la colonne tout � gauche, alors on peut se d�placer � gauche
						ButtonCell[ActiveCell[1]-1][ActiveCell[2]].CallHandler();
						break;
					}
					break;
				case sf::Keyboard::Right:
					if (ActiveCell[0] == 1 & ActiveCell[1] < 8) { //idem
						ButtonCell[ActiveCell[1]+1][ActiveCell[2]].CallHandler();
						break;
					}
					break;
				case sf::Keyboard::Up:
					if (ActiveCell[0] == 1 & ActiveCell[2] > 0) { //idem
						ButtonCell[ActiveCell[1]][ActiveCell[2]-1].CallHandler();
						break;
					}
						break;
				case sf::Keyboard::Down:
					if (ActiveCell[0] == 1 & ActiveCell[2] <8) { //idem
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

		//__On rend les differentes formes__

		//---Clear
		window.clear(BackColor);
		
		//---Fond de Grille
		window.draw(RectGrille);

		//Highlights, � remplir avant la grille et les ButtonCell
		if (HighlightsGrid) {
			window.draw(HighHorizontal);
			window.draw(HighVertical);
			window.draw(HighRegion);
		}
		

		//--Dessin des Cellules (ButtonCell)
		for (int i = 0; i <= 8; ++i) {
			for (int j = 0; j <= 8; ++j) {
				//__Dessin des buttons (la plupart du temps transparent, sauf quand la cellule est activ�e)
				window.draw(ButtonCell[i][j]);

				//Textes des cases - Mise � jour
				if ((*CurrentGrille.getCell(i, j)).getValue() == 0) { 
					   //Si value=0, on n'�crit rien
					ButtonCell[i][j].Texte.setString(" ");
				}
				else { //Sinon on �crit la value
					ButtonCell[i][j].Texte.setString(std::to_string((*CurrentGrille.getCell(i, j)).getValue()));
				}

				//On rend le texte une fois mis � jour
				window.draw(ButtonCell[i][j].Texte);
			}
		}

		//Si une cellule est activ�e, on rend le clavier virtuel (ButtonVal + CancelButton)
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


		//__Phase de jeu sans victoire
		if (phaseDeJeu & !Victory) {
			window.draw(SolveButton);
			window.draw(SolveButton.Texte);
			window.draw(HintButton);
			window.draw(HintButton.Texte);
			window.draw(ResetButton);
			window.draw(ResetButton.Texte);
		}
		else if (Victory) { //Victoire
			window.draw(VictoryButton.Texte);

		}
		else { //Definition de grille
			window.draw(TemplateButton);
			window.draw(TemplateButton.Texte);
			window.draw(FixerButton);
			window.draw(FixerButton.Texte);
		}
		
		//Menu d'aide
		window.draw(HelpMenu);
		window.draw(HelpMenu.Texte);
		window.draw(HelpValuesButton);
		window.draw(HelpValuesButton.Texte);
		window.draw(CHelpButton);
		window.draw(CHelpButton.Texte);
		
		//On met la grille par dessus le reste
		window.draw(Plinev, 12, sf::Lines);
		window.draw(Plineh, 12, sf::Lines);
		window.draw(Glinev1);
		window.draw(Glinev2);
		window.draw(Limv);
		window.draw(Glineh1);
		window.draw(Glineh2);
		window.draw(Limh);

		//Display
		window.display();
	}//Retour � la boucle "while(window.isOpen())"


}




