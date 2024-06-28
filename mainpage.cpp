#include "mainpage.h"
#include "ui_mainpage.h"
#include "loginpage.h"
#include "customization.h"
#include "booking_page.h"
#include "cancel_page.h"
#include "view_page.h"

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


enum _option option = book;

void option_selector(){
    if(option == book){
        booking_page *l = new booking_page();
        l->showMaximized();
    }
    else if(option == cancel){
        cancel_page *l = new cancel_page();
        l->showMaximized();
    }
    else{
        view_page *l = new view_page();
        l->showMaximized();
    }
}

mainpage::~mainpage()
{
    delete ui;
}


void mainpage::on_button_book_toggled(bool checked)
{
    if(checked){
        option = book;
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
        option = cancel;
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
        option = view;
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


void mainpage::on_button_football_clicked()
{
    option_selector();
}


void mainpage::on_button_basketball_clicked()
{
    option_selector();
}


void mainpage::on_button_indoor_clicked()
{
    option_selector();
}


void mainpage::on_button_volleyball_clicked()
{
    option_selector();
}

