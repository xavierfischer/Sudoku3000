#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <list>
#include <array>
#include "Controller.h"
#include <thread>

// On assume que Cell à un attribut text de type sf::Text et qu'on a juste à l'appeler

//TODO affichage swag+collones-lignes-regions actives (colors ?)
//TODO Affichage des textes (après GIT)


//"Kase"
/*std::array<int,3> Kase(int x, int y) {//Renvoie (0/1, X,Y) avec X,Y colonne ligne de la case demandée (de 1 à 9) et 0 si la souris n'est pas dans la grill, 1 si elle l'est
	array<int, 3> r;
						   //on vérifie si elle est dans la grille
	if (!(15 <= x & x <= 285 & 15 <= y & y <= 285)) {
		return <0, 1, 1>; //on met 1 deux fois par défaut, ce ne sera pas utilisé.
	}

	int X = x - 15;//on enlève la marge
	int Y = y - 15;//on enlève la marge

	X = X / 30 + 1;
	Y = Y / 30 + 1;
	return (1, X, Y);


}*/
void main()
{

//BITE


	//Highlights de lignes et colonnes



	Controller CurrentController;
	CurrentController.run();

	

}
	



	/*while (window.isOpen())
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
				x = event.mouseMove.x;
				y = event.mouseMove.y;
				continue;

			case sf::Event::MouseButtonPressed:
				if (15 <= x & x <= 285 & 295 <= y & y <= 385 & event.mouseButton.button == sf::Mouse::Left) {
					window.close();
					break;
					//Ici on va mettre "Solve"
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
		window.clear(DarkGreyColor);
		//window.draw(sprite);
		window.draw(RectangeGrille);

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

	return 0;*/

