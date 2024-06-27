#include "loginpage.h"
#include "ui_loginpage.h"
#include "mainpage.h"
#include "mainwindow.h"
#include <QMessageBox>
loginpage::loginpage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::loginpage)
{
    ui->setupUi(this);

}

loginpage::~loginpage()
{
    delete ui;
}

void decrypt_security(char *encp){
    while(*encp){
        (*encp)-=2;
        encp++;
    }
}

void loginpage::on_button_login_clicked()
{
    QString username = ui->text_username->text();
    QString password = ui->text_password->text();
    char security[10] = "cfokp";
    decrypt_security(security);
    QString encrypted(security);
    if(username == encrypted && password == encrypted){
        this->hide();
        mainpage *page = new mainpage();
        page->showMaximized();
    }
    else{
        QMessageBox error;
        error.setText("Invalid username or password.\n\nLogin Failed!!");
        error.setWindowTitle("Log In");
        error.setIcon(QMessageBox::Warning);
        error.setStyleSheet("background-color: rgb(255,255,255);color: rgb(0,0,0);");
        error.exec();
    }
}


void loginpage::on_button_show_clicked()
{
    if(ui->text_password-> echoMode() == QLineEdit::Normal) {
        ui->button_show->setText("Show");
        ui->text_password->setEchoMode(QLineEdit::Password);
    }
    else{
        ui->button_show->setText("Hide");
        ui->text_password->setEchoMode(QLineEdit::Normal);
    }
}


void loginpage::on_pushButton_clicked()
{
    this->hide();
    MainWindow *mai = new MainWindow();
    mai ->showMaximized();
}

