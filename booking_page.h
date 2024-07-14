#ifndef BOOKING_PAGE_H
#define BOOKING_PAGE_H

#include <QMainWindow>
#include <QDebug>
#include <QtSql>
#include <QMessageBox>
#include <QIntValidator>
#include <custom.h>

namespace Ui {
class booking_page;
}

class booking_page : public QMainWindow
{
    Q_OBJECT

public:
    explicit booking_page(_field selected_field,QWidget *parent = nullptr);
    ~booking_page();
private slots:
    void on_button_book_clicked();

    void on_button_clear_clicked();

private:
    Ui::booking_page *ui;
    QSqlDatabase DB;
};


#endif // BOOKING_PAGE_H
