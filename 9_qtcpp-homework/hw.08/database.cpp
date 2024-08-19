#include "database.h"

DataBase::DataBase(QObject *parent) : QObject{parent} {
    dataBase = new QSqlDatabase();
}

DataBase::~DataBase() {
    delete dataBase;
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

    auto status = dataBase->open();
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

void basicDBRequest(requestType _type) {
    if (_type == requestAllFilms) {
        this->RequestAll();
    } else if (_type == requestComedy) {
        RequestData("SELECT title, description FROM film f JOIN film_category fc on f.film_id = fc.film_id JOIN category c on c.category_id = fc.category_id WHERE c.name = 'Comedy'");
    } else if (_type == requestComedy) {
        RequestData("SELECT title, description FROM film f JOIN film_category fc on f.film_id = fc.film_id JOIN category c on c.category_id = fc.category_id WHERE c.name = 'Horror'");
    }
}

void DataBase::RequestAll() {
    QSqlTableModel model;
    model.setQuery(nullptr, *dataBase);

    model.setTable("film");
    model.select();


    emit sig_DataFromDB(model);
}

void DataBase::RequestToDB(QString request)
{
    ///Тут должен быть код ДЗ
    QSqlQueryModel model;
    model.setQuery(request, *dataBase);

    model->setHeaderData(0, Qt::Horizontal, tr("Название"));
    model->setHeaderData(1, Qt::Horizontal, tr("Описание"));

    emit sig_DataFromDB(model);
}

/*!
 * @brief Метод возвращает последнюю ошибку БД
 */

QSqlError DataBase::GetLastError()
{
    return dataBase->lastError();
}
