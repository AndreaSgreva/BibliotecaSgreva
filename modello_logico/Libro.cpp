//File Libro.cpp
#include "Libro.h"
#include <iostream>
using namespace std;

//costruttore
Libro::Libro(const string& image, const string& title, int year, const string& genre, const string& language, bool available, double cost, 
    int numberCopies, int numberLoans, const string& autor, int pages, const string& code) : Biblioteca(image, title, year, genre, 
        language, available, cost, numberCopies, numberLoans), autore(autor), pagine(pages), isbn(code){}

//getters
string Libro::getAutore() const { return autore; }
int Libro::getPagine() const { return pagine; }
//string Libro::getLingua() const { return lingua; }
string Libro::getISBN() const { return isbn; }

//setters
void Libro::setAutore(const string& autor) { autore = autor; }
void Libro::setPagine(const int& pages) { pagine = pages; }
//void Libro::setLingua(const string& language) { lingua = language; }
void Libro::setISBN(const string& code) { isbn = code; }

//metodi
void Libro::accept(Visitor* visitor) { 
    visitor->visit(this); 
}