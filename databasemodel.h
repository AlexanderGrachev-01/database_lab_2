#pragma once

#include <QObject>
#include <QSharedPointer>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlQueryModel>

class DataBaseModel : public QObject
{
    Q_OBJECT
public:
    DataBaseModel();
    virtual ~DataBaseModel() {}

    bool login(const QString& username, const QString& pass);

    bool setTable(const QString& tableName);
    bool setDatabase(const QString& tableName);

    void createDatabase(const QString& name);

    bool addEmptyRow();
    bool changeCell(int row, int column, const QString& val);
    void find(int headerID, const QString& val);
    void remove(int headerID, const QString& val);
    void removeRow(int row);
    void clearTable();
    void updateTable();

    QSharedPointer<QSqlQueryModel> model();
    QStringList headers();
    QStringList tableNames();
    QStringList databaseNames();

    void test();

private:
    QSqlDatabase m_database;
    QSharedPointer<QSqlQueryModel> m_tableModel;
    QString m_currentTable;
    QStringList m_tableNames;
    QStringList m_headers;
    QStringList m_databases;

};
