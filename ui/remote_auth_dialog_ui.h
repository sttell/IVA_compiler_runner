#ifndef REMOTE_AUTH_DIALOG_UI_H
#define REMOTE_AUTH_DIALOG_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_RemoteAuthDialog
{
public:
    QPushButton *ApplyButton;
    QPushButton *CancelButton;
    QLineEdit *HostIPLineEdit;
    QLineEdit *PasswordLineEdit;
    QLineEdit *usernameLineEdit;
    QLabel *RemoteAuthLabel;
    QLabel *HostIpLabel;
    QLabel *UsernameLabel;
    QLabel *PasswordLabel;
    QCheckBox *ForgotMeCheckBox;
    QCheckBox *ForgotHostCheckBox;

    void setupUi(QDialog *RemoteAuthDialog)
    {
        if (RemoteAuthDialog->objectName().isEmpty())
            RemoteAuthDialog->setObjectName(QString::fromUtf8("RemoteAuthDialog"));
        RemoteAuthDialog->resize(691, 430);
        RemoteAuthDialog->setStyleSheet(QString::fromUtf8("color: rgb(238, 238, 236);\n"
"background: rgb(49, 49, 49);"));
        ApplyButton = new QPushButton(RemoteAuthDialog);
        ApplyButton->setObjectName(QString::fromUtf8("ApplyButton"));
        ApplyButton->setGeometry(QRect(570, 380, 101, 31));
        CancelButton = new QPushButton(RemoteAuthDialog);
        CancelButton->setObjectName(QString::fromUtf8("CancelButton"));
        CancelButton->setGeometry(QRect(450, 380, 101, 31));
        HostIPLineEdit = new QLineEdit(RemoteAuthDialog);
        HostIPLineEdit->setObjectName(QString::fromUtf8("HostIPLineEdit"));
        HostIPLineEdit->setGeometry(QRect(60, 110, 571, 31));
        PasswordLineEdit = new QLineEdit(RemoteAuthDialog);
        PasswordLineEdit->setObjectName(QString::fromUtf8("PasswordLineEdit"));
        PasswordLineEdit->setGeometry(QRect(60, 290, 571, 31));
        PasswordLineEdit->setEchoMode(QLineEdit::Password);
        usernameLineEdit = new QLineEdit(RemoteAuthDialog);
        usernameLineEdit->setObjectName(QString::fromUtf8("usernameLineEdit"));
        usernameLineEdit->setGeometry(QRect(60, 220, 571, 31));
        RemoteAuthLabel = new QLabel(RemoteAuthDialog);
        RemoteAuthLabel->setObjectName(QString::fromUtf8("RemoteAuthLabel"));
        RemoteAuthLabel->setGeometry(QRect(150, 20, 381, 31));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        RemoteAuthLabel->setFont(font);
        RemoteAuthLabel->setStyleSheet(QString::fromUtf8("color:rgb(0, 204, 143);"));
        HostIpLabel = new QLabel(RemoteAuthDialog);
        HostIpLabel->setObjectName(QString::fromUtf8("HostIpLabel"));
        HostIpLabel->setGeometry(QRect(60, 80, 67, 17));
        UsernameLabel = new QLabel(RemoteAuthDialog);
        UsernameLabel->setObjectName(QString::fromUtf8("UsernameLabel"));
        UsernameLabel->setGeometry(QRect(60, 200, 161, 17));
        PasswordLabel = new QLabel(RemoteAuthDialog);
        PasswordLabel->setObjectName(QString::fromUtf8("PasswordLabel"));
        PasswordLabel->setGeometry(QRect(60, 270, 161, 17));
        ForgotMeCheckBox = new QCheckBox(RemoteAuthDialog);
        ForgotMeCheckBox->setObjectName(QString::fromUtf8("ForgotMeCheckBox"));
        ForgotMeCheckBox->setGeometry(QRect(490, 330, 191, 23));
        ForgotHostCheckBox = new QCheckBox(RemoteAuthDialog);
        ForgotHostCheckBox->setObjectName(QString::fromUtf8("ForgotHostCheckBox"));
        ForgotHostCheckBox->setGeometry(QRect(490, 150, 191, 23));

        retranslateUi(RemoteAuthDialog);

        QMetaObject::connectSlotsByName(RemoteAuthDialog);
    } // setupUi

    void retranslateUi(QDialog *RemoteAuthDialog)
    {
        RemoteAuthDialog->setWindowTitle(QCoreApplication::translate("RemoteAuthDialog", "Dialog", nullptr));
        ApplyButton->setText(QCoreApplication::translate("RemoteAuthDialog", "\320\222\320\276\320\271\321\202\320\270", nullptr));
        CancelButton->setText(QCoreApplication::translate("RemoteAuthDialog", "\320\236\321\202\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        RemoteAuthLabel->setText(QCoreApplication::translate("RemoteAuthDialog", "\320\220\320\262\321\202\320\276\321\200\320\270\320\267\320\260\321\206\320\270\321\217 \320\275\320\260 \321\203\320\264\320\260\320\273\320\265\320\275\320\275\320\276\320\274 \321\201\320\265\321\200\320\262\320\265\321\200\320\265", nullptr));
        HostIpLabel->setText(QCoreApplication::translate("RemoteAuthDialog", "IP \321\205\320\276\321\201\321\202\320\260:", nullptr));
        UsernameLabel->setText(QCoreApplication::translate("RemoteAuthDialog", "\320\230\320\274\321\217 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217:", nullptr));
        PasswordLabel->setText(QCoreApplication::translate("RemoteAuthDialog", "\320\237\320\260\321\200\320\276\320\273\321\214:", nullptr));
        ForgotMeCheckBox->setText(QCoreApplication::translate("RemoteAuthDialog", "\320\227\320\260\320\277\320\276\320\274\320\275\320\270\321\202\321\214 \320\274\320\265\320\275\321\217", nullptr));
        ForgotHostCheckBox->setText(QCoreApplication::translate("RemoteAuthDialog", "\320\227\320\260\320\277\320\276\320\274\320\275\320\270\321\202\321\214 \321\205\320\276\321\201\321\202\320\270\320\275\320\263", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RemoteAuthDialog: public Ui_RemoteAuthDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // REMOTE_AUTH_DIALOG_UI_H
