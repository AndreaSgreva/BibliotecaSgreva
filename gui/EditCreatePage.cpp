//File EditCreatePage.cpp
#include "EditCreatePage.h"
#include <QMessageBox>
#include <QDate>
#include <QFileDialog>

EditCreatePage::EditCreatePage(QStackedWidget* stackedWidget, QWidget* parent) 
    : QWidget(parent), stack(stackedWidget), currentItem(nullptr) {
    
    mainLayout = new QVBoxLayout(this);
    formLayout = new QFormLayout();

    setupCommonFields(); //appena aggiunto
    // PROVA
    mainLayout->addLayout(formLayout);
    
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* saveButton = new QPushButton("Salva");
    QPushButton* backButton = new QPushButton("Indietro");
    
    connect(saveButton, &QPushButton::clicked, this, &EditCreatePage::saveItem);
    connect(backButton, &QPushButton::clicked, this, &EditCreatePage::goBack);
    
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(backButton);
    
    //mainLayout->addLayout(formLayout);  PROVA
    mainLayout->addLayout(buttonLayout);
}

void EditCreatePage::setupForCreation() {
    currentMode = Create;
    currentItem = nullptr;
    cleanLayout();
    
    QDialog typeDialog(this);
    QVBoxLayout dialogLayout(&typeDialog);
    
    QLabel label("Seleziona il tipo di oggetto:");
    QPushButton bookButton("Libro");
    QPushButton filmButton("Film");
    QPushButton vinileButton("Vinile");
    
    dialogLayout.addWidget(&label);
    dialogLayout.addWidget(&bookButton);
    dialogLayout.addWidget(&filmButton);
    dialogLayout.addWidget(&vinileButton);
    
    connect(&bookButton, &QPushButton::clicked, [&]() {
        currentType = "Libro";
        typeDialog.accept();
        setupCommonFields();
        setupBookFields();
    });
    
    connect(&filmButton, &QPushButton::clicked, [&]() {
        currentType = "Film";
        typeDialog.accept();
        setupCommonFields();
        setupFilmFields();
    });
    
    connect(&vinileButton, &QPushButton::clicked, [&]() {
        currentType = "Vinile";
        typeDialog.accept();
        setupCommonFields();
        setupVinileFields();
    });
    
    typeDialog.exec();
}

void EditCreatePage::setupForEditing(Biblioteca* item) {
    currentMode = Edit;
    currentItem = item;
    cleanLayout();
    
    setupCommonFields();
    item->accept(this);
}

void EditCreatePage::visit(Libro* libro) {
    setupBookFields(libro);
}

void EditCreatePage::visit(Film* film) {
    setupFilmFields(film);
}

void EditCreatePage::visit(Vinile* vinile) {
    setupVinileFields(vinile);
}

void EditCreatePage::setupCommonFields() {
    cleanLayout();

    // Campo per il percorso immagine
    QHBoxLayout* imageLayout = new QHBoxLayout();
    imagePathEdit = new QLineEdit(currentItem ? QString::fromStdString(currentItem->getImmagine()) : "");
    browseImageButton = new QPushButton("Sfoglia...");
    
    connect(browseImageButton, &QPushButton::clicked, this, [this]() {
        QString filePath = QFileDialog::getOpenFileName(this, "Seleziona immagine", "", "Immagini (*.png *.jpg *.jpeg)");
        if (!filePath.isEmpty()) {
            imagePathEdit->setText(filePath);
        }
    });

    imageLayout->addWidget(imagePathEdit);
    imageLayout->addWidget(browseImageButton);
    formLayout->addRow("Immagine:", imageLayout);

    titleEdit = new QLineEdit(currentItem ? QString::fromStdString(currentItem->getTitolo()) : "");
    yearEdit = new QSpinBox();
    yearEdit->setRange(1900, QDate::currentDate().year());
    yearEdit->setValue(currentItem ? currentItem->getAnno() : 2000);
    
    genreEdit = new QLineEdit(currentItem ? QString::fromStdString(currentItem->getGenere()) : "");
    
    languageCombo = new QComboBox();
    languageCombo->addItems({"Italiano", "Inglese", "Spagnolo"});
    if(currentItem) {
        int index = languageCombo->findText(QString::fromStdString(currentItem->getLingua()));
        if(index >= 0) languageCombo->setCurrentIndex(index);
    }
    
    costEdit = new QDoubleSpinBox();
    costEdit->setRange(0.01, 1000.0);
    costEdit->setValue(currentItem ? currentItem->getCosto() : 0.0);
    
    copiesEdit = new QSpinBox();
    copiesEdit->setRange(1, 100);
    copiesEdit->setValue(currentItem ? currentItem->getNumeroCopie() : 1);

    loansEdit = new QSpinBox();
    loansEdit->setRange(0, 100);
    //loansEdit->setRange(0, copiesEdit->value());
    loansEdit->setValue(currentItem ? currentItem->getNumeroPrestiti() : 0);
    
    // PROVA PREVIEW IMMAGINE
    imagePreview = new QLabel();
    imagePreview->setFixedSize(200, 200);
    imagePreview->setAlignment(Qt::AlignCenter);
    imagePreview->setStyleSheet("border: 1px solid #ccc;");

    // Aggiorna la preview quando si seleziona un'immagine
    connect(imagePathEdit, &QLineEdit::textChanged, this, [this](const QString& path) {
        QPixmap pixmap(path);
        if (!pixmap.isNull()) {
            imagePreview->setPixmap(pixmap.scaled(imagePreview->size(), Qt::KeepAspectRatio));
        } else {
            imagePreview->setText("Nessuna immagine selezionata");
        }   
    });

    formLayout->addRow("Anteprima:", imagePreview);


    formLayout->addRow("Titolo:", titleEdit);
    formLayout->addRow("Anno:", yearEdit);
    formLayout->addRow("Genere:", genreEdit);
    formLayout->addRow("Lingua:", languageCombo);
    formLayout->addRow("Costo (€):", costEdit);
    formLayout->addRow("Numero Copie:", copiesEdit);
    formLayout->addRow("Numero Prestiti:", loansEdit);
}

void EditCreatePage::setupBookFields(Libro* libro) {
    authorEdit = new QLineEdit(libro ? QString::fromStdString(libro->getAutore()) : "");
    pagesEdit = new QSpinBox();
    pagesEdit->setRange(1, 5000);
    pagesEdit->setValue(libro ? libro->getPagine() : 200);
    
    isbnEdit = new QLineEdit(libro ? QString::fromStdString(libro->getISBN()) : "");
    
    formLayout->addRow("Autore:", authorEdit);
    formLayout->addRow("Pagine:", pagesEdit);
    formLayout->addRow("ISBN:", isbnEdit);
}

void EditCreatePage::setupFilmFields(Film* film) {
    directorEdit = new QLineEdit(film ? QString::fromStdString(film->getRegista()) : "");
    protagonistEdit = new QLineEdit(film ? QString::fromStdString(film->getProtagonista()) : "");
    
    durationEdit = new QSpinBox();
    durationEdit->setRange(1, 300);
    durationEdit->setValue(film ? film->getDurata() : 120);
    
    formLayout->addRow("Regista:", directorEdit);
    formLayout->addRow("Protagonista:", protagonistEdit);
    formLayout->addRow("Durata (min):", durationEdit);
}

void EditCreatePage::setupVinileFields(Vinile* vinile) {
    artistEdit = new QLineEdit(vinile ? QString::fromStdString(vinile->getArtista()) : "");
    recordCompanyEdit = new QLineEdit(vinile ? QString::fromStdString(vinile->getCasaDiscografica()) : "");
    
    rpmEdit = new QSpinBox();
    rpmEdit->setRange(33, 78);
    rpmEdit->setValue(vinile ? vinile->getRPM() : 33);
    
    formLayout->addRow("Artista:", artistEdit);
    formLayout->addRow("Casa discografica:", recordCompanyEdit);
    formLayout->addRow("RPM:", rpmEdit);
}

/*void EditCreatePage::saveItem() {
    if (titleEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Errore", "Il titolo è obbligatorio!");
        return;
    }
    Biblioteca* item = currentMode == Edit ? currentItem : createNewItem();
    
    item->setTitolo(titleEdit->text().toStdString());
    item->setAnno(yearEdit->value());
    item->setGenere(genreEdit->text().toStdString());
    item->setLingua(languageCombo->currentText().toStdString());
    item->setCosto(costEdit->value());
    item->setNumeroCopie(copiesEdit->value());    

    if(currentMode == Create) {
        emit itemCreated(item);
    } else {
        emit itemUpdated(item);
    }
    
    clearFields();  //pulisci i campi dopo il salvataggio
    goBack();
}*/
void EditCreatePage::saveItem() {
    // Validazione dei campi
    if (titleEdit->text().isEmpty() || genreEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Errore", "Compila tutti i campi necessari!");
        return;
    }
    if (loansEdit->value() > copiesEdit->value()) {
        QMessageBox::warning(this, "Errore", "Non si possono avere più prestiti che copie!");
        return;
    }

    if (currentType == "Libro") {
        if (authorEdit->text().isEmpty() || pagesEdit->value() == 0 || isbnEdit->text().isEmpty()) {
            QMessageBox::warning(this, "Errore", "Compila tutti i campi necessari!");
            return;
        }
    } else if (currentType == "Film") {
        if (directorEdit->text().isEmpty() || protagonistEdit->text().isEmpty() || durationEdit->value() == 0) {
            QMessageBox::warning(this, "Errore", "Compila tutti i campi necessari!");
            return;
        }
    } else {
        if (artistEdit->text().isEmpty() || recordCompanyEdit->text().isEmpty() || rpmEdit->value() == 0) {
            QMessageBox::warning(this, "Errore", "Compila tutti i campi necessari!");
            return;
        }
    }

    // Creazione o modifica dell'oggetto
    if (currentMode == Create) {  // Modalità creazione
        Biblioteca* newItem = createNewItem();
        if (newItem) {
            emit itemCreated(newItem);
        }
    } 
    else { // Modalità modifica
        if (!currentItem) {
            qWarning() << "Nessun oggetto corrente da modificare";
            return;
        }

        // Aggiorna l'oggetto esistente invece di crearne uno nuovo
        currentItem->setTitolo(titleEdit->text().toStdString());
        currentItem->setAnno(yearEdit->value());
        currentItem->setGenere(genreEdit->text().toStdString());
        currentItem->setLingua(languageCombo->currentText().toStdString());
        currentItem->setCosto(costEdit->value());
        currentItem->setNumeroCopie(copiesEdit->value());
        currentItem->setNumeroPrestiti(loansEdit->value());
        currentItem->setImmagine(imagePathEdit->text().toStdString());

        // Aggiorna campi specifici in base al tipo
        if (auto libro = dynamic_cast<Libro*>(currentItem)) {
            if (authorEdit->text().isEmpty() || isbnEdit->text().isEmpty()) {
                QMessageBox::warning(this, "Errore", "Compila tutti i campi necessari!");
                return;
            }
            libro->setAutore(authorEdit->text().toStdString());
            libro->setPagine(pagesEdit->value());
            libro->setISBN(isbnEdit->text().toStdString());
        }
        else if (auto film = dynamic_cast<Film*>(currentItem)) {
            if (directorEdit->text().isEmpty() || protagonistEdit->text().isEmpty()) {
                QMessageBox::warning(this, "Errore", "Compila tutti i campi necessari!");
                return;
            }
            film->setRegista(directorEdit->text().toStdString());
            film->setProtagonista(protagonistEdit->text().toStdString());
            film->setDurata(durationEdit->value());
        }
        else if (auto vinile = dynamic_cast<Vinile*>(currentItem)) {
            if (artistEdit->text().isEmpty() || recordCompanyEdit->text().isEmpty()) {
                QMessageBox::warning(this, "Errore", "Compila tutti i campi necessari!");
                return;
            }
            vinile->setArtista(artistEdit->text().toStdString());
            vinile->setCasaDiscografica(recordCompanyEdit->text().toStdString());
            vinile->setRPM(rpmEdit->value());
        }

        emit itemUpdated(currentItem);
    }
    clearFields();  //pulisci i campi dopo il salvataggio  FORSE
    goBack();
}

// NUOVO PROVA
void EditCreatePage::clearFields(){
    imagePathEdit->clear();
    titleEdit->clear();
    yearEdit->setValue(2000);
    genreEdit->clear();
    languageCombo->setCurrentIndex(0);
    costEdit->setValue(0.01);
    copiesEdit->setValue(1);
    loansEdit->setValue(0);
}

Biblioteca* EditCreatePage::createNewItem() {
    if(currentType == "Libro") {
        return new Libro(imagePathEdit->text().toStdString(), titleEdit->text().toStdString(), yearEdit->value(), 
                        genreEdit->text().toStdString(), languageCombo->currentText().toStdString(),
                        copiesEdit->value() == loansEdit->value() ? false : true, 
                        costEdit->value(), copiesEdit->value(), loansEdit->value(),
                        authorEdit->text().toStdString(), pagesEdit->value(), isbnEdit->text().toStdString());
    } else if(currentType == "Film") {
        return new Film(imagePathEdit->text().toStdString(), titleEdit->text().toStdString(), yearEdit->value(),
                       genreEdit->text().toStdString(), languageCombo->currentText().toStdString(),
                       copiesEdit->value() == loansEdit->value() ? false : true, 
                       costEdit->value(), copiesEdit->value(), loansEdit->value(),
                       directorEdit->text().toStdString(), protagonistEdit->text().toStdString(), durationEdit->value());
    } else {
        return new Vinile(imagePathEdit->text().toStdString(), titleEdit->text().toStdString(), yearEdit->value(),
                         genreEdit->text().toStdString(), languageCombo->currentText().toStdString(),
                         copiesEdit->value() == loansEdit->value() ? false : true, 
                         costEdit->value(), copiesEdit->value(), loansEdit->value(),
                         artistEdit->text().toStdString(), recordCompanyEdit->text().toStdString(), rpmEdit->value());
    }
}

void EditCreatePage::goBack() {
    stack->setCurrentIndex(2);
}

void EditCreatePage::cleanLayout() {
    // Modifica questo metodo così:
    while (formLayout->count() > 0) {
        QLayoutItem* item = formLayout->takeAt(0);
        if (item->widget()) {
            item->widget()->deleteLater();
        }
        delete item;
    }
}
/*void EditCreatePage::cleanLayout() {
    QLayoutItem* item;
    while((item = formLayout->takeAt(0))) {  // takeAt restituisce nullptr se non ci sono elementi
        if(item->widget()) {
            formLayout->removeWidget(item->widget()); // Rimuove prima il widget
            item->widget()->deleteLater();
        }
        delete item;
    }
}*/