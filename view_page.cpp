#include "view_page.h"
#include "ui_view_page.h"

view_page::view_page(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::view_page)
{
    ui->setupUi(this);
}

view_page::~view_page()
{
    delete ui;
}
