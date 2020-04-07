#include "Store.h"

vector<Product> Store::products;
vector<string> Store::categories = {"TV", "AUDIO", "GAMING", "COMPUTERS"};
int Store::amountOfProducts = products.size();

int Store::menu()
{
    int choice;
}

void Store::searchProducts()
{
    int choice;
    string searchTerm;
    vector<Product> searchedProducts;

    cout << endl
         << "### Product Search ###" << endl;
    cout << "1 to search by name " << endl;
    cout << "2 to search by category" << endl;
    cin >> choice;
    cout << endl;

    if (choice == 1)
    {
        cout << "Enter a name (no spaces, use '_'): ";
        getline(cin, searchTerm);

        for (auto product : products)
        {
            if (product.getProductName() == toUpperCase(searchTerm))
            {
                displayProduct(product);
                break;
            }
        }
    }

    else if (choice == 2)
    {
        cout << "Choose a category: ";
        searchTerm = listCategoriesMenu();

        for (auto product : products)
        {
            if (product.getCategory() == searchTerm)
            {
                displayProduct(product);
            }
        }
    }

    else
        cout << "Invalid choice" << endl;
    
}

void Store::displayProduct(Product productToDisplay)
{
    cout << productToDisplay.getSku() << "\t" << productToDisplay.getProductName() << "\t"
         << "$" << productToDisplay.getPrice() << "\t" << productToDisplay.getCategory() << "\t"
         << productToDisplay.getInventory() << endl;
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
    cout << "### Adding a product ###";
    cout << "Enter product sku: ";
    cin >> tempSku;
    cin.ignore(1, '\n'); // Otherwise will skip getline
    cout << "Enter product name (No Spaces, use '_'): ";

    //
    // trying to use getline
    //
    getline(cin, tempProductName);
    //
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

void Store::editProduct()
{
    int tempSku;
    int choice;
    cout << endl;
    cout << "### Editing Product ###" << endl;
    cout << "Enter SKU: ";
    cin >> tempSku;
    cout << endl;

    Product temp = Store::findProductBySku(tempSku);

    cout << "What to do with " << temp.getProductName() << "? ("
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
        updateInventory();
    }

    else if (choice == 2)
    {
        int newQuantity;
        cout << "Enter new quantity: ";
        cin >> newQuantity;
        temp.updateInventory(newQuantity);
        updateInventory();
    }

    else
    {
        cout << "Invalid option";
    }
}

void Store::updateInventory()
{
    ofstream inventoryFile("inventory.txt", ios::trunc);

    if (inventoryFile.is_open())
    {
        for (int i = 0; i < products.size(); i++)
        {
            inventoryFile << products[i].getSku() << "\t" << products[i].getProductName()
                          << "\t" << products[i].getCategory() << "\t" << products[i].getPrice()
                          << "\t" << products[i].getInventory() << endl;
        }
        inventoryFile.close();

        cout << endl << "*** Inventory Updated ***" << endl;
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
        cout << "No inventory file, one will be created";
        updateInventory();
    }
}

void Store::checkout()
{
    int tempSku, tempQuantity;
    double total = 0;
    Product temp;
    vector<string> cartProducts;
    vector<int> cartQuantity;

    cout << endl << "### Checkout ###" << endl;

    while (true)
    {
        cout << "Enter SKU (or 0 to exit): ";
        cin >> tempSku;

        if (tempSku == 0)
            break;

        temp = findProductBySku(tempSku);

        cartProducts.push_back(temp.getProductName());

        cout << "Enter quantity: ";
        cin >> tempQuantity;

        cartQuantity.push_back(tempQuantity);

        if (tempQuantity > 0)
        {
            if (isInStock(temp, tempQuantity))
            {
                total += (temp.getPrice() * tempQuantity);
            }
        }

        else
        {
            cout << "Invalid Quantity" << endl;
        }
        
    }
    
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

bool Store::isInStock(Product product, int quantity)
{
    if (product.getInventory() < quantity)
        return false;

    return true;
}