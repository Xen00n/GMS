#ifndef VIEW_PAGE_H
#define VIEW_PAGE_H

#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>
#include <QIntValidator>
#include <custom.h>

namespace Ui {
class view_page;
}

class view_page : public QMainWindow
{
    Q_OBJECT

public:
    explicit view_page(_field selected_field, QSqlDatabase *_DB,QWidget *parent = nullptr);
    ~view_page();

private slots:
    void on_button_refresh_clicked();

private:
    Ui::view_page *ui;
    QSqlDatabase DB;
};

#endif // VIEW_PAGE_H
