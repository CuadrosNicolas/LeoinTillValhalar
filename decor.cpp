#include "decor.h"

decor::decor()
{

}
decor::decor(std::string nom,float posX,float posY) : hitBox(posX,posY,generalTexture::textureList[nom].getSize().x,generalTexture::textureList[nom].getSize().y)
{
    //initialisation des valeurs du décor
    this->setPosition(posX,posY);
    this->m_sprite.setTexture(generalTexture::textureList[nom]);//apllication de la texture qui correspond au nom du passé
                                                                // en argument en le récupérant via la liste de texture présente dans generalTexture
    this->m_sprite.setPosition(posX,posY);
}
sf::Sprite& decor::getSprite()
{
    return this->m_sprite;
}

decor::~decor()
{
    //dtor
}
