//File Libro.h
#ifndef LIBRO_H
#define LIBRO_H
#include "Biblioteca.h"
#include <string>
using std::string;

class Libro : public Biblioteca {
    private:
        string autore;
        int pagine;
        string isbn;
    public:
        //costruttore
        Libro(const string& image, const string& title, int year, const string& genre, const string& language, bool available, double cost, 
            int numberCopies, int numberLoans, const string& autor, int pages, const string& code);

        //getters
        string getAutore() const;
        int getPagine() const;
        string getISBN() const;

        //setters
        void setAutore(const string& autor);
        void setPagine(const int& pages);
        void setISBN(const string& code);

        //metodi
        virtual void accept(Visitor* visitor) override;

};

#endif