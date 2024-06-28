#include "cancel_page.h"
#include "ui_cancel_page.h"


_field input_field_2;

cancel_page::cancel_page(_field selected_field,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::cancel_page)
{
    ui->setupUi(this);
    input_field_2 = selected_field;

}

cancel_page::~cancel_page()
{
    delete ui;
}
