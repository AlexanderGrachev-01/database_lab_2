#pragma once

#include <QObject>
#include <QSharedPointer>
#include <QtSql/QSqlTableModel>

#include <databasemodel.h>

class DataBaseViewModel : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(QSqlTableModel* table READ table WRITE setTable NOTIFY tableChanged)
public:
    DataBaseViewModel();
    virtual ~DataBaseViewModel() {}

    Q_INVOKABLE bool login(const QString& username, const QString& pass);

    Q_INVOKABLE QObject* table() const;
    Q_INVOKABLE void setTable(const QString& tableName);
    Q_INVOKABLE void setDatabase(const QString& dbName);
    Q_INVOKABLE QStringList headers() const;
    Q_INVOKABLE QStringList tableNames() const;
    Q_INVOKABLE QStringList databaseNames() const;

    Q_INVOKABLE bool addEmptyRow();
    Q_INVOKABLE bool changeCell(int row, int column, const QString& val);
    Q_INVOKABLE void find(int headerId, const QString& val);
    Q_INVOKABLE void remove(int headerId, const QString& val);
    Q_INVOKABLE void removeRow(int row);
    Q_INVOKABLE void clearTable();
    Q_INVOKABLE void updateTable();

    Q_INVOKABLE void test();

signals:
    void tableChanged();
    void databaseChanged();
    void headersChanged();

private:
    QSharedPointer<DataBaseModel> m_dataBaseModel;
};

