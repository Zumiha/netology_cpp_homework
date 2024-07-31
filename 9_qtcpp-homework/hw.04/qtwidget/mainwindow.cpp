#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <qobject.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->groupBox->setTitle("On/Off");
    ui->radioButton->setText("On");
    ui->radioButton_2->setText("Off");

    ui->comboBox->addItem("Default");
    ui->comboBox->addItem("Extra");
    ui->comboBox->addItem("Etc");

    ui->pushButton->setText("Start");

    connect(ui->radioButton, &QRadioButton::toggled, this, [this] {
        ui->comboBox->setEnabled(true);
        ui->pushButton->setEnabled(true);
        ui->progressBar->setEnabled(true);
    });

    connect(ui->radioButton_2, &QRadioButton::toggled, this, [this] {
        ui->comboBox->setEnabled(false);
        ui->pushButton->setEnabled(false);
        ui->progressBar->setEnabled(false);
    });

    ui->radioButton_2->toggle();

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::pushButtonClicked);

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::pushButtonClicked() {
    int prgbar_step = ui->progressBar->maximum()/10;
    int prg_value = ui->progressBar->value() + prgbar_step;
    if (prg_value > ui->progressBar->maximum()) {
        prg_value = ui->progressBar->minimum();
    }

    ui->progressBar->setValue(prg_value);

    qDebug() << "step";
}
