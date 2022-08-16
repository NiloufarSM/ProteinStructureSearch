#ifndef FORM2_H
#define FORM2_H

#include <QWidget>
#include<customdialog.h>
#include "ui_form2.h"
#include "QFileDialog"
#include"QMessageBox"
#include<switch.h>
#include<To_Graph.h>
#include<iostream>
#include "Parser.h"
#include "PDB.h"
#include "Graph.h"
#include <ctype.h>
#include<result.h>
namespace Ui {
class Form2;
}

class Form2 : public QWidget
{
    Q_OBJECT

public:
    explicit Form2(QWidget *parent = nullptr);
    ~Form2();

private slots:
    void setText(QString options);
    void stateChanged(int);
    void on_loadPDB_clicked();

    void on_submit_clicked();

    void on_open_list_clicked();

    void on_loadPDB_2_clicked();

private:
    Ui::Form2 *ui;
    QString currentFile;
    int stateOfSwitch=0;
    QString fileName;
    vector<string> file_name;
    QString fileName2;
    vector<string> file_name2;
    Switch* switch1 ;


//    CustomDialog* cd;
};

#endif // FORM2_H
