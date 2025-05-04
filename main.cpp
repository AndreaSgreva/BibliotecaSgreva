#include <QApplication>
#include <QStackedWidget>
#include <QFileDialog>
#include <QMessageBox>
#include "gui/MainWindow.h"
#include "gui/UserPage.h"
#include "gui/AdminPage.h"
#include "jsonHandler/Json.h"
#include "gui/EditCreatePage.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QStackedWidget stackWidget;

    // Selezione file JSON
    Json *jManager = new Json();
    QString path = QFileDialog::getOpenFileName(nullptr, "Scegli il file .json da cui prendere i dati", 
        "", "Json (*.json)");
    // Opzionale
    if (path.isEmpty()) {
        QMessageBox::critical(nullptr, "Errore", 
            "Nessun file selezionato. L'applicazione verrà chiusa.");
        return EXIT_FAILURE;
    }
    jManager->setFilePath(path);

    // Caricamento dati
    QList<Biblioteca *> listaOggetti = jManager->loadList();

    // Creazione delle pagine
    MainWindow *mainWindow = new MainWindow(&stackWidget);
    UserPage *userPage = new UserPage(listaOggetti, &stackWidget);
    AdminPage *adminPage = new AdminPage(listaOggetti, &stackWidget);
    EditCreatePage *editCreatePage = new EditCreatePage(&stackWidget);

    // NUOVE CONNESSIONI SPECIFICHE

    
    // Connessione per salvare prenotazioni e restituzioni
    QObject::connect(userPage, &UserPage::itemUpdated, jManager, &Json::aggiornaStatoOggetto);
    QObject::connect(adminPage, &AdminPage::itemUpdated, jManager, &Json::aggiornaStatoOggetto);
    QObject::connect(adminPage, &AdminPage::itemRemoved, jManager, &Json::rimuoviOggetto);
    QObject::connect(adminPage, &AdminPage::createItem, editCreatePage, &EditCreatePage::setupForCreation);
    QObject::connect(adminPage, &AdminPage::modifyItem, editCreatePage, &EditCreatePage::setupForEditing);

    QObject::connect(editCreatePage, &EditCreatePage::itemCreated, jManager, &Json::aggiungiOggetto);
    QObject::connect(editCreatePage, &EditCreatePage::itemUpdated, jManager, &Json::modificaOggetto);
    
    // NUOVO Observers
    jManager->aggiungiObserver(userPage);
    jManager->aggiungiObserver(adminPage);

    // Aggiunta delle pagine
    stackWidget.addWidget(mainWindow);  //index 0
    stackWidget.addWidget(userPage);    //index 1
    stackWidget.addWidget(adminPage);   //index 2
    stackWidget.addWidget(editCreatePage); //index 3
    stackWidget.show();

    //delete jManager; //serve?
    return app.exec();
}
