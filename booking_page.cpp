#include "booking_page.h"
#include "ui_booking_page.h"

_field input_field_1;

booking_page::booking_page(_field selected_field,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::booking_page)
{
    ui->setupUi(this);
    input_field_1 = selected_field;
    QString path_to_database = QString(PROJECT_DIR) +"/database/database.db";
    DB = QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName(path_to_database);

    if(DB.open()) {
        qDebug() << "Database connected.";
    }
    else {
        qDebug() << "Database not connected.";
        qDebug() << "Error: " << DB.lastError();
        QMessageBox::information(this,"Database error","Couldnot connect database");
        QCoreApplication::quit();
    }
}

booking_page::~booking_page()
{
    delete ui;
}

void booking_page::on_button_book_clicked()
{
    QString name = ui->text_name->text();
    QString batch = ui->text_faculty->text();
    if(batch.isEmpty() || name.isEmpty()){
        QMessageBox::information(this,"Empty Field","PLease fill all the field in order to proced!");
    }
}

