#ifndef STORE_H
#define STORE_H

#include "Product.h"

class Store : public Product
{
    private:
        static vector<Product> products;
        static int amountOfProducts;
        static vector<string> categories;
    
    public:
        static int menu();
        static void addProduct();
        static void updateInventory();
        static void readInventory();
        static void checkout();
        static void checkQuantity(int sku);
        static void listCategories();
};

#endif