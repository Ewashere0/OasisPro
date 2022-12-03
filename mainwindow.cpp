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

void turnOn() {
    // DO SOMETHING
}
void turnOff() {
    // DO SOMETHING
}

void promptSignIn() {
    // DO SOMETHING
}

void standby() {
    // DO SOMETHING
}

void handlePowerPress() {
    // DO SOMETHING
}

void updateSessionsMenu() {
    // DO SOMETHING
}

void handleDownPress() {
    // DO SOMETHING
}

void handleUpPress() {
    // DO SOMETHING
}

void handleSelectPress() {
    // DO SOMETHING
}

void startSession() {
    // DO SOMETHING
}

void displayBatteryLevel() {
    // DO SOMETHING
}

void updateBatteryLevel() {
    // DO SOMETHING
}

void handleBatteryLow() {
    // DO SOMETHING
}

void startConnectionTest() {
    // DO SOMETHING
}

void displayConnection() {
    // DO SOMETHING
}

void connectionInvalid() {
    // DO SOMETHING
}

void connectionValid() {
    // DO SOMETHING
}

void endConnectionTest() {
    // DO SOMETHING
}

void continueSession() {
    // DO SOMETHING
}

void updateIntensity() {
    // DO SOMETHING
}

void savePreferences() {
    // DO SOMETHING
}

void promptToRecord() {
    // DO SOMETHING
}

void recordTherapy() {
    // DO SOMETHING
}

void createUser() {
    // DO SOMETHING
}

void selectUser() {
    // DO SOMETHING
}

void signIn() {
    // DO SOMETHING
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




