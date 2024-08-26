#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "stopwatch.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void recive_updateTime(const QString &_text);
    void LaunchButtonClicked();
    void LapButtonClicked();
    void ClearButtonClicked();
signals:
    void timeCleared();
    void lapTime();
private:
    Ui::MainWindow *ui;
    StopWatch *stopwatch = nullptr;
};
#endif // MAINWINDOW_H
