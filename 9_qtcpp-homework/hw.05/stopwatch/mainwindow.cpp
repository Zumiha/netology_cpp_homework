#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setGeometry(200,200,250,450);

    ui->lap_button->setEnabled(false);
    ui->clear_button->setEnabled(false);

    connect(ui->launch_button, &QPushButton::clicked, this, &MainWindow::LaunchButtonClicked);
    connect(ui->lap_button, &QPushButton::clicked, this, &MainWindow::LapButtonClicked);
    connect(ui->clear_button, &QPushButton::clicked, this, &MainWindow::ClearButtonClicked);

    stopwatch = new StopWatch(this);
    connect(stopwatch, &StopWatch::emit_updateTime, this, &MainWindow::recive_updateTime);

    connect(this, &MainWindow::lapTime, stopwatch, &StopWatch::lapTime);
    connect(this, &MainWindow::timeCleared, stopwatch, &StopWatch::timeCleared);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::recive_updateTime(const QString &_text) {
    ui->time_label->setText(_text);
}

void MainWindow::LaunchButtonClicked() {
    if(stopwatch->TimerLive()) {
        stopwatch->stopTimer();
        ui->launch_button->setText("Start");
        ui->lap_button->setEnabled(false);
        ui->clear_button->setEnabled(true);
    }
    else {
        stopwatch->startTimer();
        ui->launch_button->setText("Stop");
        ui->lap_button->setEnabled(true);
        ui->clear_button->setEnabled(false);
        ui->lap_record->setEnabled(true);
    }
}
void MainWindow::LapButtonClicked() {
    emit lapTime();
    auto cursor = QTextCursor(ui->lap_record->document()); cursor.setPosition(0); ui->lap_record->setTextCursor(cursor);
    ui->lap_record->insertPlainText(stopwatch->getLapInfo());
}

void MainWindow::ClearButtonClicked() {
    ui->time_label->setText("00:00.0");
    ui->lap_record->clear();
    emit timeCleared();
}
