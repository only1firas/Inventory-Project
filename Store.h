#ifndef STORE_H
#define STORE_H

#include "Product.h"

class Store : public Product
{
private:
    static vector<Product> products;
    static int amountOfProducts;
    static vector<string> categories;
    static double TAX;
    static int DISCOUNT;

public:
    static bool menu();
    static void clearProducts();
    static void changeTax();
    static void searchProducts();
    static void displayProduct(Product &productToDisplay);
    static void addProduct();
    static void editProduct();
    static void updateInventory();
    static void readInventory();
    static void checkout();
    static int checkQuantity(int sku);
    static string listCategoriesMenu();
    static int findProductIndexBySku(int sku);
    static bool isInStock(Product product, int quantity);
};

#endif