#include "perso.h"
perso::perso()
{

}

perso::perso(float posX,float posY)
{
    //met � 0 les �tats du personnages
    m_isChangeLevel = false;
    m_end = false;
    m_dead = false;
    m_attack = false;
    //desactivation des mouvements
    m_mouvR = false;
    m_mouvL = false;
    m_colD = false;
    m_jumpActive = false;
    m_beHit = false;
    //d�claration des diff�rents type d'�tat
    m_run_left = "run_left";
    m_run_right = "run_right";
    m_wait_left = "wait_left";
    m_wait_right = "wait_right";
    m_jump_left = "jump_left";
    m_jump_right = "jump_right";
    m_attack_left = "attack_left";
    m_attack_right = "attack_right";

    //d�finit son etat de d�part
    m_etat = m_wait_right;
    //d�finit son orientation de d�part
    m_orientation = "DROITE";

    //d�claration les diff�rents temps d'animations en fonction de l'�tat
    m_animTimeTab[m_attack_left] = 0.08;
    m_animTimeTab[m_attack_right] = 0.08;
    m_animTimeTab[m_run_left] = 0.05;
    m_animTimeTab[m_run_right] = 0.05;
    m_animTimeTab[m_wait_left] = 0.05;
    m_animTimeTab[m_wait_right] = 0.05;
    m_animTimeTab[m_jump_left] = 0.05;
    m_animTimeTab[m_jump_right] = 0.05;

    //chargement des animations
    m_animMapTab = fonction::loadAnim("data/Animations/persoAnim.txt");
    //chargement des positions de la hitbox de l'arme en fonction de l'animation
    m_weaponBoxTab = fonction::loadBoxTab("data/Animations/persoHitBoxPosData.txt");
    //remise a 0 de l'horloge d'animation et mise en place de l'intervalle en chaque "image" de l'animation
    m_animClock.restart();



    //mise en position de l'entit�
    m_posX = posX;
    m_posY = posY;
    m_sprite.setPosition(m_posX,m_posY);
    m_checkPointX = posX;
    m_checkPointY = posY;

    //chargement de la texture de l'entit� � partir de generalTexture
    m_texture = &generalTexture::persoText;
    m_sprite.setTexture(*m_texture);



    //mise en place des forces et des horloges qui les g�rent
    m_force = 30;
    m_vitesse = 15;
    m_jumpForceTotale = 25;
    m_attractionForce = m_force;
    m_applyforce = 0.01;
    //on met � jour le sprite du joueur en fonction de l'animation de d�part
    m_sprite.setTextureRect(sf::IntRect(this->m_animMapTab[this->m_wait_right][0].getTab()[0],this->m_animMapTab[this->m_wait_right][0].getTab()[1],
                                        this->m_animMapTab[this->m_wait_right][0].getTab()[2],this->m_animMapTab[this->m_wait_right][0].getTab()[3]));
    //etat de d�part = attente vers la droite
    m_etat = this->m_wait_right;
    //avancement de l'animation de base = premi�re partie de l'animation
    m_animAv = 0;
    //creation des hitbox de l'entit�
    m_colBox = hitBox(posX,posY,m_animMapTab[m_run_right][0].getTab()[2],m_animMapTab[m_run_right][0].getTab()[3]);
    m_weaponBox = hitBox(posX,posY,45,45);
    m_dommageBox = hitBox(posX,posY,25,40);

    m_score = 0;//met � 0 le score
    m_lifeMax = 50;//d�finit la vie maximum du joueur
    m_life = m_lifeMax;//et lui d�finit comme vie de d�part
    m_dommage = 25;//d�finit les d�g�ts qu'il inflige
    m_live = 2;//d�finit son nombre de vie
    //diff�rents temps
    m_mouvTime = 1/50;//entre 2 mouvemets
    m_DomageBlink = 0.3;//entre 2 clignotement
    m_HitCouldown = 2;//entre 2 possibilit� d'�tre attaqu�
    //chargement du HUD du joueur(sant�,vie,score)
    m_lifeText.setFont(generalTexture::TextFont);
    m_sprite.setColor(sf::Color(255,255,255));
    m_lifeBoard.setTexture(generalTexture::textureList["lifeBoard"]);
    m_lifeLigne.setTexture(generalTexture::textureList["lifeLine"]);
    m_scoreText.setFont(generalTexture::TextFont);

    m_check = 0;//met � 0 le pointeur vers un checkpoint

    //remet � 0 les horloges
    m_fallingClock.restart();
    m_mouvClock.restart();
    m_domageClock.restart();
    m_applyforceClock.restart();
}

void perso::event()
{

                this->m_mouvL = false;//remet � 0 les variables de mouvements
                this->m_mouvR = false;
//si les touches gauche et/ou droite son pr�ss� on active le mouvement gauche et/ou droit

            if(!this->m_attack)
            {
                //si presse la fl�che gauche , on met l'orientation du personnage � gauche
                 if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                 {
                    this->m_orientation = "GAUCHE";
                //si son saut est activ� on met l'etat qui lui convient(saut gauche ou saut droit)
                if(!this->m_jumpActive)
                    this->setEtat(this->m_run_left);
                else
                    this->setEtat(this->m_jump_left);
                    //active le mouvement � gauche
                    this->m_mouvL = true;
                 }

                 else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                                    //si presse la fl�che droite , on met l'orientation du personnage � droite
                    this->m_orientation = "DROITE";
                                    //si son saut est activ� on met l'etat qui lui convient(saut gauche ou saut droit)
                if(!this->m_jumpActive)
                    this->setEtat(this->m_run_right);
                else
                    this->setEtat(this->m_jump_right);
                        //active le mouvement � droite
                    this->m_mouvR = true;
                }
                //si aucune touche n'est pr�ss� on le met en position d'attente vers son orientation actuel
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)==false && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)==false)
                {
                    if(this->m_orientation == "DROITE")
                         this->setEtat(this->m_wait_right);
                    else
                         this->setEtat(this->m_wait_left);
                }
                //si les touches gauche et droite son pr�ss� on le dirige vers la droite et en position d'attente
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) == true && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)==true && this->m_jumpActive == false && sf::Keyboard::isKeyPressed(sf::Keyboard::Space) == false )
                {
                    this->m_orientation = "DROITE";
                     this->setEtat(this->m_wait_right);
                    this->m_mouvL = false;
                    this->m_mouvR = false;
                }
                //activation du jump si la touche espace est pr�ss�
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                {
                    //si il n'est pas d�j� activ� et si il y a collision avec le sol
                    if(this->m_jumpActive == false&& this->m_colD == true)
                {
                    this->m_jumpActive = true;
                    this->m_jumpForce = this->m_jumpForceTotale;
                    this->m_attractionForce = 1;
                }
                }
            }   //si l'utilisateur presse la touche D alors il attaque
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && this->m_attack == false)
                 {
                     this->m_animAv = 0;
                    this->m_attack = true;
                    if(this->m_orientation == "GAUCHE")
                        this->m_etat = this->m_attack_left;
                    else
                        this->m_etat = this->m_attack_right;
                 }

}
void perso::gravity(std::vector<plateforme>& obs)
{
        //si le saut est activ� on bouge le joueur vers le haut
        if(this->m_jumpActive)
         this->m_colBox.moveHB(0,-this->m_jumpForce);
        //puis applique la gravit�
        this->m_colBox.moveHB(0,this->m_attractionForce);

        if(this->m_jumpActive)//si le saut est activ�
        {
            //si la force du jump est sup�rieur a 0 et que le temps est �coul� l'on le r�duit de 2
            if(this->m_jumpForce > 0 && this->m_applyforceClock.getElapsedTime().asSeconds() > this->m_applyforce)
                    this->m_jumpForce -= 2.0;
            //si il y a collisiont avec le sol on arr�te le saut le saut
            if((this->m_attractionForce >= this->m_force && this->m_jumpForce <= 0 && this->m_colD == true) )
            {

                this->m_jumpActive = false;
                this->m_attractionForce = this->m_force;
                this->m_jumpForce = 0;
            }
            this->m_colBox.moveHB(0,-this->m_jumpForce);
        }
    //si l'entit� n'est pas en collision avec le sol , il subi un mouvement vers le bas qui augmente de 1 tout this->m_applyforce jusqu'a atteindre sa valeur max this->m_force
        if(this->m_colD == false)
        {
        if(this->m_attractionForce < this->m_force && this->m_applyforceClock.getElapsedTime().asSeconds() > this->m_applyforce)
            {
                this->m_attractionForce += 1;
                this->m_applyforceClock.restart();
            }
        this->m_colBox.moveHB(0,this->m_attractionForce);
        }





    for(int e = 0;e < obs.size() ; e++)
    {
            if(!obs[e].isHiting())//si elle n'inflige pas de d�gats
    {

        if(this->m_colBox.boxCollision(obs[e].getColBox()))//si il est en collision avec
        {
            //si elle bouge , bouge le personnage avec
            if(obs[e].isMoving())
                    this->m_colBox.moveHB(obs[e].getVitX(),obs[e].getVitY());
            if(this->m_jumpActive)//si le saut est activ� on teste si il monte ou descend
            {
                    if(this->m_attractionForce - this->m_jumpForce > 0)//si la force d'attraction est sup�rieur � la force du saut on en d�duit qu'il descend
                {
                    //donc collision avec le sol
                    this->m_colD = true;
                    this->m_colBox.moveHB(0,-((this->m_colBox.getPosY() + this->m_colBox.getSizeY()) - obs[e].getPosY()) - 1);
                    //d�sactive le saut
                    this->m_jumpActive = false;

                }
                else//sinon il monte
                {
                    this->m_jumpActive = false;
                    this->m_colBox.moveHB(0,(obs[e].getPosY() + obs[e].getSizeY()) -  this->m_colBox.getPosY() + 1);
                }
            }
            else//sinon en d�duit qu'il descend forcement
            {
                this->m_colD = true;
                this->m_colBox.moveHB(0,-((this->m_colBox.getPosY() + this->m_colBox.getSizeY()) - obs[e].getPosY()) - 1);

            }


            e = obs.size();
        }



    }
    }
    //si il y a collision avec le sol -> restart de la gravit�
    if(this->m_colD == true && this->m_jumpActive == false)
        this->m_attractionForce = 1;
}

//gestion des mouvements
void perso::mouv(std::vector<plateforme>& obs)
{



if(this->m_mouvClock.getElapsedTime().asSeconds() > this->m_mouvTime)//si il le temps suffisant � leur faire bouger est pass�
{

    //le fais bouger en fonction de son mouvement actuel
    if(this->m_mouvL)
        this->m_colBox.moveHB(-this->m_vitesse,0);
    if(this->m_mouvR)
        this->m_colBox.moveHB(this->m_vitesse,0);

    this->m_mouvClock.restart();

}


        //verifie les collisiont avec les plateformes
    for(int i = 0;i < obs.size();i++)
    {
                    //si collision
    if(!obs[i].isHiting())//si elle n'inflige pas de d�gats
    {

        if(this->m_colBox.boxCollision(obs[i].getColBox()))
        {
        //si elle bouge , on bouge le personnage avec
            if(obs[i].isMoving())
                this->m_colBox.moveHB(obs[i].getVitX(),0);
                //en fonction du mouvement du personnage , il se d�cale de la plateforme pour s'align� avec
            if(this->m_mouvL)
            {
                this->m_colBox.moveHB((obs[i].getPosX() + obs[i].getSizeX()) -  this->m_colBox.getPosX() + 5,0);
                this->m_mouvL = false;
            }
            if(this->m_mouvR)
            {
                this->m_colBox.moveHB(-((this->m_colBox.getPosX() + this->m_colBox.getSizeX()) - obs[i].getPosX()) - 5,0 );
                this->m_mouvR = false;
            }
            i = obs.size();

        }
    }
    else{//sinon inflige les d�gats en cas de collision
            if(this->m_colBox.boxCollision(obs[i].getColBox()) == true)
                this->hit(obs[i].getDomage());



        }


    }
}


bool perso::update(std::vector<plateforme>& obs,
                   sf::RenderWindow& window,Vue& view,std::vector<piece>& pieceList,std::vector<checkpoint>& checkList,std::vector<adversaire*>& advList)
{
//remet � 0 sa perte de vie
this->m_dead = false;


    this->gravity(obs);//mise � jour des mouvements verticaux
    this->mouv(obs);//mise � jour des mouvements horizontaux
    this->event();//mise � jour des �v�nements
    this->updateAnim();//met � jour l'animaiton

    //on cr�e un couple de score/dommage pour mettre � jour les collisions avec les adversaires
    std::vector<int> coupleScoreDommage;
        for(int e = 0;e<advList.size();e++)
        {
            if(advList[e] !=0)
            {
                //met avec � jour les collisions avec les adversaires
            coupleScoreDommage = advList[e]->update(this->m_dommageBox,this->m_attack,this->m_dommage,this->m_weaponBox);
        this->hit(coupleScoreDommage[1]);//lui inflige les dommage relatif � la collision avec les adversaires
        this->m_score+= coupleScoreDommage[0];//incr�mente son score si il � ilimin� un adversaire
            }
        }
    //test les collisions avec les checkpoints
    for(int e = 0;e<checkList.size();e++)
    {
        if(this->m_colBox.boxCollision(checkList[e].getBox()))
        {
            this->m_check = &checkList[e];
            if(this->m_check != 0)
            {
            this->m_check->active();
            }

        }
    }
    for(int e = 0;e<pieceList.size();e++)//collision avec les pi�ces
    {
        if(this->m_colBox.boxCollision(pieceList[e]) == true && pieceList[e].isActive() == true)
        {
            this->m_score += 50;//incr�mentation du score si il y a collision
            pieceList[e].desactive();//d�sactive la pi�ce pour ne plus pouvoir entr� en collision avec
        }
    }
        //si on est en collision avec le sol on remet � 0 l'horloge de chute
        if(this->m_colD == true)
            this->m_fallingClock.restart();
        //remet � 0 la collision avec le sol
          this->m_colD = false;
        //si il tombe depuis plus de 3 secondes et qu'il ne change pas de niveau alors on ilimine le joueur
        if(this->m_fallingClock.getElapsedTime().asSeconds() > 5  && this->m_isChangeLevel == true)
        {
            this->m_fallingClock.restart();
            this->kill();
        }
    this->updateScore(environement::m_window,view);//on met � jour le score
    this->draw(window);//on le dessine
    return this->m_dead;//on renvoie si le joueur est ilimin� ou non

}

void perso::draw(sf::RenderWindow& screen)
{
        //dessin du personnage , de sa barre de vie et des textes de score et de vie
        screen.draw(this->m_sprite);
        screen.draw(this->m_lifeLigne);
        screen.draw(this->m_lifeBoard);
        screen.draw(this->m_scoreText);
        screen.draw(this->m_lifeText);



}
void perso::kill()
{
    //remise � 0 des valeurs
    this->m_jumpActive = false;
    this->m_attractionForce = 1;
//si il n'a pas atteint de checkpoint on le repositionne au d�but
if(this->m_check == 0)
    this->setPos(this->m_checkPointX,this->m_checkPointY);
else//sinon  repositionnement au dernier checkpoint atteint
    this->setPos(this->m_check->getBox().getPosX(),this->m_check->getBox().getPosY());

    //on remet toute sa sant� au personnage
    this->m_life = this->m_lifeMax;
    //on lui enl�ve 1 vie
    this->m_live -=1;
    //si il n'a plus de vie on d�clare que le joueur a finis la partie
    if(this->m_live <0)
    {
        this->m_end = true;
        this->m_dead = false;
    }
    else
    this->m_dead = true;//sinon on d�clare qu'il a juste perdu 1 vie

    //reinitialise l'horloge de chute
    this->m_fallingClock.restart();


}
//mise � jour de l'affichage du score
void perso::updateScore(sf::RenderWindow& window ,Vue& view)
{

        //remet en position les textes (en haut � gauche de l'�cran
        this->m_scoreText.setPosition(view.getView().getCenter().x - view.getView().getSize().x/2,
                                view.getView().getCenter().y - view.getView().getSize().y/2);
    this->m_lifeText.setPosition(view.getView().getCenter().x - view.getView().getSize().x/2,
                                view.getView().getCenter().y - view.getView().getSize().y/2 + 100);
    //remet en position la barre de vie
    this->m_lifeBoard.setPosition(view.getView().getCenter().x - view.getView().getSize().x/2,
                                view.getView().getCenter().y - view.getView().getSize().y/2);
    this->m_lifeLigne.setPosition(this->m_lifeBoard.getPosition().x + generalTexture::textureList["lifeBoard"].getSize().x/2 - generalTexture::textureList["lifeLine"].getSize().x/2
                                  ,this->m_lifeBoard.getPosition().y);
    //mise � jour de la barre de vie en fonction de la vie actuel du joueur
    this->m_lifeLigne.setTextureRect(sf::IntRect(0,0,generalTexture::textureList["lifeLine"].getSize().x * this->m_life/this->m_lifeMax ,100));


    //entre les valeur dans les textes affichables
    this->m_scoreText.setString("score : " + fonction::convertToString<int>(this->m_score));
    this->m_lifeText.setString("vie : " + fonction::convertToString<int>(this->m_live));





}
void perso::hit(int dommage)
{
                //si les dommage inflig� son sup�rieur � 0 on le fais clignot�
                if(dommage > 0 && this->m_beHit == false)
                {
                this->m_life -= dommage;
                this->m_beHit = true;
                this->m_domageClock.restart();
                this->m_domageBlinckClock.restart();
                this->m_sprite.setColor(sf::Color(255,0,0,125));
                }
                else if(dommage < 0)//sinon on lui rend de la sant�
                    this->m_life -= dommage;

                //si sa sant� est inf�rieur � 0
                if(this->m_life <= 0)
                    this->kill();
                if(this->m_life > this->m_lifeMax)//si sa sant� est sup�rieur � son maximum on la remet � son maximum
                    this->m_life = this->m_lifeMax;

}
void perso::updateAnim()//mise � jour de l'animation
{
        //remet en position la hitbox de l'arme du joueur
        this->m_dommageBox.setPositionByCenter(this->m_colBox.getPosX()+(this->m_colBox.getSizeX()/2),
                                           this->m_colBox.getPosY()+(this->m_colBox.getSizeY()/2));
    //si d�passe le temps d'animation de la frame actuel
        if(this->m_animClock.getElapsedTime().asSeconds() > this->m_animTimeTab[this->m_etat])
    {
    //alors passe � la suivante
        this->m_animAv++;
    if(this->m_animAv >= this->m_animMapTab[this->m_etat].size())
    {
        this->m_animAv = 0;
        if(this->m_attack)
        {


            this->m_attack = false;
        if(this->m_orientation == "DROITE")
            {
                this->setEtat(this->m_wait_right);
            }
                else
            {
                this->setEtat(this->m_wait_left);
            }
        }

    }
        this->m_animClock.restart();
        //met � jour la partie de la texture affich�
        this->m_sprite.setTextureRect(sf::IntRect(this->m_animMapTab[this->m_etat][this->m_animAv].getTab()[0],
                                                  this->m_animMapTab[this->m_etat][this->m_animAv].getTab()[1],this->m_animMapTab[this->m_etat][this->m_animAv].getTab()[2],
                                                  this->m_animMapTab[this->m_etat][this->m_animAv].getTab()[3]));
    }
    //replace le sprite pour la centr� avec la hitbox
    if(this->m_orientation == "GAUCHE")
    this->m_sprite.setPosition((this->m_colBox.getPosX() + (this->m_animMapTab[this->m_etat][0].getTab()[2] - this->m_colBox.getSizeX()))
        ,this->m_colBox.getPosY());
    else
            this->m_sprite.setPosition(this->m_colBox.getPosX()
        ,this->m_colBox.getPosY());

        this->m_sprite.move(0,this->m_colBox.getSizeY() - this->m_animMapTab[this->m_etat][0].getTab()[3]);

                    //replace la hitbox de l'arme
                    this->m_weaponBox.setPositionByCenter(this->m_sprite.getPosition().x + this->m_weaponBoxTab[this->m_etat][this->m_animAv].x,
                                              this->m_sprite.getPosition().y + this->m_weaponBoxTab[this->m_etat][this->m_animAv].y);

    if(this->m_beHit)//si il a �t� attaqu�
    {
        if(this->m_domageClock.getElapsedTime().asSeconds() >= this->m_DomageBlink)
        {
            //clignotement du personnage
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
        //si d�pass� le temps de clignotement , on remet les valeurs � 0
        if(this->m_domageClock.getElapsedTime().asSeconds() >= this->m_HitCouldown)
        {
            this->m_beHit = false;
            this->m_domageClock.restart();
            this->m_sprite.setColor(sf::Color(255,255,255));
        }

    }

}

//diff�rent initilisateur de l'objet
void perso::setVictory()
{
    this->m_etat = "victory";
        this->m_sprite.setTextureRect(sf::IntRect(this->m_animMapTab[this->m_etat][0].getTab()[0],
                                                  this->m_animMapTab[this->m_etat][0].getTab()[1],this->m_animMapTab[this->m_etat][0].getTab()[2],
                                                  this->m_animMapTab[this->m_etat][0].getTab()[3]));
}
void perso::setPos(float posX,float posY)
{
    this->m_sprite.setPosition(posX,posY);
    this->m_colBox.setPosition(posX,posY);
    this->m_checkPointX = posX;
    this->m_checkPointY = posY;
    this->m_check = 0;
}
void perso::changeLevel()
{
    this->m_isChangeLevel = true;
    this->m_fallingClock.restart();
}
void perso::setScore(int score)
{
    this->m_score = score;
}
void perso::setEtat(std::string& etat)
{
    this->m_etat = etat;
}

//diff�rent r�cup�rateur de l'objet
sf::Sprite& perso::getSprite()
{
    return this->m_sprite;
}
hitBox& perso::getBox()
{
    return this->m_colBox;
}
float perso::getSizeX()
{
    return this->m_sizeX;
}

float perso::getSizeY()
{
    return this->m_sizeY;
}

float perso::getPosX()
{
    return this->m_sprite.getPosition().x;
}
float perso::getPosY()
{
    return this->m_sprite.getPosition().y;
}
int perso::getScore()
{
    return this->m_score;
}
bool perso::isEnd()
{
    return this->m_end;
}

perso::~perso()
{
    //dtor
}
