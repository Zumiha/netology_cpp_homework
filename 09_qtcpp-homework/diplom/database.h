#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>

#include <QSqlDataBase>
#include <QSqlError>
#include <QSqlTableModel>

#define NUM_DATA_FOR_CONNECT_TO_DB 5

#define POSTGRE_DRIVER "QPSQL"
#define DB_NAME "AirportDB"

//Перечисление полей данных перенести в database.h
enum fieldsForConnect{
    hostName = 0,
    dbName = 1,
    login = 2,
    pass = 3,
    port = 4
};


class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = nullptr);
    ~DataBase();

    void AddDataBase(QString driver, QString nameDB = "");
    void ConnectToDataBase(QVector<QString> dataForConnect);
    void DisconnectFromDataBase(QString nameDb);
    void RequestToDB(QString request);
    QSqlError GetLastError(void);

signals:
    void sig_SendStatusConnection(bool);
    void sig_SendStatusRequest(QSqlError err);

private:
    QSqlDatabase* dataBase;
    QSqlTableModel* tModel;
};

#endif // DATABASE_H
