#ifndef JEU_H
#define JEU_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include "generalTexture.h"
#include <vector>
#include "button.h"
#include "niveau.h"
#include "environement.h"
#include <fstream>
#include <sstream>
#include "score.h"
#include "perso.h"
#include "blackScreen.h"
class jeu //classe permettant de gérer le déroulement du jeu
{
    public:
        jeu();
        static void play();
        static bool initiate();//initialise le jeu
        static std::vector<niveau> loadGame();//charge les niveaux
        static void loadScore();//charge le score
        static void uploadScore(score& playScore);//upload les score du joueur
        static bool game();//lance le jeu
        static void menu();//menu principal (jouer,score,quitter)
        static void theEnd();
        static void howTo();
        static score scoreVictory(int scoreP);//menu de fin pour permettre au joueur d'entrer son nom pour le tableau des scores
        static void tableauScore();//affiche le tableau des scores
        //button des menus
        static button button_jouer;
        static button button_score;
        static button button_quitter;
        static button button_controle;
        //joueur relatif à une partie en cour
        static perso player;

        //fond des menus
       static sf::Sprite fond_menu;
        static sf::Sprite titre_menu;

            //liste des niveaux qui compose une partie
        static std::vector<niveau> monde;
        //liste des scores pour le tableau des scores
        static std::map<int,score> scoreList;

        virtual ~jeu();
    protected:





    private:
};

#endif // JEU_H
