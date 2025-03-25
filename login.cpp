#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QSqlQuery>

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    populateQuestionComboBox();
}

login::~login()
{
    delete ui;
}

void login::on_loginButton_clicked()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    if (username == "admin" && password == "admin") {
        emit loginSuccessful();
        this->close();
    }
    else if (validateCredentials(username, password)) {
        userId=getUserId(username,password);
        emit loginSuccessful();
        this->close();
    } else {
        QMessageBox::critical(this, "Login Error", "Invalid username or password");
    }
}

bool login::validateCredentials(const QString& nom, const QString& mdp)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM employe WHERE nom = :nom AND mdp = :mdp");
    query.bindValue(":nom", nom);
    query.bindValue(":mdp", mdp);
    return query.exec() && query.next();
}

int login::getUserId(const QString& nom, const QString& mdp) {
    QSqlQuery query;
    query.prepare("SELECT id_employe FROM employe WHERE nom = :nom AND mdp = :mdp");
    query.bindValue(":nom", nom);
    query.bindValue(":mdp", mdp);
    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    } else {
        return -1;
    }
}

int login::getId() const {
    return userId;
}

void login::populateQuestionComboBox()
{
    ui->question->clear();
    QSqlQuery query("SELECT question FROM employe");
    while (query.next()) {
        QString question = query.value(0).toString();
        ui->question->addItem(question);
    }
}

void login::on_resetButton_clicked()
{
    QString selectedQuestion = ui->question->currentText();
    QString answer = ui->reponse->text();
    QSqlQuery query;
    query.prepare("SELECT mdp FROM employe WHERE question = :question AND reponse = :reponse");
    query.bindValue(":question", selectedQuestion);
    query.bindValue(":reponse", answer);

    if (query.exec() && query.next()) {
        QString password = query.value(0).toString();
        QMessageBox::information(this, "Password", "Your password is: " + password);
    }
}
