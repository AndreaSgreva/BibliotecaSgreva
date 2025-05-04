//File Film.cpp
#include "Film.h"
#include <iostream>
using namespace std;

//costruttore
Film::Film(string image, string title, int year, string genre, string language, bool available, double cost, 
    int numberCopies, int numberLoans, string director, string protagonist, int duration) : Biblioteca(image, title, 
    year, genre, language, available, cost, numberCopies, numberLoans), regista(director), 
    protagonista(protagonist), durata(duration) {}

//getters
string Film::getRegista() const { return regista; }
string Film::getProtagonista() const { return protagonista; }
int Film::getDurata() const { return durata; }

//setters
void Film::setRegista(const string& director) { regista = director; }
void Film::setProtagonista(const string& protagonist) { protagonista = protagonist; }
void Film::setDurata(const int& duration) { durata = duration; }

//metodi
void Film::stampaInfo() const {
    cout << *this << endl;
}
void Film::accept(Visitor* visitor) { 
    visitor->visit(this); 
}

//overloading
std::ostream& operator<<(std::ostream& os, const Film& film) {
    os << "Immagine: " << film.getImmagine() << endl;
    os << "Titolo: " << film.getTitolo() << endl;
    os << "Anno: " << film.getAnno() << endl;
    os << "Genere: " << film.getGenere() << endl;   
    os << "Lingua: " << film.getLingua() << endl; 
    os << "Disponibile: " << (film.getDisponibile() ? "Si" : "No") << endl;
    os << "Costo: " << film.getCosto() << " euro"<< endl;
    os << "Numero Copie: " << film.getNumeroCopie() << endl;
    os << "Numero Prestiti: " << film.getNumeroPrestiti() << endl;
    os << "Regista: " << film.getRegista() << endl;
    os << "Protagonista: " << film.getProtagonista() << endl;
    os << "Durata: " << film.getDurata() << " minuti"<< endl;
    return os;
}