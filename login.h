#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    int getId() const;

signals:
    void loginSuccessful();

private slots:
    void on_loginButton_clicked();

    void on_resetButton_clicked();

private:
    Ui::login *ui;
    bool validateCredentials(const QString& username, const QString& password);
    int getUserId(const QString&, const QString&);
    int userId;
    void populateQuestionComboBox();
};

#endif // LOGIN_H
