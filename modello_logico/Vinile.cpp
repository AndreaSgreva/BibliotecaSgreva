//File Vinile.cpp
#include "Vinile.h"
#include <iostream>
using namespace std;

//costruttore
Vinile::Vinile(string image, string title, int year, string genre, string language, bool available, double cost, 
    int numberCopies, int numberLoans, string artist, string recordCompany, int rpm) : Biblioteca(image, title, year, 
    genre, language, available, cost, numberCopies, numberLoans), artista(artist), 
    casaDiscografica(recordCompany), rpm(rpm) {}

//getters
string Vinile::getArtista() const { return artista; }
string Vinile::getCasaDiscografica() const { return casaDiscografica;}
int Vinile::getRPM() const { return rpm; }

//setters
void Vinile::setArtista(const string& artist) { artista = artist; }
void Vinile::setCasaDiscografica(const string& recordCompany) { casaDiscografica = recordCompany; }
void Vinile::setRPM(const int& rpm) { this->rpm = rpm; }

//metodi
void Vinile::accept(Visitor* visitor) { 
    visitor->visit(this); 
}