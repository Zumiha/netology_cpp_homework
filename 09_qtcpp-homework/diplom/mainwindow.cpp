#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusbar->setStyleSheet("color: default");
    ui->statusbar->setStyleSheet("QStatusBar::item {border: None;}");

    conn_info = new QLabel(tr("Статус  -"));
    connection_status = new QLabel(tr("Отключено"));
    connection_status->setStyleSheet("color:red");
    ui->statusbar->addPermanentWidget(conn_info, 0);
    ui->statusbar->addPermanentWidget(connection_status, 0);

    createActions();
    createMenu();

    dataDb = new DbData(this);
    dataBase = new DataBase(this);
    msg = new QMessageBox(this);

    connect(dataDb, &DbData::sig_sendData, this, [&](QVector<QString> receivedData){
        dataForConnect = receivedData;
    });

    dataForConnect.resize(NUM_DATA_FOR_CONNECT_TO_DB);
    dataBase->AddDataBase(POSTGRE_DRIVER, DB_NAME);
    connect(dataBase, &DataBase::sig_SendStatusConnection, this, &MainWindow::ReceiveStatusConnectionToDB);
    connect(dataBase, &DataBase::sig_SendStatusRequest, this, &MainWindow::ReceiveStatusRequestToDB);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete dataDb;
    delete dataBase;
}

void MainWindow::createActions() {
    act_addData = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::DocumentNew), tr("&Адрес подключения"), this);
    act_addData->setStatusTip(tr("Ввод данных для подключения к серверу"));
    connect(act_addData, &QAction::triggered, this, &MainWindow::act_addConnectionInfo);

    act_ConnectDB = new QAction(QIcon::fromTheme(QIcon::ThemeIcon::NetworkWireless), tr("&Подключиться"), this);
    act_ConnectDB->setStatusTip(tr("Подключение к серверу"));
    connect(act_ConnectDB, &QAction::triggered, this, &MainWindow::act_connectTo);
}

void MainWindow::createMenu() {
    connectMenu = menuBar()->addMenu(tr("&Подключение"));
    connectMenu->addAction(act_addData);
    connectMenu->addSeparator();
    connectMenu->addAction(act_ConnectDB);
}

void MainWindow::act_addConnectionInfo() {
    dataDb->show();
}

void MainWindow::act_connectTo() {
    if(connection_status->text() == "Отключено"){
        connection_status->setText("Подключение");
        connection_status->setStyleSheet("color : black");

        auto conn = [&]{dataBase->ConnectToDataBase(dataForConnect);};
        QtConcurrent::run(conn);
    }
    else{
        dataBase->DisconnectFromDataBase(DB_NAME);
        connection_status->setText("Отключено");
        act_ConnectDB->setText("Подключиться");
        connection_status->setStyleSheet("color:red");
        // ui->pb_request->setEnabled(false); //окно с таблицами должно быть тут
    }
}

void MainWindow::ReceiveStatusConnectionToDB(bool status) {
    if(status){
        act_ConnectDB->setText("Отключиться");
        connection_status->setText("Подключено к БД");
        connection_status->setStyleSheet("color:green");
        // ui->pb_request->setEnabled(true); //окно с таблицами должно быть тут
    }
    else{
        dataBase->DisconnectFromDataBase(DB_NAME);
        msg->setIcon(QMessageBox::Critical);
        msg->setText(dataBase->GetLastError().text());
        connection_status->setText("Отключено");
        connection_status->setStyleSheet("color:red");
        msg->exec();
    }
}

void MainWindow::ReceiveStatusRequestToDB(QSqlError err) {
    if(err.type() != QSqlError::NoError){
        msg->setText(err.text());
        msg->exec();
    }
    //else{dataBase->ReadAnswerFromDB(ui->cb_category->currentIndex());} //currentIndex это выпадающее меню выбора
}
