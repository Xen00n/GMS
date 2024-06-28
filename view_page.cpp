#include "view_page.h"
#include "ui_view_page.h"

_field input_field_3;

view_page::view_page(_field selected_field,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::view_page)
{
    ui->setupUi(this);
    input_field_3 = selected_field;
}

view_page::~view_page()
{
    delete ui;
}

