// File Json.cpp
#include "Json.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include "../modello_logico/Libro.h"
#include "../modello_logico/Film.h"
#include "../modello_logico/Vinile.h"

// NUOVO
#include "JsonObserver.h"

Json::Json(const QString &filePath, QObject *parent) : QObject(parent), path(filePath) {}

// Metodo per impostare il percorso del file JSON
void Json::setFilePath(const QString& path){
    this->path = path;
}

// Metodo per caricare i dati dal file JSON
QList<Biblioteca*> Json::loadList(){
    QList<Biblioteca*> listaOggetti;
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Impossibile aprire il file JSON!");
        return listaOggetti;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (doc.isNull() || !doc.isArray()) {
        qWarning("Errore nel parsing del JSON!");
        return listaOggetti;
    }

    QJsonArray jsonArray = doc.array();
    for (const QJsonValue& value : jsonArray) {
        QJsonObject obj = value.toObject();
        QString classe = obj["classe"].toString();
        QString immagine = obj["immagine"].toString();
        QString titolo = obj["titolo"].toString();
        QString genere = obj["genere"].toString();
        QString lingua = obj["lingua"].toString();
        double costo = obj["costo"].toDouble();
        int anno = obj["anno"].toInt();
        int numeroCopie = obj["numeroCopie"].toInt();
        int numeroPrestiti = obj["numeroPrestiti"].toInt();
        bool disponibile = obj["disponibile"].toBool();

        if (classe == "libro") {  
            QString autore = obj["autore"].toString();
            int pagine = obj["pagine"].toInt();
            QString isbn = obj["isbn"].toString();
            listaOggetti.append(new Libro(immagine.toStdString(), titolo.toStdString(), anno, genere.toStdString(), lingua.toStdString(), disponibile, 
                costo, numeroCopie, numeroPrestiti, autore.toStdString(), pagine, isbn.toStdString()));
        } 
        else if (classe == "film") {  
            QString regista = obj["regista"].toString();
            QString protagonisti = obj["protagonisti"].toString();
            int durata = obj["durata"].toInt();
            listaOggetti.append(new Film(immagine.toStdString(), titolo.toStdString(), anno, genere.toStdString(), lingua.toStdString(), disponibile, 
                costo, numeroCopie, numeroPrestiti, regista.toStdString(), protagonisti.toStdString(), durata));
        } 
        else if (classe == "vinile") {  
            QString artista = obj["artista"].toString();
            QString casaDiscografica = obj["casaDiscografica"].toString();
            int rpm = obj["rpm"].toInt();
            listaOggetti.append(new Vinile(immagine.toStdString(), titolo.toStdString(), anno, genere.toStdString(), lingua.toStdString(), disponibile, 
                costo, numeroCopie, numeroPrestiti, artista.toStdString(), casaDiscografica.toStdString(), rpm));
        }
    }
    biblioteca = listaOggetti;
    return listaOggetti;
    
}

// CON DEEPSEEK
// Metodo per salvare i dati nel file JSON
/*
bool Json::saveList(const QList<Biblioteca*>& lista) const {
    if (path.isEmpty()) {
        qWarning("Nessun percorso file specificato per il salvataggio!");
        return false;
    }

    QJsonArray jsonArray;
    for (auto oggetto : lista) {
        QJsonObject obj;
        obj["immagine"] = QString::fromStdString(oggetto->getImmagine());
        obj["titolo"] = QString::fromStdString(oggetto->getTitolo());
        obj["anno"] = oggetto->getAnno();
        obj["genere"] = QString::fromStdString(oggetto->getGenere());
        obj["lingua"] = QString::fromStdString(oggetto->getLingua());
        obj["disponibile"] = oggetto->getDisponibile();
        obj["costo"] = oggetto->getCosto();
        obj["numeroCopie"] = oggetto->getNumeroCopie();
        obj["numeroPrestiti"] = oggetto->getNumeroPrestiti();

        // Dynamic cast per tipo specifico
        if (auto libro = dynamic_cast<Libro*>(oggetto)) {
            obj["classe"] = "libro";
            obj["autore"] = QString::fromStdString(libro->getAutore());
            obj["pagine"] = libro->getPagine();
            obj["isbn"] = QString::fromStdString(libro->getISBN());
        }
        else if (auto film = dynamic_cast<Film*>(oggetto)) {
            obj["classe"] = "film";
            obj["regista"] = QString::fromStdString(film->getRegista());
            obj["protagonisti"] = QString::fromStdString(film->getProtagonista());
            obj["durata"] = film->getDurata();
        }
        else if (auto vinile = dynamic_cast<Vinile*>(oggetto)) {
            obj["classe"] = "vinile";
            obj["artista"] = QString::fromStdString(vinile->getArtista());
            obj["casaDiscografica"] = QString::fromStdString(vinile->getCasaDiscografica());
            obj["rpm"] = vinile->getRPM();
        }
        jsonArray.append(obj);
    }

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qWarning("Errore durante l'apertura del file per il salvataggio!");
        return false;
    }

    file.write(QJsonDocument(jsonArray).toJson());
    file.close();
    return true;
}
*/

// Metodo per trovare l'indice di un oggetto nel file JSON
int Json::findIndex(Biblioteca* oggetto) const {
    if (!oggetto) {
        qWarning() << "Oggetto nullo";
        return -1;
    }
    for (int i = 0; i < biblioteca.size(); ++i) {
        if (biblioteca[i] == oggetto) {
            return i;
        }
    }
    return -1;
}
/*
int Json::findIndex(Biblioteca* oggetto) const {
    if (!oggetto || path.isEmpty()) {
        qWarning() << "Oggetto nullo o percorso file non valido";
        return -1;
    }

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qCritical() << "Impossibile aprire il file:" << file.errorString();
        return -1;
    }

    QJsonArray jsonArray = QJsonDocument::fromJson(file.readAll()).array();
    file.close();

    const QString titolo = QString::fromStdString(oggetto->getTitolo());
    const int anno = oggetto->getAnno();
    const QString lingua = QString::fromStdString(oggetto->getLingua());

    for (int i = 0; i < jsonArray.size(); ++i) {
        QJsonObject obj = jsonArray[i].toObject();
        if (obj["titolo"].toString() == titolo &&
            obj["anno"].toInt() == anno &&
            obj["lingua"].toString() == lingua) {
            return i;
        }
    }

    qWarning() << "Oggetto non trovato:" << titolo;
    return -1;
}
*/
// Metodo per aggiornare lo stato di un oggetto nel file JSON (prenotazione/restituzione)
bool Json::aggiornaStatoOggetto(Biblioteca* oggetto) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qCritical() << "Impossibile aprire il file per l'aggiornamento";
        return false;
    }

    QJsonArray jsonArray = QJsonDocument::fromJson(file.readAll()).array();
    file.close();

    int index = findIndex(oggetto);
    if (index == -1) {
        qWarning() << "Oggetto non trovato nel file JSON";
        return false;
    }

    QJsonObject obj = jsonArray[index].toObject();
    obj["disponibile"] = oggetto->getDisponibile();
    obj["numeroPrestiti"] = oggetto->getNumeroPrestiti();

    jsonArray.replace(index, obj);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qCritical() << "Impossibile aprire il file per il salvataggio";
        return false;
    }

    if (file.write(QJsonDocument(jsonArray).toJson()) != -1) {
        file.close();
        notificaObservers(); // Notifica gli observer dopo l'aggiornamento
        return true;
    }
    file.close();
    return false;
    /*file.write(QJsonDocument(jsonArray).toJson());
    file.close();
    return true;*/
}

// Metodo per rimuovere un oggetto dal file JSON
bool Json::rimuoviOggetto(Biblioteca* oggetto) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qCritical() << "Impossibile aprire il file per la rimozione";
        return false;
    }

    QJsonArray jsonArray = QJsonDocument::fromJson(file.readAll()).array();
    file.close();

    int index = findIndex(oggetto);
    if (index == -1) {
        qWarning() << "Oggetto non trovato nel file JSON";
        return false;
    }

    jsonArray.removeAt(index);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qCritical() << "Impossibile aprire il file per il salvataggio";
        return false;
    }

    if (file.write(QJsonDocument(jsonArray).toJson()) != -1) {
        // 1. Prima rimuovi dalla lista
        biblioteca.removeAt(index);
        
        // 2. Notifica gli observer PRIMA di eliminare l'oggetto
        notificaObservers();
        
        // 3. Ora puoi eliminare l'oggetto in sicurezza
        delete oggetto;
        
        file.close();
        return true;
    }
    file.close();
    return false;
    /*if (file.write(QJsonDocument(jsonArray).toJson()) != -1) {
        biblioteca.removeAt(index);  // Rimuovi dalla lista interna
        delete oggetto;  // Dealloca l'oggetto
        file.close();
        return true;
    }
    file.close();
    return true;*/
}

// Metodo per aggiungere un oggetto al file JSON
bool Json::aggiungiOggetto(Biblioteca* oggetto) {
    //biblioteca.append(oggetto);
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qCritical() << "Impossibile aprire il file per l'aggiunta";
        return false;
    }

    QJsonArray jsonArray = QJsonDocument::fromJson(file.readAll()).array();
    file.close();

    QJsonObject newObj;
    newObj["immagine"] = QString::fromStdString(oggetto->getImmagine());
    newObj["titolo"] = QString::fromStdString(oggetto->getTitolo());
    newObj["anno"] = oggetto->getAnno();
    newObj["genere"] = QString::fromStdString(oggetto->getGenere());
    newObj["lingua"] = QString::fromStdString(oggetto->getLingua());
    newObj["disponibile"] = oggetto->getDisponibile();
    newObj["costo"] = oggetto->getCosto();
    newObj["numeroCopie"] = oggetto->getNumeroCopie();
    newObj["numeroPrestiti"] = oggetto->getNumeroPrestiti();

    // Dynamic cast per tipo specifico
    if (auto libro = dynamic_cast<Libro*>(oggetto)) {
        newObj["classe"] = "libro";
        newObj["autore"] = QString::fromStdString(libro->getAutore());
        newObj["pagine"] = libro->getPagine();
        newObj["isbn"] = QString::fromStdString(libro->getISBN());
    }
    else if (auto film = dynamic_cast<Film*>(oggetto)) {
        newObj["classe"] = "film";
        newObj["regista"] = QString::fromStdString(film->getRegista());
        newObj["protagonisti"] = QString::fromStdString(film->getProtagonista());
        newObj["durata"] = film->getDurata();
    }
    else if (auto vinile = dynamic_cast<Vinile*>(oggetto)) {
        newObj["classe"] = "vinile";
        newObj["artista"] = QString::fromStdString(vinile->getArtista());
        newObj["casaDiscografica"] = QString::fromStdString(vinile->getCasaDiscografica());
        newObj["rpm"] = vinile->getRPM();
    }

    jsonArray.append(newObj);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qCritical() << "Impossibile aprire il file per il salvataggio";
        return false;
    }

    
    if (file.write(QJsonDocument(jsonArray).toJson()) != -1) {
        biblioteca.append(oggetto);
        file.close();
        notificaObservers(); // Notifica gli observer dopo l'aggiunta
        return true;
    }
    file.close();
    return false;
    /*file.write(QJsonDocument(jsonArray).toJson());
    file.close();
    return true;*/
}

// Metodo per modificare un oggetto nel file JSON
bool Json::modificaOggetto(Biblioteca* oggetto) {
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qCritical() << "Impossibile aprire il file per la modifica";
        return false;
    }

    QJsonArray jsonArray = QJsonDocument::fromJson(file.readAll()).array();
    file.close();

    int index = findIndex(oggetto);
    if (index == -1) {
        qWarning() << "Oggetto non trovato nel file JSON";
        return false;
    }

    QJsonObject obj = jsonArray[index].toObject();
    obj["immagine"] = QString::fromStdString(oggetto->getImmagine());
    obj["titolo"] = QString::fromStdString(oggetto->getTitolo());
    obj["anno"] = oggetto->getAnno();
    obj["genere"] = QString::fromStdString(oggetto->getGenere());
    obj["lingua"] = QString::fromStdString(oggetto->getLingua());
    obj["disponibile"] = oggetto->getDisponibile();
    obj["costo"] = oggetto->getCosto();
    obj["numeroCopie"] = oggetto->getNumeroCopie();
    obj["numeroPrestiti"] = oggetto->getNumeroPrestiti();

    // Dynamic cast per tipo specifico
    if (auto libro = dynamic_cast<Libro*>(oggetto)) {
        obj["classe"] = "libro";
        obj["autore"] = QString::fromStdString(libro->getAutore());
        obj["pagine"] = libro->getPagine();
        obj["isbn"] = QString::fromStdString(libro->getISBN());
    }
    else if (auto film = dynamic_cast<Film*>(oggetto)) {
        obj["classe"] = "film";
        obj["regista"] = QString::fromStdString(film->getRegista());
        obj["protagonisti"] = QString::fromStdString(film->getProtagonista());
        obj["durata"] = film->getDurata();
    }
    else if (auto vinile = dynamic_cast<Vinile*>(oggetto)) {
        obj["classe"] = "vinile";
        obj["artista"] = QString::fromStdString(vinile->getArtista());
        obj["casaDiscografica"] = QString::fromStdString(vinile->getCasaDiscografica());
        obj["rpm"] = vinile->getRPM();
    }

    jsonArray.replace(index, obj);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qCritical() << "Impossibile aprire il file per il salvataggio";
        return false;
    }

    if (file.write(QJsonDocument(jsonArray).toJson()) != -1) {
        // Aggiorna l'oggetto esistente nella lista invece di cancellarlo
        if (index >= 0 && index < biblioteca.size()) {
            // Aggiorna le proprietà dell'oggetto esistente
            Biblioteca* existingObj = biblioteca[index];
            *existingObj = *oggetto; // Assumendo che ci siano operatori di copia implementati correttamente
        }
        file.close();
        notificaObservers();
        return true;
    }

    /*if (file.write(QJsonDocument(jsonArray).toJson()) != -1) {
        int index = findIndex(oggetto);
        if (index != -1) {
            delete biblioteca[index]; // Dealloca il vecchio oggetto
            biblioteca[index] = oggetto; // Sostituisci con quello nuovo
        }
        file.close();
        notificaObservers(); // Notifica gli observer dopo la modifica
        return true;
    }*/
    file.close();
    return false;
    /*file.write(QJsonDocument(jsonArray).toJson());
    file.close();
    return true;*/
}

// Metodo per aggiungere un observer
void Json::aggiungiObserver(JsonObserver* observer) {
    if(observer && !observers.contains(observer)) {
        observers.append(observer);
    }
}

// Metodo per rimuovere un observer
void Json::rimuoviObserver(JsonObserver* observer) {
    observers.removeAll(observer);
}

// Metodo per notificare gli observers
void Json::notificaObservers(){
    for(JsonObserver* observer : observers) {
        observer->onBibliotecaAggiornata(biblioteca);
    }
}

/*
bool Json::savePrenotaRestituisci(const QList<Biblioteca*>& lista){
    if (path.isEmpty()) {
        qCritical("Percorso file JSON non impostato!");
        return false;
    }

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qCritical("Impossibile aprire il file per il salvataggio!");
        return false;
    }

    QJsonArray jsonArray;
    for (const auto& oggetto : lista) {
        if (!oggetto) continue;

        QJsonObject obj;
        obj["immagine"] = QString::fromStdString(oggetto->getImmagine());
        obj["titolo"] = QString::fromStdString(oggetto->getTitolo());
        obj["anno"] = oggetto->getAnno();
        obj["genere"] = QString::fromStdString(oggetto->getGenere());
        obj["lingua"] = QString::fromStdString(oggetto->getLingua());
        obj["disponibile"] = oggetto->getDisponibile();
        obj["costo"] = oggetto->getCosto();
        obj["numeroCopie"] = oggetto->getNumeroCopie();
        obj["numeroPrestiti"] = oggetto->getNumeroPrestiti();

        // Aggiungi campi specifici in base al tipo
        if (auto libro = dynamic_cast<Libro*>(oggetto)) {
            obj["classe"] = "libro";
            obj["autore"] = QString::fromStdString(libro->getAutore());
            obj["pagine"] = libro->getPagine();
            obj["isbn"] = QString::fromStdString(libro->getISBN());
        } 
        else if (auto film = dynamic_cast<Film*>(oggetto)) {
            obj["classe"] = "film";
            obj["regista"] = QString::fromStdString(film->getRegista());
            obj["protagonisti"] = QString::fromStdString(film->getProtagonista());
            obj["durata"] = film->getDurata();
        }
        else if (auto vinile = dynamic_cast<Vinile*>(oggetto)) {
            obj["classe"] = "vinile";
            obj["artista"] = QString::fromStdString(vinile->getArtista());
            obj["casaDiscografica"] = QString::fromStdString(vinile->getCasaDiscografica());
            obj["rpm"] = vinile->getRPM();
        }

        jsonArray.append(obj);
    }

    file.write(QJsonDocument(jsonArray).toJson());
    file.close();
    qDebug("Salvataggio prenotazione/restituzione completato");
    return true;
}
*/