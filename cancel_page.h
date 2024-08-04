#ifndef CANCEL_PAGE_H
#define CANCEL_PAGE_H

#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>
#include <QIntValidator>
#include <custom.h>

namespace Ui {
class cancel_page;
}

class cancel_page : public QMainWindow
{
    Q_OBJECT

public:
    explicit cancel_page(_field selected_field, QSqlDatabase *_DB, QWidget *parent = nullptr);
    ~cancel_page();
    void loadAllBookings();
    void loadBookingsWithinRange(int _start_date, int _end_date);
    bool dateRangeModified;

private slots:
    void on_refresh_button_clicked();
    void on_cancel_button_clicked();
    void on_date_changed(); // Slot for handling date change

private:
    Ui::cancel_page *ui;
    QSqlDatabase DB;
};

#endif // CANCEL_PAGE_H
