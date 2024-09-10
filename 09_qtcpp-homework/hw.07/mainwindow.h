#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDataStream>
#include <QMessageBox>
#include <QtGlobal>
#include <QtConcurrent>
#include <QStandardPaths>
#include <QProgressDialog>

///Подключаем все что нужно для графиков

#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>

#define FD 1000.0 //частота дискретизации

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //Метод считывает данные из исходного файла
    QVector<uint32_t> ReadFile(QString path, uint8_t numberChannel);
    //Метод преобразует данные физические величины, В?
    QVector<double> ProcessFile(QVector<uint32_t> dataFile);
    //Метод ищет Максимумы
    QVector<double> FindMax(QVector<double> resultData);
    //Метод ищет минимумы
    QVector<double> FindMin(QVector<double> resultData);
    //Метод отображает результаты
    void ClearGraph();
    void DisplayResult(QVector<double> mins, QVector<double> maxs);

signals:
    void signal_toPlot();


private slots:
    void on_pb_path_clicked();
    void on_pb_start_clicked();

    void slot_showGraph();
    void slot_ChartData();

private:
    Ui::MainWindow *ui;
    QString pathToFile = "";
    uint8_t numberSelectChannel = 0xEA;

    QVector<uint32_t> readData;
    QVector<double> procesData;
    QVector<double> mins, maxs;

    QPointer<QAction> mp_showGraph = nullptr;

    QLineSeries *line_series;
    QChart *chart;
    QChartView *chart_view;
};
#endif // MAINWINDOW_H
