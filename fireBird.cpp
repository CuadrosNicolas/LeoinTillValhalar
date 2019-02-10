#include "fireBird.h"

fireBird::fireBird(float posX,float posY) : adversaire(posX,posY)
{
m_sprite.setTexture(generalTexture::textureList["fireBird"]);
m_animMapTab = fonction::loadAnim("data/Animations/fireBirdAnim.txt");
m_etat = "move";
m_sprite.setTextureRect(sf::IntRect(this->m_animMapTab[m_etat][0].getTab()[0],this->m_animMapTab[m_etat][0].getTab()[1],
                                        this->m_animMapTab[m_etat][0].getTab()[2],this->m_animMapTab[m_etat][0].getTab()[3]));
m_dommage = 10;
m_goDown = false;
m_col = false;
m_box = hitBox(posX,posY,this->m_animMapTab[m_etat][0].getTab()[2],this->m_animMapTab[m_etat][0].getTab()[3]);
m_vit = 10;
this->m_sprite.setPosition(posX,posY);
m_use = false;
}
void fireBird::updateCollision(std::vector<plateforme>& plList,Vue& vue,std::vector<blocusAdv>& BadvList)
{
    if(!this->m_use)//si il n'a pas été en collision avec le joueur
    {
    for(int e = 0;e<plList.size();e++)
    {
        if(this->m_box.boxCollision(plList[e].getColBox()) && this->m_col == false)//si il est en collision avec une plateforme
        {
            this->m_dommage*= -10;//il donne 10 point de santé
            this->m_etat = "death";
            m_sprite.setTextureRect(sf::IntRect(this->m_animMapTab[m_etat][0].getTab()[0],this->m_animMapTab[m_etat][0].getTab()[1],
                                        this->m_animMapTab[m_etat][0].getTab()[2],this->m_animMapTab[m_etat][0].getTab()[3]));
            this->m_col = true;//il a été en collision avec le sol
        }

    }
    if(this->m_goDown == true && this->m_col == false)//si il descend
    {
        this->m_box.moveHB(0,this->m_vit);//descend son sprite et sa hitbox
        this->m_sprite.move(0,this->m_vit);
    }
    if(this->m_box.boxCollision(vue))//si il est dans la vue
        environement::m_window.draw(this->m_sprite);//il s'affiche

}

}
std::vector<int>  fireBird::update(hitBox& colBox,bool persoIsHiting,int persoDommage,hitBox& persoWeaponBox)
{

    std::vector<int> coupleScoreDommage;//preparation de son couple de score et de dommage
    coupleScoreDommage.push_back(0);
    coupleScoreDommage.push_back(0);
        if(!this->m_use)//si n'a pas été en collision avec le joueur
    {
    if(this->m_goDown == false && this->m_col == false)//si il ne va pas vers le bas et qu'il n'a pas été en collision avec le sole
    {


    if((colBox.getPosX() > this->m_box.getPosX() && colBox.getPosX()< this->m_box.getPosX() + this->m_box.getSizeX())//si joueur passe en dessous
       || (colBox.getPosX() + colBox.getSizeX() > this->m_box.getPosX() && colBox.getPosX() + colBox.getSizeX()< this->m_box.getPosX() + this->m_box.getSizeX() ))
       {
           this->m_goDown = true;//il va vers le bas
       }

    }
                if(this->m_box.boxCollision(colBox))//si il est en collision avec le joueur
    {
        coupleScoreDommage[1] = this->m_dommage;//ajout des dommages au couple dommage/score
        this->m_use = true;//il a été en collision avec le joueur
    }



    }


return coupleScoreDommage;//revoie de son couple score/dommage





}


fireBird::~fireBird()
{
    //dtor
}
