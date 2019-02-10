#include "checkpoint.h"

checkpoint::checkpoint(float posX,float posY) : m_box(posX,posY,50,45)
{
    //initialisation les différentes textures
    m_animMapTab = fonction::loadAnim("data/Animations/checkPointAnim.txt");
    this->m_sprite.setTexture(generalTexture::textureList["checkpoint"]);
    this->m_sprite.setTextureRect(sf::IntRect(this->m_animMapTab["babe"][0].getTab()[0],this->m_animMapTab["babe"][0].getTab()[1],
                                        this->m_animMapTab["babe"][0].getTab()[2],this->m_animMapTab["babe"][0].getTab()[3]));
    this->m_sprite.setPosition(posX,posY);
    this->m_check.setTexture(generalTexture::textureList["checkpoint"]);
    this->m_check.setTextureRect(sf::IntRect(this->m_animMapTab["check"][0].getTab()[0],this->m_animMapTab["check"][0].getTab()[1],
                                        this->m_animMapTab["check"][0].getTab()[2],this->m_animMapTab["check"][0].getTab()[3]));
    this->m_box = hitBox(posX,posY,this->m_animMapTab["babe"][0].getTab()[2],this->m_animMapTab["babe"][0].getTab()[3]);
    this->m_check.setPosition(posX,posY - 700);
    this->m_isActive = false;
    this->m_empalle = false;
    m_checkBox = hitBox(posX,posY - 500,this->m_animMapTab["check"][0].getTab()[2],this->m_animMapTab["check"][0].getTab()[3]);
}
void checkpoint::update(Vue& vue)
{

    if(this->m_isActive == true && this->m_empalle == false)//si il est activé et qu'il n'a pas encore été en contact avec le cochon
    {
        this->m_check.move(0,25);//descend le panneau
        this->m_checkBox.moveHB(0,25);

        environement::m_window.draw(this->m_check);
        if(this->m_checkBox.boxCollision(this->m_box))//si ils sont en contact
        {
            this->m_empalle = true;//ils on été en contact
    this->m_sprite.setTextureRect(sf::IntRect(this->m_animMapTab["empalle"][0].getTab()[0],this->m_animMapTab["empalle"][0].getTab()[1],
                                        this->m_animMapTab["empalle"][0].getTab()[2],this->m_animMapTab["empalle"][0].getTab()[3]));//changement de la partie affiché de la texture à celle qui correspond

        }
    }


   if(this->m_box.boxCollision(vue))//si il est dans la vue
    environement::m_window.draw(this->m_sprite);//s'affiche à l'écran


}
void checkpoint::active()
{
    this->m_isActive = true;//activation du checkpoint
}
hitBox& checkpoint::getBox()
{
    return this->m_box;
}
sf::Sprite& checkpoint::getSprite()
{
    return this->m_sprite;
}

checkpoint::~checkpoint()
{
    //dtor
}
