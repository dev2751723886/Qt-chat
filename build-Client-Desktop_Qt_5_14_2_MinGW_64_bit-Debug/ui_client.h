/********************************************************************************
** Form generated from reading UI file 'client.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_H
#define UI_CLIENT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Client
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *name_LE;
    QLabel *label_2;
    QLineEdit *pwd_LE;
    QHBoxLayout *horizontalLayout;
    QPushButton *login_PB;
    QSpacerItem *horizontalSpacer;
    QPushButton *regist_PB;

    void setupUi(QWidget *Client)
    {
        if (Client->objectName().isEmpty())
            Client->setObjectName(QString::fromUtf8("Client"));
        Client->resize(327, 197);
        QFont font;
        font.setFamily(QString::fromUtf8("Agency FB"));
        Client->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../dir.png"), QSize(), QIcon::Normal, QIcon::Off);
        Client->setWindowIcon(icon);
        widget = new QWidget(Client);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(20, 30, 281, 121));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Agency FB"));
        font1.setPointSize(11);
        label->setFont(font1);

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        name_LE = new QLineEdit(widget);
        name_LE->setObjectName(QString::fromUtf8("name_LE"));

        formLayout->setWidget(0, QFormLayout::FieldRole, name_LE);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font1);

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        pwd_LE = new QLineEdit(widget);
        pwd_LE->setObjectName(QString::fromUtf8("pwd_LE"));
        pwd_LE->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(1, QFormLayout::FieldRole, pwd_LE);


        verticalLayout->addLayout(formLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        login_PB = new QPushButton(widget);
        login_PB->setObjectName(QString::fromUtf8("login_PB"));
        login_PB->setFont(font1);

        horizontalLayout->addWidget(login_PB);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        regist_PB = new QPushButton(widget);
        regist_PB->setObjectName(QString::fromUtf8("regist_PB"));
        regist_PB->setFont(font1);

        horizontalLayout->addWidget(regist_PB);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Client);

        QMetaObject::connectSlotsByName(Client);
    } // setupUi

    void retranslateUi(QWidget *Client)
    {
        Client->setWindowTitle(QCoreApplication::translate("Client", "\347\231\273\345\275\225/\346\263\250\345\206\214", nullptr));
        label->setText(QCoreApplication::translate("Client", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_2->setText(QCoreApplication::translate("Client", "\345\257\206\347\240\201", nullptr));
        login_PB->setText(QCoreApplication::translate("Client", "\347\231\273\345\275\225", nullptr));
        regist_PB->setText(QCoreApplication::translate("Client", "\346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Client: public Ui_Client {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
