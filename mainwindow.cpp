#include "mainwindow.h"


using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Setting initial state of UI
    powerStatus = false;
    ui->setupUi(this);
    toggleButtonState(powerStatus);

    // Connect buttons to slot functions
    connect(ui->pwrButton, SIGNAL(released()), this, SLOT (handlePowerPress()));
    connect(ui->holdButton, SIGNAL(released()), this, SLOT (handleHoldPress()));
    connect(ui->upButton, SIGNAL(released()), this, SLOT (handleUpPress()));
    connect(ui->downButton, SIGNAL(released()), this, SLOT (handleDownPress()));
    connect(ui->selectButton, SIGNAL(released()), this, SLOT (handleSelectPress()));
    connect(ui->addProfileButton, SIGNAL(released()), this, SLOT (handleAddProfilePress()));




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
    ui->holdButton->installEventFilter(this);
    ui->upButton->installEventFilter(this);
    ui->downButton->installEventFilter(this);
    ui->selectButton->installEventFilter(this);


    // All available Session Frequency Ranges (can be used when the user wants to create a new Session in the User Designated group)
    sessionFreqRanges = {"MET", "Sub-Delta", "Delta", "Theta"};

    // All available CES Modes (can be used when the user wants to create a new Session in the User Designated group)
    cesModes = {"Short-Pulse", "50% Duty Cycle"};






    // All available Session Durations ('0' can be overriden when the user wants to create a new Session in the User Designated group)
    durations = {20, 45, 0};

    // Create the pre-defined sessions
    for (int i = 0; i < 4; i++) {
        if (i == 1) {
            Session* session = new Session(i, sessionFreqRanges[i], cesModes[1]);
            sessionTypes.push_back(session);
        }
        else {
            Session* session = new Session(i, sessionFreqRanges[i], cesModes[0]);
            sessionTypes.push_back(session);
        }
    }

    // Indexes used to cycle through different Session Groups and Sessions when the user pressed the Power or Up and Down buttons
    curSessionGroupIndex = 0;
    curSessionIndex = 0;

    // Setting current duration according to current session group selected
    curDuration = durations[curSessionGroupIndex];

    // Default intensity Level
    curIntensity = 4;

    // Default battery Level
    batteryLevel = 100;

    // Test: sessionTypes[index]
    qInfo("%s", sessionTypes[2]->getFrequency().c_str());
}

MainWindow::~MainWindow()
{
    for (int i = 0; i < sessionTypes.size(); i++) {
        delete sessionTypes[i];
    }

    delete ui;
}

//#define YELLOW "#e5e400"
//#define RED "#fd0002"
//#define GREEN "#00ed00"
//#define BLUE "#80c3bf"
void MainWindow::oneLightOn(){
    ui->oneLabel->setStyleSheet("color: #00ed00");
    ui->oneLabel->repaint();
}

void MainWindow::oneLightOff(){
    ui->oneLabel->setStyleSheet("color: grey");
    ui->oneLabel->repaint();
}

void MainWindow::twoLightOn(){
    ui->twoLabel->setStyleSheet("color: #00ed00");
    ui->twoLabel->repaint();
}

void MainWindow::twoLightOff(){
    ui->twoLabel->setStyleSheet("color: grey");
    ui->twoLabel->repaint();
}

void MainWindow::threeLightOn(){
    ui->threeLabel->setStyleSheet("color: #00ed00");
    ui->threeLabel->repaint();
}

void MainWindow::threeLightOff(){
    ui->threeLabel->setStyleSheet("color: grey");
    ui->threeLabel->repaint();
}

void MainWindow::fourLightOn(){
    ui->fourLabel->setStyleSheet("color: #e5e400");
    ui->fourLabel->repaint();
}

void MainWindow::fourLightOff(){
    ui->fourLabel->setStyleSheet("color: grey");
    ui->fourLabel->repaint();
}

void MainWindow::fiveLightOn(){
    ui->fiveLabel->setStyleSheet("color: #e5e400");
    ui->fiveLabel->repaint();
}

void MainWindow::fiveLightOff(){
    ui->fiveLabel->setStyleSheet("color: grey");
    ui->fiveLabel->repaint();
}

void MainWindow::sixLightOn(){
    ui->sixLabel->setStyleSheet("color: #e5e400");
    ui->sixLabel->repaint();
}

void MainWindow::sixLightOff(){
    ui->sixLabel->setStyleSheet("color: grey");
    ui->sixLabel->repaint();
}

void MainWindow::sevenLightOn(){
    ui->sevenLabel->setStyleSheet("color: #fd0002");
    ui->sevenLabel->repaint();
}

void MainWindow::sevenLightOff(){
    ui->sevenLabel->setStyleSheet("color: grey");
    ui->sevenLabel->repaint();
}

void MainWindow::eightLightOn(){
    ui->eightLabel->setStyleSheet("color: #fd0002");
    ui->eightLabel->repaint();
}

void MainWindow::eightLightOff(){
    ui->eightLabel->setStyleSheet("color: grey");
    ui->eightLabel->repaint();
}

void MainWindow::togglePowerStatus() {
    powerStatus = !powerStatus;
    toggleButtonState(powerStatus);
    if (powerStatus) {
        greenLightOn();
        displayBatteryLevel();
    }
    else {
        greenLightOff();
    }
}

void MainWindow::toggleButtonState(bool state) {
    ui->upButton->setEnabled(state);
    ui->downButton->setEnabled(state);
    ui->pwrButton->setEnabled(state);
    ui->selectButton->setEnabled(state);
    ui->tabWidget->setEnabled(state);
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
    else if(obj == (QObject*)ui->holdButton){
        changeButtonStyles(ui->holdButton, event);
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

void MainWindow:: promptSignIn() {
    // DO SOMETHING
    //Force users to make or select profile. Or select Guest

    //DEPRECATED
}

void MainWindow:: standby() {
    // DO SOMETHING
}

void MainWindow:: handlePowerPress() {
    // Cycle through the sessionGroupList using the index
    // If the end of the array is reached, set index back to 0

    if (curSessionGroupIndex == 2) {
        curSessionGroupIndex = 0;
        curDuration = durations[curSessionGroupIndex]; // Set current duration accordingly
    }
    // Else, increment the index to reach the next Session Group
    else {
        curSessionGroupIndex += 1;
        curDuration = durations[curSessionGroupIndex]; // Set current duration accordingly
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
    //Either start session or choose behaviour depending on mode
}

void MainWindow:: startSession() {
    // DO SOMETHING
}

void MainWindow:: displayBatteryLevel() {

    if (batteryLevel > 50) {

        for (int i =0; i < 2 ; ++i) {
            oneLightOn();
            twoLightOn();
            threeLightOn();
            usleep(100000 * 2); //Sleeps for two seconds
            oneLightOff();
            twoLightOff();
            threeLightOff();
            usleep(100000 * 2); //Sleeps for two seconds
            cout << "Battery Level is at: "<<batteryLevel<<endl;
        }
    } else if (batteryLevel > 25) {

        for (int i =0; i < 2 ; ++i) {
            oneLightOn();
            twoLightOn();
            usleep(100000 * 2); //Sleeps for two seconds
            oneLightOff();
            twoLightOff();
            usleep(100000 * 2); //Sleeps for two seconds
        }
        cout << "Battery Level is at: "<< batteryLevel << endl;
    } else if (batteryLevel >10) {
        for (int i =0; i < 2 ; ++i) {
            oneLightOn();
            usleep(100000 * 2); //Sleeps for two seconds
            oneLightOff();
            usleep(100000 * 2); //Sleeps for two seconds
        }
        cout << "Battery Level is at: "<<batteryLevel<<endl;
        handleBatteryLow(); //End session if running, and continue blinking for a short period while ending session
    }
}

void MainWindow:: updateBatteryLevel() {
    // DO SOMETHING
}

void MainWindow:: handleBatteryLow() {


    //End session if session running, if during a session continuously keep calling the function///Continue blinking as well while ending session
}

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
        fourLightOn();
        fiveLightOn();
        sixLightOn();
        usleep(100000 * 2); //Sleeps for two seconds
        fourLightOff();
        fiveLightOff();
        sixLightOff();
        usleep(100000 * 2); //Sleeps for two seconds
    }
}

void MainWindow::noConnection(){

    for (int i =0; i < 4 ; ++i) {
        sevenLightOn();
        eightLightOn();
        usleep(100000 * 2); //Sleeps for two seconds
        sevenLightOff();
        eightLightOff();
        usleep(100000 * 2); //Sleeps for two seconds
    }
    //Scroll graph up and down to show unit returning to normal voltage (15-20 seconds)
    //to be continued
}

void MainWindow::solidConnection(){
    for (int i =0; i < 4 ; ++i) {
        oneLightOn();
        twoLightOn();
        threeLightOn();
        usleep(100000 * 2); //Sleeps for two seconds
        oneLightOff();
        twoLightOff();
        threeLightOff();
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

void MainWindow::handleHoldPress()
{
    togglePowerStatus();
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

void MainWindow::updateView() {

    ui->profileSelector->clear(); //Clears Previous Values

    for (int i = 0; i < int(users.size()); ++i) {
        string temp = users.at(i)->getUsername();
        ui->profileSelector->addItem(QString::fromStdString(temp));
    }

}


/* END OF SLOTS */




