#ifndef ITEMCUPHEAD_H
#define ITEMCUPHEAD_H

#include "storeitem.h"

class ItemCuphead : public StoreItem
{
    Q_OBJECT
protected:
    virtual void setStatus() override;
    virtual void pressAddToCart() override;
    virtual void pressInstall() override;
    virtual void pressPlay() override;
    virtual void pressUninstall() override;

public:
    ItemCuphead(MainWindow* _mainWindow, UserAccount* _currentAccount);
    ~ItemCuphead();
};
#endif // ITEMCUPHEAD_H
