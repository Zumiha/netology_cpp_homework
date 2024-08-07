#include "stopwatch.h"

StopWatch::StopWatch(QObject *parent) : QObject{parent} {
    timer = new QTimer(this);
    timer->setInterval(100);
   connect(timer, &QTimer::timeout, this, StopWatch::updateTime);
}

StopWatch::~StopWatch() {
    delete timer;
}

bool StopWatch::TimerLive() {
    if (timer != nullptr) return timer->isActive();
    return false;
}

void StopWatch::updateTime() {
    current_time = current_time.addMSecs(100);
    stopwatch_time = current_time.toString("mm:ss.z");
    emit emit_updateTime(stopwatch_time);
}

void StopWatch::startTimer() {
    this->timer->start();
}

void StopWatch::stopTimer() {
    this->timer->stop();
}

QString StopWatch::getLapInfo() {
    return this->lap_string;
}

void StopWatch::lapTime() {

    auto lap_time_min = current_time.minute() - last_time.minute();
    auto lap_time_sec = current_time.second() - last_time.second();
    int lap_time_msec;
    if(current_time.msec() < last_time.msec()) {
        lap_time_msec = (last_time.msec() - current_time.msec())/100;
    } else {lap_time_msec = (current_time.msec() - last_time.msec())/100;}
    this->lap_string = "Lap #" + QString::number(this->lap_count) + "\tTime: ";
    if(lap_time_min != 0) this->lap_string.append(QString::number(lap_time_min) + " min ");
    this->lap_string.append(QString::number(lap_time_sec) + "." + QString::number(lap_time_msec) + " sec\n");
    this->last_time = this->current_time;
    this->lap_count++;
}

void StopWatch::timeCleared() {
    this->lap_count = 1;
    this->current_time.setHMS(0,0,0,0);
    this->last_time = this->current_time;
}
