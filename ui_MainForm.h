/********************************************************************************
** Form generated from reading UI file 'MainForm.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFORM_H
#define UI_MAINFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QtQuickWidgets/QQuickWidget"

QT_BEGIN_NAMESPACE

class Ui_MainForm
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_4;
    QWidget *widgetTop;
    QHBoxLayout *horizontalLayout_3;
    QWidget *widgetBottom;
    QVBoxLayout *verticalLayout_8;
    QWidget *tab_2;
    QScrollArea *scrollAreaHa;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout_5;
    QWidget *widgetIoHa;
    QScrollArea *scrollAreaSa;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_3;
    QWidget *widgetIoSa;
    QWidget *tab_3;
    QScrollArea *scrollAreaState;
    QWidget *scrollAreaWidgetContents_3;
    QVBoxLayout *verticalLayout_6;
    QWidget *widgetIoState;
    QGroupBox *gbState;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QSpinBox *sbSatelliteIndex;
    QPushButton *btnSend;
    QPushButton *btnPlot;
    QGroupBox *gbDevice;
    QVBoxLayout *verticalLayout;
    QComboBox *comboBox;
    QPushButton *btnOpen;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_7;
    QQuickWidget *quickWidget;
    QPlainTextEdit *teLog;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainForm)
    {
        if (MainForm->objectName().isEmpty())
            MainForm->setObjectName(QStringLiteral("MainForm"));
        MainForm->resize(620, 559);
        QIcon icon;
        icon.addFile(QStringLiteral(":/earth.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainForm->setWindowIcon(icon);
        centralwidget = new QWidget(MainForm);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, -1);
        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(widget_2);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout_4 = new QVBoxLayout(tab);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        widgetTop = new QWidget(tab);
        widgetTop->setObjectName(QStringLiteral("widgetTop"));
        horizontalLayout_3 = new QHBoxLayout(widgetTop);
        horizontalLayout_3->setSpacing(8);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(8, 8, 8, 4);

        verticalLayout_4->addWidget(widgetTop);

        widgetBottom = new QWidget(tab);
        widgetBottom->setObjectName(QStringLiteral("widgetBottom"));
        verticalLayout_8 = new QVBoxLayout(widgetBottom);
        verticalLayout_8->setSpacing(8);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(8, 4, 8, 8);

        verticalLayout_4->addWidget(widgetBottom);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        scrollAreaHa = new QScrollArea(tab_2);
        scrollAreaHa->setObjectName(QStringLiteral("scrollAreaHa"));
        scrollAreaHa->setGeometry(QRect(290, 10, 231, 351));
        scrollAreaHa->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollAreaHa->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 212, 349));
        verticalLayout_5 = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        widgetIoHa = new QWidget(scrollAreaWidgetContents_2);
        widgetIoHa->setObjectName(QStringLiteral("widgetIoHa"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widgetIoHa->sizePolicy().hasHeightForWidth());
        widgetIoHa->setSizePolicy(sizePolicy);

        verticalLayout_5->addWidget(widgetIoHa);

        scrollAreaHa->setWidget(scrollAreaWidgetContents_2);
        scrollAreaSa = new QScrollArea(tab_2);
        scrollAreaSa->setObjectName(QStringLiteral("scrollAreaSa"));
        scrollAreaSa->setGeometry(QRect(20, 10, 231, 351));
        scrollAreaSa->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollAreaSa->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 212, 349));
        verticalLayout_3 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        widgetIoSa = new QWidget(scrollAreaWidgetContents);
        widgetIoSa->setObjectName(QStringLiteral("widgetIoSa"));
        sizePolicy.setHeightForWidth(widgetIoSa->sizePolicy().hasHeightForWidth());
        widgetIoSa->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(widgetIoSa);

        scrollAreaSa->setWidget(scrollAreaWidgetContents);
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        scrollAreaState = new QScrollArea(tab_3);
        scrollAreaState->setObjectName(QStringLiteral("scrollAreaState"));
        scrollAreaState->setGeometry(QRect(290, 0, 231, 351));
        scrollAreaState->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollAreaState->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QStringLiteral("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 212, 349));
        verticalLayout_6 = new QVBoxLayout(scrollAreaWidgetContents_3);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        widgetIoState = new QWidget(scrollAreaWidgetContents_3);
        widgetIoState->setObjectName(QStringLiteral("widgetIoState"));
        sizePolicy.setHeightForWidth(widgetIoState->sizePolicy().hasHeightForWidth());
        widgetIoState->setSizePolicy(sizePolicy);

        verticalLayout_6->addWidget(widgetIoState);

        scrollAreaState->setWidget(scrollAreaWidgetContents_3);
        gbState = new QGroupBox(tab_3);
        gbState->setObjectName(QStringLiteral("gbState"));
        gbState->setGeometry(QRect(19, 69, 181, 111));
        gbState->setFlat(false);
        groupBox = new QGroupBox(tab_3);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 20, 81, 41));
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        sbSatelliteIndex = new QSpinBox(groupBox);
        sbSatelliteIndex->setObjectName(QStringLiteral("sbSatelliteIndex"));
        sbSatelliteIndex->setMinimum(1);
        sbSatelliteIndex->setMaximum(32);

        horizontalLayout_2->addWidget(sbSatelliteIndex);

        btnSend = new QPushButton(groupBox);
        btnSend->setObjectName(QStringLiteral("btnSend"));

        horizontalLayout_2->addWidget(btnSend);

        btnPlot = new QPushButton(tab_3);
        btnPlot->setObjectName(QStringLiteral("btnPlot"));
        btnPlot->setGeometry(QRect(110, 30, 75, 23));
        gbDevice = new QGroupBox(tab_3);
        gbDevice->setObjectName(QStringLiteral("gbDevice"));
        gbDevice->setGeometry(QRect(40, 200, 117, 97));
        gbDevice->setFlat(false);
        gbDevice->setCheckable(false);
        verticalLayout = new QVBoxLayout(gbDevice);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        comboBox = new QComboBox(gbDevice);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        verticalLayout->addWidget(comboBox);

        btnOpen = new QPushButton(gbDevice);
        btnOpen->setObjectName(QStringLiteral("btnOpen"));

        verticalLayout->addWidget(btnOpen);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        verticalLayout_7 = new QVBoxLayout(tab_4);
        verticalLayout_7->setSpacing(0);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        quickWidget = new QQuickWidget(tab_4);
        quickWidget->setObjectName(QStringLiteral("quickWidget"));
        quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
        quickWidget->setSource(QUrl(QStringLiteral("qrc:/widget.qml")));

        verticalLayout_7->addWidget(quickWidget);

        tabWidget->addTab(tab_4, QString());

        verticalLayout_2->addWidget(tabWidget);

        teLog = new QPlainTextEdit(widget_2);
        teLog->setObjectName(QStringLiteral("teLog"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(teLog->sizePolicy().hasHeightForWidth());
        teLog->setSizePolicy(sizePolicy1);
        teLog->setMaximumSize(QSize(16777215, 128));
        teLog->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        teLog->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        verticalLayout_2->addWidget(teLog);


        horizontalLayout->addWidget(widget_2);

        MainForm->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainForm);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainForm->setStatusBar(statusbar);

        retranslateUi(MainForm);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainForm);
    } // setupUi

    void retranslateUi(QMainWindow *MainForm)
    {
        MainForm->setWindowTitle(QApplication::translate("MainForm", "Mite", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainForm", "Standard", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainForm", "High", 0));
        gbState->setTitle(QApplication::translate("MainForm", "Locked", 0));
        groupBox->setTitle(QApplication::translate("MainForm", "Satellite", 0));
        btnSend->setText(QApplication::translate("MainForm", "Set", 0));
        btnPlot->setText(QApplication::translate("MainForm", "Plot", 0));
        gbDevice->setTitle(QApplication::translate("MainForm", "Device", 0));
        btnOpen->setText(QApplication::translate("MainForm", "Open", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainForm", "State", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MainForm", "Widget", 0));
    } // retranslateUi

};

namespace Ui {
    class MainForm: public Ui_MainForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFORM_H
