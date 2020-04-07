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
    this->sku = sku;
    this->productName = toUpperCase(productName);
    this->category = category;
    this->price = price;
    this->inventory = inventory;
}

int Product::getSku() { return sku; }

string Product::getProductName() { return productName; }

string Product::getCategory() { return category; }

double Product::getPrice() { return price; }

void Product::updatePrice(double newPrice)
{
    price = newPrice;
}

int Product::getInventory() { return inventory; }

int Product::updateInventory(int newInventory) { inventory = newInventory; }

string Product::toUpperCase(string input)
{
    char c;
    string output = input;

    for (int i = 0; i < output.length(); i++)
    {
        // Changes letters to upper case using ASCII
        c = output[i];
        if (c <= 'z' && c >= 'a')
            output[i] = (c - ('z' - 'Z'));

        // In case a space is entered
        if (output[i] == ' ')
            output[i] = '_';
    }

    return output;
}