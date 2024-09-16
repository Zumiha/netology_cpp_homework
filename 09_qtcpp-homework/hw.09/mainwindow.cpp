#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    udpWorker = new UDPworker(this);
    udpService = new UDPworker(this);
    udpWorker->InitSocket();
    udpService->InitSocket();

    connect(udpWorker, &UDPworker::sig_sendTimeToGUI, this, &MainWindow::DisplayTime);
    connect(udpWorker, &UDPworker::sig_sendDataToGUI, this, &MainWindow::DisplayData);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [&]{

        QDateTime dateTime = QDateTime::currentDateTime();

        QByteArray dataToSend;
        QDataStream outStr(&dataToSend, QIODevice::WriteOnly);

        outStr << msgType::Default;
        outStr << dateTime;

        udpWorker->SendDatagram(dataToSend);
        timer->start(TIMER_DELAY);

    });

    connect(ui->pb_user_data, &QPushButton::clicked, this, [&]{

        QByteArray dataToSend;
        QDataStream outStr(&dataToSend, QIODevice::WriteOnly);

        outStr << msgType::User;
        outStr << ui->le_user_input->text();

        udpService->SendDatagram(dataToSend);
    });

}

MainWindow::~MainWindow() {delete ui;}
void MainWindow::on_pb_start_clicked() {timer->start(TIMER_DELAY);}
void MainWindow::on_pb_stop_clicked() {timer->stop();}

void MainWindow::DisplayTime(QDateTime data) {
    counterPck++;
    if(counterPck % 20 == 0){
        ui->te_result->clear();
    }
    ui->te_result->append("Текущее время: " + data.toString() + ". Принято пакетов " + QString::number(counterPck));
}

void MainWindow::DisplayData(QString data) {
    counterPck++;
    if(counterPck % 20 == 0){
        ui->te_result->clear();
    }
    ui->te_result->append(data);
}

