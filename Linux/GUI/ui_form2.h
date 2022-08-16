/********************************************************************************
** Form generated from reading UI file 'form2.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM2_H
#define UI_FORM2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form2
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
    QPushButton *loadPDB_2;
    QTextEdit *PDBText_2;
    QLabel *reading_2;

    void setupUi(QWidget *Form2)
    {
        if (Form2->objectName().isEmpty())
            Form2->setObjectName(QString::fromUtf8("Form2"));
        Form2->resize(644, 645);
        textEdit_2 = new QTextEdit(Form2);
        textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));
        textEdit_2->setGeometry(QRect(30, 371, 471, 81));
        textEdit_2->setReadOnly(true);
        input = new QTextEdit(Form2);
        input->setObjectName(QString::fromUtf8("input"));
        input->setGeometry(QRect(30, 451, 471, 31));
        submit = new QPushButton(Form2);
        submit->setObjectName(QString::fromUtf8("submit"));
        submit->setGeometry(QRect(220, 521, 89, 25));
        reading = new QLabel(Form2);
        reading->setObjectName(QString::fromUtf8("reading"));
        reading->setGeometry(QRect(0, 0, 9, 17));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(reading->sizePolicy().hasHeightForWidth());
        reading->setSizePolicy(sizePolicy);
        reading->setWordWrap(true);
        PDBText = new QTextEdit(Form2);
        PDBText->setObjectName(QString::fromUtf8("PDBText"));
        PDBText->setGeometry(QRect(30, 30, 351, 31));
        PDBText->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 229, 255);"));
        PDBText->setReadOnly(true);
        loadPDB = new QPushButton(Form2);
        loadPDB->setObjectName(QString::fromUtf8("loadPDB"));
        loadPDB->setGeometry(QRect(390, 30, 109, 25));
        widget = new QWidget(Form2);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(30, 181, 311, 21));
        QFont font;
        font.setPointSize(8);
        widget->setFont(font);
        widget->setAutoFillBackground(false);
        widget->setStyleSheet(QString::fromUtf8("background-color: rgba(191, 64, 64, 0);"));
        label = new QLabel(Form2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 221, 211, 31));
        label->setStyleSheet(QString::fromUtf8(""));
        label->setMargin(3);
        label->setIndent(1);
        edge_graph = new QTextEdit(Form2);
        edge_graph->setObjectName(QString::fromUtf8("edge_graph"));
        edge_graph->setEnabled(false);
        edge_graph->setGeometry(QRect(250, 221, 51, 31));
        useCH = new QCheckBox(Form2);
        useCH->setObjectName(QString::fromUtf8("useCH"));
        useCH->setGeometry(QRect(30, 261, 141, 21));
        useCH->setAutoFillBackground(false);
        useCH->setTristate(false);
        n_outputs = new QTextEdit(Form2);
        n_outputs->setObjectName(QString::fromUtf8("n_outputs"));
        n_outputs->setGeometry(QRect(180, 291, 51, 31));
        label_2 = new QLabel(Form2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 291, 141, 31));
        label_2->setMargin(3);
        label_2->setIndent(1);
        edge_match = new QTextEdit(Form2);
        edge_match->setObjectName(QString::fromUtf8("edge_match"));
        edge_match->setGeometry(QRect(390, 331, 51, 31));
        label_3 = new QLabel(Form2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(30, 331, 351, 31));
        label_3->setMargin(3);
        label_3->setIndent(1);
        label_4 = new QLabel(Form2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(30, 491, 271, 17));
        label_4->setMargin(3);
        label_4->setIndent(1);
        proglabel = new QLabel(Form2);
        proglabel->setObjectName(QString::fromUtf8("proglabel"));
        proglabel->setGeometry(QRect(370, 221, 151, 101));
        proglabel->setStyleSheet(QString::fromUtf8("background: transparent;"));
        open_list = new QPushButton(Form2);
        open_list->setObjectName(QString::fromUtf8("open_list"));
        open_list->setGeometry(QRect(300, 490, 31, 21));
        open_list->setStyleSheet(QString::fromUtf8("background-color: rgba(226, 244, 244, 12);"));
        loadPDB_2 = new QPushButton(Form2);
        loadPDB_2->setObjectName(QString::fromUtf8("loadPDB_2"));
        loadPDB_2->setGeometry(QRect(390, 100, 109, 25));
        PDBText_2 = new QTextEdit(Form2);
        PDBText_2->setObjectName(QString::fromUtf8("PDBText_2"));
        PDBText_2->setGeometry(QRect(30, 100, 351, 31));
        PDBText_2->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 229, 255);"));
        PDBText_2->setReadOnly(true);
        reading_2 = new QLabel(Form2);
        reading_2->setObjectName(QString::fromUtf8("reading_2"));
        reading_2->setGeometry(QRect(0, 10, 9, 17));
        sizePolicy.setHeightForWidth(reading_2->sizePolicy().hasHeightForWidth());
        reading_2->setSizePolicy(sizePolicy);
        reading_2->setWordWrap(true);

        retranslateUi(Form2);

        QMetaObject::connectSlotsByName(Form2);
    } // setupUi

    void retranslateUi(QWidget *Form2)
    {
        Form2->setWindowTitle(QCoreApplication::translate("Form2", "Form", nullptr));
        textEdit_2->setHtml(QCoreApplication::translate("Form2", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:7.8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Ubuntu'; font-size:9pt;\">Write your selected residues:</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Ubuntu'; font-size:9pt;\">example:</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Ubuntu'; font-size:9pt;\">12A,43B,44B,45B,23C</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin"
                        "-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Ubuntu'; font-size:9pt;\">(At least 4 residues, At most 10 residues)</span></p></body></html>", nullptr));
        submit->setText(QCoreApplication::translate("Form2", "Submit", nullptr));
        reading->setText(QString());
        PDBText->setHtml(QCoreApplication::translate("Form2", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:7.8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Ubuntu'; font-size:11pt;\">Please select your PDB containing the subprotein: </span></p></body></html>", nullptr));
        loadPDB->setText(QCoreApplication::translate("Form2", "LoadPDB", nullptr));
        label->setText(QCoreApplication::translate("Form2", "Edge threshold(Between7-15):", nullptr));
        edge_graph->setHtml(QCoreApplication::translate("Form2", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:7.8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Ubuntu'; font-size:11pt;\">15</span></p></body></html>", nullptr));
        useCH->setText(QCoreApplication::translate("Form2", "Use ConvexHull", nullptr));
        n_outputs->setHtml(QCoreApplication::translate("Form2", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:7.8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Ubuntu'; font-size:11pt;\">100</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("Form2", "Number of outputs:", nullptr));
        edge_match->setHtml(QCoreApplication::translate("Form2", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:7.8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Ubuntu'; font-size:11pt;\">1</span></p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("Form2", "Enter edge threshold for matching (Between 0.1,1):", nullptr));
        label_4->setText(QCoreApplication::translate("Form2", "Or select from the list of residues from ", nullptr));
        proglabel->setText(QString());
        open_list->setText(QCoreApplication::translate("Form2", "here", nullptr));
        loadPDB_2->setText(QCoreApplication::translate("Form2", "LoadPDB", nullptr));
        PDBText_2->setHtml(QCoreApplication::translate("Form2", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:7.8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Ubuntu'; font-size:11pt;\">Please select your template PDB: </span></p></body></html>", nullptr));
        reading_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Form2: public Ui_Form2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM2_H
