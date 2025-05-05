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
        Vinile(string image, string title, int year, string genre, string language, bool available, double cost, 
            int numberCopies, int numberLoans, string artist, string recordCompany, int rpm);

        //getters
        string getArtista() const;
        string getCasaDiscografica() const;
        int getRPM() const;

        //setters
        void setArtista(const string& artist);
        void setCasaDiscografica(const string& recordCompany);
        void setRPM(const int& rpm);

        //metodi
        virtual void stampaInfo() const override;
        virtual void accept(Visitor* visitor) override;
};

//overloading
std::ostream& operator<<(std::ostream& os, const Vinile& vinile);

#endif