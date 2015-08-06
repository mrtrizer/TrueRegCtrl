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
        if (i->getAddr() == n)
        {
            i->setValueU(value);
            return;
        }
    assert(false);
}

unsigned int ProxyMemCtrl::getValue(unsigned int n)
{
    for (RegList::iterator i = regList.begin(); i != regList.end(); i++)
        if (i->getAddr() == n)
        {
            return i->getValueU();
        }
    assert(false);
}
