#include "view_page.h"
#include "ui_view_page.h"

#include <QString>
#include <QDate>

_field input_field_3;

QString enum_to_string_3(_field _enum)
{
    switch (_enum)
    {
    case football:
        return "football";
    case basketball:
        return "basketball";
    case volleyball:
        return "volleyball";
    case indoor:
        return "indoor";
    default:
        return "";
    }
}

int date_to_int_3(QString date)
{
    QString day = date.mid(0, 2);
    QString month = date.mid(3, 2);
    QString year = date.mid(6, 4);
    int dateInt = year.toInt() * 10000 + month.toInt() * 100 + day.toInt();
    return dateInt;
}
QString int_to_date_3(const QVariant &dateVariant)
{
    int dateInt = dateVariant.toInt();
    int year = dateInt / 10000;
int month = (dateInt % 10000) / 100;
int day = dateInt % 100;
QDate date(year, month, day);
return date.toString("yyyy-MM-dd");
}
view_page::view_page(_field selected_field,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::view_page)
{
    ui->setupUi(this);
    input_field_3 = selected_field;
    ui->date_from->setDate(QDate::currentDate());
    ui->date_to->setDate(QDate::currentDate());
    QString path_to_database = QString(PROJECT_DIR) + "/database/database.db";
    DB = QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName(path_to_database);

    if (DB.open())
    {
        qDebug() << "Database connected.";
    }
    else
    {
        qDebug() << "Database not connected.";
        qDebug() << "Error: " << DB.lastError();
        QMessageBox::information(this, "Database error", "Could not connect to database");
        QCoreApplication::quit();
    }
    QSqlQuery query;
    query.prepare("SELECT * FROM bookings WHERE field = :field");
    query.bindValue(":field",enum_to_string_3(input_field_3));
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
            ui->tableWidget->setItem(RowNumber, 4, new QTableWidgetItem(QString(int_to_date_3(query.value("start_date")))));
            ui->tableWidget->setItem(RowNumber, 5, new QTableWidgetItem(QString(int_to_date_3(query.value("end_date")))));
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
    int _start_date = date_to_int_3(ui->date_from->text());
    int _end_date = date_to_int_3(ui->date_to->text());
    QSqlQuery query;
    query.prepare("SELECT * FROM bookings WHERE field = :field AND ((start_date>:start_date AND start_date<:end_date) OR (end_date>:start_date AND end_date<:end_date))");
    query.bindValue(":field",enum_to_string_3(input_field_3));
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
            ui->tableWidget->setItem(RowNumber, 4, new QTableWidgetItem(QString(int_to_date_3(query.value("start_date")))));
            ui->tableWidget->setItem(RowNumber, 5, new QTableWidgetItem(QString(int_to_date_3(query.value("end_date")))));
            RowNumber++;
        }
    } else {
        qDebug() << "Data loading to table error.";
    }
}

