//File Biblioteca.cpp
#include "Biblioteca.h"
#include <iostream>
using namespace std;

//costruttore e distruttore
Biblioteca::Biblioteca(string image,string title, int year, string genre, string language, bool available, 
    double cost, int numberCopies, int numberLoans) : immagine(image), titolo(title), anno(year), genere(genre), 
    lingua(language), disponibile(available), costo(cost), numeroCopie(numberCopies < 1 ? 1 : numberCopies), 
    numeroPrestiti(numberLoans < 0 ? 0 : numberLoans) {}

//getters
string Biblioteca::getImmagine() const { return immagine; }
string Biblioteca::getTitolo() const { return titolo; }
int Biblioteca::getAnno() const { return anno; }
string Biblioteca::getGenere() const { return genere; }
string Biblioteca::getLingua() const { return lingua; }
bool Biblioteca::getDisponibile() const { return disponibile; }
double Biblioteca::getCosto() const { return costo; }
int Biblioteca::getNumeroCopie() const { return numeroCopie; }
int Biblioteca::getNumeroPrestiti() const { return numeroPrestiti; }

//setters
void Biblioteca::setImmagine(const string& image) { immagine = image; }
void Biblioteca::setTitolo(const string& title) { titolo = title; }
void Biblioteca::setAnno(const int& year) { anno = year; }
void Biblioteca::setGenere(const string& genre) { genere = genre; }
void Biblioteca::setLingua(const string& language) { lingua = language; }
void Biblioteca::setCosto(const double& cost) { costo = cost; }
void Biblioteca::setNumeroCopie(const int& numberCopies) { numeroCopie = numberCopies; }
void Biblioteca::setNumeroPrestiti(const int& numberLoans) { numeroPrestiti = numberLoans; }


//metodi
/*void Biblioteca::stampaInfo() const {
    cout << this << endl;
}*/

void Biblioteca::prenota() {
    if (disponibile){
        numeroPrestiti++;
        if (numeroPrestiti == numeroCopie) {
            cout << "Prestiti finiti" << endl;
            disponibile = false;
        }
    }
    else cout << "Copie non disponibili" << endl;
    return;
}
void Biblioteca::restituisci() {    
    if(!disponibile) disponibile = true;
    if(numeroPrestiti > 0) numeroPrestiti--;
}

//overloading
std::ostream& operator<<(std::ostream& os, const Biblioteca& b) {
    os << "Titolo: " << b.getTitolo() << endl;
    os << "Anno: " << b.getAnno() << endl;
    os << "Genere: " << b.getGenere() << endl;   
    os << "Lingua: " << b.getLingua() << endl; 
    os << "Disponibile: " << (b.getDisponibile() ? "Si" : "No") << endl;
    os << "Costo: " << b.getCosto() << " euro"<< endl;
    os << "Numero Copie: " << b.getNumeroCopie() << endl;
    os << "Numero Prestiti: " << b.getNumeroPrestiti() << endl;
    return os;
}

