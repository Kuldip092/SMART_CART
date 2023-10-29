#include <bits/stdc++.h>
using namespace std;

const string RED = "\033[1;31m";
    const string GREEN = "\033[1;32m";
    const string YELLOW = "\033[1;33m";
    const string BLUE = "\033[1;34m";
    const string RESET = "\033[0m";
    const string CYAN = "\033[1;36m";
    const string MAGENTA = "\033[1;35m";

class Shopping
{
private:
    int product_id;
    string product_name;
    float product_price;
    float product_discount;

public:

    void menu();
    void admin();
    void customer();
    void add_product();
    void delete_product();
    void update_product();
    void remove_product();
    void display_product();
    void receipt();
};

void Shopping::menu()
{
menu:

    int choice;
    string password;
    string email;
   
    cout << CYAN << "|---------------------------------------------------------------------------------|" << RESET << "\n";
    cout << MAGENTA << "|                                                                                 |" << RESET << "\n";
    cout << BLUE << "|\t\t\t\t" << GREEN << "S" << YELLOW << "M" << BLUE << "A" << RED << "R" << GREEN << "T" << YELLOW << "C" << BLUE << "A" << RED << "R" << GREEN << "T" << RESET << "\t\t\t\t\t  |\n";
    cout << MAGENTA << "|                                                                                 |" << RESET << "\n";
    cout << CYAN << "|---------------------------------------------------------------------------------|" << RESET << "\n";
    cout << "\n";
    cout << GREEN << "  Welcome to SmartCart - Your Supermarket Companion" << RESET << "\n";

    cout << "\n";
    cout << YELLOW << "Choose your role:" << RESET << "\n";
    cout << "\n";
    cout << GREEN << "1. Admin" << RESET << "\n";
    cout << BLUE << "2. Customer" << RESET << "\n";
    cout << RED << "3. Exit" << RESET << "\n";
    cout << "\n";
    cout<<YELLOW<<"Enter your choice: "<<RESET;
    cin>>choice;

    switch(choice)
    {
        case 1:
            cout << YELLOW << "Enter your email: " << RESET;
            cin >> email;
            cout << YELLOW << "Enter your password: " << RESET;
            cin >> password;
            cout << "\n";
            if(email == "k" && password == "0")
            {
                admin();
            }
            else
            {
                //clear screen
                cout << "\033[2J\033[1;1H";

                cout << RED << "Invalid email or password" << RESET << "\n";
                cout << "\n";
                menu(); 
            }
            break;

        case 2:
            customer();
            break;

        case 3:
            exit(0);
            break;

        default:
            cout<<"Invalid choice\n";
            break;             
}

goto menu;
}

void Shopping::admin()
{
admin:
    int choice;
    cout << CYAN << "==============================================" << RESET << endl;
    cout << MAGENTA << "\t\tADMIN MENU" << RESET << endl;
    cout << CYAN << "==============================================" << RESET << endl;
    cout << BLUE << "1. Add product" << RESET << endl;
    cout << BLUE << "2. Delete product" << RESET << endl;
    cout << BLUE << "3. Update product" << RESET << endl;
    cout << BLUE << "4. Display product" << RESET << endl;
    cout << BLUE << "5. Back to main menu" << RESET << endl;
    cout << BLUE << "6. Exit" << RESET << endl;
    cout << CYAN << "==============================================" << RESET << endl;
    cout<<"\n";
    cout<<YELLOW<<"Enter your choice: "<<RESET;
    cin>>choice;

    switch(choice)
    {
        case 1:
            add_product();
            break;

        case 2:
            delete_product();
            break;

        case 3:
            update_product();
            break;

        case 4:
            display_product();
            break;

        case 5:
            menu();
            break;

        case 6:
            exit(0);
            break;
            
        default:
            cout<<"Invalid choice\n";
            break;
    }

    goto admin;
}

void Shopping::customer()
{
customer:
    int choice;
    cout << CYAN << "-----------------------------" << RESET << endl;
    cout << MAGENTA << "          CUSTOMER" << RESET << endl;
    cout << CYAN << "-----------------------------" << RESET << endl;
    cout << BLUE << "1. Buy product" << RESET << endl;
    cout << BLUE << "2. Go to main menu" << RESET << endl;

    cin >> choice;

    switch(choice)
    {
        case 1:
            receipt(); 
            break;

        case 2:
            menu();
            break;

        default:
            cout << RED << "Invalid choice" << RESET << endl;
            break;
    }

    goto customer;
}

void Shopping::add_product()
{
add_p:
    fstream file;
    int p_code;
    int token=0;
    float p_price;
    float p_discount;
    string p_name;

    cout << BLUE << "Enter product id: " << RESET;
    cin >> product_id;
    cout << BLUE << "Enter product name: " << RESET;
    cin >> product_name;
    cout << BLUE << "Enter product price: " << RESET;
    cin >> product_price;
    cout << BLUE << "Enter product discount: " << RESET;
    cin >> product_discount;

    cout << YELLOW << "Are you sure you want to add this product? (y/n)" << RESET << endl;
    char confirm;
    cin >> confirm;
    if (confirm != 'y' && confirm != 'Y') {
        cout << RED << "Product not added." << RESET << endl;
        return;
    }

    file.open("product.txt", ios::in); // Open the file in read mode
    if(!file)
    {
        file.open("product.txt", ios::app|ios::out);
        file<<product_id<<" "<<product_name<<" "<<product_price<<" "<<product_discount<<endl;
        file.close();
    }
    else
    {
        file>>p_code>>p_name>>p_price>>p_discount;
        while(!file.eof()) // eof() - end of file 
        {
            if(p_code == product_id)
            {
                token++;
            }
            file>>p_code>>p_name>>p_price>>p_discount;
        }
        file.close();
        if(token == 1)
        {
            goto add_p;
        }
        else
        {
            file.open("product.txt", ios::app|ios::out);
            file<<product_id<<" "<<product_name<<" "<<product_price<<" "<<product_discount<<endl;
            file.close();
        }
    }
    cout << GREEN << "Product added successfully" << RESET << endl;
    cout<<"\n";
}

void Shopping::update_product() {
    fstream file, file1;
    int p_code;
    int token = 0;
    float p_price;
    float p_discount;
    string p_name;
    bool found = false;

    cout << YELLOW << "Enter product id: " << RESET;
    cin >> product_id;

    file.open("product.txt", ios::in);
    if (!file) {
        cout << RED << "File not found\n" << RESET;
    } else {
        file1.open("temp.txt", ios::out);
        while (file >> p_code >> p_name >> p_price >> p_discount) {
            if (p_code == product_id) {
                found = true;
                cout << YELLOW << "Are you sure you want to update this product? (y/n): " << RESET;
                char confirm;
                cin >> confirm;
                if (confirm == 'y' || confirm == 'Y') {
                    cout << YELLOW << "Enter new Product id: " << RESET;
                    cin >> p_code;
                    cout << YELLOW << "Enter new Product name: " << RESET;
                    cin >> p_name;
                    cout << YELLOW << "Enter new Product price: " << RESET;
                    cin >> p_price;
                    cout << YELLOW << "Enter new Product discount: " << RESET;
                    cin >> p_discount;
                    file1 << p_code << " " << p_name << " " << p_price << " " << p_discount << endl;
                    token++;
                } else {
                    file1 << p_code << " " << p_name << " " << p_price << " " << p_discount << endl;
                }
            } else {
                file1 << p_code << " " << p_name << " " << p_price << " " << p_discount << endl;
            }
        }
        file1.close();
        file.close();

        if (found) {
            remove("product.txt");
            rename("temp.txt", "product.txt");
            cout<<"\n";
            cout << GREEN << "Product updated successfully\n" << RESET;
            cout<<"\n";
        } else {
            cout << RED << "Product not found\n" << RESET;
        }
    }
}


void Shopping::delete_product()
{
    fstream file, file1;
    int p_code;
    int token=0;
    float p_price;
    float p_discount;
    string p_name;

    cout<<"Enter product id: ";
    cin>>product_id;

    file.open("product.txt", ios::in);
    if(!file)
    {
        cout<<"File not found\n";
    }
    else 
    {
        file1.open("temp.txt", ios::app|ios::out);
        file>>product_id>>product_name>>product_price>>product_discount; 
        while(!file.eof())
        {
            if(p_code == product_id)
            {
                token++;
            }
            else
            {
                file1<<product_id<<" "<<product_name<<" "<<product_price<<" "<<product_discount<<endl;
            }
            file>>product_id>>product_name>>product_price>>product_discount;

            file1.close();
            file.close();

            remove("product.txt");
            rename("temp.txt", "product.txt");

            if(token == 0)
            {
                cout<< RED << "Product not found\n";
            }
            else
            {
                cout<<"Product deleted successfully\n";
            }
        }
    }
}

void Shopping::display_product() {
    fstream file;
    int token = 0;

    file.open("product.txt", ios::in);
    if (!file) {
        cout << "\033[1;31mFile not found\033[0m\n";
    } else {
        cout << "\033[1;36m*****************************************************************\033[0m" << endl;
        cout << "\033[1;36m*                    \033[1;35mProduct List\033[1;36m                            *\033[0m" << endl;
        cout << "\033[1;36m***************************************************************** \033[0m" << endl;
        cout << "\033[1;36m| \033[1;35mProduct ID\033[1;36m | \033[1;35mProduct Name\033[1;36m         | \033[1;35mPrice\033[1;36m      | \033[1;35mDiscount\033[1;36m   |\033[0m" << endl;
        cout << "\033[1;36m*****************************************************************\033[0m" << endl;

        while (file >> product_id >> product_name >> product_price >> product_discount) {
            cout << "\033[1;36m| \033[1;33m" << setw(10) << product_id << "\033[1;36m | \033[1;33m" << setw(15) << product_name << "\033[1;36m | \033[1;33m" << setw(8) << product_price << "\033[1;36m | \033[1;33m" << setw(10) << product_discount << "\033[1;36m |\033[0m" << endl;
            token++;
        }

        cout << "\033[1;36m*****************************************************************\033[0m" << endl;
        file.close();

        if (token == 0) {
            cout << "\033[1;31mNo products found\033[0m\n";
        }
    }
}

void Shopping::receipt() {
    fstream file;

    int arrc[100];
    int arrq[100];

    char choice = 'y'; // Initialize choice to 'y'
    int token = 0;
    float total = 0;
    bool productFound = false;

    // Check if the file "product.txt" exists before opening it.
    file.open("product.txt", ios::in);
    if (!file) {
        cout << RED << "File not found\n" << RESET;
        return;
    }

    display_product();

    cout << "\n" << CYAN << "---------------- Receipt ----------------\n" << RESET;

    cout << left << setw(12) << BLUE << "ID" << setw(25) << "Product Name" << setw(10) << "Price" << setw(12) << "Discount" << setw(15) << "Quantity" << endl;
    cout << "-------------------------------------------------------------------------------------------" << endl;

    do {
        int product_id;
        float product_price;
        float product_discount;
        string product_name;

        cout << YELLOW << "Enter product id: " << RESET;
        cin >> arrc[token];

        // Check if the product ID entered by the user is valid.
        productFound = false; // Reset the flag
        file.seekg(0, ios::beg);
        while (file >> product_id >> product_name >> product_price >> product_discount) {
            if (arrc[token] == product_id) {
                productFound = true;
                break;
            }
        }

        if (!productFound) {
            cout << RED << "Product not found\n" << RESET;
            continue;
        }

        cout << left << setw(12) << product_id << setw(25) << product_name << setw(10) << product_price << setw(12) << product_discount;
        cin >> arrq[token];

        float amount = (product_price * arrq[token]);
        float discount = ((product_price * arrq[token]) * product_discount / 100);
        float discounted_price = amount - discount;
        total += discounted_price;

        cout << setw(15) << arrq[token] << setw(12) << amount << setw(20) << discounted_price << setw(10) << discount << endl;

        cout << YELLOW << "Do you want to add another product? (y/n): " << RESET;
        cout << "\n";
        cin >> choice; // Ask the user if they want to add another product
        token++;
    } while (choice == 'y' || choice == 'Y');

    cout << "-------------------------------------------------------------------------------------------" << endl;
    cout << GREEN << "Total: " << total << RESET << endl;
    cout << "\n";

    // Bill section
    cout << CYAN << "------------------ Bill ------------------\n" << RESET;
    cout << left << setw(12) << BLUE << "ID" << setw(25) << "Product Name" << setw(15) << "Quantity" << setw(15) << "Amount" << setw(20) << "Discounted Price" << RESET << endl;
    cout << "-------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < token; i++) {
        // Reopen the file to get product details.
        file.clear();
        file.seekg(0, ios::beg);
        int product_id;
        float product_price;
        float product_discount;
        string product_name;

        while (file >> product_id >> product_name >> product_price >> product_discount) {
            if (arrc[i] == product_id) {
                float amount = (product_price * arrq[i]);
                float discount = ((product_price * arrq[i] * product_discount) / 100);
                float discounted_price = amount - discount;
                cout << left << setw(12) << product_id << setw(25) << product_name << setw(15) << arrq[i] << setw(15) << amount << setw(20) << discounted_price << endl;
            }
        }
    }

    cout << "-------------------------------------------------------------------------------------------" << endl;
    cout << GREEN << "Total: " << total << RESET << endl;
    cout << "\n";

    // Informative section
    cout << CYAN << "-------------- Thank You! --------------\n" << RESET;
    cout << CYAN << "---------------------------------------\n" << RESET;
    cout << MAGENTA << "Payment Due: " << RESET << total << endl;
    cout << MAGENTA << "Payment Method: Cash/Credit Card" << RESET << endl;
    cout << MAGENTA << "Date: " << RESET << __DATE__ << endl;
}

int main()
{
    Shopping s;
    s.menu();
    return 0;
}