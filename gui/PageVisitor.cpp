// File PageVisitor.cpp
#include "PageVisitor.h"
#include "../modello_logico/Biblioteca.h"
#include "../modello_logico/Libro.h"
#include "../modello_logico/Film.h"
#include "../modello_logico/Vinile.h"

#include <QFormLayout>
#include <QLabel>
#include <QPixmap>

PageVisitor::PageVisitor() : pageWidget(new QWidget()), pageLayout(new QVBoxLayout()) {
    pageWidget->setLayout(pageLayout);
}

void PageVisitor::visit(Biblioteca *biblioteca){
    // pulizia
    QLayoutItem *item;
    while ((item = pageLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
    // Layout per i dettagli
    QFormLayout *detailsLayout = new QFormLayout();

    // Creazione delle etichette
    QLabel *titleLabel = new QLabel("<b>" + QString::fromStdString(biblioteca->getTitolo()) + "</b>");
    QLabel *yearLabel = new QLabel(QString::number(biblioteca->getAnno()));
    QLabel *genreLabel = new QLabel(QString::fromStdString(biblioteca->getGenere()));
    QLabel *languageLabel = new QLabel(QString::fromStdString(biblioteca->getLingua()));
    QLabel *costLabel = new QLabel(QString::number(biblioteca->getCosto(), 'f', 2) + "€");

    QLabel *avaiableLabel = new QLabel(QString(biblioteca->getDisponibile() ? "Disponibile" : "Non disponibile"));

    // Immagine
    QLabel *imageLabel = new QLabel();
    QString path = QString::fromStdString(biblioteca->getImmagine());
    QPixmap image(path);

    if (!image.isNull()) {
        imageLabel->setPixmap(image.scaled(180, 180, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        imageLabel->setText("\n\n\n\n\n[Nessuna immagine disponibile]\n\n\n\n\n\n\n");
        imageLabel->setAlignment(Qt::AlignCenter);
        imageLabel->setStyleSheet("color: gray;");
    }
    imageLabel->setFixedSize(160, 160);
    imageLabel->setAlignment(Qt::AlignCenter);

    // Layout per centrare l'immagine
    QHBoxLayout *imageLayout = new QHBoxLayout();
    imageLayout->addStretch();
    imageLayout->addWidget(imageLabel);
    imageLayout->addStretch();

    titleLabel->setStyleSheet("font-size: 16px; color:rgb(19, 64, 110);");

    // Aggiunta delle informazioni al form layout
    detailsLayout->addRow("Titolo:", titleLabel);
    detailsLayout->addRow("Anno:", yearLabel);
    detailsLayout->addRow("Genere:", genreLabel);
    detailsLayout->addRow("Lingua:", languageLabel);
    detailsLayout->addRow("Costo:", costLabel);
    detailsLayout->addRow("Disponibilità:", avaiableLabel);

    // Inserimento nel layout principale
    pageLayout->addLayout(imageLayout);
    pageLayout->addLayout(detailsLayout);
}

// Metodo per visualizzare un Libro (chiama prima Biblioteca e poi aggiunge info specifiche)
void PageVisitor::visit(Libro *libro) {
    // Chiama il visit di Biblioteca per le info generiche
    visit(static_cast<Biblioteca*>(libro));

    // Layout per i dettagli specifici
    QFormLayout *bookDetailsLayout = new QFormLayout();

    // Creazione delle etichette specifiche per il libro
    QLabel *authorLabel = new QLabel(QString::fromStdString(libro->getAutore()));
    QLabel *pagesLabel = new QLabel(QString::number(libro->getPagine()));
    QLabel *isbnLabel = new QLabel(QString::fromStdString(libro->getISBN()));

    // Aggiunta al form layout
    bookDetailsLayout->addRow("Autore:", authorLabel);
    bookDetailsLayout->addRow("Pagine:", pagesLabel);
    bookDetailsLayout->addRow("ISBN:", isbnLabel);

    // Inserimento nel layout principale
    pageLayout->addLayout(bookDetailsLayout);
}

void PageVisitor::visit(Film *film){
    // Chiama il visit di Biblioteca per le info generiche
    visit(static_cast<Biblioteca*>(film));

    // Layout per i dettagli specifici
    QFormLayout *filmDetailsLayout = new QFormLayout();

    // Creazione delle etichette specifiche per il film
    QLabel *directorLabel = new QLabel(QString::fromStdString(film->getRegista()));
    QLabel *maincharacterLabel = new QLabel(QString::fromStdString(film->getProtagonista()));
    QLabel *durationLabel = new QLabel(QString::number(film->getDurata()) + " minuti");

    // Aggiunta al form layout
    filmDetailsLayout->addRow("Regista:", directorLabel);
    filmDetailsLayout->addRow("Protagonista:", maincharacterLabel);
    filmDetailsLayout->addRow("Durata:", durationLabel);

    // Inserimento nel layout principale
    pageLayout->addLayout(filmDetailsLayout);
}

void PageVisitor::visit(Vinile *vinile){
    // Chiama il visit di Biblioteca per le info generiche
    visit(static_cast<Biblioteca*>(vinile));

    // Layout per i dettagli specifici
    QFormLayout *vinileDetailsLayout = new QFormLayout();

    // Creazione delle etichette specifiche per il vinile
    QLabel *artistLabel = new QLabel(QString::fromStdString(vinile->getArtista()));
    QLabel *recordcompanyLabel = new QLabel(QString::fromStdString(vinile->getCasaDiscografica()));
    QLabel *rpmLabel = new QLabel(QString::number(vinile->getRPM()) + " rpm");

    // Aggiunta al form layout
    vinileDetailsLayout->addRow("Artista:", artistLabel);
    vinileDetailsLayout->addRow("Casa Discografica:", recordcompanyLabel);
    vinileDetailsLayout->addRow("Velocita' di riproduzione:", rpmLabel);

    // Inserimento nel layout principale
    pageLayout->addLayout(vinileDetailsLayout);
}

QWidget* PageVisitor::getObjectWidget() const{
    return pageWidget;
}