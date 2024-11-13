#include "dbdata.h"
#include "ui_dbdata.h"

DbData::DbData(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DbData)
{
    ui->setupUi(this);
    checkSettingsDir();
    checkSettingsFile();

    data.resize(NUM_DATA_FOR_CONNECT_TO_DB);

}

DbData::~DbData() {
    delete ui;
    delete con_info_parsed;
}

void DbData::on_buttonBox_accepted() {
    if (ui->le_host->text() != _host ||
        ui->le_dbName->text() != _dbName ||
        ui->le_login->text() != _login ||
        ui->le_pass->text() != _pass ||
        ui->spB_port->text() != _port) {
        QDir::setCurrent(settings_dir.path());

        settings_file.open(QIODevice::WriteOnly|QIODevice::Truncate|QIODevice::Text);
        QTextStream streamOut(&settings_file);
        streamOut << "[airport_db]\n"
            "host = " + ui->le_host->text() +
            "\nport = " + ui->le_dbName->text() +
            "\ndbname = " + ui->le_login->text() +
            "\nuser = " + ui->le_pass->text() +
            "\npassword = " + ui->spB_port->text();
        settings_file.close();
        loadConnectionInfo();
        QDir::setCurrent(QCoreApplication::applicationDirPath());
    }
    data[hostName] = ui->le_host->text();
    data[dbName] = ui->le_dbName->text();
    data[login] = ui->le_login->text();
    data[pass] = ui->le_pass->text();
    data[port] = ui->spB_port->text();

    emit sig_sendData(data);
}

void DbData::loadConnectionInfo() {
    con_info_parsed = new IniParser(settings_file.fileName().toStdString());

    _host = QString::fromStdString(con_info_parsed->getValue("airport_db","host"));
    _port = QString::fromStdString(con_info_parsed->getValue("airport_db","port"));
    _dbName = QString::fromStdString(con_info_parsed->getValue("airport_db","dbname"));
    _login = QString::fromStdString(con_info_parsed->getValue("airport_db","user"));
    _pass = QString::fromStdString(con_info_parsed->getValue("airport_db","password"));

    ui->le_host->setText(_host);
    ui->spB_port->setValue(_port.toInt());
    ui->le_dbName->setText(_dbName);
    ui->le_login->setText(_login);
    ui->le_pass->setText(_pass);
}

void DbData::checkSettingsDir() {
    settings_dir.setPath("settings");
    if (!settings_dir.exists()) {QDir().mkdir("settings");}
}

void DbData::checkSettingsFile() {
    settings_file.setFileName("dbconnectioninfo.ini");
    QDir::setCurrent(settings_dir.path());
    if(!settings_file.exists()) {
        settings_file.open(QIODevice::WriteOnly|QIODevice::Text);
        QTextStream streamOut(&settings_file);
        streamOut << "[airport_db]\n"
                     "host = 981757-ca08998.tmweb.ru\n"
                     "port = 5432\n"
                     "dbname = demo\n"
                     "user = netology_usr_cpp\n"
                     "password = CppNeto3";
        settings_file.close();
    }
    loadConnectionInfo();
    QDir::setCurrent(QCoreApplication::applicationDirPath());
}

