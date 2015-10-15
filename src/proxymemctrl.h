#ifndef PROXYMEMCTRL_H
#define PROXYMEMCTRL_H

#include "imemctrl.h"

#include <inttypes.h>
#include <vector>
#include <assert.h>

template <typename Param, typename ParamType>
class RegisterT
{
public:
    enum Flag {R = 1, W = 2, RW = 3};
    RegisterT(uint32_t addr, IMemCtrlT<Param, ParamType> * target, uint32_t targetAddr, uint32_t flags = R|W):
        addr(addr),
        target(target),
        targetAddr(targetAddr),
        flags(flags)
    {}
    inline void setValueU(uint32_t value){assert(flags & W); target->setValue(targetAddr,value);}
    inline uint32_t getValueU(){assert(flags & R); return target->getValue(targetAddr);}
    inline bool isEnable(Flag flag){return flags & flag;}
    inline uint32_t getAddr(){return addr;}
private:
    uint32_t addr;
    IMemCtrlT<Param, ParamType> * target;
    uint32_t targetAddr;
    unsigned char flags;
};

template <typename Param, typename ParamType>
class ProxyMemCtrlT : public IMemCtrlT<Param, ParamType>
{
public:
    typedef RegisterT<Param, ParamType> Register;

    ProxyMemCtrlT(){}
    ~ProxyMemCtrlT(){}
    void setValue(Param n, ParamType value)
    {
        for (typename RegList::iterator i = regList.begin(); i != regList.end(); i++)
            if ((i->getAddr() == n) && (i->isEnable(Register::W)))
                i->setValueU(value);
    }
    unsigned int getValue(Param n)
    {
        for (typename RegList::iterator i = regList.begin(); i != regList.end(); i++)
            if ((i->getAddr() == n) && (i->isEnable(Register::R)))
            {
                return i->getValueU();
            }
        assert(false);
    }
    inline void addReg(Register reg){regList.push_back(reg);}
private:
    typedef std::vector<Register> RegList;
    RegList regList;
};

#endif // PROXYMEMCTRL_H
