#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    powerStatus = false;
    ui->setupUi(this);
    ui->holdButton->setEnabled(true);
    ui->upButton->setEnabled(false);
    ui->downButton->setEnabled(false);
    ui->pwrButton->setEnabled(false);
    ui->checkButton->setEnabled(false);
    ui->tabWidget->setEnabled(false);

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

void MainWindow:: turnOn() {
    // DO SOMETHING
    ui->upButton->setEnabled(true);
    ui->downButton->setEnabled(true);
    ui->pwrButton->setEnabled(true);
    ui->checkButton->setEnabled(true);
    ui->tabWidget->setEnabled(true);
    powerStatus = !powerStatus;

}
void MainWindow:: turnOff() {

    // DO SOMETHING
    ui->upButton->setEnabled(false);
    ui->downButton->setEnabled(false);
    ui->pwrButton->setEnabled(false);
    ui->checkButton->setEnabled(false);
    ui->tabWidget->setEnabled(false);
    powerStatus = !powerStatus;

}

void MainWindow:: promptSignIn() {
    // DO SOMETHING
}

void MainWindow:: standby() {
    // DO SOMETHING
}

void MainWindow:: handlePowerPress() {
    // DO SOMETHING
}

void MainWindow:: updateSessionsMenu() {
    // DO SOMETHING
}

void MainWindow:: handleDownPress() {
    // DO SOMETHING
}

void MainWindow:: handleUpPress() {
    // DO SOMETHING
}

void MainWindow:: handleSelectPress() {
    // DO SOMETHING
}

void MainWindow:: startSession() {
    // DO SOMETHING
}

void MainWindow:: displayBatteryLevel() {
    // DO SOMETHING
}

void MainWindow:: updateBatteryLevel() {
    // DO SOMETHING
}

void MainWindow:: handleBatteryLow() {
    // DO SOMETHING
}

void MainWindow:: startConnectionTest() {
    // DO SOMETHING
}

void MainWindow:: displayConnection() {
    // DO SOMETHING
}

void MainWindow:: connectionInvalid() {
    // DO SOMETHING
}

void MainWindow:: connectionValid() {
    // DO SOMETHING
}

void MainWindow:: endConnectionTest() {
    // DO SOMETHING
}

void MainWindow:: continueSession() {
    // DO SOMETHING
}

void MainWindow:: updateIntensity() {
    // DO SOMETHING
}

void MainWindow:: savePreferences() {
    // DO SOMETHING
}

void MainWindow:: promptToRecord() {
    // DO SOMETHING
}

void MainWindow:: recordTherapy() {
    // DO SOMETHING
}

void MainWindow:: createUser() {
    // DO SOMETHING
}

void MainWindow:: selectUser() {
    // DO SOMETHING
}

void MainWindow:: signIn() {
    // DO SOMETHING
}

/* SLOTS */
void MainWindow::on_pwrButton_clicked()
{
    //doSomething
}
void MainWindow::on_holdButton_clicked()
{

    if (powerStatus == true) {
        turnOff();
    }

    else {
        turnOn();
    }
}

void MainWindow::on_upButton_clicked()
{
    cout<< "Up button pressed"<< endl;  // testing if button disabled on power off
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




