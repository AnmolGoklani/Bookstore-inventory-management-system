#include "../lib/include/book.hpp"
#include "../lib/include/magazine.hpp"
#include "../lib/include/customer.hpp"
#include "../lib/include/manager.hpp"
#include "../lib/include/cashier.hpp"
#include <regex>

// used files for storing data, so the below functions save and load data to and from the files

int load_data(Manager& manager, Cashier& cashier , vector <Customer>& customers) {
    ifstream file;

    file.open("manager.txt");
    if (!file) {
        cout << "Unable to open manager.txt";
        return 1;
    }
    string name, employee_id;
    getline(file, name);
    getline(file, employee_id);

    manager = Manager(name, employee_id);
    file.close();

    file.open("customer.txt");
    if (!file) {
        cout << "Unable to open customer.txt";
        return 1;
    }
    string email, points;
    while (getline(file, name, ',') && !file.eof()) {
        getline(file, email, ',');
        getline(file, points);
        customers.push_back(Customer(name, email, stoi(points)));
    }
    file.close();

    file.open("book.txt");
    if (!file) {
        cout << "Unable to open book.txt";
        return 1;
    }
    cashier.load_books(file);
    file.close();

    file.open("profit.txt");
    if (!file) {
        cout << "Unable to open profit.txt";
        return 1;
    }
    cashier.load_profit(file);
    file.close();

    file.open("magazine.txt");
    if (!file) {
        cout << "Unable to open magazine.txt";
        return 1;
    }
    cashier.load_magazines(file);
    file.close();
    
    return 0;

}

int save_data(Manager& manager, Cashier& cashier, vector <Customer>& customers) {
    ofstream file;

    file.open("manager.txt");
    if (!file) {
        cout << "Unable to open manager.txt";
        return 1;
    }
    file.clear();
    file << manager.getName() << endl;
    file << manager.getManagerId() << endl;
    file.close();

    file.open("customer.txt");
    if (!file) {
        cout << "Unable to open customer.txt";
        return 1;
    }
    for (Customer customer : customers) {
        file << customer.getName() << "," << customer.getEmail() << "," << customer.getPoints() << endl;
    }
    file.close();

    file.open("book.txt");
    if (!file) {
        cout << "Unable to open book.txt";
        return 1;
    }
    cashier.save_books(file);
    file.close();

    file.open("profit.txt");
    if (!file) {
        cout << "Unable to open profit.txt";
        return 1;
    }
    cashier.save_profit(file);
    file.close();

    file.open("magazine.txt");
    if (!file) {
        cout << "Unable to open magazine.txt";
        return 1;
    }
   
    cashier.save_magazines(file);

    file.close();

    return 0;
}

// function to verify email of the customer
bool verify_email(const string& email) {
    const regex pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    return regex_match(email, pattern);
}

int main() {
    Manager manager;
    Cashier cashier;
    
    vector<Customer> customers;

    if (load_data(manager, cashier, customers) != 0) {
        cout << "Error loading data" << endl;
    }

    int quit = 0;

    //main game loop
    while(!quit){
        cout << "Welcome to the Bookstore, press" << endl;
        cout << "1 to Login as Manager" << endl;
        cout << "2 to Login as Customer" << endl;
        cout << "3 to New Customer" << endl;
        cout << "Any other key to Quit" << endl << endl;

        int option;
        cin >> option;

        //manager
        if(option == 1){
            string name, employee_id;
            cout << "Enter name: ";
            getline(cin >> ws, name);
            cout << "Enter employee_id: ";
            cin >> employee_id;
            if(manager.checkCredentials(name, employee_id)){
                cout << "Welcome " << name << endl;
                while(1){
                    cout << "Press:" << endl;
                    cout << "1 to add items to the inventory" << endl;
                    cout << "2 to delete items from the inventory" << endl;
                    cout << "3 to view profit" << endl;  //this is the profit since the bookstore started its operations
                    cout << "4 to view list of all items" << endl;
                    cout << "5 to view items low on stock" << endl;
                    cout << "6 to change the details of an item" << endl;
                    cout << "Any other key to Logout" << endl;

                    int opt;
                    cin >> opt;

                    //add items to inventory
                    if(opt == 1){
                        while(1){
                            cout<<"Press 1 to add a book, 2 to add a magazine, anything else to go back: ";
                            int choice;
                            cin >> choice;

                            //book
                            if(choice == 1){
                                while(1){
                                    cout << "Press 1 for restock, 2 for new book anything else to go back: ";
                                    int restock;
                                    cin >> restock;
                                    if(restock == 1){
                                        cout << "Enter the id of the book you want to restock: ";
                                        int id;
                                        cin >> id;
                                        cout << "Enter the number of books you want to add: ";
                                        int stock;
                                        cin >> stock;
                                        manager.restockBook(id, stock);
                        
                                    }
                                    else if(restock == 2){
                                        manager.addBook(); // adding new book
                                    }
                                    else{
                                        break;
                                    }
                                }
                            }
                            //magazine
                            else if(choice == 2){
                                while(1){
                                    cout << "Press 1 for restock, 2 for new magazine, anything else to go back: ";
                                    int restock;
                                    cin >> restock;
                                    if(restock == 1){
                                        cout << "Enter the id of the magazine you want to restock: ";
                                        int id;
                                        cin >> id;
                                        cout << "Enter the number of magazines you want to add: ";
                                        int stock;
                                        cin >> stock;
                                        manager.restockMagazine(id, stock);
                                    }
                                    else if(restock == 2){
                                        manager.addMagazine(); // adding new magazine
                                    }
                                    else{
                                        break;
                                    }
                                }
                            }
                            else{
                                break;
                            }
                        }
                    }

                    //delete items from inventory
                    else if(opt == 2){
                        while(1){
                            cout << "Press 1 to delete a book, 2 to delete a magazine, anything else to go back: ";
                            int choice;
                            cin >> choice;
                            //delete book
                            if(choice == 1){
                                cout << "Enter the id of the book you want to delete: ";
                                int id;
                                cin >> id;
                                manager.deleteBook(id);
                            }
                            //delete magazine
                            else if(choice == 2){
                                cout << "Enter the id of the magazine you want to delete: ";
                                int id;
                                cin >> id;
                                manager.deleteMagazine(id);
                            }
                            else{
                                break;
                            }
                        }
                    }
                    else if(opt == 3){
                        cout << "Daily profit: " << manager.getProfit() << endl;
                    }
                    //view detailed list of all items
                    else if(opt == 4){
                        manager.printItems();
                    }
                    //view items low on stock
                    else if(opt == 5){
                        manager.printLowStock();
                    }
                    //change the details of an item
                    else if(opt == 6){
                        while(1){
                            cout << "Press 1 to change the cost of an item, 2 to change the price of an item, anything else to go back: ";
                            int choice;
                            cin >> choice;
                            //change cost
                            if(choice == 1){
                                cout << "Enter the id of the item you want to change the cost of: ";
                                int id;
                                cin >> id;
                                cout << "Enter the new cost: ";
                                double cost;
                                cin >> cost;
                                manager.changeCost(id, cost);
                            }
                            //change price
                            else if(choice == 2){
                                cout << "Enter the id of the item you want to change the price of: ";
                                int id;
                                cin >> id;
                                cout << "Enter the new price: ";
                                double price;
                                cin >> price;
                                manager.changePrice(id, price);
                            }
                            else{
                                break;
                            }
                        }
                    }
                    else{
                        break;
                    }
                    
                } // the loop for manager ends here
                
            }
            else {
                cout << "Invalid credentials" << endl;
            }


        }
        //customer login
        else if(option == 2){
            string name, email;
            cout << "Enter name: ";
            getline(cin >> ws, name);
            cout << "Enter email: ";
            cin >> email;
            while(!verify_email(email)){ //email verification
                cout << "Invalid email. Please enter a valid email: ";
                cin >> email;
            }
            int login = 0;
            for(Customer customer : customers){
                if(customer.checkCredentials(name, email)){
                    login = 1;
                    cout << "Welcome " << name << "!" << endl;
                    cout << " You have " << customer.getPoints() << " points in your account. Buy more items to collect more points and get exciting discounts!" << endl <<endl;
                    
                    while(1){
                        cout << "Press" << endl;
                        cout << "1 to Buy Book" << endl;
                        cout << "2 to Buy Magazine" << endl;
                        cout << "3 to display cart or checkout" << endl;
                        cout << "Any other key to Logout (your cart will be gone)" << endl;
                        int opt;
                        cin >> opt;

                        //book
                        if(opt == 1){
                            while(1){
                                cout<<"Great! Now let's help you find the perfect book for you."<<endl;
                                cout << "Press: " << endl;
                                cout << "1 to see book written by a particular author" << endl;
                                cout << "2 to see books of a particular genre" << endl;
                                cout << "3 if you know what you want to buy" << endl;
                                cout << "Any other key to go back" << endl;
                                int choice;
                                cin >> choice;

                                //author based search
                                if(choice == 1){
                                    string author;
                                    cout <<endl<< "Enter author: ";
                                    getline(cin >> ws, author);
                                    cashier.printBooksByAuthor(author);
                                    cout<<endl<<"Enter the ids of the book you want to add to your cart (when you're done press 0): "<<endl;
                                    int id;
                                    //adding books to cart
                                    while(1){
                                        cin >> id;
                                        if(id == 0){
                                            break;
                                        }
                                        else{
                                            cashier.addBookToCart(id);
                                        }
                                    }

                                }
                                //genre based search
                                else if(choice == 2){
                                    cout <<endl<< "Enter genre (Fantasy, Science Fiction, Mystery, Romance, Horror, Non Fiction, Other): ";
                                    string genre;
                                    cin >> genre;
                                    cashier.printBooksByGenre(stringToGenre(genre));
                                    cout<<endl<<"Enter the ids of the book you want to add to your cart (when you're done press 0): "<<endl;
                                    int id;
                                    //adding books to cart
                                    while(1){
                                        cin >> id;
                                        if(id == 0){
                                            break;
                                        }
                                        else{
                                            cashier.addBookToCart(id);
                                        }
                                    }
                                }
                                //when the customer knows the book they want to buy
                                else if(choice == 3){
                                    cout << "If you know the isbn of the book enter that, else press 0: ";
                                    string isbn;
                                    cin >> isbn; //unique code for every book

                                    if(isbn != "0"){
                                        isbn.erase(remove(isbn.begin(), isbn.end(), '-'), isbn.end()); //in case someone adds dashes in their input
                                        cashier.addBookByIsbn(isbn);
                                    }
                                    else{
                                        cout<<"Enter the title of the book:";
                                        string title;
                                        getline(cin >> ws, title);
                                        cout<<"Enter the author of the book:";
                                        string author;
                                        getline(cin >> ws, author);
                                        cashier.addBookByTitleAuthor(title, author);
                                    }

                                }
                                else{
                                    break;
                                }
                            }
                        }
                        //magazine
                        else if(opt == 2){
                            cout<<"Here is a list of all the magazines we have: "<<endl;
                            cashier.printMagazines();

                            cout<<endl<<"Enter the ids of the magazine you want to add to your cart (when you're done press 0): "<<endl;
                            int id;
                            //adding magazines to cart
                            while(1){
                                cin >> id;
                                if(id == 0){
                                    break;
                                }
                                else{
                                    cashier.addBookToCart(id);
                                }
                            }

                            cout<<endl<<endl;

                        }
                        //display cart or checkout
                        //if the customer wants to back down at any point, they can do it and their cart remains safe
                        else if(opt == 3){
                            cashier.displayCart();
                            cout<<"Do you wanna finalise purchase? Press 1 to checkout, any other key to continue exploring: ";
                            int checkout;
                            cin >> checkout;
                            if(checkout == 1){
                                //confirming the final cart
                                cashier.displayCart();
                                cout<<"Enter the ids of the elements you want to remove from your cart, when you're done press 0: "<<endl;
                                int id;
                                while(1){
                                    cin >> id;
                                    if(id == 0){
                                        break;
                                    }
                                    else{
                                        cashier.removeItemFromCart(id);
                                    }
                                }

                                cashier.displayCart();
                                cout<<"Press 1 to continue, any other key to continue exploring: ";
                                int check;
                                cin >> check;
                                if(check == 1){
                                    cashier.checkout(customer);
                                }
                                else{
                                    cout<<"No worries! Hope you find what you like. Yout purchase was cancelled, your cart is still full."<<endl;
                                }


                            }
                        }
                        else{
                            break;
                        }

                    }

                    break;
                    
                }// end of customer login loop
            }
            if(!login){
                cout << "Customer doesnt exist, try signing up instead." << endl;
            }
        }
        else if(option == 3){
            string name, email;
            cout << "Enter name: ";
            getline(cin >> ws, name);
            cout << "Enter email: ";
            cin >> email;
            while(!verify_email(email)){
                cout << "Invalid email. Please enter a valid email: ";
                cin >> email;
            }
            
            bool customerExists = false;
            Customer curr_customer;
            for(Customer customer : customers){
                if(customer.checkCredentials(name, email)){
                    cout << "Hello again " << name << "! Your account already exists. You have " << customer.getPoints() << " points in your account. Buy items to collect more points and get exciting discounts!" << endl;
                    customerExists = true;
                    curr_customer = customer;
                    break;
                }
            }
            if(!customerExists){
                curr_customer = Customer(name, email, 0);
                customers.push_back(curr_customer);
                cout << "Welcome aboard, " << name << "!" << endl;
                cout << "Currently, you have 0 points in your account. Buy items to collect more points and get exciting discounts!" << endl << endl;
            }

            while(1){
                cout << "Press" << endl;
                cout << "1 to Buy Book" << endl;
                cout << "2 to Buy Magazine" << endl;
                cout << "3 to display cart or checkout" << endl;
                cout << "Any other key to Logout (your cart will be gone)" << endl;
                int opt;
                cin >> opt;

                //book
                if(opt == 1){
                    while(1){
                        cout<<"Great! Now let's help you find the perfect book for you."<<endl;
                        cout << "Press: " << endl;
                        cout << "1 to see book written by a particular author" << endl;
                        cout << "2 to see books of a particular genre" << endl;
                        cout << "3 if you know what you want to buy" << endl;
                        cout << "Any other key to go back" << endl;
                        int choice;
                        cin >> choice;

                        //author based search
                        if(choice == 1){
                            string author;
                            cout <<endl<< "Enter author: ";
                            getline(cin >> ws, author);
                            cashier.printBooksByAuthor(author);
                            cout<<endl<<"Enter the ids of the book you want to add to your cart (when you're done press 0): "<<endl;
                            int id;
                            //adding books to cart
                            while(1){
                                cin >> id;
                                if(id == 0){
                                    break;
                                }
                                else{
                                    cashier.addBookToCart(id);
                                }
                            }

                        }
                        //genre based search
                        else if(choice == 2){
                            cout <<endl<< "Enter genre (Fantasy, Science Fiction, Mystery, Romance, Horror, Non Fiction, Other): ";
                            string genre;
                            cin >> genre;
                            cashier.printBooksByGenre(stringToGenre(genre));
                            cout<<endl<<"Enter the ids of the book you want to add to your cart (when you're done press 0): "<<endl;
                            int id;
                            //adding books to cart
                            while(1){
                                cin >> id;
                                if(id == 0){
                                    break;
                                }
                                else{
                                    cashier.addBookToCart(id);
                                }
                            }
                        }
                        //when the customer knows the book they want to buy
                        else if(choice == 3){
                            cout << "If you know the isbn of the book enter that, else press 0: ";
                            string isbn;
                            cin >> isbn; //unique code for every book

                            if(isbn != "0"){
                                isbn.erase(remove(isbn.begin(), isbn.end(), '-'), isbn.end()); //in case someone adds dashes in their input
                                cashier.addBookByIsbn(isbn);
                            }
                            else{
                                cout<<"Enter the title of the book:";
                                string title;
                                getline(cin >> ws, title);
                                cout<<"Enter the author of the book:";
                                string author;
                                getline(cin >> ws, author);
                                cashier.addBookByTitleAuthor(title, author);
                            }

                        }
                        else{
                            break;
                        }
                    }
                }
                //magazine
                else if(opt == 2){
                    cout<<"Here is a list of all the magazines we have: "<<endl;
                    cashier.printMagazines();

                    cout<<endl<<"Enter the ids of the magazine you want to add to your cart (when you're done press 0): "<<endl;
                    int id;
                    //adding magazines to cart
                    while(1){
                        cin >> id;
                        if(id == 0){
                            break;
                        }
                        else{
                            cashier.addBookToCart(id);
                        }
                    }

                    cout<<endl<<endl;

                }
                //display cart or checkout
                //if the customer wants to back down at any point, they can do it and their cart remains safe
                else if(opt == 3){
                    cashier.displayCart();
                    cout<<"Do you wanna finalise purchase? Press 1 to checkout, any other key to continue exploring: ";
                    int checkout;
                    cin >> checkout;
                    if(checkout == 1){
                        //confirming the final cart
                        cashier.displayCart();
                        cout<<"Enter the ids of the elements you want to remove from your cart, when you're done press 0: "<<endl;
                        int id;
                        while(1){
                            cin >> id;
                            if(id == 0){
                                break;
                            }
                            else{
                                cashier.removeItemFromCart(id);
                            }
                        }

                        cashier.displayCart();
                        cout<<"Press 1 to continue, any other key to continue exploring: ";
                        int check;
                        cin >> check;
                        if(check == 1){
                            cashier.checkout(curr_customer);
                        }
                        else{
                            cout<<"No worries! Hope you find what you like. Yout purchase was cancelled, your cart is still full."<<endl;
                        }


                    }
                }
                else{
                    break;
                }

            }

        }
        else{
            quit = 1;
        } 
    }

    if (save_data(manager, cashier, customers) != 0) {
        cout << "Error saving data" << endl;
    }

    return 0;
}