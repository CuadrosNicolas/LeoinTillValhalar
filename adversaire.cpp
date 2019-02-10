#include "adversaire.h"

adversaire::adversaire()
{
    //ctor
}
adversaire::adversaire(float posX,float posY) : m_box(posX,posY,0,0)
{
    m_sprite.setPosition(posX,posY);
}
void adversaire::updateCollision(std::vector<plateforme>& plList,Vue& vue,std::vector<blocusAdv>& BadvList)
{

}
std::vector<int>  adversaire::update(hitBox& colBox,bool persoIsHiting,int persoDommage,hitBox& persoWeaponBox)
{
    std::vector<int> coupleScoreDommage;
    return coupleScoreDommage;
}
hitBox& adversaire::getBox()
{
    return this->m_box;
}

adversaire::~adversaire()
{
    //dtor
}
