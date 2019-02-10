#ifndef PIECE_H
#define PIECE_H
#include "hitbox.h"
#include <SFML/Graphics.hpp>
#include "generalTexture.h"

class piece : public hitBox//objet permettant au joueur d'augmenter son score
{
    public:
        piece(float posX,float posY);
        sf::Sprite& getSprite();
        bool isActive();
        void desactive();
        virtual ~piece();
    protected:
        sf::Sprite m_sprite;
        bool m_isActive;
    private:
};

#endif // PIECE_H
