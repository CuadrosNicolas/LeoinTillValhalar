#ifndef NIVEAU_H
#define NIVEAU_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include"perso.h"
#include "plateforme.h"
#include "generalTexture.h"
#include <iostream>
#include "Vue.h"
#include "decor.h"
#include "Fond.h"
#include "piece.h"
#include "checkpoint.h"
#include <vector>
#include "environement.h"
#include "fonction.h"
#include "fin_niveau.h"
#include "adversaire.h"
#include "fireBird.h"
#include "joe.h"
#include "blocusAdv.h"
#include "punchRabbit.h"
#include "blackScreen.h"
#include "score.h"
#include "panda.h"
class niveau // objet représentant un niveau composé de liste pour
            //chaque type d'entité(spawn,fin de niveau,plateforme,
            //blocus de plateform,decor arrière et avant,pièce,checkpoint,adversaire et blocus d'adversaire)
{
    public:
        niveau();
        void load(const char* chemin);//charge un niveau a partir du chemin passé en paramètre
        static std::string extract(std::string nom);
        void play(perso& Hero);




    fin_niveau m_levelEnd;
    sf::Vector2f m_spawn;
    std::vector<plateforme> m_obsList;
    std::vector<blocus_plateForme> m_BlList;
    std::vector<decor> m_BackDecor;
    std::vector<decor> m_FrontDecor;
    std::vector<piece> m_pieceList;
    std::vector<checkpoint> m_checkList;
    std::vector<adversaire*> m_advList;
    std::vector<blocusAdv> m_BAdvList;
    blackScreen m_blackScreen;
        virtual ~niveau();
    protected:
    private:
};

#endif // NIVEAU_H
