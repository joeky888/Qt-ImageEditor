/********************************************************************************
** Form generated from reading UI file 'qt_opengl_framework.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QT_OPENGL_FRAMEWORK_H
#define UI_QT_OPENGL_FRAMEWORK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Qt_Opengl_FrameworkClass
{
public:
    QAction *actionExit;
    QAction *actionOpen;
    QAction *actionGray;
    QAction *actionUniform_Quantization;
    QAction *actionPopulosity;
    QAction *actionNaive_Threshold_Dithering;
    QAction *actionBrightness_Preserving_Threshold_Dithering;
    QAction *actionRandom;
    QAction *actionClustered;
    QAction *actionFloyd_Steinberg;
    QAction *actionColor_Floyd_Steinberg;
    QAction *actionBox;
    QAction *actionBartlett;
    QAction *actionGaussian;
    QAction *actionArbitrary_Size_Gaussian;
    QAction *actionHalf;
    QAction *actionDouble;
    QAction *actionArbitrary_Uniform_Scale;
    QAction *actionEdge;
    QAction *actionEnhance;
    QAction *actionRotate;
    QAction *actionResample_src;
    QAction *actionOver;
    QAction *actionIn;
    QAction *actionOut;
    QAction *actionAtop;
    QAction *actionXor;
    QAction *actionSave;
    QAction *actionNPR;
    QAction *actionAbout;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QSlider *BrightnessSlider;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QLabel *label;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuColor;
    QMenu *menuDithering;
    QMenu *menuFiltering;
    QMenu *menuResize;
    QMenu *menuComposing;
    QMenu *menuNPR;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *Qt_Opengl_FrameworkClass)
    {
        if (Qt_Opengl_FrameworkClass->objectName().isEmpty())
            Qt_Opengl_FrameworkClass->setObjectName(QStringLiteral("Qt_Opengl_FrameworkClass"));
        Qt_Opengl_FrameworkClass->resize(651, 600);
        Qt_Opengl_FrameworkClass->setStyleSheet(QLatin1String("QMenuBar {\n"
"     background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,\n"
"                                       stop:0 lightgray, stop:1 black);\n"
"	color : white;\n"
"	padding: 10px; \n"
"	spacing:  10px; \n"
"	font-size : 20px;\n"
" }\n"
"\n"
" QMenuBar::item {\n"
"     spacing: 3px; /* spacing between menu bar items */\n"
"     padding: 1px 4px;\n"
"     background: transparent;\n"
"     border-radius: 8px;\n"
" }\n"
"\n"
" QMenuBar::item:selected { /* when selected using mouse or keyboard */\n"
"     background: #a8a8a8;\n"
" }\n"
"\n"
" QMenuBar::item:pressed {\n"
"     background: #888888;\n"
" }\n"
"\n"
"QMenu{\n"
"	background-color : black;\n"
"	color : white;\n"
"	padding: 10px; \n"
"	spacing:  10px; \n"
"	font-size : 20px;\n"
"}\n"
"QMenu:selected{\n"
"	background-color : grey;\n"
"}\n"
"#centralWidget, #mainToolBar{\n"
"	background-color : black;\n"
"}\n"
"QPushButton{\n"
"	color : white;\n"
"	font-family : 'Arial';\n"
"	font-size : 16px;\n"
"	background-color : grey;\n"
"	padding : 5px;\n"
""
                        "}\n"
"\n"
"QPushButton:hover{\n"
"	background-color : red;\n"
"	border : 3px solid white; \n"
"}\n"
"QPushButton:pressed{\n"
"	background-color : rgb(200, 0, 0);\n"
"}\n"
"QSlider::groove:horizontal {\n"
"	border: 1px solid #999999;\n"
"	background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);\n"
"	height: 26px;\n"
"	margin: 0 0 0 0;\n"
"}\n"
"QSlider::handle:horizontal {\n"
"	background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);\n"
"	border: 1px solid #5c5c5c;\n"
"	width: 60px;\n"
"	margin: -2px 0 -2px 0;\n"
"	border-radius: 3px;\n"
"}"));
        actionExit = new QAction(Qt_Opengl_FrameworkClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionOpen = new QAction(Qt_Opengl_FrameworkClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionGray = new QAction(Qt_Opengl_FrameworkClass);
        actionGray->setObjectName(QStringLiteral("actionGray"));
        actionUniform_Quantization = new QAction(Qt_Opengl_FrameworkClass);
        actionUniform_Quantization->setObjectName(QStringLiteral("actionUniform_Quantization"));
        actionPopulosity = new QAction(Qt_Opengl_FrameworkClass);
        actionPopulosity->setObjectName(QStringLiteral("actionPopulosity"));
        actionNaive_Threshold_Dithering = new QAction(Qt_Opengl_FrameworkClass);
        actionNaive_Threshold_Dithering->setObjectName(QStringLiteral("actionNaive_Threshold_Dithering"));
        actionBrightness_Preserving_Threshold_Dithering = new QAction(Qt_Opengl_FrameworkClass);
        actionBrightness_Preserving_Threshold_Dithering->setObjectName(QStringLiteral("actionBrightness_Preserving_Threshold_Dithering"));
        actionRandom = new QAction(Qt_Opengl_FrameworkClass);
        actionRandom->setObjectName(QStringLiteral("actionRandom"));
        actionClustered = new QAction(Qt_Opengl_FrameworkClass);
        actionClustered->setObjectName(QStringLiteral("actionClustered"));
        actionFloyd_Steinberg = new QAction(Qt_Opengl_FrameworkClass);
        actionFloyd_Steinberg->setObjectName(QStringLiteral("actionFloyd_Steinberg"));
        actionColor_Floyd_Steinberg = new QAction(Qt_Opengl_FrameworkClass);
        actionColor_Floyd_Steinberg->setObjectName(QStringLiteral("actionColor_Floyd_Steinberg"));
        actionBox = new QAction(Qt_Opengl_FrameworkClass);
        actionBox->setObjectName(QStringLiteral("actionBox"));
        actionBartlett = new QAction(Qt_Opengl_FrameworkClass);
        actionBartlett->setObjectName(QStringLiteral("actionBartlett"));
        actionGaussian = new QAction(Qt_Opengl_FrameworkClass);
        actionGaussian->setObjectName(QStringLiteral("actionGaussian"));
        actionArbitrary_Size_Gaussian = new QAction(Qt_Opengl_FrameworkClass);
        actionArbitrary_Size_Gaussian->setObjectName(QStringLiteral("actionArbitrary_Size_Gaussian"));
        actionHalf = new QAction(Qt_Opengl_FrameworkClass);
        actionHalf->setObjectName(QStringLiteral("actionHalf"));
        actionDouble = new QAction(Qt_Opengl_FrameworkClass);
        actionDouble->setObjectName(QStringLiteral("actionDouble"));
        actionArbitrary_Uniform_Scale = new QAction(Qt_Opengl_FrameworkClass);
        actionArbitrary_Uniform_Scale->setObjectName(QStringLiteral("actionArbitrary_Uniform_Scale"));
        actionEdge = new QAction(Qt_Opengl_FrameworkClass);
        actionEdge->setObjectName(QStringLiteral("actionEdge"));
        actionEnhance = new QAction(Qt_Opengl_FrameworkClass);
        actionEnhance->setObjectName(QStringLiteral("actionEnhance"));
        actionRotate = new QAction(Qt_Opengl_FrameworkClass);
        actionRotate->setObjectName(QStringLiteral("actionRotate"));
        actionResample_src = new QAction(Qt_Opengl_FrameworkClass);
        actionResample_src->setObjectName(QStringLiteral("actionResample_src"));
        actionOver = new QAction(Qt_Opengl_FrameworkClass);
        actionOver->setObjectName(QStringLiteral("actionOver"));
        actionIn = new QAction(Qt_Opengl_FrameworkClass);
        actionIn->setObjectName(QStringLiteral("actionIn"));
        actionOut = new QAction(Qt_Opengl_FrameworkClass);
        actionOut->setObjectName(QStringLiteral("actionOut"));
        actionAtop = new QAction(Qt_Opengl_FrameworkClass);
        actionAtop->setObjectName(QStringLiteral("actionAtop"));
        actionXor = new QAction(Qt_Opengl_FrameworkClass);
        actionXor->setObjectName(QStringLiteral("actionXor"));
        actionSave = new QAction(Qt_Opengl_FrameworkClass);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionNPR = new QAction(Qt_Opengl_FrameworkClass);
        actionNPR->setObjectName(QStringLiteral("actionNPR"));
        actionAbout = new QAction(Qt_Opengl_FrameworkClass);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        centralWidget = new QWidget(Qt_Opengl_FrameworkClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(5);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(0, -1, -1, 0);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(10);
        sizePolicy.setVerticalStretch(11);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(pushButton);

        BrightnessSlider = new QSlider(centralWidget);
        BrightnessSlider->setObjectName(QStringLiteral("BrightnessSlider"));
        BrightnessSlider->setMinimum(-255);
        BrightnessSlider->setMaximum(255);
        BrightnessSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(BrightnessSlider);


        verticalLayout->addLayout(horizontalLayout);

        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 631, 479));
        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName(QStringLiteral("label"));
        label->setScaledContents(true);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        Qt_Opengl_FrameworkClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Qt_Opengl_FrameworkClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 651, 51));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuColor = new QMenu(menuBar);
        menuColor->setObjectName(QStringLiteral("menuColor"));
        menuDithering = new QMenu(menuBar);
        menuDithering->setObjectName(QStringLiteral("menuDithering"));
        menuFiltering = new QMenu(menuBar);
        menuFiltering->setObjectName(QStringLiteral("menuFiltering"));
        menuResize = new QMenu(menuBar);
        menuResize->setObjectName(QStringLiteral("menuResize"));
        menuComposing = new QMenu(menuBar);
        menuComposing->setObjectName(QStringLiteral("menuComposing"));
        menuNPR = new QMenu(menuBar);
        menuNPR->setObjectName(QStringLiteral("menuNPR"));
        Qt_Opengl_FrameworkClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Qt_Opengl_FrameworkClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Qt_Opengl_FrameworkClass->addToolBar(Qt::TopToolBarArea, mainToolBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuColor->menuAction());
        menuBar->addAction(menuDithering->menuAction());
        menuBar->addAction(menuFiltering->menuAction());
        menuBar->addAction(menuResize->menuAction());
        menuBar->addAction(menuComposing->menuAction());
        menuBar->addAction(menuNPR->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionExit);
        menuFile->addSeparator();
        menuFile->addAction(actionAbout);
        menuColor->addAction(actionGray);
        menuColor->addAction(actionUniform_Quantization);
        menuColor->addAction(actionPopulosity);
        menuDithering->addAction(actionNaive_Threshold_Dithering);
        menuDithering->addAction(actionBrightness_Preserving_Threshold_Dithering);
        menuDithering->addAction(actionRandom);
        menuDithering->addAction(actionClustered);
        menuDithering->addAction(actionFloyd_Steinberg);
        menuDithering->addAction(actionColor_Floyd_Steinberg);
        menuFiltering->addAction(actionBox);
        menuFiltering->addAction(actionBartlett);
        menuFiltering->addAction(actionGaussian);
        menuFiltering->addAction(actionArbitrary_Size_Gaussian);
        menuFiltering->addAction(actionEdge);
        menuFiltering->addAction(actionEnhance);
        menuResize->addAction(actionHalf);
        menuResize->addAction(actionDouble);
        menuResize->addAction(actionArbitrary_Uniform_Scale);
        menuResize->addAction(actionRotate);
        menuComposing->addAction(actionOver);
        menuComposing->addAction(actionIn);
        menuComposing->addAction(actionOut);
        menuComposing->addAction(actionAtop);
        menuComposing->addAction(actionXor);
        menuNPR->addAction(actionNPR);

        retranslateUi(Qt_Opengl_FrameworkClass);

        QMetaObject::connectSlotsByName(Qt_Opengl_FrameworkClass);
    } // setupUi

    void retranslateUi(QMainWindow *Qt_Opengl_FrameworkClass)
    {
        Qt_Opengl_FrameworkClass->setWindowTitle(QApplication::translate("Qt_Opengl_FrameworkClass", "Qt_Opengl_Framework", 0));
        actionExit->setText(QApplication::translate("Qt_Opengl_FrameworkClass", "Exit", 0));
        actionOpen->setText(QApplication::translate("Qt_Opengl_FrameworkClass", "Open", 0));
        actionGray->setText(QApplication::translate("Qt_Opengl_FrameworkClass", "Gray", 0));
        actionUniform_Quantization->setText(QApplication::translate("Qt_Opengl_FrameworkClass", "Uniform Quantization", 0));
        actionPopulosity->setText(QApplication::translate("Qt_Opengl_FrameworkClass", "Populosity", 0));
        actionNaive_Threshold_Dithering->setText(QApplication::translate("Qt_Opengl_FrameworkClass", "Naive Threshold Dithering", 0));
        actionBrightness_Preserving_Threshold_Dithering->setText(QApplication::translate("Qt_Opengl_FrameworkClass", "Brightness Preserving Threshold", 0));
        actionRandom->setText(QApplication::translate("Qt_Opengl_FrameworkClass", "Random ", 0));
        actionClustered->setText(QApplication::translate("Qt_Opengl_FrameworkClass", "Clustered ", 0));
        actionFloyd_Steinberg->setText(QApplication::translate("Qt_Opengl_FrameworkClass", "Floyd-Steinberg ", 0));
        actionColor_Floyd_Steinberg->setText(QApplication::translate("Qt_Opengl_FrameworkClass", "Color Floyd-Steinberg ", 0));
        actionBox->setText(QApplication::translate("Qt_Opengl_FrameworkClass", "Box", 0));
        actionBartlett->setText(QApplication::translate("Qt_Opengl_FrameworkClass", "Bartlett", 0));
        actionGaussian->setText(QApplication::translate("Qt_Opengl_FrameworkClass", "Gaussian ", 0));
        actionArbitrary_Size_Gaussian->setText(QApplication::translate("Qt_Opengl_FrameworkClass", "Arbitrary-Size Gaussian ", 0));
        actionHalf->setText(QApplication::translate("Qt_Opengl_FrameworkClass", "Half ", 0));
        actionDouble->setText(QApplication::translate("Qt_Opengl_FrameworkClass", "Double ", 0));
        actionArbitrary_Uniform_Scale->setText(QApplication::translate("Qt_Opengl_FrameworkClass", "Arbitrary Uniform Scale", 0));
        actionEdge->setText(QApplication::translate("Qt_Opengl_FrameworkClass", "Edge", 0));
        actionEnhance->setText(QApplication::translate("Qt_Opengl_FrameworkClass", "Enhance", 0));
        actionRotate->setText(QApplication::translate("Qt_Opengl_FrameworkClass", "Rotate", 0));
        actionResample_src->setText(QApplication::translate("Qt_Opengl_FrameworkClass", "resample_src", 0));
        actionOver->setText(QApplication::translate("Qt_Opengl_FrameworkClass", "Over", 0));
        actionIn->setText(QApplication::translate("Qt_Opengl_FrameworkClass", "In", 0));
        actionOut->setText(QApplication::translate("Qt_Opengl_FrameworkClass", "Out", 0));
        actionAtop->setText(QApplication::translate("Qt_Opengl_FrameworkClass", "Atop", 0));
        actionXor->setText(QApplication::translate("Qt_Opengl_FrameworkClass", "Xor", 0));
        actionSave->setText(QApplication::translate("Qt_Opengl_FrameworkClass", "Save", 0));
        actionNPR->setText(QApplication::translate("Qt_Opengl_FrameworkClass", "NPR", 0));
        actionAbout->setText(QApplication::translate("Qt_Opengl_FrameworkClass", "About", 0));
        pushButton->setText(QApplication::translate("Qt_Opengl_FrameworkClass", " Reset All ", 0));
        label->setText(QString());
        menuFile->setTitle(QApplication::translate("Qt_Opengl_FrameworkClass", "File", 0));
        menuColor->setTitle(QApplication::translate("Qt_Opengl_FrameworkClass", "Color", 0));
        menuDithering->setTitle(QApplication::translate("Qt_Opengl_FrameworkClass", "Dithering", 0));
        menuFiltering->setTitle(QApplication::translate("Qt_Opengl_FrameworkClass", "Filtering", 0));
        menuResize->setTitle(QApplication::translate("Qt_Opengl_FrameworkClass", "Size&&Rotate", 0));
        menuComposing->setTitle(QApplication::translate("Qt_Opengl_FrameworkClass", "Composing", 0));
        menuNPR->setTitle(QApplication::translate("Qt_Opengl_FrameworkClass", "Bouns", 0));
    } // retranslateUi

};

namespace Ui {
    class Qt_Opengl_FrameworkClass: public Ui_Qt_Opengl_FrameworkClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT_OPENGL_FRAMEWORK_H
