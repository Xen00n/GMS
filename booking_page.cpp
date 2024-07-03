#include "booking_page.h"
#include "ui_booking_page.h"

_field input_field_1;

booking_page::booking_page(_field selected_field,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::booking_page)
{
    ui->setupUi(this);
    input_field_1 = selected_field;
}

booking_page::~booking_page()
{
    delete ui;
}

void booking_page::on_pushButton_clicked()
{
    QString name = ui->text_name->text();
    QString batch = ui->text_batch->text();
    QString department = ui->text_department->text();
    QDate _date = ui->dateEdit->date();
}

