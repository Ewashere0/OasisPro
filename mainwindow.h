#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

/* Constants for color scheme sampled from device for altering color outside of design mode */
#define YELLOW "#e5e400"
#define RED "#fd0002"
#define GREEN "#00ed00"
#define BLUE "#80c3bf"


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
//these aren't final
    void on_pwrButton_pressed();

    void on_pwrButton_clicked();

    void on_pwrButton_released();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
