//File Biblioteca.cpp
#include "Biblioteca.h"
#include <iostream>
using namespace std;

//costruttore e distruttore
Biblioteca::Biblioteca(const string& image, const string& title, int year, const string& genre, const string& language, bool available, 
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
void Biblioteca::setDisponibile(const bool& available) { disponibile = available; }
void Biblioteca::setCosto(const double& cost) { costo = cost; }
void Biblioteca::setNumeroCopie(const int& numberCopies) { numeroCopie = numberCopies; }
void Biblioteca::setNumeroPrestiti(const int& numberLoans) { numeroPrestiti = numberLoans; }

bool Biblioteca::prenota() {
    if (numeroPrestiti >= numeroCopie) return false;
    
    numeroPrestiti++;
    disponibile = (numeroPrestiti < numeroCopie);
    return true;
}

bool Biblioteca::restituisci() {
    if (numeroPrestiti <= 0) return false;
    
    numeroPrestiti--;
    disponibile = true;
    return true;
}