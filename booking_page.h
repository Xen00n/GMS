#ifndef BOOKING_PAGE_H
#define BOOKING_PAGE_H

#include <QMainWindow>


namespace Ui {
class booking_page;
}

class booking_page : public QMainWindow
{
    Q_OBJECT

public:
    explicit booking_page(QWidget *parent = nullptr);
    ~booking_page();

private:
    Ui::booking_page *ui;
};


#endif // BOOKING_PAGE_H
