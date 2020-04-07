#include "Store.h"

vector<Product> Store::products;
vector<string> Store::categories = {"TV", "AUDIO", "GAMING", "COMPUTERS"};
int Store::amountOfProducts = products.size();

int Store::menu()
{
    int choice;
}

void Store::addProduct()
{
    int tempSku;
    string tempProductName;
    string tempCategory;
    double tempPrice;
    int tempInventory;
    char choice;

    cout << endl;
    cout << "Enter product sku: ";
    cin >> tempSku;
    cout << "Enter product name (No Spaces, use '_'): ";
    getline(cin, tempProductName);
    cout << "Enter a product category: \n";
    tempCategory = listCategoriesMenu();
    cout << "Enter Price: ";
    cin >> tempPrice;
    cout << "Enter quantity: ";
    cin >> tempInventory;

    Product temp(tempSku, tempProductName, tempCategory,
                 tempPrice, tempInventory);

    products.push_back(temp);

    cout << "Add another? (Y/N): ";
    cin >> choice;
    if (choice == 'Y')
        addProduct();
}

void editProduct()
{
    int tempSku;
    int choice;
    cout << endl;
    cout << "Enter SKU: ";
    cin >> tempSku;
    cout << endl;

    Product temp = Store::findProductBySku(tempSku);

    cout << "WHat to do with " << temp.getProductName() << "? ("
         << temp.getInventory() << " @ $" << temp.getPrice() << ") \n";
    cout << "Enter choice: \n";
    cout << "1 to change price" << endl;
    cout << "2 to change quantity" << endl;
    cin >> choice;

    if (choice == 1)
    {
        double newPrice;
        cout << "Enter new price: ";
        cin >> newPrice;
        temp.updatePrice(newPrice);
    }

    else if (choice)
    {
        int newQuantity;
        cout << "Enter new quantity: ";
        cin >> newQuantity;
        temp.updateInventory(newQuantity);
    }

    else
    {
        cout << "Invalid option";
    }
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

int Store::checkQuantity(int sku)
{
    Product temp = findProductBySku(sku);
    temp.getInventory();
}

string Store::listCategoriesMenu()
{
    cout << endl;
    bool validChoice = false;
    while (!validChoice)
    {
        int choice;
        for (int i = 1; i <= categories.size(); i++)
        {
            cout << i << " for " << categories[i - 1] << endl;
        }
        validChoice = true;
        cin >> choice;

        if (choice < 1 || choice > categories.size())
        {
            cout << "Invalid choice \n";
            validChoice = false;
        }
        else
            return categories[choice - 1];
    }
}

Product Store::findProductBySku(int sku)
{
    // Goes through each product in array to find matching sku
    for (auto x : products)
    {
        if (x.getSku() == sku)
            return x;
    }
}