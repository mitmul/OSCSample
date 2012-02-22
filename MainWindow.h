#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include "OSCSender.h"
#include <lo.h>

using namespace boost;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_OSCSend_clicked();

    void on_pushButton_SendOSC_lo_clicked();

private:
    bool isInt32_t(string s);
    bool isFloat(string s);

    Ui::MainWindow *ui;
    OSCSender sender;

};

#endif // MAINWINDOW_H
