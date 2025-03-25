#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "employes.h"
#include "salle.h"
#include "login.h"
#include <QMainWindow>
#include <QMouseEvent>
#include <QWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateNameAndSurnameLabels(int userId);

private slots:
    void on_pushButton_ajouter_2_clicked();
    void on_pushButton_supprimer_2_clicked();
    void on_tableView_clicked(const QModelIndex &index);
    void on_pushButton_modifier_2_clicked();
    void on_tri_2_clicked();
    void on_add_2_2_clicked();
    void on_recherche_textChanged(const QString &text);
    void createChart();
    void on_deconnexion_2_clicked();
    void on_tableView_2_clicked(const QModelIndex &index);
    void searchByReference(const QString &reference);
    void on_pushButton_trie_clicked();
    void on_pushButton_export_clicked();
    void createChart2();
    void on_help_clicked();
    void on_addToFavoritesButton_clicked();
    bool addToFavorites(const QString& reference);
    void saveFavoritesToFile(const QString& filePath);
    void on_textToSpeech_clicked();
    void on_close_clicked();
    void on_employes_clicked();
    void on_equipements_clicked();
    void on_patients_clicked();
    void on_rendezvous_clicked();
    void on_salles_clicked();
    void on_therapies_clicked();
    void on_pushButton_ajouter_6_clicked();
    void on_pushButton_supprimer_7_clicked();
    void on_pushButton_modifier_6_clicked();

    //Arduino
    void addPerson(const QByteArray &data);

signals:
    void windowShown();
    void dataReceived(const QByteArray &data);
    void dataSent(const QByteArray &data);

private:
    bool ascending;
    Ui::MainWindow *ui;
    Employe Etmp;
    QTimer *inactivityTimer;
    login loginPage;

    //equipements
    QVector<QString> favorites;
    QSqlQueryModel *equipementModel;
    void setupModel();

    //Arduino
    QByteArray data;
    int numPeople;
    void readDataFromSerialPort();
    void writeDataFromSerialPort();
    Salle S;
};

#endif // MAINWINDOW_H
