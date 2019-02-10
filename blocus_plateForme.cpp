#include "blocus_plateForme.h"

blocus_plateForme::blocus_plateForme(float posX,float posY,std::string type) : hitBox(posX,posY,50,50)
{
    m_type = type;
}
std::string blocus_plateForme::getType()
{
    return this->m_type;
}
blocus_plateForme::~blocus_plateForme()
{
    //dtor
}
