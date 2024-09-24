#ifndef ITEMPLAGUETALE_H
#define ITEMPLAGUETALE_H

#include "storeitem.h"

class ItemPlagueTale : public StoreItem
{
    Q_OBJECT
protected:
    virtual void setStatus() override;
    virtual void pressAddToCart() override;
    virtual void pressInstall() override;
    virtual void pressPlay() override;
    virtual void pressUninstall() override;

public:
    ItemPlagueTale(MainWindow* _mainWindow, UserAccount* _currentAccount);
    ~ItemPlagueTale();
};
#endif // ITEMPLAGUETALE_H
