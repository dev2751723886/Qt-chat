/********************************************************************************
** Form generated from reading UI file 'file.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILE_H
#define UI_FILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_File
{
public:
    QHBoxLayout *horizontalLayout;
    QListWidget *listWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *flush_PB;
    QPushButton *mkDir_PB;
    QPushButton *delFile_PB;
    QPushButton *rename_PB;
    QPushButton *move_PB;
    QPushButton *return_PB;
    QPushButton *upload_PB;
    QPushButton *download_PB;
    QPushButton *share_PB;

    void setupUi(QWidget *File)
    {
        if (File->objectName().isEmpty())
            File->setObjectName(QString::fromUtf8("File"));
        File->resize(497, 349);
        horizontalLayout = new QHBoxLayout(File);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        listWidget = new QListWidget(File);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        horizontalLayout->addWidget(listWidget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        flush_PB = new QPushButton(File);
        flush_PB->setObjectName(QString::fromUtf8("flush_PB"));

        verticalLayout->addWidget(flush_PB);

        mkDir_PB = new QPushButton(File);
        mkDir_PB->setObjectName(QString::fromUtf8("mkDir_PB"));

        verticalLayout->addWidget(mkDir_PB);

        delFile_PB = new QPushButton(File);
        delFile_PB->setObjectName(QString::fromUtf8("delFile_PB"));

        verticalLayout->addWidget(delFile_PB);

        rename_PB = new QPushButton(File);
        rename_PB->setObjectName(QString::fromUtf8("rename_PB"));

        verticalLayout->addWidget(rename_PB);

        move_PB = new QPushButton(File);
        move_PB->setObjectName(QString::fromUtf8("move_PB"));

        verticalLayout->addWidget(move_PB);

        return_PB = new QPushButton(File);
        return_PB->setObjectName(QString::fromUtf8("return_PB"));

        verticalLayout->addWidget(return_PB);

        upload_PB = new QPushButton(File);
        upload_PB->setObjectName(QString::fromUtf8("upload_PB"));

        verticalLayout->addWidget(upload_PB);

        download_PB = new QPushButton(File);
        download_PB->setObjectName(QString::fromUtf8("download_PB"));

        verticalLayout->addWidget(download_PB);

        share_PB = new QPushButton(File);
        share_PB->setObjectName(QString::fromUtf8("share_PB"));

        verticalLayout->addWidget(share_PB);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(File);

        QMetaObject::connectSlotsByName(File);
    } // setupUi

    void retranslateUi(QWidget *File)
    {
        File->setWindowTitle(QCoreApplication::translate("File", "Form", nullptr));
        flush_PB->setText(QCoreApplication::translate("File", "\345\210\267\346\226\260\346\226\207\344\273\266", nullptr));
        mkDir_PB->setText(QCoreApplication::translate("File", "\345\210\233\345\273\272\346\226\207\344\273\266", nullptr));
        delFile_PB->setText(QCoreApplication::translate("File", "\345\210\240\351\231\244\346\226\207\344\273\266", nullptr));
        rename_PB->setText(QCoreApplication::translate("File", "\351\207\215\345\221\275\345\220\215", nullptr));
        move_PB->setText(QCoreApplication::translate("File", "\347\247\273\345\212\250\346\226\207\344\273\266", nullptr));
        return_PB->setText(QCoreApplication::translate("File", "\350\277\224\345\233\236\344\270\212\344\270\200\347\272\247", nullptr));
        upload_PB->setText(QCoreApplication::translate("File", "\344\270\212\344\274\240\346\226\207\344\273\266", nullptr));
        download_PB->setText(QCoreApplication::translate("File", "\344\270\213\350\275\275\346\226\207\344\273\266", nullptr));
        share_PB->setText(QCoreApplication::translate("File", "\345\210\206\344\272\253\346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class File: public Ui_File {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILE_H
