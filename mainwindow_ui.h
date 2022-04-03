/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *CompilationSettings;
    QAction *RunnerSettings;
    QAction *AnalysisSettings;
    QAction *MainDocs;
    QAction *CompilationDocs;
    QAction *RunnerDocs;
    QAction *AnalysisDocs;
    QWidget *centralwidget;
    QWidget *TabsMenu;
    QLabel *CurrentTimeLabel;
    QLabel *CurrentTime;
    QCheckBox *CompilerTabButton;
    QCheckBox *RunnerTabButton;
    QCheckBox *AnalysisTabButton;
    QCheckBox *SettingsButton;
    QCheckBox *CompilerSettingsButton;
    QCheckBox *RunnerSettingsButton;
    QCheckBox *AnalysisSettingsButton;
    QWidget *MainLogoWidget;
    QWidget *CompilerTabWidget;
    QWidget *HeaderPlaneWidget;
    QLabel *CompilationParametersLabel;
    QPushButton *RedactJsonPushButton;
    QLabel *JsonPathLabel;
    QPushButton *ChangeJsonPathPushButton;
    QLineEdit *JsonPathLineEdit;
    QLabel *WrongFmtJsonPathLabel;
    QPushButton *ChangeWeightsPathPushButton;
    QLabel *WeightsPathLabel;
    QLabel *WrongFmtWeightsPathLabel;
    QLineEdit *WeightsPathLineEdit;
    QLabel *WrongFmtOutputDirPathLabel;
    QPushButton *OutputDirPathPushButton;
    QLabel *OutputDirPathLabel;
    QLineEdit *OutputDirPathLineEdit;
    QLabel *WrongFmtCatalogNameLabel;
    QLineEdit *CatalogNameLineEdit;
    QLabel *CatalogNameLabel;
    QFrame *HorisontalSeparator1;
    QLabel *TensorParametersLabel;
    QLineEdit *OutputPadDownLineEdit;
    QLabel *WrongFmtInputPadDownLabel;
    QLineEdit *InputSizeEditLine;
    QLabel *InputTensorLabel;
    QLabel *WrongFmtOutputSizeLabel;
    QLabel *OutputTensorLabel;
    QLabel *PaddingsDownLabel;
    QLabel *TensorSizeLabel;
    QLineEdit *InputPadUpLineEdit;
    QLabel *WrongFmtInputPadUpLabel;
    QLabel *WrongFmtOutputPadDownLabel;
    QLineEdit *OutputSizeLineEdit;
    QLabel *WrongFmtInputSizeLabel;
    QLineEdit *InputPadDownLineEdit;
    QLabel *WrongFmtOutputPadUpLabel;
    QLabel *PaddingsUpLabel;
    QLineEdit *OutputPadUpLineEdit;
    QFrame *HorisontalSeparator2;
    QLabel *OptimizationOptionsLabel;
    QLabel *CompilationOptionsLabel;
    QCheckBox *AddCompilationLogCheckBox;
    QCheckBox *AddDebugModeCheckBox;
    QCheckBox *AddInputOptimizationCheckBox;
    QCheckBox *AddFilterPreloadCheckBox;
    QCheckBox *AddBiasPreloadCheckBox;
    QCheckBox *AddReorderOptimizationCheckBox;
    QLabel *ExecutionProcessLabel;
    QTextBrowser *CompilerStatusBar;
    QFrame *VerticalSeparator1;
    QCheckBox *CompileProgrammCheckBox;
    QCheckBox *PickleConvertationCheckBox;
    QCheckBox *AddressCheckCheckBox;
    QCheckBox *JsonConvertationCheckBox;
    QLabel *CompilationPipelineLabel;
    QCheckBox *MakeMetadataCheckBox;
    QCheckBox *MakeArchiveCheckBox;
    QLabel *DeviceComboBoxLabel;
    QComboBox *DeviceComboBox;
    QPushButton *RunProcessPushButton;
    QWidget *RunnerTabWidget;
    QWidget *HeaderPlaneWidget_2;
    QLabel *CompilationParametersLabel_2;
    QTextBrowser *RunnerStatusBar;
    QLabel *RunnerProcessLabel;
    QLineEdit *ProgramDirPathLineEdit;
    QLabel *ProgramDirPathLabel;
    QPushButton *ChangeProgramDirPathButton;
    QLabel *WrongFmtProgramDirPathLabel;
    QCheckBox *IsRemoteTensor;
    QFrame *line;
    QLineEdit *InputTensorPathLineEdit;
    QLabel *InputTensorPathLabel;
    QComboBox *RunMode;
    QLabel *RunModeLabel;
    QPushButton *ShowCmdJsonButton;
    QPushButton *ShowMetadataButton;
    QPushButton *ShowCmd0Button;
    QPushButton *ShowCmd1Button;
    QPushButton *ShowCmd3Button;
    QPushButton *ShowCmd2Button;
    QPushButton *ShowCmd4Button;
    QPushButton *ShowCmd5Button;
    QPushButton *ShowOutputTensorButton;
    QPushButton *ShowCacheDataButton;
    QPushButton *ShowTpuDataButton;
    QLabel *PanelLabel;
    QPushButton *RunButton;
    QCheckBox *isGenerateTensor;
    QLineEdit *TensorSizeLineEdit;
    QLabel *GeneratedTensorSizeLabel;
    QLabel *WrongFmtGeneratedTensorSizeLabel;
    QPushButton *ChangeInputTensorPathButton;
    QFrame *line_2;
    QLabel *ProgramPrametersLabel;
    QLabel *InputParametersLabel;
    QProgressBar *RunnerProgressBar;
    QLabel *GeneratedTensorSavePathLabel;
    QLineEdit *GeneratedTensorSavePathLineEdit;
    QLabel *WrongFmtGeneratedTensorSavePathLabel;
    QPushButton *ChangeGeneratedTensorSavePathButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1920, 1000);
        MainWindow->setStyleSheet(QString::fromUtf8("background: rgb(38, 38, 38);\n"
"color: rgb(238, 238, 236);\n"
"\n"
""));
        CompilationSettings = new QAction(MainWindow);
        CompilationSettings->setObjectName(QString::fromUtf8("CompilationSettings"));
        RunnerSettings = new QAction(MainWindow);
        RunnerSettings->setObjectName(QString::fromUtf8("RunnerSettings"));
        AnalysisSettings = new QAction(MainWindow);
        AnalysisSettings->setObjectName(QString::fromUtf8("AnalysisSettings"));
        MainDocs = new QAction(MainWindow);
        MainDocs->setObjectName(QString::fromUtf8("MainDocs"));
        CompilationDocs = new QAction(MainWindow);
        CompilationDocs->setObjectName(QString::fromUtf8("CompilationDocs"));
        RunnerDocs = new QAction(MainWindow);
        RunnerDocs->setObjectName(QString::fromUtf8("RunnerDocs"));
        AnalysisDocs = new QAction(MainWindow);
        AnalysisDocs->setObjectName(QString::fromUtf8("AnalysisDocs"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        TabsMenu = new QWidget(centralwidget);
        TabsMenu->setObjectName(QString::fromUtf8("TabsMenu"));
        TabsMenu->setGeometry(QRect(0, 0, 340, 1081));
        TabsMenu->setStyleSheet(QString::fromUtf8("QCheckBox:hover {\n"
"background: rgb(49, 49, 49);\n"
"}\n"
"QCheckBox::indicator {\n"
"	width: 30px;\n"
"    height: 30px;\n"
"}"));
        CurrentTimeLabel = new QLabel(TabsMenu);
        CurrentTimeLabel->setObjectName(QString::fromUtf8("CurrentTimeLabel"));
        CurrentTimeLabel->setGeometry(QRect(160, 60, 81, 31));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        CurrentTimeLabel->setFont(font);
        CurrentTime = new QLabel(TabsMenu);
        CurrentTime->setObjectName(QString::fromUtf8("CurrentTime"));
        CurrentTime->setGeometry(QRect(160, 100, 121, 31));
        QFont font1;
        font1.setPointSize(19);
        font1.setBold(true);
        CurrentTime->setFont(font1);
        CompilerTabButton = new QCheckBox(TabsMenu);
        CompilerTabButton->setObjectName(QString::fromUtf8("CompilerTabButton"));
        CompilerTabButton->setGeometry(QRect(10, 220, 331, 61));
        QFont font2;
        font2.setPointSize(13);
        CompilerTabButton->setFont(font2);
        CompilerTabButton->setStyleSheet(QString::fromUtf8("QCheckBox {\n"
"	padding-left: 30px;\n"
"	spacing: 50px;\n"
"}\n"
"QCheckBox::indicator {\n"
"	image: url(\"img/build.png\");\n"
"}"));
        CompilerTabButton->setIconSize(QSize(30, 30));
        RunnerTabButton = new QCheckBox(TabsMenu);
        RunnerTabButton->setObjectName(QString::fromUtf8("RunnerTabButton"));
        RunnerTabButton->setGeometry(QRect(10, 280, 331, 61));
        RunnerTabButton->setFont(font2);
        RunnerTabButton->setStyleSheet(QString::fromUtf8("QCheckBox {\n"
"	padding-left: 30px;\n"
"	spacing: 50px;\n"
"}\n"
"QCheckBox::indicator {\n"
"	image: url(\"img/runner.png\");\n"
"}"));
        RunnerTabButton->setIconSize(QSize(30, 30));
        AnalysisTabButton = new QCheckBox(TabsMenu);
        AnalysisTabButton->setObjectName(QString::fromUtf8("AnalysisTabButton"));
        AnalysisTabButton->setGeometry(QRect(10, 340, 331, 61));
        AnalysisTabButton->setFont(font2);
        AnalysisTabButton->setStyleSheet(QString::fromUtf8("QCheckBox {\n"
"	padding-left: 30px;\n"
"	spacing: 50px;\n"
"}\n"
"QCheckBox::indicator {\n"
"	image: url(\"img/analysis.png\");\n"
"}"));
        AnalysisTabButton->setIconSize(QSize(30, 30));
        SettingsButton = new QCheckBox(TabsMenu);
        SettingsButton->setObjectName(QString::fromUtf8("SettingsButton"));
        SettingsButton->setGeometry(QRect(10, 940, 331, 61));
        SettingsButton->setFont(font2);
        SettingsButton->setStyleSheet(QString::fromUtf8("QCheckBox {\n"
"	padding-left: 30px;\n"
"	spacing: 50px;\n"
"}\n"
"QCheckBox::indicator {\n"
"	image: url(\"img/settings.png\");\n"
"}"));
        SettingsButton->setIconSize(QSize(30, 30));
        CompilerSettingsButton = new QCheckBox(TabsMenu);
        CompilerSettingsButton->setObjectName(QString::fromUtf8("CompilerSettingsButton"));
        CompilerSettingsButton->setGeometry(QRect(10, 820, 331, 61));
        CompilerSettingsButton->setFont(font2);
        CompilerSettingsButton->setStyleSheet(QString::fromUtf8("QCheckBox {\n"
"	padding-left: 30px;\n"
"	spacing: 30px;\n"
"}\n"
"QCheckBox::indicator {\n"
"	image: url(\"img/build.png\");\n"
"}"));
        CompilerSettingsButton->setIconSize(QSize(30, 30));
        RunnerSettingsButton = new QCheckBox(TabsMenu);
        RunnerSettingsButton->setObjectName(QString::fromUtf8("RunnerSettingsButton"));
        RunnerSettingsButton->setGeometry(QRect(10, 880, 331, 61));
        RunnerSettingsButton->setFont(font2);
        RunnerSettingsButton->setStyleSheet(QString::fromUtf8("QCheckBox {\n"
"	padding-left: 30px;\n"
"	spacing: 30px;\n"
"	\n"
"}\n"
"QCheckBox::indicator {\n"
"	image: url(\"img/runner.png\");\n"
"}"));
        RunnerSettingsButton->setIconSize(QSize(30, 30));
        AnalysisSettingsButton = new QCheckBox(TabsMenu);
        AnalysisSettingsButton->setObjectName(QString::fromUtf8("AnalysisSettingsButton"));
        AnalysisSettingsButton->setGeometry(QRect(10, 940, 331, 61));
        AnalysisSettingsButton->setFont(font2);
        AnalysisSettingsButton->setStyleSheet(QString::fromUtf8("QCheckBox {\n"
"	padding-left: 30px;\n"
"	spacing: 30px;\n"
"}\n"
"QCheckBox::indicator {\n"
"	image: url(\"img/analysis.png\");\n"
"}"));
        AnalysisSettingsButton->setIconSize(QSize(30, 30));
        MainLogoWidget = new QWidget(TabsMenu);
        MainLogoWidget->setObjectName(QString::fromUtf8("MainLogoWidget"));
        MainLogoWidget->setGeometry(QRect(10, 50, 121, 101));
        MainLogoWidget->setStyleSheet(QString::fromUtf8("image: url(\"img/build.png\");"));
        CurrentTimeLabel->raise();
        CurrentTime->raise();
        CompilerTabButton->raise();
        RunnerTabButton->raise();
        AnalysisTabButton->raise();
        CompilerSettingsButton->raise();
        RunnerSettingsButton->raise();
        AnalysisSettingsButton->raise();
        MainLogoWidget->raise();
        SettingsButton->raise();
        CompilerTabWidget = new QWidget(centralwidget);
        CompilerTabWidget->setObjectName(QString::fromUtf8("CompilerTabWidget"));
        CompilerTabWidget->setGeometry(QRect(340, -20, 1581, 1100));
        CompilerTabWidget->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"border-radius: 5px;\n"
"background: rgb(0, 182, 128);\n"
"color: rgb(46, 52, 54);\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"background: rgb(0, 204, 143);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"background: rgb(0, 166, 117);\n"
"}"));
        HeaderPlaneWidget = new QWidget(CompilerTabWidget);
        HeaderPlaneWidget->setObjectName(QString::fromUtf8("HeaderPlaneWidget"));
        HeaderPlaneWidget->setGeometry(QRect(0, 20, 1581, 71));
        HeaderPlaneWidget->setStyleSheet(QString::fromUtf8("background: rgb(0, 182, 128)"));
        CompilationParametersLabel = new QLabel(HeaderPlaneWidget);
        CompilationParametersLabel->setObjectName(QString::fromUtf8("CompilationParametersLabel"));
        CompilationParametersLabel->setGeometry(QRect(30, 24, 271, 21));
        CompilationParametersLabel->setFont(font);
        CompilationParametersLabel->setStyleSheet(QString::fromUtf8("color:rgb(46, 52, 54)"));
        RedactJsonPushButton = new QPushButton(CompilerTabWidget);
        RedactJsonPushButton->setObjectName(QString::fromUtf8("RedactJsonPushButton"));
        RedactJsonPushButton->setGeometry(QRect(740, 140, 141, 25));
        JsonPathLabel = new QLabel(CompilerTabWidget);
        JsonPathLabel->setObjectName(QString::fromUtf8("JsonPathLabel"));
        JsonPathLabel->setGeometry(QRect(20, 120, 221, 17));
        ChangeJsonPathPushButton = new QPushButton(CompilerTabWidget);
        ChangeJsonPathPushButton->setObjectName(QString::fromUtf8("ChangeJsonPathPushButton"));
        ChangeJsonPathPushButton->setGeometry(QRect(600, 140, 110, 25));
        JsonPathLineEdit = new QLineEdit(CompilerTabWidget);
        JsonPathLineEdit->setObjectName(QString::fromUtf8("JsonPathLineEdit"));
        JsonPathLineEdit->setGeometry(QRect(20, 140, 550, 25));
        WrongFmtJsonPathLabel = new QLabel(CompilerTabWidget);
        WrongFmtJsonPathLabel->setObjectName(QString::fromUtf8("WrongFmtJsonPathLabel"));
        WrongFmtJsonPathLabel->setGeometry(QRect(30, 170, 541, 17));
        QFont font3;
        font3.setPointSize(8);
        WrongFmtJsonPathLabel->setFont(font3);
        WrongFmtJsonPathLabel->setStyleSheet(QString::fromUtf8("color:rgb(241, 45, 45)"));
        ChangeWeightsPathPushButton = new QPushButton(CompilerTabWidget);
        ChangeWeightsPathPushButton->setObjectName(QString::fromUtf8("ChangeWeightsPathPushButton"));
        ChangeWeightsPathPushButton->setGeometry(QRect(600, 220, 110, 25));
        WeightsPathLabel = new QLabel(CompilerTabWidget);
        WeightsPathLabel->setObjectName(QString::fromUtf8("WeightsPathLabel"));
        WeightsPathLabel->setGeometry(QRect(20, 200, 221, 17));
        WrongFmtWeightsPathLabel = new QLabel(CompilerTabWidget);
        WrongFmtWeightsPathLabel->setObjectName(QString::fromUtf8("WrongFmtWeightsPathLabel"));
        WrongFmtWeightsPathLabel->setGeometry(QRect(30, 245, 541, 17));
        WrongFmtWeightsPathLabel->setFont(font3);
        WrongFmtWeightsPathLabel->setStyleSheet(QString::fromUtf8("color:rgb(241, 45, 45)"));
        WeightsPathLineEdit = new QLineEdit(CompilerTabWidget);
        WeightsPathLineEdit->setObjectName(QString::fromUtf8("WeightsPathLineEdit"));
        WeightsPathLineEdit->setGeometry(QRect(20, 220, 550, 25));
        WrongFmtOutputDirPathLabel = new QLabel(CompilerTabWidget);
        WrongFmtOutputDirPathLabel->setObjectName(QString::fromUtf8("WrongFmtOutputDirPathLabel"));
        WrongFmtOutputDirPathLabel->setGeometry(QRect(30, 315, 541, 17));
        WrongFmtOutputDirPathLabel->setFont(font3);
        WrongFmtOutputDirPathLabel->setStyleSheet(QString::fromUtf8("color:rgb(241, 45, 45)"));
        OutputDirPathPushButton = new QPushButton(CompilerTabWidget);
        OutputDirPathPushButton->setObjectName(QString::fromUtf8("OutputDirPathPushButton"));
        OutputDirPathPushButton->setGeometry(QRect(600, 290, 110, 25));
        OutputDirPathLabel = new QLabel(CompilerTabWidget);
        OutputDirPathLabel->setObjectName(QString::fromUtf8("OutputDirPathLabel"));
        OutputDirPathLabel->setGeometry(QRect(20, 270, 271, 17));
        OutputDirPathLineEdit = new QLineEdit(CompilerTabWidget);
        OutputDirPathLineEdit->setObjectName(QString::fromUtf8("OutputDirPathLineEdit"));
        OutputDirPathLineEdit->setGeometry(QRect(20, 290, 550, 25));
        WrongFmtCatalogNameLabel = new QLabel(CompilerTabWidget);
        WrongFmtCatalogNameLabel->setObjectName(QString::fromUtf8("WrongFmtCatalogNameLabel"));
        WrongFmtCatalogNameLabel->setGeometry(QRect(30, 390, 541, 17));
        WrongFmtCatalogNameLabel->setFont(font3);
        WrongFmtCatalogNameLabel->setStyleSheet(QString::fromUtf8("color:rgb(241, 45, 45)"));
        CatalogNameLineEdit = new QLineEdit(CompilerTabWidget);
        CatalogNameLineEdit->setObjectName(QString::fromUtf8("CatalogNameLineEdit"));
        CatalogNameLineEdit->setGeometry(QRect(20, 365, 550, 25));
        CatalogNameLabel = new QLabel(CompilerTabWidget);
        CatalogNameLabel->setObjectName(QString::fromUtf8("CatalogNameLabel"));
        CatalogNameLabel->setGeometry(QRect(20, 345, 251, 17));
        HorisontalSeparator1 = new QFrame(CompilerTabWidget);
        HorisontalSeparator1->setObjectName(QString::fromUtf8("HorisontalSeparator1"));
        HorisontalSeparator1->setGeometry(QRect(10, 410, 907, 16));
        HorisontalSeparator1->setFrameShape(QFrame::HLine);
        HorisontalSeparator1->setFrameShadow(QFrame::Sunken);
        TensorParametersLabel = new QLabel(CompilerTabWidget);
        TensorParametersLabel->setObjectName(QString::fromUtf8("TensorParametersLabel"));
        TensorParametersLabel->setGeometry(QRect(30, 440, 221, 21));
        QFont font4;
        font4.setPointSize(14);
        font4.setBold(true);
        TensorParametersLabel->setFont(font4);
        TensorParametersLabel->setStyleSheet(QString::fromUtf8("color: rgb(0, 182, 128)"));
        OutputPadDownLineEdit = new QLineEdit(CompilerTabWidget);
        OutputPadDownLineEdit->setObjectName(QString::fromUtf8("OutputPadDownLineEdit"));
        OutputPadDownLineEdit->setGeometry(QRect(680, 570, 201, 25));
        WrongFmtInputPadDownLabel = new QLabel(CompilerTabWidget);
        WrongFmtInputPadDownLabel->setObjectName(QString::fromUtf8("WrongFmtInputPadDownLabel"));
        WrongFmtInputPadDownLabel->setGeometry(QRect(690, 530, 191, 17));
        WrongFmtInputPadDownLabel->setFont(font3);
        WrongFmtInputPadDownLabel->setStyleSheet(QString::fromUtf8("color:rgb(241, 45, 45)"));
        InputSizeEditLine = new QLineEdit(CompilerTabWidget);
        InputSizeEditLine->setObjectName(QString::fromUtf8("InputSizeEditLine"));
        InputSizeEditLine->setGeometry(QRect(280, 505, 121, 21));
        InputTensorLabel = new QLabel(CompilerTabWidget);
        InputTensorLabel->setObjectName(QString::fromUtf8("InputTensorLabel"));
        InputTensorLabel->setGeometry(QRect(130, 505, 141, 20));
        QFont font5;
        font5.setPointSize(12);
        font5.setBold(true);
        InputTensorLabel->setFont(font5);
        InputTensorLabel->setStyleSheet(QString::fromUtf8("color: rgb(0, 182, 128)"));
        WrongFmtOutputSizeLabel = new QLabel(CompilerTabWidget);
        WrongFmtOutputSizeLabel->setObjectName(QString::fromUtf8("WrongFmtOutputSizeLabel"));
        WrongFmtOutputSizeLabel->setGeometry(QRect(290, 595, 151, 17));
        WrongFmtOutputSizeLabel->setFont(font3);
        WrongFmtOutputSizeLabel->setStyleSheet(QString::fromUtf8("color:rgb(241, 45, 45)"));
        OutputTensorLabel = new QLabel(CompilerTabWidget);
        OutputTensorLabel->setObjectName(QString::fromUtf8("OutputTensorLabel"));
        OutputTensorLabel->setGeometry(QRect(120, 570, 151, 20));
        OutputTensorLabel->setFont(font5);
        OutputTensorLabel->setStyleSheet(QString::fromUtf8("color: rgb(0, 182, 128)"));
        PaddingsDownLabel = new QLabel(CompilerTabWidget);
        PaddingsDownLabel->setObjectName(QString::fromUtf8("PaddingsDownLabel"));
        PaddingsDownLabel->setGeometry(QRect(680, 470, 201, 20));
        TensorSizeLabel = new QLabel(CompilerTabWidget);
        TensorSizeLabel->setObjectName(QString::fromUtf8("TensorSizeLabel"));
        TensorSizeLabel->setGeometry(QRect(280, 470, 131, 17));
        QFont font6;
        font6.setBold(false);
        TensorSizeLabel->setFont(font6);
        TensorSizeLabel->setStyleSheet(QString::fromUtf8(""));
        InputPadUpLineEdit = new QLineEdit(CompilerTabWidget);
        InputPadUpLineEdit->setObjectName(QString::fromUtf8("InputPadUpLineEdit"));
        InputPadUpLineEdit->setGeometry(QRect(442, 505, 201, 25));
        WrongFmtInputPadUpLabel = new QLabel(CompilerTabWidget);
        WrongFmtInputPadUpLabel->setObjectName(QString::fromUtf8("WrongFmtInputPadUpLabel"));
        WrongFmtInputPadUpLabel->setGeometry(QRect(450, 530, 191, 17));
        WrongFmtInputPadUpLabel->setFont(font3);
        WrongFmtInputPadUpLabel->setStyleSheet(QString::fromUtf8("color:rgb(241, 45, 45)"));
        WrongFmtOutputPadDownLabel = new QLabel(CompilerTabWidget);
        WrongFmtOutputPadDownLabel->setObjectName(QString::fromUtf8("WrongFmtOutputPadDownLabel"));
        WrongFmtOutputPadDownLabel->setGeometry(QRect(690, 595, 191, 17));
        WrongFmtOutputPadDownLabel->setFont(font3);
        WrongFmtOutputPadDownLabel->setStyleSheet(QString::fromUtf8("color:rgb(241, 45, 45)"));
        OutputSizeLineEdit = new QLineEdit(CompilerTabWidget);
        OutputSizeLineEdit->setObjectName(QString::fromUtf8("OutputSizeLineEdit"));
        OutputSizeLineEdit->setGeometry(QRect(280, 570, 121, 25));
        WrongFmtInputSizeLabel = new QLabel(CompilerTabWidget);
        WrongFmtInputSizeLabel->setObjectName(QString::fromUtf8("WrongFmtInputSizeLabel"));
        WrongFmtInputSizeLabel->setGeometry(QRect(290, 530, 141, 17));
        WrongFmtInputSizeLabel->setFont(font3);
        WrongFmtInputSizeLabel->setStyleSheet(QString::fromUtf8("color:rgb(241, 45, 45)"));
        InputPadDownLineEdit = new QLineEdit(CompilerTabWidget);
        InputPadDownLineEdit->setObjectName(QString::fromUtf8("InputPadDownLineEdit"));
        InputPadDownLineEdit->setGeometry(QRect(680, 505, 201, 25));
        WrongFmtOutputPadUpLabel = new QLabel(CompilerTabWidget);
        WrongFmtOutputPadUpLabel->setObjectName(QString::fromUtf8("WrongFmtOutputPadUpLabel"));
        WrongFmtOutputPadUpLabel->setGeometry(QRect(450, 595, 191, 17));
        WrongFmtOutputPadUpLabel->setFont(font3);
        WrongFmtOutputPadUpLabel->setStyleSheet(QString::fromUtf8("color:rgb(241, 45, 45)"));
        PaddingsUpLabel = new QLabel(CompilerTabWidget);
        PaddingsUpLabel->setObjectName(QString::fromUtf8("PaddingsUpLabel"));
        PaddingsUpLabel->setGeometry(QRect(440, 470, 201, 20));
        OutputPadUpLineEdit = new QLineEdit(CompilerTabWidget);
        OutputPadUpLineEdit->setObjectName(QString::fromUtf8("OutputPadUpLineEdit"));
        OutputPadUpLineEdit->setGeometry(QRect(442, 570, 201, 25));
        HorisontalSeparator2 = new QFrame(CompilerTabWidget);
        HorisontalSeparator2->setObjectName(QString::fromUtf8("HorisontalSeparator2"));
        HorisontalSeparator2->setGeometry(QRect(10, 640, 907, 16));
        HorisontalSeparator2->setFrameShape(QFrame::HLine);
        HorisontalSeparator2->setFrameShadow(QFrame::Sunken);
        OptimizationOptionsLabel = new QLabel(CompilerTabWidget);
        OptimizationOptionsLabel->setObjectName(QString::fromUtf8("OptimizationOptionsLabel"));
        OptimizationOptionsLabel->setGeometry(QRect(450, 680, 211, 21));
        OptimizationOptionsLabel->setFont(font4);
        OptimizationOptionsLabel->setStyleSheet(QString::fromUtf8("color: rgb(0, 182, 128)"));
        CompilationOptionsLabel = new QLabel(CompilerTabWidget);
        CompilationOptionsLabel->setObjectName(QString::fromUtf8("CompilationOptionsLabel"));
        CompilationOptionsLabel->setGeometry(QRect(40, 680, 201, 21));
        CompilationOptionsLabel->setFont(font4);
        CompilationOptionsLabel->setStyleSheet(QString::fromUtf8("color: rgb(0, 182, 128)"));
        AddCompilationLogCheckBox = new QCheckBox(CompilerTabWidget);
        AddCompilationLogCheckBox->setObjectName(QString::fromUtf8("AddCompilationLogCheckBox"));
        AddCompilationLogCheckBox->setGeometry(QRect(40, 760, 401, 23));
        AddDebugModeCheckBox = new QCheckBox(CompilerTabWidget);
        AddDebugModeCheckBox->setObjectName(QString::fromUtf8("AddDebugModeCheckBox"));
        AddDebugModeCheckBox->setGeometry(QRect(460, 830, 401, 23));
        AddInputOptimizationCheckBox = new QCheckBox(CompilerTabWidget);
        AddInputOptimizationCheckBox->setObjectName(QString::fromUtf8("AddInputOptimizationCheckBox"));
        AddInputOptimizationCheckBox->setGeometry(QRect(460, 770, 401, 23));
        AddFilterPreloadCheckBox = new QCheckBox(CompilerTabWidget);
        AddFilterPreloadCheckBox->setObjectName(QString::fromUtf8("AddFilterPreloadCheckBox"));
        AddFilterPreloadCheckBox->setGeometry(QRect(460, 710, 401, 23));
        AddBiasPreloadCheckBox = new QCheckBox(CompilerTabWidget);
        AddBiasPreloadCheckBox->setObjectName(QString::fromUtf8("AddBiasPreloadCheckBox"));
        AddBiasPreloadCheckBox->setGeometry(QRect(460, 740, 401, 23));
        AddReorderOptimizationCheckBox = new QCheckBox(CompilerTabWidget);
        AddReorderOptimizationCheckBox->setObjectName(QString::fromUtf8("AddReorderOptimizationCheckBox"));
        AddReorderOptimizationCheckBox->setGeometry(QRect(460, 800, 401, 23));
        ExecutionProcessLabel = new QLabel(CompilerTabWidget);
        ExecutionProcessLabel->setObjectName(QString::fromUtf8("ExecutionProcessLabel"));
        ExecutionProcessLabel->setGeometry(QRect(10, 880, 161, 17));
        QFont font7;
        font7.setBold(true);
        ExecutionProcessLabel->setFont(font7);
        ExecutionProcessLabel->setStyleSheet(QString::fromUtf8("color: rgb(0, 182, 128)"));
        CompilerStatusBar = new QTextBrowser(CompilerTabWidget);
        CompilerStatusBar->setObjectName(QString::fromUtf8("CompilerStatusBar"));
        CompilerStatusBar->setGeometry(QRect(10, 900, 1561, 131));
        VerticalSeparator1 = new QFrame(CompilerTabWidget);
        VerticalSeparator1->setObjectName(QString::fromUtf8("VerticalSeparator1"));
        VerticalSeparator1->setGeometry(QRect(910, 99, 20, 801));
        VerticalSeparator1->setFrameShape(QFrame::VLine);
        VerticalSeparator1->setFrameShadow(QFrame::Sunken);
        CompileProgrammCheckBox = new QCheckBox(CompilerTabWidget);
        CompileProgrammCheckBox->setObjectName(QString::fromUtf8("CompileProgrammCheckBox"));
        CompileProgrammCheckBox->setGeometry(QRect(1050, 360, 301, 23));
        CompileProgrammCheckBox->setFont(font5);
        PickleConvertationCheckBox = new QCheckBox(CompilerTabWidget);
        PickleConvertationCheckBox->setObjectName(QString::fromUtf8("PickleConvertationCheckBox"));
        PickleConvertationCheckBox->setGeometry(QRect(1050, 260, 421, 23));
        PickleConvertationCheckBox->setFont(font5);
        AddressCheckCheckBox = new QCheckBox(CompilerTabWidget);
        AddressCheckCheckBox->setObjectName(QString::fromUtf8("AddressCheckCheckBox"));
        AddressCheckCheckBox->setGeometry(QRect(1050, 310, 421, 23));
        AddressCheckCheckBox->setFont(font5);
        JsonConvertationCheckBox = new QCheckBox(CompilerTabWidget);
        JsonConvertationCheckBox->setObjectName(QString::fromUtf8("JsonConvertationCheckBox"));
        JsonConvertationCheckBox->setGeometry(QRect(1050, 210, 431, 23));
        JsonConvertationCheckBox->setFont(font5);
        CompilationPipelineLabel = new QLabel(CompilerTabWidget);
        CompilationPipelineLabel->setObjectName(QString::fromUtf8("CompilationPipelineLabel"));
        CompilationPipelineLabel->setGeometry(QRect(1140, 160, 281, 31));
        QFont font8;
        font8.setPointSize(18);
        font8.setBold(true);
        CompilationPipelineLabel->setFont(font8);
        CompilationPipelineLabel->setStyleSheet(QString::fromUtf8("color: rgb(0, 182, 128)"));
        MakeMetadataCheckBox = new QCheckBox(CompilerTabWidget);
        MakeMetadataCheckBox->setObjectName(QString::fromUtf8("MakeMetadataCheckBox"));
        MakeMetadataCheckBox->setGeometry(QRect(1050, 410, 411, 23));
        MakeMetadataCheckBox->setFont(font5);
        MakeArchiveCheckBox = new QCheckBox(CompilerTabWidget);
        MakeArchiveCheckBox->setObjectName(QString::fromUtf8("MakeArchiveCheckBox"));
        MakeArchiveCheckBox->setGeometry(QRect(1050, 460, 411, 23));
        MakeArchiveCheckBox->setFont(font5);
        DeviceComboBoxLabel = new QLabel(CompilerTabWidget);
        DeviceComboBoxLabel->setObjectName(QString::fromUtf8("DeviceComboBoxLabel"));
        DeviceComboBoxLabel->setGeometry(QRect(1180, 600, 201, 21));
        DeviceComboBoxLabel->setFont(font4);
        DeviceComboBoxLabel->setStyleSheet(QString::fromUtf8("color:rgb(0, 182, 128)"));
        DeviceComboBox = new QComboBox(CompilerTabWidget);
        DeviceComboBox->addItem(QString());
        DeviceComboBox->addItem(QString());
        DeviceComboBox->addItem(QString());
        DeviceComboBox->setObjectName(QString::fromUtf8("DeviceComboBox"));
        DeviceComboBox->setGeometry(QRect(1100, 630, 291, 41));
        DeviceComboBox->setFont(font5);
        RunProcessPushButton = new QPushButton(CompilerTabWidget);
        RunProcessPushButton->setObjectName(QString::fromUtf8("RunProcessPushButton"));
        RunProcessPushButton->setGeometry(QRect(1100, 800, 291, 60));
        RunProcessPushButton->setFont(font4);
        HeaderPlaneWidget->raise();
        RedactJsonPushButton->raise();
        JsonPathLabel->raise();
        ChangeJsonPathPushButton->raise();
        JsonPathLineEdit->raise();
        WrongFmtJsonPathLabel->raise();
        ChangeWeightsPathPushButton->raise();
        WeightsPathLabel->raise();
        WrongFmtWeightsPathLabel->raise();
        WeightsPathLineEdit->raise();
        WrongFmtOutputDirPathLabel->raise();
        OutputDirPathPushButton->raise();
        OutputDirPathLabel->raise();
        OutputDirPathLineEdit->raise();
        WrongFmtCatalogNameLabel->raise();
        CatalogNameLineEdit->raise();
        CatalogNameLabel->raise();
        TensorParametersLabel->raise();
        OutputPadDownLineEdit->raise();
        WrongFmtInputPadDownLabel->raise();
        InputSizeEditLine->raise();
        InputTensorLabel->raise();
        WrongFmtOutputSizeLabel->raise();
        OutputTensorLabel->raise();
        PaddingsDownLabel->raise();
        TensorSizeLabel->raise();
        InputPadUpLineEdit->raise();
        WrongFmtInputPadUpLabel->raise();
        WrongFmtOutputPadDownLabel->raise();
        OutputSizeLineEdit->raise();
        WrongFmtInputSizeLabel->raise();
        InputPadDownLineEdit->raise();
        WrongFmtOutputPadUpLabel->raise();
        PaddingsUpLabel->raise();
        OutputPadUpLineEdit->raise();
        OptimizationOptionsLabel->raise();
        CompilationOptionsLabel->raise();
        AddCompilationLogCheckBox->raise();
        AddDebugModeCheckBox->raise();
        AddInputOptimizationCheckBox->raise();
        AddFilterPreloadCheckBox->raise();
        AddBiasPreloadCheckBox->raise();
        AddReorderOptimizationCheckBox->raise();
        ExecutionProcessLabel->raise();
        CompilerStatusBar->raise();
        VerticalSeparator1->raise();
        CompileProgrammCheckBox->raise();
        PickleConvertationCheckBox->raise();
        AddressCheckCheckBox->raise();
        JsonConvertationCheckBox->raise();
        CompilationPipelineLabel->raise();
        MakeMetadataCheckBox->raise();
        MakeArchiveCheckBox->raise();
        DeviceComboBoxLabel->raise();
        DeviceComboBox->raise();
        RunProcessPushButton->raise();
        HorisontalSeparator2->raise();
        HorisontalSeparator1->raise();
        RunnerTabWidget = new QWidget(centralwidget);
        RunnerTabWidget->setObjectName(QString::fromUtf8("RunnerTabWidget"));
        RunnerTabWidget->setGeometry(QRect(340, 0, 1580, 1100));
        RunnerTabWidget->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"border-radius: 5px;\n"
"background: rgb(0, 182, 128);\n"
"color: rgb(46, 52, 54);\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"background: rgb(0, 204, 143);\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"background: rgb(0, 166, 117);\n"
"}\n"
"\n"
"QPushButton:disabled {\n"
"background: rgb(136, 138, 133);\n"
"}"));
        HeaderPlaneWidget_2 = new QWidget(RunnerTabWidget);
        HeaderPlaneWidget_2->setObjectName(QString::fromUtf8("HeaderPlaneWidget_2"));
        HeaderPlaneWidget_2->setGeometry(QRect(0, 0, 1581, 71));
        HeaderPlaneWidget_2->setStyleSheet(QString::fromUtf8("background: rgb(0, 182, 128)"));
        CompilationParametersLabel_2 = new QLabel(HeaderPlaneWidget_2);
        CompilationParametersLabel_2->setObjectName(QString::fromUtf8("CompilationParametersLabel_2"));
        CompilationParametersLabel_2->setGeometry(QRect(30, 14, 271, 41));
        CompilationParametersLabel_2->setFont(font);
        CompilationParametersLabel_2->setStyleSheet(QString::fromUtf8("color:rgb(46, 52, 54)"));
        RunnerStatusBar = new QTextBrowser(RunnerTabWidget);
        RunnerStatusBar->setObjectName(QString::fromUtf8("RunnerStatusBar"));
        RunnerStatusBar->setGeometry(QRect(10, 880, 1561, 131));
        RunnerProcessLabel = new QLabel(RunnerTabWidget);
        RunnerProcessLabel->setObjectName(QString::fromUtf8("RunnerProcessLabel"));
        RunnerProcessLabel->setGeometry(QRect(10, 860, 161, 17));
        RunnerProcessLabel->setFont(font7);
        RunnerProcessLabel->setStyleSheet(QString::fromUtf8("color: rgb(0, 182, 128)"));
        ProgramDirPathLineEdit = new QLineEdit(RunnerTabWidget);
        ProgramDirPathLineEdit->setObjectName(QString::fromUtf8("ProgramDirPathLineEdit"));
        ProgramDirPathLineEdit->setGeometry(QRect(40, 290, 721, 31));
        ProgramDirPathLabel = new QLabel(RunnerTabWidget);
        ProgramDirPathLabel->setObjectName(QString::fromUtf8("ProgramDirPathLabel"));
        ProgramDirPathLabel->setGeometry(QRect(40, 260, 251, 17));
        ChangeProgramDirPathButton = new QPushButton(RunnerTabWidget);
        ChangeProgramDirPathButton->setObjectName(QString::fromUtf8("ChangeProgramDirPathButton"));
        ChangeProgramDirPathButton->setGeometry(QRect(780, 290, 161, 31));
        WrongFmtProgramDirPathLabel = new QLabel(RunnerTabWidget);
        WrongFmtProgramDirPathLabel->setObjectName(QString::fromUtf8("WrongFmtProgramDirPathLabel"));
        WrongFmtProgramDirPathLabel->setGeometry(QRect(50, 330, 291, 17));
        WrongFmtProgramDirPathLabel->setFont(font3);
        WrongFmtProgramDirPathLabel->setStyleSheet(QString::fromUtf8("color: rgb(204, 0, 0);"));
        IsRemoteTensor = new QCheckBox(RunnerTabWidget);
        IsRemoteTensor->setObjectName(QString::fromUtf8("IsRemoteTensor"));
        IsRemoteTensor->setGeometry(QRect(40, 620, 391, 31));
        line = new QFrame(RunnerTabWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(0, 460, 1011, 21));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        InputTensorPathLineEdit = new QLineEdit(RunnerTabWidget);
        InputTensorPathLineEdit->setObjectName(QString::fromUtf8("InputTensorPathLineEdit"));
        InputTensorPathLineEdit->setGeometry(QRect(400, 620, 371, 31));
        InputTensorPathLabel = new QLabel(RunnerTabWidget);
        InputTensorPathLabel->setObjectName(QString::fromUtf8("InputTensorPathLabel"));
        InputTensorPathLabel->setGeometry(QRect(400, 600, 361, 17));
        RunMode = new QComboBox(RunnerTabWidget);
        RunMode->addItem(QString());
        RunMode->addItem(QString());
        RunMode->setObjectName(QString::fromUtf8("RunMode"));
        RunMode->setGeometry(QRect(1100, 624, 371, 51));
        RunMode->setFont(font4);
        RunModeLabel = new QLabel(RunnerTabWidget);
        RunModeLabel->setObjectName(QString::fromUtf8("RunModeLabel"));
        RunModeLabel->setGeometry(QRect(1100, 590, 261, 21));
        RunModeLabel->setFont(font4);
        RunModeLabel->setStyleSheet(QString::fromUtf8("color: rgb(0, 182, 128)"));
        ShowCmdJsonButton = new QPushButton(RunnerTabWidget);
        ShowCmdJsonButton->setObjectName(QString::fromUtf8("ShowCmdJsonButton"));
        ShowCmdJsonButton->setGeometry(QRect(1310, 270, 161, 51));
        ShowCmdJsonButton->setFont(font5);
        ShowMetadataButton = new QPushButton(RunnerTabWidget);
        ShowMetadataButton->setObjectName(QString::fromUtf8("ShowMetadataButton"));
        ShowMetadataButton->setGeometry(QRect(1310, 330, 161, 51));
        ShowMetadataButton->setFont(font5);
        ShowCmd0Button = new QPushButton(RunnerTabWidget);
        ShowCmd0Button->setObjectName(QString::fromUtf8("ShowCmd0Button"));
        ShowCmd0Button->setGeometry(QRect(1100, 170, 151, 41));
        ShowCmd0Button->setFont(font5);
        ShowCmd1Button = new QPushButton(RunnerTabWidget);
        ShowCmd1Button->setObjectName(QString::fromUtf8("ShowCmd1Button"));
        ShowCmd1Button->setGeometry(QRect(1100, 220, 151, 41));
        ShowCmd1Button->setFont(font5);
        ShowCmd3Button = new QPushButton(RunnerTabWidget);
        ShowCmd3Button->setObjectName(QString::fromUtf8("ShowCmd3Button"));
        ShowCmd3Button->setGeometry(QRect(1100, 330, 151, 51));
        ShowCmd3Button->setFont(font5);
        ShowCmd2Button = new QPushButton(RunnerTabWidget);
        ShowCmd2Button->setObjectName(QString::fromUtf8("ShowCmd2Button"));
        ShowCmd2Button->setGeometry(QRect(1100, 270, 151, 51));
        ShowCmd2Button->setFont(font5);
        ShowCmd4Button = new QPushButton(RunnerTabWidget);
        ShowCmd4Button->setObjectName(QString::fromUtf8("ShowCmd4Button"));
        ShowCmd4Button->setEnabled(true);
        ShowCmd4Button->setGeometry(QRect(1100, 390, 151, 51));
        ShowCmd4Button->setFont(font5);
        ShowCmd5Button = new QPushButton(RunnerTabWidget);
        ShowCmd5Button->setObjectName(QString::fromUtf8("ShowCmd5Button"));
        ShowCmd5Button->setGeometry(QRect(1100, 450, 151, 51));
        ShowCmd5Button->setFont(font5);
        ShowOutputTensorButton = new QPushButton(RunnerTabWidget);
        ShowOutputTensorButton->setObjectName(QString::fromUtf8("ShowOutputTensorButton"));
        ShowOutputTensorButton->setGeometry(QRect(1310, 450, 161, 51));
        ShowOutputTensorButton->setFont(font5);
        ShowCacheDataButton = new QPushButton(RunnerTabWidget);
        ShowCacheDataButton->setObjectName(QString::fromUtf8("ShowCacheDataButton"));
        ShowCacheDataButton->setGeometry(QRect(1310, 220, 161, 41));
        ShowCacheDataButton->setFont(font5);
        ShowTpuDataButton = new QPushButton(RunnerTabWidget);
        ShowTpuDataButton->setObjectName(QString::fromUtf8("ShowTpuDataButton"));
        ShowTpuDataButton->setGeometry(QRect(1310, 170, 161, 41));
        ShowTpuDataButton->setFont(font5);
        PanelLabel = new QLabel(RunnerTabWidget);
        PanelLabel->setObjectName(QString::fromUtf8("PanelLabel"));
        PanelLabel->setGeometry(QRect(1150, 110, 291, 41));
        QFont font9;
        font9.setPointSize(15);
        font9.setBold(true);
        PanelLabel->setFont(font9);
        PanelLabel->setStyleSheet(QString::fromUtf8("color: rgb(0, 182, 128)"));
        RunButton = new QPushButton(RunnerTabWidget);
        RunButton->setObjectName(QString::fromUtf8("RunButton"));
        RunButton->setGeometry(QRect(1100, 760, 371, 61));
        RunButton->setFont(font4);
        isGenerateTensor = new QCheckBox(RunnerTabWidget);
        isGenerateTensor->setObjectName(QString::fromUtf8("isGenerateTensor"));
        isGenerateTensor->setGeometry(QRect(40, 700, 311, 31));
        TensorSizeLineEdit = new QLineEdit(RunnerTabWidget);
        TensorSizeLineEdit->setObjectName(QString::fromUtf8("TensorSizeLineEdit"));
        TensorSizeLineEdit->setGeometry(QRect(400, 700, 191, 31));
        GeneratedTensorSizeLabel = new QLabel(RunnerTabWidget);
        GeneratedTensorSizeLabel->setObjectName(QString::fromUtf8("GeneratedTensorSizeLabel"));
        GeneratedTensorSizeLabel->setGeometry(QRect(400, 680, 181, 17));
        WrongFmtGeneratedTensorSizeLabel = new QLabel(RunnerTabWidget);
        WrongFmtGeneratedTensorSizeLabel->setObjectName(QString::fromUtf8("WrongFmtGeneratedTensorSizeLabel"));
        WrongFmtGeneratedTensorSizeLabel->setGeometry(QRect(400, 740, 171, 17));
        WrongFmtGeneratedTensorSizeLabel->setFont(font3);
        WrongFmtGeneratedTensorSizeLabel->setStyleSheet(QString::fromUtf8("color: rgb(204, 0, 0);"));
        ChangeInputTensorPathButton = new QPushButton(RunnerTabWidget);
        ChangeInputTensorPathButton->setObjectName(QString::fromUtf8("ChangeInputTensorPathButton"));
        ChangeInputTensorPathButton->setGeometry(QRect(780, 620, 161, 31));
        line_2 = new QFrame(RunnerTabWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(1003, 71, 20, 810));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        ProgramPrametersLabel = new QLabel(RunnerTabWidget);
        ProgramPrametersLabel->setObjectName(QString::fromUtf8("ProgramPrametersLabel"));
        ProgramPrametersLabel->setGeometry(QRect(20, 100, 251, 31));
        ProgramPrametersLabel->setFont(font9);
        ProgramPrametersLabel->setStyleSheet(QString::fromUtf8("color: rgb(0, 182, 128)"));
        InputParametersLabel = new QLabel(RunnerTabWidget);
        InputParametersLabel->setObjectName(QString::fromUtf8("InputParametersLabel"));
        InputParametersLabel->setGeometry(QRect(30, 500, 311, 31));
        InputParametersLabel->setFont(font9);
        InputParametersLabel->setStyleSheet(QString::fromUtf8("color: rgb(0, 182, 128)"));
        RunnerProgressBar = new QProgressBar(RunnerTabWidget);
        RunnerProgressBar->setObjectName(QString::fromUtf8("RunnerProgressBar"));
        RunnerProgressBar->setGeometry(QRect(1100, 830, 371, 23));
        RunnerProgressBar->setValue(24);
        GeneratedTensorSavePathLabel = new QLabel(RunnerTabWidget);
        GeneratedTensorSavePathLabel->setObjectName(QString::fromUtf8("GeneratedTensorSavePathLabel"));
        GeneratedTensorSavePathLabel->setGeometry(QRect(60, 770, 351, 17));
        GeneratedTensorSavePathLineEdit = new QLineEdit(RunnerTabWidget);
        GeneratedTensorSavePathLineEdit->setObjectName(QString::fromUtf8("GeneratedTensorSavePathLineEdit"));
        GeneratedTensorSavePathLineEdit->setGeometry(QRect(60, 790, 701, 31));
        WrongFmtGeneratedTensorSavePathLabel = new QLabel(RunnerTabWidget);
        WrongFmtGeneratedTensorSavePathLabel->setObjectName(QString::fromUtf8("WrongFmtGeneratedTensorSavePathLabel"));
        WrongFmtGeneratedTensorSavePathLabel->setGeometry(QRect(60, 830, 701, 17));
        WrongFmtGeneratedTensorSavePathLabel->setFont(font3);
        WrongFmtGeneratedTensorSavePathLabel->setStyleSheet(QString::fromUtf8("color: rgb(204, 0, 0);"));
        ChangeGeneratedTensorSavePathButton = new QPushButton(RunnerTabWidget);
        ChangeGeneratedTensorSavePathButton->setObjectName(QString::fromUtf8("ChangeGeneratedTensorSavePathButton"));
        ChangeGeneratedTensorSavePathButton->setGeometry(QRect(780, 790, 161, 31));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "IVA Compiler Runner", nullptr));
        CompilationSettings->setText(QApplication::translate("MainWindow", "\320\232\320\276\320\274\320\277\320\270\320\273\321\217\321\206\320\270\321\217", nullptr));
        RunnerSettings->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\277\321\203\321\201\320\272 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\321\213", nullptr));
        AnalysisSettings->setText(QApplication::translate("MainWindow", "\320\220\320\275\320\260\320\273\320\270\320\267 \321\200\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\320\276\320\262", nullptr));
        MainDocs->setText(QApplication::translate("MainWindow", "\320\236\320\261\321\211\320\265\320\265 \321\200\321\203\320\272\320\276\320\262\320\276\320\264\321\201\321\202\320\262\320\276", nullptr));
        CompilationDocs->setText(QApplication::translate("MainWindow", "\320\232\320\276\320\274\320\277\320\270\320\273\321\217\321\206\320\270\321\217 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274", nullptr));
        RunnerDocs->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\277\321\203\321\201\320\272 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274", nullptr));
        AnalysisDocs->setText(QApplication::translate("MainWindow", "\320\220\320\275\320\260\320\273\320\270\320\267 \321\200\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\320\276\320\262", nullptr));
        CurrentTimeLabel->setText(QApplication::translate("MainWindow", "\320\222\321\200\320\265\320\274\321\217:", nullptr));
        CurrentTime->setText(QApplication::translate("MainWindow", "00 : 00 : 00", nullptr));
        CompilerTabButton->setText(QApplication::translate("MainWindow", "\320\232\320\276\320\274\320\277\320\270\320\273\321\217\321\206\320\270\321\217 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274", nullptr));
        RunnerTabButton->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\277\321\203\321\201\320\272 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274", nullptr));
        AnalysisTabButton->setText(QApplication::translate("MainWindow", "\320\220\320\275\320\260\320\273\320\270\320\267 \321\200\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\320\276\320\262", nullptr));
        SettingsButton->setText(QApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", nullptr));
        CompilerSettingsButton->setText(QApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270 \320\272\320\276\320\274\320\277\320\270\320\273\321\217\321\206\320\270\320\270", nullptr));
        RunnerSettingsButton->setText(QApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270 \320\267\320\260\320\277\321\203\321\201\320\272\320\260 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274", nullptr));
        AnalysisSettingsButton->setText(QApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270 \320\260\320\275\320\260\320\273\320\270\320\267\320\260\321\202\320\276\321\200\320\260", nullptr));
        CompilationParametersLabel->setText(QApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \320\272\320\276\320\274\320\277\320\270\320\273\321\217\321\206\320\270\320\270", nullptr));
        RedactJsonPushButton->setText(QApplication::translate("MainWindow", "\320\240\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        JsonPathLabel->setText(QApplication::translate("MainWindow", "\320\237\321\203\321\202\321\214 \320\272 JSON \320\276\320\277\320\270\321\201\320\260\320\275\320\270\321\216 \321\201\320\265\321\202\320\270:", nullptr));
        ChangeJsonPathPushButton->setText(QApplication::translate("MainWindow", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        WrongFmtJsonPathLabel->setText(QApplication::translate("MainWindow", "\320\235\320\265\320\262\320\265\321\200\320\275\321\213\320\271 \321\204\320\276\321\200\320\274\320\260\321\202", nullptr));
        ChangeWeightsPathPushButton->setText(QApplication::translate("MainWindow", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        WeightsPathLabel->setText(QApplication::translate("MainWindow", "\320\237\321\203\321\202\321\214 \320\272 \321\204\320\260\320\271\320\273\321\203 \321\201 \320\262\320\265\321\201\320\260\320\274\320\270 \321\201\320\265\321\202\320\270:", nullptr));
        WrongFmtWeightsPathLabel->setText(QApplication::translate("MainWindow", "\320\235\320\265\320\262\320\265\321\200\320\275\321\213\320\271 \321\204\320\276\321\200\320\274\320\260\321\202", nullptr));
        WrongFmtOutputDirPathLabel->setText(QApplication::translate("MainWindow", "\320\235\320\265\320\262\320\265\321\200\320\275\321\213\320\271 \321\204\320\276\321\200\320\274\320\260\321\202", nullptr));
        OutputDirPathPushButton->setText(QApplication::translate("MainWindow", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        OutputDirPathLabel->setText(QApplication::translate("MainWindow", "\320\224\320\270\321\200\320\265\320\272\321\202\320\276\321\200\320\270\321\217 \320\264\320\273\321\217 \320\262\321\213\321\205\320\276\320\264\320\275\321\213\321\205 \321\204\320\260\320\271\320\273\320\276\320\262:", nullptr));
        WrongFmtCatalogNameLabel->setText(QApplication::translate("MainWindow", "\320\235\320\265\320\262\320\265\321\200\320\275\321\213\320\271 \321\204\320\276\321\200\320\274\320\260\321\202", nullptr));
        CatalogNameLabel->setText(QApplication::translate("MainWindow", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \320\272\320\260\321\202\320\260\320\273\320\276\320\263\320\260 \321\201 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\276\320\271:", nullptr));
        TensorParametersLabel->setText(QApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \321\202\320\265\320\275\320\267\320\276\321\200\320\276\320\262:", nullptr));
        WrongFmtInputPadDownLabel->setText(QApplication::translate("MainWindow", "\320\235\320\265\320\262\320\265\321\200\320\275\321\213\320\271 \321\204\320\276\321\200\320\274\320\260\321\202", nullptr));
        InputTensorLabel->setText(QApplication::translate("MainWindow", "\320\222\321\205\320\276\320\264\320\275\320\276\320\271 \321\202\320\265\320\275\320\267\320\276\321\200", nullptr));
        WrongFmtOutputSizeLabel->setText(QApplication::translate("MainWindow", "\320\235\320\265\320\262\320\265\321\200\320\275\321\213\320\271 \321\204\320\276\321\200\320\274\320\260\321\202", nullptr));
        OutputTensorLabel->setText(QApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264\320\275\320\276\320\271 \321\202\320\265\320\275\320\267\320\276\321\200", nullptr));
        PaddingsDownLabel->setText(QApplication::translate("MainWindow", "\320\235\320\270\320\266\320\275\320\270\320\265 \320\277\320\260\320\264\320\264\320\270\320\275\320\263\320\270(B, X, Y, L):", nullptr));
        TensorSizeLabel->setText(QApplication::translate("MainWindow", "\320\240\320\260\320\267\320\274\320\265\321\200(B, X, Y, L):", nullptr));
        WrongFmtInputPadUpLabel->setText(QApplication::translate("MainWindow", "\320\235\320\265\320\262\320\265\321\200\320\275\321\213\320\271 \321\204\320\276\321\200\320\274\320\260\321\202", nullptr));
        WrongFmtOutputPadDownLabel->setText(QApplication::translate("MainWindow", "\320\235\320\265\320\262\320\265\321\200\320\275\321\213\320\271 \321\204\320\276\321\200\320\274\320\260\321\202", nullptr));
        WrongFmtInputSizeLabel->setText(QApplication::translate("MainWindow", "\320\235\320\265\320\262\320\265\321\200\320\275\321\213\320\271 \321\204\320\276\321\200\320\274\320\260\321\202", nullptr));
        WrongFmtOutputPadUpLabel->setText(QApplication::translate("MainWindow", "\320\235\320\265\320\262\320\265\321\200\320\275\321\213\320\271 \321\204\320\276\321\200\320\274\320\260\321\202", nullptr));
        PaddingsUpLabel->setText(QApplication::translate("MainWindow", "\320\222\320\265\321\200\321\205\320\275\320\270\320\265 \320\277\320\260\320\264\320\264\320\270\320\275\320\263\320\270(B, X, Y, L):", nullptr));
        OptimizationOptionsLabel->setText(QApplication::translate("MainWindow", "\320\236\320\277\321\206\320\270\320\270 \320\276\320\277\321\202\320\270\320\274\320\270\320\267\320\260\321\206\320\270\320\271:", nullptr));
        CompilationOptionsLabel->setText(QApplication::translate("MainWindow", "\320\236\320\277\321\206\320\270\320\270 \320\272\320\276\320\274\320\277\320\270\320\273\321\217\321\206\320\270\320\270:", nullptr));
        AddCompilationLogCheckBox->setText(QApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\273\320\276\320\263\320\270 \320\272\320\276\320\274\320\277\320\270\320\273\321\217\321\206\320\270\320\270 \320\272 \320\262\321\213\321\205\320\276\320\264\320\275\320\276\320\271 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\265", nullptr));
        AddDebugModeCheckBox->setText(QApplication::translate("MainWindow", "\320\222\320\272\320\273\321\216\321\207\320\270\321\202\321\214 debug \321\200\320\265\320\266\320\270\320\274 \320\264\320\273\321\217 tpu_data + cache_data", nullptr));
        AddInputOptimizationCheckBox->setText(QApplication::translate("MainWindow", "\320\222\320\272\320\273\321\216\321\207\320\270\321\202\321\214 \320\276\320\277\321\202\320\270\320\274\320\270\320\267\320\260\321\206\320\270\321\216 \320\262\321\205\320\276\320\264\320\275\320\276\320\271 \320\272\320\260\321\200\321\202\321\213 \320\277\321\200\320\270\320\267\320\275\320\260\320\272\320\276\320\262", nullptr));
        AddFilterPreloadCheckBox->setText(QApplication::translate("MainWindow", "\320\222\320\272\320\273\321\216\321\207\320\270\321\202\321\214 \320\277\321\200\320\265\320\264\320\267\320\260\320\263\321\200\321\203\320\267\320\272\321\203 \321\204\320\270\320\273\321\214\321\202\321\200\320\276\320\262", nullptr));
        AddBiasPreloadCheckBox->setText(QApplication::translate("MainWindow", "\320\222\320\272\320\273\321\216\321\207\320\270\321\202\321\214 \320\276\320\277\321\202\320\270\320\274\320\270\320\267\320\260\321\206\320\270\321\216 \320\277\321\200\320\265\320\264\320\267\320\260\320\263\321\200\321\203\320\267\320\272\320\270 BIAS + SCALE", nullptr));
        AddReorderOptimizationCheckBox->setText(QApplication::translate("MainWindow", "\320\222\320\272\320\273\321\216\321\207\320\270\321\202\321\214 \320\276\320\277\321\202\320\270\320\274\320\270\320\267\320\260\321\206\320\270\321\216 \321\201 \320\277\320\265\321\200\320\265\321\201\321\202\320\260\320\275\320\276\320\262\320\272\320\276\320\271 \320\261\320\260\320\275\320\272\320\276\320\262", nullptr));
        ExecutionProcessLabel->setText(QApplication::translate("MainWindow", "\320\237\321\200\320\276\321\206\320\265\321\201\321\201 \320\262\321\213\320\277\320\276\320\273\320\275\320\265\320\275\320\270\321\217", nullptr));
        CompileProgrammCheckBox->setText(QApplication::translate("MainWindow", "\320\241\320\272\320\276\320\274\320\277\320\270\320\273\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\321\203", nullptr));
        PickleConvertationCheckBox->setText(QApplication::translate("MainWindow", "\320\232\320\276\320\275\320\262\320\265\321\200\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\262\320\265\321\201\320\260 Pickle -> bin(HPM Scheduler)", nullptr));
        AddressCheckCheckBox->setText(QApplication::translate("MainWindow", "\320\237\321\200\320\276\320\262\320\265\321\200\320\270\321\202\321\214 \320\260\320\264\321\200\320\265\321\201\320\260 \320\270 \321\200\320\260\320\267\320\274\320\265\321\200\321\213 \320\262\320\265\321\201\320\276\320\262 \320\262 JSON \321\204\320\260\320\271\320\273\320\265", nullptr));
        JsonConvertationCheckBox->setText(QApplication::translate("MainWindow", "\320\232\320\276\320\275\320\262\320\265\321\200\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 JSON Tensorflow - > HPM Scheduler", nullptr));
        CompilationPipelineLabel->setText(QApplication::translate("MainWindow", "\320\237\320\260\320\271\320\277\320\273\320\260\320\271\320\275 \320\272\320\276\320\274\320\277\320\270\320\273\321\217\321\206\320\270\320\270", nullptr));
        MakeMetadataCheckBox->setText(QApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \321\204\320\260\320\271\320\273 \321\201 \320\274\320\265\321\202\320\260\320\264\320\260\320\275\320\275\321\213\320\274\320\270", nullptr));
        MakeArchiveCheckBox->setText(QApplication::translate("MainWindow", "\320\241\320\276\320\261\321\200\320\260\321\202\321\214 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\321\203 \320\262 \320\260\321\200\321\205\320\270\320\262 \320\270 \320\277\320\265\321\200\320\265\320\275\320\265\321\201\321\202\320\270 \320\262 \320\277\320\260\320\277\320\272\321\203", nullptr));
        DeviceComboBoxLabel->setText(QApplication::translate("MainWindow", "\320\243\321\201\321\202\321\200\320\276\320\271\321\201\321\202\320\262\320\276", nullptr));
        DeviceComboBox->setItemText(0, QApplication::translate("MainWindow", "MOBILE", nullptr));
        DeviceComboBox->setItemText(1, QApplication::translate("MainWindow", "KCU", nullptr));
        DeviceComboBox->setItemText(2, QApplication::translate("MainWindow", "SERVER", nullptr));

        RunProcessPushButton->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\277\321\203\321\201\320\272", nullptr));
        CompilationParametersLabel_2->setText(QApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \320\267\320\260\320\277\321\203\321\201\320\272\320\260", nullptr));
        RunnerProcessLabel->setText(QApplication::translate("MainWindow", "\320\237\321\200\320\276\321\206\320\265\321\201\321\201 \320\262\321\213\320\277\320\276\320\273\320\275\320\265\320\275\320\270\321\217", nullptr));
        ProgramDirPathLabel->setText(QApplication::translate("MainWindow", "\320\237\321\203\321\202\321\214 \320\272 \320\264\320\270\321\200\320\265\320\272\321\202\320\276\321\200\320\270\320\270 \321\201 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\276\320\271:", nullptr));
        ChangeProgramDirPathButton->setText(QApplication::translate("MainWindow", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        WrongFmtProgramDirPathLabel->setText(QApplication::translate("MainWindow", "\320\243\320\272\320\260\320\267\320\260\320\275\320\275\320\276\320\271 \320\264\320\270\321\200\320\265\320\272\321\202\320\276\321\200\320\270\320\270 \320\275\320\265 \321\201\321\203\321\211\320\265\321\201\321\202\320\262\321\203\320\265\321\202", nullptr));
        IsRemoteTensor->setText(QApplication::translate("MainWindow", "\320\222\321\205\320\276\320\264\320\275\320\276\320\271 \321\202\320\265\320\275\320\267\320\276\321\200 \320\273\320\265\320\266\320\270\321\202 \320\275\320\260 \321\203\320\264\320\260\320\273\320\265\320\275\320\275\320\276\320\274 \321\205\320\276\321\201\321\202\320\265", nullptr));
        InputTensorPathLabel->setText(QApplication::translate("MainWindow", "\320\237\321\203\321\202\321\214 \320\272 \320\262\321\205\320\276\320\264\320\275\320\276\320\274\321\203 \321\202\320\265\320\275\320\267\320\276\321\200\321\203 \320\275\320\260 \321\203\320\264\320\260\320\273\320\265\320\275\320\275\320\276\320\274 \321\205\320\276\321\201\321\202\320\265:", nullptr));
        RunMode->setItemText(0, QApplication::translate("MainWindow", "LOCAL", nullptr));
        RunMode->setItemText(1, QApplication::translate("MainWindow", "REMOTE", nullptr));

        RunModeLabel->setText(QApplication::translate("MainWindow", "\320\240\320\265\320\266\320\270\320\274 \320\267\320\260\320\277\321\203\321\201\320\272\320\260 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274:", nullptr));
        ShowCmdJsonButton->setText(QApplication::translate("MainWindow", "cmd.json", nullptr));
        ShowMetadataButton->setText(QApplication::translate("MainWindow", "metadata.json", nullptr));
        ShowCmd0Button->setText(QApplication::translate("MainWindow", "cmd0.bin", nullptr));
        ShowCmd1Button->setText(QApplication::translate("MainWindow", "cmd1.bin", nullptr));
        ShowCmd3Button->setText(QApplication::translate("MainWindow", "cmd3.bin", nullptr));
        ShowCmd2Button->setText(QApplication::translate("MainWindow", "cmd2.bin", nullptr));
        ShowCmd4Button->setText(QApplication::translate("MainWindow", "cmd4.bin", nullptr));
        ShowCmd5Button->setText(QApplication::translate("MainWindow", "cmd5.bin", nullptr));
        ShowOutputTensorButton->setText(QApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264\320\275\320\276\320\271 \321\202\320\265\320\275\320\267\320\276\321\200", nullptr));
        ShowCacheDataButton->setText(QApplication::translate("MainWindow", "Cache Data", nullptr));
        ShowTpuDataButton->setText(QApplication::translate("MainWindow", "Tpu Data", nullptr));
        PanelLabel->setText(QApplication::translate("MainWindow", "\320\237\320\260\320\275\320\265\320\273\321\214 \320\261\321\213\321\201\321\202\321\200\320\276\320\263\320\276 \320\264\320\276\321\201\321\202\321\203\320\277\320\260", nullptr));
        RunButton->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\277\321\203\321\201\321\202\320\270\321\202\321\214", nullptr));
        isGenerateTensor->setText(QApplication::translate("MainWindow", "\320\241\320\263\320\265\320\275\320\265\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\275\320\276\320\262\321\213\320\271 \320\262\321\205\320\276\320\264\320\275\320\276\320\271 \321\202\320\265\320\275\320\267\320\276\321\200", nullptr));
        GeneratedTensorSizeLabel->setText(QApplication::translate("MainWindow", "\320\240\320\260\320\267\320\274\320\265\321\200 \321\202\320\265\320\275\320\267\320\276\321\200\320\260(B,X,Y,L):", nullptr));
        WrongFmtGeneratedTensorSizeLabel->setText(QApplication::translate("MainWindow", "\320\235\320\265\320\262\320\265\321\200\320\275\321\213\320\271 \321\204\320\276\321\200\320\274\320\260\321\202", nullptr));
        ChangeInputTensorPathButton->setText(QApplication::translate("MainWindow", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        ProgramPrametersLabel->setText(QApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\321\213", nullptr));
        InputParametersLabel->setText(QApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \320\262\321\205\320\276\320\264\320\275\320\276\320\263\320\276 \321\202\320\265\320\275\320\267\320\276\321\200\320\260", nullptr));
        GeneratedTensorSavePathLabel->setText(QApplication::translate("MainWindow", "\320\237\321\203\321\202\321\214 \320\264\320\273\321\217 \321\201\320\276\321\205\321\200\320\260\320\275\320\265\320\275\320\270\321\217 \320\275\320\276\320\262\320\276\320\263\320\276 \321\202\320\265\320\275\320\267\320\276\321\200\320\260:", nullptr));
        WrongFmtGeneratedTensorSavePathLabel->setText(QApplication::translate("MainWindow", "\320\235\320\265\320\262\320\265\321\200\320\275\321\213\320\271 \321\204\320\276\321\200\320\274\320\260\321\202", nullptr));
        ChangeGeneratedTensorSavePathButton->setText(QApplication::translate("MainWindow", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
