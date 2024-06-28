#include "booking_page.h"
#include "ui_booking_page.h"


booking_page::booking_page(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::booking_page)
{
    ui->setupUi(this);
}

booking_page::~booking_page()
{
    delete ui;
}
