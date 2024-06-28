#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QMainWindow>
#include "customization.h"
namespace Ui {
class mainpage;
}

class mainpage : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainpage(QWidget *parent = nullptr);
    ~mainpage();
    static void book_window(_field field);
    static void cancel_window(_field field);
    static void view_window(_field field);


private slots:
    void on_button_book_toggled(bool checked);

    void on_button_cancel_toggled(bool checked);

    void on_button_view_toggled(bool checked);

    void on_button_logout_clicked();

    void on_button_football_clicked();

    void on_button_basketball_clicked();

    void on_button_indoor_clicked();

    void on_button_volleyball_clicked();

private:
    Ui::mainpage *ui;
};


#endif // MAINPAGE_H
