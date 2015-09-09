/********************************************************************************
** Form generated from reading UI file 'IoForm.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IOFORM_H
#define UI_IOFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IoForm
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QLineEdit *leValue;
    QPushButton *btnSet;

    void setupUi(QWidget *IoForm)
    {
        if (IoForm->objectName().isEmpty())
            IoForm->setObjectName(QStringLiteral("IoForm"));
        IoForm->resize(216, 56);
        verticalLayout = new QVBoxLayout(IoForm);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(IoForm);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        leValue = new QLineEdit(groupBox);
        leValue->setObjectName(QStringLiteral("leValue"));

        horizontalLayout->addWidget(leValue);

        btnSet = new QPushButton(groupBox);
        btnSet->setObjectName(QStringLiteral("btnSet"));

        horizontalLayout->addWidget(btnSet);


        verticalLayout->addWidget(groupBox);


        retranslateUi(IoForm);

        QMetaObject::connectSlotsByName(IoForm);
    } // setupUi

    void retranslateUi(QWidget *IoForm)
    {
        IoForm->setWindowTitle(QApplication::translate("IoForm", "IoForm", 0));
        groupBox->setTitle(QApplication::translate("IoForm", "Parameter", 0));
        btnSet->setText(QApplication::translate("IoForm", "set", 0));
    } // retranslateUi

};

namespace Ui {
    class IoForm: public Ui_IoForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IOFORM_H
