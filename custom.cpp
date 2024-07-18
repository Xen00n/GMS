#include <custom.h>

QString enum_to_string(_field _enum)
{
    switch (_enum)
    {
    case football:
        return "football";
    case basketball:
        return "basketball";
    case volleyball:
        return "volleyball";
    case indoor:
        return "indoor";
    default:
        return "";
    }
}

int date_to_int(QString date)
{
    QString day = date.mid(0, 2);
    QString month = date.mid(3, 2);
    QString year = date.mid(6, 4);
    int dateInt = year.toInt() * 10000 + month.toInt() * 100 + day.toInt();
    return dateInt;
}

QString int_to_date(const QVariant &dateVariant)
{
    int dateInt = dateVariant.toInt();
    int year = dateInt / 10000;
    int month = (dateInt % 10000) / 100;
    int day = dateInt % 100;
    QDate date(year, month, day);
    return date.toString("yyyy-MM-dd");
}
