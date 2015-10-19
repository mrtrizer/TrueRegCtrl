#ifndef IMEMCTRL_H
#define IMEMCTRL_H

#include <inttypes.h>

#define NOT_DEFINED (static_cast<unsigned int>(0xFFFFFFF))

template <typename Param, typename ParamType>
class IMemCtrlT
{
public:
    virtual ~IMemCtrlT(){}
    virtual void setValue(Param n, ParamType value) = 0;
    virtual unsigned int getValue(Param n) = 0;
};

#endif // IMEMCTRL_H
