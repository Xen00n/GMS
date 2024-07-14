#include "cancel_page.h"
#include "ui_cancel_page.h"

#include <QString>
#include <QDate>

_field input_field_2;

QString enum_to_string_2(_field _enum)
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

int date_to_int_2(QString date)
{
    QString day = date.mid(0, 2);
    QString month = date.mid(3, 2);
    QString year = date.mid(6, 4);
    int dateInt = year.toInt() * 10000 + month.toInt() * 100 + day.toInt();
    return dateInt;
}

QString int_to_date_2(const QVariant &dateVariant)
{
    int dateInt = dateVariant.toInt();
    int year = dateInt / 10000;
    int month = (dateInt % 10000) / 100;
    int day = dateInt % 100;
    QDate date(year, month, day);
    return date.toString("yyyy-MM-dd");
}

void cancel_page::loadAllBookings()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM bookings WHERE field = :field");
    query.bindValue(":field", enum_to_string_2(input_field_2));
    ui->tableWidget->verticalHeader()->setVisible(false);

    if (query.exec()) {
        int RowNumber = 0;
        while (query.next())
        {
            ui->tableWidget->insertRow(RowNumber);
            ui->tableWidget->setRowHeight(RowNumber, 40);
            ui->tableWidget->setItem(RowNumber, 0, new QTableWidgetItem(query.value("booking_number").toString()));
            ui->tableWidget->setItem(RowNumber, 1, new QTableWidgetItem(query.value("name").toString()));
            ui->tableWidget->setItem(RowNumber, 2, new QTableWidgetItem(query.value("faculty").toString()));
            ui->tableWidget->setItem(RowNumber, 3, new QTableWidgetItem(query.value("batch").toString()));
            ui->tableWidget->setItem(RowNumber, 4, new QTableWidgetItem(int_to_date_2(query.value("start_date"))));
            ui->tableWidget->setItem(RowNumber, 5, new QTableWidgetItem(int_to_date_2(query.value("end_date"))));
            RowNumber++;
        }
    } else {
        qDebug() << "Data loading to table error:" << query.lastError().text();
    }
}

void cancel_page::loadBookingsWithinRange(int startDate, int endDate)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM bookings WHERE field = :field AND ((start_date >= :start_date AND start_date <= :end_date) OR (end_date >= :start_date AND end_date <= :end_date))");
    query.bindValue(":field", enum_to_string_2(input_field_2));
    query.bindValue(":start_date", startDate);
    query.bindValue(":end_date", endDate);

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->verticalHeader()->setVisible(false);

    if (query.exec()) {
        int RowNumber = 0;
        while (query.next()) {
            ui->tableWidget->insertRow(RowNumber);
            ui->tableWidget->setRowHeight(RowNumber, 40);
            ui->tableWidget->setItem(RowNumber, 0, new QTableWidgetItem(query.value("booking_number").toString()));
            ui->tableWidget->setItem(RowNumber, 1, new QTableWidgetItem(query.value("name").toString()));
            ui->tableWidget->setItem(RowNumber, 2, new QTableWidgetItem(query.value("faculty").toString()));
            ui->tableWidget->setItem(RowNumber, 3, new QTableWidgetItem(query.value("batch").toString()));
            ui->tableWidget->setItem(RowNumber, 4, new QTableWidgetItem(int_to_date_2(query.value("start_date").toInt())));
            ui->tableWidget->setItem(RowNumber, 5, new QTableWidgetItem(int_to_date_2(query.value("end_date").toInt())));
            RowNumber++;
        }
    } else {
        qDebug() << "Data loading to table error:" << query.lastError().text();
    }
}

cancel_page::cancel_page(_field selected_field, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::cancel_page)
{
    ui->setupUi(this);
    input_field_2 = selected_field;
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

    loadAllBookings();
}

cancel_page::~cancel_page()
{
    delete ui;
}


void cancel_page::on_refresh_button_clicked()
{
    int _start_date = date_to_int_2(ui->date_from->text());
    int _end_date = date_to_int_2(ui->date_to->text());
    loadBookingsWithinRange(_start_date, _end_date);
}


void cancel_page::on_cancel_button_clicked()
{
    QString booking_number = ui->booking_number->text();

    if (booking_number.isEmpty()) {
        QMessageBox::information(this, "Input Error", "Please enter a booking number.");
        return;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM bookings WHERE booking_number = :booking_number");
    query.bindValue(":booking_number", booking_number);

    if (query.exec()) {
        if (query.numRowsAffected() > 0) {
            QMessageBox::information(this, "Success", "Booking canceled successfully.");
            ui->booking_number->clear();
        } else {
            QMessageBox::information(this, "Error", "No booking found with the provided booking number.");
        }
    } else {
        qDebug() << "Error canceling booking: " << query.lastError().text();
        QMessageBox::information(this, "Database Error", "Could not cancel the booking.");
    }
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    if (ui->date_from->date() != QDate::currentDate() || ui->date_to->date() != QDate::currentDate()) {
        int _start_date = date_to_int_2(ui->date_from->text());
        int _end_date = date_to_int_2(ui->date_to->text());
        loadBookingsWithinRange(_start_date, _end_date);
    } else {
        loadAllBookings();
    }
}
