//File Biblioteca.h
#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H
#include "../gui/Visitor.h"
#include <string>
using std::string;

class Biblioteca{
    private:
        string immagine;
        string titolo; 
        int anno;
        string genere;
        string lingua;
        bool disponibile;
        double costo;
        int numeroCopie;
        int numeroPrestiti;
    public:
        //costruttore e distruttore
        Biblioteca(const string& image, const string& title, int year, const string& genre, const string& language, bool available, double cost, 
            int numberCopies, int numberLoans);
        virtual ~Biblioteca() = default;

        //getters
        string getImmagine() const;
        string getTitolo() const;
        int getAnno() const;
        string getGenere() const;
        string getLingua() const;
        bool getDisponibile() const;
        double getCosto() const;
        int getNumeroCopie() const;
        int getNumeroPrestiti() const;

        //setters
        void setImmagine(const string& image);
        void setTitolo(const string& title);
        void setAnno(const int& year);
        void setGenere(const string& genre);
        void setLingua(const string& language);
        void setDisponibile(const bool& available);
        void setCosto(const double& cost);
        void setNumeroCopie(const int& numberCopies);
        void setNumeroPrestiti(const int& numberLoans);
        
        //metodi
        virtual void accept(Visitor* visitor) = 0;
        bool prenota();
        bool restituisci();

};

#endif