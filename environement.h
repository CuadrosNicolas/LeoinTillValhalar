#ifndef ENVIRONEMENT_H
#define ENVIRONEMENT_H
#include <SFML/Graphics.hpp>

//class g�rant l'environement du jeu(la fenetre ou celui-�i s'ex�cute)
class environement
{
    public:
        environement();
        static void initiateWindow();
        static sf::RenderWindow m_window;//fenetre utilis� dans le programme
        virtual ~environement();
        static bool m_theEnd;
    protected:
    private:
};

#endif // ENVIRONEMENT_H
