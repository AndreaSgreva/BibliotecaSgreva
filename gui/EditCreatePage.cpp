//File EditCreatePage.cpp
#include "EditCreatePage.h"
#include <QMessageBox>
#include <QDate>
#include <QFileDialog>

EditCreatePage::EditCreatePage(QStackedWidget* stackedWidget, QWidget* parent) 
    : QWidget(parent), stack(stackedWidget), currentItem(nullptr) {
    
    mainLayout = new QVBoxLayout(this);
    formLayout = new QFormLayout();

    // Menu a tendina per selezionare il tipo
    typeSelector = new QComboBox();
    typeSelector->addItem("Seleziona tipo...");
    typeSelector->addItem("Libro");
    typeSelector->addItem("Film");
    typeSelector->addItem("Vinile");

    typeSelector->setMinimumWidth(200);
    typeSelector->setFixedHeight(40);

    typeSelector->setStyleSheet("font-size: 16px; font-weight: bold; color:rgb(19, 64, 110);");


    mainLayout->addWidget(typeSelector);

    mainLayout->addLayout(formLayout);
    
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    saveButton = new QPushButton("Salva");
    backButton = new QPushButton("Indietro");
    
    connect(saveButton, &QPushButton::clicked, this, &EditCreatePage::saveItem);
    connect(backButton, &QPushButton::clicked, this, &EditCreatePage::goBack);
    
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(backButton);
    mainLayout->addLayout(buttonLayout);

    // Reagisci alla selezione
    connect(typeSelector, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=](int index) {
        if (index == 0) {
            saveButton->setEnabled(false);
            cleanLayout();
            return;
        }

        saveButton->setEnabled(true);
        cleanLayout();
        currentType = typeSelector->currentText();
        setupCommonFields();

        if (currentType == "Libro") setupBookFields();
        else if (currentType == "Film") setupFilmFields();
        else if (currentType == "Vinile") setupVinileFields();
    });
}

void EditCreatePage::setupForCreation() {
    currentMode = Create;
    currentItem = nullptr;
    typeSelector->setCurrentIndex(0);
    saveButton->setEnabled(false);
    cleanLayout();
}

/*void EditCreatePage::setupForCreation() {
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
}*/

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
    // Campo per il percorso immagine
    //QHBoxLayout* imageLayout = new QHBoxLayout();
    imagePathEdit = new QLineEdit(currentItem ? QString::fromStdString(currentItem->getImmagine()) : "");
    browseImageButton = new QPushButton("Sfoglia immagine da locale...");
    
    connect(browseImageButton, &QPushButton::clicked, this, [this]() {
        QString filePath = QFileDialog::getOpenFileName(this, "Seleziona immagine", "", "Immagini (*.png *.jpg *.jpeg)");
        if (!filePath.isEmpty()) {
            imagePathEdit->setText(filePath);
        }
    });

    //imageLayout->addWidget(imagePathEdit);
    //imageLayout->addWidget(browseImageButton);

    // PREVIEW IMMAGINE
    imagePreview = new QLabel();
    imagePreview->setFixedSize(200, 200);
    imagePreview->setAlignment(Qt::AlignCenter);
    imagePreview->setStyleSheet("border: 1px solid #ccc;");

    if (currentItem && !QString::fromStdString(currentItem->getImmagine()).isEmpty()) {
        QPixmap pixmap(QString::fromStdString(currentItem->getImmagine()));
        if (!pixmap.isNull()) {
            imagePreview->setPixmap(pixmap.scaled(imagePreview->size(), Qt::KeepAspectRatio));
        } else {
            imagePreview->setText("Immagine non valida");
        }
    } else {
        imagePreview->setText("Nessuna immagine selezionata");
    }

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
    
    costLabel = new QLabel("");   //PROVAA

    copiesEdit = new QSpinBox();
    copiesEdit->setRange(1, 100);
    copiesEdit->setValue(currentItem ? currentItem->getNumeroCopie() : 1);

    loansEdit = new QSpinBox();
    loansEdit->setRange(0, 100);
    loansEdit->setValue(currentItem ? currentItem->getNumeroPrestiti() : 0);
    
    // Aggiorna la preview quando si seleziona un'immagine
    connect(imagePathEdit, &QLineEdit::textChanged, this, [this](const QString& path) {
        QPixmap pixmap(path);
        if (!pixmap.isNull()) {
            imagePreview->setPixmap(pixmap.scaled(imagePreview->size(), Qt::KeepAspectRatio));
        } else {
            imagePreview->setText("Nessuna immagine selezionata");
        }   
    });

    formLayout->addRow("Immagine:", imagePathEdit);
    formLayout->addWidget(browseImageButton);

    formLayout->addRow("Anteprima:", imagePreview);
    formLayout->addRow("Titolo:", titleEdit);
    formLayout->addRow("Anno:", yearEdit);
    formLayout->addRow("Genere:", genreEdit);
    formLayout->addRow("Lingua:", languageCombo);
    //formLayout->addRow("Costo (€):", costEdit);
    formLayout->addRow("Costo (€):", costLabel);
    formLayout->addRow("Numero Copie:", copiesEdit);
    formLayout->addRow("Numero Prestiti:", loansEdit);
}

void EditCreatePage::setupBookFields(Libro* libro) {
    authorEdit = new QLineEdit(libro ? QString::fromStdString(libro->getAutore()) : "");
    pagesEdit = new QSpinBox();
    pagesEdit->setRange(1, 5000);
    pagesEdit->setValue(libro ? libro->getPagine() : 200);
    
    isbnEdit = new QLineEdit(libro ? QString::fromStdString(libro->getISBN()) : "");

    costLabel->setText("1.50");
    
    formLayout->addRow("Autore:", authorEdit);
    formLayout->addRow("Pagine:", pagesEdit);
    formLayout->addRow("ISBN:", isbnEdit);
}

void EditCreatePage::setupFilmFields(Film* film) {
    directorEdit = new QLineEdit(film ? QString::fromStdString(film->getRegista()) : "");
    protagonistEdit = new QLineEdit(film ? QString::fromStdString(film->getProtagonista()) : "");
    
    costLabel->setText("3.50");   

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
    
    costLabel->setText("5.00");

    rpmCombo = new QComboBox();
    rpmCombo->addItems({"33", "45"});
    if (vinile) {
        int index = rpmCombo->findText(QString::number(vinile->getRPM()));
        if (index >= 0) rpmCombo->setCurrentIndex(index);
    }
    
    formLayout->addRow("Artista:", artistEdit);
    formLayout->addRow("Casa discografica:", recordCompanyEdit);
    formLayout->addRow("RPM:", rpmCombo);
}

void EditCreatePage::aggiornaDisponibilità(Biblioteca* item) {
    if (item->getNumeroPrestiti() == item->getNumeroCopie()) {
        item->setDisponibile(false);
    } else if (item->getNumeroPrestiti() < item->getNumeroCopie()) {
        item->setDisponibile(true);
    }
}

bool EditCreatePage::aggiornaFields(Biblioteca* item){
    // Validazione dei campi
    if (titleEdit->text().isEmpty() || genreEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Errore", "Compila tutti i campi necessari!");
        return false;
    }
    if (loansEdit->value() > copiesEdit->value()) {
        QMessageBox::warning(this, "Errore", "Non si possono avere più prestiti che copie!");
        return false;
    }
    item->setTitolo(titleEdit->text().toStdString());
    item->setAnno(yearEdit->value());
    item->setGenere(genreEdit->text().toStdString());
    item->setLingua(languageCombo->currentText().toStdString());
    //item->setCosto(costEdit->value());
    item->setNumeroCopie(copiesEdit->value());
    item->setNumeroPrestiti(loansEdit->value());
    item->setImmagine(imagePathEdit->text().toStdString());
    return aggiornaSpecificFields(item);
}

bool EditCreatePage::aggiornaSpecificFields(Biblioteca* item) {
    if (auto libro = dynamic_cast<Libro*>(item)) {
        if (authorEdit->text().isEmpty() || isbnEdit->text().isEmpty()) {
            QMessageBox::warning(this, "Errore", "Compila tutti i campi necessari!");
            return false;
        }
        libro->setAutore(authorEdit->text().toStdString());
        libro->setPagine(pagesEdit->value());
        libro->setISBN(isbnEdit->text().toStdString());

        //libro->setCosto(10)
    }
    else if (auto film = dynamic_cast<Film*>(item)) {
        if (directorEdit->text().isEmpty() || protagonistEdit->text().isEmpty()) {
            QMessageBox::warning(this, "Errore", "Compila tutti i campi necessari!");
            return false;
        }
        film->setRegista(directorEdit->text().toStdString());
        film->setProtagonista(protagonistEdit->text().toStdString());
        film->setDurata(durationEdit->value());
    }
    else if (auto vinile = dynamic_cast<Vinile*>(item)) {
        if (artistEdit->text().isEmpty() || recordCompanyEdit->text().isEmpty()) {
            QMessageBox::warning(this, "Errore", "Compila tutti i campi necessari!");
            return false;
        }
        vinile->setArtista(artistEdit->text().toStdString());
        vinile->setCasaDiscografica(recordCompanyEdit->text().toStdString());
        vinile->setRPM(rpmCombo->currentText().toInt());
    }
    return true;
}

void EditCreatePage::saveItem() {
    // Creazione o modifica dell'oggetto
    if (currentMode == Create) {  // Modalità creazione
        Biblioteca* newItem = createNewItem();
        if (!aggiornaFields(newItem)) return;
        aggiornaDisponibilità(newItem);
        emit itemCreated(newItem);
    } 
    else { // Modalità modifica
        if (!currentItem) {
            qWarning() << "Nessun oggetto corrente da modificare";
            return;
        }

        if (!aggiornaFields(currentItem)) return;
        aggiornaDisponibilità(currentItem);

        emit itemUpdated(currentItem);
    }
    goBack();
}

Biblioteca* EditCreatePage::createNewItem() {
    if(currentType == "Libro") {
        return new Libro(imagePathEdit->text().toStdString(), titleEdit->text().toStdString(), yearEdit->value(), 
                        genreEdit->text().toStdString(), languageCombo->currentText().toStdString(),
                        copiesEdit->value() > loansEdit->value(), 
                        10, copiesEdit->value(), loansEdit->value(),
                        authorEdit->text().toStdString(), pagesEdit->value(), isbnEdit->text().toStdString());
    } else if(currentType == "Film") {
        return new Film(imagePathEdit->text().toStdString(), titleEdit->text().toStdString(), yearEdit->value(),
                        genreEdit->text().toStdString(), languageCombo->currentText().toStdString(),
                        copiesEdit->value() > loansEdit->value(), 
                        20, copiesEdit->value(), loansEdit->value(),
                        directorEdit->text().toStdString(), protagonistEdit->text().toStdString(), durationEdit->value());
    } else {
        return new Vinile(imagePathEdit->text().toStdString(), titleEdit->text().toStdString(), yearEdit->value(),
                        genreEdit->text().toStdString(), languageCombo->currentText().toStdString(),
                        copiesEdit->value() > loansEdit->value(), 
                        30, copiesEdit->value(), loansEdit->value(),
                        artistEdit->text().toStdString(), recordCompanyEdit->text().toStdString(), rpmCombo->currentText().toInt());
    }
}

void EditCreatePage::goBack() {
    cleanLayout();
    stack->setCurrentIndex(2);
}

void EditCreatePage::cleanLayout() {
    while (formLayout->count() > 0) {
        QLayoutItem* item = formLayout->takeAt(0);
        if (item->widget()) {
            item->widget()->deleteLater();
        }
        delete item;
    }

    
    // Azzera i puntatori per evitare accessi a memoria invalidata
    imagePathEdit = nullptr;
    browseImageButton = nullptr;
    imagePreview = nullptr;
    titleEdit = nullptr;
    yearEdit = nullptr;
    genreEdit = nullptr;
    languageCombo = nullptr;
    costEdit = nullptr;
    copiesEdit = nullptr;
    loansEdit = nullptr;

    authorEdit = nullptr;
    pagesEdit = nullptr;
    isbnEdit = nullptr;

    directorEdit = nullptr;
    protagonistEdit = nullptr;
    durationEdit = nullptr;

    artistEdit = nullptr;
    recordCompanyEdit = nullptr;
    rpmCombo = nullptr;
}