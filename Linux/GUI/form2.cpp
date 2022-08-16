#include "form2.h"

using namespace std;

vector<string> split2(const string& str, const string& delim);
Form2::Form2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form2)
{
    ui->setupUi(this);
    QHBoxLayout layout;
    ui->widget->setLayout(&layout);
    ui->reading->setVisible(false);
    ui->reading_2->setVisible(true);

    switch1 = new Switch("Select the edge threshold manually",0);
    connect(switch1,SIGNAL(stateChanged(int)),this,SLOT(stateChanged(int)));
    layout.addWidget(switch1);
    ui->widget->resize(400,35);
//    ui->widget->setStyleSheet("QWidget{background-image: url(:/new/prefix1/pf-misctexture01-beer-000_5.jpg);}");
    //    cout<<"chech:"<<switch1->checkState()<<endl;
    //    connect(&new_options, SIGNAL(sendSignal()), this, SLOT(setSlots()));

}

Form2::~Form2()
{
    delete ui;
}

void Form2::on_loadPDB_clicked()
{

    fileName = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;

    }
    file_name=split2(fileName.toStdString(),"/");
    ui->reading->setVisible(true);
    ui->reading->setText("Loading:" +QString::fromStdString(file_name.at(file_name.size()-1)));
    ui->reading->setGeometry(30,70,0,0);
    ui->reading->adjustSize();
    file.close();

}

void Form2::on_submit_clicked(){
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
    if(stateOfSwitch!=0)
        if(ui->edge_graph->toPlainText()!= "")
            edge_graph_thereshold=ui->edge_graph->toPlainText().toFloat();
        else{
            edge_graph_thereshold=-1.0;
            ui->edge_graph->setText("15");
        }
    int selected_thereshold=15;

    To_Graph to_graph(fileName.toStdString(),input_str.toStdString(),edge_graph_thereshold,&selected_thereshold);
    To_Graph to_graph2(fileName2.toStdString(),edge_graph_thereshold);

    //    cout << input_str.toStdString()<<endl;
    //    string command = "/home/niloufar/eclipse-workspace/OneAgainstAll/Debug/OneAgainstAll "+file_name.at(file_name.size()-1).substr(0,4)+".sub.grf "+nOfOutputs+" "+ input_str.toStdString()+" "+useCHstr+" "+;
    QMovie *movie = new QMovie("ajax-loader2.gif");
    ui->proglabel->setMovie(movie);
    ui->proglabel->setAlignment(Qt::AlignCenter);
    ui->proglabel->show();
    movie->start();

    string command = "./OneAgainstOne "+file_name.at(file_name.size()-1).substr(0,4)+".sub.grf "+nOfOutputs+" "+ input_str.toStdString()+ " "+useCHstr+" "+match_edge_thereshold+" "+to_string(selected_thereshold);
    system(command.c_str());
    movie->stop();
    ui->proglabel->hide();
    Result *result;
    result = new Result(this);
    result->setModal(true);
    result->show();



}
//split the input string(index of selected residues)
vector<string> split2(const string& str, const string& delim) {
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

void Form2::on_open_list_clicked()
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
void Form2::setText(QString options){
    ui->input->setText(options);
}
void Form2::stateChanged(int state){
//    cout<<state<<endl;
    if(state==0){
        ui->edge_graph->setText("15");
        ui->edge_graph->setDisabled(true);}
    else{
        ui->edge_graph->setDisabled(false);

    }
}

void Form2::on_loadPDB_2_clicked()
{
    fileName2 = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(fileName2);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;

    }
    file_name2=split2(fileName2.toStdString(),"/");
    ui->reading_2->setVisible(true);
    ui->reading_2->setText("Loading:" +QString::fromStdString(file_name2.at(file_name2.size()-1)));
    ui->reading_2->setGeometry(30,140,0,0);
    ui->reading_2->adjustSize();
    file.close();
}
