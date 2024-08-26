#ifndef DBCONNECT_H
#define DBCONNECT_H

#include <QMainWindow>
#include "dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class DBconnect;
}
QT_END_NAMESPACE

class dbconnect : public QMainWindow
{
    Q_OBJECT

public:
    dbconnect(QWidget *parent = nullptr);
    ~dbconnect();

private slots:
    void on_connect2db_clicked();

private:
    Ui::DBconnect *ui;
    Dialog* newDialogWindow;
};
#endif // DBCONNECT_H
