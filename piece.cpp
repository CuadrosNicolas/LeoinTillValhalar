#include "piece.h"

piece::piece(float posX,float posY) : hitBox(posX,posY,50,46)
{
    //charge le sprite(position et texture)
    this->m_sprite.setTexture(generalTexture::textureList["piece"]);
    this->m_sprite.setPosition(posX,posY);
    //et active la pièce
    this->m_isActive = true;
}
sf::Sprite& piece::getSprite()
{
    return this->m_sprite;
}
bool piece::isActive()
{
    return this->m_isActive;
}
void piece::desactive()
{
    this->m_isActive = false;//désactive la pièce pour ne plus l'afficher et tester les collisions avec
}


piece::~piece()
{
    //dtor
}
