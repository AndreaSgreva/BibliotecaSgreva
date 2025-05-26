//Film Vinile.h
#ifndef FILM_VINILE_H
#define FILM_VINILE_H
#include "Biblioteca.h"
#include <string>
using std::string;

class Vinile : public Biblioteca {
    private:
        string artista;
        string casaDiscografica;
        int rpm;
    public:
        //costruttore
        Vinile(const string& image, const string& title, int year, const string& genre, const string& language, bool available, double cost, 
            int numberCopies, int numberLoans, const string& artist, const string& recordCompany, int rpm);

        //getters
        string getArtista() const;
        string getCasaDiscografica() const;
        int getRPM() const;

        //setters
        void setArtista(const string& artist);
        void setCasaDiscografica(const string& recordCompany);
        void setRPM(const int& rpm);

        //metodi
        virtual void accept(Visitor* visitor) override;
};

#endif