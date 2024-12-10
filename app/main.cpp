#include "../lib/include/book.hpp"
#include "../lib/include/magazine.hpp"
#include "../lib/include/customer.hpp"
#include "../lib/include/manager.hpp"
#include "../lib/include/cashier.hpp"
#include <regex>

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

    file.open("cashier.txt");
    if (!file) {
        cout << "Unable to open cashier.txt";
        return 1;
    }
    getline(file, name);
    getline(file, employee_id);
    cashier = Cashier(name, employee_id);
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
    file << manager.getEmployeeId() << endl;
    file.close();

    file.open("cashier.txt");
    if (!file) {
        cout << "Unable to open cashier.txt";
        return 1;
    }
    file << cashier.getName() << endl;
    file << cashier.getEmployeeId() << endl;
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

    file.open("magazine.txt");
    if (!file) {
        cout << "Unable to open magazine.txt";
        return 1;
    }
   
    cashier.save_magazines(file);

    file.close();

    return 0;
}

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

    // for (Book book : books) {
    //     book.print();
    // }

    // for (Magazine magazine : magazines) {
    //     magazine.print();
    // }
    
    int quit = 0;

    while(!quit){
        cout << "Welcome to the Bookstore, press" << endl;
        cout << "1 to Login as Manager" << endl;
        cout << "2 to Login as Cashier" << endl;
        cout << "3 to Login as Customer" << endl;
        cout << "4 to New Customer" << endl;
        cout << "Any other key to Quit" << endl << endl;

        int option;
        cin >> option;

        if(option == 1){
            string name, employee_id;
            cout << "Enter name: ";
            getline(cin >> ws, name);
            cout << "Enter employee_id: ";
            cin >> employee_id;
            if(manager.checkCredentials(name, employee_id)){
                cout << "Welcome " << name << endl;
            } else {
                cout << "Invalid credentials" << endl;
            }
        }
        else if(option == 2){
            string name, employee_id;
            cout << "Enter name: ";
            getline(cin >> ws, name);
            cout << "Enter employee_id: ";
            cin >> employee_id;
            if(cashier.checkCredentials(name, employee_id)){
                cout << "Welcome " << name << endl;
            } else {
                cout << "Invalid credentials" << endl;
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
                        cout << "Any other key to Logout" << endl;
                        int opt;
                        cin >> opt;
                        if(opt == 1){
                            while(1){
                                cout<<"Great! Now let's help you find the perfect book for you."<<endl;
                                cout << "Do you want a particular author or a genre? (1 for author, 2 for genre, 3 to go back)" << endl;
                                int choice;
                                cin >> choice;
                                if(choice == 1){
                                    string author;
                                    cout <<endl<< "Enter author: ";
                                    getline(cin >> ws, author);
                                    cashier.printBooksByAuthor(author);
                                    cout<<endl<<"Enter the ids of the book you want to add to your cart (when you're done press 0): "<<endl;
                                    int id;
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
                                else if(choice == 2){
                                    cout <<endl<< "Enter genre (Fantasy, Science Fiction, Mystery, Romance, Horror, Non Fiction, Other): ";
                                    string genre;
                                    cin >> genre;
                                    cashier.printBooksByGenre(stringToGenre(genre));
                                    cout<<endl<<"Enter the ids of the book you want to add to your cart (when you're done press 0): "<<endl;
                                    int id;
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
                                else{
                                    break;
                                }
                            }
                        }
                        else if(opt == 2){
                            cout<<"Here is a list of all the magazines we have: "<<endl;
                            cashier.printMagazines();

                            cout<<endl<<"Enter the ids of the magazine you want to add to your cart (when you're done press 0): "<<endl;
                            int id;
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
                        else{
                            break;
                        }

                    }
                    break;
                    
                }
            }
            if(!login){
                cout << "Customer doesnt exist, try signing up instead." << endl;
            }
        }
        else if(option == 4){
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
            for(Customer customer : customers){
                if(customer.checkCredentials(name, email)){
                    cout << "Hello again " << name << "! Your account already exists. You have " << customer.getPoints() << " points in your account. Buy items to collect more points and get exciting discounts!" << endl;
                    customerExists = true;
                    while(1){
                        cout << "Press" << endl;
                        cout << "1 to Buy Book" << endl;
                        cout << "2 to Buy Magazine" << endl;
                        cout << "Any other key to Logout" << endl;
                        int opt;
                        cin >> opt;
                        if(opt == 1){
                            while(1){
                                cout<<"Great! Now let's help you find the perfect book for you."<<endl;
                                cout << "Do you want a particular author or a genre? (1 for author, 2 for genre, 3 to go back)" << endl;
                                int choice;
                                cin >> choice;
                                if(choice == 1){
                                    string author;
                                    cout <<endl<< "Enter author: ";
                                    getline(cin >> ws, author);
                                    cashier.printBooksByAuthor(author);
                                    cout<<endl<<"Enter the ids of the book you want to add to your cart (when you're done press 0): "<<endl;
                                    int id;
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
                                else if(choice == 2){
                                    cout <<endl<< "Enter genre (Fantasy, Science Fiction, Mystery, Romance, Horror, Non Fiction, Other): ";
                                    string genre;
                                    cin >> genre;
                                    cashier.printBooksByGenre(stringToGenre(genre));
                                    cout<<endl<<"Enter the ids of the book you want to add to your cart (when you're done press 0): "<<endl;
                                    int id;
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
                                else{
                                    break;
                                }
                            }
                        }
                        else if(opt == 2){
                            cout<<"Here is a list of all the magazines we have: "<<endl;
                            cashier.printMagazines();

                            cout<<endl<<"Enter the ids of the magazine you want to add to your cart (when you're done press 0): "<<endl;
                            int id;
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
                        else{
                            break;
                        }

                    }
                    break;
                }
            }
            if(!customerExists){
                customers.push_back(Customer(name, email, 0));
                cout << "Welcome aboard, " << name << "!" << endl;
                cout << "Currently, you have 0 points in your account. Buy items to collect more points and get exciting discounts!" << endl << endl;
                while(1){
                    cout << "Press" << endl;
                    cout << "1 to Buy Book" << endl;
                    cout << "2 to Buy Magazine" << endl;
                    cout << "Any other key to Logout" << endl;
                    int opt;
                    cin >> opt;
                    if(opt == 1){
                        while(1){
                            cout<<"Great! Now let's help you find the perfect book for you."<<endl;
                            cout << "Do you want a particular author or a genre? (1 for author, 2 for genre, 3 to go back)" << endl;
                            int choice;
                            cin >> choice;
                            if(choice == 1){
                                string author;
                                cout <<endl<< "Enter author: ";
                                getline(cin >> ws, author);
                                cashier.printBooksByAuthor(author);
                                cout<<endl<<"Enter the ids of the book you want to add to your cart (when you're done press 0): "<<endl;
                                int id;
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
                            else if(choice == 2){
                                cout <<endl<< "Enter genre (Fantasy, Science Fiction, Mystery, Romance, Horror, Non Fiction, Other): ";
                                string genre;
                                cin >> genre;
                                cashier.printBooksByGenre(stringToGenre(genre));
                                cout<<endl<<"Enter the ids of the book you want to add to your cart (when you're done press 0): "<<endl;
                                int id;
                                while(1){
                                    cin >> id;
                                    if(id == 0){
                                        break;
                                    }
                                    else{
                                        cashier.addBookToCart(id);
                                    }
                                }
                                cout<<endl;
                            }
                            else{
                                break;
                            }
                        }
                    }
                    else if(opt == 2){
                        cout<<"Here is a list of all the magazines we have: "<<endl;
                        cashier.printMagazines();

                        cout<<endl<<"Enter the ids of the magazine you want to add to your cart (when you're done press 0): "<<endl;
                        int id;
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
                    else{
                        break;
                    }

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