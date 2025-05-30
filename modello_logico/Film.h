//File Film.h
#ifndef FILM_H
#define FILM_H
#include "Biblioteca.h"
#include <string>
using std::string;

class Film : public Biblioteca {
    private:
        string regista;
        string protagonista;
        int durata;
    public:
        //costruttore
        Film(const string& image, const string& title, int year, const string& genre, const string& language, bool available, double cost, 
            int numberCopies, int numberLoans, const string& director, const string& protagonist, int duration);
        
        //getters
        string getRegista() const;
        string getProtagonista() const;
        int getDurata() const;
        
        //setters
        void setRegista(const string& director);
        void setProtagonista(const string& protagonist);
        void setDurata(const int& duration);
        
        //metodi
        virtual void accept(Visitor* visitor) override;
};
#endif