#ifndef BOOK_HPP
#define BOOK_HPP

#include <iostream>
#include <string>
#include <algorithm>
#include "item.hpp"

using namespace std;

enum Genre
{
    FANTASY,
    SCIENCE_FICTION,
    MYSTERY,
    ROMANCE,
    HORROR,
    NON_FICTION,
    OTHER
};


class Book : public Item {
    private:
        string isbn;
        string author;
        Genre genre;
        int pages;

    public:
        Book() : Item(), isbn(""), author(""), genre(OTHER), pages(0) {}
        Book(const string& title, const string& publisher, const double& cost, const double& price, const int& stock, const string& isbn, const string& author, const Genre& genre, const int& pages) : Item(title, publisher, cost, price, stock) {
            this->isbn = isbn;
            this->author = author;
            this->genre = genre;
            this->pages = pages;
        }
        void print(){
            Item::print();
            cout << "ISBN: " << this->isbn << endl;
            cout << "Author: " << this->author << endl;
            cout << "Genre: " << genreToString() << endl;
            cout << "Pages: " << this->pages << endl;
        }

        

        void printCustomerInfo(){
            Item::printCustomerInfo();
            if(getStock()){
                cout << "ISBN: " << this->isbn << endl;
                cout << "Author: " << this->author << endl;
                cout << "Genre: " << genreToString() << endl;
                cout << "Pages: " << this->pages << endl;
            }
        }
        string genreToString(){
            switch (this->genre)
            {
            case FANTASY:
                return "Fantasy";
                break;
            case SCIENCE_FICTION:
                return "Science Fiction";
                break;
            case MYSTERY:
                return "Mystery";
                break;
            case ROMANCE:
                return "Romance";
                break;
            case HORROR:
                return "Horror";
                break;
            case NON_FICTION:
                return "Non Fiction";
                break;
            default:
                return "Other";
                break;
            }
        }
        string getIsbn() const {
            return isbn;
        }

        string getAuthor() const {
            return author;
        }

        Genre getGenre() const {
            return genre;
        }

        int getPages() const {
            return pages;
        }

};

Genre stringToGenre(string genre){
    transform(genre.begin(), genre.end(), genre.begin(), ::toupper);
    if (genre == "FANTASY")
        return FANTASY;
    else if (genre == "SCIENCE FICTION")
        return SCIENCE_FICTION;
    else if (genre == "MYSTERY")
        return MYSTERY;
    else if (genre == "ROMANCE")
        return ROMANCE;
    else if (genre == "HORROR")
        return HORROR;
    else if (genre == "NON FICTION")
        return NON_FICTION;
    else
        return OTHER;
}



#endif