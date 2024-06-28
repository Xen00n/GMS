#ifndef CANCEL_PAGE_H
#define CANCEL_PAGE_H

#include <QMainWindow>
#include <custom.h>


namespace Ui {
class cancel_page;
}

class cancel_page : public QMainWindow
{
    Q_OBJECT

public:
    explicit cancel_page(_field selected_field,QWidget *parent = nullptr);
    ~cancel_page();

private:
    Ui::cancel_page *ui;
};

#endif // CANCEL_PAGE_H
