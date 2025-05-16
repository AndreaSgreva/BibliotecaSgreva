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
void Film::accept(Visitor* visitor) { 
    visitor->visit(this); 
}