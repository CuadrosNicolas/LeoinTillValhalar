#include "niveau.h"

niveau::niveau() : m_levelEnd(0,0)
{

}
void niveau::load(const char* chemin)
{
            std::vector<std::string> tab;
            tab = fonction::loadData(chemin);//chargement du fichier du niveau dans un tableau de chaine de caractère
            int A(0);
            bool Av(false);
            while( A < tab.size())
            {

                Av = true;
                            if(A < tab.size())//puis rajoute les objets dans les différentes listes du niveau
                if((fonction::extract(tab[A]) == "plate") &&  (Av == true))//si c'est une plateforme
                {

                        //rajoute une plateforme à la liste de plateforme
                        this->m_obsList.push_back( plateforme( fonction::convertStrToFlo(tab[A + 1]) ,fonction::convertStrToFlo(tab[A + 2]) , &(generalTexture::textureList[tab[A]]),
                                                               fonction::convertStrToFlo(tab[A + 3]),tab[A + 4],fonction::convertStrToFlo(tab[A + 5])
                                                               ,fonction::convertStrToFlo(tab[A + 6]),fonction::convertStrToFlo(tab[A + 7])));
                        A +=8;
                        Av = false;

                }
                            if(A < tab.size())
                if((tab[A] == "piece") &&  (Av == true))//si c'est une pice
                {

                       //rajoute une piece à la liste de piece
                        this->m_pieceList.push_back( piece(fonction::convertStrToFlo(tab[A+1]),fonction::convertStrToFlo(tab[A+2])));
                        A +=3;
                        Av = false;

                }
                                            if(A < tab.size())
                if((fonction::extract(tab[A]) == "checkpoint") &&  (Av == true))//si c'est un checkpoint
                {

                        //rajoute un checkpoint à la liste de checkpoint
                        this->m_checkList.push_back(checkpoint(fonction::convertStrToFlo(tab[A+1]),fonction::convertStrToFlo(tab[A+2])));
                        A +=3;
                        Av = false;

                }
                            if(A < tab.size())
                                if((tab[A] == "levelEnd") &&  (Av == true))//si c'est une fin de niveau
                {

                        //on place la fin de niveau
                        this->m_levelEnd = fin_niveau(fonction::convertStrToFlo(tab[A+1]),fonction::convertStrToFlo(tab[A+2]));
                        A +=3;
                        Av = false;

                }
            if(A < tab.size())
                if((tab[A] == "spawn") && (Av == true) )//si c'est le point d'appartion du personnage
                {
                    //placement du point d'apparition du personnage
                    this->m_spawn = sf::Vector2f(fonction::convertStrToFlo(tab[A + 1]),fonction::convertStrToFlo(tab[A + 2]));
                    A += 3;
                    Av = false;

                }
            if(A < tab.size())
                if( (fonction::extract(tab[A]) == "blocus") &&  (Av == true) )//si c'est un blocus de plateforme
                {
                    //on test son nom
                    if(tab[A] == "blocus_Bup")//si c'est un blocus up
                        this->m_BlList.push_back(blocus_plateForme(fonction::convertStrToFlo(tab[A + 1]) ,fonction::convertStrToFlo(tab[A + 2]),"up"));
                    if(tab[A] == "blocus_Bdown")//si c'est un blocus down
                        this->m_BlList.push_back(blocus_plateForme(fonction::convertStrToFlo(tab[A + 1]) ,fonction::convertStrToFlo(tab[A + 2]),"down"));
                    if(tab[A] == "blocus_Bleft")//si c'est un blocus left
                        this->m_BlList.push_back(blocus_plateForme(fonction::convertStrToFlo(tab[A + 1]) ,fonction::convertStrToFlo(tab[A + 2]),"left"));
                    if(tab[A] == "blocus_Bright")//si c'est un blocus right
                        this->m_BlList.push_back(blocus_plateForme(fonction::convertStrToFlo(tab[A + 1]) ,fonction::convertStrToFlo(tab[A + 2]),"right"));

                A +=3;
                Av = false;

                }
            if(A < tab.size())
                if( (fonction::extract(tab[A]) == "blocusAdv") &&  (Av == true) )//si c'est un blocus d'adversaire
                {
                        //on rajoute un blocus d'adversaire à la liste de blocusAdv
                        this->m_BAdvList.push_back(blocusAdv(fonction::convertStrToFlo(tab[A + 1]) ,fonction::convertStrToFlo(tab[A + 2])));

                A +=3;
                Av = false;

                }
            if(A < tab.size())
                if( (fonction::extract(tab[A]) == "BackDecor") &&  (Av == true) )//si c'est un decor de fond
                {
                    this->m_BackDecor.push_back(decor(tab[A],fonction::convertStrToFlo(tab[A + 1]) ,fonction::convertStrToFlo(tab[A + 2])));
                    A +=3;
                    Av = false;
                }
            if(A < tab.size())
                if( (fonction::extract(tab[A]) == "FrontDecor") &&  (Av == true) )//si c'est un decor positionné de vant
                {
                    this->m_FrontDecor.push_back(decor(tab[A],fonction::convertStrToFlo(tab[A + 1]) ,fonction::convertStrToFlo(tab[A + 2])));
                    A +=3;
                    Av = false;
                }
            if(A < tab.size())
                if( (fonction::extract(tab[A]) == "adv") &&  (Av == true) )//si c'est un adversaire
                {
                if(tab[A] == "adv_fireBird")//si c'est un fireBird
                    this->m_advList.push_back(new fireBird(fonction::convertStrToFlo(tab[A + 1]) ,fonction::convertStrToFlo(tab[A + 2])));//on rajoute un pointeur vers
                                                                                                                                        //un fireBird à la liste de pointeur d'adversaire
                if(tab[A] == "adv_joe")//si c'est un Joe
                    this->m_advList.push_back(new joe(fonction::convertStrToFlo(tab[A + 1]) ,fonction::convertStrToFlo(tab[A + 2])));
                if(tab[A] == "adv_punchRabbit")//si c'est un punchRabbit
                    this->m_advList.push_back(new punchRabbit(fonction::convertStrToFlo(tab[A + 1]) ,fonction::convertStrToFlo(tab[A + 2])));
                if(tab[A] == "adv_panda")//si c'est un punchRabbit
                    this->m_advList.push_back(new panda(fonction::convertStrToFlo(tab[A + 1]) ,fonction::convertStrToFlo(tab[A + 2])));
                    A +=3;
                    Av = false;
                }




            }




}
void niveau::play(perso& Hero)
{
        //précise la taille de la fenêtre
    int window_sizeX(1024);
    int window_sizeY(890);
    //création de la vue
    Vue camera(window_sizeX,window_sizeY);
    camera.setPos(window_sizeX/2,window_sizeY/2);//positionnement de celle ci
    m_blackScreen = blackScreen(camera);//on crée l'écran noir
    Fond fond(camera);//on crée le fond
    sf::Event event;
    //met à 0 les valeurs qui gère le déroulement du niveau
    bool finish(false);
    bool respawn(false);
    bool firstOpen(true);//précise que c'est la première ouverture de l'écran noir
    Hero.changeLevel();//précise que le joueur change ou commence un niveau
    Hero.setPos(this->m_spawn.x,this->m_spawn.y);//positionnement du point d'apparition du niveau

    while (environement::m_window.isOpen())
    {


        fond.update(environement::m_window);//met à jour l'écran noir
        if(this->m_blackScreen.isOpen() || this->m_blackScreen.isClose())//si l'écran et ouvert ou fermé on centre la vue sur le joueur
        camera.setPos(Hero.getBox().getPosX() + Hero.getBox().getSizeX()/2,Hero.getBox().getPosY() + Hero.getBox().getSizeY()/2);
        environement::m_window.setView(camera.getView());//met à jour la vue actuel de la fenêtre
        for(int e = 0;e<this->m_BackDecor.size();e++)
        {
                    if(this->m_BackDecor[e].boxCollision(camera))//si les décors de fond sont dans la vue
            environement::m_window.draw(this->m_BackDecor[e].getSprite());//les affiches
        }

        for(int e = 0;e<this->m_checkList.size();e++)
          this->m_checkList[e].update(camera);//met à jour les checkpoints

        for(int e = 0;e<this->m_pieceList.size();e++)
        {
            if(this->m_pieceList[e].isActive() == true && this->m_pieceList[e].boxCollision(camera)== true)//si la pièce est active et qu'elle est dans la vue
            environement::m_window.draw(this->m_pieceList[e].getSprite());//l'affiche
        }

        for(int e = 0;e < this->m_obsList.size();e++)
            this->m_obsList[e].draw(environement::m_window,camera,this->m_BlList);//met à jour les plateforms

        if(this->m_levelEnd.boxCollision(camera))//si la fin de niveau est dans la vue
            environement::m_window.draw(this->m_levelEnd.getSprite());//l'affiche

            if(this->m_blackScreen.isClose() == true && respawn == true)//si l'écran noir est fermé et que le joueur est entrain d'être repositionnée
            {
                this->m_blackScreen.open();//réouvre l'écran noir
                respawn = false;//désactive le repositionement
            }
    if(this->m_blackScreen.isOpen())//si l'écran noir est ouvert
    {
     respawn = Hero.update(this->m_obsList,environement::m_window,camera,this->m_pieceList,this->m_checkList,this->m_advList);//on met à jour le joueur
        if(respawn && this->m_blackScreen.isOpen())//si il va être repositioné(il n'a plus de santé ou de vie)
            this->m_blackScreen.close();//ferme l'écran noir
    }
    else
        environement::m_window.draw(Hero.getSprite());//sinon affiche juste le joueur sans l'affiché pour créer un effet de transition


        for(int e = 0;e < this->m_advList.size();e++)
            this->m_advList[e]->updateCollision(this->m_obsList,camera,this->m_BAdvList);//met à jour les adversaires avec les plateformes et les blocus d'adversaire


        for(int e = 0;e<this->m_FrontDecor.size();e++)
        {
            if(this->m_FrontDecor[e].boxCollision(camera))//si les decor de devant son dans la vue
            environement::m_window.draw(this->m_FrontDecor[e].getSprite());//les affichent
        }

        if(Hero.getBox().boxCollision(this->m_levelEnd) || environement::m_theEnd == true)//si le joueur à atteint la fin de niveau
        {
            Hero.changeLevel();//précise que le joueur change de niveau
            Hero.setVictory();
            this->m_blackScreen.close();//ferme l'écran noir
            finish = true;//précise que le niveau est finit
        }
        if(Hero.isEnd())
        {
            this->m_blackScreen.close();//ferme l'écran noir
            finish = true;//précise que le niveau est finit
        }
        this->m_blackScreen.update(environement::m_window);//met à jour l'écran noir
        if(firstOpen)//si c'est le commencement du niveau
        {
                firstOpen = false;//précise que ce n'est plus le cas
                this->m_blackScreen.open();//ouvre l'écran noir
        }

        while (environement::m_window.pollEvent(event))
        {
        if (event.type == sf::Event::Closed)
            environement::m_window.close();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            environement::m_window.close();


        if(this->m_blackScreen.isClose() && finish == true)//si l'écran noir est fermé et que le niveau est finis
            break;//sort de la boucle de jeu du niveau
        //rafraichissement la fenêtre
        environement::m_window.display();
        environement::m_window.clear();

    }//on sort de la boucle de jeu du niveau




for(int e = 0;e<this->m_advList.size();e++)//vide la liste de pointeur d'adversaire et on les remets à 0
{
    delete this->m_advList[e];
    this->m_advList[e] = 0;
}








}
niveau::~niveau()
{
    //dtor
}
