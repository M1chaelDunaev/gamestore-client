#ifndef ITEMGODOFWAR_H
#define ITEMGODOFWAR_H

#include "storeitem.h"

class ItemGodOfWar : public StoreItem
{
        Q_OBJECT
    protected:
        virtual void setStatus() override;
        virtual void pressAddToCart() override;
        virtual void pressInstall() override;
        virtual void pressPlay() override;
        virtual void pressUninstall() override;

    public:
        ItemGodOfWar(MainWindow* _mainWindow, UserAccount* _currentAccount);
        ~ItemGodOfWar();

};

#endif // ITEMGODOFWAR_H
