#ifndef EDITCREATEPAGE_H
#define EDITCREATEPAGE_H

#include "../modello_logico/Libro.h"
#include "../modello_logico/Film.h"
#include "../modello_logico/Vinile.h"
#include "../modello_logico/Biblioteca.h"
#include "Visitor.h"

#include <QWidget>
#include <QStackedWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QDialog>

class EditCreatePage : public QWidget, public Visitor {
    Q_OBJECT
public:
    enum Mode { Create, Edit };

    EditCreatePage(QStackedWidget* stackedWidget, QWidget* parent = nullptr);
    void setupForCreation();
    void setupForEditing(Biblioteca* item);

    void visit(Libro* libro) override;
    void visit(Film* film) override;
    void visit(Vinile* vinile) override;

    void setupCommonFields();
    void setupBookFields(Libro* libro = nullptr);
    void setupFilmFields(Film* film = nullptr);
    void setupVinileFields(Vinile* vinile = nullptr);
    void cleanLayout();
    Biblioteca* createNewItem();

    void aggiornaDisponibilità(Biblioteca* item);
    bool aggiornaFields(Biblioteca* item);
    bool aggiornaSpecificFields(Biblioteca* item);

signals:
    void itemCreated(Biblioteca* newItem);
    void itemUpdated(Biblioteca* updatedItem);

private slots:
    void saveItem();
    void goBack();

private:
    QStackedWidget* stack;
    Mode currentMode;
    Biblioteca* currentItem;
    QString currentType;
    
    QVBoxLayout* mainLayout;
    QFormLayout* formLayout;
    
    QLineEdit* titleEdit;
    QSpinBox* yearEdit;
    QLineEdit* genreEdit;
    QComboBox* languageCombo;
    QDoubleSpinBox* costEdit;
    QSpinBox* copiesEdit;
    QSpinBox* loansEdit;
    
    QLineEdit* authorEdit;
    QSpinBox* pagesEdit;
    QLineEdit* isbnEdit;
    
    QLineEdit* directorEdit;
    QLineEdit* protagonistEdit;
    QSpinBox* durationEdit;
    
    QLineEdit* artistEdit;
    QLineEdit* recordCompanyEdit;
    QSpinBox* rpmEdit;

    //per immagine
    QLineEdit* imagePathEdit;
    QPushButton* browseImageButton;
    QLabel* imagePreview;

    void clearFields();
};

#endif // EDITCREATEPAGE_H