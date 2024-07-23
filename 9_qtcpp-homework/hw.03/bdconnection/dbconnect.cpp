#include "dbconnect.h"
#include "./ui_dbconnect.h"

dbconnect::dbconnect(QWidget *parent) : QMainWindow(parent), ui(new Ui::DBconnect)
{
    ui->setupUi(this);
    newDialogWindow = new Dialog();
}

dbconnect::~dbconnect()
{
    delete ui;
    delete newDialogWindow;
}

void dbconnect::on_connect2db_clicked()
{
    newDialogWindow->show();
}

