#include "Product.h"

Product::Product()
{
    sku = 0;
    productName = "NOT_NAMED";
    category = "N/A";
    price = 0;
    inventory = 0;
}

Product::Product(int sku, string productName, string category,
                 double price, int inventory)
{
}

int Product::getSku() { return sku; }

string Product::getProductName() { return productName; }

string Product::getCategory() { return category; }

double Product::getPrice() { return price; }

int Product::getInventory() { return inventory; }

int Product::updateInventory(int x) { inventory -= x; }

string Product::toUpperCase(string input)
{
    char c;
    string output = input;

    for (int i = 0; i < output.length(); i++)
    {
        c = output[i];
        if (c <= 'Z' && c >= 'A')
            output[i] = (c - ('Z' - 'z'));
    }
    
    return output;
}