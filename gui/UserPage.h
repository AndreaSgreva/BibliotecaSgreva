//File UserPage.h
#ifndef USERPAGE_H
#define USERPAGE_H

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

class UserPage : public QWidget, public JsonObserver {
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

    QString linguaSelezionata;
    
    static const QString fieldStyle;

public:
    UserPage(QList<Biblioteca*> listaOggetti, QStackedWidget *stackedwidget, QWidget *parent = nullptr);
    ~UserPage();
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

signals:
    void itemUpdated(Biblioteca* item);
};

#endif // USERPAGE_H
