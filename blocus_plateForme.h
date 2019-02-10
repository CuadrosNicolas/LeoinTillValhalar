#ifndef BLOCUS_PLATEFORME_H
#define BLOCUS_PLATEFORME_H
#include "hitbox.h"

class blocus_plateForme : public hitBox//simple hitbox qui permet de rediriger une plateforme vers le direction qui lui correspond(type)
{
    public:
        blocus_plateForme(float posX,float posY,std::string type);
        std::string getType();
        virtual ~blocus_plateForme();
    protected:
        std::string m_type;
    private:
};

#endif // BLOCUS_PLATEFORME_H
