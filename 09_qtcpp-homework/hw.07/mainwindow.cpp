#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Обработка данных");
    ui->pb_clearResult->setCheckable(true);

    mp_showGraph = new QAction("Окно графиков", this);
    mp_showGraph->setCheckable(true);
    mp_showGraph->setChecked(true);

    line_series = new QLineSeries;
    chart = new QChart;
    chart_view = new QChartView;

    QMenu* graph_menu = menuBar()->addMenu("Графики");
    graph_menu->addAction(mp_showGraph);
    connect(mp_showGraph, &QAction::triggered, this, &MainWindow::slot_showGraph);
    connect(ui->pb_clearResult, &QPushButton::clicked, this, &MainWindow::ClearGraph);

    connect(this, &MainWindow::signal_toPlot, this, &MainWindow::slot_ChartData);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete line_series;
    delete chart;
    delete chart_view;
}

void MainWindow::slot_showGraph () {
    if(!mp_showGraph) {return;}

    // qDebug() << "Тест";
    if(mp_showGraph->isChecked()) {
        // qDebug() << "Показываем окно графиков";
    } else {
        // qDebug() << "Не показываем окно графиков";
    }
}

/****************************************************/
/*!
@brief:	Метод считывает данные из файла
@param: path - путь к файлу
        numberChannel - какой канал АЦП считать
*/
/****************************************************/
QVector<uint32_t> MainWindow::ReadFile(QString path, uint8_t numberChannel)
{

    QFile file(path);
    file.open(QIODevice::ReadOnly);

    if(file.isOpen() == false){

        if(pathToFile.isEmpty()){
            QMessageBox mb;
            mb.setWindowTitle("Ошибка");
            mb.setText("Ошибка открытия фала");
            mb.exec();
        }
    }
    else{




        //продумать как выйти из функции
    }

    QDataStream dataStream;
    dataStream.setDevice(&file);
    dataStream.setByteOrder(QDataStream::LittleEndian);

    QVector<uint32_t> readData;
    readData.clear();
    uint32_t currentWorld = 0, sizeFrame = 0;

    while(dataStream.atEnd() == false){

        dataStream >> currentWorld;

        if(currentWorld == 0xFFFFFFFF){

            dataStream >> currentWorld;

            if(currentWorld < 0x80000000){

                dataStream >> sizeFrame;

                if(sizeFrame > 1500){
                    continue;
                }

                for(int i = 0; i<sizeFrame/sizeof(uint32_t); i++){

                    dataStream >> currentWorld;

                    if((currentWorld >> 24) == numberChannel){

                        readData.append(currentWorld);

                    }
                }
            }
        }
    }
    ui->chB_readSucces->setChecked(true);
    return readData;
}

QVector<double> MainWindow::ProcessFile(const QVector<uint32_t> dataFile)
{
    QVector<double> resultData;
    resultData.clear();

    foreach (int word, dataFile) {
        word &= 0x00FFFFFF;
        if(word > 0x800000){
            word -= 0x1000000;
        }

        double res = ((double)word/6000000)*10;
        resultData.append(res);
    }
    ui->chB_procFileSucces->setChecked(true);

    return resultData;
}

QVector<double> MainWindow::FindMax(QVector<double> resultData)
{
    double max = 0, sMax=0;
    //Поиск первого максиума
    foreach (double num, resultData){
        //QThread::usleep(1);
        if(num > max){
            max = num;
        }
    }

    //Поиск 2го максимума
    foreach (double num, resultData){
        //QThread::usleep(1);
        if(num > sMax && (qFuzzyCompare(num, max) == false)){
            sMax = num;
        }
    }

    QVector<double> maxs = {max, sMax};
    ui->chB_maxSucess->setChecked(true);
    return maxs;
}

QVector<double> MainWindow::FindMin(QVector<double> resultData)
{

    double min = 0, sMin = 0;
    QThread::sleep(1);
    //Поиск первого максиума
    foreach (double num, resultData){
        if(num < min){
            min = num;
        }
    }
    QThread::sleep(1);
    //Поиск 2го максимума
    foreach (double num, resultData){
        if(num < sMin && (qFuzzyCompare(num, min) == false)){
            sMin = num;
        }
    }

    QVector<double> mins = {min, sMin};
    ui->chB_minSucess->setChecked(true);
    return mins;

}

void MainWindow::DisplayResult(QVector<double> mins, QVector<double> maxs)
{
    ui->te_Result->append("Расчет закончен!");

    ui->te_Result->append("Первый минимум " + QString::number(mins.first()));
    ui->te_Result->append("Второй минимум " + QString::number(mins.at(1)));

    ui->te_Result->append("Первый максимум " + QString::number(maxs.first()));
    ui->te_Result->append("Второй максимум " + QString::number(maxs.at(1)));
}

void MainWindow::ClearGraph()
{
    line_series->clear();
    chart->removeSeries(line_series);
}

void MainWindow::slot_ChartData() {
    chart->setTitle("Данные");
    chart->addSeries(line_series);
    chart->createDefaultAxes();

    chart_view->setChart(chart);
    chart_view->setWindowTitle("График");
    chart_view->show();
}


/****************************************************/
/*!
@brief:	Обработчик клика на кнопку "Выбрать путь"
*/
/****************************************************/
void MainWindow::on_pb_path_clicked()
{
    pathToFile = "";
    ui->le_path->clear();

    pathToFile =  QFileDialog::getOpenFileName(this,
                                              tr("Открыть файл"),
                                              QStandardPaths::writableLocation(QStandardPaths::DownloadLocation),
                                              tr("ADC Files (*.adc)")
                                              );

    ui->le_path->setText(pathToFile);
}

/****************************************************/
/*!
@brief:	Обработчик клика на кнопку "Старт"
*/
/****************************************************/
void MainWindow::on_pb_start_clicked()
{
    ui->te_Result->setText("");
    ClearGraph();
    //проверка на то, что файл выбран
    if(pathToFile.isEmpty()){
        QMessageBox mb;
        mb.setWindowTitle("Ошибка");
        mb.setText("Выберите файл!");
        mb.exec();
        return;
    }

    ui->chB_maxSucess->setChecked(false);
    ui->chB_procFileSucces->setChecked(false);
    ui->chB_readSucces->setChecked(false);
    ui->chB_minSucess->setChecked(false);

    int selectIndex = ui->cmB_numCh->currentIndex();
    //Маски каналов
    if(selectIndex == 0){
        numberSelectChannel = 0xEA;
    }
    else if(selectIndex == 1){
        numberSelectChannel = 0xEF;
    }
    else if(selectIndex == 2){
        numberSelectChannel = 0xED;
    }

    auto block_bttn = [&] {
        ui->pb_start->setEnabled(false);
        ui->pb_clearResult->setEnabled(false);
        ui->pb_path->setEnabled(false);
        ui->cmB_numCh->setEnabled(false);
        ui->spinBox->setEnabled(false);
        menuBar()->setEnabled(false);
        ui->te_Result->append("Чтение файла.");
    };
    auto read = [&]{ return ReadFile(pathToFile, numberSelectChannel); };
    auto process = [&](QVector<uint32_t> res){ return ProcessFile(res);};
    auto findMax = [&](QVector<double> res){
        ui->te_Result->append("Расчет данных.");
        maxs = FindMax(res);
        mins = FindMin(res);
        DisplayResult(mins, maxs);

        // код наполнения серии и вызов сигнала для отображения графика
        auto freq = 1000.0;
        for(int i = 0; i < freq; ++i){
            line_series->append(i, res[i]);
        }
        if (mp_showGraph->isChecked()) emit signal_toPlot();
    };
    auto unblock_bttn = [&] {
        ui->pb_start->setEnabled(true);
        ui->pb_clearResult->setEnabled(true);
        ui->pb_path->setEnabled(true);
        ui->cmB_numCh->setEnabled(true);
        ui->spinBox->setEnabled(true);
        menuBar()->setEnabled(true);
    };

    auto result = QtConcurrent::run(block_bttn).then(read).then(process).then(findMax).then(unblock_bttn);
}


