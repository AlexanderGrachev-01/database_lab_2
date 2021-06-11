#include "databaseviewmodel.h"

#include <QtSql/QSqlDatabase>

DataBaseViewModel::DataBaseViewModel()
{
    m_dataBaseModel = QSharedPointer<DataBaseModel>::create();
}

bool DataBaseViewModel::login(const QString &username, const QString &pass)
{
    return m_dataBaseModel->login(username, pass);
}

void DataBaseViewModel::createDatabase(const QString &name)
{
    m_dataBaseModel->createDatabase(name);
}

QObject* DataBaseViewModel::table() const
{
    return m_dataBaseModel->model().data();
}

void DataBaseViewModel::setTable(const QString &tableName)
{
    m_dataBaseModel->setTable(tableName);
    emit tableChanged();
    emit headersChanged();
}

void DataBaseViewModel::setDatabase(const QString &dbName)
{
    m_dataBaseModel->setDatabase(dbName);
    emit tableChanged();
    emit databaseChanged();
    emit headersChanged();
}

QStringList DataBaseViewModel::headers() const
{
    return m_dataBaseModel->headers();
}

QStringList DataBaseViewModel::tableNames() const
{
    return m_dataBaseModel->tableNames();
}

QStringList DataBaseViewModel::databaseNames() const
{
    return m_dataBaseModel->databaseNames();
}

bool DataBaseViewModel::addEmptyRow()
{
    bool ret = m_dataBaseModel->addEmptyRow();
    emit tableChanged();
    return ret;
}

bool DataBaseViewModel::changeCell(int row, int column, const QString &val)
{
    bool ret = m_dataBaseModel->changeCell(row, column, val);
    emit tableChanged();
    return ret;
}

void DataBaseViewModel::find(int headerId, const QString &val)
{
    m_dataBaseModel->find(headerId, val);
}

void DataBaseViewModel::remove(int headerId, const QString &val)
{
    m_dataBaseModel->remove(headerId, val);
}

void DataBaseViewModel::removeRow(int row)
{
    m_dataBaseModel->removeRow(row);
}

void DataBaseViewModel::addColumn(const QString &name, const QString &type, const QString &flags)
{
    m_dataBaseModel->addColumn(name, type, flags);
}

void DataBaseViewModel::clearTable()
{
    m_dataBaseModel->clearTable();
}

void DataBaseViewModel::updateTable()
{
    m_dataBaseModel->updateTable();
}

void DataBaseViewModel::test()
{
    m_dataBaseModel->test();
}
