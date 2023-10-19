/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include <qchartview.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QChartView *widget_ch3;
    QTextEdit *textEdit;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEdit;
    QChartView *widget_ch2;
    QChartView *widget_ch1;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QWidget *widget;
    QPushButton *minButton;
    QPushButton *closeButton;
    QLabel *label_5;
    QLabel *label_6;
    QPushButton *pushButton_4;
    QPushButton *pushButton_3;
    QComboBox *portBox;
    QPushButton *pushButton_2;
    QPushButton *pushButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(722, 860);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        widget_ch3 = new QChartView(centralWidget);
        widget_ch3->setObjectName(QString::fromUtf8("widget_ch3"));
        widget_ch3->setGeometry(QRect(150, 520, 450, 200));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(10, 740, 351, 91));
        horizontalLayoutWidget_2 = new QWidget(centralWidget);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(0, 70, 141, 51));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget_2);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        lineEdit = new QLineEdit(horizontalLayoutWidget_2);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout_2->addWidget(lineEdit);

        widget_ch2 = new QChartView(centralWidget);
        widget_ch2->setObjectName(QString::fromUtf8("widget_ch2"));
        widget_ch2->setGeometry(QRect(150, 320, 450, 200));
        widget_ch1 = new QChartView(centralWidget);
        widget_ch1->setObjectName(QString::fromUtf8("widget_ch1"));
        widget_ch1->setGeometry(QRect(150, 120, 450, 200));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(50, 200, 72, 15));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(50, 400, 72, 15));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(50, 600, 72, 15));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 801, 51));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 255);"));
        minButton = new QPushButton(widget);
        minButton->setObjectName(QString::fromUtf8("minButton"));
        minButton->setGeometry(QRect(580, 20, 54, 20));
        minButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-image: url(:/prefix1/min.png);\n"
"	border: 2px solid #8f8f91;\n"
"	border-radius: 6px;\n"
"    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #f6f7fa, stop:1 #dadbde);\n"
"	min-width: 50px;\n"
"}"));
        closeButton = new QPushButton(widget);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));
        closeButton->setGeometry(QRect(640, 20, 54, 20));
        closeButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border-image: url(:/prefix1/close.png);\n"
"	border: 2px solid #8f8f91;\n"
"	border-radius: 6px;\n"
"    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #f6f7fa, stop:1 #dadbde);\n"
"	min-width: 50px;\n"
"}"));
        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(100, 10, 141, 31));
        label_5->setStyleSheet(QString::fromUtf8("font: 25 20pt \"\345\276\256\350\275\257\351\233\205\351\273\221 Light\";"));
        label_6 = new QLabel(widget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 0, 61, 51));
        label_6->setStyleSheet(QString::fromUtf8("border-image: url(:/prefix1/music.png);"));
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(332, 77, 100, 30));
        pushButton_4->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border: 2px solid #8f8f91;\n"
"	border-radius: 6px;\n"
"    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #f6f7fa, stop:1 #dadbde);\n"
"	min-width: 80px;\n"
"}"));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(570, 77, 100, 30));
        pushButton_3->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border: 2px solid #8f8f91;\n"
"	border-radius: 6px;\n"
"    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #f6f7fa, stop:1 #dadbde);\n"
"	min-width: 80px;\n"
"}"));
        portBox = new QComboBox(centralWidget);
        portBox->setObjectName(QString::fromUtf8("portBox"));
        portBox->setGeometry(QRect(440, 80, 111, 21));
        portBox->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border: 2px solid #8f8f91;\n"
"	border-radius: 6px;\n"
"    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #f6f7fa, stop:1 #dadbde);\n"
"	min-width: 80px;\n"
"}"));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(541, 771, 160, 40));
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border: 2px solid #8f8f91;\n"
"	border-radius: 6px;\n"
"    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #f6f7fa, stop:1 #dadbde);\n"
"	min-width: 80px;\n"
"}"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(370, 770, 160, 40));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	border: 2px solid #8f8f91;\n"
"	border-radius: 6px;\n"
"    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #f6f7fa, stop:1 #dadbde);\n"
"	min-width: 80px;\n"
"}"));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\347\224\265\351\207\217\345\211\251\344\275\231\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\351\200\232\351\201\2231", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\351\200\232\351\201\2232", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\351\200\232\351\201\2233", nullptr));
        minButton->setText(QString());
        closeButton->setText(QString());
        label_5->setText(QCoreApplication::translate("MainWindow", "\350\204\221\346\263\242\351\237\263\344\271\220", nullptr));
        label_6->setText(QString());
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "\346\220\234\347\264\242\344\270\262\345\217\243", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\351\237\263\344\271\220", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\351\207\207\351\233\206", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
