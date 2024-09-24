#ifndef ITEMHORIZON_H
#define ITEMHORIZON_H

#include "storeitem.h"

class ItemHorizon : public StoreItem
{
    Q_OBJECT
protected:
    virtual void setStatus() override;
    virtual void pressAddToCart() override;
    virtual void pressInstall() override;
    virtual void pressPlay() override;
    virtual void pressUninstall() override;

public:
    ItemHorizon(MainWindow* _mainWindow, UserAccount* _currentAccount);
    ~ItemHorizon();
};
#endif // ITEMHORIZON_H
