#include "fin_niveau.h"

fin_niveau::fin_niveau() : hitBox()
{

}
fin_niveau::fin_niveau(float posX,float posY) : hitBox(posX,posY,generalTexture::textureList["levelEnd"].getSize().x,generalTexture::textureList["levelEnd"].getSize().y)
{
    //initialisation des valeur de la fin de niveau
    m_sprite.setPosition(posX,posY);
    m_sprite.setTexture(generalTexture::textureList["levelEnd"]);//aplication de la texture qui lui correspond
}
sf::Sprite& fin_niveau::getSprite()
{
    return this->m_sprite;
}

fin_niveau::~fin_niveau()
{
    //dtor
}
