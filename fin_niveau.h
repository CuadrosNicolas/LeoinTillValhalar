#ifndef FIN_NIVEAU_H
#define FIN_NIVEAU_H
#include "hitbox.h"
#include <SFML/Graphics.hpp>
#include "generalTexture.h"

//objet symbolisant la fin de niveau
class fin_niveau : public hitBox
{
    public:
        fin_niveau();
        fin_niveau(float posX,float posY);
        sf::Sprite& getSprite();//récupération du sprite
        virtual ~fin_niveau();
    protected:
        sf::Sprite m_sprite;//sprite
    private:
};

#endif // FIN_NIVEAU_H
