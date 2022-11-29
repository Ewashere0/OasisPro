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

void MainWindow::on_pwrButton_clicked()
{
    qInfo("the button was clicked");
}

void MainWindow::on_pwrButton_pressed()
{
    qInfo("the button was held");
}

void MainWindow::on_pwrButton_released()
{
    qInfo("button was released");
}
