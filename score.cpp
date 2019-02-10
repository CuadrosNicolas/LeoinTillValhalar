#include "score.h"

score::score() : m_nom("")
{
    //ctor
}
score::score(std::string nom,int nombre)
{
    m_nom = nom;
    m_nombre = nombre;
}
//test si il est supérieur au score entré en paramètre
bool score::superior(score* a)
{
    if(this->m_nombre > a->m_nombre)
        return true;
    else
        return false;
}

score::~score()
{
    //dtor
}
