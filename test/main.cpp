#include <QCoreApplication>
#include <QDebug>

#include "proxymemctrl.h"
#include "dynamicmemctrl.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ProxyMemCtrl proxyMemCtrl;
    DynamicMemCtrl dynamicMemCtrl;
    DynamicMemCtrl dynamicMemCtrl2;
    proxyMemCtrl.addReg(Register(100500,&dynamicMemCtrl,1,Register::R));
    proxyMemCtrl.addReg(Register(100500,&dynamicMemCtrl2,1));
    proxyMemCtrl.addReg(Register(100501,&dynamicMemCtrl,100,Register::R));
    proxyMemCtrl.addReg(Register(100502,&dynamicMemCtrl,1,Register::RW));
    proxyMemCtrl.setValue(100500,10000);
    qDebug() << proxyMemCtrl.getValue(100500);
    qDebug() << proxyMemCtrl.getValue(100501);
    qDebug() << proxyMemCtrl.getValue(100502);
    return a.exec();
}
