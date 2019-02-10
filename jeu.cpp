#include "jeu.h"
button jeu::button_jouer;
button jeu::button_quitter;
button jeu::button_score;
button jeu::button_controle;

sf::Sprite jeu::fond_menu;
sf::Sprite jeu::titre_menu;

std::vector<niveau> jeu::monde;
std::map<int , score> jeu::scoreList;

perso jeu::player;


jeu::jeu()
{

}
void jeu::play()
{
    initiate();//initialisation du jeu
    menu();//lancement du menu
}
void jeu::loadScore()
{



            std::vector<std::string> tabA;
            tabA = fonction::loadData("data/Score/score.txt");
            int Av(1);
            for(int e = 0;e <tabA.size();e += 2)
            {
            scoreList[Av] = score(tabA[e],fonction::convertStrToFlo(tabA[e+1]));
            Av++;
            }

}
bool jeu::initiate()
{



            generalTexture::initiate();//création des textures
            environement::initiateWindow();//création de la fenêtre
            loadScore();//chargement des scores


    return true;
}
void jeu::menu()
{

    //création du menu
    sf::View vueMenu(sf::FloatRect(0,0,1024,890));
    titre_menu.setTexture(generalTexture::textureList["titre"]);
    titre_menu.setPosition(299.5,0);
    //création du fond
    fond_menu.setTexture(generalTexture::textureList["fond_menu"]);
    //création des boutons
    button_jouer = button(464,296,"button_jouer");
    button_score = button(465,593,"button_score");
    button_quitter = button(450.5,690,"button_quitter");
    button_controle = button(440.5,500,"button_controle");
    sf::Event event;
    environement::m_window.setView(vueMenu);
        while(environement::m_window.isOpen())
    {


        while (environement::m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                environement::m_window.close();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            environement::m_window.close();

    environement::m_window.draw(fond_menu);
    environement::m_window.draw(titre_menu);
    if(button_jouer.update(environement::m_window))//si le bouton jouer est préssé on lance le jeu
        game();
    if(button_quitter.update(environement::m_window))
        environement::m_window.close();

    if(button_controle.update(environement::m_window))
        howTo();
        if(button_score.update(environement::m_window))//si le bouton score est préssé
            tableauScore();//lancement du tableau des scores

        //rafraichissement de la fenêtre
        environement::m_window.display();
        environement::m_window.clear();


    }


}
bool jeu::game()
{
    //création du personnage
    player = perso(0,0);
    monde = loadGame();//chargement des niveaux
    score scoreP("",0);
    environement::m_theEnd = false;
    for(int e = 0;e<monde.size();e++)//enchainement des niveaux
    {
        if(environement::m_window.isOpen() && player.isEnd() == false)//si la fenêtre est ouverte et que le joueur n'a pas finis la partie(qu'il lui reste encore des vies)
        monde[e].play(player);//lancement du niveau
    }

    if(environement::m_window.isOpen())//si la fenetre est toujours ouverte
    {
     if(environement::m_theEnd)
     theEnd();

    score playerScore("",player.getScore());//chargement du score du joueur
    playerScore = scoreVictory(player.getScore());
    uploadScore(playerScore);//rajout du score du joueur au score général
    loadScore();//chargement du tableau des scores
    }


    return true;
}
void jeu::theEnd()
{

    int window_sizeX(1024);
    int window_sizeY(890);
    Vue vue(window_sizeX,window_sizeY);
    vue.setPos(window_sizeX/2,window_sizeY/2);
    sf::Sprite fond;
    fond.setTexture(generalTexture::textureList["TheEnd"]);
    blackScreen black(vue);
    sf::Clock clockT;
    clockT.restart();
    environement::m_window.setView(vue.getView());
    float time(10);
    bool continu = false;
    bool go = false;
    black.open();
    sf::Event event;
    while(!go)
    {

        if(clockT.getElapsedTime().asSeconds()>time)
        {
            continu = true;
            black.close();
        }
        if(continu == true && black.isClose() == true)
            go = true;

        while (environement::m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                environement::m_window.close();
            go = true;
        }


        environement::m_window.draw(fond);
        black.update(environement::m_window);
        environement::m_window.display();
        environement::m_window.clear();


    }








}
score jeu::scoreVictory(int scoreP)
{

    int window_sizeX(1024);
    int window_sizeY(890);
    Vue vue(window_sizeX,window_sizeY);
    vue.setPos(window_sizeX/2,window_sizeY/2);
    blackScreen black(vue);
    black.open();

        //création du menu pour entrer son nom de joueur(bouton , titre,zone de texte,image de fond)
        sf::View vueScore(sf::FloatRect(0,0,1024,890));

        sf::Sprite victoireFond;
        victoireFond.setTexture(generalTexture::textureList["victoire_fond"]);//on charge l'image de fond

        //chargement du score du joueur pour le rendre affichable
        sf::Text scoreText;
        scoreText.setFont(generalTexture::TextFont);
        std::string scoreStrin("votre score : ");
        std::ostringstream convert;
        std::string temp("");
        convert << scoreP;
        temp = convert.str();
        scoreStrin += temp;
        scoreText.setString(scoreStrin);
        scoreText.setPosition(400,400);

        sf::Sprite zoneDeText;
        zoneDeText.setTexture(generalTexture::textureList["textZone"]);
        zoneDeText.setPosition(462,435);


        //préparation du texte pour l'entrée du nom
        sf::Text playerName;
        playerName.setString("");
        playerName.setFont(generalTexture::TextFont);
        playerName.setPosition(465,435);
        playerName.setCharacterSize(15);
        playerName.setColor(sf::Color::Blue);
        bool go(false);
        sf::Event event;
        sf::Clock textClock;
        float textTime(0.1);


        while(!go)
        {
            while (environement::m_window.pollEvent(event))
        {

                if (event.type == sf::Event::TextEntered)//recup de commendes
    {
        if (event.text.unicode < 128 && textClock.getElapsedTime().asSeconds() > textTime)//si une touche est préssé
        {


        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))//si la touche echape est préssé on ferme la fenetre
        {
            environement::m_window.close();
            go = true;
        }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return) )//si on appuie sur entrée on retourne au menu
                go = true;
            else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
            {

            playerName.setString(playerName.getString() + static_cast<char>(event.text.unicode));//rajout de la touche appuyé au nom du joueur

            }
             else   if(playerName.getString().getSize() > 0)
            {

                std::string returnText("");
            returnText = fonction::textBack(playerName.getString());
            playerName.setString(returnText);
            }

            textClock.restart();
        }
    }


        }




        //dessine les éléments
            environement::m_window.draw(victoireFond);
            environement::m_window.draw(zoneDeText);
            environement::m_window.draw(scoreText);
            environement::m_window.draw(playerName);
            black.update(environement::m_window);

        environement::m_window.display();
        environement::m_window.clear();
        environement::m_window.setView(vueScore);



        }
        score playScore(playerName.getString(),scoreP);
        return playScore;//renvoie le nom du joueur et son score


}
void    jeu::uploadScore(score& playScore)
{
    int pos(1);
    for(int e = 1;e<scoreList.size();e++)
    {
        if(playScore.superior(&scoreList[e]) == false && pos <= 5)//test pour savoir la position du joueur dans les scores actuel
            pos++;
    }
    if(pos <= 5)
    {

                std::ofstream flux("data/Score/score.txt");
            for(int e = 1;e<= pos;e++)
            {
                //réecrie les scores précédant
                if(e < pos)
                flux << scoreList[e].m_nom << std::endl << scoreList[e].m_nombre << std::endl;
                if(e == pos)//écrit le score du joueur si on est arrivé à sa position
                    flux << playScore.m_nom << std::endl << playScore.m_nombre << std::endl;

            }
            for(int e = pos;e <= scoreList.size();e++)
                    flux << scoreList[e].m_nom << std::endl << scoreList[e].m_nombre << std::endl;//on réecrie le reste des scores


    }






}
std::vector<niveau> jeu::loadGame()
{
            std::vector<niveau> tabNiv;

            std::vector<std::string> tab;
            tab = fonction::loadData("data/Level/level_list.txt");//charge le fichier qui donne tout les noms des différents niveau a charger(dans l'ordre)
            for(int e = 0;e<tab.size();e++)
            {
                tabNiv.push_back(niveau());//récupère le chemin du fichier contenant le niveau
                tabNiv[e].load(tab[e].c_str());
            }
        return tabNiv;

}
void jeu::tableauScore()
{
    //préparation les différents sprite à afficher
    sf::Sprite scoreTitre;
    scoreTitre.setTexture(generalTexture::textureList["score_text"]);
    scoreTitre.setPosition(200,150);
    button button_retour(450.5,650,"button_retour");
    std::vector<sf::Text> scoreText;
    float posX(200);
    float posY(200);
    std::string text("");
    for(int e = 1 ;e <= scoreList.size();e++)//initialisation des textes en leurs attribuant les scores contenu dans le fichier
    {
        scoreText.push_back(sf::Text());
        scoreText[e-1].setFont(generalTexture::TextFont);
        scoreText[e-1].setPosition(posX,posY);
        std::string test("");
        test = fonction::convertToString<int>(e);
        text += test;
        text += ". " ;
        text += scoreList[e].m_nom ;
        text += " : " ;
        text += fonction::convertToString<int>(scoreList[e].m_nombre);
        scoreText[e-1].setString(text);
        text = "";
        scoreText[e-1].setCharacterSize(25);
        posY += 25;
    }
    sf::Sprite fond;
    fond.setTexture(generalTexture::textureList["score_fond"]);//chargement du fond
    bool continu(true);
    sf::Event event;
    while(continu)
    {



        environement::m_window.draw(fond);//affiche le fond
        for(int e = 0;e<scoreText.size();e++)
            environement::m_window.draw(scoreText[e]);//affiche les scores
        environement::m_window.draw(scoreTitre);
        if(button_retour.update(environement::m_window))//si le bouton retour est préssé on retourne au menu
            continu = false;
        while (environement::m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                environement::m_window.close();
        }
        //rafraichissement la fenêtre
        environement::m_window.display();
        environement::m_window.clear();




    }






}
void jeu::howTo()
{
    sf::Sprite fond;
    fond.setTexture(generalTexture::textureList["howTo"]);
    button button_retour(450.5,800,"button_retour");
    bool continu(true);


        sf::Event event;
    while(continu)
    {

        environement::m_window.draw(fond);
        if(button_retour.update(environement::m_window))//si le bouton retour est préssé on retourne au menu
            continu = false;
        while (environement::m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                environement::m_window.close();
        }
        environement::m_window.display();
        environement::m_window.clear();




    }













}
jeu::~jeu()
{
    //dtor
}
