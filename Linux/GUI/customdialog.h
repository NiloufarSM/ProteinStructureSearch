#ifndef CUSTOMDIALOG_H
#define CUSTOMDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QListView>
#include <QPushButton>
#include "customlistmodel.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QMessageBox>

class CustomDialog : public QDialog
{
    Q_OBJECT

public:
    static QStringList empty;
    CustomDialog(QWidget *parent = 0,QStringList options=empty);
signals:
    void setText(QString options);
public slots:
    void save();

private:
    CustomListModel* model;
    QListView* view;
    QDialogButtonBox* buttonBox;
    QGroupBox* viewBox;
    QPushButton* saveButton;
    QPushButton* closeButton;

    void createListModelView();
    void createOtherWidgets();
    void createLayout();
    void createConnections();

};

#endif // CUSTOMDIALOG_H
