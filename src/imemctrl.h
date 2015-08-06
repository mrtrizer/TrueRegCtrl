#ifndef IMEMCTRL_H
#define IMEMCTRL_H

#include <inttypes.h>

class IMemCtrl
{
public:
    virtual ~IMemCtrl(){}
    virtual void setValue(unsigned int n, unsigned int value) = 0;
    virtual unsigned int getValue(uint32_t n) = 0;
};

#endif // IMEMCTRL_H
