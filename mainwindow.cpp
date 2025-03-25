#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "salle.h"
#include "login.h"
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
#include <QTextToSpeech>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //employe
    ascending = true;
    ui->tableView->setModel(Etmp.afficher(ascending));
    Employe E;
    E.populateComboBox(ui->comboBoxdel_2);
    connect(ui->recherche, &QLineEdit::textChanged, this, &MainWindow::on_recherche_textChanged);
    createChart();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_ajouter_2_clicked()
{
        QString id_employe=ui->lineEdit_id_2->text();
        QString cin=ui->lineEdit_cin_2->text();
        QString nom=ui->lineEdit_nom_2->text();
        QString prenom=ui->lineEdit_prenom_2->text();
        QString tel=ui->lineEdit_tel_2->text();
        QString email=ui->lineEdit_email_2->text();
        QString mdp=ui->lineEdit_mdp_2->text();
        QString type=ui->lineEdit_type_2->text();
        QString question=ui->lineEdit_question_2->text();
        QString reponse=ui->lineEdit_reponse_2->text();

        if (Employe::referenceExists(id_employe)) {
                                QMessageBox::critical(nullptr, QObject::tr("Invalid input"),
                                                      QObject::tr("ID already exists."),
                                                      QMessageBox::Cancel);
            return;
        }
        //control id
        if (id_employe.length() < 1 || !id_employe.toInt()) {
               QMessageBox::warning(nullptr, "Validation Error", "Id must not be empty");
               return;
           }
        //control cin
        if (cin.length() != 8 || !cin.toInt()) {
            QMessageBox::warning(nullptr, "Validation Error", "CIN must be exactly 8 numeric characters.");
               return;
           }
        //control tel
        if (tel.length() != 8 || !tel.toInt()) {
               QMessageBox::warning(nullptr, "Validation Error", "Tel must be exactly 8 numeric characters.");
               return;
        }
        //control nom
        if (nom.isEmpty()) {
            QMessageBox::warning(this, "Validation Error", "Nom must not be empty");
            return;
        }
        if (nom.contains(QRegExp("\\d"))) {
            QMessageBox::warning(this, "Validation Error", "Nom must not contain numbers");
            return;
        }
        //control prenom
        if (prenom.isEmpty()) {
            QMessageBox::warning(this, "Validation Error", "Prenom must not be empty");
            return;
        }
        if (prenom.contains(QRegExp("\\d"))) {
            QMessageBox::warning(this, "Validation Error", "Prenom must not contain numbers");
            return;
        }
        //control email
        if (email.isEmpty()) {
            QMessageBox::warning(this, "Validation Error", "Email must not be empty");
            return;
        }
        QRegularExpression regex("(gmail\\.com|outlook\\.com|esprit\\.com)$");
        QRegularExpressionMatch match = regex.match(email);
        if (!match.hasMatch()) {
            QMessageBox::warning(this, "Validation Error", "Invalid email domain. Accepted domains are gmail.com, outlook.com, and esprit.com");
            return;
        }
        //control mdp
        if (mdp.isEmpty()) {
            QMessageBox::warning(this, "Validation Error", "Mdp must not be empty");
            return;
        }
        //control type
        if (type.isEmpty()) {
            QMessageBox::warning(this, "Validation Error", "Type must not be empty");
            return;
        }
        Employe E(id_employe,cin,nom,prenom,tel,email,mdp,type,question,reponse);
        //ui->comboBoxdel->addItem(id);
        bool test=E.ajouter();
        if(test)
            {
                ui->tableView->setModel(Etmp.afficher(ascending));
                createChart();
                QMessageBox::information(nullptr, QObject::tr("ok"),
                            QObject::tr("Ajout effectué\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
                ui->lineEdit_id_2->clear();
                ui->lineEdit_cin_2->clear();
                ui->lineEdit_nom_2->clear();
                ui->lineEdit_prenom_2->clear();
                ui->lineEdit_tel_2->clear();
                ui->lineEdit_email_2->clear();
                ui->lineEdit_mdp_2->clear();
                ui->lineEdit_type_2->clear();
                ui->lineEdit_question_2->clear();
                ui->lineEdit_reponse_2->clear();
                E.populateComboBox(ui->comboBoxdel_2);

        }
            else
                QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
                            QObject::tr("Ajout non effectué\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_supprimer_2_clicked()
{
    QString id_employe=ui->comboBoxdel_2->currentText();
    bool test=Etmp.supprimer(id_employe);
    if(test)
        {
            ui->tableView->setModel(Etmp.afficher(ascending));
            Employe E;
            E.populateComboBox(ui->comboBoxdel_2);
            createChart();
            QMessageBox::information(nullptr, QObject::tr("ok"),
                        QObject::tr("Suppression effectué\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

    }
        else
            QMessageBox::critical(nullptr, QObject::tr("Not Ok"),
                        QObject::tr("Suppression non effectué\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
        int selectedId = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 0)).toInt();
        Employe emp;
        emp = emp.getEmployeById(selectedId);
        ui->lineEdit_idm_2->setReadOnly(true);
        ui->lineEdit_idm_2->setText(emp.getId());
        ui->lineEdit_cinm_2->setText(emp.getCin());
        ui->lineEdit_nomm_2->setText(emp.getNom());
        ui->lineEdit_prenomm_2->setText(emp.getPrenom());
        ui->lineEdit_telm_2->setText(emp.getTel());
        ui->lineEdit_emailm_2->setText(emp.getEmail());
        ui->lineEdit_mdpm_2->setText(emp.getMdp());
        ui->lineEdit_typem_2->setText(emp.getType());
        ui->lineEdit_questionm_2->setText(emp.getQuestion());
        ui->lineEdit_reponsem_2->setText(emp.getReponse());

}

void MainWindow::on_pushButton_modifier_2_clicked()
{
        QString id_employe = ui->lineEdit_idm_2->text();
        QString cin = ui->lineEdit_cinm_2->text();
        QString nom = ui->lineEdit_nomm_2->text();
        QString prenom = ui->lineEdit_prenomm_2->text();
        QString tel = ui->lineEdit_telm_2->text();
        QString email = ui->lineEdit_emailm_2->text();
        QString mdp = ui->lineEdit_mdpm_2->text();
        QString type = ui->lineEdit_typem_2->text();
        QString question = ui->lineEdit_questionm_2->text();
        QString reponse = ui->lineEdit_reponsem_2->text();
        //control id
        if (id_employe.length() < 1 || !id_employe.toInt()) {
               QMessageBox::warning(this, "Validation Error", "Id must not be empty");
               return;
           }
        //control cin
        if (cin.length() != 8 || !cin.toInt()) {
               QMessageBox::warning(this, "Validation Error", "CIN must be exactly 8 numeric characters.");
               return;
           }
        //control tel
        if (tel.length() != 8 || !tel.toInt()) {
               QMessageBox::warning(this, "Validation Error", "Tel must be exactly 8 numeric characters.");
               return;
        }
        //control nom
        if (nom.isEmpty()) {
            QMessageBox::warning(this, "Validation Error", "Nom must not be empty");
            return;
        }
        if (nom.contains(QRegExp("\\d"))) {
            QMessageBox::warning(this, "Validation Error", "Nom must not contain numbers");
            return;
        }
        //control prenom
        if (prenom.isEmpty()) {
            QMessageBox::warning(this, "Validation Error", "Prenom must not be empty");
            return;
        }
        if (prenom.contains(QRegExp("\\d"))) {
            QMessageBox::warning(this, "Validation Error", "Prenom must not contain numbers");
            return;
        }
        //control email
        if (email.isEmpty()) {
            QMessageBox::warning(this, "Validation Error", "Email must not be empty");
            return;
        }
        QRegularExpression regex("(gmail\\.com|outlook\\.com|esprit\\.com)$");
        QRegularExpressionMatch match = regex.match(email);
        if (!match.hasMatch()) {
            QMessageBox::warning(this, "Validation Error", "Invalid email domain. Accepted domains are gmail.com, outlook.com, and esprit.com");
            return;
        }
        //control mdp
        if (mdp.isEmpty()) {
            QMessageBox::warning(this, "Validation Error", "Mdp must not be empty");
            return;
        }
        //control type
        if (type.isEmpty()) {
            QMessageBox::warning(this, "Validation Error", "Type must not be empty");
            return;
        }

        Employe emp(id_employe, cin, nom, prenom, tel, email, mdp, type, question, reponse);
        bool modificationSuccess = emp.modifier();

        if (modificationSuccess) {
            ui->tableView->setModel(Etmp.afficher(ascending));
            createChart();
            QMessageBox::information(nullptr, QObject::tr("Modification success"),
                                     QObject::tr("Modification effectuée\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);
            ui->lineEdit_idm_2->clear();
            ui->lineEdit_cinm_2->clear();
            ui->lineEdit_nomm_2->clear();
            ui->lineEdit_prenomm_2->clear();
            ui->lineEdit_telm_2->clear();
            ui->lineEdit_emailm_2->clear();
            ui->lineEdit_mdpm_2->clear();
            ui->lineEdit_typem_2->clear();
            ui->lineEdit_questionm_2->clear();
            ui->lineEdit_reponsem_2->clear();

        } else {
            QMessageBox::critical(nullptr, QObject::tr("Modification failed"),
                                  QObject::tr("Modification non effectuée\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
        }
}


void MainWindow::on_recherche_textChanged(const QString &text)
{
    QSqlQueryModel *filteredModel = Etmp.filterTable(text);
    ui->tableView->setModel(filteredModel);
}

void MainWindow::on_tri_2_clicked()
{
        ascending = !ascending;
        ui->tableView->setModel(Etmp.afficher(ascending));
}

void MainWindow::on_add_2_2_clicked()
{
    QString exportFormat = ui->comboBox_2->currentText();
    if (exportFormat == "PDF") {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save PDF File"), "", "PDF Files (*.pdf)");
        if (fileName.isEmpty()) {
            return;
        }
        QTextDocument doc;
        Employe E;
        QSqlQueryModel *model = E.pdf();
        QTextCursor cursor(&doc);
        QTextTableFormat tableFormat;
        tableFormat.setAlignment(Qt::AlignLeft);
        QTextTable *table = cursor.insertTable(model->rowCount() + 1, model->columnCount(), tableFormat);
        QTextFrameFormat frameFormat = cursor.currentFrame()->frameFormat();
        frameFormat.setBorder(1);
        cursor.currentFrame()->setFrameFormat(frameFormat);
        for (int i = 0; i < model->columnCount(); ++i) {
            table->cellAt(0, i).firstCursorPosition().insertText(model->headerData(i, Qt::Horizontal).toString());
        }
        for (int i = 0; i < model->rowCount(); ++i) {
            for (int j = 0; j < model->columnCount(); ++j) {
                table->cellAt(i + 1, j).firstCursorPosition().insertText(model->data(model->index(i, j)).toString());
            }
        }
        QPrinter printer;
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);
        doc.print(&printer);
    }
}


void MainWindow::createChart()
{
    int totalCount = 0;
    QLayoutItem *child;
    while ((child = ui->verticalLayout_2->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }
    QPieSeries *series = new QPieSeries();
    Employe E;
    E.pieChart(series, &totalCount);

    for (QPieSlice *slice : series->slices()) {
        qreal percentage = (slice->percentage() * 100);
        slice->setLabel(QString("%1 (%2%)").arg(slice->label()).arg(QString::number(percentage, 'f', 1)));
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->verticalLayout_2->addWidget(chartView);
}



void MainWindow::updateNameAndSurnameLabels(int id_employe) {
    QSqlQuery query;
    query.prepare("SELECT nom, prenom, type FROM employe WHERE id_employe = :id_employe");
    query.bindValue(":id_employe", id_employe);
    if (query.exec() && query.next()) {
        QString name = query.value(0).toString();
        QString surname = query.value(1).toString();
        QString type = query.value(2).toString();
        ui->nameLabel_2->setText(name);
        ui->lastNameLabel_2->setText(surname);
        ui->typeLabel_2->setText(type);
    }
    else
    {
        qDebug() << query.lastQuery();
        ui->nameLabel_2->setText("user");
        ui->lastNameLabel_2->setText("user");
        ui->typeLabel_2->setText("none");
    }
}


// menu ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void MainWindow::on_employes_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_equipements_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_patients_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_rendezvous_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_salles_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_therapies_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_deconnexion_2_clicked()
{
    loginPage.showFullScreen();
    close();
}

void MainWindow::on_close_clicked()
{
    close();
}

