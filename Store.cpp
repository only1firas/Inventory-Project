#include "Store.h"

vector<Product> Store::products;
vector<string> Store::categories = {"TV", "AUDIO", "GAMING", "COMPUTERS"};

int Store::menu()
{
}

void Store::addProduct()
{
    int tempSku;
    string tempProductName;
    string tempCategory;
    double tempPrice;
    int tempInventory;

    cout << "Enter product sku: ";
    cin >> tempSku;
    cout << "Enter product name (No Spaces, use '_'): ";
    cin >> tempProductName;
    cout << "Enter a product category: \n";
    tempCategory = listCategoriesMenu();
    cout << "Enter Price: ";
    cin >> tempPrice;
    cout << "Enter quantity: ";
    cin >> tempInventory;

    Product temp(tempSku, tempProductName, tempCategory,
                 tempPrice, tempInventory);

    products.push_back(temp);
}

void Store::updateInventory()
{
    ofstream inventoryFile("inventory.txt");

    if (inventoryFile.is_open())
    {
        for (int i = 0; i < products.size(); i++)
        {
            inventoryFile << products[i].getSku() << "\t" << products[i].getProductName()
                          << "\t" << products[i].getCategory() << "\t" << products[i].getPrice()
                          << "\t" << products[i].getInventory() << endl;
        }
        inventoryFile.close();
    }
    else
    {
        cout << "Can't open file";
    }
}

void Store::readInventory()
{
    int tempSku;
    string tempProductName;
    string tempCategory;
    double tempPrice;
    int tempInventory;
    int counter = 0;

    ifstream inventoryFile("inventory.txt");

    if (inventoryFile.is_open())
    {
        while (inventoryFile.good())
        {
            inventoryFile >> tempSku >> tempProductName >> tempCategory >> tempPrice >> tempInventory;

            Product temp(tempSku, tempProductName, tempCategory, tempPrice,
                         tempInventory);

            products[counter] = temp;
            counter++;
        }
        inventoryFile.close();
    }
    else
    {
        cout << "Can't open file";
    }
}

void Store::checkout()
{
}

void Store::checkQuantity(int sku)
{
}

string Store::listCategoriesMenu()
{
    while (true)
    {
        int choice;
        for (int i = 1; i <= categories.size(); i++)
        {
            cout << i << " for " << categories[i - 1] << endl;
        }

        cin >> choice;

        if (choice < 1 || choice > categories.size())
            cout << "Invalid choice \n";
        else
            return categories[choice - 1];
    }
}