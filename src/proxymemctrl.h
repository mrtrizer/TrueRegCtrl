#ifndef PROXYMEMCTRL_H
#define PROXYMEMCTRL_H

#include "imemctrl.h"

#include <inttypes.h>
#include <vector>
#include <assert.h>

class Register
{
public:
    enum Flag {R = 1, W = 2, RW = 3};
    Register(uint32_t addr, IMemCtrl * target, uint32_t targetAddr, uint32_t flags = R|W):
        addr(addr),
        target(target),
        targetAddr(targetAddr),
        flags(flags)
    {}
    inline uint32_t setValueU(uint32_t value){assert(flags & W); target->setValue(targetAddr,value);}
    inline uint32_t getValueU(){assert(flags & R); return target->getValue(targetAddr);}
    inline bool isEnable(Flag flag){return flags & flag;}
    inline uint32_t getAddr(){return addr;}
private:
    uint32_t addr;
    IMemCtrl * target;
    uint32_t targetAddr;
    unsigned char flags;
};

class ProxyMemCtrl : public IMemCtrl
{
public:
    ProxyMemCtrl();
    ~ProxyMemCtrl();
    void setValue(unsigned int n, unsigned int value);
    unsigned int getValue(unsigned int n);
    inline void addReg(Register reg){regList.push_back(reg);}
private:
    typedef std::vector<Register> RegList;
    RegList regList;
};

#endif // PROXYMEMCTRL_H
