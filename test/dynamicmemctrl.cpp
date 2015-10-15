#include "dynamicmemctrl.h"

DynamicMemCtrl::DynamicMemCtrl() : value(0)
{

}

DynamicMemCtrl::~DynamicMemCtrl()
{

}

void DynamicMemCtrl::setValue(unsigned int n, unsigned int value)
{
    (void)n;
    this->value = value;
}

unsigned int DynamicMemCtrl::getValue(unsigned int n)
{
    return this->value + n;
}
