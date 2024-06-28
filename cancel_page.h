#ifndef CANCEL_PAGE_H
#define CANCEL_PAGE_H

#include <QMainWindow>



namespace Ui {
class cancel_page;
}

class cancel_page : public QMainWindow
{
    Q_OBJECT

public:
    explicit cancel_page(QWidget *parent = nullptr);
    ~cancel_page();

private:
    Ui::cancel_page *ui;
};

#endif // CANCEL_PAGE_H
