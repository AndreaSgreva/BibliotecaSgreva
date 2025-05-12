#ifndef JSON_H
#define JSON_H

#include <QObject>
#include <QString>
#include <QList>
#include "../modello_logico/Biblioteca.h"

class JsonObserver;

class Json : public QObject {
    Q_OBJECT
public:
    explicit Json(const QString& filePath = "", QObject *parent = nullptr);

    // Carica i dati dal file JSON
    QList<Biblioteca*> loadList();
    // Salva i dati nel file JSON
    void setFilePath(const QString& path);

    bool aggiornaStatoOggetto(Biblioteca* oggetto); // Per prenotazioni/restituzioni
    bool rimuoviOggetto(Biblioteca* oggetto); // Per eliminazioni
    bool aggiungiOggetto(Biblioteca* oggetto); // Per aggiunta
    bool modificaOggetto(Biblioteca* oggetto); // Per modifiche

    // NUOVI metodi per gli observer
    void aggiungiObserver(JsonObserver* observer);
    void rimuoviObserver(JsonObserver* observer);

private:
    QString path;
    int findIndex(Biblioteca* oggetto) const;
    QList<Biblioteca *> biblioteca;
    QList<JsonObserver*> observers;
    void notificaObservers();
};

#endif // JSON_H
