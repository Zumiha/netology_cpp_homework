#ifndef STOPWATCH_H
#define STOPWATCH_H

#pragma once
#include <QObject>
#include <QTimer>
#include <QTime>

class StopWatch : public QObject {
    Q_OBJECT
public:
    StopWatch(QObject *parent = nullptr);
    ~StopWatch();
    bool TimerLive();

    QString getLapInfo();

    void updateTime();
    void startTimer();
    void stopTimer();

signals:
    void emit_updateTime(QString &_time);
public slots:
    void lapTime();
    void timeCleared();
private:
    QTimer *timer;
    QTime current_time = QTime(0,0,0,0);
    QTime last_time = QTime(0,0,0,0);

    QString stopwatch_time;
    QString lap_string;
    int lap_count = 1;
};

#endif // STOPWATCH_H
