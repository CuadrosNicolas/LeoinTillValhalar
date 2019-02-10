#ifndef DECOR_LIST_H
#define DECOR_LIST_H
#include "decor.h"
#include <iostream>
class decor_list
{
    public:
        decor_list();
        std::vector<decor>& getList();
        virtual ~decor_list();
    protected:
        std::vector<decor> m_list;
    private:
};

#endif // DECOR_LIST_H
