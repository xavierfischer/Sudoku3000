#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <array>
#include <thread>
#include "Cellule.h"
#include "Button.h"
#include "Controller.h"
#include "Grille.h"

//La classe Controller contient certains attributs necessaires � la communication � travers l'interface, 
//elle contient la m�thode qui lanc la fenetre du jeu, run().

class Controller 
{
public:

	int ActiveCell[3]; //contient l'"activation"(1) ou non (0) d'une Cellule � l'�cran, 
					   //et le couple i , j coordonn�es de cette cellule, ou de la derni�re activ�e

	//Rectangle Turquoises de surlignage des colonnes et lignes correspondantes � la cellule.
	sf::RectangleShape HighVertical;
	sf::RectangleShape HighHorizontal ;
	sf::RectangleShape HighRegion;

	Controller();
	sf::Vector2i CellToPosition(int x, int y); //Renvoie la position sur la fenetre de la cellule (i,j)
	void run(); //Methode qui lance la fenetre
	void MaJHighlights(int i, int j); //Met � jour les rectangles de surlignage

	bool ConsistencyHelp = false; //L'aide sur la consistence est elle activ�e ?
	bool ValuesHelp = false; //L'aide sur les valeurs possibles est elle activ�e ?
	bool HighlightsGrid = false; //les rectangle de surlignage sont ils activ�s ?

	bool Victory = false; //Bool�en de victoire, compl�tion du sudoku
	Possibilities currentPossibilities; //On stocke 9 bool�en qui repr�sentent la possibilit� pour chaque valeur d'�tre dans la cellule activ�e
	bool phaseDeJeu = false; //Si False, on est dans la phase de d�finition du Sudoku, � True, on joue.
};
