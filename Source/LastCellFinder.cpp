//Cette classe permet de trouver la derniere cellule pour chaque region.
#include "LastCellFinder.h"

LastCellFinder::LastCellFinder(TripleHolder &tri1, TripleHolder &tri2, TripleHolder &tri3):triplet1(tri1),triplet2(tri2),triplet3(tri3){}

bool LastCellFinder::fill() {

    //On copie les cellules dans un tableau
    Cell tableCells[9];
    tableCells[0]=triplet1.getCell1();
    tableCells[1]=triplet1.getCell2();
    tableCells[2]=triplet1.getCell3();
    tableCells[3]=triplet2.getCell1();
    tableCells[4]=triplet2.getCell2();
    tableCells[5]=triplet2.getCell3();
    tableCells[6]=triplet3.getCell1();
    tableCells[7]=triplet3.getCell2();
    tableCells[8]=triplet3.getCell3();

    int count=0;
    int count2=0;
    int pos=0;
    int num=0;

    //On compte le nombre de cellule vide
    for (int i=0; i<=8; i++) {
        if (tableCells[i].isEmpty()) {
            count++;
            pos=i;//On enregistre la position de la derniere cellule vide parcourue (la seule dans le cas qui nous interesse)
        }
    }
    if (count==1) {//Si on a effectivement un changement à faire (si il n'y a qu'une seule cellule vide)
        for (int i=1; i<=9; i++) {//Pour chaque nombre en 1 et 9
            count2=0;
            for (int j=0; j<=8; j++) {//On compte le nombre de fois qu'il apparait
                if (tableCells[j].numberCell==i) {
                    count2++;
                }
            }//Si le nombre n'apparait pas
            if (count2==0) {
                num=i;//Alors on le stocke dans num
            }
        }
        tableCells[pos]=Cell((char)(((int)'0')+num));//On remplace la cellule vide par le nombre num
        triplet1=TripleHolder(tableCells[0], tableCells[1], tableCells[2]);
        triplet2=TripleHolder(tableCells[3], tableCells[4], tableCells[5]);
        triplet3=TripleHolder(tableCells[6], tableCells[7], tableCells[8]);
        return true;
    }
    return false;
}
