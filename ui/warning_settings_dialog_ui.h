#ifndef WARNING_SETTINGS_DIALOG_UI_H
#define WARNING_SETTINGS_DIALOG_UI_H

#include <QPushButton>
#include <QLabel>
#include <QApplication>
#include <QDialog>

class Ui_WarningSettingsDialog
{
public:
    QPushButton *CancelButton;
    QPushButton *ApplyButton;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(641, 300);
        Dialog->setStyleSheet(QString::fromUtf8("background: rgb(38, 38, 38);\n"
"color: rgb(238, 238, 236);"));
        CancelButton = new QPushButton(Dialog);
        CancelButton->setObjectName(QString::fromUtf8("CancelButton"));
        CancelButton->setGeometry(QRect(398, 260, 101, 25));
        ApplyButton = new QPushButton(Dialog);
        ApplyButton->setObjectName(QString::fromUtf8("ApplyButton"));
        ApplyButton->setGeometry(QRect(520, 260, 101, 25));
        label = new QLabel(Dialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(220, 20, 191, 31));
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("color:rgb(0, 182, 128)"));
        label_2 = new QLabel(Dialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 100, 601, 17));
        QFont font1;
        font1.setPointSize(12);
        label_2->setFont(font1);
        label_3 = new QLabel(Dialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(30, 170, 601, 17));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        label_3->setFont(font2);
        label_4 = new QLabel(Dialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(30, 120, 601, 17));
        label_4->setFont(font1);

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Подтвердите действие", nullptr));
        CancelButton->setText(QCoreApplication::translate("Dialog", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        ApplyButton->setText(QCoreApplication::translate("Dialog", "\320\237\321\200\320\276\320\264\320\276\320\273\320\266\320\270\321\202\321\214", nullptr));
        label->setText(QCoreApplication::translate("Dialog", "\320\237\321\200\320\265\320\264\321\203\320\277\321\200\320\265\320\266\320\264\320\265\320\275\320\270\320\265!", nullptr));
        label_2->setText(QCoreApplication::translate("Dialog", "\320\236\320\264\320\275\320\276 \320\270\320\267 \320\277\320\276\320\273\320\265\320\271 \320\275\320\260\321\201\321\202\321\200\320\276\320\265\320\272 \320\262\320\262\320\265\320\264\320\265\320\275\320\276 \320\275\320\265 \320\277\321\200\320\260\320\262\320\270\320\273\321\214\320\275\320\276.", nullptr));
        label_3->setText(QCoreApplication::translate("Dialog", "\320\222\321\213 \320\264\320\265\320\271\321\201\321\202\320\262\320\270\321\202\320\265\320\273\321\214\320\275\320\276 \321\205\320\276\321\202\320\270\321\202\320\265 \321\201\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \321\202\320\265\320\272\321\203\321\211\320\270\320\265 \320\275\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270?", nullptr));
        label_4->setText(QCoreApplication::translate("Dialog", "\320\241\320\276\321\205\321\200\320\260\320\275\320\265\320\275\320\270\320\265 \321\202\320\260\320\272\320\276\320\271 \320\272\320\276\320\275\321\204\320\270\320\263\321\203\321\200\320\260\321\206\320\270\320\270 \320\274\320\276\320\266\320\265\321\202 \320\277\321\200\320\270\320\262\320\265\321\201\321\202\320\270 \320\272 \320\275\320\265\320\277\321\200\320\260\320\262\320\270\320\273\321\214\320\275\320\276\320\271 \321\200\320\260\320\261\320\276\321\202\320\265 \320\237\320\236.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WarningSettingsDialog: public Ui_WarningSettingsDialog {};
} // namespace Ui


#endif // WARNING_SETTINGS_DIALOG_UI_H
