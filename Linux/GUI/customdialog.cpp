#include "customdialog.h"
QStringList strList;

CustomDialog::CustomDialog(QWidget *parent,QStringList options): QDialog(parent)
{
    strList=options;
    setWindowTitle("Checkable list in Qt");
    createListModelView();
    createOtherWidgets();
    createLayout();
    createConnections();
}
void CustomDialog::createListModelView(){
    view = new QListView;
    model = new CustomListModel;
    view->setModel(model);


//    strList << "monitor" << "mouse" << "keyboard" << "hard disk drive"
//            << "graphic card" << "sound card" << "memory" << "motherboard";

    model->setStringList(strList);
}

void CustomDialog::createOtherWidgets(){
    viewBox = new QGroupBox(tr("Required componenCheckable list modelts"));
    buttonBox = new QDialogButtonBox;
    saveButton = buttonBox->addButton(QDialogButtonBox::Save);
    closeButton = buttonBox->addButton(QDialogButtonBox::Close);

}

void CustomDialog::createLayout(){
    QVBoxLayout* viewLayout = new QVBoxLayout;
    viewLayout->addWidget(view);
    viewBox->setLayout(viewLayout);

    QHBoxLayout* horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(buttonBox);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(viewBox);
    mainLayout->addLayout(horizontalLayout);

    setLayout(mainLayout);
}

void CustomDialog::createConnections(){
    QObject::connect(saveButton, SIGNAL(clicked()), this, SLOT(save()));
    QObject::connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

}

void CustomDialog::save(){
    model->save();
    QString str= model->get_data();
    QMessageBox::information(this, tr("Selected Residues"),
                                   str,
                                    QMessageBox::Ok);
    emit setText(str);
}
