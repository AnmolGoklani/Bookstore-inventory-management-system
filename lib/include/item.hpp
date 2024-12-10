#ifndef ITEM_HPP
#define ITEM_HPP

#include <iostream>
#include <string>

using namespace std;

class Item{
    private:
        static int id_counter;
        int id;
        string title;
        string publisher;
        double cost;
        double price;
        int stock;

    public:
        Item() : id(++id_counter), title(""), publisher(""), cost(0.0), price(0.0), stock(0) {}
        Item(const string& title, const string& publisher, const double& cost, const double& price, const int& stock){
            this->id = ++id_counter;
            this->title = title;
            this->publisher = publisher;
            this->cost = cost;
            this->price = price;
            this->stock = stock;
        }
        virtual void print(){
            cout << "ID: " << this->id << endl;
            cout << "Title: " << this->title << endl;
            cout << "Publisher: " << this->publisher << endl;
            cout << "Cost: " << this->cost << endl;
            cout << "Price: " << this->price << endl;
            cout << "Stock: " << this->stock << endl;
        } 
        virtual void printCustomerInfo(){
            if(this->stock){
                cout << "ID: " << this->id << endl;
                cout << "Title: " << this->title << endl;
                cout << "Publisher: " << this->publisher << endl;
                cout << "Price: " << this->price << endl;
            }
        }
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


};

int Item::id_counter = 0;

#endif