#include "mainpage.h"
#include "ui_mainpage.h"
#include "loginpage.h"

mainpage::mainpage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainpage)
{
    ui->setupUi(this);
    ui->button_book->setCheckable(true);
    ui->button_cancel->setCheckable(true);
    ui->button_view->setCheckable(true);
    ui->button_book->setChecked(true);
}

mainpage::~mainpage()
{
    delete ui;
}


void mainpage::on_button_book_toggled(bool checked)
{
    if(checked){
        ui->button_view->setChecked(false);
        ui->button_cancel->setChecked(false);
    }
    else if(!checked && ui->button_cancel->isChecked() == false && ui->button_view->isChecked() == false){
        ui->button_book->setChecked(true);
    }
}


void mainpage::on_button_cancel_toggled(bool checked)
{
    if(checked){
        ui->button_view->setChecked(false);
        ui->button_book->setChecked(false);
    }
    else if(!checked && ui->button_book->isChecked() == false && ui->button_view->isChecked() == false){
        ui->button_cancel->setChecked(true);
    }
}

void mainpage::on_button_view_toggled(bool checked)
{
    if(checked){
        ui->button_cancel->setChecked(false);
        ui->button_book->setChecked(false);
    }
    else if(!checked && ui->button_cancel->isChecked() == false && ui->button_book->isChecked() == false){
        ui->button_view->setChecked(true);
    }
}


void mainpage::on_button_logout_clicked()
{
    loginpage *l = new loginpage();
    this->hide();
    l->showMaximized();
}
