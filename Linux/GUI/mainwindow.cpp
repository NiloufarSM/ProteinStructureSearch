#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "form2.h"
#include "form.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //    ui->centralwidget->setStyleSheet("QWidget {background-image: url(:/new/prefix1/blue-background.jpg);}");
    ui->tabWidget->addTab(new Form(),"Protein against DB");
//    ui->tabWidget->addTab(new Form2(),"Protein against Proein");
    setStyleSheet("MainWindow {background-image: url(:/new/prefix1/blue-background.jpg);}");
    //     ui->tabWidget->setStyleSheet("background-image: url(:/new/prefix1/pf-misctexture01-beer-000_5.jpg);");
}

MainWindow::~MainWindow()
{
    delete ui;


}

