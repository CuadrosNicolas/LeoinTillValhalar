#ifndef ADVERSAIRE_H
#define ADVERSAIRE_H
#include "pixelCoordTab.h"
#include "fonction.h"
#include "environement.h"
#include "plateforme.h"
#include "hitbox.h"
#include <SFML/Graphics.hpp>
#include "Vue.h"
#include "blocusAdv.h"

class adversaire//classe adversaire servant de base pour tout les adversaires
{
    public:
        adversaire();
        adversaire(float posX,float posY);
        virtual void updateCollision(std::vector<plateforme>& plList,Vue& vue,std::vector<blocusAdv>& BadvList);//permet de mettre a jour les collisions
        virtual std::vector<int>  update(hitBox& colBox,bool persoIsHiting,int persoDommage,hitBox& persoWeaponBox);//permet de mettre a jour les collisions avec le joueur
        hitBox& getBox();
        virtual ~adversaire();
    protected:
        int m_dommage;
        std::string m_etat;
        sf::Sprite m_sprite;
        hitBox m_box;
        std::map<std::string,std::vector<pixelCoordTab> > m_animMapTab;

    private:
};

#endif // ADVERSAIRE_H
