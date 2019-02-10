#ifndef COORDTAB_H
#define COORDTAB_H

//tableau de coordonnées
class coordTab
{
    public:
        coordTab();
        coordTab(int posX,int posY);
        virtual ~coordTab();
        int x;
        int y;
    protected:
    private:
};

#endif // COORDTAB_H
