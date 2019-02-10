#ifndef BLOCUSADV_H
#define BLOCUSADV_H
#include "hitbox.h"

//simple hitbox qui au contact des adversaires les faits changer de direction
class blocusAdv : public hitBox
{
    public:
        blocusAdv(float posX,float posY);
        virtual ~blocusAdv();
    protected:
    private:
};

#endif // BLOCUSADV_H
