#ifndef CHECKPOINT_H
#define CHECKPOINT_H
#include <SFML/Graphics.hpp>
#include "generalTexture.h"
#include "hitbox.h"
#include "pixelCoordTab.h"
#include <map>
#include "Vue.h"
#include "environement.h"

//objet repr�sant les checkpoints du jeu
//Le panneau s'abat sur lui lors de sa premi�re activation
class checkpoint
{
    public:
        checkpoint(float posX,float posY);
        void active();//activation
        void update(Vue& vue);
        sf::Sprite& getSprite();
        hitBox& getBox();
        virtual ~checkpoint();
    protected:
        hitBox m_box;//hitbox du cochon
        hitBox m_checkBox;//hitbox du panneau
        sf::Sprite m_sprite;//sprite du cochon
        sf::Sprite m_check;//sprite du panneau
        bool m_isActive;//si a �t� activ�
        bool m_empalle;//si il a �t� en contact avec son panneau
        std::map<std::string,std::vector<pixelCoordTab> > m_animMapTab;//diff�rente images du checkpoint

    private:
};

#endif // CHECKPOINT_H
