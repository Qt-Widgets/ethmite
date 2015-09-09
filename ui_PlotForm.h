/********************************************************************************
** Form generated from reading UI file 'PlotForm.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOTFORM_H
#define UI_PLOTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_PlotForm
{
public:
    QHBoxLayout *horizontalLayout;
    QwtPlot *qwtPlot;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QToolButton *btnYAxisLog;
    QToolButton *btnAutoScale;
    QPushButton *btnSave;
    QLabel *label;
    QLineEdit *leMax;
    QLabel *label_2;
    QLineEdit *leMin;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QPushButton *btnZoomIn;
    QPushButton *btnZoomOut;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *PlotForm)
    {
        if (PlotForm->objectName().isEmpty())
            PlotForm->setObjectName(QStringLiteral("PlotForm"));
        PlotForm->resize(640, 450);
        horizontalLayout = new QHBoxLayout(PlotForm);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        qwtPlot = new QwtPlot(PlotForm);
        qwtPlot->setObjectName(QStringLiteral("qwtPlot"));
        qwtPlot->setFrameShadow(QFrame::Plain);

        horizontalLayout->addWidget(qwtPlot);

        frame = new QFrame(PlotForm);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Sunken);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        btnYAxisLog = new QToolButton(frame);
        btnYAxisLog->setObjectName(QStringLiteral("btnYAxisLog"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnYAxisLog->sizePolicy().hasHeightForWidth());
        btnYAxisLog->setSizePolicy(sizePolicy);
        btnYAxisLog->setCheckable(true);
        btnYAxisLog->setAutoRaise(true);

        verticalLayout_2->addWidget(btnYAxisLog);

        btnAutoScale = new QToolButton(frame);
        btnAutoScale->setObjectName(QStringLiteral("btnAutoScale"));
        sizePolicy.setHeightForWidth(btnAutoScale->sizePolicy().hasHeightForWidth());
        btnAutoScale->setSizePolicy(sizePolicy);
        btnAutoScale->setCheckable(true);
        btnAutoScale->setChecked(true);
        btnAutoScale->setAutoRaise(true);

        verticalLayout_2->addWidget(btnAutoScale);

        btnSave = new QPushButton(frame);
        btnSave->setObjectName(QStringLiteral("btnSave"));

        verticalLayout_2->addWidget(btnSave);

        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_2->addWidget(label);

        leMax = new QLineEdit(frame);
        leMax->setObjectName(QStringLiteral("leMax"));
        sizePolicy.setHeightForWidth(leMax->sizePolicy().hasHeightForWidth());
        leMax->setSizePolicy(sizePolicy);
        leMax->setMaxLength(64);

        verticalLayout_2->addWidget(leMax);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_2->addWidget(label_2);

        leMin = new QLineEdit(frame);
        leMin->setObjectName(QStringLiteral("leMin"));
        sizePolicy.setHeightForWidth(leMin->sizePolicy().hasHeightForWidth());
        leMin->setSizePolicy(sizePolicy);
        leMin->setMaxLength(64);

        verticalLayout_2->addWidget(leMin);

        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        btnZoomIn = new QPushButton(groupBox);
        btnZoomIn->setObjectName(QStringLiteral("btnZoomIn"));

        verticalLayout->addWidget(btnZoomIn);

        btnZoomOut = new QPushButton(groupBox);
        btnZoomOut->setObjectName(QStringLiteral("btnZoomOut"));

        verticalLayout->addWidget(btnZoomOut);


        verticalLayout_2->addWidget(groupBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout->addWidget(frame);


        retranslateUi(PlotForm);

        QMetaObject::connectSlotsByName(PlotForm);
    } // setupUi

    void retranslateUi(QWidget *PlotForm)
    {
        PlotForm->setWindowTitle(QApplication::translate("PlotForm", "Plot", 0));
        btnYAxisLog->setText(QApplication::translate("PlotForm", "Log10", 0));
        btnAutoScale->setText(QApplication::translate("PlotForm", "Auto", 0));
        btnSave->setText(QApplication::translate("PlotForm", "save", 0));
        label->setText(QApplication::translate("PlotForm", "Max", 0));
        leMax->setText(QApplication::translate("PlotForm", "100", 0));
        label_2->setText(QApplication::translate("PlotForm", "Min", 0));
        leMin->setText(QApplication::translate("PlotForm", "-100", 0));
        groupBox->setTitle(QApplication::translate("PlotForm", "Zoom", 0));
        btnZoomIn->setText(QApplication::translate("PlotForm", "+", 0));
        btnZoomOut->setText(QApplication::translate("PlotForm", "-", 0));
    } // retranslateUi

};

namespace Ui {
    class PlotForm: public Ui_PlotForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOTFORM_H
