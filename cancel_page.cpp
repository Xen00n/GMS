#include "cancel_page.h"
#include "ui_cancel_page.h"

cancel_page::cancel_page(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::cancel_page)
{
    ui->setupUi(this);
}

cancel_page::~cancel_page()
{
    delete ui;
}
