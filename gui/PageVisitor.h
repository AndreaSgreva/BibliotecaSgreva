// File PageVisitor.h
#ifndef PAGEVISITOR_H
#define PAGEVISITOR_H
#include "Visitor.h"
#include <QWidget>
#include <QVBoxLayout>

class Biblioteca;

class PageVisitor : public Visitor {
    private:
        QWidget *pageWidget;
        QVBoxLayout *pageLayout;
    public:
        PageVisitor();
        void visit(Biblioteca *biblioteca);
        void visit(Libro *libro) override; 
        void visit(Film *film) override;
        void visit(Vinile *vinile) override;
        QWidget* getObjectWidget() const;
};


#endif // PAGEVISITOR_H