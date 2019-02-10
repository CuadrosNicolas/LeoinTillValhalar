#include "panda.h"

panda::panda(float posX,float posY) : adversaire(posX,posY) , m_laser(posX,posY,100,sf::Color::White)
{

    m_laserPos = fonction::loadBoxTab("data/Animations/LaserPos.txt");
    m_sprite.setTexture(generalTexture::textureList["panda"]);
    m_sprite.setPosition(posX,posY);
    m_animMapTab = fonction::loadAnim("data/Animations/pandAnim.txt");
    m_sprite.setTextureRect(sf::IntRect(this->m_animMapTab["wait"][0].getTab()[0],this->m_animMapTab["wait"][0].getTab()[1],
                                        this->m_animMapTab["wait"][0].getTab()[2],this->m_animMapTab["wait"][0].getTab()[3]));
    m_box = hitBox(posX,posY,this->m_animMapTab["wait"][0].getTab()[2],this->m_animMapTab["wait"][0].getTab()[3]);



    m_force = 35;
    m_applyforceClock.restart();
    m_attractionForce = m_force;
    m_applyforce = 0.02;
    m_colD = false;

    m_beHit = false;
    m_colorChange = false;
    m_DomageBlink = 0.3;
    m_HitCouldown = 1;
    m_domageClock.restart();
    m_domageBlinckClock.restart();

        m_goToBeat = false;
        m_isDead = false;
        m_givePoint = false;
         m_isActive = false;
         m_isAttack = false;
         m_isPausing = false;
         m_isBlocking = false;

         m_isFlying = false;
         m_isFlyingTAdvBlocus = false;
         m_goToFly = false;
         m_goToFlyTime = 1;
         m_goToLaserTime = 1;
         m_laserTime = 2;
         m_isGoToLaser = false;
         m_isLaser = false;

         m_life = 150;
         m_point = 5000;


         m_pauseTime = 3;
         m_attackTime = 1;
         m_goToBeatTime = 1;
    m_etat = "wait";
    m_animAv = 0;
    int posXBB(posX  - 450);
    m_spawn = hitBox(posX + 25,posY +25,50,50);
    m_spawn.setPositionByCenter(posX + 200,posY + 100);
    for(int e = 0;e<3;e++)
    {
        m_blackBirdList.push_back(BlackBird(posXBB,posY - 1500));
        posXBB += 150;
    }
    m_dommageBox = hitBox(posX,posY,this->m_animMapTab[this->m_etat][0].getTab()[2]*1.5,this->m_animMapTab[this->m_etat][0].getTab()[3]*1.5);
    m_dommageBox.reSize(this->m_animMapTab[this->m_etat][0].getTab()[2]*1.5,this->m_animMapTab[this->m_etat][0].getTab()[3]*1.5);
    m_dommageBox.setPositionByCenter(this->m_box.getPosX() + this->m_box.getSizeX()/2,this->m_box.getPosY() + this->m_box.getSizeY()/2);
}
void panda::gravity(std::vector<plateforme>& obs)
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






    for(int e = 0;e < obs.size() ;e++)
    {
        if(this->m_box.boxCollision(obs[e].getColBox()) == true && obs[e].isHiting() == false)
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
void panda::updateCollision(std::vector<plateforme>& plList,Vue& vue,std::vector<blocusAdv>& BadvList)
{

    if(this->m_isDead)
            environement::m_theEnd = true;
    if(!this->m_isDead)
    {
        if(this->m_isFlying)
        {
            if(!this->m_isFlyingTAdvBlocus)
            {
                for(int e = 0;e<BadvList.size();e++)
                {
                    if(this->m_box.boxCollision(BadvList[e]))
                    {
                        this->m_isFlyingTAdvBlocus = true;
                                   this->m_animAv = 1;
                    }
                }
            }
            else
            {
                if(this->m_dommageBox.boxCollision(this->m_spawn))
                {
                    this->m_isFlyingTAdvBlocus = false;
                    this->m_isFlying = false;
                    this->m_etat = "laser";
                    this->m_controlClock.restart();
                    this->m_animAv = 0;
                    this->m_isGoToLaser = true;

                }
            }

        }

        for(int e = 0;e< this->m_blackBirdList.size();e++)
            this->m_blackBirdList[e].updateCollision(plList,vue,BadvList);
    if(!this->m_isFlying)
        this->gravity(plList);
        this->m_colD = false;
        if(this->m_isDead == false)
        this->m_sprite.setPosition(this->m_box.getPosX(),this->m_box.getPosY());
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

        this->m_sprite.setTextureRect(sf::IntRect(this->m_animMapTab[this->m_etat][this->m_animAv].getTab()[0],
                                                  this->m_animMapTab[this->m_etat][this->m_animAv].getTab()[1],this->m_animMapTab[this->m_etat][this->m_animAv].getTab()[2],
                                                  this->m_animMapTab[this->m_etat][this->m_animAv].getTab()[3]));
                    this->m_sprite.move(0,this->m_box.getSizeY() - this->m_animMapTab[this->m_etat][0].getTab()[3] );
        this->m_dommageBox.reSize(this->m_animMapTab[this->m_etat][0].getTab()[2],this->m_animMapTab[this->m_etat][0].getTab()[3]*1.2);
    this->m_dommageBox.setPositionByCenter(this->m_box.getPosX() + this->m_box.getSizeX()/2,this->m_box.getPosY() + this->m_box.getSizeY()/2);
    if(this->m_isFlyingTAdvBlocus)
        this->m_dommageBox.moveHB(50,0);
    }
    if(this->m_isLaser)
    {
        this->m_laser.setPos(this->m_sprite.getPosition().x + this->m_laserPos["laser"][1].x,this->m_sprite.getPosition().y + this->m_laserPos["laser"][1].y);
        this->m_laser.update(vue);
    }
    environement::m_window.draw(this->m_sprite);
if(this->m_isLaser)
    this->m_laser.draw();





}



std::vector<int> panda::update(hitBox& colBox,bool persoIsHiting,int persoDommage,hitBox& persoWeaponBox)
{

        std::vector<int> coupleScoreDommage;
        coupleScoreDommage.push_back(0);
        coupleScoreDommage.push_back(0);
if(!this->m_isDead)
{


    if( (this->m_dommageBox.boxCollision(colBox) == true || this->m_box.boxCollision(persoWeaponBox) == true  )
         && this->m_goToBeat == false && this->m_isAttack == false && this->m_isFlying == false && this->m_isPausing == false && this->m_isGoToLaser == false && this->m_isLaser == false)
    {
        this->m_goToBeat = true;
        this->m_controlClock.restart();
    }
    if(this->m_goToBeat)
    {
        if(this->m_controlClock.getElapsedTime().asSeconds() > this->m_goToBeatTime)
        {
            this->m_isAttack = true;
            this->m_goToBeat = false;
            this->m_controlClock.restart();
            this->m_etat = "attack";

        }
    }
    if(this->m_isAttack == true && this->m_controlClock.getElapsedTime().asSeconds() > this->m_attackTime)
    {
        this->m_isAttack = false;
        this->m_controlClock.restart();
        this->m_etat = "block";
        this->m_isPausing = true;
        for(int e = 0;e< this->m_blackBirdList.size();e++)
            this->m_blackBirdList[e].Active();


    }
    if(this->m_isPausing)
    {
        if(this->m_controlClock.getElapsedTime().asSeconds() > this->m_pauseTime)
        {
            this->m_etat = "wait";
            this->m_isPausing = false;
            this->m_goToFly = true;
           this->m_controlClock.restart();
        }
    }
    if(this->m_goToFly == true && (this->m_controlClock.getElapsedTime().asSeconds() > this->m_goToFlyTime))
       {
           this->m_goToFly = false;
           this->m_isFlying = true;
           this->m_controlClock.restart();
           this->m_etat = "fly";
           this->m_animAv = 0;
            this->m_sprite.move(0,-20);
            this->m_box.moveHB(0,-20);
       }
    if(this->m_isFlying)
    {
        if(!this->m_isFlyingTAdvBlocus)
        {
            this->m_sprite.move(-20,0);
            this->m_box.moveHB(-20,0);
        }
        else
           {
            this->m_sprite.move(20,0);
            this->m_box.moveHB(20,0);
            }

    }
    if(this->m_isGoToLaser == true && this->m_controlClock.getElapsedTime().asSeconds() > this->m_goToLaserTime)
    {
        this->m_animAv = 1;
        this->m_isLaser = true;
        this->m_isGoToLaser = false;
        this->m_controlClock.restart();
    }
    if(this->m_isLaser)
    {

        if(this->m_laser.LaserCol(colBox))
                coupleScoreDommage[1] += 50;
        if(this->m_controlClock.getElapsedTime().asSeconds() > this->m_laserTime)
        {
            this->m_animAv  = 0;
            this->m_etat = "wait";
            this->m_controlClock.restart();
            this->m_isLaser = false;
        }

    }
    if( (this->m_isAttack == true || this->m_isFlying == true) &&
        (this->m_dommageBox.boxCollision(colBox) == true)
            && this->m_isGoToLaser == false && this->m_isLaser == false)
        coupleScoreDommage[1] += 10;



    if(persoIsHiting == true && this->m_isFlying == false && this->m_isDead == false && this->m_isPausing == false)
    {
        if(this->m_box.boxCollision(persoWeaponBox))
            this->hit(persoDommage);

    }

    if(this->m_givePoint)
    {
        coupleScoreDommage[0] = this->m_point;
        this->m_givePoint = false;
    }
    for(int e = 0;e< this->m_blackBirdList.size();e++)
    {
        if(this->m_blackBirdList[e].getBox().boxCollision(colBox))
            coupleScoreDommage[1] += this->m_blackBirdList[e].getDommage();
    }

}
    return coupleScoreDommage;
}
void panda::hit(int dommage)
{
        if(this->m_beHit == false)
        this->m_life -= dommage;
        if(this->m_beHit == false)
        {
                this->m_beHit = true;
                this->m_domageClock.restart();
                this->m_domageBlinckClock.restart();
                this->m_sprite.setColor(sf::Color(255,0,0,125));
        }
        if(this->m_life <= 0 && this->m_isDead == false)
                this->kill();
}
void panda::kill()
{
            this->m_givePoint = true;
            this->m_isDead = true;
            this->m_etat = "dead";
            this->m_animAv = 0;
            this->m_goToBeat = false;
            this->m_goToFly = false;
            this->m_isAttack = false;
            this->m_isLaser = false;
            this->m_isPausing = false;
            this->m_isBlocking = false;
        this->m_sprite.setTextureRect(sf::IntRect(this->m_animMapTab[this->m_etat][0].getTab()[0],
                                                  this->m_animMapTab[this->m_etat][0].getTab()[1],this->m_animMapTab[this->m_etat][0].getTab()[2],
                                                  this->m_animMapTab[this->m_etat][0].getTab()[3]));
                    this->m_sprite.move(0,this->m_box.getSizeY() - this->m_animMapTab[this->m_etat][0].getTab()[3] );
            this->m_sprite.setColor(sf::Color(255,255,255));
            this->m_controlClock.restart();
}
panda::~panda()
{
    //dtor
}
