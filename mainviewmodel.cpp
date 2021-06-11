#include "mainviewmodel.h"

MainViewModel::MainViewModel()
{
    m_dataBase = QSharedPointer<DataBaseViewModel>::create();
}

DataBaseViewModel* MainViewModel::dataBaseViewModel()
{
    return m_dataBase.data();
}

QString MainViewModel::hello()
{
    return "Hello";
}
