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
    ui->selectButton->setEnabled(false);
    ui->tabWidget->setEnabled(false);

    // Connect buttons to slot functions
    connect(ui->pwrButton, SIGNAL(released()), this, SLOT (handlePowerPress()));
    connect(ui->holdButton, SIGNAL(released()), this, SLOT (handleHoldPress()));
    connect(ui->upButton, SIGNAL(released()), this, SLOT (handleUpPress()));
    connect(ui->downButton, SIGNAL(released()), this, SLOT (handleDownPress()));
    connect(ui->selectButton, SIGNAL(released()), this, SLOT (handleSelectPress()));
    connect(ui->startSessionButton, SIGNAL(released()), this, SLOT (handleStartSessionPress()));
    connect(ui->addProfileButton, SIGNAL(released()), this, SLOT (handleAddProfilePress()));

    // All available Session Frequency Ranges (can be used when the user wants to create a new Session in the User Designated group)
    sessionFreqRanges = {"MET", "Sub-Delta", "Delta", "Theta"};

    // All available CES Modes (can be used when the user wants to create a new Session in the User Designated group)
    cesModes = {"Short-Pulse", "50% Duty Cycle"};

    // Create the sessions for the 20-min session group
    for (int i = 0; i < 4; i++) {
        if (i == 1) {
            Session session(i, sessionFreqRanges[i], cesModes[1], 20);
            sessionGroup1.push_back(session);
        }
        else {
            Session session(i, sessionFreqRanges[i], cesModes[0], 20);
            sessionGroup1.push_back(session);
        }
    }

    // Create the sessions for the 45-min session group
    for (int i = 0; i < 4; i++) {
        if (i == 1) {
            Session session(i, sessionFreqRanges[i], cesModes[1], 45);
            sessionGroup2.push_back(session);
        }
        else {
            Session session(i, sessionFreqRanges[i], cesModes[0], 45);
            sessionGroup2.push_back(session);
        }
    }

    // Create a list containing all three Session Groups
    sessionGroupList = {sessionGroup1, sessionGroup2, sessionGroup3};

    // Indexes used to cycle through different Session Groups and Sessions when the user pressed the Power or Up and Down buttons
    curSessionGroupIndex = 0;
    curSessionIndex = 0;

    // Default intensity Level
    curIntensity = 4;

    // Default battery Level
    batteryLevel = 100;

    // Test: sessionGroupList[group-index][session-index]
    qInfo(sessionGroupList[0][3].getFrequency().c_str());
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
    ui->selectButton->setEnabled(true);
    ui->tabWidget->setEnabled(true);
    powerStatus = !powerStatus;

}
void MainWindow:: turnOff() {

    // DO SOMETHING
    ui->upButton->setEnabled(false);
    ui->downButton->setEnabled(false);
    ui->pwrButton->setEnabled(false);
    ui->selectButton->setEnabled(false);
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
    // Cycle through the sessionGroupList using the index
    // If the end of the array is reached, set index back to 0
    if (curSessionGroupIndex == 2) {
        curSessionGroupIndex = 0;
    }
    // Else, increment the index to reach the next Session Group
    else {
        curSessionGroupIndex += 1;
    }

    updateSessionsMenu();

    qInfo("%i", curSessionGroupIndex);
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

void MainWindow::handleHoldPress()
{
    if (powerStatus == true) {
        turnOff();
    }

    else {
        turnOn();
    }
}

void MainWindow::handleAddProfilePress()
{
    //doSomething
}

void MainWindow::handleStartSessionPress()
{
    //doSomething when user selects profile
}
/* END OF SLOTS */




