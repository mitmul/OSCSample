#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_OSCSend_clicked()
{
    string host = ui->lineEdit_HostIP->text().toStdString();
    int port = ui->lineEdit_Port->text().toInt();
    sender.setServer(host, port);

    QStringList msg = ui->lineEdit_Message->text().split(" ");
    sender.setAddress(msg.at(0).toStdString());

    for(int i = 1; i < msg.size(); ++i)
    {
        string arg = msg.at(i).toStdString();
        if(isInt32_t(arg))
        {
            sender.addInt(lexical_cast<int32_t>(arg));
            cout << "i";
        }
        else if(isFloat(arg))
        {
            sender.addFloat(lexical_cast<float>(arg));
            cout << "f";
        }
        else
        {
            sender.addString(arg); cout << "s";
        }
    }
    cout << endl;

    sender.send();
}

bool MainWindow::isInt32_t(string s)
{
    istringstream iss(s);
    int32_t dummy;
    iss >> noskipws >> dummy;

    return iss && iss.eof();
}

bool MainWindow::isFloat(string s)
{
    istringstream iss(s);
    float dummy;
    iss >> noskipws >> dummy;

    return iss && iss.eof();
}

void MainWindow::on_pushButton_SendOSC_lo_clicked()
{
    string host = ui->lineEdit_HostIP_lo->text().toStdString();
    int port = ui->lineEdit_Port_lo->text().toInt();
    sender.setServer(host, port);

    QStringList msg = ui->lineEdit_Message_lo->text().split(" ");
    sender.setAddress(msg.at(0).toStdString());

    for(int i = 1; i < msg.size(); ++i)
    {
        string arg = msg.at(i).toStdString();
        if(isInt32_t(arg))
            sender.addInt(lexical_cast<int32_t>(arg));
        else if(isFloat(arg))
            sender.addFloat(lexical_cast<float>(arg));
        else
            sender.addString(arg);
    }

    sender.send_lo();
}
