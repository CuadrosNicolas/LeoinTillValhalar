#ifndef SCORE_H
#define SCORE_H
#include <iostream>

class score //objet composé d'un nom et d'un nombre pour exprimé les scores (nom du joueur + score)
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
