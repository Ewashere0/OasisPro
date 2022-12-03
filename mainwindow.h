#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    int powerStatus;    // indicator of power status
    bool inSessionStatus;   // checks whether a session is ongoing
    int currentSessionGroup;   // indicates what session group (duration) is selected
    int currentSessionType; // indicates what session type the user chose
    bool signedInStatus;    // checks whether user is signed in
    int batteryLevel;   // indicates the battery level
    int currentIntensity; // indicates the intensity level

    /* Some helper functions that can be cut and paste later into functions to do some operations on the UI
     * Not sure about what conditions need to be satisfied to do a lot of these so I am putting them as helpers for now
     */
    
    void turnOn(); // turns on the device by enabling the UI
    void turnOff(); // turns off the device by disabling the UI

    void promptSignIn(); // opens the sign in prompt for the user
    void standby(); // what does this function do?

    void handlePowerPress(); // handles the functionality for the power button
    void updateSessionsMenu(); // updates the UI of the available sessions depending on the session group
    void handleDownPress(); // handles the down button press for selecting session type
    void handleUpPress(); // handles the up button press for selecting session type
    void handleSelectPress(); // handles the select button press to confirm the session start
    void startSession(); // starts the session functionality
    void displayBatteryLevel(); // displays the current battery level by checking the batteryLevel variable
    void updateBatteryLevel(); // updates the batterylevel variable after
    void handleBatteryLow(); // handles the battery level low extension
    void startConnectionTest(); // to check device connection before session start
    void displayConnection(); // displays connection strength on UI (on the numbers 1-4 bar)
    void connectionInvalid(); // handles the case where connection status is low
    void connectionValid(); // confirms that connection is valid so session can start
    void endConnectionTest(); // ends the connection test
    void continueSession(); // continues the session (maybe have a countdown for the duration?)
    void updateIntensity(); // updates the currentIntensity variable according to user input
    void savePreferences(); // saves the user's preferred intensity (where?)
    void promptToRecord(); // post session, prompts user if they wish to record the just completed session
    void recordTherapy(); // records the therapy session information (duration, frequency, type)
    void createUser(); // handles the new user profile creation
    void selectUser(); // handles the case where the user selects an existing profile
    void signIn(); // handles user sign-in


    //changes the color of the light, can be private later or just cut&paste into different function.
    void greenLightOn(); //turns greenlight on
    void greenLightOff(); //turns the greenlight off

private slots:
    //slot that determines what calls a specific function based on the state of the program (ie; in session)
    void on_pwrButton_clicked();

    //slot that determines what to call when the "hold" button is pressed
    void on_holdButton_clicked();

    //slot to call function when "up" button is pressed
    void on_upButton_clicked();

    //slot to call function when "down" button is pressed
    void on_downButton_clicked();

    //slot to determine what to do when check button is clicked
    void on_checkButton_clicked();

    //do something when the add profile button is clicked
    void on_addProfileButton_clicked();

    //slot when user selects a profile
    void on_startSessionButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
