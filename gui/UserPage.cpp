//File UserPage.cpp
#include "UserPage.h"
#include "PageVisitor.h"
#include "MainWindow.h" 
#include <QVBoxLayout>  
#include <QPushButton>  
#include <QApplication> 
#include <QMessageBox> 
#include <QButtonGroup> 

UserPage::UserPage(QList<Biblioteca*> listaOggetti, QStackedWidget *stackedwidget, QWidget *parent)
    : QWidget(parent), lista(listaOggetti), stack(stackedwidget) {

    // Layout principale della pagina
    QVBoxLayout *userLayout = new QVBoxLayout(this);

    // Layout orizzontale per la barra superiore
    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->setContentsMargins(4, 4, 4, 4);
    
    // Pulsante "Torna indietro"
    QPushButton *backButton = new QPushButton("Torna Indietro");
    backButton->setFixedSize(120, 40);
    connect(backButton, &QPushButton::clicked, this, &UserPage::goBack);

    // Pulsante per i filtri
    QPushButton *filterButton = new QPushButton("Filtri");
    filterButton->setFixedSize(100, 40);
    connect(filterButton, &QPushButton::clicked, this, &UserPage::filter);

    // Barra di ricerca
    searchBar = new QLineEdit(this);
    searchBar->setPlaceholderText("Cerca per lettere...");
    searchBar->setFixedHeight(40);
    searchBar->setMinimumWidth(750); 

    // Pulsante di ricerca
    QPushButton *searchButton = new QPushButton("Cerca");
    searchButton->setFixedSize(100, 40);
    connect(searchButton, &QPushButton::clicked, this, &UserPage::search);

    // Pulsante "Esci"
    QPushButton *exitButton = new QPushButton("Esci");
    exitButton->setFixedSize(100, 40);
    connect(exitButton, &QPushButton::clicked, this, &UserPage::close);

    // Spaziatura tra gli elementi per centrarli meglio
    topLayout->addWidget(backButton);
    topLayout->addWidget(filterButton);
    topLayout->addStretch();  // Spinge gli elementi successivi a destra
    topLayout->addWidget(searchBar);
    topLayout->addWidget(searchButton);
    topLayout->addStretch();  // Spinge l'elemento successivo a destra
    topLayout->addWidget(exitButton);

    // Aggiunta del layout superiore al layout principale
    userLayout->addLayout(topLayout);
    
    // Area di scorrimento
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    // Widget contentiore e layout per gli oggetti
    contentWidget = new QWidget(); 
    contentLayout = new QGridLayout(contentWidget);

    scrollArea->setWidget(contentWidget);
    userLayout->addWidget(scrollArea);  // Aggiunta al layout principale

    //Testo centrale che mostra prestiti totali
    labelPrestiti = new QLabel("Prestiti totali: " + QString::number(showTotPrestiti()));
    labelPrestiti->setAlignment(Qt::AlignCenter);
    labelPrestiti->setStyleSheet("font-size: 18px;");
    userLayout->addWidget(labelPrestiti);
    
    // Imposta il layout principale
    setLayout(userLayout);
    showAll();
}

UserPage::~UserPage() {}

// Metodo per chiudere la finestra
void UserPage::close() {
    QApplication::quit();
}

// Metodo per tornare alla pagina precedente
void UserPage::goBack() {
    stack->setCurrentIndex(0);
}

// Metodo per la ricerca
void UserPage::search() {
    QString searchText = searchBar->text().trimmed().toLower();
    if (searchText.isEmpty()) {
        QMessageBox::warning(this, "ATTENZIONE", "Inserisci un testo di ricerca!");
        return;
    }
    // Pulizia layout precedente
    cleanLayout();

    int row = 0, col = 0;  
    int maxColumns = 3; // Colonne massime
    bool found = false;  // Per sapere se ci sono risultati

    for (Biblioteca *obj : lista) {
        QString titolo = QString::fromStdString(obj->getTitolo()).toLower();
        if (titolo.contains(searchText)) {
            found = true;
            riquadroOggetto(obj, row, col, maxColumns);
        }
    }
    if (!found) {
        QMessageBox::information(this, "Nessun risultato", "Nessun oggetto trovato con il titolo inserito.");
    }
    contentLayout->setColumnStretch(maxColumns, 1);
}

// Metodo per i filtri
void UserPage::filter() {
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("Filtra gli oggetti");
    dialog->setMinimumSize(300, 180);
    QVBoxLayout *dialogLayout = new QVBoxLayout(dialog);

    // Titolo in grassetto per "Categoria"
    QLabel *categoryLabel = new QLabel("Seleziona una categoria", dialog);
    categoryLabel->setStyleSheet("font-weight: bold;");

    // Creazione dei radio button per categoria
    allRadioButton = new QRadioButton("Tutte le categorie", dialog);
    libroRadioButton = new QRadioButton("Libro", dialog);
    vinileRadioButton = new QRadioButton("Vinile", dialog);
    filmRadioButton = new QRadioButton("Film", dialog);

    // Titolo in grassetto per "Lingua"
    QLabel *linguaLabel = new QLabel("Seleziona una lingua", dialog);
    linguaLabel->setStyleSheet("font-weight: bold;");

    // Creazione dei radio button per lingua
    allLinguaRadioButton = new QRadioButton("Tutte le lingue", dialog);
    italianoRadioButton = new QRadioButton("Italiano", dialog);
    ingleseRadioButton = new QRadioButton("Inglese", dialog);
    spagnoloRadioButton = new QRadioButton("Spagnolo", dialog);

    // Raggruppiamo i radio button in un QButtonGroup per forzare la selezione unica
    // Gruppo categoria
    QButtonGroup *categoryGroup = new QButtonGroup(dialog);
    categoryGroup->addButton(allRadioButton);
    categoryGroup->addButton(libroRadioButton);
    categoryGroup->addButton(vinileRadioButton);
    categoryGroup->addButton(filmRadioButton);

    // Gruppo lingua
    QButtonGroup *linguaGroup = new QButtonGroup(dialog);
    linguaGroup->addButton(allLinguaRadioButton);
    linguaGroup->addButton(italianoRadioButton);
    linguaGroup->addButton(ingleseRadioButton);
    linguaGroup->addButton(spagnoloRadioButton);
    
    // Selezione predefinita: mostra tutto
    allRadioButton->setChecked(true);
    allLinguaRadioButton->setChecked(true);

    QPushButton *applyButton = new QPushButton("Applica", dialog);
    connect(applyButton, &QPushButton::clicked, dialog, &QDialog::accept);

    // Aggiunta dei radio button al layout
    dialogLayout->addWidget(categoryLabel);
    dialogLayout->addWidget(allRadioButton);
    dialogLayout->addWidget(libroRadioButton);
    dialogLayout->addWidget(vinileRadioButton);
    dialogLayout->addWidget(filmRadioButton);
    dialogLayout->addWidget(linguaLabel);
    dialogLayout->addWidget(allLinguaRadioButton);
    dialogLayout->addWidget(italianoRadioButton);
    dialogLayout->addWidget(ingleseRadioButton);
    dialogLayout->addWidget(spagnoloRadioButton);
    dialogLayout->addWidget(applyButton);

    if (dialog->exec() == QDialog::Accepted) {
        cleanLayout();

        // Mostriamo gli elementi in base alla selezione
        if (allRadioButton->isChecked()) showAll();
        else showOggetto();
    }
}

// Metodo per pulire il layout
void UserPage::cleanLayout() {
    // Pulizia layout precedente 
    QLayoutItem *item;
    while ((item = contentLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
}

// Metodo per mostrare tutti gli oggetti
void UserPage::showAll() {
    cleanLayout();  // Pulisce il layout precedente
    int row = 0, col = 0;  // Per tenere traccia della posizione nella griglia
    int maxColumns = 3;    // Numero massimo di colonne per riga
    // Mostra tutti gli oggetti (libri, vinili, film)
    for (Biblioteca *obj : lista) {
        riquadroOggetto(obj, row, col, maxColumns);
    }
}

// Metodo per prenotare un oggetto
void UserPage::prenotaOggetto(Biblioteca *obj) {
    if (!obj) {
        qWarning() << "Tentativo di prenotare oggetto nullo";
        return;
    }

    int copieRimaste = obj->getNumeroCopie() - obj->getNumeroPrestiti();
    if (copieRimaste > 0) {
        obj->prenota();
        copieRimaste--;

        // Aggiornamento UI
        QMessageBox::information(this, "Prenotazione", 
                               "Prenotato! Copie rimaste: " + QString::number(copieRimaste));
        labelPrestiti->setText("Prestiti totali: " + QString::number(showTotPrestiti()));

        // Notifica l'aggiornamento
        emit itemUpdated(obj);

        // Se esaurito, aggiorna tutta la UI
        if (copieRimaste == 0) {
            QMessageBox::information(this, "Aggiornamento", 
                                   "Oggetto esaurito, aggiornamento interfaccia...");
            showAll();
        }
    } else {
        QMessageBox::warning(this, "Errore", 
                           "Non ci sono copie disponibili per la prenotazione.");
    }
}

// Metodo per restituire un oggetto
void UserPage::restituisciOggetto(Biblioteca *obj) {
    if (!obj) {
        qWarning() << "Tentativo di restituire oggetto nullo";
        return;
    }

    if (obj->getNumeroPrestiti() > 0) {
        obj->restituisci();

        // Aggiornamento UI
        QMessageBox::information(this, "Restituzione", "Restituito! Prestiti rimanenti: " + 
            QString::number(obj->getNumeroPrestiti()));
        labelPrestiti->setText("Prestiti totali: " + QString::number(showTotPrestiti()));

        // Notifica l'aggiornamento
        emit itemUpdated(obj);

        // Se torna disponibile, aggiorna UI
        if ((obj->getNumeroCopie() - obj->getNumeroPrestiti()) == 1) {
            QMessageBox::information(this, "Aggiornamento", 
                                   "Oggetto nuovamente disponibile, aggiornamento interfaccia...");
            showAll();
        }
    } else {
        QMessageBox::warning(this, "Errore", 
                           "Non ci sono prestiti da restituire per questo oggetto.");
    }
}

// Metodo per mostrare il numero totale di prestiti
int UserPage::showTotPrestiti() {
    int tot = 0;
    for (Biblioteca *obj : lista) {
        tot = tot + obj->getNumeroPrestiti();
    }
    return tot;
}

// Metodo per mostrare gli oggetti in base al tipo
void UserPage::showOggetto() {
    cleanLayout();  // Pulisce il layout precedente
    int row = 0, col = 0;  // Per tenere traccia della posizione nella griglia
    int maxColumns = 3;    // Numero massimo di colonne per riga

    QString linguaSelezionata; // Memorizza la lingua selezionata

    // Verifica la lingua selezionata tramite i radio button
    if (italianoRadioButton->isChecked()) linguaSelezionata = "italiano";
    else if (ingleseRadioButton->isChecked()) linguaSelezionata = "inglese";
    else if (spagnoloRadioButton->isChecked()) linguaSelezionata = "spagnolo";

    // Determina la categoria selezionata
    if (allRadioButton->isChecked()) showAll();
    else if (libroRadioButton->isChecked()) {
        // Mostra solo i libri
        for (Biblioteca *obj : lista) {
            Libro *libro = dynamic_cast<Libro*>(obj);
            if (libro && (allLinguaRadioButton->isChecked() || libro->getLingua() == linguaSelezionata.toStdString())) {
                riquadroOggetto(obj, row, col, maxColumns);
            }
        }
    }
    else if (filmRadioButton->isChecked()) {
        // Mostra solo i film
        for (Biblioteca *obj : lista) {
            Film *film = dynamic_cast<Film*>(obj);
            if (film && (allLinguaRadioButton->isChecked() || film->getLingua() == linguaSelezionata.toStdString())) {
                riquadroOggetto(obj, row, col, maxColumns);
            }
        }
    }
    else if (vinileRadioButton->isChecked()) {
        // Mostra solo i vinili
        for (Biblioteca *obj : lista) {
            Vinile *vinile = dynamic_cast<Vinile*>(obj);
            if (vinile && (allLinguaRadioButton->isChecked() || vinile->getLingua() == linguaSelezionata.toStdString())) {
                riquadroOggetto(obj, row, col, maxColumns);
            }
        }
    }
    contentLayout->setColumnStretch(maxColumns, 1);  // Mantiene la griglia bilanciata
}

// Metodo per creare i riquadri per ogni oggetto
void UserPage::riquadroOggetto(Biblioteca *obj, int &row, int &col, int maxColumns) {
    PageVisitor visitor;
    obj->accept(&visitor);  // Chiama il visit() appropriato

    QWidget *objWidget = visitor.getObjectWidget();
    
    // Contenitore con bordo per separare gli oggetti
    QFrame *frame = new QFrame();
    frame->setFrameShape(QFrame::Box);
    frame->setFrameShadow(QFrame::Raised);

    // Imposta una dimensione fissa per i riquadri
    frame->setMinimumSize(335, 415);  // Larghezza e altezza minime
    frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QVBoxLayout *frameLayout = new QVBoxLayout(frame);
    frameLayout->addWidget(objWidget);

    // Creazione di un layout orizzontale per i pulsanti
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *prenotaButton = new QPushButton("Prenota");
    QPushButton *restituisciButton = new QPushButton("Restituisci");

    // Connetti i pulsanti all'oggetto corrente
    connect(prenotaButton, &QPushButton::clicked, this, [this, obj]() { prenotaOggetto(obj); });
    connect(restituisciButton, &QPushButton::clicked, this, [this, obj]() { restituisciOggetto(obj); });

    // Aggiunta dei pulsanti al layout orizzontale
    buttonLayout->addWidget(prenotaButton);
    buttonLayout->addWidget(restituisciButton);

    // Aggiunta del layout orizzontale al frameLayout
    frameLayout->addLayout(buttonLayout);

    // Aggiungiamo il frame alla griglia
    contentLayout->addWidget(frame, row, col);

    // Aggiorniamo la posizione (va a capo quando col == maxColumns-1)
    col++;
    if (col >= maxColumns) {
        col = 0;
        row++;
    }
}

void UserPage::onBibliotecaAggiornata(const QList<Biblioteca*>& nuovaLista) {
    lista = nuovaLista;
    refreshUI();
}

void UserPage::refreshUI(){
    cleanLayout();
    showAll();
    labelPrestiti->setText("Prestiti totali: " + QString::number(showTotPrestiti()));
}
