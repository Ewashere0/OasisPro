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
