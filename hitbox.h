#ifndef HITBOX_H
#define HITBOX_H
#include <SFML/Graphics.hpp>
#include <iostream>
class hitBox
{
    public:

        //Hitbox , rectangle d'une position m_posX,m_posY taille m_sizeX,m_sizeY,composé de 4 lignes pour être déssiner
        hitBox();
        hitBox(float posX,float posY,float sizeX,float sizeY);
        void reSize(float sizeX,float sizeY);
        void setPosition(float posX,float posY);//met la position de la hitbox
        void setPositionByCenter(float posX,float posY);//met en position la hitbox par rapport à son centre
        void setPositionToRight(float posX,float posY);//met en position la hitbox par rapport à son coté droit
        void moveHB(float posX,float posY);//bouge la hitbox
        bool boxCollision(hitBox& box);//retourne true si il y a collision entre les Hitbox
        bool pointCollision(float pointX,float pointY);//retourne true si il y a collisiont avec le point
        void drawBox(sf::RenderWindow& window);//dessine la hitbox a l'écran via ses 4 lignes
        void lineSetRed();
        void lineSetWhite();

        //fonction pour récupérer les attributs de la hitbox
        float getPosX();
        float getPosY();
        float getSizeX();
        float getSizeY();

        virtual ~hitBox();
    protected:

       float m_posX;
        float m_posY;
        float m_sizeX;
        float m_sizeY;
        float m_animTime;


        sf::RectangleShape m_lineUp;
        sf::RectangleShape m_lineDown;
        sf::RectangleShape m_lineRight;
        sf::RectangleShape m_lineLeft;
        sf::Clock m_clock;
        sf::Color m_Red;
        sf::Color m_White;


    private:
};

#endif // HITBOX_H
