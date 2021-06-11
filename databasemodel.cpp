#include "databasemodel.h"

#include <QDebug>
#include <QSqlError>

DataBaseModel::DataBaseModel()
{
    m_database = QSqlDatabase::addDatabase("QPSQL");
    m_tableModel = QSharedPointer<QSqlQueryModel>::create();
//    m_database.setDatabaseName("qt_db");
//    m_database.setUserName("postgres");
//    m_database.setPassword("root");

//    if (!m_database.open()) {
//        qWarning() << "Can not connect to the DB";
//    } else {
//        qDebug() << "Successfully connect to the " << m_database.databaseName();
//    }

//    QSqlQuery query(m_database);
//    query.exec("SELECT table_name \
//                FROM information_schema.tables \
//                WHERE table_schema='public' \
//                AND table_type='BASE TABLE';");
//    while (query.next()) {
//        QString name = query.value(0).toString();
//        qDebug() << "TableName " << name;
//        m_tableNames << name;
//    }

//    m_currentTable = m_tableNames.at(0);

//    m_tableModel = QSharedPointer<QSqlQueryModel>::create();
//    m_tableModel->setQuery("SELECT * FROM " + m_currentTable, m_database);

//    qDebug() << "Table: " << m_currentTable << "Colums: " << m_tableModel->columnCount() << " Rows: " << m_tableModel->rowCount();

//    query.exec("SELECT datname \
//                FROM pg_database;");
//    while (query.next()) {
//        QString db_name = query.value(0).toString();
//        m_databases << db_name;
//    }

//    query.exec("SELECT column_name \
//                FROM information_schema.columns \
//                WHERE table_name='" + m_currentTable + "';");
//    while (query.next()) {
//        QString header = query.value(0).toString();
//        m_headers << header;
//    }

//    QSqlQuery query(m_database);
//    query.exec("CREATE DATABASE QT_DB;");

//    m_database.close();
//    m_database.setDatabaseName("qt_db");

//    if (!m_database.open()) {
//        qWarning() << "Can not connect to the DB";
//    } else {
//        qDebug() << "Successfully connect to the " << m_database.databaseName();
//    }

}

bool DataBaseModel::login(const QString &username, const QString &pass)
{
    m_database.setDatabaseName("postgres");
    m_database.setUserName(username);
    m_database.setPassword(pass);

    if (!m_database.open()) {
        qWarning() << "Can not connect to the DB";
        return false;
    } else {
        qDebug() << "Successfully connect to the " << m_database.databaseName();
    }

    QSqlQuery query(m_database);
    query.exec("SELECT table_name \
                FROM information_schema.tables \
                WHERE table_schema='public' \
                AND table_type='BASE TABLE';");
    while (query.next()) {
        QString name = query.value(0).toString();
        qDebug() << "TableName " << name;
        m_tableNames << name;
    }

    m_currentTable = m_tableNames.at(0);

    m_tableModel = QSharedPointer<QSqlQueryModel>::create();
    m_tableModel->setQuery("SELECT * FROM " + m_currentTable, m_database);

    query.exec("SELECT datname \
                FROM pg_database;");
    while (query.next()) {
        QString db_name = query.value(0).toString();
        m_databases << db_name;
    }

    query.exec("SELECT column_name \
                FROM information_schema.columns \
                WHERE table_name='" + m_currentTable + "';");
    while (query.next()) {
        QString header = query.value(0).toString();
        m_headers << header;
    }

    return true;
}

bool DataBaseModel::setTable(const QString& tableName)
{
    if (!m_tableNames.contains(tableName))
        return false;

    m_currentTable = tableName;
    m_tableModel->setQuery("SELECT * FROM " + m_currentTable, m_database);

    m_headers.clear();
    QSqlQuery query(m_database);
    query.exec("SELECT column_name \
                FROM information_schema.columns \
                WHERE table_name='" + m_currentTable + "';");
    while (query.next()) {
        QString header = query.value(0).toString();
        m_headers << header;
    }

    return true;
}

bool DataBaseModel::setDatabase(const QString &dbName)
{
    if (!m_databases.contains(dbName))
        return false;

    m_database.close();
    m_database.setDatabaseName(dbName);

    if (!m_database.open()) {
        qWarning() << "Can not connect to the DB";
        return false;
    } else {
        qDebug() << "Successfully connect to the " << m_database.databaseName();
    }

    m_tableNames.clear();

    QSqlQuery query(m_database);
    query.exec("SELECT table_name \
                FROM information_schema.tables \
                WHERE table_schema='public' \
                AND table_type='BASE TABLE';");
    while (query.next()) {
        QString name = query.value(0).toString();
        qDebug() << "TableName " << name;
        m_tableNames << name;
    }

    if (!m_tableNames.empty())
        setTable(m_tableNames.at(0));
    return true;
}

void DataBaseModel::createDatabase(const QString &name)
{
    QSqlQuery query(m_database);
    query.exec("CREATE DATABASE " + name + ";");

    if (!m_database.open()) {
        qWarning() << "Can not connect to the DB";
    } else {
        qDebug() << "Successfully connect to the " << m_database.databaseName();
    }
}

bool DataBaseModel::addEmptyRow()
{
    QSqlQuery query(m_database);
    query.exec("INSERT INTO " + m_currentTable + " DEFAULT VALUES;");
    if (query.lastError().type() == QSqlError::NoError)
        return true;
    return false;
}

bool DataBaseModel::changeCell(int row, int column, const QString& val)
{
    QString q;
    q += "UPDATE " + m_currentTable + " SET " + m_headers.at(column) + " = '" + val + "' WHERE ";
    int i = 0;
    bool isFirst = true;
    for (auto h : m_headers) {
        if (m_tableModel->data(m_tableModel->index(row, i)).toString() != "") {
            if (!isFirst)
                q += "' AND ";
            q += h + " = '" + m_tableModel->data(m_tableModel->index(row, i)).toString();
            isFirst = false;
        }
        ++i;
    }

    q += "';";

    qDebug() << "Query: " << q;

    QSqlQuery query(m_database);
    query.exec(q);
    if (query.lastError().type() == QSqlError::NoError)
        return true;
    return false;

}

void DataBaseModel::find(int headerID, const QString &val)
{
    updateTable();
    m_tableModel->setQuery("SELECT * FROM " + m_currentTable + " WHERE " + m_headers.at(headerID) + " = '" + val + "';" , m_database);
}

void DataBaseModel::remove(int headerID, const QString &val)
{
    QSqlQuery query(m_database);
    query.exec("DELETE FROM " + m_currentTable + " WHERE " + m_headers.at(headerID) + " = '" + val + "';");
    updateTable();
}

void DataBaseModel::removeRow(int row)
{
    QString q;
    q += "DELETE FROM " + m_currentTable + " WHERE ";
    int i = 0;
    bool isFirst = true;
    for (auto h : m_headers) {
        if (m_tableModel->data(m_tableModel->index(row, i)).toString() != "") {
            if (!isFirst)
                q += "' AND ";
            q += h + " = '" + m_tableModel->data(m_tableModel->index(row, i)).toString();
            isFirst = false;
        }
        ++i;
    }

    q += "';";

    qDebug() << "Query: " << q;

    QSqlQuery query(m_database);
    query.exec(q);
}

void DataBaseModel::clearTable()
{
    QSqlQuery query(m_database);
    query.exec("DELETE FROM " + m_currentTable + ";");
    updateTable();
}

void DataBaseModel::updateTable()
{
    setTable(m_currentTable);
}

QSharedPointer<QSqlQueryModel> DataBaseModel::model()
{
    return m_tableModel;
}

QStringList DataBaseModel::headers()
{
    return m_headers;
}

QStringList DataBaseModel::tableNames()
{
    return m_tableNames;
}

QStringList DataBaseModel::databaseNames()
{
    return m_databases;
}

void DataBaseModel::test()
{
    QModelIndex t = m_tableModel->index(0, 1);
    qDebug() << m_tableModel->data(t);
}
