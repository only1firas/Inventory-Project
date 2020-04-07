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
    static void searchProducts();
    static void displayProduct(Product productToDisplay);
    static void addProduct();
    static void editProduct();
    static void updateInventory();
    static void readInventory();
    static void checkout();
    static int checkQuantity(int sku);
    static string listCategoriesMenu();
    static Product findProductBySku(int sku);
    static bool isInStock(Product product, int quantity);
};

#endif