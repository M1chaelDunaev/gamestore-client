#include "desktopclient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DesktopClient client;
    client.launch();
    return a.exec();
}
