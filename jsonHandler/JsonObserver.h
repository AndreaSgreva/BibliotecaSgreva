// File JsonObserver.h
#ifndef JSONOBSERVER_H
#define JSONOBSERVER_H

#include <QList>
class Biblioteca;

class JsonObserver {
public:
    virtual void onBibliotecaAggiornata(const QList<Biblioteca*>& nuovaLista) = 0;
    virtual ~JsonObserver() = default;
};

#endif // JSONOBSERVER_H