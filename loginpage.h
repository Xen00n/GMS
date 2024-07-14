#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QMainWindow>

namespace Ui {
class loginpage;
}

class loginpage : public QMainWindow
{
    Q_OBJECT

public:
    explicit loginpage(QWidget *parent = nullptr);
    ~loginpage();

private slots:
    void on_button_login_clicked();

    void on_button_show_clicked();

    void on_logo_clicked();

private:
    Ui::loginpage *ui;
    QMainWindow *mainWindow;

};

#endif // LOGINPAGE_H
