#include "authform.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AuthForm authForm; // Создайте экземпляр класса AuthForm

    return a.exec();
}
