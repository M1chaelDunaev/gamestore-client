#ifndef ITEMSTRAY_H
#define ITEMSTRAY_H

#include "storeitem.h"

class ItemStray : public StoreItem
{
    Q_OBJECT
protected:
    virtual void setStatus() override;
    virtual void pressAddToCart() override;
    virtual void pressInstall() override;
    virtual void pressPlay() override;
    virtual void pressUninstall() override;

public:
    ItemStray(MainWindow* _mainWindow, UserAccount* _currentAccount);
    ~ItemStray();
};
#endif // ITEMSTRAY_H
