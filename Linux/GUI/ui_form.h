/********************************************************************************
** Form generated from reading UI file 'form.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_H
#define UI_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QTextEdit *textEdit_2;
    QTextEdit *input;
    QPushButton *submit;
    QLabel *reading;
    QTextEdit *PDBText;
    QPushButton *loadPDB;
    QWidget *widget;
    QLabel *label;
    QTextEdit *edge_graph;
    QCheckBox *useCH;
    QTextEdit *n_outputs;
    QLabel *label_2;
    QTextEdit *edge_match;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *proglabel;
    QPushButton *open_list;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(644, 859);
        textEdit_2 = new QTextEdit(Form);
        textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));
        textEdit_2->setGeometry(QRect(30, 320, 471, 81));
        textEdit_2->setReadOnly(true);
        input = new QTextEdit(Form);
        input->setObjectName(QString::fromUtf8("input"));
        input->setGeometry(QRect(30, 400, 471, 31));
        submit = new QPushButton(Form);
        submit->setObjectName(QString::fromUtf8("submit"));
        submit->setGeometry(QRect(220, 470, 89, 25));
        reading = new QLabel(Form);
        reading->setObjectName(QString::fromUtf8("reading"));
        reading->setGeometry(QRect(0, 0, 9, 17));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(reading->sizePolicy().hasHeightForWidth());
        reading->setSizePolicy(sizePolicy);
        reading->setWordWrap(true);
        PDBText = new QTextEdit(Form);
        PDBText->setObjectName(QString::fromUtf8("PDBText"));
        PDBText->setGeometry(QRect(30, 30, 311, 31));
        QFont font;
        font.setPointSize(8);
        PDBText->setFont(font);
        PDBText->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 229, 255);"));
        PDBText->setReadOnly(true);
        loadPDB = new QPushButton(Form);
        loadPDB->setObjectName(QString::fromUtf8("loadPDB"));
        loadPDB->setGeometry(QRect(360, 30, 109, 25));
        widget = new QWidget(Form);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(30, 130, 311, 21));
        widget->setFont(font);
        widget->setAutoFillBackground(false);
        widget->setStyleSheet(QString::fromUtf8("background-color: rgba(191, 64, 64, 0);"));
        label = new QLabel(Form);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 170, 211, 31));
        QFont font1;
        font1.setPointSize(9);
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8(""));
        label->setMargin(3);
        label->setIndent(1);
        edge_graph = new QTextEdit(Form);
        edge_graph->setObjectName(QString::fromUtf8("edge_graph"));
        edge_graph->setEnabled(false);
        edge_graph->setGeometry(QRect(250, 170, 61, 31));
        useCH = new QCheckBox(Form);
        useCH->setObjectName(QString::fromUtf8("useCH"));
        useCH->setGeometry(QRect(30, 210, 141, 21));
        useCH->setFont(font1);
        useCH->setAutoFillBackground(false);
        useCH->setTristate(false);
        n_outputs = new QTextEdit(Form);
        n_outputs->setObjectName(QString::fromUtf8("n_outputs"));
        n_outputs->setGeometry(QRect(180, 240, 41, 31));
        n_outputs->setFont(font);
        label_2 = new QLabel(Form);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 240, 141, 31));
        label_2->setFont(font1);
        label_2->setMargin(3);
        label_2->setIndent(1);
        edge_match = new QTextEdit(Form);
        edge_match->setObjectName(QString::fromUtf8("edge_match"));
        edge_match->setGeometry(QRect(390, 280, 71, 31));
        label_3 = new QLabel(Form);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(30, 280, 351, 31));
        label_3->setFont(font1);
        label_3->setMargin(3);
        label_3->setIndent(1);
        label_4 = new QLabel(Form);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(30, 440, 271, 21));
        label_4->setFont(font1);
        label_4->setMargin(3);
        label_4->setIndent(1);
        proglabel = new QLabel(Form);
        proglabel->setObjectName(QString::fromUtf8("proglabel"));
        proglabel->setGeometry(QRect(390, 160, 121, 91));
        open_list = new QPushButton(Form);
        open_list->setObjectName(QString::fromUtf8("open_list"));
        open_list->setGeometry(QRect(285, 440, 41, 20));
        open_list->setFont(font1);
        open_list->setStyleSheet(QString::fromUtf8("background-color: rgba(226, 244, 244, 12);\n"
"color: rgb(0, 0, 255);"));
        textEdit_2->raise();
        input->raise();
        submit->raise();
        reading->raise();
        PDBText->raise();
        loadPDB->raise();
        widget->raise();
        label->raise();
        edge_graph->raise();
        useCH->raise();
        n_outputs->raise();
        label_2->raise();
        edge_match->raise();
        label_3->raise();
        label_4->raise();
        open_list->raise();
        proglabel->raise();

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        textEdit_2->setHtml(QCoreApplication::translate("Form", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt;\">Write your selected residues:</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt;\">example:</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt;\">12A,43B,44B,45B,23C</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span s"
                        "tyle=\" font-size:9pt;\">(At least 4 residues, At most 10 residues)</span></p></body></html>", nullptr));
        submit->setText(QCoreApplication::translate("Form", "Submit", nullptr));
        reading->setText(QString());
        PDBText->setHtml(QCoreApplication::translate("Form", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">Please select your PDB: </span></p></body></html>", nullptr));
        loadPDB->setText(QCoreApplication::translate("Form", "LoadPDB", nullptr));
        label->setText(QCoreApplication::translate("Form", "Edge threshold(Between7-15):", nullptr));
        edge_graph->setHtml(QCoreApplication::translate("Form", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">15</p></body></html>", nullptr));
        useCH->setText(QCoreApplication::translate("Form", "Use ConvexHull", nullptr));
        n_outputs->setHtml(QCoreApplication::translate("Form", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt;\">100</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("Form", "Number of outputs:", nullptr));
        edge_match->setHtml(QCoreApplication::translate("Form", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt;\">1</span></p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("Form", "Enter edge threshold for matching (Between 0.1,1):", nullptr));
        label_4->setText(QCoreApplication::translate("Form", "Or select from the list of residues from ", nullptr));
        proglabel->setText(QString());
        open_list->setText(QCoreApplication::translate("Form", "here", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
