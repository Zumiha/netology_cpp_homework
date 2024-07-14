#include <iostream>
#include <QCoreApplication>
#include <QtNetwork>
#include <QSqlQuery>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QAuthenticator network_object;
    QSqlDatabase sql_database = QSqlDatabase::addDatabase("QPSQL");

    network_object.setUser("Admin");
    sql_database.setDatabaseName("SQL database");

    qInfo() << "Username: " << network_object.user();
    qInfo() << "SQL DB name: " << sql_database.databaseName();
}
