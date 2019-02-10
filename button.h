#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include "hitbox.h"
#include "generalTexture.h"

//objet repr�sentant un bouton
class button
{
    public:
        button();
        button(float posX,float posY,std::string nom);//g�n�ration du bouton en fonction de sa position et de sa texture
        bool update(sf::RenderWindow& window);//mise a jour du bouton (renvoie vrai si le bouton est pr�ss�)
        virtual ~button();
    protected:
        hitBox m_box;
        sf::Sprite m_sprite;

    private:
};

#endif // BUTTON_H
