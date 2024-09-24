#include "desktopclient.h"
#include "mainapplication.h"

DesktopClient::DesktopClient()
{
    mainApp = new MainApplication();
}

DesktopClient::~DesktopClient()
{
    delete mainApp;
}

void DesktopClient::launch()
{
    mainApp->exec();
}
