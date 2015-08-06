#include "proxymemctrl.h"

ProxyMemCtrl::ProxyMemCtrl()
{

}

ProxyMemCtrl::~ProxyMemCtrl()
{

}

void ProxyMemCtrl::setValue(unsigned int n, unsigned int value)
{
    for (RegList::iterator i = regList.begin(); i != regList.end(); i++)
        if ((i->getAddr() == n) && (i->isEnable(Register::W)))
            i->setValueU(value);
}

unsigned int ProxyMemCtrl::getValue(unsigned int n)
{
    for (RegList::iterator i = regList.begin(); i != regList.end(); i++)
        if ((i->getAddr() == n) && (i->isEnable(Register::R)))
        {
            return i->getValueU();
        }
    assert(false);
}
