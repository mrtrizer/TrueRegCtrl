#include <QCoreApplication>
#include <QDebug>

#include "proxymemctrl.h"
#include "dynamicmemctrl.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    typedef ProxyMemCtrlT<unsigned int, unsigned int> ProxyMemCtrl;
    ProxyMemCtrl proxyMemCtrl;
    DynamicMemCtrl dynamicMemCtrl;
    DynamicMemCtrl dynamicMemCtrl2;
    proxyMemCtrl.addReg(ProxyMemCtrl::Register(100500,&dynamicMemCtrl,1,ProxyMemCtrl::Register::R));
    proxyMemCtrl.addReg(ProxyMemCtrl::Register(100500,&dynamicMemCtrl2,1));
    proxyMemCtrl.addReg(ProxyMemCtrl::Register(100501,&dynamicMemCtrl,100,ProxyMemCtrl::Register::R));
    proxyMemCtrl.addReg(ProxyMemCtrl::Register(100502,&dynamicMemCtrl,1,ProxyMemCtrl::Register::RW));
    proxyMemCtrl.setValue(100500,10000);
    qDebug() << proxyMemCtrl.getValue(100500);
    qDebug() << proxyMemCtrl.getValue(100501);
    qDebug() << proxyMemCtrl.getValue(100502);
    return a.exec();
}
