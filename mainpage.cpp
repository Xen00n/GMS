#include "mainpage.h"
#include "ui_mainpage.h"
#include "loginpage.h"
#include "booking_page.h"
#include "cancel_page.h"
#include "view_page.h"
#include "custom.h"

QSqlDatabase _DB;

mainpage::mainpage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainpage)
{
    ui->setupUi(this);
    ui->button_book->setCheckable(true);
    ui->button_cancel->setCheckable(true);
    ui->button_view->setCheckable(true);
    ui->button_book->setChecked(true);
    QString path_to_database = QString(PROJECT_DIR) + "/database/database.db";
    _DB = QSqlDatabase::addDatabase("QSQLITE");
    _DB.setDatabaseName(path_to_database);

    if (_DB.open())
    {
        qDebug() << "Database connected.";
    }
    else
    {
        qDebug() << "Database not connected.";
        qDebug() << "Error: " << _DB.lastError();
        QMessageBox::information(this, "Database error", "Could not connect to database");
        QCoreApplication::quit();
    }

    // Creating table if not exists
    QSqlQuery query(_DB);
    query.prepare("CREATE TABLE IF NOT EXISTS bookings (booking_number INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, faculty TEXT, batch TEXT, start_date INTEGER, end_date INTEGER, field TEXT)");
    if (!query.exec())
    {
        qDebug() << "Error creating table" << query.lastError().text();
    }
}

enum _option{
    book,
    cancel,
    view
};

enum _option option = book;

void option_selector(_field field){
    if(option == book){
        booking_page *l = new booking_page(field,&_DB);
        l->showMaximized();
    }
    else if(option == cancel){
        cancel_page *l = new cancel_page(field,&_DB);
        l->showMaximized();
    }
    else{
        view_page *l = new view_page(field,&_DB);
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
    option_selector(football);
}


void mainpage::on_button_basketball_clicked()
{
    option_selector(basketball);
}

void mainpage::on_button_volleyball_clicked()
{
    option_selector(volleyball);
}

void mainpage::on_button_indoor_clicked()
{
    option_selector(indoor);
}
