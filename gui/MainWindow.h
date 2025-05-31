// File MainWindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QStackedWidget>
#include <QLineEdit>

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    QStackedWidget *stack;
public:
    MainWindow(QStackedWidget *stackedwidget, QWidget *parent = nullptr);
private slots:
    void handleAdminAccess();
    void handleUserAccess();
    void close();

private: 
    QLineEdit *adminUsername;
    QLineEdit *adminPassword;
};

#endif // MAINWINDOW_H
