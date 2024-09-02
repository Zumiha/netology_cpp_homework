#include "mainwindow.h"
#include "./ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->sb_initNum->setValue(200000);
    ui->rb_synchOff->setChecked(true);
    ui->concr_mutexed->setEnabled(false);

   race1 = new Controller(&m);
   race2 = new Controller(&m);

   concurRace1 = new ExampleRace(&m);
   concurRace2 = new ExampleRace(&m);

    //Сигналы по завершению работы потоков
    connect(race1, &Controller::sig_WorkFinish, this, &MainWindow::countResult);
    connect(race2, &Controller::sig_WorkFinish, this, &MainWindow::countResult);

    connect(concurRace1, &ExampleRace::sig_Finish, this, &MainWindow::countResult);
    connect(concurRace2, &ExampleRace::sig_Finish, this, &MainWindow::countResult);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::countResult() { //рефакторинг для DRY
    if(countFinish == 0){
        countFinish++;
    }
    else{
        ui->te_debug->append("Искомое число равно: " + QString::number(number) + ", а должно быть " + QString::number(ui->sb_initNum->value()*2));
        ui->pb_start->setEnabled(true);
    }
}

//Метод запускает два потока
void MainWindow::StartRace(void){
    if(ui->rb_qtConcur->isChecked()){
        auto initNum = ui->sb_initNum->value();
        auto mutexOn = ui->concr_mutexed->isChecked();

        auto concr_race1 = QtConcurrent::run([this, mutexOn, initNum]() {concurRace1->DoWork(&number, mutexOn, initNum);});
        auto concr_race2 = QtConcurrent::run([this, mutexOn, initNum]() {concurRace2->DoWork(&number, mutexOn, initNum);});
        concr_race1.waitForFinished();
        concr_race2.waitForFinished();
    }
    else{
        race1->operate(&number, ui->rb_mutexOn->isChecked(), ui->sb_initNum->value());
        race2->operate(&number, ui->rb_mutexOn->isChecked(), ui->sb_initNum->value());
    }
}

void MainWindow::on_rb_qtConcur_toggled() {
    if (ui->rb_qtConcur->isChecked()) {
        ui->concr_mutexed->setEnabled(true);
    } else {
        ui->concr_mutexed->setEnabled(false);
    }
}

//Обработка кнопки "Старт"
void MainWindow::on_pb_start_clicked()
{
    ui->pb_start->setEnabled(false);
    countFinish = 0;
    number = 0;
    StartRace();
}

