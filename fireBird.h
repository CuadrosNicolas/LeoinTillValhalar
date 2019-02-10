#ifndef FIREBIRD_H
#define FIREBIRD_H
#include "adversaire.h"
#include "generalTexture.h"
#include "plateforme.h"
#include "Vue.h"
#include <iostream>
//adversaire fireBird
// celui descend vers le bas si le joueur passe en dessous
//au contact du joueur celui-�i re�ois 100 de d�g�ts (sufisant pour tuer en 1 coup le jour)
//au contact d'une plateforme il se transforme en poulet
//une fois en poulet si le joueur entre en contact avec , le joueur r�cup�re 10 points de vie

class fireBird  : public adversaire//adversaire fireBird
{
    public:
        fireBird(float posX,float posY);
        void updateCollision(std::vector<plateforme>& plList,Vue& vue,std::vector<blocusAdv>& BadvList);//misa jour des collisions avec les plateformes
        std::vector<int>  update(hitBox& colBox,bool persoIsHiting,int persoDommage,hitBox& persoWeaponBox);//mise � jour des collisions avec le joueur
        virtual ~fireBird();
    protected:

        bool m_use;//si il a �t� touch�
        int m_dommage;//dommage qu'il inflige
        float m_vit;//vitesse
        bool m_goDown;//si il se dirige vers la bas
        bool m_col;//si il est entr� en collision avec une plateforme
    private:
};

#endif // FIREBIRD_H
