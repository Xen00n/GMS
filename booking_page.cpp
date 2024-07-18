#include "booking_page.h"
#include "ui_booking_page.h"


_field input_field;


booking_page::booking_page(_field selected_field, QSqlDatabase *_DB, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::booking_page)
{
    ui->setupUi(this);
    input_field = selected_field;
    DB = *_DB;
    ui->date_from->setDate(QDate::currentDate());
    ui->date_to->setDate(QDate::currentDate());
}



booking_page::~booking_page()
{
    // Close the database connection and remove it
    DB.close();
    QSqlDatabase::removeDatabase(QString(PROJECT_DIR) + "/database/database.db");
    delete ui;
}

void booking_page::on_button_book_clicked()
{
    QString name = ui->text_name->text();
    QString faculty = ui->text_faculty->text();
    QString batch = ui->text_batch->text();
    int _date_from = date_to_int(ui->date_from->text());
    int _date_to = date_to_int(ui->date_to->text());

    if (faculty.isEmpty() || name.isEmpty() || (_date_to < _date_from))
    {
        QMessageBox::information(this, "Field error", "Please fill all fields properly with correct information!");
        return;
    }

    QSqlQuery query(DB);
    query.prepare(R"(SELECT COUNT(*) FROM bookings WHERE field = :field AND start_date <= :end_date AND end_date >= :start_date)");
    query.bindValue(":field", enum_to_string(input_field));
    query.bindValue(":start_date", _date_from);
    query.bindValue(":end_date", _date_to);
    if (!query.exec())
    {
        qDebug() << "Error checking for overlapping bookings:" << query.lastError().text();
        QMessageBox::information(this, "Database error", "Error checking for overlapping bookings");
        return;
    }

    query.next();
    int count = query.value(0).toInt();
    if (count > 0)
    {
        QMessageBox::information(this, "Booking error", "Required field is already booked for given range of date");
        ui->date_from->setDate(QDate::currentDate());
        ui->date_to->setDate(QDate::currentDate());
        return;
    }

    // Insert the new booking
    query.prepare("INSERT INTO bookings (name, faculty, batch, start_date, end_date, field) VALUES (:name, :faculty, :batch, :start_date, :end_date, :field)");
    query.bindValue(":name", name);
    query.bindValue(":faculty", faculty);
    query.bindValue(":batch", batch);
    query.bindValue(":start_date", _date_from);
    query.bindValue(":end_date", _date_to);
    query.bindValue(":field", enum_to_string(input_field));

    if (!query.exec())
    {
        qDebug() << "Error inserting booking:" << query.lastError().text();
        QMessageBox::information(this, "Database error", "Error inserting data");
    }
    else
    {
        qDebug() << "Booking inserted successfully.";
        QMessageBox::information(this, "Booking", "Successfully Booked");
        on_button_clear_clicked();
    }
}

void booking_page::on_button_clear_clicked()
{
    ui->text_name->setText("");
    ui->text_faculty->setText("");
    ui->text_batch->setText("");
    ui->date_from->setDate(QDate::currentDate());
    ui->date_to->setDate(QDate::currentDate());
}



