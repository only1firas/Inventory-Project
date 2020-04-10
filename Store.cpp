#include "Store.h"

vector<Product> Store::products;
vector<string> Store::categories = {"TV", "AUDIO", "GAMING", "COMPUTERS", "MOBILE"};
int Store::amountOfProducts = products.size();
double Store::TAX = 0.12;
int Store::DISCOUNT = 0;

void Store::clearProducts()
{
    products.clear();
}

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
    cout << "6) Set a discount (Currently: " << DISCOUNT << "%)" << endl;
    cout << "7) Show entire inventory" << endl;
    cout << "8) Wipe inventory" << endl;
    cout << "9) Exit Program" << endl;
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
        cout << endl
         << "Current tax rate: " << (TAX * 100) << "%" << endl
         << "New discount (e.g 25): ";
        cin >> DISCOUNT;
        cout << endl;
        break;

    case 7 :
        cout << endl;
        for (auto product : products)
        {
            displayProduct(product);
        }
        break;

    case 8:
        int wipe;
        cout << "ARE YOU SURE YOU WANT TO WIPE THE INVENTORY?" << endl;
        cout << "Enter 0 to wipe or any other digit to go back to the menu: " << endl;
        cin >> wipe;
        if (wipe == 0)
        {
            products.clear();
            updateInventory();
        }
        break;

    case 9:
        return true;

    default:
        cout << "Invalid option!";
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

    while (true)
    {
        if (choice == 1)
        {
            cout << "Enter exact name (no spaces, use '_'): ";
            cin >> searchTerm;
            cout << endl;

            int counter = 0;
            for (auto product : products)
            {
                if (product.getProductName() == toUpperCase(searchTerm))
                {
                    displayProduct(product);
                    counter++;
                    break;
                }
            }
            if (counter  == 0)
            {
                cout << "No items found!";
            }
        }

        else if (choice == 2)
        {
            cout << "Choose a category: ";
            searchTerm = listCategoriesMenu();

            int counter = 0;
            for (auto product : products)
            {
                if (product.getCategory() == searchTerm)
                {
                    displayProduct(product);
                    counter++;
                }
            }

            if (counter  == 0)
            {
                cout << "No items found!";
            }
        }

        else
            cout << "Invalid choice" << endl;

        cout << endl;
        int choice;
        cout << "\nEnter 0 to go back to main menu: ";
        cin >> choice;
        break;
    }
}

void Store::displayProduct(Product &productToDisplay)
{
    cout << productToDisplay.getSku() << "\t" << productToDisplay.getProductName()
         << "\t$" << productToDisplay.getPrice() << "\t" << productToDisplay.getCategory() << "\t"
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
    cout << "Enter product SKU (Product ID): ";
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
    // Product temp;

    //Product temp = Store::findProductBySku(tempSku);

    // for (auto &x : products)
    // {
    //     if (x.getSku() == tempSku)
    //         temp = x;
    // }

    cout << "What to do with " << products[findProductIndexBySku(tempSku)].getProductName() << "? ("
         << products[findProductIndexBySku(tempSku)].getInventory() << " @ $" << products[findProductIndexBySku(tempSku)].getPrice() << ") \n";
    cout << "Enter choice: \n";
    cout << "1 to change price" << endl;
    cout << "2 to change quantity" << endl;
    cin >> choice;

    if (choice == 1)
    {
        double newPrice;
        cout << "Enter new price: ";
        cin >> newPrice;
        products[findProductIndexBySku(tempSku)].updatePrice(newPrice);
    }

    else if (choice == 2)
    {
        int newQuantity;
        cout << "Enter new quantity: ";
        cin >> newQuantity;
        products[findProductIndexBySku(tempSku)].updateInventory(newQuantity);
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
    clearProducts();

    bool alreadyFile = false;
    int tempSku;
    string tempProductName;
    string tempCategory;
    double tempPrice;
    int tempInventory;

    ifstream inventoryFile("inventory.txt");

    if (inventoryFile.is_open())
    {
        while (inventoryFile.good())
        {
            inventoryFile >> tempSku >> tempProductName >> tempCategory >> tempPrice >> tempInventory;

            Product temp(tempSku, tempProductName, tempCategory, tempPrice,
                         tempInventory);

            products.push_back(temp);
        }
        inventoryFile.close();
        alreadyFile = true;

        // delete the last element because there will be a duplicate
        products.pop_back();
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
    // Product temp;
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

        // temp = products[findProductIndexBySku(tempSku)];

        cartProducts.push_back(products[findProductIndexBySku(tempSku)].getProductName());

        cout << "Enter quantity: ";
        cin >> tempQuantity;

        cartQuantity.push_back(tempQuantity);

        if (tempQuantity > 0)
        {
            if (isInStock(products[findProductIndexBySku(tempSku)], tempQuantity))
            {
                total += (products[findProductIndexBySku(tempSku)].getPrice() * tempQuantity);
                products[findProductIndexBySku(tempSku)].updateInventory(products[findProductIndexBySku(tempSku)].getInventory() - tempQuantity);
            }
            cout<<"fail";
        }

        else if (!isInStock(products[findProductIndexBySku(tempSku)], tempQuantity))
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

    double price;
    for (int i = 0; i < cartProducts.size(); i++)
    {
        for (int j = 0; j < products.size(); j++)
        {
            if (products[j].getProductName() == cartProducts[i])
                price = products[j].getPrice();
        }
        cout << endl
             << cartQuantity[i] << " x " << cartProducts[i] << ": \t";
        printf("$%.2lf", price);
    }
    cout << endl << endl;
    printf("SubTotal: $%.2lf", total);
    cout << endl;
    printf("Tax: $%.2lf", (total * TAX));
    cout << endl;
    printf("Total: $%.2lf", (total + (total * TAX)));
    cout << endl;
    int choice;
    cout << "\nEnter 0 to go back to main menu: ";
    cin >> choice;
}

int Store::checkQuantity(int sku)
{
    return products[findProductIndexBySku(sku)].getInventory();
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

int Store::findProductIndexBySku(int sku)
{
    // Goes through each product in array to find matching sku
    for (int i = 0; i < products.size(); i++)
    {

        if (products[i].getSku() == sku)
            return i;
    }
}

bool Store::isInStock(Product product, int quantity)
{
    if (product.getInventory() < quantity)
        return false;

    return true;
}