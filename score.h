#ifndef SCORE_H
#define SCORE_H
#include <iostream>

class score //objet compos� d'un nom et d'un nombre pour exprim� les scores (nom du joueur + score)
{
    public:
        score();
        score(std::string nom,int nombre);
        bool superior(score* a);
        virtual ~score();
        std::string m_nom;
        int m_nombre;

    protected:
    private:
};

#endif // SCORE_H
