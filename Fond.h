#ifndef FOND_H
#define FOND_H
#include <SFML/Graphics.hpp>
#include "Vue.h"
#include "generalTexture.h"
class Fond  //arrière plan d'un niveau
{
    public:
        Fond(Vue& view);
        void update(sf::RenderWindow& window);
        virtual ~Fond();
    protected:
        Vue* m_vue;
        sf::VertexArray m_vertexArray;
        sf::Texture* m_text;
    private:
};

#endif // FOND_H
