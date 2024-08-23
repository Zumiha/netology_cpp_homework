#include "database.h"

DataBase::DataBase(QObject *parent) : QObject{parent} {
    dataBase = new QSqlDatabase();
    simpleQuery = new QSqlQuery();
    tableWidget = new QTableWidget();

    tModel = new QSqlTableModel();
    qModel = new QSqlQueryModel();
}

DataBase::~DataBase()
{
    delete dataBase;
    delete simpleQuery;
    delete tableWidget;

    delete tModel;
    delete qModel;
}

/*!
 * \brief Метод добавляет БД к экземпляру класса QSqlDataBase
 * \param driver драйвер БД
 * \param nameDB имя БД (Если отсутствует Qt задает имя по умолчанию)
 */
void DataBase::AddDataBase(QString driver, QString nameDB) {
    *dataBase = QSqlDatabase::addDatabase(driver, nameDB);
}

/*!
 * \brief Метод подключается к БД
 * \param для удобства передаем контейнер с данными необходимыми для подключения
 * \return возвращает тип ошибки
 */
void DataBase::ConnectToDataBase(QVector<QString> data) {
    dataBase->setHostName(data[hostName]);
    dataBase->setDatabaseName(data[dbName]);
    dataBase->setUserName(data[login]);
    dataBase->setPassword(data[pass]);
    dataBase->setPort(data[port].toInt());

    ///Тут должен быть код ДЗ

    bool status;
    status = dataBase->open();
    emit sig_SendStatusConnection(status);

}
/*!
 * \brief Метод производит отключение от БД
 * \param Имя БД
 */
void DataBase::DisconnectFromDataBase(QString nameDb) {
    *dataBase = QSqlDatabase::database(nameDb);
    dataBase->close();

}
/*!
 * \brief Метод формирует запрос к БД.
 * \param request - SQL запрос
 * \return
 */
void DataBase::RequestToDB(QString request)
{

    ///Тут должен быть код ДЗ

    *simpleQuery = QSqlQuery(*dataBase);
    QSqlError err;
    if(simpleQuery->exec(request) == false){
        err = simpleQuery->lastError();
    }
    // qDebug() << simpleQuery->executedQuery();

    emit sig_SendStatusRequest(err);
}

void DataBase::ReadAnswerFromDB(int reqType)
{
    auto request = simpleQuery->executedQuery();

    switch (reqType) {
    case requestAllFilms:
    {
        // qDebug() << request;
        if(tModel != nullptr) {
            delete tModel;
            tModel = nullptr;
        }
        tModel = new QSqlTableModel (nullptr, *dataBase);
        // qDebug() << "Database to Model";
        tModel->setTable("film");
        tModel->select();
        // qDebug() << "Select() in tModel";
        tModel->setHeaderData(1, Qt::Horizontal, tr("Название"));
        tModel->setHeaderData(2, Qt::Horizontal, tr("Описание"));
        // qDebug() << "setHeader in model";


        //Реализация tModel через setQuery

        // tModel->setQuery(request, *dataBase);
        // tModel->setHeaderData(1, Qt::Horizontal, tr("Название"));
        // tModel->setHeaderData(2, Qt::Horizontal, tr("Описание"));

        emit sig_SendDataFromDBtM(tModel, requestAllFilms);
        break;
    }
    case requestComedy:
    case requestHorrors:
    {
        qModel->setQuery(request, *dataBase);
        qModel->setHeaderData(0, Qt::Horizontal, tr("Название"));
        qModel->setHeaderData(1, Qt::Horizontal, tr("Описание"));
        qModel->setHeaderData(2, Qt::Horizontal, tr("Жанр"));

        if (reqType == requestComedy) {
            emit sig_SendDataFromDBqM(qModel, requestComedy);
        }
        else {
            emit sig_SendDataFromDBqM(qModel, requestHorrors);
        }
        break;
    }
    case requestAllFilmsTableWidget:
    {
        // tableWidget->setColumnCount(3);
        // tableWidget->setRowCount(0);
        // QStringList hdrs;
        // hdrs << "Название" << "Описание" << "Genre";
        // tableWidget->setHorizontalHeaderLabels(hdrs);

        // uint32_t conterRows = 0;

        // while(simpleQuery->next()){
        //     QString str;
        //     tableWidget->insertRow(conterRows);

        //     for(int i = 0; i<tableWidget->columnCount(); ++i){
        //         str = simpleQuery->value(i).toString();
        //         QTableWidgetItem *item = new QTableWidgetItem(str);
        //         tableWidget->setItem(tableWidget->rowCount() - 1, i, item);
        //     }
        //     ++conterRows;
        // }
        // emit sig_SendDataFromDB(tableWidget, requestAllFilmsTableWidget);
        break;
    }
    default:
        break;
    }

}

/*!
 * @brief Метод возвращает последнюю ошибку БД
 */
QSqlError DataBase::GetLastError()
{
    return dataBase->lastError();
}
