#ifndef SALLE_H
#define SALLE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include<QComboBox>

class Salle
{
    QString num_salle, type, capacite, nbr;

public:

    //constructeurs
    Salle(){}
    Salle(QString,QString,QString,QString);

    //getters

    //setters

    //fonctionnalites de base
    int nombre (int);
    void updateNombre(int, int);
    int capacity (int);
};

#endif // SALLE_H
