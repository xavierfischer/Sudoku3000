#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <array>
#include <thread>
#include "Cellule.h"
#include "Button.h"
#include "Controller.h"
#include "Grille.h"
#include "MasterSolve.h"

//La classe Controller contient certains attributs necessaires à la communication à travers l'interface, 
//elle contient la méthode qui lanc la fenetre du jeu, run().

class Controller 
{
public:

	int ActiveCell[3]; //contient l'"activation"(1) ou non (0) d'une Cellule à l'écran, 
					   //et le couple i , j coordonnées de cette cellule, ou de la dernière activée

	//Rectangle Turquoises de surlignage des colonnes et lignes correspondantes à la cellule.
	sf::RectangleShape HighVertical;
	sf::RectangleShape HighHorizontal ;
	sf::RectangleShape HighRegion;

	Controller();
	sf::Vector2i CellToPosition(int x, int y); //Renvoie la position sur la fenetre de la cellule (i,j)
	void run(); //Methode qui lance la fenetre
	void MaJHighlights(int i, int j); //Met à jour les rectangles de surlignage

	bool ConsistencyHelp = false; //L'aide sur la consistence est elle activée ?
	bool ValuesHelp = false; //L'aide sur les valeurs possibles est elle activée ?
	bool HighlightsGrid = false; //les rectangle de surlignage sont ils activés ?

	bool Victory = false; //Booléen de victoire, complétion du sudoku
	Possibilities currentPossibilities; //On stocke 9 booléen qui représentent la possibilité pour chaque valeur d'être dans la cellule activée
	bool phaseDeJeu = false; //Si False, on est dans la phase de définition du Sudoku, à True, on joue.
};
