#include "connection.h"

Connection::Connection(){}

bool Connection::createconnection()
{
    db = QSqlDatabase::addDatabase("QODBC");
    bool test=false;
    db.setDatabaseName("base");
    db.setUserName("yahya");
    db.setPassword("yahya");

    if (db.open()) test=true;
    return  test;
}

void Connection::closeconnetion(){db.close();}
