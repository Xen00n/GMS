#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QMainWindow>

namespace Ui {
class mainpage;
}

class mainpage : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainpage(QWidget *parent = nullptr);
    ~mainpage();


private slots:
    void on_button_book_toggled(bool checked);

    void on_button_cancel_toggled(bool checked);

    void on_button_view_toggled(bool checked);

    void on_button_logout_clicked();

private:
    Ui::mainpage *ui;
};

#endif // MAINPAGE_H
