#pragma once

#include <QObject>
#include <QSharedPointer>

#include <databaseviewmodel.h>


class MainViewModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(DataBaseViewModel* dataBaseViewModel READ dataBaseViewModel CONSTANT)
public:
    MainViewModel();

    DataBaseViewModel* dataBaseViewModel();
    Q_INVOKABLE QString hello();
private:
    QSharedPointer<DataBaseViewModel> m_dataBase;
};

