#ifndef ITEMELDENRING_H
#define ITEMELDENRING_H

#include "storeitem.h"


class ItemEldenRing : public StoreItem
{
    Q_OBJECT
protected:
    virtual void setStatus() override;
    virtual void pressAddToCart() override;
    virtual void pressInstall() override;
    virtual void pressPlay() override;
    virtual void pressUninstall() override;

public:
    ItemEldenRing(MainWindow* _mainWindow, UserAccount* _currentAccount);
    ~ItemEldenRing();
};

#endif // ITEMELDENRING_H
