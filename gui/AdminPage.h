//File AdminPage.h
#ifndef ADMINPAGE_H
#define ADMINPAGE_H

#include "../modello_logico/Libro.h"
#include "../modello_logico/Film.h"
#include "../modello_logico/Vinile.h"   

#include <QWidget>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QLabel>
#include <QLineEdit>
#include <QScrollArea>
#include <QRadioButton> 
#include <QGridLayout>  

//NUOVO
#include "../jsonHandler/JsonObserver.h"

class AdminPage : public QWidget, public JsonObserver {
    Q_OBJECT
private:
    QList<Biblioteca*> lista;
    QStackedWidget *stack;
    QLineEdit *searchBar;
    QLabel *labelPrestiti; 

    QGridLayout *contentLayout; 
    QWidget *contentWidget;     //Widget contenitore
    QScrollArea *scrollArea;    //Area di scorrimento

    // Radio button per categorie
    QRadioButton *allCategoryRadioButton;
    QRadioButton *libroRadioButton;
    QRadioButton *vinileRadioButton;
    QRadioButton *filmRadioButton;

    // Radio button per lingua
    QRadioButton *allLinguaRadioButton;
    QRadioButton *italianoRadioButton;
    QRadioButton *ingleseRadioButton;
    QRadioButton *spagnoloRadioButton;

    QString *linguaSelezionata;

public:
    AdminPage(QList<Biblioteca*> listaOggetti, QStackedWidget *stackedwidget, QWidget *parent = nullptr);
    ~AdminPage();
    void showAll();
    int showTotPrestiti();
    void cleanLayout();

    // Polimorfismo per mostrare gli oggetti
    void showOggetto();
    void riquadroOggetto(Biblioteca *obj, int &row, int &col, int maxColumns);

    // NUOVO -
    void onBibliotecaAggiornata(const QList<Biblioteca*>& nuovaLista) override;
    void refreshUI();

private slots:
    void close();
    void goBack();
    void search();
    void filter();
    void prenotaOggetto(Biblioteca *obj);
    void restituisciOggetto(Biblioteca *obj);

    // NUOVO
    void create();
    void modificaOggetto(Biblioteca *obj); 
    void eliminaOggetto(Biblioteca *obj);

signals:
    void itemUpdated(Biblioteca* item);
    void itemRemoved(Biblioteca* item);
    void createItem();
    void modifyItem(Biblioteca* item);
};

#endif // ADMINPAGE_H
