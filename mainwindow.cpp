#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAction>
#include <QMenuBar>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    currentAction(NoAction),
    isEmpty(true)
{
    ui->setupUi(this);

    bar1 = new QLabel("State");
    bar2 = new QLabel("Bar2");
    statusBar()->addWidget(bar1);
    statusBar()->addWidget(bar2, 1);
    bar1->show();
    bar2->show();
    showMessage("Designed by QHD", 5000);

    // Function realize
    // Basic function
    connect(ui->btn_AC, SIGNAL(clicked(bool)), this, SLOT(clear()));
    connect(ui->btn_reverse, SIGNAL(clicked(bool)), this, SLOT(reverseClicked()));
    connect(ui->btn_percent, SIGNAL(clicked(bool)), this, SLOT(percentageClicked()));
    connect(ui->btn_dot, SIGNAL(clicked(bool)), this, SLOT(dotClicked()));
    connect(ui->btn_equal, SIGNAL(clicked(bool)), this, SLOT(equalClicked()));

    // Operation
    connect(ui->btn_add, SIGNAL(clicked(bool)), this, SLOT(actionChanged()));
    connect(ui->btn_sub, SIGNAL(clicked(bool)), this, SLOT(actionChanged()));
    connect(ui->btn_mult, SIGNAL(clicked(bool)), this, SLOT(actionChanged()));
    connect(ui->btn_div, SIGNAL(clicked(bool)), this, SLOT(actionChanged()));

    // Number
    connect(ui->Num_0, SIGNAL(clicked(bool)), this, SLOT(inputNumber()));
    connect(ui->Num_1, SIGNAL(clicked(bool)), this, SLOT(inputNumber()));
    connect(ui->Num_2, SIGNAL(clicked(bool)), this, SLOT(inputNumber()));
    connect(ui->Num_3, SIGNAL(clicked(bool)), this, SLOT(inputNumber()));
    connect(ui->Num_4, SIGNAL(clicked(bool)), this, SLOT(inputNumber()));
    connect(ui->Num_5, SIGNAL(clicked(bool)), this, SLOT(inputNumber()));
    connect(ui->Num_6, SIGNAL(clicked(bool)), this, SLOT(inputNumber()));
    connect(ui->Num_7, SIGNAL(clicked(bool)), this, SLOT(inputNumber()));
    connect(ui->Num_8, SIGNAL(clicked(bool)), this, SLOT(inputNumber()));
    connect(ui->Num_9, SIGNAL(clicked(bool)), this, SLOT(inputNumber()));

    currentNum = "0";
    displayNumber();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::showMessage(const QString &message, int timeOut) {
    bar2->setText(message);
    QTimer *timer = new QTimer;
    timer->singleShot(timeOut, bar2, SLOT(clear()));
} // 没问题

void MainWindow::clear() {
    if (ui->btn_AC->text()=="AC"){
        currentAction = NoAction;
        currentNum = "0";
        lastNum = "0";
        isEmpty = true;
    } else {
        currentNum = "0";
        isEmpty = true;
        ui->btn_AC->setText("AC");
    }
    displayNumber();
} // 没问题

void MainWindow::actionChanged() {
    QPushButton *currentButton = qobject_cast<QPushButton *>(this->sender());

    if (currentButton) {
        isEmpty = false;
        if (currentButton == ui->btn_add) {
            currentAction = AdditionFlag;
            statusBar()->showMessage("Enter +", 3000);
        } else if (currentButton == ui->btn_sub) {
            currentAction = SubtractionFlag;
            statusBar()->showMessage("Enter -", 3000);
        } else if (currentButton == ui->btn_mult) {
            currentAction = MultiplicationFlag;
            statusBar()->showMessage("Enter ×", 3000);
        } else if (currentButton == ui->btn_div) {
            currentAction = DivisionFlag;
            statusBar()->showMessage("Enter ÷");
        } else {
            currentAction = NoAction;
        }
    }
}

void MainWindow::inputNumber() {
    QPushButton *currentButton = qobject_cast<QPushButton *>(this->sender());

    if (currentButton) {
        ui->btn_AC->setText("C");
        if (!isEmpty) {
            lastNum = currentNum;
            currentNum = "0";
            isEmpty = true;
        }
        if (currentNum == "0") currentNum.clear(); // 把零删掉

        if (currentButton == ui->Num_0) {
            currentNum.append("0");
            statusBar()->showMessage("Enter 0", 3000);
        } else if (currentButton == ui->Num_1) {
            currentNum.append("1");
            statusBar()->showMessage("Enter 1", 3000);
        } else if (currentButton == ui->Num_2) {
            currentNum.append("2");
            statusBar()->showMessage("Enter 2", 3000);
        } else if (currentButton == ui->Num_3) {
            currentNum.append("3");
            statusBar()->showMessage("Enter 3", 3000);
        } else if (currentButton == ui->Num_4) {
            currentNum.append("4");
            statusBar()->showMessage("Enter 4", 3000);
        } else if (currentButton == ui->Num_5) {
            currentNum.append("5");
            statusBar()->showMessage("Enter 5", 3000);
        } else if (currentButton == ui->Num_6) {
            currentNum.append("6");
            statusBar()->showMessage("Enter 6", 3000);
        } else if (currentButton == ui->Num_7) {
            currentNum.append("7");
            statusBar()->showMessage("Enter 7", 3000);
        } else if (currentButton == ui->Num_8) {
            currentNum.append("8");
            statusBar()->showMessage("Enter 8", 3000);
        } else if (currentButton == ui->Num_9) {
            currentNum.append("9");
            statusBar()->showMessage("Enter 9", 3000);
        }
        displayNumber();
    }
} // 没问题

void MainWindow::displayNumber() {
    ui->label->setText(currentNum);
} // 没问题

void MainWindow::reverseClicked() {
    if (!isEmpty) {
        currentNum = "0";
        isEmpty = true;
    } else {
        if (currentNum.at(0) == "-") {
            currentNum.remove(0,1);
        } else {
            currentNum.push_front("-");
        }
    }
    displayNumber();
    statusBar()->showMessage("Opposite Number", 3000);
} // 没问题

void MainWindow::percentageClicked() {
    if (!isEmpty || currentNum.size() == 0) {
        currentNum = "0";
        isEmpty = true;
    } else {
        double number = currentNum.toDouble() / 100; // 后面改为有理数字类型
        currentNum = QString::number(number);
    }
    displayNumber();
    statusBar()->showMessage("Percentage", 3000);
} // 没问题

void MainWindow::dotClicked() {
    if (!isEmpty) {
        currentNum = "0";
        isEmpty = true;
    } else if (currentNum.indexOf(".") == -1) {
        currentNum.push_back(".");
    }
    displayNumber();
    statusBar()->showMessage("Dot", 3000);
} //没问题

void MainWindow::equalClicked() {
    switch (currentAction) {
    case NoAction: {
        statusBar()->showMessage("Please enter an operation", 3000);
        return;
        break;
    } case AdditionFlag: {
        currentNum = QString::number(lastNum.toDouble() + currentNum.toDouble());
    } case SubtractionFlag: {
        currentNum = QString::number(lastNum.toDouble() - currentNum.toDouble());
    } case MultiplicationFlag: {
        currentNum = QString::number(lastNum.toDouble() * currentNum.toDouble());
    } case DivisionFlag: {
        currentNum = QString::number(lastNum.toDouble() / currentNum.toDouble());
    }
    default:
        break;
    }
    displayNumber();
    currentNum = "0";
    statusBar()->showMessage("Equal to", 3000);
}
