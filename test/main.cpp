#include <QCoreApplication>
#include <QDebug>

#include "proxymemctrl.h"
#include "dynamicmemctrl.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ProxyMemCtrl proxyMemCtrl;
    DynamicMemCtrl dynamicMemCtrl;
    proxyMemCtrl.addReg(Register(100500,&dynamicMemCtrl,1));
    proxyMemCtrl.addReg(Register(100501,&dynamicMemCtrl,100,Register::R));
    proxyMemCtrl.addReg(Register(100502,&dynamicMemCtrl,1,Register::RW));
    qDebug() << proxyMemCtrl.getValue(100500);
    qDebug() << proxyMemCtrl.getValue(100501);
    proxyMemCtrl.setValue(100502,10);
    qDebug() << proxyMemCtrl.getValue(100502);
    return a.exec();
}
