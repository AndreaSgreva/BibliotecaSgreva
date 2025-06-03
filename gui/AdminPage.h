//File AdminPage.h
#ifndef ADMINPAGE_H
#define ADMINPAGE_H

#include "../modello_logico/Libro.h"
#include "../modello_logico/Film.h"
#include "../modello_logico/Vinile.h"   
#include "../jsonHandler/JsonObserver.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QLabel>
#include <QLineEdit>
#include <QScrollArea>
#include <QRadioButton> 
#include <QGridLayout>  

class AdminPage : public QWidget, public JsonObserver {
    Q_OBJECT
private:
    QList<Biblioteca*> lista;
    QStackedWidget *stack;
    QLineEdit *searchBar;
    QLabel *labelPrestiti; 

    QGridLayout *contentLayout; 
    QWidget *contentWidget;     
    QScrollArea *scrollArea;    

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

    QString linguaSelezionata;

    static const QString fieldStyle;

public:
    AdminPage(QList<Biblioteca*> listaOggetti, QStackedWidget *stackedwidget, QWidget *parent = nullptr);
    ~AdminPage();
    void showAll();
    int showTotPrestiti();
    void cleanLayout();
    void showOggetto();
    void riquadroOggetto(Biblioteca *obj, int &row, int &col, int maxColumns);
    void onBibliotecaAggiornata(const QList<Biblioteca*>& nuovaLista) override;
    void refreshUI();

private slots:
    void close();
    void goBack();
    void search();
    void filter();
    void prenotaOggetto(Biblioteca *obj);
    void restituisciOggetto(Biblioteca *obj);
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
