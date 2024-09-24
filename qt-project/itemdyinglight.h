#ifndef ITEMDYINGLIGHT_H
#define ITEMDYINGLIGHT_H

#include "storeitem.h"

class ItemDyingLight : public StoreItem
{
    Q_OBJECT
protected:
    virtual void setStatus() override;
    virtual void pressAddToCart() override;
    virtual void pressInstall() override;
    virtual void pressPlay() override;
    virtual void pressUninstall() override;

public:
    ItemDyingLight(MainWindow* _mainWindow, UserAccount* _currentAccount);
    ~ItemDyingLight();
};;

#endif // ITEMDYINGLIGHT_H
