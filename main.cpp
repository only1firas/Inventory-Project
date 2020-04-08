// Firas Al-Mohammad
// T00645688
// Store inventory system

#include "Store.h"

int main()
{
    Store::readInventory();
    bool isProgramOver = false;

    wcout << endl << "Welcome to Store Inventory System " << endl;
    
    while (!isProgramOver)
    {
        isProgramOver = Store::menu();
    }

    Store::updateInventory();

    cout << endl << "#### End of Program ####";

    return 0;
}
