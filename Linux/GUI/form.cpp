#include "form.h"
#include "ui_form.h"
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
using namespace std;

vector<string> split(const string& str, const string& delim);
Switch* switch1 ;
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    QHBoxLayout layout;
    ui->widget->setLayout(&layout);
    switch1 = new Switch("Select the edge threshold manually",0);
    connect(switch1,SIGNAL(stateChanged(int)),this,SLOT(stateChanged(int)));
    layout.addWidget(switch1);
    ui->widget->resize(400,35);
    //    ui->widget->setStyleSheet("QWidget{background-image: url(:/new/prefix1/pf-misctexture01-beer-000_5.jpg);}");
    //    cout<<"chech:"<<switch1->checkState()<<endl;
    //    connect(&new_options, SIGNAL(sendSignal()), this, SLOT(setSlots()));

}

Form::~Form()
{
    delete ui;
}
QString fileName;
vector<string> file_name;

void Form::on_loadPDB_clicked()
{

    fileName = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;

    }
    file_name=split(fileName.toStdString(),"/");
    ui->reading->setText("Loading:" +QString::fromStdString(file_name.at(file_name.size()-1)));
    ui->reading->setGeometry(30,90,0,0);
    ui->reading->adjustSize();
    file.close();

}

void Form::on_submit_clicked(){
    //read input residues
    QString input_str = ui->input->toPlainText();
    //read number of outputs
    string nOfOutputs = ui->n_outputs->toPlainText().toStdString();
    //read matching edge thereshold
    string match_edge_thereshold="1";
    if(ui->edge_match->toPlainText()!="")
        match_edge_thereshold = ui->edge_match->toPlainText().toStdString();
    //edge_graph_thereshold

    bool useCH=true;
    string useCHstr;
    int edge_graph_thereshold=-1;
    //read convexhull state
    useCH=ui->useCH->checkState();
    if (useCH)
        useCHstr="true";
    else
        useCHstr="false";
    if(stateOfSwitch!=0){
        if(ui->edge_graph->toPlainText()!= ""){
            edge_graph_thereshold=ui->edge_graph->toPlainText().toInt();
            if (7>edge_graph_thereshold || edge_graph_thereshold>15)
            {
                QMessageBox messageBox;
                messageBox.critical(0,"Error","The edge thereshold is not between 7 and 15");
                messageBox.setFixedSize(500,200);
                return;
            }
        }else{
            edge_graph_thereshold=-1;
            ui->edge_graph->setText("15");
        }
    }
    int selected_thereshold=15;
    try{
    To_Graph to_graph(fileName.toStdString(),input_str.toStdString(),edge_graph_thereshold,&selected_thereshold);

    //    cout << input_str.toStdString()<<endl;
    //    string command = "/home/niloufar/eclipse-workspace/OneAgainstAll/Debug/OneAgainstAll "+file_name.at(file_name.size()-1).substr(0,4)+".sub.grf "+nOfOutputs+" "+ input_str.toStdString()+" "+useCHstr+" "+;
    QMovie *movie = new QMovie("ajax-loader2.gif");
    ui->proglabel->setMovie(movie);
    ui->proglabel->setAlignment(Qt::AlignCenter);
    ui->proglabel->show();
    movie->start();

    string command = "./OneAgainstAll "+file_name.at(file_name.size()-1).substr(0,4)+".sub.grf "+nOfOutputs+" "+ input_str.toStdString()+ " "+useCHstr+" "+match_edge_thereshold +" "+to_string(selected_thereshold);
    system(command.c_str());
    movie->stop();
    ui->proglabel->hide();
    Result *result;
    result = new Result(this);
    result->setModal(true);
    result->show();
    }catch (int a) {
        if(a!=1){
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Something went wrong!");
        messageBox.setFixedSize(500,200);}
        else
            std::cerr << "Selected residues were not acceptable! "<< '\n';

}



}
//split the input string(index of selected residues)
vector<string> split(const string& str, const string& delim) {
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do {
        pos = str.find(delim, prev);
        if (pos == string::npos)
            pos = str.length();
        string token = str.substr(prev, pos - prev);
        if (!token.empty())
            tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}

void Form::on_open_list_clicked()
{
//    cout<<"pushed"<<endl;
    QStringList options;
    Parser myParser(fileName.toStdString());
    PDB myPDB(myParser);
    if(myPDB.getNumberOfAminos()==0){
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Problem with PDB file");
        messageBox.setFixedSize(500,200);
    }else{
        for (int i = 0; i < myPDB.getNumberOfAminos(); i++) {
            string amino = myPDB.getAllAminos(i);
            //        cout<<amino<<" "<<myPDB.aminosChain.at(i)<<myPDB.aminosNumber.at(i)<<endl;
            options.push_back(QString::fromStdString(to_string(myPDB.aminosNumber.at(i))+myPDB.aminosChain.at(i)+" "+amino));
        }

        CustomDialog cd(0,options);

        connect(&cd,SIGNAL(setText(QString)),this,SLOT(setText(QString)));

        //    cd.set_options(options);
        cd.setModal(true);
        cd.exec();}
}
void Form::setText(QString options){
    ui->input->setText(options);
}
void Form::stateChanged(int state){
//    cout<<state<<endl;
    if(state==0){
        ui->edge_graph->setText("15");
        ui->edge_graph->setDisabled(true);
        stateOfSwitch =0;
    }
    else{
        ui->edge_graph->setDisabled(false);
        stateOfSwitch=1;

    }
}
