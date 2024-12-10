#ifndef ITEM_HPP
#define ITEM_HPP

#include <iostream>
#include <string>

using namespace std;

class Manager;  // predeclaration to avoid circular dependency

class Item{
    private:
        static int id_counter; // to keep track of the id of the items (auto-incremented)
        int id;
        string title;
        string publisher;
        double cost;
        double price;
        int stock;

    public:

        friend class Manager; // so that Manager can access the private attributes of Item and change cost and price

        Item() : id(++id_counter), title(""), publisher(""), cost(0.0), price(0.0), stock(0) {}
        Item(const string& title, const string& publisher, const double& cost, const double& price, const int& stock){
            this->id = ++id_counter;
            this->title = title;
            this->publisher = publisher;
            this->cost = cost;
            this->price = price;
            this->stock = stock;
        }

        // the below 3 virtual functions are overridden in the derived classes
        // and are written to be used by the derived classes
        virtual void print(){
            cout << "ID: " << this->id << endl;
            cout << "Title: " << this->title << endl;
            cout << "Publisher: " << this->publisher << endl;
            cout << "Cost: " << this->cost << endl;
            cout << "Price: " << this->price << endl;
            cout << "Stock: " << this->stock << endl;
        } 

        // print function for the manager to print all the details that the manager needs
        virtual void printManagerinfo(){
            cout << "ID: " << this->id << endl;
            cout << "Title: " << this->title << endl;
            cout << "Publisher: " << this->publisher << endl;
            cout << "Cost: " << this->cost << endl;
            cout << "Price: " << this->price << endl;
            cout << "Stock: " << this->stock << endl;
        }


        // print function for the cashier to print things customers are interested in
        virtual void printCustomerInfo(){
            if(this->stock){
                cout << "ID: " << this->id << endl;
                cout << "Title: " << this->title << endl;
                cout << "Publisher: " << this->publisher << endl;
                cout << "Price: " << this->price << endl;
            }
        }

        //i wrote get functions so that the cashier can access the private attributes of the items but not change them
        //the customers can't access the books directly (as the vector of books is stored in Employee class) so they 
        // can't use these get functions on the books in the inventory.

        int getId() const {
            return id;
        }

        string getTitle() const {
            return title;
        }

        string getPublisher() const {
            return publisher;
        }

        double getCost() const {
            return cost;
        }

        double getPrice() const {
            return price;
        }

        int getStock() const {
            return stock;
        }

        // used by cashier to substract from stock when a customer buys something
        void setStock(const int& stock){
            this->stock = stock;
        }


};

int Item::id_counter = 0;

#endif