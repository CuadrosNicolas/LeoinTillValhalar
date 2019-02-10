#ifndef BLACKBIRD_H
#define BLACKBIRD_H
#include "adversaire.h"
#include "generalTexture.h"
#include "plateforme.h"
#include "Vue.h"
#include <iostream>
#include <SFML/Graphics.hpp>


class BlackBird  : public adversaire//adversaire fireBird
{
    public:
        BlackBird(float posX,float posY);
        void updateCollision(std::vector<plateforme>& plList,Vue& vue,std::vector<blocusAdv>& BadvList);//misa jour des collisions avec les plateformes
        int getDommage();
        void Active();
        void Desactive();
        hitBox& getBox();
        virtual ~BlackBird();
    protected:

        bool m_active;
        sf::Vector2f m_spawn;
        int m_dommage;//dommage qu'il inflige
        float m_vit;//vitesse
        bool m_col;//si il est entr� en collision avec une plateforme
    private:
};

#endif // BLACKBIRD_H
