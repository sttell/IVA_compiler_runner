#ifndef WELCOME_FROM_UI_H
#define WELCOME_FROM_UI_H

#include <QVariant>
#include <QApplication>
#include <QCheckBox>
#include <QWidget>
#include <QWizard>
#include <QWizardPage>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

QT_BEGIN_NAMESPACE

class Ui_WelcomeWizard
{
public:
    QWizardPage *WelcomePage;
    QWidget *HeaderWidget;
    QLabel *PageDescription_3;
    QLabel *WelcomeLabel;
    QLabel *WelcomeSubLabel;
    QWizardPage *CompilerFindPage;
    QWidget *HeaderWidget_2;
    QLabel *WrongFmtCompilerDirectoryLabel;
    QLabel *PageDescription;
    QLabel *InputCompilerPathLabel;
    QLineEdit *InputCompilerPathLineEdit;
    QLabel *InputCompierPathDescriptionLabel;
    QPushButton *ChangeCompilerPathPushButton;
    QWizardPage *CMakeSettingsPage;
    QLabel *WrongFmtNumberCoresLabel;
    QLabel *WrongFmtNumberRunsLabel;
    QLabel *WrongArchiveNameLabel;
    QLabel *NumberCoresLabel;
    QLabel *NumberRunsLabel;
    QCheckBox *MakeParallelCheckBox;
    QLabel *CMakeParametersLabel;
    QWidget *HeaderWidget_3;
    QLabel *PageDescription_2;
    QLineEdit *NumberCoresLineEdit;
    QPushButton *NumCoresDecrement;
    QPushButton *NumCoresIncrement;
    QPushButton *NumRunsDecrement;
    QLineEdit *NumberRunsLineEdit;
    QPushButton *NumRunsIncrement;
    QLabel *ArchiveNameLabel;
    QLineEdit *ArchiveNameLineEdit;
    QWizardPage *MetadataSettingsPage;
    QWidget *HeaderWidget_4;
    QLabel *PageDescription_4;
    QLabel *MetadataSettingsLabel;
    QLabel *InputScaleLabel;
    QLineEdit *InputScaleLineEdit;
    QLineEdit *OutputScaleLineEdit;
    QLabel *WrongFmtInputScaleLabel;
    QLabel *WrongFmtOutputScaleLabel;
    QLabel *OutputScaleLabel;
    QLabel *DescriptionLabel;
    QWizardPage *DevicesSettingsPage;
    QWidget *HeaderWidget_5;
    QLabel *PageDescription_5;
    QLabel *DeviceParametersLabel;
    QLabel *KcuIpCoreVersionLabel;
    QLabel *KcuApiVersionLabel;
    QLineEdit *KcuIpVersionEditLine;
    QLineEdit *KcuApiVersionEditLine;
    QLineEdit *MobileApiVersionEditLine;
    QLabel *MobileApiVersionLabel;
    QLabel *MobileIpCoreVersionLabel;
    QLineEdit *MobileIpVersionEditLine;
    QLineEdit *ServerIpVersionEditLine;
    QLabel *ServerIpCoreVersionLabel;
    QLabel *ServerApiVersionLabel;
    QLineEdit *ServerApiVersionEditLine;
    QLabel *KcuDeviceLabel;
    QLabel *MobileDeviceLabel;
    QLabel *ServerDeviceLabel;

    void setupUi(QWizard *Wizard)
    {

        QFont wrong_fmt_font;
        QString wrong_fmt_stylesheet = "color:rgb(205, 0, 0);";
        wrong_fmt_font.setPointSize(8);


        // Wizard Form
        if (Wizard->objectName().isEmpty())
            Wizard->setObjectName(QString::fromUtf8("Wizard"));

        Wizard->resize(1200, 700);
        Wizard->setStyleSheet(
                    QString::fromUtf8(
                        "background: rgb(38, 38, 38);\n"
                        "color: rgb(238, 238, 236);"
                        )
                    );


        // Welcome Page
        WelcomePage = new QWizardPage();
        WelcomePage->setObjectName(QString::fromUtf8("WelcomePage"));

        HeaderWidget = new QWidget(WelcomePage);
        HeaderWidget->setObjectName(QString::fromUtf8("HeaderWidget"));
        HeaderWidget->setGeometry(QRect(0, 0, 1180, 100));
        HeaderWidget->setStyleSheet(
                    QString::fromUtf8(
                        "background:rgb(0, 182, 128);\n"
                        "color:rgb(38, 38, 38);"
                        )
                    );

        QFont font;
        font.setPointSize(16);
        PageDescription_3 = new QLabel(HeaderWidget);
        PageDescription_3->setObjectName(QString::fromUtf8("PageDescription_3"));
        PageDescription_3->setGeometry(QRect(40, 30, 261, 41));
        PageDescription_3->setFont(font);

        QFont font1;
        font1.setPointSize(30);
        WelcomeLabel = new QLabel(WelcomePage);
        WelcomeLabel->setObjectName(QString::fromUtf8("WelcomeLabel"));
        WelcomeLabel->setGeometry(QRect(70, 270, 811, 71));
        WelcomeLabel->setFont(font1);

        QFont font2;
        font2.setPointSize(14);
        WelcomeSubLabel = new QLabel(WelcomePage);
        WelcomeSubLabel->setObjectName(QString::fromUtf8("WelcomeSubLabel"));
        WelcomeSubLabel->setGeometry(QRect(70, 340, 581, 31));
        WelcomeSubLabel->setFont(font2);

        Wizard->addPage(WelcomePage);


        // Compiler Page
        CompilerFindPage = new QWizardPage();
        CompilerFindPage->setObjectName(QString::fromUtf8("CompilerFindPage"));

        HeaderWidget_2 = new QWidget(CompilerFindPage);
        HeaderWidget_2->setObjectName(QString::fromUtf8("HeaderWidget_2"));
        HeaderWidget_2->setGeometry(QRect(0, 0, 1180, 100));
        HeaderWidget_2->setStyleSheet(
                    QString::fromUtf8(
                        "background:rgb(0, 182, 128);\n"
                        "color:rgb(38, 38, 38);"
                        )
                    );

        WrongFmtCompilerDirectoryLabel = new QLabel(CompilerFindPage);
        WrongFmtCompilerDirectoryLabel->setObjectName(QString::fromUtf8("WrongFmtCompilerDirectoryLabel"));
        WrongFmtCompilerDirectoryLabel->setGeometry(QRect(40, 352, 700, 17));
        WrongFmtCompilerDirectoryLabel->setStyleSheet(wrong_fmt_stylesheet);
        WrongFmtCompilerDirectoryLabel->setFont(wrong_fmt_font);

        PageDescription = new QLabel(HeaderWidget_2);
        PageDescription->setObjectName(QString::fromUtf8("PageDescription"));
        PageDescription->setGeometry(QRect(40, 30, 261, 41));
        PageDescription->setFont(font);

        InputCompilerPathLabel = new QLabel(CompilerFindPage);
        InputCompilerPathLabel->setObjectName(QString::fromUtf8("InputCompilerPathLabel"));
        InputCompilerPathLabel->setGeometry(QRect(40, 270, 811, 31));
        InputCompilerPathLabel->setFont(font);

        InputCompilerPathLineEdit = new QLineEdit(CompilerFindPage);
        InputCompilerPathLineEdit->setObjectName(QString::fromUtf8("InputCompilerPathLineEdit"));
        InputCompilerPathLineEdit->setGeometry(QRect(40, 320, 841, 31));

        InputCompierPathDescriptionLabel = new QLabel(CompilerFindPage);
        InputCompierPathDescriptionLabel->setObjectName(QString::fromUtf8("InputCompierPathDescriptionLabel"));
        InputCompierPathDescriptionLabel->setGeometry(QRect(40, 370, 701, 17));

        ChangeCompilerPathPushButton = new QPushButton(CompilerFindPage);
        ChangeCompilerPathPushButton->setObjectName(QString::fromUtf8("ChangeCompilerPathPushButton"));
        ChangeCompilerPathPushButton->setGeometry(QRect(900, 320, 141, 31));

        Wizard->addPage(CompilerFindPage);


        // CMake Settings Page
        CMakeSettingsPage = new QWizardPage();
        CMakeSettingsPage->setObjectName(QString::fromUtf8("CMakeSettingsPage"));

        QFont font3;
        font3.setPointSize(12);
        NumberCoresLabel = new QLabel(CMakeSettingsPage);
        NumberCoresLabel->setObjectName(QString::fromUtf8("NumberCoresLabel"));
        NumberCoresLabel->setGeometry(QRect(150, 380, 461, 31));
        NumberCoresLabel->setFont(font3);

        NumberRunsLabel = new QLabel(CMakeSettingsPage);
        NumberRunsLabel->setObjectName(QString::fromUtf8("NumberRunsLabel"));
        NumberRunsLabel->setGeometry(QRect(130, 305, 231, 31));
        NumberRunsLabel->setFont(font3);

        MakeParallelCheckBox = new QCheckBox(CMakeSettingsPage);
        MakeParallelCheckBox->setObjectName(QString::fromUtf8("MakeParallelCheckBox"));
        MakeParallelCheckBox->setGeometry(QRect(130, 350, 411, 23));
        MakeParallelCheckBox->setFont(font3);

        CMakeParametersLabel = new QLabel(CMakeSettingsPage);
        CMakeParametersLabel->setObjectName(QString::fromUtf8("CMakeParametersLabel"));
        CMakeParametersLabel->setGeometry(QRect(70, 260, 811, 31));
        CMakeParametersLabel->setFont(font);


        WrongFmtNumberCoresLabel = new QLabel(CMakeSettingsPage);
        WrongFmtNumberCoresLabel->setGeometry(QRect(150, 435, 111, 17));
        WrongFmtNumberCoresLabel->setObjectName(QString::fromUtf8("WrongFmtNumberCoresLabel"));
        WrongFmtNumberCoresLabel->setFont(wrong_fmt_font);
        WrongFmtNumberCoresLabel->setStyleSheet(wrong_fmt_stylesheet);

        WrongFmtNumberRunsLabel = new QLabel(CMakeSettingsPage);
        WrongFmtNumberRunsLabel->setGeometry(QRect(360, 335, 111, 17));
        WrongFmtNumberRunsLabel->setObjectName(QString::fromUtf8("WrongFmtNumberRunsLabel"));
        WrongFmtNumberRunsLabel->setFont(wrong_fmt_font);
        WrongFmtNumberRunsLabel->setStyleSheet(wrong_fmt_stylesheet);

        WrongArchiveNameLabel = new QLabel(CMakeSettingsPage);
        WrongArchiveNameLabel->setGeometry(QRect(870, 335, 400, 17));
        WrongArchiveNameLabel->setObjectName(QString::fromUtf8("WrongArchiveNameLabel"));
        WrongArchiveNameLabel->setFont(wrong_fmt_font);
        WrongArchiveNameLabel->setStyleSheet(wrong_fmt_stylesheet);

        HeaderWidget_3 = new QWidget(CMakeSettingsPage);
        HeaderWidget_3->setObjectName(QString::fromUtf8("HeaderWidget_3"));
        HeaderWidget_3->setGeometry(QRect(0, 0, 1180, 100));
        HeaderWidget_3->setStyleSheet(
                    QString::fromUtf8(
                        "background:rgb(0, 182, 128);\n"
                        "color:rgb(38, 38, 38);"
                        )
                    );

        PageDescription_2 = new QLabel(HeaderWidget_3);
        PageDescription_2->setObjectName(QString::fromUtf8("PageDescription_2"));
        PageDescription_2->setGeometry(QRect(40, 30, 321, 41));
        PageDescription_2->setFont(font);

        NumberCoresLineEdit = new QLineEdit(CMakeSettingsPage);
        NumberCoresLineEdit->setObjectName(QString::fromUtf8("NumberCoresLineEdit"));
        NumberCoresLineEdit->setGeometry(QRect(150, 410, 81, 25));

        NumCoresDecrement = new QPushButton(CMakeSettingsPage);
        NumCoresDecrement->setObjectName(QString::fromUtf8("NumCoresDecrement"));
        NumCoresDecrement->setGeometry(QRect(240, 410, 31, 25));

        NumCoresIncrement = new QPushButton(CMakeSettingsPage);
        NumCoresIncrement->setObjectName(QString::fromUtf8("NumCoresIncrement"));
        NumCoresIncrement->setGeometry(QRect(280, 410, 31, 25));

        QFont font4;
        font4.setPointSize(13);
        NumRunsDecrement = new QPushButton(CMakeSettingsPage);
        NumRunsDecrement->setObjectName(QString::fromUtf8("NumRunsDecrement"));
        NumRunsDecrement->setGeometry(QRect(450, 310, 31, 25));
        NumRunsDecrement->setFont(font4);

        NumberRunsLineEdit = new QLineEdit(CMakeSettingsPage);
        NumberRunsLineEdit->setObjectName(QString::fromUtf8("NumberRunsLineEdit"));
        NumberRunsLineEdit->setGeometry(QRect(360, 310, 81, 25));
        NumberRunsLineEdit->setFont(font4);

        NumRunsIncrement = new QPushButton(CMakeSettingsPage);
        NumRunsIncrement->setObjectName(QString::fromUtf8("NumRunsIncrement"));
        NumRunsIncrement->setGeometry(QRect(490, 310, 31, 25));
        NumRunsIncrement->setFont(font4);

        ArchiveNameLabel = new QLabel(CMakeSettingsPage);
        ArchiveNameLabel->setObjectName(QString::fromUtf8("ArchiveNameLabel"));
        ArchiveNameLabel->setGeometry(QRect(580, 305, 291, 31));
        ArchiveNameLabel->setFont(font3);

        ArchiveNameLineEdit = new QLineEdit(CMakeSettingsPage);
        ArchiveNameLineEdit->setObjectName(QString::fromUtf8("ArchiveNameLineEdit"));
        ArchiveNameLineEdit->setGeometry(QRect(870, 310, 221, 25));

        Wizard->addPage(CMakeSettingsPage);



        // Metadata Settings Page
        MetadataSettingsPage = new QWizardPage();
        MetadataSettingsPage->setObjectName(QString::fromUtf8("MetadataSettingsPage"));

        HeaderWidget_4 = new QWidget(MetadataSettingsPage);
        HeaderWidget_4->setObjectName(QString::fromUtf8("HeaderWidget_4"));
        HeaderWidget_4->setGeometry(QRect(0, 0, 1180, 100));
        HeaderWidget_4->setStyleSheet(
                    QString::fromUtf8(
                        "background:rgb(0, 182, 128);\n"
                        "color:rgb(38, 38, 38);"
                        )
                    );

        PageDescription_4 = new QLabel(HeaderWidget_4);
        PageDescription_4->setObjectName(QString::fromUtf8("PageDescription_4"));
        PageDescription_4->setGeometry(QRect(40, 30, 321, 41));
        PageDescription_4->setFont(font);

        MetadataSettingsLabel = new QLabel(MetadataSettingsPage);
        MetadataSettingsLabel->setObjectName(QString::fromUtf8("MetadataSettingsLabel"));
        MetadataSettingsLabel->setGeometry(QRect(50, 260, 951, 41));
        MetadataSettingsLabel->setFont(font);

        InputScaleLabel = new QLabel(MetadataSettingsPage);
        InputScaleLabel->setObjectName(QString::fromUtf8("InputScaleLabel"));
        InputScaleLabel->setGeometry(QRect(80, 330, 531, 17));
        InputScaleLabel->setFont(font3);

        InputScaleLineEdit = new QLineEdit(MetadataSettingsPage);
        InputScaleLineEdit->setObjectName(QString::fromUtf8("InputScaleLineEdit"));
        InputScaleLineEdit->setGeometry(QRect(100, 360, 411, 25));

        OutputScaleLineEdit = new QLineEdit(MetadataSettingsPage);
        OutputScaleLineEdit->setObjectName(QString::fromUtf8("OutputScaleLineEdit"));
        OutputScaleLineEdit->setGeometry(QRect(100, 460, 411, 25));

        OutputScaleLabel = new QLabel(MetadataSettingsPage);
        OutputScaleLabel->setObjectName(QString::fromUtf8("OutputScaleLabel"));
        OutputScaleLabel->setGeometry(QRect(80, 430, 531, 17));
        OutputScaleLabel->setFont(font3);

        DescriptionLabel = new QLabel(MetadataSettingsPage);
        DescriptionLabel->setObjectName(QString::fromUtf8("DescriptionLabel"));
        DescriptionLabel->setGeometry(QRect(630, 390, 761, 21));

        WrongFmtInputScaleLabel = new QLabel(MetadataSettingsPage);
        WrongFmtInputScaleLabel->setGeometry(QRect(100, 390, 400, 17));
        WrongFmtInputScaleLabel->setObjectName(QString::fromUtf8("WrongFmtInputScaleLabel"));
        WrongFmtInputScaleLabel->setFont(wrong_fmt_font);
        WrongFmtInputScaleLabel->setStyleSheet(wrong_fmt_stylesheet);


        WrongFmtOutputScaleLabel = new QLabel(MetadataSettingsPage);
        WrongFmtOutputScaleLabel->setGeometry(QRect(100, 490, 400, 17));
        WrongFmtOutputScaleLabel->setObjectName(QString::fromUtf8("WrongFmtInputScaleLabel"));
        WrongFmtOutputScaleLabel->setFont(wrong_fmt_font);
        WrongFmtOutputScaleLabel->setStyleSheet(wrong_fmt_stylesheet);

        Wizard->addPage(MetadataSettingsPage);


        // Devices Settings Page
        DevicesSettingsPage = new QWizardPage();
        DevicesSettingsPage->setObjectName(QString::fromUtf8("DevicesSettingsPage"));

        HeaderWidget_5 = new QWidget(DevicesSettingsPage);
        HeaderWidget_5->setObjectName(QString::fromUtf8("HeaderWidget_5"));
        HeaderWidget_5->setGeometry(QRect(0, 0, 1180, 100));
        HeaderWidget_5->setStyleSheet(
                    QString::fromUtf8(
                        "background:rgb(0, 182, 128);\n"
                        "color:rgb(38, 38, 38);"
                        )
                    );

        PageDescription_5 = new QLabel(HeaderWidget_5);
        PageDescription_5->setObjectName(QString::fromUtf8("PageDescription_5"));
        PageDescription_5->setGeometry(QRect(40, 30, 321, 41));
        PageDescription_5->setFont(font);

        DeviceParametersLabel = new QLabel(DevicesSettingsPage);
        DeviceParametersLabel->setObjectName(QString::fromUtf8("DeviceParametersLabel"));
        DeviceParametersLabel->setGeometry(QRect(50, 280, 871, 31));
        DeviceParametersLabel->setFont(font);

        KcuIpCoreVersionLabel = new QLabel(DevicesSettingsPage);
        KcuIpCoreVersionLabel->setObjectName(QString::fromUtf8("KcuIpCoreVersionLabel"));
        KcuIpCoreVersionLabel->setGeometry(QRect(10, 370, 201, 31));
        KcuIpCoreVersionLabel->setFont(font3);
        KcuIpCoreVersionLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        KcuApiVersionLabel = new QLabel(DevicesSettingsPage);
        KcuApiVersionLabel->setObjectName(QString::fromUtf8("KcuApiVersionLabel"));
        KcuApiVersionLabel->setGeometry(QRect(70, 400, 141, 31));
        KcuApiVersionLabel->setFont(font3);
        KcuApiVersionLabel->setLayoutDirection(Qt::LeftToRight);
        KcuApiVersionLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        KcuIpVersionEditLine = new QLineEdit(DevicesSettingsPage);
        KcuIpVersionEditLine->setObjectName(QString::fromUtf8("KcuIpVersionEditLine"));
        KcuIpVersionEditLine->setGeometry(QRect(220, 373, 113, 25));

        KcuApiVersionEditLine = new QLineEdit(DevicesSettingsPage);
        KcuApiVersionEditLine->setObjectName(QString::fromUtf8("KcuApiVersionEditLine"));
        KcuApiVersionEditLine->setGeometry(QRect(220, 403, 113, 25));

        MobileApiVersionEditLine = new QLineEdit(DevicesSettingsPage);
        MobileApiVersionEditLine->setObjectName(QString::fromUtf8("MobileApiVersionEditLine"));
        MobileApiVersionEditLine->setGeometry(QRect(570, 400, 113, 25));

        MobileApiVersionLabel = new QLabel(DevicesSettingsPage);
        MobileApiVersionLabel->setObjectName(QString::fromUtf8("MobileApiVersionLabel"));
        MobileApiVersionLabel->setGeometry(QRect(410, 397, 151, 31));
        MobileApiVersionLabel->setFont(font3);
        MobileApiVersionLabel->setLayoutDirection(Qt::LeftToRight);
        MobileApiVersionLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        MobileIpCoreVersionLabel = new QLabel(DevicesSettingsPage);
        MobileIpCoreVersionLabel->setObjectName(QString::fromUtf8("MobileIpCoreVersionLabel"));
        MobileIpCoreVersionLabel->setGeometry(QRect(360, 367, 201, 31));
        MobileIpCoreVersionLabel->setFont(font3);
        MobileIpCoreVersionLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        MobileIpVersionEditLine = new QLineEdit(DevicesSettingsPage);
        MobileIpVersionEditLine->setObjectName(QString::fromUtf8("MobileIpVersionEditLine"));
        MobileIpVersionEditLine->setGeometry(QRect(570, 370, 113, 25));
        ServerIpVersionEditLine = new QLineEdit(DevicesSettingsPage);
        ServerIpVersionEditLine->setObjectName(QString::fromUtf8("ServerIpVersionEditLine"));
        ServerIpVersionEditLine->setGeometry(QRect(950, 370, 113, 25));

        ServerIpCoreVersionLabel = new QLabel(DevicesSettingsPage);
        ServerIpCoreVersionLabel->setObjectName(QString::fromUtf8("ServerIpCoreVersionLabel"));
        ServerIpCoreVersionLabel->setGeometry(QRect(740, 367, 201, 31));
        ServerIpCoreVersionLabel->setFont(font3);
        ServerIpCoreVersionLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        ServerApiVersionLabel = new QLabel(DevicesSettingsPage);
        ServerApiVersionLabel->setObjectName(QString::fromUtf8("ServerApiVersionLabel"));
        ServerApiVersionLabel->setGeometry(QRect(790, 397, 151, 31));
        ServerApiVersionLabel->setFont(font3);
        ServerApiVersionLabel->setLayoutDirection(Qt::LeftToRight);
        ServerApiVersionLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        ServerApiVersionEditLine = new QLineEdit(DevicesSettingsPage);
        ServerApiVersionEditLine->setObjectName(QString::fromUtf8("ServerApiVersionEditLine"));
        ServerApiVersionEditLine->setGeometry(QRect(950, 400, 113, 25));

        KcuDeviceLabel = new QLabel(DevicesSettingsPage);
        KcuDeviceLabel->setObjectName(QString::fromUtf8("KcuDeviceLabel"));
        KcuDeviceLabel->setGeometry(QRect(240, 340, 71, 17));
        KcuDeviceLabel->setFont(font3);

        MobileDeviceLabel = new QLabel(DevicesSettingsPage);
        MobileDeviceLabel->setObjectName(QString::fromUtf8("MobileDeviceLabel"));
        MobileDeviceLabel->setGeometry(QRect(580, 340, 91, 17));
        MobileDeviceLabel->setFont(font3);

        ServerDeviceLabel = new QLabel(DevicesSettingsPage);
        ServerDeviceLabel->setObjectName(QString::fromUtf8("ServerDeviceLabel"));
        ServerDeviceLabel->setGeometry(QRect(960, 340, 91, 17));
        ServerDeviceLabel->setFont(font3);

        Wizard->addPage(DevicesSettingsPage);

        retranslateUi(Wizard);

        QMetaObject::connectSlotsByName(Wizard);
    } // setupUi

    void retranslateUi(QWizard *Wizard)
    {
        Wizard->setWindowTitle(QCoreApplication::translate("Wizard", "Добро пожаловать в IVA Compiler Runner", nullptr));
        PageDescription_3->setText(QCoreApplication::translate("Wizard", "\320\224\320\276\320\261\321\200\320\276 \320\277\320\276\320\266\320\260\320\273\320\276\320\262\320\260\321\202\321\214!", nullptr));
        WelcomeLabel->setText(QCoreApplication::translate("Wizard", "\320\224\320\276\320\261\321\200\320\276 \320\277\320\276\320\266\320\260\320\273\320\276\320\262\320\260\321\202\321\214 \320\262 IVA Compiler Runner!", nullptr));
        WelcomeSubLabel->setText(QCoreApplication::translate("Wizard", "\320\255\321\202\320\276 \320\275\320\260\321\210 \320\277\320\265\321\200\320\262\321\213\320\271 \320\267\320\260\320\277\321\203\321\201\320\272, \320\277\320\276\321\215\321\202\320\276\320\274\321\203 \320\275\321\203\320\266\320\275\320\276 \320\272\320\276\320\265-\321\207\321\202\320\276 \320\267\320\260\320\277\320\276\320\273\320\275\320\270\321\202\321\214.", nullptr));
        PageDescription->setText(QCoreApplication::translate("Wizard", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270 \320\272\320\276\320\274\320\277\320\270\320\273\321\217\321\202\320\276\321\200\320\260", nullptr));
        InputCompilerPathLabel->setText(QCoreApplication::translate("Wizard", "\320\243\320\272\320\260\320\266\320\270\321\202\320\265 \320\277\321\203\321\202\321\214 \320\272 \320\277\320\260\320\277\320\272\320\265 \321\201 \320\277\320\273\320\260\320\275\320\270\321\200\320\276\320\262\321\211\320\270\320\272\320\276\320\274:", nullptr));
        InputCompierPathDescriptionLabel->setText(QCoreApplication::translate("Wizard", "\320\237\321\203\321\202\321\214 \320\264\320\276\320\273\320\266\320\265\320\275 \321\203\320\272\320\260\320\267\321\213\320\262\320\260\321\202\321\214 \320\275\320\260 \320\277\320\260\320\277\320\272\321\203 \320\262 \320\272\320\276\321\202\320\276\321\200\320\276\320\271 \321\200\320\260\321\201\320\277\320\276\320\273\320\276\320\266\320\265\320\275 \320\277\320\273\320\260\320\275\320\270\321\200\320\276\320\262\321\211\320\270\320\272 \321\201 \320\261\320\270\320\261\320\273\320\270\320\276\321\202\320\265\320\272\320\276\320\271 \320\264\320\273\321\217 IVA.", nullptr));
        ChangeCompilerPathPushButton->setText(QCoreApplication::translate("Wizard", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        NumberCoresLabel->setText(QCoreApplication::translate("Wizard", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \321\217\320\264\320\265\321\200 \320\277\321\200\320\270 \320\270\321\201\320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\320\275\320\270\320\270 \320\277\320\260\321\200\320\260\320\273\320\273\320\265\320\273\321\214\320\275\320\276\320\271 \321\201\320\261\320\276\321\200\320\272\320\270", nullptr));
        NumberRunsLabel->setText(QCoreApplication::translate("Wizard", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\267\320\260\320\277\321\203\321\201\320\272\320\276\320\262 \321\201\320\261\320\276\321\200\320\272\320\270", nullptr));
        MakeParallelCheckBox->setText(QCoreApplication::translate("Wizard", "\320\240\320\260\320\267\321\200\320\265\321\210\320\270\321\202\321\214 \320\277\320\260\321\200\320\260\320\273\320\273\320\265\320\273\321\214\320\275\321\203\321\216 \321\201\320\261\320\276\321\200\320\272\321\203 CMake(--n_jobs)", nullptr));
        CMakeParametersLabel->setText(QCoreApplication::translate("Wizard", "\320\235\320\265\320\276\320\261\321\205\320\276\320\264\320\270\320\274\320\276 \320\275\320\260\321\201\321\202\321\200\320\276\320\270\321\202\321\214 \320\277\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \321\201\320\261\320\276\321\200\320\272\320\270 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274 \321\201 \320\277\320\276\320\274\320\276\321\211\321\214\321\216 \320\277\320\273\320\260\320\275\320\270\321\200\320\276\320\262\321\211\320\270\320\272\320\260:", nullptr));
        PageDescription_2->setText(QCoreApplication::translate("Wizard", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270 \321\201\320\261\320\276\321\200\320\272\320\270 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274", nullptr));
        NumCoresDecrement->setText(QCoreApplication::translate("Wizard", "-", nullptr));
        NumCoresIncrement->setText(QCoreApplication::translate("Wizard", "+", nullptr));
        NumRunsDecrement->setText(QCoreApplication::translate("Wizard", "-", nullptr));
        NumRunsIncrement->setText(QCoreApplication::translate("Wizard", "+", nullptr));
        ArchiveNameLabel->setText(QCoreApplication::translate("Wizard", "\320\232\320\260\320\272 \320\275\320\260\320\267\320\262\320\260\321\202\321\214 .zip \320\260\321\200\321\205\320\270\320\262 \321\201 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\276\320\271:", nullptr));
        PageDescription_4->setText(QCoreApplication::translate("Wizard", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270 \320\274\320\265\321\202\320\260\320\264\320\260\320\275\320\275\321\213\321\205", nullptr));
        MetadataSettingsLabel->setText(QCoreApplication::translate("Wizard", "\320\227\320\264\320\265\321\201\321\214 \320\275\321\203\320\266\320\275\320\276 \320\262\320\262\320\265\321\201\321\202\320\270 \320\275\320\265\320\272\320\276\321\202\320\276\321\200\321\213\320\265 \320\277\320\276\320\273\321\217, \320\275\320\265\320\276\320\261\321\205\320\276\320\264\320\270\320\274\321\213\320\265 \320\264\320\273\321\217 \321\204\320\276\321\200\320\274\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217 \320\274\320\265\321\202\320\260\320\264\320\260\320\275\320\275\321\213\321\205:", nullptr));
        InputScaleLabel->setText(QCoreApplication::translate("Wizard", "Scale \320\262\321\205\320\276\320\264\320\275\320\276\320\271 \320\272\320\260\321\200\321\202\321\213 \320\262 \321\204\320\260\320\271\320\273\320\265 \321\201 \320\274\320\265\321\202\320\260\320\264\320\260\320\275\320\275\321\213\320\274\320\270(float):", nullptr));
        OutputScaleLabel->setText(QCoreApplication::translate("Wizard", "Scale \320\262\321\213\321\205\320\276\320\264\320\275\320\276\320\271 \320\272\320\260\321\200\321\202\321\213 \320\262 \321\204\320\260\320\271\320\273\320\265 \321\201 \320\274\320\265\321\202\320\260\320\264\320\260\320\275\320\275\321\213\320\274\320\270(float):", nullptr));
        DescriptionLabel->setText(QCoreApplication::translate("Wizard", "\320\224\320\260\320\275\320\275\321\213\320\265 \320\277\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \320\275\320\260\321\205\320\276\320\264\321\217\321\202\321\201\321\217 \320\262 metadata->inputs/outputs->scale", nullptr));
        PageDescription_5->setText(QCoreApplication::translate("Wizard", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270 \320\264\321\200\320\260\320\271\320\262\320\265\321\200\320\260 \321\203\321\201\321\202\321\200\320\276\320\271\321\201\321\202\320\262", nullptr));
        DeviceParametersLabel->setText(QCoreApplication::translate("Wizard", "\320\227\320\264\320\265\321\201\321\214 \320\275\321\203\320\266\320\275\320\276 \321\203\320\272\320\260\320\267\320\260\321\202\321\214 \320\262\320\265\321\200\321\201\320\270\320\270 IP/API \320\264\320\273\321\217 \320\262\321\201\320\265\321\205 \320\262\320\276\320\267\320\274\320\276\320\266\320\275\321\213\321\205 \321\203\321\201\321\202\321\200\320\276\320\271\321\201\321\202\320\262(\320\225\321\201\320\273\320\270 \320\276\320\275\320\270 \320\270\320\267\320\262\320\265\321\201\321\202\320\275\321\213):", nullptr));
        KcuIpCoreVersionLabel->setText(QCoreApplication::translate("Wizard", "Core IP version:", nullptr));
        KcuApiVersionLabel->setText(QCoreApplication::translate("Wizard", "API version:", nullptr));
        MobileApiVersionLabel->setText(QCoreApplication::translate("Wizard", "API version:", nullptr));
        MobileIpCoreVersionLabel->setText(QCoreApplication::translate("Wizard", "Core IP version:", nullptr));
        ServerIpCoreVersionLabel->setText(QCoreApplication::translate("Wizard", "Core IP version:", nullptr));
        ServerApiVersionLabel->setText(QCoreApplication::translate("Wizard", "API version:", nullptr));
        KcuDeviceLabel->setText(QCoreApplication::translate("Wizard", "IVA KCU", nullptr));
        MobileDeviceLabel->setText(QCoreApplication::translate("Wizard", "IVA MOBILE", nullptr));
        ServerDeviceLabel->setText(QCoreApplication::translate("Wizard", "IVA SERVER", nullptr));
        WrongFmtNumberCoresLabel->setText(QCoreApplication::translate("Wizard", "Введите число", nullptr));
        WrongFmtNumberRunsLabel->setText(QCoreApplication::translate("Wizard", "Введите число", nullptr));
        WrongArchiveNameLabel->setText(QCoreApplication::translate("Wizard", "Не должно содержать символов *|:\"<>?/\\", nullptr));
        WrongFmtCompilerDirectoryLabel->setText(QCoreApplication::translate("Wizard", "Директория по указанному пути не найдена", nullptr));
        WrongFmtInputScaleLabel->setText(QCoreApplication::translate("Wizard", "Введите число с плавающей точкой", nullptr));
        WrongFmtOutputScaleLabel->setText(QCoreApplication::translate("Wizard", "Введите число с плавающей точкой", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WelcomeWizard: public Ui_WelcomeWizard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // WELCOME_FROM_UI_H
