#ifndef DATABASE_H
#define DATABASE_H

#include <QTableWidget>
#include <QObject>
#include <QSqlDataBase>
#include <QSqlError>
#include <QSqlQuery>

#include <QSqlQueryModel>
#include <QSqlTableModel>

#include <QConcatenateTablesProxyModel>

#define POSTGRE_DRIVER "QPSQL"
#define DB_NAME "MyDB"

//Количество полей данных необходимых для подключения к БД
#define NUM_DATA_FOR_CONNECT_TO_DB 5

//Перечисление полей данных
enum fieldsForConnect{
    hostName = 0,
    dbName = 1,
    login = 2,
    pass = 3,
    port = 4
};

//Типы запросов
enum requestType{
    requestAllFilms,
    requestComedy,
    requestHorrors,
    requestAllFilmsTableWidget

};



class DataBase : public QObject
{
    Q_OBJECT

public:
    explicit DataBase(QObject *parent = nullptr);
    ~DataBase();

    void AddDataBase(QString driver, QString nameDB = "");
    void DisconnectFromDataBase(QString nameDb = "");
    void RequestToDB(QString request);
    QSqlError GetLastError(void);
    void ConnectToDataBase(QVector<QString> dataForConnect);
    void ReadAnswerFromDB(int reqType);


signals:

    // void sig_SendDataFromDB(const QTableWidget *tableWg, int typeR);
    void sig_SendDataFromDBqM(QSqlQueryModel *tableWg, int typeR);
    void sig_SendDataFromDBtM(QSqlTableModel *tableWg, int typeR);

    void sig_SendStatusConnection(bool);
    void sig_SendStatusRequest(QSqlError err);



private:

    QSqlDatabase* dataBase;
    QSqlQuery* simpleQuery;
    QTableWidget* tableWidget;

    QSqlTableModel* tModel;
    QSqlQueryModel* qModel;

};

#endif // DATABASE_H
