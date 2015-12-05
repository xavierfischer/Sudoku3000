#include "Grille.h"

/*
	Une grille est un ensemble de 81 cellules
*/

/*
	Constructeur par défaut : toutes les cellules sont initialisées sans valeurs
*/

Grille::Grille() {
	Cellule cells[9][9];
}

/*
	Constructeur à partir de données entières : toutes les cellules sont initialisées par les valeurs données
*/

Grille::Grille(int * a[9])
{
	Cellule cells[9][9];
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cells[i][j] = Cellule();
		}
	}
}

/*
	Retourne un NineUplet représentant la région où se trouve la cellule (i, j)
*/

NineUplet Grille::getRegion(int i, int j)
{
	int regionI = i - (i % 3);
	int localI = i % 3;
	int localJ = j % 3;
}

NineUplet Grille::getRegion(int)
{
	return NineUplet();
}

/*
Constructeur à partir des régions :

NO1   |   N1   |   NE1
____     ____     ____

O1    |   C1   |   E1
____     ____     ____

SO1   |   S1   |   SE1

*/

Grille::Grille(Region NO1, Region N1, Region NE1, Region O1, Region C1, Region E1, Region SO1, Region S1, Region SE1) {
	list<Region> list1;
	list1.push_back(NO1);
	list1.push_back(N1);
	list1.push_back(NE1);
	list1.push_back(O1);
	list1.push_back(C1);
	list1.push_back(E1);
	list1.push_back(SO1);
	list1.push_back(S1);
	list1.push_back(SE1);
	regions.assign(list1.begin(), list1.end());
}

//On verifie grace a la fonction ci dessous si une grille est bien pleine
bool Grille::isFull() {
	if (regions.size() != 9) {
		return false;
	}
	for (Region reg : regions) {
		if (!reg.isFull()) {
			return false;
		}
	}
	return true;
}

RegionHolder &Grille::NO() {
	RegionHolder* regionHolder = nullptr;
	list<Region>::iterator iterator = regions.begin();
	for (int i = 0; i<0; i++) {
		iterator++;
	}
	Region regio(*iterator);
	regionHolder = new RegionHolder(regio);
	return *regionHolder;
}

RegionHolder &Grille::N() {
	RegionHolder* regionHolder = nullptr;
	list<Region>::iterator iterator = regions.begin();
	for (int i = 0; i<1; i++) {
		iterator++;
	}
	Region regio(*iterator);
	regionHolder = new RegionHolder(regio);
	return *regionHolder;
}

RegionHolder &Grille::NE() {
	RegionHolder* regionHolder = nullptr;
	list<Region>::iterator iterator = regions.begin();
	for (int i = 0; i<2; i++) {
		iterator++;
	}
	Region regio(*iterator);
	regionHolder = new RegionHolder(regio);
	return *regionHolder;
}

RegionHolder &Grille::O() {
	RegionHolder* regionHolder = nullptr;
	list<Region>::iterator iterator = regions.begin();
	for (int i = 0; i<3; i++) {
		iterator++;
	}
	Region regio(*iterator);
	regionHolder = new RegionHolder(regio);
	return *regionHolder;
}

RegionHolder &Grille::C() {
	RegionHolder* regionHolder = nullptr;
	list<Region>::iterator iterator = regions.begin();
	for (int i = 0; i<4; i++) {
		iterator++;
	}
	Region regio(*iterator);
	regionHolder = new RegionHolder(regio);
	return *regionHolder;
}

RegionHolder &Grille::E() {
	RegionHolder* regionHolder = nullptr;
	list<Region>::iterator iterator = regions.begin();
	for (int i = 0; i<5; i++) {
		iterator++;
	}
	Region regio(*iterator);
	regionHolder = new RegionHolder(regio);
	return *regionHolder;
}

RegionHolder &Grille::SO() {
	RegionHolder* regionHolder = nullptr;
	list<Region>::iterator iterator = regions.begin();
	for (int i = 0; i<6; i++) {
		iterator++;
	}
	Region regio(*iterator);
	regionHolder = new RegionHolder(regio);
	return *regionHolder;
}

RegionHolder &Grille::S() {
	RegionHolder* regionHolder = nullptr;
	list<Region>::iterator iterator = regions.begin();
	for (int i = 0; i<7; i++) {
		iterator++;
	}
	Region regio(*iterator);
	regionHolder = new RegionHolder(regio);
	return *regionHolder;
}

RegionHolder &Grille::SE() {
	RegionHolder* regionHolder = nullptr;
	list<Region>::iterator iterator = regions.begin();
	for (int i = 0; i<8; i++) {
		iterator++;
	}
	Region regio(*iterator);
	regionHolder = new RegionHolder(regio);
	return *regionHolder;
}

void Grille::Accept() {}
//On verifie grace a la fonction ci dessous que la grille respecte bien les regles du sudoku.
bool Grille::isConsistent() {
	bool cons = true;
	RegionHolder reg1;
	RegionHolder reg2;
	RegionHolder reg3;
	list<Region>::iterator iterator = regions.begin();
	for (int i = 0; i<9; i++) {//On regarde les regions
		Region reg = *iterator;
		cons = reg.isConsistent() && cons;
		iterator++;
	}
	//Puis on regarde les lignes
	iterator = regions.begin();
	for (int i = 0; i<3; i++) {
		reg1 = RegionHolder(*iterator);
		iterator++;
		reg2 = RegionHolder(*iterator);
		iterator++;
		reg3 = RegionHolder(*iterator);
		iterator++;
		Region reg((reg1.TopRow().getString() + reg2.TopRow().getString()) + reg3.TopRow().getString());
		cons = reg.isConsistent() && cons;
		reg = Region((reg1.MiddleRow().getString() + reg2.MiddleRow().getString()) + reg3.MiddleRow().getString());
		cons = reg.isConsistent() && cons;
		reg = Region((reg1.BottomRow().getString() + reg2.BottomRow().getString()) + reg3.BottomRow().getString());
		cons = reg.isConsistent() && cons;
	}
	//Puis on regarde les colonnes
	for (int i = 0; i<3; i++) {
		iterator = regions.begin();
		for (int j = 0; i<j; i++) {
			iterator++;
		}
		reg1 = RegionHolder(*iterator);
		iterator++;
		iterator++;
		iterator++;
		reg2 = RegionHolder(*iterator);
		iterator++;
		iterator++;
		iterator++;
		reg3 = RegionHolder(*iterator);

		Region reg((reg1.LeftColumn().getString() + reg2.LeftColumn().getString()) + reg3.LeftColumn().getString());
		cons = reg.isConsistent() && cons;
		reg = Region((reg1.MiddleColumn().getString() + reg2.MiddleColumn().getString()) + reg3.MiddleColumn().getString());
		cons = reg.isConsistent() && cons;
		reg = Region((reg1.RightColumn().getString() + reg2.RightColumn().getString()) + reg3.RightColumn().getString());
		cons = reg.isConsistent() && cons;
	}
	return cons;
}

void Grille::create() {
	list<int> possibilities[9][9];
	int values[9][9];

	/* initialize random seed: */
	//srand (time(NULL));


	for (int i = 1; i<10; i++) {
		for (int j = 1; j<10; j++) {
			int myInts[9] = { 1,2,3,4,5,6,7,8,9 };
			possibilities[i][j] = list<int>(myInts, myInts + sizeof(myInts) / sizeof(int));
			values[i][j] = 0;
		}
	}
}

void assignValue(int i, int j, list<int> possibilities) {

}

bool Grille::isEmpty() {
	for (list<Region>::iterator it = regions.begin(); it != regions.end(); it++) {
		if ((*(it)).isFull()) {
			return false;
		}
	}
	return true;
}
