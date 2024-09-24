#ifndef ITEMLASTOFUS_H
#define ITEMLASTOFUS_H

#include "storeitem.h"

class ItemLastOfUs : public StoreItem
{
    Q_OBJECT
protected:
    virtual void setStatus() override;
    virtual void pressAddToCart() override;
    virtual void pressInstall() override;
    virtual void pressPlay() override;
    virtual void pressUninstall() override;

public:
    ItemLastOfUs(MainWindow* _mainWindow, UserAccount* _currentAccount);
    ~ItemLastOfUs();
};

#endif // ITEMLASTOFUS_H
