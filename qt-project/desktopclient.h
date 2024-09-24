#ifndef DESKTOPCLIENT_H
#define DESKTOPCLIENT_H

class MainApplication;

class DesktopClient
{
    MainApplication* mainApp;

public:
    DesktopClient();
    ~DesktopClient();

    void launch();
};

#endif // DESKTOPCLIENT_H
