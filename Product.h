#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Product
{
private:
    int sku;
    string productName;
    string category;
    double price;
    int inventory;

public:
    Product();
    Product(int sku, string productName, string category,
            double price, int inventory);
    int getSku();
    string getProductName();
    string getCategory();
    double getPrice();
    void updatePrice(double newPrice);
    int getInventory();
    int updateInventory(int x);
    string static toUpperCase(string original);
};

#endif