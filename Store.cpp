#include "Store.h"

vector<Product> Store::products;
vector<string> Store::categories = {"TV", "AUDIO", "GAMING", "COMPUTERS", "MOBILE"};
int Store::amountOfProducts = products.size();
double Store::TAX = 0.12;

bool Store::menu()
{
    int choice;

    cout << "\n#### MAIN MENU ####\n"
         << endl;
    cout << "Select an option:" << endl;
    cout << "1) Search Products" << endl;
    cout << "2) Checkout" << endl;
    cout << "3) Add product" << endl;
    cout << "4) Edit product" << endl;
    cout << "5) Change tax rate (Currently: " << (TAX * 100) << "%)" << endl;
    cout << "6) Exit Program" << endl;
    cin >> choice;

    switch (choice)
    {
    case 1:
        searchProducts();
        break;

    case 2:
        checkout();
        break;

    case 3:
        addProduct();
        break;

    case 4:
        editProduct();
        break;

    case 5:
        changeTax();
        break;

    case 6:
        return true;

    default:
        break;
    }
    return false;
}

void Store::changeTax()
{
    cout << endl
         << "Current tax rate: " << (TAX * 100) << "%" << endl
         << "New tax rate? (e.g 15): ";
    cin >> TAX;
    TAX = TAX / 100;
}

void Store::searchProducts()
{
    int choice;
    string searchTerm;
    vector<Product> searchedProducts;

    cout << endl
         << "### Product Search ###" << endl;
    cout << "1) to search by name " << endl;
    cout << "2) to search by category" << endl;
    cin >> choice;
    cout << endl;

    if (choice == 1)
    {
        cout << "Enter a name (no spaces, use '_'): ";
        cin >> searchTerm;
        cout << endl;

        for (auto &product : products)
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

        for (auto &product : products)
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

void Store::displayProduct(Product &productToDisplay)
{
    cout << productToDisplay.getSku() << "\t" << productToDisplay.getProductName()
         << "\n$" << productToDisplay.getPrice() << "\t" << productToDisplay.getCategory() << "\t"
         << productToDisplay.getInventory() << " Units" << endl;
}

void Store::addProduct()
{
    int tempSku;
    string tempProductName;
    string tempCategory;
    double tempPrice;
    int tempInventory;
    string choice;

    cout << endl;
    cout << "### Adding a product ###" << endl;
    cout << "Enter product sku: ";
    cin >> tempSku;
    cin.ignore(1, '\n'); // Otherwise will skip getline
    cout << "Enter product name: ";
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
    choice = toUpperCase(choice);
    if (choice == "Y")
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
    Product temp;

    //Product temp = Store::findProductBySku(tempSku);

    for (auto &x : products)
    {
        if (x.getSku() == tempSku)
            temp = x;
    }

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

        cout << endl
             << "*** Inventory Updated ***" << endl;
    }
    else
    {
        cout << "Can't open file";
    }
}

void Store::readInventory()
{
    bool alreadyFile = false;
    int tempSku;
    string tempProductName;
    string tempCategory;
    double tempPrice;
    int tempInventory;

    ifstream inventoryFile("inventory.txt");

    if (inventoryFile.is_open())
    {
        cout << "Past if";
        while (!inventoryFile.eof())
        {
            cout << "passed while";
            inventoryFile >> tempSku >> tempProductName >> tempCategory >> tempPrice >> tempInventory;

            Product temp(tempSku, tempProductName, tempCategory, tempPrice,
                         tempInventory);

            products.push_back(temp);
        }
        cout << "finished loop";
        inventoryFile.close();
        cout << "file closed";
        alreadyFile = true;
    }

    if (!alreadyFile)
    {
        cout << "\nNo inventory file, one will be created";
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

    cout << endl
         << "### Checkout ###" << endl;

    while (true)
    {
        cout << endl
             << "Enter SKU (or 0 to exit): ";
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
                temp.updateInventory(temp.getInventory() - tempQuantity);
            }
        }

        else if (!isInStock(temp, tempQuantity))
        {
            cout << "Out of stock!";
        }

        else
        {
            cout << "Invalid Quantity" << endl;
        }
    }

    cout << "\n******************************"
         << "\nCart:" << endl;
    for (int i = 0; i < cartProducts.size(); i++)
    {
        cout << endl
             << cartQuantity[i] << " x " << cartProducts[i] << endl;
    }
    printf("SubTotal: $%.2lf", total);
    printf("Tax: $%.2lf", (total * TAX));
    printf("Total: $%.2lf", (total + (total * TAX)));
    int choice;
    cout << "\nEnter 0 to go back to main menu: ";
    cin >> choice;
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

        cout << endl;

        if (choice < 1 || choice > categories.size())
        {
            cout << "Invalid choice \n";
            validChoice = false;
        }
        else
            return categories[choice - 1];
    }
}

Product &Store::findProductBySku(int sku)
{
    // Goes through each product in array to find matching sku
    for (auto &x : products)
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