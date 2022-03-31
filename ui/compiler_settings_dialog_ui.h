#ifndef COMPILER_SETTINGS_DIALOG_UI_H
#define COMPILER_SETTINGS_DIALOG_UI_H

#include <QVariant>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QCoreApplication>

QT_BEGIN_NAMESPACE

class Ui_CompilerSettingsDialog
{
public:
    QPushButton *ApplyButton;
    QPushButton *CancelButton;
    QWidget *HeaderWidget;
    QLabel *HeaderDescription;
    QLabel *CompilerDirLabel;
    QLineEdit *CompilerDirLineEdit;
    QPushButton *ChangeCompilerDirPushButton;
    QLabel *WrongFmtCompilerDirLabel;
    QFrame *line;
    QLabel *CMakeNumRunsLabel;
    QLineEdit *CMakeNumRunsLineEdit;
    QPushButton *CMakeNumRunsDecrementButton;
    QPushButton *CMakeNumRunsIncrementButton;
    QLabel *CMakeNumCoresLabel;
    QCheckBox *MakeParallelCheckBox;
    QPushButton *CMakeNumCoresIncrementButton;
    QLineEdit *CMakeNumCoresLineEdit;
    QPushButton *CMakeNumCoresDecrementButton;
    QLabel *WrongFmtNumRunsLabel;
    QLabel *WrongFmtNumCoresLabel;
    QFrame *line_2;
    QLabel *InputScaleLabel;
    QLabel *OutputScaleLabel;
    QLineEdit *InputScaleLineEdit;
    QLineEdit *OutputScaleLineEdit;
    QLabel *WrongFmtInputScaleLabel;
    QLabel *WrongFmtOutputScaleLabel;
    QFrame *line_3;
    QLineEdit *KcuIpVersionEditLine;
    QLineEdit *ServerApiVersionEditLine;
    QLabel *ServerApiVersionLabel;
    QLineEdit *MobileIpVersionEditLine;
    QLabel *MobileApiVersionLabel;
    QLineEdit *ServerIpVersionEditLine;
    QLabel *KcuApiVersionLabel;
    QLabel *ServerDeviceLabel;
    QLabel *MobileDeviceLabel;
    QLabel *KcuDeviceLabel;
    QLineEdit *KcuApiVersionEditLine;
    QLineEdit *MobileApiVersionEditLine;
    QLabel *ServerIpCoreVersionLabel;
    QLabel *KcuIpCoreVersionLabel;
    QLabel *MobileIpCoreVersionLabel;
    QLabel *WrongFmtKcuVersionLabel;
    QLabel *WrongFmtMobileVersionLabel;
    QLabel *WrongFmtServerVersionLabel;
    QLabel *WrongFmtArchiveNameLabel;
    QLineEdit *ArchiveNameLineEdit;
    QLabel *ArchiveNameLabel;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(1200, 700);
        Dialog->setStyleSheet(QString::fromUtf8("background: rgb(38, 38, 38);\n"
"color: rgb(238, 238, 236)"));
        ApplyButton = new QPushButton(Dialog);
        ApplyButton->setObjectName(QString::fromUtf8("ApplyButton"));
        ApplyButton->setGeometry(QRect(1068, 654, 111, 31));
        CancelButton = new QPushButton(Dialog);
        CancelButton->setObjectName(QString::fromUtf8("CancelButton"));
        CancelButton->setGeometry(QRect(930, 654, 111, 31));
        HeaderWidget = new QWidget(Dialog);
        HeaderWidget->setObjectName(QString::fromUtf8("HeaderWidget"));
        HeaderWidget->setGeometry(QRect(0, 0, 1201, 81));
        HeaderWidget->setStyleSheet(QString::fromUtf8("background: rgb(0, 182, 128);\n"
"color:rgb(38, 38, 38);"));
        HeaderDescription = new QLabel(HeaderWidget);
        HeaderDescription->setObjectName(QString::fromUtf8("HeaderDescription"));
        HeaderDescription->setGeometry(QRect(50, 6, 391, 71));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        HeaderDescription->setFont(font);
        CompilerDirLabel = new QLabel(Dialog);
        CompilerDirLabel->setObjectName(QString::fromUtf8("CompilerDirLabel"));
        CompilerDirLabel->setGeometry(QRect(50, 110, 371, 17));
        CompilerDirLineEdit = new QLineEdit(Dialog);
        CompilerDirLineEdit->setObjectName(QString::fromUtf8("CompilerDirLineEdit"));
        CompilerDirLineEdit->setGeometry(QRect(50, 130, 751, 25));
        ChangeCompilerDirPushButton = new QPushButton(Dialog);
        ChangeCompilerDirPushButton->setObjectName(QString::fromUtf8("ChangeCompilerDirPushButton"));
        ChangeCompilerDirPushButton->setGeometry(QRect(820, 130, 151, 25));
        WrongFmtCompilerDirLabel = new QLabel(Dialog);
        WrongFmtCompilerDirLabel->setObjectName(QString::fromUtf8("WrongFmtCompilerDirLabel"));
        WrongFmtCompilerDirLabel->setGeometry(QRect(60, 160, 741, 17));
        QFont font1;
        font1.setPointSize(8);
        WrongFmtCompilerDirLabel->setFont(font1);
        WrongFmtCompilerDirLabel->setStyleSheet(QString::fromUtf8("color:rgb(205, 0, 0);"));
        line = new QFrame(Dialog);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(0, 250, 1201, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        CMakeNumRunsLabel = new QLabel(Dialog);
        CMakeNumRunsLabel->setObjectName(QString::fromUtf8("CMakeNumRunsLabel"));
        CMakeNumRunsLabel->setGeometry(QRect(50, 270, 271, 17));
        CMakeNumRunsLineEdit = new QLineEdit(Dialog);
        CMakeNumRunsLineEdit->setObjectName(QString::fromUtf8("CMakeNumRunsLineEdit"));
        CMakeNumRunsLineEdit->setGeometry(QRect(60, 290, 111, 25));
        CMakeNumRunsDecrementButton = new QPushButton(Dialog);
        CMakeNumRunsDecrementButton->setObjectName(QString::fromUtf8("CMakeNumRunsDecrementButton"));
        CMakeNumRunsDecrementButton->setGeometry(QRect(180, 290, 31, 25));
        CMakeNumRunsIncrementButton = new QPushButton(Dialog);
        CMakeNumRunsIncrementButton->setObjectName(QString::fromUtf8("CMakeNumRunsIncrementButton"));
        CMakeNumRunsIncrementButton->setGeometry(QRect(220, 290, 31, 25));
        CMakeNumCoresLabel = new QLabel(Dialog);
        CMakeNumCoresLabel->setObjectName(QString::fromUtf8("CMakeNumCoresLabel"));
        CMakeNumCoresLabel->setGeometry(QRect(460, 305, 271, 17));
        MakeParallelCheckBox = new QCheckBox(Dialog);
        MakeParallelCheckBox->setObjectName(QString::fromUtf8("MakeParallelCheckBox"));
        MakeParallelCheckBox->setGeometry(QRect(440, 270, 381, 23));
        CMakeNumCoresIncrementButton = new QPushButton(Dialog);
        CMakeNumCoresIncrementButton->setObjectName(QString::fromUtf8("CMakeNumCoresIncrementButton"));
        CMakeNumCoresIncrementButton->setGeometry(QRect(900, 300, 31, 25));
        CMakeNumCoresLineEdit = new QLineEdit(Dialog);
        CMakeNumCoresLineEdit->setObjectName(QString::fromUtf8("CMakeNumCoresLineEdit"));
        CMakeNumCoresLineEdit->setGeometry(QRect(740, 300, 111, 25));
        CMakeNumCoresDecrementButton = new QPushButton(Dialog);
        CMakeNumCoresDecrementButton->setObjectName(QString::fromUtf8("CMakeNumCoresDecrementButton"));
        CMakeNumCoresDecrementButton->setGeometry(QRect(860, 300, 31, 25));
        WrongFmtNumRunsLabel = new QLabel(Dialog);
        WrongFmtNumRunsLabel->setObjectName(QString::fromUtf8("WrongFmtNumRunsLabel"));
        WrongFmtNumRunsLabel->setGeometry(QRect(60, 320, 191, 17));
        WrongFmtNumRunsLabel->setFont(font1);
        WrongFmtNumRunsLabel->setStyleSheet(QString::fromUtf8("color:rgb(205, 0, 0);"));
        WrongFmtNumCoresLabel = new QLabel(Dialog);
        WrongFmtNumCoresLabel->setObjectName(QString::fromUtf8("WrongFmtNumCoresLabel"));
        WrongFmtNumCoresLabel->setGeometry(QRect(740, 330, 191, 17));
        WrongFmtNumCoresLabel->setFont(font1);
        WrongFmtNumCoresLabel->setStyleSheet(QString::fromUtf8("color:rgb(205, 0, 0);"));
        line_2 = new QFrame(Dialog);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(10, 370, 1201, 16));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        InputScaleLabel = new QLabel(Dialog);
        InputScaleLabel->setObjectName(QString::fromUtf8("InputScaleLabel"));
        InputScaleLabel->setGeometry(QRect(50, 390, 131, 17));
        OutputScaleLabel = new QLabel(Dialog);
        OutputScaleLabel->setObjectName(QString::fromUtf8("OutputScaleLabel"));
        OutputScaleLabel->setGeometry(QRect(730, 390, 181, 17));
        InputScaleLineEdit = new QLineEdit(Dialog);
        InputScaleLineEdit->setObjectName(QString::fromUtf8("InputScaleLineEdit"));
        InputScaleLineEdit->setGeometry(QRect(50, 410, 351, 25));
        OutputScaleLineEdit = new QLineEdit(Dialog);
        OutputScaleLineEdit->setObjectName(QString::fromUtf8("OutputScaleLineEdit"));
        OutputScaleLineEdit->setGeometry(QRect(730, 410, 351, 25));
        WrongFmtInputScaleLabel = new QLabel(Dialog);
        WrongFmtInputScaleLabel->setObjectName(QString::fromUtf8("WrongFmtInputScaleLabel"));
        WrongFmtInputScaleLabel->setGeometry(QRect(50, 440, 351, 17));
        WrongFmtInputScaleLabel->setFont(font1);
        WrongFmtInputScaleLabel->setStyleSheet(QString::fromUtf8("color:rgb(205, 0, 0);"));
        WrongFmtOutputScaleLabel = new QLabel(Dialog);
        WrongFmtOutputScaleLabel->setObjectName(QString::fromUtf8("WrongFmtOutputScaleLabel"));
        WrongFmtOutputScaleLabel->setGeometry(QRect(730, 440, 351, 17));
        WrongFmtOutputScaleLabel->setFont(font1);
        WrongFmtOutputScaleLabel->setStyleSheet(QString::fromUtf8("color:rgb(205, 0, 0);"));
        line_3 = new QFrame(Dialog);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(0, 470, 1201, 16));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        KcuIpVersionEditLine = new QLineEdit(Dialog);
        KcuIpVersionEditLine->setObjectName(QString::fromUtf8("KcuIpVersionEditLine"));
        KcuIpVersionEditLine->setGeometry(QRect(170, 543, 113, 25));
        QFont font2;
        font2.setPointSize(11);
        KcuIpVersionEditLine->setFont(font2);
        ServerApiVersionEditLine = new QLineEdit(Dialog);
        ServerApiVersionEditLine->setObjectName(QString::fromUtf8("ServerApiVersionEditLine"));
        ServerApiVersionEditLine->setGeometry(QRect(950, 570, 113, 25));
        ServerApiVersionEditLine->setFont(font2);
        ServerApiVersionLabel = new QLabel(Dialog);
        ServerApiVersionLabel->setObjectName(QString::fromUtf8("ServerApiVersionLabel"));
        ServerApiVersionLabel->setGeometry(QRect(790, 567, 151, 31));
        ServerApiVersionLabel->setFont(font2);
        ServerApiVersionLabel->setLayoutDirection(Qt::LeftToRight);
        ServerApiVersionLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        MobileIpVersionEditLine = new QLineEdit(Dialog);
        MobileIpVersionEditLine->setObjectName(QString::fromUtf8("MobileIpVersionEditLine"));
        MobileIpVersionEditLine->setGeometry(QRect(550, 540, 113, 25));
        MobileIpVersionEditLine->setFont(font2);
        MobileApiVersionLabel = new QLabel(Dialog);
        MobileApiVersionLabel->setObjectName(QString::fromUtf8("MobileApiVersionLabel"));
        MobileApiVersionLabel->setGeometry(QRect(390, 567, 151, 31));
        MobileApiVersionLabel->setFont(font2);
        MobileApiVersionLabel->setLayoutDirection(Qt::LeftToRight);
        MobileApiVersionLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ServerIpVersionEditLine = new QLineEdit(Dialog);
        ServerIpVersionEditLine->setObjectName(QString::fromUtf8("ServerIpVersionEditLine"));
        ServerIpVersionEditLine->setGeometry(QRect(950, 540, 113, 25));
        ServerIpVersionEditLine->setFont(font2);
        KcuApiVersionLabel = new QLabel(Dialog);
        KcuApiVersionLabel->setObjectName(QString::fromUtf8("KcuApiVersionLabel"));
        KcuApiVersionLabel->setGeometry(QRect(20, 570, 141, 31));
        KcuApiVersionLabel->setFont(font2);
        KcuApiVersionLabel->setLayoutDirection(Qt::LeftToRight);
        KcuApiVersionLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        ServerDeviceLabel = new QLabel(Dialog);
        ServerDeviceLabel->setObjectName(QString::fromUtf8("ServerDeviceLabel"));
        ServerDeviceLabel->setGeometry(QRect(960, 510, 91, 17));
        ServerDeviceLabel->setFont(font2);
        MobileDeviceLabel = new QLabel(Dialog);
        MobileDeviceLabel->setObjectName(QString::fromUtf8("MobileDeviceLabel"));
        MobileDeviceLabel->setGeometry(QRect(560, 510, 91, 17));
        MobileDeviceLabel->setFont(font2);
        KcuDeviceLabel = new QLabel(Dialog);
        KcuDeviceLabel->setObjectName(QString::fromUtf8("KcuDeviceLabel"));
        KcuDeviceLabel->setGeometry(QRect(190, 510, 71, 17));
        KcuDeviceLabel->setFont(font2);
        KcuApiVersionEditLine = new QLineEdit(Dialog);
        KcuApiVersionEditLine->setObjectName(QString::fromUtf8("KcuApiVersionEditLine"));
        KcuApiVersionEditLine->setGeometry(QRect(170, 573, 113, 25));
        KcuApiVersionEditLine->setFont(font2);
        MobileApiVersionEditLine = new QLineEdit(Dialog);
        MobileApiVersionEditLine->setObjectName(QString::fromUtf8("MobileApiVersionEditLine"));
        MobileApiVersionEditLine->setGeometry(QRect(550, 570, 113, 25));
        MobileApiVersionEditLine->setFont(font2);
        ServerIpCoreVersionLabel = new QLabel(Dialog);
        ServerIpCoreVersionLabel->setObjectName(QString::fromUtf8("ServerIpCoreVersionLabel"));
        ServerIpCoreVersionLabel->setGeometry(QRect(740, 537, 201, 31));
        ServerIpCoreVersionLabel->setFont(font2);
        ServerIpCoreVersionLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        KcuIpCoreVersionLabel = new QLabel(Dialog);
        KcuIpCoreVersionLabel->setObjectName(QString::fromUtf8("KcuIpCoreVersionLabel"));
        KcuIpCoreVersionLabel->setGeometry(QRect(-40, 540, 201, 31));
        KcuIpCoreVersionLabel->setFont(font2);
        KcuIpCoreVersionLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        MobileIpCoreVersionLabel = new QLabel(Dialog);
        MobileIpCoreVersionLabel->setObjectName(QString::fromUtf8("MobileIpCoreVersionLabel"));
        MobileIpCoreVersionLabel->setGeometry(QRect(340, 537, 201, 31));
        MobileIpCoreVersionLabel->setFont(font2);
        MobileIpCoreVersionLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        WrongFmtKcuVersionLabel = new QLabel(Dialog);
        WrongFmtKcuVersionLabel->setObjectName(QString::fromUtf8("WrongFmtKcuVersionLabel"));
        WrongFmtKcuVersionLabel->setGeometry(QRect(180, 600, 111, 17));
        WrongFmtKcuVersionLabel->setFont(font1);
        WrongFmtKcuVersionLabel->setStyleSheet(QString::fromUtf8("color:rgb(205, 0, 0);"));
        WrongFmtMobileVersionLabel = new QLabel(Dialog);
        WrongFmtMobileVersionLabel->setObjectName(QString::fromUtf8("WrongFmtMobileVersionLabel"));
        WrongFmtMobileVersionLabel->setGeometry(QRect(560, 600, 111, 17));
        WrongFmtMobileVersionLabel->setFont(font1);
        WrongFmtMobileVersionLabel->setStyleSheet(QString::fromUtf8("color:rgb(205, 0, 0);"));
        WrongFmtServerVersionLabel = new QLabel(Dialog);
        WrongFmtServerVersionLabel->setObjectName(QString::fromUtf8("WrongFmtServerVersionLabel"));
        WrongFmtServerVersionLabel->setGeometry(QRect(960, 600, 111, 17));
        WrongFmtServerVersionLabel->setFont(font1);
        WrongFmtServerVersionLabel->setStyleSheet(QString::fromUtf8("color:rgb(205, 0, 0);"));
        WrongFmtArchiveNameLabel = new QLabel(Dialog);
        WrongFmtArchiveNameLabel->setObjectName(QString::fromUtf8("WrongFmtArchiveNameLabel"));
        WrongFmtArchiveNameLabel->setGeometry(QRect(60, 230, 741, 17));
        WrongFmtArchiveNameLabel->setFont(font1);
        WrongFmtArchiveNameLabel->setStyleSheet(QString::fromUtf8("color:rgb(205, 0, 0);"));
        ArchiveNameLineEdit = new QLineEdit(Dialog);
        ArchiveNameLineEdit->setObjectName(QString::fromUtf8("ArchiveNameLineEdit"));
        ArchiveNameLineEdit->setGeometry(QRect(50, 200, 751, 25));
        ArchiveNameLabel = new QLabel(Dialog);
        ArchiveNameLabel->setObjectName(QString::fromUtf8("ArchiveNameLabel"));
        ArchiveNameLabel->setGeometry(QRect(50, 180, 371, 17));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Изменение настроек компиляции", nullptr));
        ApplyButton->setText(QCoreApplication::translate("Dialog", "\320\237\321\200\320\270\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        CancelButton->setText(QCoreApplication::translate("Dialog", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
        HeaderDescription->setText(QCoreApplication::translate("Dialog", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270 \320\272\320\276\320\274\320\277\320\270\320\273\321\217\321\206\320\270\320\270", nullptr));
        CompilerDirLabel->setText(QCoreApplication::translate("Dialog", "\320\237\321\203\321\202\321\214 \320\272 \320\264\320\270\321\200\320\265\320\272\321\202\320\276\321\200\320\270\320\270 \321\201 \320\272\320\276\320\274\320\277\320\270\320\273\321\217\321\202\320\276\321\200\320\276\320\274:", nullptr));
        ChangeCompilerDirPushButton->setText(QCoreApplication::translate("Dialog", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        WrongFmtCompilerDirLabel->setText(QCoreApplication::translate("Dialog", "\320\243\320\272\320\260\320\267\320\260\320\275\320\275\320\260\321\217 \320\264\320\270\321\200\320\265\320\272\321\202\320\276\321\200\320\270\321\217 \321\203\320\272\320\260\320\267\320\260\320\275\320\260 \320\275\320\265 \320\277\321\200\320\260\320\262\320\270\320\273\321\214\320\275\320\276 \320\270\320\273\320\270 \320\275\320\265 \321\201\321\203\321\211\320\265\321\201\321\202\320\262\321\203\320\265\321\202", nullptr));
        CMakeNumRunsLabel->setText(QCoreApplication::translate("Dialog", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\267\320\260\320\277\321\203\321\201\320\272\320\276\320\262 \321\201\320\261\320\276\321\200\320\272\320\270 CMake:", nullptr));
        CMakeNumRunsDecrementButton->setText(QCoreApplication::translate("Dialog", "-", nullptr));
        CMakeNumRunsIncrementButton->setText(QCoreApplication::translate("Dialog", "+", nullptr));
        CMakeNumCoresLabel->setText(QCoreApplication::translate("Dialog", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \321\217\320\264\320\265\321\200 \320\264\320\273\321\217 \321\201\320\261\320\276\321\200\320\272\320\270 CMake:", nullptr));
        MakeParallelCheckBox->setText(QCoreApplication::translate("Dialog", "\320\240\320\260\320\267\321\200\320\265\321\210\320\270\321\202\321\214 \320\277\320\260\321\200\320\260\320\273\320\273\320\265\320\273\321\214\320\275\321\203\321\216 \321\201\320\261\320\276\321\200\320\272\321\203 (CMake --n_jobs)", nullptr));
        CMakeNumCoresIncrementButton->setText(QCoreApplication::translate("Dialog", "+", nullptr));
        CMakeNumCoresDecrementButton->setText(QCoreApplication::translate("Dialog", "-", nullptr));
        WrongFmtNumRunsLabel->setText(QCoreApplication::translate("Dialog", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \321\206\320\265\320\273\320\276\320\265 \321\207\320\270\321\201\320\273\320\276", nullptr));
        WrongFmtNumCoresLabel->setText(QCoreApplication::translate("Dialog", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \321\206\320\265\320\273\320\276\320\265 \321\207\320\270\321\201\320\273\320\276", nullptr));
        InputScaleLabel->setText(QCoreApplication::translate("Dialog", "Input tensor scale:", nullptr));
        OutputScaleLabel->setText(QCoreApplication::translate("Dialog", "Output tensor scale:", nullptr));
        WrongFmtInputScaleLabel->setText(QCoreApplication::translate("Dialog", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \321\207\320\270\321\201\320\273\320\276 \321\201 \320\277\320\273\320\260\320\262\320\260\321\216\321\211\320\265\320\271 \321\202\320\276\321\207\320\272\320\276\320\271", nullptr));
        WrongFmtOutputScaleLabel->setText(QCoreApplication::translate("Dialog", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \321\207\320\270\321\201\320\273\320\276 \321\201 \320\277\320\273\320\260\320\262\320\260\321\216\321\211\320\265\320\271 \321\202\320\276\321\207\320\272\320\276\320\271", nullptr));
        ServerApiVersionLabel->setText(QCoreApplication::translate("Dialog", "API version:", nullptr));
        MobileApiVersionLabel->setText(QCoreApplication::translate("Dialog", "API version:", nullptr));
        KcuApiVersionLabel->setText(QCoreApplication::translate("Dialog", "API version:", nullptr));
        ServerDeviceLabel->setText(QCoreApplication::translate("Dialog", "IVA SERVER", nullptr));
        MobileDeviceLabel->setText(QCoreApplication::translate("Dialog", "IVA MOBILE", nullptr));
        KcuDeviceLabel->setText(QCoreApplication::translate("Dialog", "IVA KCU", nullptr));
        ServerIpCoreVersionLabel->setText(QCoreApplication::translate("Dialog", "Core IP version:", nullptr));
        KcuIpCoreVersionLabel->setText(QCoreApplication::translate("Dialog", "Core IP version:", nullptr));
        MobileIpCoreVersionLabel->setText(QCoreApplication::translate("Dialog", "Core IP version:", nullptr));
        WrongFmtKcuVersionLabel->setText(QCoreApplication::translate("Dialog", "\320\235\320\265\320\262\320\265\321\200\320\275\321\213\320\271 \321\204\320\276\321\200\320\274\320\260\321\202", nullptr));
        WrongFmtMobileVersionLabel->setText(QCoreApplication::translate("Dialog", "\320\235\320\265\320\262\320\265\321\200\320\275\321\213\320\271 \321\204\320\276\321\200\320\274\320\260\321\202", nullptr));
        WrongFmtServerVersionLabel->setText(QCoreApplication::translate("Dialog", "\320\235\320\265\320\262\320\265\321\200\320\275\321\213\320\271 \321\204\320\276\321\200\320\274\320\260\321\202", nullptr));
        WrongFmtArchiveNameLabel->setText(QCoreApplication::translate("Dialog", "\320\235\320\265\320\262\320\265\321\200\320\275\321\213\320\271 \321\204\320\276\321\200\320\274\320\260\321\202. \320\236\320\266\320\270\320\264\320\260\320\265\321\202\321\201\321\217 .zip \320\260\321\200\321\205\320\270\320\262 \321\201 \320\275\320\260\320\267\320\262\320\260\320\275\320\270\320\265\320\274 \320\261\320\265\320\267 \321\201\320\270\320\274\320\262\320\276\320\273\320\276\320\262 *|:\"<>?/\\", nullptr));
        ArchiveNameLineEdit->setText(QString());
        ArchiveNameLabel->setText(QCoreApplication::translate("Dialog", "\320\230\320\274\321\217 \320\260\321\200\321\205\320\270\320\262\320\260 \321\201 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\276\320\271:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CompilerSettingsDialog: public Ui_CompilerSettingsDialog {};
} // namespace Ui

#endif // COMPILER_SETTINGS_DIALOG_UI_H
