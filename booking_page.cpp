#include "booking_page.h"
#include "ui_booking_page.h"

_field input_field_1;

booking_page::booking_page(_field selected_field, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::booking_page)
{
    ui->setupUi(this);
    input_field_1 = selected_field;
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

    // Creating table if not exists
    QSqlQuery query(DB);
    query.prepare("CREATE TABLE IF NOT EXISTS bookings (booking_number INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, faculty TEXT, batch TEXT, start_date INTEGER, end_date INTEGER, field TEXT)");
    if (!query.exec())
    {
        qDebug() << "Error creating table" << query.lastError().text();
    }
}

QString enum_to_string(_field _enum)
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
int date_to_int(QString date)
{
    QString day = date.mid(0, 2);
    QString month = date.mid(3, 2);
    QString year = date.mid(6, 4);
    int dateInt = year.toInt() * 10000 + month.toInt() * 100 + day.toInt();
    return dateInt;
}
booking_page::~booking_page()
{
    // Close the database connection and remove it
    QString connectionName = DB.connectionName();
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
    query.bindValue(":field", enum_to_string(input_field_1));
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
    query.bindValue(":field", enum_to_string(input_field_1));

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
