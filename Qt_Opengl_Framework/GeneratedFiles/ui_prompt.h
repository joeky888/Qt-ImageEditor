/********************************************************************************
** Form generated from reading UI file 'prompt.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROMPT_H
#define UI_PROMPT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QPushButton *GLButton;
    QPushButton *DirectXButton;
    QLabel *label;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->setWindowModality(Qt::ApplicationModal);
        Dialog->resize(401, 228);
        Dialog->setContextMenuPolicy(Qt::NoContextMenu);
        Dialog->setStyleSheet(QLatin1String("QWidget{\n"
"	font-family : 'Arial';\n"
"	font-size : 20px;\n"
"	background-color : black;\n"
"	color : white;\n"
"}\n"
"\n"
"QPushButton{\n"
"	background-color : grey;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	background-color : red;\n"
"	border: 3px solid white\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"	background-color : rgb(200, 0, 0);\n"
"}"));
        Dialog->setSizeGripEnabled(true);
        Dialog->setModal(true);
        GLButton = new QPushButton(Dialog);
        GLButton->setObjectName(QStringLiteral("GLButton"));
        GLButton->setGeometry(QRect(20, 80, 361, 51));
        DirectXButton = new QPushButton(Dialog);
        DirectXButton->setObjectName(QStringLiteral("DirectXButton"));
        DirectXButton->setGeometry(QRect(20, 140, 361, 51));
        label = new QLabel(Dialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 20, 371, 20));
        label->setLayoutDirection(Qt::RightToLeft);
        label->setAlignment(Qt::AlignCenter);

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0));
        GLButton->setText(QApplication::translate("Dialog", "OpenGL", 0));
        DirectXButton->setText(QApplication::translate("Dialog", "DirectX", 0));
        label->setText(QApplication::translate("Dialog", "Choose Render Mode", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROMPT_H
