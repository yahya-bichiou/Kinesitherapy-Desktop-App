#include "salle.h"
#include <QDebug>

int Salle::nombre(int num_salle)
{
    QSqlQuery query;
    query.prepare("SELECT nbr FROM salles WHERE num_salle = :num_salle");
    query.bindValue(":num_salle", num_salle);

    if (query.exec() && query.next()) {
        int capacite = query.value(0).toInt();
        return capacite;
    } else {
        return -1;
    }
}

void Salle::updateNombre(int num_salle, int nbr)
{
    QSqlQuery query;
    query.prepare("UPDATE salles SET nbr = :nbr WHERE num_salle = :num_salle");
    query.bindValue(":nbr", nbr);
    query.bindValue(":num_salle", num_salle);
    if (query.exec()){
        qDebug() << "updated:" << nbr;
    }
    else
        qDebug() << "not updated";
}

int Salle::capacity(int num_salle)
{
    QSqlQuery query;
    query.prepare("SELECT capacite FROM salles WHERE num_salle = :num_salle");
    query.bindValue(":num_salle", num_salle);

    if (query.exec() && query.next()) {
        int capacite = query.value(0).toInt();
        return capacite;
    } else {
        return -1;
    }
}
