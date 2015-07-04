#ifndef IMEMCTRL_H
#define IMEMCTRL_H

class IMemCtrl
{
public:
    virtual ~IMemCtrl(){}
    virtual void setValue(unsigned int n, unsigned int value) = 0;
    virtual unsigned int getValue(unsigned int n) = 0;
};

#endif // IMEMCTRL_H
