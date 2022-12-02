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

void MainWindow::greenLightOn(){
    ui->pwrLight->setStyleSheet("background-color: #00ed00");
    ui->pwrLight->repaint();
}

void MainWindow::greenLightOff(){
    ui->pwrLight->setStyleSheet("background-color : black");
    ui->pwrLight->repaint();
}

/* SLOTS */
void MainWindow::on_pwrButton_clicked()
{
    greenLightOff();
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




