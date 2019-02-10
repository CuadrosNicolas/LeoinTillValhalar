#include "punchRabbit.h"

punchRabbit::punchRabbit(float posX,float posY): adversaire(posX,posY)
{
    m_sprite.setTexture(generalTexture::textureList["punchRabbit"]);
    m_sprite.setPosition(posX,posY);
    m_animMapTab = fonction::loadAnim("data/Animations/punchRabbitAnim.txt");
    m_etat = "run_left";
    m_sprite.setTextureRect(sf::IntRect(this->m_animMapTab[m_etat][0].getTab()[0],this->m_animMapTab[m_etat][0].getTab()[1],
                                        this->m_animMapTab[m_etat][0].getTab()[2],this->m_animMapTab[m_etat][0].getTab()[3]));
    m_box = hitBox(posX,posY,this->m_animMapTab["attack_left"][0].getTab()[2],this->m_animMapTab[this->m_etat][0].getTab()[3]);
    m_life = 50;

    m_animTime = 0.5;
    m_force = 35;
    m_applyforceClock.restart();
    m_vitesse = 5;
    m_colD = false;
    m_attractionForce = m_force;
    m_applyforce = 0.02;
    m_applyforceClock.restart();
    m_animAv = 0;


    m_goToBeat = false;
    m_goToBeatTime = 0.5;

    m_isBeating = false;
    m_beatTime = 3;

    m_orientation = "GAUCHE";
    m_dommage = 5;

    m_beHit = false;
    m_colorChange = false;
    m_DomageBlink = 0.3;
    m_HitCouldown = 1;
    m_domageClock.restart();

    m_isAlive = true;
    m_isDying = false;

    m_point = 250;
    m_givePoint = false;
}
void punchRabbit::updateAnim()
{

if(m_isAlive)
{



if(this->m_goToBeat == false)
        if(this->m_animTimeClock.getElapsedTime().asSeconds() > this->m_animTime)
    {
        this->m_animAv++;
        if(this->m_animAv >= this->m_animMapTab[this->m_etat].size())
            this->m_animAv = 0;
        this->m_animTimeClock.restart();
        this->m_sprite.setTextureRect(sf::IntRect(this->m_animMapTab[this->m_etat][this->m_animAv].getTab()[0],
                                                  this->m_animMapTab[this->m_etat][this->m_animAv].getTab()[1],this->m_animMapTab[this->m_etat][this->m_animAv].getTab()[2],
                                                  this->m_animMapTab[this->m_etat][this->m_animAv].getTab()[3]));
    }
}

}
void punchRabbit::updateCollision(std::vector<plateforme>& plList,Vue& vue,std::vector<blocusAdv>& BadvList)
{
if(m_isAlive == true && this->m_isDying == false)
{
        if(this->m_goToBeat == true)
        {
            if(this->m_beatClock.getElapsedTime().asSeconds() > this->m_goToBeatTime)
            {
                this->m_goToBeat = false;
                this->m_isBeating = true;
                if(this->m_orientation == "DROITE")
                    this->m_etat = "attack_right";
                else
                    this->m_etat = "attack_left";

                this->m_beatClock.restart();
            }

        }
        if(this->m_isBeating)
        {

            if(this->m_beatClock.getElapsedTime().asSeconds() > this->m_beatTime)
            {
                this->m_isBeating = false;
                if(this->m_orientation == "DROITE")
                    this->m_etat = "run_right";
                else
                    this->m_etat = "run_left";"attack_left";

            }


        }


        for(int e = 0;e< BadvList.size();e++)
        {
            if(this->m_box.boxCollision(BadvList[e]))
                this->m_vitesse *=-1;
                        if(this->m_isBeating == false && this->m_goToBeat == false)
            {
                if(this->m_orientation == "DROITE")
                    this->m_etat = "run_right";
                else
                    this->m_etat = "run_left";


            }
        }
        this->updateAnim();
        this->gravity(plList);
        this->mouv(plList);
        this->updateOrientation();
        this->m_colD = false;
        this->m_sprite.setPosition(this->m_box.getPosX() - this->m_box.getSizeX()/2,this->m_box.getPosY() -(this->m_animMapTab[this->m_etat][0].getTab()[3] - this->m_box.getSizeY()));
        if(this->m_box.boxCollision(vue))
            environement::m_window.draw(this->m_sprite);







            if(this->m_beHit)
    {
        if(this->m_domageClock.getElapsedTime().asSeconds() >= this->m_DomageBlink)
        {
                if(this->m_colorChange)
                {

                    this->m_colorChange = false;
                    this->m_sprite.setColor(sf::Color(255,0,0,125));
                }
                else
                {

                    this->m_colorChange = true;
                    this->m_sprite.setColor(sf::Color(255,255,255,125));
                }
            this->m_domageBlinckClock.restart();
        }

        if(this->m_domageClock.getElapsedTime().asSeconds() >= this->m_HitCouldown)
        {
            this->m_beHit = false;
            this->m_domageClock.restart();
            this->m_sprite.setColor(sf::Color(255,255,255));
        }

    }


}
if(this->m_isDying == true  && this->m_isAlive == true)
{
    if(this->m_deathClock.getElapsedTime().asSeconds() > 2)
        this->m_isAlive = false;
    environement::m_window.draw(this->m_sprite);

}
}
std::vector<int> punchRabbit::update(hitBox& colBox,bool persoIsHiting,int persoDommage,hitBox& persoWeaponBox)
{
    std::vector<int> coupleScoreDommage;
if(!this->m_givePoint)
    coupleScoreDommage.push_back(0);
else
{
     coupleScoreDommage.push_back(this->m_point);
    this->m_givePoint = false;
}
    if(this->m_box.boxCollision(colBox) == true && this->m_goToBeat == false)
    {
        this->m_goToBeat = true;
        this->m_beatClock.restart();
        if(this->m_orientation == "GAUCHE")
            this->m_etat = "prepareBeat_left";
        else
             this->m_etat = "prepareBeat_right";
        this->m_sprite.setTextureRect(sf::IntRect(this->m_animMapTab[this->m_etat][0].getTab()[0],
                                                  this->m_animMapTab[this->m_etat][0].getTab()[1],this->m_animMapTab[this->m_etat][0].getTab()[2],
                                                  this->m_animMapTab[this->m_etat][0].getTab()[3]));
            this->m_sprite.move(0,-(this->m_animMapTab[this->m_etat][0].getTab()[3] - this->m_box.getSizeY()));
    }
    if(persoIsHiting)
    {
        if(this->m_box.boxCollision(persoWeaponBox))
            this->hit(persoDommage);

    }
    if(this->m_isBeating)
    {
        if(this->m_box.boxCollision(colBox))
            coupleScoreDommage.push_back(this->m_dommage);
    }
    else
        coupleScoreDommage.push_back(0);

    return coupleScoreDommage;
}
void punchRabbit::hit(int dommage)
{
        if(this->m_beHit == false)
        this->m_life -= dommage;
        if(this->m_life <= 0 && this->m_isDying == false && this->m_isAlive == true)
                this->kill();
        else if(this->m_beHit == false)
        {
                this->m_beHit = true;
                this->m_domageClock.restart();
                this->m_domageBlinckClock.restart();
                this->m_sprite.setColor(sf::Color(255,0,0,125));
        }
}
void punchRabbit::kill()
{
            this->m_isBeating = false;
            this->m_givePoint = true,
            this->m_sprite.setTextureRect(sf::IntRect(this->m_animMapTab["death"][0].getTab()[0],
                                                  this->m_animMapTab["death"][0].getTab()[1],this->m_animMapTab["death"][0].getTab()[2],
                                                  this->m_animMapTab["death"][0].getTab()[3]));
            this->m_isDying = true;
            this->m_deathClock.restart();
            this->m_sprite.move(0,this->m_box.getSizeY() - this->m_animMapTab["death"][0].getTab()[3] );
            this->m_sprite.setColor(sf::Color(255,255,255));


}
void punchRabbit::updateOrientation()
{

    if(this->m_vitesse > 0)
        this->m_orientation = "DROITE";
    else
        this->m_orientation = "GAUCHE";






}
void punchRabbit::gravity(std::vector<plateforme>& obs)//même gestion de mouvement que pour le personnage principale
{
        this->m_box.moveHB(0,this->m_attractionForce);




    //si l'entité n'est pas en collision avec le sol , il subi un mouvement vers le bas qui augmente de 1 tout this->m_applyforce jusqu'a atteindre sa valeur max this->m_force
        if(this->m_colD == false)
        {
        if(this->m_attractionForce < this->m_force && this->m_applyforceClock.getElapsedTime().asSeconds() > this->m_applyforce)
            {
                this->m_attractionForce += 1;
                this->m_applyforceClock.restart();
            }
        this->m_box.moveHB(0,this->m_attractionForce);
        }






    for(int e = 0;e < obs.size() ; e++)
    {
        if(this->m_box.boxCollision(obs[e].getColBox()) == true)
        {
                if(obs[e].isMoving())
                    this->m_box.moveHB(obs[e].getVitX(),obs[e].getVitY());
                this->m_colD = true;
                this->m_box.moveHB(0,-((this->m_box.getPosY() + this->m_box.getSizeY()) - obs[e].getPosY()) - 1);
            e = obs.size();
        }



    }



    //si il y a collision avec le sol -> restart de la gravité
    if(this->m_colD == true)
        this->m_attractionForce = 1;

}
void punchRabbit::mouv(std::vector<plateforme>& obs)//même gestion de mouvement que pour le personnage principale
{

        if(this->m_goToBeat == false && this->m_isBeating == false)
    {
        this->m_sprite.move(this->m_vitesse,0);
        this->m_box.moveHB(this->m_vitesse,0);
    }
        //verifie les collisiont avec les plateformes
    for(int i = 0;i < obs.size();i++)
    {
                    //si collision
        if(this->m_box.boxCollision(obs[i].getColBox()))
        {

            if(this->m_vitesse < 0)
            {
                this->m_box.moveHB((obs[i].getPosX() + obs[i].getSizeX()) -  this->m_box.getPosX() + 5,0);
            }
            if(this->m_vitesse > 0)
            {
                this->m_box.moveHB(-((this->m_box.getPosX() + this->m_box.getSizeX()) - obs[i].getPosX()) - 5,0 );
            }
            i = obs.size();
            this->m_vitesse *=-1;
            if(this->m_isBeating == false && this->m_goToBeat == false)
            {
                if(this->m_orientation == "DROITE")
                    this->m_etat = "run_right";
                else
                    this->m_etat = "run_left";


            }
        }
    }
    this->m_sprite.setPosition(this->m_box.getPosX(),this->m_box.getPosY());




}

punchRabbit::~punchRabbit()
{
    //dtor
}
