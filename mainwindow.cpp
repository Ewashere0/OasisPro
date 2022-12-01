#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


/* SLOTS */
void MainWindow::on_pwrButton_clicked()
{
    qInfo("the button was clicked");
}
void MainWindow::on_holdButton_clicked()
{
    //doSomething
}

void MainWindow::on_upButton_clicked()
{
    //doSomething
}

void MainWindow::on_downButton_clicked()
{
    //doSomething
}

void MainWindow::on_checkButton_clicked()
{
    //doSomething
}

void MainWindow::on_addProfileButton_clicked()
{
    //doSomething
}

void MainWindow::on_startSessionButton_clicked()
{
    //doSomething when user selects profile
}
/* END OF SLOTS */




