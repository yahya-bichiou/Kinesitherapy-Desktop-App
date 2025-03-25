#ifndef EMPLOYES_H
#define EMPLOYES_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include<QComboBox>
#include <QtCharts>

class Employe
{
    QString nom, prenom, email, mdp, type, id_employe, cin, tel, question, reponse;

public:

    //constructeurs
    Employe(){}
    Employe(QString,QString,QString,QString,QString,QString,QString,QString,QString,QString);

    //getters
    QString getNom(){return nom;}
    QString getPrenom(){return prenom;}
    QString getEmail(){return email;}
    QString getMdp(){return mdp;}
    QString getType(){return type;}
    QString getId(){return id_employe;}
    QString getCin(){return cin;}
    QString getTel(){return tel;}
    QString getQuestion(){return question;}
    QString getReponse(){return reponse;}

    //setters
    void setNom(QString n){nom=n;}
    void setPrenom(QString p){prenom=p;}
    void setEmail(QString e){email=e;}
    void setMdp(QString m){mdp=m;}
    void setType(QString t){type=t;}
    void setId(QString ide){id_employe=ide;}
    void setCin(QString ci){cin=ci;}
    void setTel(QString te){tel=te;}
    void setQuestion(QString q){question=q;}
    void setReponse(QString r){reponse=r;}

    //fonctionnalites de base
    bool ajouter();
    QSqlQueryModel * afficher(bool ascending);
    bool supprimer(QString);
    void populateComboBox(QComboBox*);
    Employe getEmployeById(int);
    bool modifier();
    QSqlQueryModel * filterTable(const QString&);
    static bool referenceExists(const QString &);
    void createRoleChart(QString *, int *);
    QSqlQueryModel * pdf();
    void pieChart(QPieSeries *, int*);
};


#endif // EMPLOYES_H
