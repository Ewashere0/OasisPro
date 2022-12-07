#include "mainwindow.h"


using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Setting initial state of UI
    powerStatus = false;
    ui->setupUi(this);
    ui->pwrButton->setEnabled(true);
    toggleButtonState(powerStatus);

    // Connect buttons to slot functions
    connect(ui->pwrButton, SIGNAL(released()), this, SLOT (handlePowerPress()));
    connect(ui->upButton, SIGNAL(released()), this, SLOT (handleUpPress()));
    connect(ui->downButton, SIGNAL(released()), this, SLOT (handleDownPress()));
    connect(ui->selectButton, SIGNAL(released()), this, SLOT (handleSelectPress()));
    connect(ui->addProfileButton, SIGNAL(released()), this, SLOT (handleAddProfilePress()));
    connect(ui->modeButton, SIGNAL(released()), this, SLOT (handleModePress()));
    connect(ui->pwrButton, SIGNAL(pressed()), this, SLOT (handlePowerHold()));

    // connect session timer to its handler
    connect(&sessionTimer, SIGNAL(timeout()), this, SLOT (promptToRecord()));

    // connect per second timer to its handler
    connect(&perSecondTimer, SIGNAL(timeout()), this, SLOT (updatePerSecond()));

    // starting per second timer with one second intervals
    perSecondTimer.start(1000);

    // setting session time label to 00:00 as default on start-up
    ui->remainTimeN->setText("00:00");

    //Adding Default Guest Profile
    UserProfile* guest;
    QString g = "Guest";
    //Create user
    createUser(g.toStdString(), &guest);
    users.push_back(guest);

    cout <<"Profile: " << guest->getUsername() << " Added." <<endl;

    //Add profile to profileSelector
    updateView();

    // Hover feature
    ui->pwrButton->installEventFilter(this);
    ui->upButton->installEventFilter(this);
    ui->downButton->installEventFilter(this);
    ui->selectButton->installEventFilter(this);


    // All available Session Frequency Ranges (can be used when the user wants to create a new Session in the User Designated group)
    sessionFreqRanges = {"MET", "Sub-Delta", "Delta", "Theta"};

    // All available CES Modes (can be used when the user wants to create a new Session in the User Designated group)
    cesModes = {"Short-Pulse", "50% Duty Cycle"};

    // All available Session Durations ('0' can be overriden when the user wants to create a new Session in the User Designated group)
    // Since the only difference between the session groups is duration, cycling through the durations will be equivalent to cycling
    // through the session groups
    durations = {20, 45, 0};

    // Create the 4 pre-defined sessions, storing them inside a Session Group
    for (int i = 0; i < 4; i++) {
        if (i == 1) {
            Session* session = new Session(sessionFreqRanges[i], cesModes[1]);
            sessionTypes.push_back(session);
        }
        else {
            Session* session = new Session(sessionFreqRanges[i], cesModes[0]);
            sessionTypes.push_back(session);
        }
    }

    // Indexes used to cycle through different Session Groups and Sessions when the user pressed the Power or Up and Down buttons
    curSessionGroupIndex = 0;
    curSessionIndex = 0;

    // Indexes used to cycle through different frequencies and toggle between the two different modes
    curFrequencyIndex = 0;
    curModeIndex = 0;

    // Updating mode UI as set for default value
    updateModeUI();

    // Setting current duration according to current session group selected
    curDuration = durations[curSessionGroupIndex];

    // Default intensity Level
    curIntensity = 4;

    // Default battery Level
    batteryLevel = 100;
}

MainWindow::~MainWindow()
{
// This line is commented out, unsure of its purpose. The sessionTypes is reset automatically every time the program is run, so why do
// we need to manually remove each item in the sessionTypes ??? - Henry
    for (Session *s: sessionTypes) {
        if (s != NULL) {
            delete s;
        }
    }

    delete ui;
}

//#define YELLOW "#e5e400"
//#define RED "#fd0002"
//#define GREEN "#00ed00"
//#define BLUE "#80c3bf"

void MainWindow:: startConnectionTest() {
    // DO SOMETHING
    //Display connection,
}

void MainWindow:: displayConnection(int connectionQuality) {
    // DO SOMETHING
    //call a helper function based on the given connection

    if (connectionQuality == 0 ) { //No connection
        noConnection(); //Will blink and return to safe mode, and then restart test with new connection

    } else if(connectionQuality == 1) { //"Okay" Connection
        //display connection and end connection test
        okayConnection();

    } else if (connectionQuality == 2) { // "Solid" connection
        //display connection and end
        solidConnection();
    }


}

void MainWindow::okayConnection(){

    for (int i =0; i < 4 ; ++i) {
        pwrLightOn(4);
        pwrLightOn(5);
        pwrLightOn(6);
        usleep(100000 * 2); //Sleeps for two seconds
        pwrLightOff(4);
        pwrLightOff(5);
        pwrLightOff(6);
        usleep(100000 * 2); //Sleeps for two seconds
    }
}

void MainWindow::noConnection(){

    for (int i =0; i < 4 ; ++i) {
        pwrLightOn(7);
        pwrLightOn(8);
        usleep(100000 * 2); //Sleeps for two seconds
        pwrLightOff(7);
        pwrLightOff(8);
        usleep(100000 * 2); //Sleeps for two seconds
    }
    //Scroll graph up and down to show unit returning to normal voltage (15-20 seconds)
    //to be continued
}

void MainWindow::solidConnection(){
    for (int i =0; i < 4 ; ++i) {
        pwrLightOn(1);
        pwrLightOn(2);
        pwrLightOn(3);
        usleep(100000 * 2); //Sleeps for two seconds
        pwrLightOff(1);
        pwrLightOff(2);
        pwrLightOff(3);
        usleep(100000 * 2); //Sleeps for two seconds
    }
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
    // after session end, set timer to zero
    ui->remainTimeN->setText("00:00");
    // testing timer
    cout << "Timer finished now!" << endl;
    // DO SOMETHING
}

void MainWindow:: recordTherapy() {
    // DO SOMETHING
}

void MainWindow:: createUser(string un, UserProfile** p) {
    //Create a profile to the profile selector
    UserProfile* newProfile = new UserProfile(un);
    *p = newProfile;
}

void MainWindow:: selectUser() {
    // DO SOMETHING
}

void MainWindow:: signIn() {
    // DO SOMETHING
}

void MainWindow::pwrLightOn(int index){
    switch(index){
        case 1: ui->oneLabel->setStyleSheet("color: #00ed00");break;
        case 2: ui->twoLabel->setStyleSheet("color: #00ed00");break;
        case 3: ui->threeLabel->setStyleSheet("color: #00ed00");break;
        case 4: ui->fourLabel->setStyleSheet("color: #e5e400");break;
        case 5: ui->fiveLabel->setStyleSheet("color: #e5e400");break;
        case 6: ui->sixLabel->setStyleSheet("color: #e5e400");break;
        case 7: ui->sevenLabel->setStyleSheet("color: #fd0002");break;
        case 8: ui->eightLabel->setStyleSheet("color: #fd0002");break;
    }
    ui->pwrLvlSplitter->repaint();
}

void MainWindow::pwrLightOff(int index){
    switch(index){
        case 1: ui->oneLabel->setStyleSheet("color: grey");break;
        case 2: ui->twoLabel->setStyleSheet("color: grey");break;
        case 3: ui->threeLabel->setStyleSheet("color: grey");break;
        case 4: ui->fourLabel->setStyleSheet("color: grey");break;
        case 5: ui->fiveLabel->setStyleSheet("color: grey");break;
        case 6: ui->sixLabel->setStyleSheet("color: grey");break;
        case 7: ui->sevenLabel->setStyleSheet("color: grey");break;
        case 8: ui->eightLabel->setStyleSheet("color: grey");break;
    }
    ui->pwrLvlSplitter->repaint();
}



void MainWindow::togglePowerStatus() {
    powerStatus = !powerStatus;
    toggleButtonState(powerStatus);
    if (powerStatus) {
        greenLightOn();
        displayBatteryLevel();
        // Light up the default session group and session number icons when turned on
//        groupTwentyMinLightOn();
//        sessionMETLightOn();
        updateSessionsMenu();
    }
    else {
        greenLightOff();
        // Turn off all session groups and session numbers icons when turned off
        allSessionGroupLightOff();
        allFrequencyLightOff();
    }
}

void MainWindow:: promptSignIn() {
    // DO SOMETHING
    //Force users to make or select profile. Or select Guest

    //DEPRECATED
}

void MainWindow:: standby() {
    // DO SOMETHING
}

void MainWindow:: updateBatteryLevel() {
    // DO SOMETHING
}

void MainWindow:: startSession() {

    // Use curSessionGroupIndex for the duration vector to get the chosen Duration
    // Use curSessionIndex for the sessionTypes vector to get the chosen Session object, which will contain the chosen
    // session frequency type and CES mode

    inSessionStatus = true;

    Session *curSession;
    sessionTimer.setSingleShot(true);

    // if curSessionGroupIndex is not 2 (user-defined), use the current pre-defined session with the curDuration
    if(curSessionGroupIndex != 2) {
        curSession = sessionTypes[curSessionIndex];
    }

    // user-selected frequency and mode chosen, along with user-selected duration
    else {
        curSession = new Session(sessionFreqRanges[curFrequencyIndex], cesModes[curModeIndex]);
    }

    // created a QTimer object in mainWindow on which you can call the QTimer functions
    // once this timer ends, the promptToRecord() function is called (connected by timeout() signal)
    //session time = minutes but in seconds hence the 1000 to convert ms to s.

    sessionTimer.start(curDuration*1000);


    //when session is started, will do a timer and on the end of timer, user will be prompted to record.


    //QTimer::singleShot(curDuration*1000,this,&MainWindow::promptToRecord);



}

void MainWindow:: displayBatteryLevel() {

    if (batteryLevel > 50) {

        for (int i =0; i < 2 ; ++i) {
            pwrLightOn(1);
            pwrLightOn(2);
            pwrLightOn(3);
            usleep(100000 * 2); //Sleeps for two seconds
            pwrLightOff(1);
            pwrLightOff(2);
            pwrLightOff(3);
            usleep(100000 * 2); //Sleeps for two seconds
            cout << "Battery Level is at: "<<batteryLevel<<endl;
        }
    } else if (batteryLevel > 25) {

        for (int i =0; i < 2 ; ++i) {
            pwrLightOn(1);
            pwrLightOn(2);
            usleep(100000 * 2); //Sleeps for two seconds
            pwrLightOff(1);
            pwrLightOff(2);
            usleep(100000 * 2); //Sleeps for two seconds
        }
        cout << "Battery Level is at: "<< batteryLevel << endl;
    } else if (batteryLevel >10) {
        for (int i =0; i < 2 ; ++i) {
            pwrLightOn(1);
            usleep(100000 * 2); //Sleeps for two seconds
            pwrLightOff(1);
            usleep(100000 * 2); //Sleeps for two seconds
        }
        cout << "Battery Level is at: "<<batteryLevel<<endl;
        handleBatteryLow(); //End session if running, and continue blinking for a short period while ending session
    }
}

/* --------------------------------START OF SLOTS--------------------------------- */

void MainWindow:: handlePowerPress() {
    // turn on device
    if (!powerStatus) {
        int te = powerHoldTimer.elapsed();
        if (te > 1000) {
            cout << "Turning on device" << endl;
            togglePowerStatus();
            return;
        }

    }

    else {
        int te = powerHoldTimer.elapsed();
        if (te > 1000) {
            cout << "Turning off device" << endl;
            togglePowerStatus();
            return;
        }

        // Cycle through the session groups, since the only difference between the groups is duration, only the durations vector will be cycled through
        // If the end of the array is reached, set index back to 0
        else if (curSessionGroupIndex == 2) {
            curSessionGroupIndex = 0;
            curDuration = durations[curSessionGroupIndex]; // Set current duration accordingly

            // disable mode change button
            ui->modeButton->setEnabled(false);
        }
        // Else, increment the index to reach the next duration, which indicates the next session group
        else {
            curSessionGroupIndex += 1;
            curDuration = durations[curSessionGroupIndex]; // Set current duration accordingly

            // disable mode change button
            ui->modeButton->setEnabled(false);
        }

        // If the User Designated Group is chosen, allow the user to choose a custom duration, session frequency type and ces mode
        if (curSessionGroupIndex == 2) {
           // DO SOMETHING
           // enable mode change button
           ui->modeButton->setEnabled(true);
        }

        // Update the UI to reflect changes
        updateSessionsMenu();

        qInfo("Session Group: %i", curSessionGroupIndex);
    }
}

void MainWindow:: handleDownPress() {
    // Cycle through the sessions, since sessions and session frequency types are one and the same, we will cycle through the session
    // frequency types icons
    // If index = 0 is reached, reset index back to 3

    // if current duration is user-defined, the options to change frequency available
    if (curSessionGroupIndex == 2) {
        if (curFrequencyIndex == 0) {
            curFrequencyIndex = 3;
        }
        // Else, decrement the index to reach the next session
        else {
            curFrequencyIndex -= 1;
        }
        // Update the UI to reflect changes
        updateSessionsMenu();

        qInfo("Frequency: %i", curFrequencyIndex);
    }

    // if current duration is not user-defined
    else {
        if (curSessionIndex == 0) {
            curSessionIndex = 3;
        }
        // Else, decrement the index to reach the next session
        else {
            curSessionIndex -= 1;
        }
        // Update the UI to reflect changes
        updateSessionsMenu();

        qInfo("Pre-defined session: %i", curSessionIndex);
    }
}

void MainWindow:: handleUpPress() {
    // Cycle through the sessions, since sessions and session frequency types are one and the same, we will cycle through the session
    // frequency types icons
    // If index = 3 is reached, reset index back to 0

    // if current duration is user-defined, the options to change frequency available
    if (curSessionGroupIndex == 2) {
        if (curFrequencyIndex == 3) {
            curFrequencyIndex = 0;
        }
        // Else, decrement the index to reach the next session
        else {
            curFrequencyIndex += 1;
        }
        // Update the UI to reflect changes
        updateSessionsMenu();

        qInfo("Frequency: %i", curFrequencyIndex);
    }

    // if current duration is not user-defined
    else {
        if (curSessionIndex == 3) {
            curSessionIndex = 0;
        }
        // Else, decrement the index to reach the next session
        else {
            curSessionIndex += 1;
        }
        // Update the UI to reflect changes
        updateSessionsMenu();

        qInfo("Pre-defined session: %i", curSessionIndex);
    }
}

void MainWindow:: handleSelectPress() {
    // DO SOMETHING
    //Either start session or choose behaviour depending on mode
    startSession();
}



void MainWindow:: handleBatteryLow() {


    //End session if session running, if during a session continuously keep calling the function///Continue blinking as well while ending session
}

void MainWindow::handleAddProfilePress()
{
    UserProfile* newUser;
    //Create user
    createUser(ui->nameInput->text().toStdString(), &newUser);
    users.push_back(newUser);

    cout <<"Profile: " << newUser->getUsername() << " Added." <<endl;
    //Add profile to profileSelector
    updateView();
}

void MainWindow::handleModePress() {
    // if current duration/session group is user-defined
    if (curSessionGroupIndex == 2) {
        switch (curModeIndex) {
        case 0: curModeIndex = 1; break;
        case 1: curModeIndex = 0; break;
        }
    }

    updateModeUI();
}

void MainWindow::updatePerSecond() {
    if (sessionTimer.isActive()) {
        int rt = sessionTimer.remainingTime() / 1000;

        QString rtStr = QString::number(rt) + ":00";
        ui->remainTimeN->setText(rtStr);
        qDebug() << "Remaining time: " << rtStr;

    }
}

void MainWindow::handlePowerHold() {
    powerHoldTimer.start();
}

/* ---------------------------------END OF SLOTS--------------------------- */






/* ---------------------------------UI UPDATES----------------------------- */

void MainWindow::updateView() {

    ui->profileSelector->clear(); //Clears Previous Values

    for (int i = 0; i < int(users.size()); ++i) {
        string temp = users.at(i)->getUsername();
        ui->profileSelector->addItem(QString::fromStdString(temp));
    }

}

void MainWindow::updateModeUI() {
    // user-defined session group, so they can change mode
    if (curSessionGroupIndex == 2) {
        if(curModeIndex == 0) {
            ui->shortPulse->setStyleSheet("image : url(:/pulses/Short_pulse_green.png)");
            ui->longPulse->setStyleSheet("image : url(:/pulses/Long_pulse.png)");
        }
        else {
            ui->longPulse->setStyleSheet("image : url(:/pulses/Long_pulse_green.png)");
            ui->shortPulse->setStyleSheet("image : url(:/pulses/Short_pulse.png)");
        }
    }

    // if session group is pre-defined
    else {
        switch (curSessionIndex) {
        case 0: {ui->shortPulse->setStyleSheet("image : url(:/pulses/Short_pulse_green.png)");
                ui->longPulse->setStyleSheet("image : url(:/pulses/Long_pulse.png)");} break;
        case 1: {ui->longPulse->setStyleSheet("image : url(:/pulses/Long_pulse_green.png)");
                ui->shortPulse->setStyleSheet("image : url(:/pulses/Short_pulse.png)");} break;
        case 2: {ui->shortPulse->setStyleSheet("image : url(:/pulses/Short_pulse_green.png)");
                ui->longPulse->setStyleSheet("image : url(:/pulses/Long_pulse.png)");} break;
        case 3: {ui->shortPulse->setStyleSheet("image : url(:/pulses/Short_pulse_green.png)");
                ui->longPulse->setStyleSheet("image : url(:/pulses/Long_pulse.png)");} break;
        }
    }

    ui->shortPulse->repaint();
    ui->longPulse->repaint();
}

void MainWindow:: updateSessionsMenu() {
    // Update UI when cycling through session groups
    allSessionGroupLightOff();
    switch (curSessionGroupIndex) {
        case 0: groupTwentyMinLightOn(); break;
        case 1: groupFortyFiveMinLightOn(); break;
        case 2: groupUserDesignatedLightOn(); break;
    }

    // Update UI when cycling through sessions (i.e. session frequency types)
    allFrequencyLightOff();

    // if current duration is user-defined, change light according to user-selected frequency and turn off number light of current session type
    if (curSessionGroupIndex == 2) {
        pwrLightOff(curSessionIndex+1);
        switch (curFrequencyIndex) {
            case 0: sessionMETLightOn(); break;
            case 1: sessionSDeltaLightOn(); break;
            case 2: sessionDeltaLightOn(); break;
            case 3: sessionThetaLightOn(); break;
        }
    }

    // if current duration is pre-defined, change light according to pre-defined session frequency
    else {
        switch (curSessionIndex) {
        case 0: {pwrLightOn(1); pwrLightOff(2); pwrLightOff(3); pwrLightOff(4); sessionMETLightOn();} break;
        case 1: {pwrLightOn(2); pwrLightOff(1); pwrLightOff(3); pwrLightOff(4); sessionSDeltaLightOn();} break;
        case 2: {pwrLightOn(3); pwrLightOff(2); pwrLightOff(1); pwrLightOff(4); sessionDeltaLightOn();} break;
        case 3: {pwrLightOn(4); pwrLightOff(2); pwrLightOff(3); pwrLightOff(1); sessionThetaLightOn();} break;
        }
    }

    updateModeUI();
}

// Functions for Session Group and Session Numbers UI changes:
void MainWindow::groupTwentyMinLightOn() {
    ui->twentyMinLabel->setStyleSheet("color: #e5e400;");
    ui->twentyMinLabel->repaint();
}

void MainWindow::groupFortyFiveMinLightOn() {
    ui->fortyFiveMinLabel->setStyleSheet("color: #e5e400");
    ui->fortyFiveMinLabel->repaint();
}

void MainWindow::groupUserDesignatedLightOn() {
    ui->userDesignatedLabel->setStyleSheet("color: #e5e400;");
    ui->userDesignatedLabel->repaint();
}

void MainWindow::allSessionGroupLightOff() {
    ui->twentyMinLabel->setStyleSheet("color: grey");
    ui->twentyMinLabel->repaint();

    ui->fortyFiveMinLabel->setStyleSheet("color: grey");
    ui->fortyFiveMinLabel->repaint();

    ui->userDesignatedLabel->setStyleSheet("color: grey");
    ui->userDesignatedLabel->repaint();
}

void MainWindow::sessionMETLightOn() {
    ui->METLabel->setStyleSheet("color: #00ed00");
    ui->METLabel->repaint();
}

void MainWindow::sessionSDeltaLightOn() {
    ui->sDeltaLabel->setStyleSheet("color: #00ed00");
    ui->sDeltaLabel->repaint();
}

void MainWindow::sessionDeltaLightOn() {
    ui->deltaLabel->setStyleSheet("color: #00ed00");
    ui->deltaLabel->repaint();
}

void MainWindow::sessionThetaLightOn() {
    ui->thetaLabel->setStyleSheet("color: #00ed00");
    ui->thetaLabel->repaint();
}

void MainWindow::allFrequencyLightOff() {
    ui->METLabel->setStyleSheet("color: grey");
    ui->METLabel->repaint();

    ui->sDeltaLabel->setStyleSheet("color: grey");
    ui->sDeltaLabel->repaint();

    ui->deltaLabel->setStyleSheet("color: grey");
    ui->deltaLabel->repaint();

    ui->thetaLabel->setStyleSheet("color: grey");
    ui->thetaLabel->repaint();
}

void MainWindow:: changeButtonStyles(QPushButton* btn, QEvent* event){
    if(event->type() == QEvent::Enter){
         btn->setStyleSheet("color: #e5e400;"
                                      "border: 0.2em solid #e6faf8;"
                                      "min-height: 3em;"
                                      "max-height: 3em;"
                                      "min-width: 3em;"
                                      "max-width: 3em;"
                                      "border-radius: 1.5em;");

    }
    else if(event->type() == QEvent::Leave){
        btn->setStyleSheet("color: #e5e400;"
                                     "border: 0.2em solid #80c3bf;"
                                     "min-height: 3em;"
                                     "max-height: 3em;"
                                     "min-width: 3em;"
                                     "max-width: 3em;"
                                     "border-radius: 1.5em;");

   }
}

void MainWindow::toggleButtonState(bool state) {
    ui->upButton->setEnabled(state);
    ui->downButton->setEnabled(state);
    ui->selectButton->setEnabled(state);
    ui->tabWidget->setEnabled(state);
    ui->modeButton->setEnabled(state);
}

void MainWindow::greenLightOn(){
    ui->pwrLight->setStyleSheet("background-color: #00ed00");
    ui->pwrLight->repaint();
}

void MainWindow::greenLightOff(){
    ui->pwrLight->setStyleSheet("color: black");
    ui->pwrLight->repaint();
}

bool MainWindow:: eventFilter(QObject* obj, QEvent* event){
    if(obj == (QObject*)ui->pwrButton){
        changeButtonStyles(ui->pwrButton, event);
    }
    else if(obj == (QObject*)ui->upButton){
        changeButtonStyles(ui->upButton, event);
    }
    else if(obj == (QObject*)ui->downButton){
        changeButtonStyles(ui->downButton, event);
    }
    else if(obj == (QObject*)ui->selectButton){
        changeButtonStyles(ui->selectButton, event);
    }
    return QWidget::eventFilter(obj, event);
}
