#include "mainwindow.h"
#include "login.h"
#include "connection.h"
#include <QMessageBox>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    bool test = c.createconnection();

    if (!test) {
        QMessageBox::critical(nullptr, QObject::tr("Database Connection Failed"),
                              QObject::tr("Failed to connect to the database.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        return -1;
    }

    login loginPage;
    MainWindow employePage;
    QObject::connect(&loginPage, &login::loginSuccessful, [&employePage, &loginPage]() {
        employePage.updateNameAndSurnameLabels(loginPage.getId());
        employePage.showFullScreen();
    });

    loginPage.showFullScreen();

    return a.exec();
}
