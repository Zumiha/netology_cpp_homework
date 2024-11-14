#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtConcurrent>

#include <windows.h>
#include "dbdata.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
class QAction;
class QActionGroup;
class QLabel;
class QMenu;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void act_addConnectionInfo();
    void act_connectTo();

    void ReceiveStatusConnectionToDB(bool status);
    void ReceiveStatusRequestToDB(QSqlError err);

private:
    Ui::MainWindow *ui;

    void createActions();
    void createMenu();

    void startUpConnect();

    QMenu *connectMenu;
    QAction *act_addData;
    QAction *act_ConnectDB;
    QLabel *conn_info;
    QLabel *connection_status;

    DbData *dataDb;
    QVector<QString> dataForConnect;
    DataBase* dataBase;
    QMessageBox* msg;
};
#endif // MAINWINDOW_H
