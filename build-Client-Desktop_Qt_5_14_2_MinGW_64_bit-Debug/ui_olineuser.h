/********************************************************************************
** Form generated from reading UI file 'olineuser.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OLINEUSER_H
#define UI_OLINEUSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OlineUser
{
public:
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget;

    void setupUi(QWidget *OlineUser)
    {
        if (OlineUser->objectName().isEmpty())
            OlineUser->setObjectName(QString::fromUtf8("OlineUser"));
        OlineUser->resize(272, 456);
        verticalLayout = new QVBoxLayout(OlineUser);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        listWidget = new QListWidget(OlineUser);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        verticalLayout->addWidget(listWidget);


        retranslateUi(OlineUser);

        QMetaObject::connectSlotsByName(OlineUser);
    } // setupUi

    void retranslateUi(QWidget *OlineUser)
    {
        OlineUser->setWindowTitle(QCoreApplication::translate("OlineUser", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OlineUser: public Ui_OlineUser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OLINEUSER_H
