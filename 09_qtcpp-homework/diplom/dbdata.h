#ifndef DBDATA_H
#define DBDATA_H

#include <QDialog>
#include <QFile>
#include <QDir>

#include "database.h"
#include "IniParser.h"

namespace Ui {
class DbData;
}

class DbData : public QDialog
{
    Q_OBJECT

public:
    explicit DbData(QWidget *parent = nullptr);
    ~DbData();
    void sendData();


signals:
    void sig_sendData(QVector<QString> dbData);


private slots:
    void on_buttonBox_accepted();
    void checkSettingsDir();
    void checkSettingsFile();

private:
    Ui::DbData *ui;
    QDir settings_dir;
    QFile settings_file;
    QVector<QString> data;

    void loadConnectionInfo();

    IniParser *con_info_parsed;

    QString _host;
    QString _port;
    QString _dbName;
    QString _login;
    QString _pass;
};
#endif // DBDATA_H
