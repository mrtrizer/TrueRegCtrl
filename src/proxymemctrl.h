#ifndef PROXYMEMCTRL_H
#define PROXYMEMCTRL_H

#include "imemctrl.h"

#include <inttypes.h>
#include <vector>
#include <assert.h>

template <typename Param, typename ParamType>
class AbstractRegiserT
{
public:
    enum Flag {R = 1, W = 2, RW = 3, UNBUFF = 4};
    AbstractRegiserT(Param addr, uint32_t flags = R|W):
        addr(addr),
        flags(flags)
    {}
    virtual ~AbstractRegiserT()
    {}
    virtual AbstractRegiserT<Param, ParamType> * getClone() const = 0;
    virtual void setValue(ParamType value) = 0;
    virtual void setValueU(uint32_t value) = 0;
    virtual uint32_t getValueU() const = 0;
    inline bool isEnable(Flag flag) const {return flags & flag;}
    inline uint32_t getAddr() const {return addr;}
protected:
    Param addr;
    unsigned char flags;
};

template <typename Param, typename TargetParam, typename ParamType>
class RegisterT: public AbstractRegiserT<Param, ParamType>
{
public:
    typedef AbstractRegiserT<Param, ParamType> AbstractRegister;
    RegisterT(Param addr, IMemCtrlT<TargetParam, ParamType> * target, TargetParam targetAddr, uint32_t flags = AbstractRegister::RW):
        AbstractRegiserT<Param, ParamType>(addr, flags),
        target(target),
        targetAddr(targetAddr)
    {}
    AbstractRegiserT<Param, ParamType> * getClone() const
    {
        return new RegisterT<Param, TargetParam, ParamType>(*this);
    }
    void setValue(ParamType value)
    {
        assert(this->flags & AbstractRegister::W);
        if (this->flags & AbstractRegister::UNBUFF)
            target->setValueUnbuff(targetAddr,value);
        else
            target->setValue(targetAddr, value);
    }
    void setValueU(uint32_t value)
    {
        assert(this->flags & AbstractRegister::W);
        setValue(value);
    }
    uint32_t getValueU() const
    {
        assert(this->flags & AbstractRegister::R);
        return target->getValue(targetAddr);
    }
private:
    IMemCtrlT<TargetParam, ParamType> * target;
    TargetParam targetAddr;
};

template <typename Param, typename ParamType>
class ProxyMemCtrlT : public IMemCtrlT<Param, ParamType>
{
public:
    typedef AbstractRegiserT<Param, ParamType> AbstractRegister;

    ProxyMemCtrlT(){}
    ~ProxyMemCtrlT()
    {
        for (typename RegList::iterator i = regList.begin(); i != regList.end(); i++)
            delete *i;
    }
    void setValue(Param n, ParamType value)
    {
        for (typename RegList::iterator i = regList.begin(); i != regList.end(); i++)
            if (((*i)->getAddr() == n) && ((*i)->isEnable(AbstractRegister::W)))
                (*i)->setValueU(value);
    }
    unsigned int getValue(Param n) const
    {
        for (typename RegList::const_iterator i = regList.begin(); i != regList.end(); i++)
            if (((*i)->getAddr() == n) && ((*i)->isEnable(AbstractRegister::R)))
            {
                return (*i)->getValueU();
            }
        assert(false);
    }
    inline void addReg(const AbstractRegister & reg){regList.push_back(reg.getClone());}
private:
    typedef std::vector<AbstractRegister *> RegList;
    RegList regList;
};

#endif // PROXYMEMCTRL_H
