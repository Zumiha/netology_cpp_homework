#include "database.h"

DataBase::DataBase(QObject *parent) : QObject{parent} {
    dataBase = new QSqlDatabase();
    tModel = new QSqlTableModel();
}

DataBase::~DataBase() {
    delete dataBase;
    delete tModel;
}

void DataBase::AddDataBase(QString driver, QString nameDB) {
    *dataBase = QSqlDatabase::addDatabase(driver, nameDB);
    tModel = new QSqlTableModel (nullptr, *dataBase);
}

void DataBase::ConnectToDataBase(QVector<QString> dataForConnect) {
    dataBase->setHostName(dataForConnect[hostName]);
    dataBase->setDatabaseName(dataForConnect[dbName]);
    dataBase->setUserName(dataForConnect[login]);
    dataBase->setPassword(dataForConnect[pass]);
    dataBase->setPort(dataForConnect[port].toInt());

    bool status;
    status = dataBase->open();
    emit sig_SendStatusConnection(status);
}

void DataBase::DisconnectFromDataBase(QString nameDb) {
    *dataBase = QSqlDatabase::database(nameDb);
    dataBase->close();
}

void DataBase::RequestToDB(QString request) {
    QSqlError err;
    // *simpleQuery = QSqlQuery(*dataBase);
    // if(simpleQuery->exec(request) == false){
    //     err = simpleQuery->lastError();
    // }
    emit sig_SendStatusRequest(err);
}

QSqlError DataBase::GetLastError(void) {
    return dataBase->lastError();
}
