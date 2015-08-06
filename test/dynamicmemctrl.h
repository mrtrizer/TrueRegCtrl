#ifndef DYNAMICMEMCTRL_H
#define DYNAMICMEMCTRL_H

#include "imemctrl.h"

class DynamicMemCtrl : public IMemCtrl
{
public:
    DynamicMemCtrl();
    ~DynamicMemCtrl();
    void setValue(unsigned int n, unsigned int value);
    unsigned int getValue(unsigned int n);
private:
    uint32_t value;
};

#endif // DYNAMICMEMCTRL_H
