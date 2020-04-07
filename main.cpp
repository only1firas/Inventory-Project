// #include "Store.h"
#include "Product.h"

int main()
{
    cout << "Hello";
    Product a1;
    cout << a1.getCategory() << a1.getInventory() << 
        a1.getSku() << a1.getProductName();

    return 0;
}
