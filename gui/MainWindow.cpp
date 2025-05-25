#include "MainWindow.h"
#include <QMessageBox>
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "AdminPage.h"  //poi toglierai
#include "UserPage.h"   //poi toglierai

MainWindow::MainWindow(QStackedWidget *stackedwidget, QWidget *parent) : QMainWindow(parent), stack(stackedwidget)  {
    setWindowTitle("Accesso");
    setMinimumSize(1000, 800);

    stackedwidget->setStyleSheet("background-color: rgb(104, 193, 225);"); 

    // Schermata principale con due sezioni: Admin e Utente
    QWidget *loginWidget = new QWidget(this);
    QVBoxLayout *loginLayout = new QVBoxLayout(loginWidget);

    // Layout per posizionare in alto a destra
    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->addStretch();  // Spinge a destra
    
    // Pulsante per uscire
    QWidget *exitWidget = new QWidget(loginWidget);
    QPushButton *exitButton = new QPushButton("Esci", exitWidget);
    exitButton->setFixedSize(120, 40);
    exitButton->setStyleSheet("font-size: 18px; padding: 5px;");
    connect(exitButton, &QPushButton::clicked, this, &MainWindow::close);

    topLayout->addWidget(exitButton);

    loginLayout->addLayout(topLayout);
    loginLayout->addStretch();

    // Widget Admin
    QWidget *adminWidget = new QWidget(loginWidget);
    QVBoxLayout *adminLayout = new QVBoxLayout(adminWidget);
    adminLayout->setAlignment(Qt::AlignCenter);

    QLabel *adminLabel = new QLabel("Accesso per Admin", adminWidget);
    adminLabel->setAlignment(Qt::AlignCenter);
    adminLabel->setStyleSheet("font-size: 24px; font-weight: bold;");

    adminUsername = new QLineEdit(adminWidget);
    adminUsername->setPlaceholderText("Username");
    adminUsername->setFixedSize(300, 40);  // Imposta una larghezza specifica
    adminUsername->setStyleSheet("font-size: 18px; padding: 5px;");

    adminPassword = new QLineEdit(adminWidget);
    adminPassword->setPlaceholderText("Password");
    adminPassword->setEchoMode(QLineEdit::Password);
    adminPassword->setFixedSize(300, 40);
    adminPassword->setStyleSheet("font-size: 18px; padding: 5px;");

    QPushButton *adminLoginButton = new QPushButton("Accedi come Admin", adminWidget);
    adminLoginButton->setFixedSize(250, 50);
    adminLoginButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    adminLoginButton->setStyleSheet("font-size: 20px; padding: 10px;");
    connect(adminLoginButton, &QPushButton::clicked, this, &MainWindow::handleAdminAccess);

    adminLayout->addWidget(adminLabel);
    adminLayout->addWidget(adminUsername);
    adminLayout->addWidget(adminPassword);
    adminLayout->addWidget(adminLoginButton, 0, Qt::AlignCenter);
    adminWidget->setLayout(adminLayout);

    // Widget Utente
    QWidget *userWidget = new QWidget(loginWidget);
    QVBoxLayout *userLayout = new QVBoxLayout(userWidget);
    userLayout->setAlignment(Qt::AlignCenter);

    QLabel *userLabel = new QLabel("Accesso per Utente", userWidget);
    userLabel->setAlignment(Qt::AlignCenter);
    userLabel->setStyleSheet("font-size: 24px; font-weight: bold;");

    QPushButton *userAccessButton = new QPushButton("Accedi come Utente", userWidget);
    userAccessButton->setFixedSize(250, 50);
    userAccessButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    userAccessButton->setStyleSheet("font-size: 20px; padding: 10px;");
    connect(userAccessButton, &QPushButton::clicked, this, &MainWindow::handleUserAccess);

    userLayout->addWidget(userLabel);
    userLayout->addWidget(userAccessButton, 0, Qt::AlignCenter);
    userWidget->setLayout(userLayout);

    // Aggiunge entrambi i widget alla schermata principale
    loginLayout->addWidget(adminWidget);
    loginLayout->addWidget(userWidget);
    loginLayout->addStretch();
    loginLayout->setAlignment(Qt::AlignCenter);

    setCentralWidget(loginWidget);

    loginWidget->setStyleSheet("background-color: rgb(104, 193, 225);"); 
    //userWidget->setStyleSheet("background-color: rgb(175, 238, 238);"); 
    //adminWidget->setStyleSheet("background-color: rgb(175, 238, 238);"); 
}

// Metodo per gestire l'accesso come Admin
void MainWindow::handleAdminAccess() {
    if (adminUsername->text() == "admin" && adminPassword->text() == "admin") {
        QMessageBox::information(this, "AVVISO", "Caricamento pagina Admin");
        adminUsername->clear();
        adminPassword->clear();
        stack->setCurrentIndex(2);
    } else {
        QMessageBox::warning(this, "ERRORE", "Username o password errati!");
        adminUsername->clear();
        adminPassword->clear();
    }
}

// Metodo per gestire l'accesso come Utente
void MainWindow::handleUserAccess() {
    QMessageBox::information(this, "AVVISO", "Caricamento pagina Utente");
    stack->setCurrentIndex(1);
}

// Metodo per chiudere l'applicazione
void MainWindow::close() {
    QApplication::quit();
}