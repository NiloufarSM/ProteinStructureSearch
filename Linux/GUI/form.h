#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include<customdialog.h>
namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

private slots:
    void setText(QString options);
    void stateChanged(int);
    void on_loadPDB_clicked();

    void on_submit_clicked();

    void on_open_list_clicked();

private:
    Ui::Form *ui;
    QString currentFile;
    int stateOfSwitch=0;

//    CustomDialog* cd;
};

#endif // FORM_H
