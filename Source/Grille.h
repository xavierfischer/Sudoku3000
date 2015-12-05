#ifndef GRILLE_H
#define GRILLE_H


class Grille
{
    public:
        Grille();
        void setValues(int[9][9]);
        int* getRegion(int);
        int* getColumn(int);
        int* getLine(int);

    private:
        int values[9][9];


};

#endif // GRILLE_H
