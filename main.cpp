// Firas Al-Mohammad
// T00645688
// Store inventory system

#include <string>
#include <sstream>
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
    Product()
    {
        sku = 0;
        productName = "NOT_NAMED";
        category = "N/A";
        price = 0;
        inventory = 0;
    }

    Product(int sku, string productName, string category,
            double price, int inventory)
    {
        this->sku = sku;
        this->productName = toUpperCase(productName);
        this->category = category;
        this->price = price;
        this->inventory = inventory;
    }

    int getSku() { return sku; }

    string getProductName() { return productName; }

    string getCategory() { return category; }

    double getPrice() { return price; }

    void updatePrice(double newPrice)
    {
        price = newPrice;
    }

    int getInventory() { return inventory; }

    int updateInventory(int newInventory) { inventory = newInventory; }

    string toUpperCase(string input)
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
};
class Store : public Product
{
private:
    vector<Product> products;
    vector<string> categories = {"TV", "AUDIO", "GAMING", "COMPUTERS", "MOBILE"};
    int amountOfProducts = products.size();
    double TAX = 0.12;
    int DISCOUNT = 0;

public:
    void clearProducts()
    {
        products.clear();
    }

    bool menu()
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

        case 7:
            cout << "\n#### Full Inventory ####\n";
            while (true)
            {
                cout << endl;
                for (auto product : products)
                {
                    displayProduct(product);
                }
                cout << endl;
                int leave;
                cout << "\nEnter 0 to go back to main menu: ";
                cin >> leave;
                break;
            }
            break;

        case 8:
            int wipe;
            cout << "ARE YOU SURE YOU WANT TO WIPE THE INVENTORY?" << endl;
            cout << "Enter 0 to wipe or any other number to go back to the menu: " << endl;
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

    void changeTax()
    {
        cout << endl
             << "Current tax rate: " << (TAX * 100) << "%" << endl
             << "New tax rate? (e.g 15): ";
        cin >> TAX;
        TAX = TAX / 100;
    }

    void searchProducts()
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
                if (counter == 0)
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

                if (counter == 0)
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

    void displayProduct(Product &productToDisplay)
    {
        cout << productToDisplay.getSku() << "\t" << productToDisplay.getProductName()
             << "\t$" << productToDisplay.getPrice() << "\t" << productToDisplay.getCategory() << "\t"
             << productToDisplay.getInventory() << " Units" << endl;
    }

    void addProduct()
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

    void editProduct()
    {
        int tempSku;
        int choice;
        cout << endl;
        cout << "### Editing Product ###" << endl;
        cout << "Enter SKU: ";
        cin >> tempSku;
        cout << endl;

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

    void updateInventory()
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

    void readInventory()
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

    void checkout()
    {
        int tempSku, tempQuantity;
        double total = 0;
        vector<string> cartProducts;
        vector<int> cartQuantity;

        cout << endl
             << "### Checkout ###" << endl;

        while (true)
        {
            cout << endl
                 << "Enter SKU (or 0 to proceed): ";
            cin >> tempSku;

            if (tempSku == 0)
                break;

            cartProducts.push_back(products[findProductIndexBySku(tempSku)].getProductName());

            cout << "(" << products[findProductIndexBySku(tempSku)].getInventory() << " @ $"
                 << products[findProductIndexBySku(tempSku)].getPrice() << ") \n";

            while (true)
            {
                cout << "Enter quantity: ";
                cin >> tempQuantity;

                cartQuantity.push_back(tempQuantity);

                if (products[findProductIndexBySku(tempSku)].getInventory() >= tempQuantity)
                {
                    total += (products[findProductIndexBySku(tempSku)].getPrice() * tempQuantity);
                    products[findProductIndexBySku(tempSku)].updateInventory(products[findProductIndexBySku(tempSku)].getInventory() - tempQuantity);
                }

                else if (products[findProductIndexBySku(tempSku)].getInventory() < tempQuantity)
                {
                    cout << endl
                         << "Out of stock! (Only " << products[findProductIndexBySku(tempSku)].getInventory() << " left)" << endl;
                    cartQuantity.pop_back();
                    continue;
                }

                else
                {
                    cout << "Invalid Quantity" << endl;
                }
                break;
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
        cout << endl
             << endl;
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

    int checkQuantity(int sku)
    {
        return products[findProductIndexBySku(sku)].getInventory();
    }

    string listCategoriesMenu()
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

    int findProductIndexBySku(int sku)
    {
        // Goes through each product in array to find matching sku
        for (int i = 0; i < products.size(); i++)
        {

            if (products[i].getSku() == sku)
                return i;
        }
    }

    bool isInStock(Product product, int quantity)
    {
        if (product.getInventory() < quantity)
            return false;

        return true;
    }
};

int main()
{
    Store s1;
    s1.readInventory();
    bool isProgramOver = false;

    cout << endl
         << "Welcome to Store Inventory System " << endl;

    while (!isProgramOver)
    {
        isProgramOver = s1.menu();
    }

    s1.updateInventory();
    s1.clearProducts();

    cout << endl
         << "#### End of Program ####";

    return 0;
}
