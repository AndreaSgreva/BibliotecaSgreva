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
void Vinile::stampaInfo() const {
    cout << *this << endl;
}
void Vinile::accept(Visitor* visitor) { 
    visitor->visit(this); 
}

//overloading
std::ostream& operator<<(std::ostream& os, const Vinile& vinile) {
    os << "Immagine: " << vinile.getImmagine() << endl;
    os << "Titolo: " << vinile.getTitolo() << endl;
    os << "Anno: " << vinile.getAnno() << endl;
    os << "Genere: " << vinile.getGenere() << endl;    
    os << "Lingua: " << vinile.getLingua() << endl;
    os << "Disponibile: " << (vinile.getDisponibile() ? "Si" : "No") << endl;
    os << "Costo: " << vinile.getCosto() << " euro"<< endl;
    os << "Numero Copie: " << vinile.getNumeroCopie() << endl;
    os << "Numero Prestiti: " << vinile.getNumeroPrestiti() << endl;
    os << "Artista: " << vinile.getArtista() << endl;
    os << "Casa Discografica: " << vinile.getCasaDiscografica() << endl;
    os << "Velocita' di riproduzione: " << vinile.getRPM() <<" rpm"<< endl;
    return os;
}