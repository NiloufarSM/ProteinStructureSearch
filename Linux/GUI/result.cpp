#include "result.h"
#include "ui_result.h"
#include<QFile>
#include<QMessageBox>
#include<QTextStream>
#include<QTableWidget>
#include<QTableWidgetItem>
#include<iostream>
Result::Result(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Result)
{
    ui->setupUi(this);
    //    QTableWidget *tableWidget=new QTableWidget(this);
    QFile file("output.txt");
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","No Results found");
        messageBox.setFixedSize(500,200);
        return;
    }else{

        QTextStream instream (&file);
        QString line;
        QList< QStringList > lists;
        do {
            line = instream.readLine();
            lists << line.split("\t");
            std::cout<<line.toStdString()<<std::endl;
        } while (!line.isNull() && !line.isEmpty());
        // Set the table size (assuming the rows are all the same length).
        ui->tableWidget->setRowCount( lists.size()-1 );
        ui->tableWidget->setColumnCount( 5 );
        QStringList s;
        s << "PDBID_Target";
        s << "Matched Residues";
        s << "Score";
        s << "RMSD";
        s << "TM_Score";
//        std::cout<<"here"<<std::endl;
        ui->tableWidget->setHorizontalHeaderLabels(s);
        for ( int row = 0; row < lists.size()-1; ++row ) {
//            std::cout<<"or there"<<std::endl;
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(lists[row][0]));
//            QString str="";
//            int count =1 ;
//            for (int i=2; i<lists[row].size()-1;i++){
//                str.append(lists[row][i]);
//                if (count==2){
//                    str.append(", ");
//                    i+=2;
//                    count=0;
//                }else
//                    str.append(" ");
//                count++;
//            }
//            str.remove(str.size()-2,2);
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(lists[row][1]));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(lists[row][2]));
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(lists[row][3]));
            ui->tableWidget->setItem(row, 4, new QTableWidgetItem(lists[row][4]));

        }
    }
}
Result::~Result()
{
    delete ui;
}
