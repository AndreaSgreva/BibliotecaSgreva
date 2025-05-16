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
        Libro(string image, string title, int year, string genre, string language, bool available, double cost, 
            int numberCopies, int numberLoans, string autor, int pages, string code);

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