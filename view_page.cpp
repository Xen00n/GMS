#include "view_page.h"
#include "ui_view_page.h"

#include <QString>
#include <QDate>

_field input_field_3;

view_page::view_page(_field selected_field, QSqlDatabase *_DB,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::view_page)
{
    ui->setupUi(this);
    input_field_3 = selected_field;
    DB = *_DB;
    ui->date_from->setDate(QDate::currentDate());
    ui->date_to->setDate(QDate::currentDate());
    QSqlQuery query;
    query.prepare("SELECT * FROM bookings WHERE field = :field");
    query.bindValue(":field",enum_to_string(input_field_3));
    ui->tableWidget->verticalHeader()->setVisible(false);
    if (query.exec()) {
        int RowNumber = 0;

        while(query.next())
        {
            ui->tableWidget->insertRow(RowNumber);
            ui->tableWidget->setRowHeight(RowNumber,40);
            ui->tableWidget->setItem(RowNumber, 0, new QTableWidgetItem(QString(QString::number(RowNumber+1))));
            ui->tableWidget->setItem(RowNumber, 1, new QTableWidgetItem(QString(query.value("name").toString())));
            ui->tableWidget->setItem(RowNumber, 2, new QTableWidgetItem(QString(query.value("faculty").toString())));
            ui->tableWidget->setItem(RowNumber, 3, new QTableWidgetItem(QString(query.value("batch").toString())));
            ui->tableWidget->setItem(RowNumber, 4, new QTableWidgetItem(QString(int_to_date(query.value("start_date")))));
            ui->tableWidget->setItem(RowNumber, 5, new QTableWidgetItem(QString(int_to_date(query.value("end_date")))));
            RowNumber++;
        }
    } else {
        qDebug() << "Data loading to table error.";
    }

}

view_page::~view_page()
{
    delete ui;
}


void view_page::on_button_refresh_clicked()
{
    int _start_date = date_to_int(ui->date_from->text());
    int _end_date = date_to_int(ui->date_to->text());
    QSqlQuery query;
    query.prepare("SELECT * FROM bookings WHERE field = :field AND ((start_date>=:start_date AND start_date<=:end_date) OR (end_date>=:start_date AND end_date<=:end_date))");
    query.bindValue(":field",enum_to_string(input_field_3));
    query.bindValue(":start_date",_start_date);
    query.bindValue(":end_date",_end_date);
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->verticalHeader()->setVisible(false);
    if (query.exec()) {
        int RowNumber = 0;

        while(query.next())
        {
            ui->tableWidget->insertRow(RowNumber);
            ui->tableWidget->setRowHeight(RowNumber,40);
            ui->tableWidget->setItem(RowNumber, 0, new QTableWidgetItem(QString(QString::number(RowNumber+1))));
            ui->tableWidget->setItem(RowNumber, 1, new QTableWidgetItem(QString(query.value("name").toString())));
            ui->tableWidget->setItem(RowNumber, 2, new QTableWidgetItem(QString(query.value("faculty").toString())));
            ui->tableWidget->setItem(RowNumber, 3, new QTableWidgetItem(QString(query.value("batch").toString())));
            ui->tableWidget->setItem(RowNumber, 4, new QTableWidgetItem(QString(int_to_date(query.value("start_date")))));
            ui->tableWidget->setItem(RowNumber, 5, new QTableWidgetItem(QString(int_to_date(query.value("end_date")))));
            RowNumber++;
        }
    } else {
        qDebug() << "Data loading to table error.";
    }
}

