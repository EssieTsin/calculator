#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QQueue>

namespace Ui {
class MainWindow;
}

enum ActionFlag {
    NoAction,
    AdditionFlag,
    SubtractionFlag,
    MultiplicationFlag,
    DivisionFlag,
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QLabel *bar1;
    QLabel *bar2;

    ActionFlag currentAction;
    QString lastNum;
    QString currentNum;
    QString currentExp;
    bool isEmpty;

public slots:

    // ui
    void showMessage(const QString & message, int timeOut);

    // function
    void clear();
    void actionChanged();
    void inputNumber();
    void displayNumber();
    void displayExpression();
    void reverseClicked();
    void percentageClicked();
    void dotClicked();
    void equalClicked();

    // history
    //QQueue<QString> expression;

};

#endif // MAINWINDOW_H
