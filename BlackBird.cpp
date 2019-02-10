#include "BlackBird.h"

BlackBird::BlackBird(float posX,float posY) : adversaire(posX,posY)
{
    m_sprite.setTexture(generalTexture::textureList["blackBird"]);
    m_animMapTab = fonction::loadAnim("data/Animations/fireBirdAnim.txt");
m_etat = "move";
m_sprite.setTextureRect(sf::IntRect(this->m_animMapTab[m_etat][0].getTab()[0],this->m_animMapTab[m_etat][0].getTab()[1],
                                        this->m_animMapTab[m_etat][0].getTab()[2],this->m_animMapTab[m_etat][0].getTab()[3]));
    m_box = hitBox(posX,posY,this->m_animMapTab[m_etat][0].getTab()[2],this->m_animMapTab[m_etat][0].getTab()[3]);
    m_spawn = sf::Vector2f (posX,posY);
    m_active = false;
    m_vit = 40;
    m_dommage = 25;
    m_col = false;
}
void BlackBird::updateCollision(std::vector<plateforme>& plList,Vue& vue,std::vector<blocusAdv>& BadvList)
{
    if(this->m_active)//si il descend
    {
        this->m_box.moveHB(0,this->m_vit);//descend son sprite et sa hitbox
        this->m_sprite.move(0,this->m_vit);
    }
    for(int e = 0;e<plList.size();e++)
    {
        if(this->m_box.boxCollision(plList[e].getColBox()) && this->m_col == false && plList[e].isHiting() == false)
        {
            this->m_col = true;
        }

    }
    if(this->m_box.boxCollision(vue))//si il est dans la vue
        environement::m_window.draw(this->m_sprite);//il s'affiche


    if(this->m_active == true && this->m_col == true)
    {
        this->Desactive();
        this->m_sprite.setPosition(this->m_spawn);
        this->m_box.setPosition(this->m_spawn.x,this->m_spawn.y);
    }
    this->m_col = false;

}
int BlackBird::getDommage()
{
    return this->m_dommage;
}
void BlackBird::Active()
{
    this->m_active = true;
}
void BlackBird::Desactive()
{
    this->m_active = false;
}
hitBox& BlackBird::getBox()
{
    return this->m_box;
}
BlackBird::~BlackBird()
{
    //dtor
}
