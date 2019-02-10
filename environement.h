#ifndef ENVIRONEMENT_H
#define ENVIRONEMENT_H
#include <SFML/Graphics.hpp>

//class gérant l'environement du jeu(la fenetre ou celui-çi s'exécute)
class environement
{
    public:
        environement();
        static void initiateWindow();
        static sf::RenderWindow m_window;//fenetre utilisé dans le programme
        virtual ~environement();
        static bool m_theEnd;
    protected:
    private:
};

#endif // ENVIRONEMENT_H
