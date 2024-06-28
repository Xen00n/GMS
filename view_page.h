#ifndef VIEW_PAGE_H
#define VIEW_PAGE_H

#include <QMainWindow>


namespace Ui {
class view_page;
}

class view_page : public QMainWindow
{
    Q_OBJECT

public:
    explicit view_page(QWidget *parent = nullptr);
    ~view_page();

private:
    Ui::view_page *ui;
};

#endif // VIEW_PAGE_H
