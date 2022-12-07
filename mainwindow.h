#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <string>
#include <list>
#include <iostream>
#include "UserProfile.h"
#include <unistd.h>
#include "Session.h"
#include "ui_mainwindow.h"
#include <QTimer>


using namespace std;
/* Constants for color scheme sampled from device for altering color outside of design mode */
#define YELLOW "#e5e400"
#define RED "#fd0002"
#define GREEN "#00ed00"
#define BLUE "#80c3bf"

/* Change color instructions:
 * use the command ui->elementYourChanging->setStyleSheet("background-color : newColor");
 * then, use the command ui->elementYourChanging->repaint(); for those changes to be shown on gui.
 */

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    
    
private:
    bool powerStatus;    // indicator of power status
    bool inSessionStatus;   // checks whether a session is ongoing
    int curSessionGroupIndex;   // indicates what session group (duration) is selected
    int curSessionIndex;    // Indicates currently highlighted session type (1 - 4)
    bool signedInStatus;    // checks whether user is signed in
    int batteryLevel;   // indicates the battery level
    int curDuration;    // Indicate the current duration of the chosen session (in mins), based on the chosen session group
    int curIntensity; // indicates the intensity level
    int curFrequencyIndex; // indicates the currently highlighted frequency
    int curModeIndex; // indicates currently highlighted mode

    QTimer sessionTimer; // timer for session durations;
    QTimer perSecondTimer; // timer which repeats every one second for updating the session timer remaining time

    vector<string> sessionFreqRanges;
    vector<string> cesModes;
    vector<UserProfile*> users;

    // Trying to implement sessions without duration attribute, and with pointers

    vector<int> durations;  // available options for duration
    vector<Session*> sessionTypes; // a list of all session types



    /* Some helper functions that can be cut and paste later into functions to do some operations on the UI
     * Not sure about what conditions need to be satisfied to do a lot of these so I am putting them as helpers for now
     */

    void togglePowerStatus(); // changes the power status (ON/OFF) and the UI accordingly

    void toggleButtonState(bool state); // enables/disables the buttons, except for holdButton (always enabled)

    bool eventFilter(QObject* obj, QEvent* event);
    void changeButtonStyles(QPushButton* btn, QEvent* event);

    void promptSignIn(); // opens the sign in prompt for the user
    void standby(); // what does this function do?

    void updateSessionsMenu(); // updates the UI of the available sessions depending on the session group
    void startSession(); // starts the session functionality
    void displayBatteryLevel(); // displays the current battery level by checking the batteryLevel variable
    void updateBatteryLevel(); // updates the batterylevel variable after
    void handleBatteryLow(); // handles the battery level low extension
    void startConnectionTest(); // to check device connection before session start
    void displayConnection(int connectionQuality); // displays connection strength on UI (on the numbers 1-4 bar)
    void connectionInvalid(); // handles the case where connection status is low
    void connectionValid(); // confirms that connection is valid so session can start
    void endConnectionTest(); // ends the connection test
    void continueSession(); // continues the session (maybe have a countdown for the duration?)
    void updateIntensity(); // updates the currentIntensity variable according to user input
    void savePreferences(); // saves the user's preferred intensity (where?)
    //void promptToRecord(); // post session, prompts user if they wish to record the just completed session
    void recordTherapy(); // records the therapy session information (duration, frequency, type)
    void createUser(string un, UserProfile**); // handles the new user profile creation
    void selectUser(); // handles the case where the user selects an existing profile
    void signIn(); // handles user sign-in
    void updateView(); //Updates user profile list

    void solidConnection();
    void noConnection();
    void okayConnection();

    void pwrLightOn(int index); //turns the specified power light on
    void pwrLightOff(int index); //turns the specified power light off
    //changes the color of the light, can be private later or just cut&paste into different function.
    void greenLightOn(); //turns greenlight on
    void greenLightOff(); //turns the greenlight off

    // updates the UI according to the currently selected mode
    void updateModeUI();

    // Function to change colors for Session Group Icons when cycling through the session groups
    void groupTwentyMinLightOn();
    void groupFortyFiveMinLightOn();
    void groupUserDesignatedLightOn();
    void allSessionGroupLightOff();
    // Functions to change colors for the Session Icons (i.e. Session Frequency Types Icons) when cycling through the sessions
    void sessionMETLightOn();
    void sessionSDeltaLightOn();
    void sessionDeltaLightOn();
    void sessionThetaLightOn();
    void allSessionLightOff();

private slots:

    void promptToRecord(); // post session, prompts user if they wish to record the just completed session

    void updatePerSecond(); // used to update the displayed value of the session timer per second

    void handlePowerPress(); // handles the functionality for the power button

    //slot that determines what to call when the "hold" button is pressed
    void handleHoldPress();

    void handleDownPress(); // handles the down button press for selecting session type
    void handleUpPress(); // handles the up button press for selecting session type
    void handleSelectPress(); // handles the select button press to confirm the session start

    //do something when the add profile button is clicked
    void handleAddProfilePress();

    // handles the press of the change mode button
    void handleModePress();

    //slot when user selects a profile

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
