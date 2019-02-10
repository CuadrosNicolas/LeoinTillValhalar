#ifndef DECOR_H
#define DECOR_H
#include <SFML/Graphics.hpp>
#include "generalTexture.h"
#include "hitbox.h"
//sprite affich� en arri�re plan ou devant
class decor : public hitBox
{
    public:
        decor();
        decor(std::string nom,float posX,float posY);
        sf::Sprite& getSprite();
        virtual ~decor();
    protected:
        sf::Sprite m_sprite;
    private:
};

#endif // DECOR_H
