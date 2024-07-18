#ifndef CUSTOM_H
#define CUSTOM_H

#include <QtSql>
#include <QMessageBox>
#include <QIntValidator>
#include <QDebug>



typedef enum __field{
    football,
    basketball,
    volleyball,
    indoor
}_field;

QString enum_to_string(_field _enum);
int date_to_int(QString date);
QString int_to_date(const QVariant &dateVariant);

#endif // CUSTOM_H
