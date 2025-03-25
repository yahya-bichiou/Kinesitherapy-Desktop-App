#include "employes.h"
#include <qmessagebox.h>
#include <QFileDialog>
#include <QSqlRecord>
#include <QTextDocument>
#include <QTextTable>
#include <QPrinter>
#include <QPrintDialog>
#include <QtSql>
#include <QtCharts>
#include <QSqlQuery>
#include <QSqlRecord>


Employe::Employe(QString id_employe,QString cin,QString nom,QString prenom,QString tel,QString email,QString mdp,QString type,QString question,QString reponse)
{
    this->id_employe=id_employe;
    this->cin=cin;
    this->nom=nom;
    this->prenom=prenom;
    this->tel=tel;
    this->email=email;
    this->mdp=mdp;
    this->type=type;
    this->question=question;
    this->reponse=reponse;
}

bool Employe::ajouter()
{
    QSqlQuery query;
    QString res = id_employe;
    query.prepare("insert into employe (id_employe,cin,nom,prenom,tel,email,mdp,type,question,reponse)" "values (:id_employe,:cin,:nom,:prenom,:tel,:email,:mdp,:type,:question,:reponse)");
    query.bindValue(":id_employe",res);
    query.bindValue(":cin",cin);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":tel",tel);
    query.bindValue(":email",email);
    query.bindValue(":mdp",mdp);
    query.bindValue(":type",type);
    query.bindValue(":question",question);
    query.bindValue(":reponse",reponse);

    return query.exec();

}

QSqlQueryModel * Employe::afficher(bool ascending)
{
    QSqlQueryModel *model = new QSqlQueryModel();

    QString query = QString("SELECT * FROM employe ORDER BY id_employe %1").arg(ascending ? "ASC" : "DESC");

    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("TEL"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("EMAIL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("MDP"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("QUESTION"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("REPONSE"));

    return model;
}

bool Employe::supprimer(QString id_employe)
{
    QSqlQuery query;
    QString res=id_employe;
    query.prepare("Delete from employe where id_employe=:id_employe");
    query.bindValue(":id_employe", res);
    return query.exec();
}

void Employe::populateComboBox(QComboBox* comboBoxdel) {
    QSqlQuery query;
    query.prepare ("select id_employe from employe");

    if (query.exec()) {
            comboBoxdel->clear();
            while (query.next()) {
                int id_employe = query.value(0).toInt();
                comboBoxdel->addItem(QString::number(id_employe));
            }
   }
}

Employe Employe::getEmployeById(int id_employe) {
    Employe emp;

    QSqlQuery query;
    query.prepare("SELECT * FROM employe WHERE id_employe = :id_employe");
    query.bindValue(":id_employe", id_employe);

    if (query.exec() && query.next()) {
        emp.setId(query.value("id_employe").toString());
        emp.setCin(query.value("cin").toString());
        emp.setNom(query.value("nom").toString());
        emp.setPrenom(query.value("prenom").toString());
        emp.setTel(query.value("tel").toString());
        emp.setEmail(query.value("email").toString());
        emp.setMdp(query.value("mdp").toString());
        emp.setType(query.value("type").toString());
        emp.setQuestion(query.value("question").toString());
        emp.setReponse(query.value("reponse").toString());
    }

    return emp;
}

bool Employe::modifier() {
    QSqlQuery query;
    query.prepare("UPDATE employe SET cin=:cin, nom=:nom, prenom=:prenom, tel=:tel, email=:email, mdp=:mdp, type=:type, question=:question, reponse=:reponse WHERE id_employe=:id_employe");
    query.bindValue(":id_employe", id_employe);
    query.bindValue(":cin", cin);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":tel", tel);
    query.bindValue(":email", email);
    query.bindValue(":mdp", mdp);
    query.bindValue(":type", type);
    query.bindValue(":question", question);
    query.bindValue(":reponse", reponse);

    return query.exec();
}

bool Employe::referenceExists(const QString &id_employe) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM employe WHERE id_employe = ?");
    query.bindValue(0, id_employe);
    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        return count > 0;
    }
    return false;
}

QSqlQueryModel * Employe::filterTable(const QString &text)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QString filterQuery = QString("SELECT * FROM employe WHERE nom LIKE '%%1%'").arg(text);
    model->setQuery(filterQuery);
    return model;
}

QSqlQueryModel * Employe::pdf()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM employe");
    return model;
}

void Employe::pieChart(QPieSeries *series, int *totalCount)
{
    QSqlQuery query("SELECT type, COUNT(*) FROM employe GROUP BY type");
    *totalCount = 0;
    while (query.next()) {
        QString type = query.value(0).toString();
        int count = query.value(1).toInt();
        *totalCount += count;
        series->append(type, count);
    }
}

