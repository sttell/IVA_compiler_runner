#include "compiler_settings_dialog.h"
#include "compiler_settings_dialog_ui.h"
#include "include/settings_config.h"
#include "include/wrong_fmt_captures.h"
#include "ui/warning_settings_dialog.h"

#include <filesystem>
#include <iostream>
#include <QFileDialog>
#include <QRegularExpression>
#include <unistd.h>



// Конструктор принимает на вход родительский виджет + объект
// Содержащий настройки приложения.
CompilerSettingsDialog::CompilerSettingsDialog(QWidget *parent, SettingsBuffer* parent_settings)
    : QDialog(parent)
    , ui(new Ui::CompilerSettingsDialog)
    , settings(parent_settings)
{

    // Инициализация UI
    ui->setupUi(this);

    // Инициализация состояний UI интерфейса
    initUiStates();
}

// Инициализация состояний UI
void CompilerSettingsDialog::initUiStates()
{
    // Инициализация состояний из настроек(LineEdits, CheckBoxes, etc.)
    initStatesFromSettings();

    // Инициализация индикаторов неправильного формата
    initWrongFormatIndicators();

    // Инициализация состояния блока с выбором количества ядер
    // параллельной сборки
    // Если чек бокс не отмечен, то скрываем нужные виджеты
    if (!ui->MakeParallelCheckBox->isChecked()) {
        ui->CMakeNumCoresDecrementButton->setVisible(false);
        ui->CMakeNumCoresIncrementButton->setVisible(false);
        ui->CMakeNumCoresLabel->setVisible(false);
        ui->CMakeNumCoresLineEdit->setVisible(false);
        ui->WrongFmtNumCoresLabel->setVisible(false);
    }
}

// Инициализация состояний неверных форматов ввода
void CompilerSettingsDialog::initWrongFormatIndicators()
{
    // Вызываем все слоты, которые проверяют форматы ввода
    on_CompilerDirLineEdit_editingFinished();
    on_ArchiveNameLineEdit_editingFinished();
    on_InputScaleLineEdit_editingFinished();
    on_OutputScaleLineEdit_editingFinished();
    on_KcuApiVersionEditLine_editingFinished();
    on_MobileApiVersionEditLine_editingFinished();
    on_ServerApiVersionEditLine_editingFinished();
    if (ui->MakeParallelCheckBox->isChecked())
        on_CMakeNumCoresLineEdit_editingFinished();
    on_CMakeNumRunsLineEdit_editingFinished();
}

// Инициализация состояний из настроек
void CompilerSettingsDialog::initStatesFromSettings()
{

    settings->beginGroup(GLOBAL_SETTINGS_GROUP);
    // Устанавливаем все поля в соответствии с настройками
    ui->CompilerDirLineEdit->setText(settings->value("CompilerDirectory", "/home/").toString());
    ui->CMakeNumRunsLineEdit->setText(settings->value("CMakeNumberRuns", "2").toString());
    ui->CMakeNumCoresLineEdit->setText(settings->value("CMakeNumberCores", "4").toString());
    ui->ArchiveNameLineEdit->setText(settings->value("ArchiveName", "program.zip").toString());
    ui->InputScaleLineEdit->setText(settings->value("InputScale", "0.0").toString());
    ui->OutputScaleLineEdit->setText(settings->value("OutputScale", "0.0").toString());
    ui->KcuApiVersionEditLine->setText(settings->value("KcuAPIVersion", "2.0.0").toString());
    ui->KcuIpVersionEditLine->setText(settings->value("KcuIPVersion", "02.05.02").toString());
    ui->MobileApiVersionEditLine->setText(settings->value("MobileAPIVersion", "2.0.0").toString());
    ui->MobileIpVersionEditLine->setText(settings->value("MobileIPVersion", "02.05.04").toString());
    ui->ServerApiVersionEditLine->setText(settings->value("ServerAPIVersion", "2.0.0").toString());
    ui->ServerIpVersionEditLine->setText(settings->value("ServerIPVersion", "02.05.02").toString());
    ui->MakeParallelCheckBox->setChecked(settings->value("CMakeParallelMode", false).toBool());
    on_MakeParallelCheckBox_stateChanged(1);
    settings->endGroup();
}

// Сохранение настроек
void CompilerSettingsDialog::saveSettings()
{
    settings->beginGroup(GLOBAL_SETTINGS_GROUP);
    settings->setValue("CompilerDirectory", ui->CompilerDirLineEdit->text());
    settings->setValue("CMakeNumberRuns", ui->CMakeNumRunsLineEdit->text());
    settings->setValue("CMakeNumberCores", ui->CMakeNumCoresLineEdit->text());
    settings->setValue("CMakeParallelMode", ui->MakeParallelCheckBox->isChecked());
    settings->setValue("ArchiveName", ui->ArchiveNameLineEdit->text());
    settings->setValue("InputScale", ui->InputScaleLineEdit->text());
    settings->setValue("OutputScale", ui->OutputScaleLineEdit->text());
    settings->setValue("KcuAPIVersion", ui->KcuApiVersionEditLine->text());
    settings->setValue("KcuIPVersion", ui->KcuIpVersionEditLine->text());
    settings->setValue("MobileAPIVersion", ui->MobileApiVersionEditLine->text());
    settings->setValue("MobileIPVersion", ui->MobileIpVersionEditLine->text());
    settings->setValue("ServerAPIVersion", ui->ServerApiVersionEditLine->text());
    settings->setValue("ServerIPVersion", ui->ServerIpVersionEditLine->text());
    settings->endGroup();

    settings->sync();
}

// Проверка всех форматов ввода
void CompilerSettingsDialog::checkFormats()
{
    // Вызываем все методы, которые проверяют формат ввода
    on_ArchiveNameLineEdit_editingFinished();
    on_CompilerDirLineEdit_editingFinished();
    on_CMakeNumRunsLineEdit_editingFinished();
    on_InputScaleLineEdit_editingFinished();
    on_OutputScaleLineEdit_editingFinished();
    if (ui->MakeParallelCheckBox->isChecked())
        on_CMakeNumCoresLineEdit_editingFinished();
    on_KcuApiVersionEditLine_editingFinished();
    on_MobileApiVersionEditLine_editingFinished();
    on_ServerApiVersionEditLine_editingFinished();
}

// Деструктор высвобождает ресурсы и сохраняет введенные данные
CompilerSettingsDialog::~CompilerSettingsDialog()
{
    settings = nullptr;
    delete ui;
    delete settings;
}

// ::::::::: UI SLOTS :::::::::

void CompilerSettingsDialog::on_ApplyButton_clicked()
{
    // Проверка индикаторов неверного формата (Перевыставление)
    checkFormats();

    int warning_return_code = 1;
    // Если форматы впорядке
    bool is_normal_formats = true;

    is_normal_formats = is_normal_formats && !(ui->WrongFmtArchiveNameLabel->isVisible());
    is_normal_formats = is_normal_formats && !(ui->WrongFmtCompilerDirLabel->isVisible());
    is_normal_formats = is_normal_formats && !(ui->WrongFmtInputScaleLabel->isVisible());
    is_normal_formats = is_normal_formats && !(ui->WrongFmtOutputScaleLabel->isVisible());
    is_normal_formats = is_normal_formats && !(ui->WrongFmtNumRunsLabel->isVisible());
    if (ui->MakeParallelCheckBox->isChecked())
        is_normal_formats = is_normal_formats && !(ui->WrongFmtNumCoresLabel->isVisible());

    // Один из девайсов должен иметь правильный формат IP && API
    bool one_of_device = false;

    one_of_device = one_of_device || !(ui->WrongFmtKcuVersionLabel->isVisible());
    one_of_device = one_of_device || !(ui->WrongFmtMobileVersionLabel->isVisible());
    one_of_device = one_of_device || !(ui->WrongFmtServerVersionLabel->isVisible());

    is_normal_formats = is_normal_formats && one_of_device;

    // Если хотя бы один формат не верный, то вызывается диалговое окно
    if(!is_normal_formats) {
        WarningSettingsDialog warning(this);
        warning.show();
        warning_return_code = warning.exec();
    }

    // Если пользователь подтвердил или диалог не был вызван, то сохраняем настройки и закрываем
    if (warning_return_code == 1) {
        saveSettings();
        this->done(1);
    }
}

void CompilerSettingsDialog::on_CancelButton_clicked()
{
    // Закрываем без сохранений с кодом 0
    this->reject();
}

void CompilerSettingsDialog::on_ChangeCompilerDirPushButton_clicked()
{
    // Текущая директория
    QString current_dir = ui->CompilerDirLineEdit->text();
    // Путь по которому откроется проводник
    QString open_path;

    // Если текущая введенная директория существует, то открываем там
    // иначе - в домашней папке
    if (std::filesystem::is_directory(current_dir.toStdString()))
        open_path = current_dir;
    else
        open_path = "/home/";

    // Поиск каталога
    QString finded_dir = QFileDialog::getExistingDirectory(
                this,
                "Выберите директорию с компилятором IVA",
                open_path
                );

    // Если каталог не пустая строка, тогда выставляем текст
    if (!finded_dir.isEmpty())
        ui->CompilerDirLineEdit->setText(finded_dir);

    // На всякий случай проверяем формат введенного значения
    on_CompilerDirLineEdit_editingFinished();
}

void CompilerSettingsDialog::on_CompilerDirLineEdit_editingFinished()
{
    // Проверка существования директории при ручном вводе
    std::string path(ui->CompilerDirLineEdit->text().toStdString());

    // Если путь существует, то норм, если нет - высветим индикатор
    if(!std::filesystem::is_directory(path)) {
        ui->WrongFmtCompilerDirLabel->setVisible(true);
    } else {
        ui->WrongFmtCompilerDirLabel->setVisible(false);
    }
}

void CompilerSettingsDialog::on_ArchiveNameLineEdit_editingFinished()
{
    // Проверка соответствия формата имени допустимым в ОС нормам

    // Плохие символы
    QString bad_symbols("*|:\"<>?/\\");
    QString current_text(ui->ArchiveNameLineEdit->text());

    // Если формат не верный
    bool is_bad_format {false};
    // Если это не zip архив
    bool is_not_zip = !(current_text.endsWith(".zip"));

    // Прверка введенного текста на наличие плохих символов
    for (const auto& symbol : current_text) {
        if (bad_symbols.contains(symbol)) {
            is_bad_format = true;
            break;
        }
    }

    // Ставим сообщение в зависимости от ошибки
    if (is_bad_format) {
        ui->WrongFmtArchiveNameLabel->setText(WRONG_FMT_TEXT::bad_dir_format_short);
    } else if (is_not_zip){
        ui->WrongFmtArchiveNameLabel->setText(WRONG_FMT_TEXT::not_zip_fmt);
    }

    // Если ошибка есть, показываем индикатор
    if (is_bad_format || is_not_zip) {
        ui->WrongFmtArchiveNameLabel->setVisible(true);
    } else {
        ui->WrongFmtArchiveNameLabel->setVisible(false);
    }

}

void CompilerSettingsDialog::on_CMakeNumRunsDecrementButton_clicked()
{
    // Декремент убавляет текущее значение на 1, если это возможно
    int current_value = ui->CMakeNumRunsLineEdit->text().toInt();

    if (current_value > 0) current_value--;

    ui->CMakeNumRunsLineEdit->setText(QString::fromStdString(std::to_string(current_value)));

    on_CMakeNumRunsLineEdit_editingFinished();
}

void CompilerSettingsDialog::on_CMakeNumRunsIncrementButton_clicked()
{
    // Инкремент прибавляет к текущему значению 1
    int current_value = ui->CMakeNumRunsLineEdit->text().toInt();

    current_value++;

    ui->CMakeNumRunsLineEdit->setText(QString::fromStdString(std::to_string(current_value)));

    on_CMakeNumRunsLineEdit_editingFinished();
}

void CompilerSettingsDialog::on_CMakeNumRunsLineEdit_editingFinished()
{
    // Проверка соответствия формату целого положительного числа
    QRegularExpression rx("^(\\d+)$");

    QString current_text = ui->CMakeNumRunsLineEdit->text();

    // Если регулярное выражение не подходит, то выставляем индикатор неверного формата
    bool is_matched = rx.match(current_text).hasMatch();

    if (!is_matched) {
        ui->WrongFmtNumRunsLabel->setVisible(true);
    } else {
        ui->WrongFmtNumRunsLabel->setVisible(false);
    }

}

void CompilerSettingsDialog::on_MakeParallelCheckBox_stateChanged(int index)
{
    // По умолчанию элементы не видны, когда CheckBox
    // не отмечен. Если его отметить, то состояние
    // visible переключается в True

    bool visible_state = false;

    if (ui->MakeParallelCheckBox->isChecked()) {
        visible_state = true;
    }

    ui->CMakeNumCoresDecrementButton->setVisible(visible_state);
    ui->CMakeNumCoresIncrementButton->setVisible(visible_state);
    ui->CMakeNumCoresLabel->setVisible(visible_state);
    ui->CMakeNumCoresLineEdit->setVisible(visible_state);

    if (visible_state == false)
        ui->WrongFmtNumCoresLabel->setVisible(visible_state);
    else
        on_CMakeNumCoresLineEdit_editingFinished();
}

void CompilerSettingsDialog::on_CMakeNumCoresLineEdit_editingFinished()
{
    // Проверка соответствия формату целого положительного числа
    QRegularExpression rx("^(\\d+)$");

    QString current_text = ui->CMakeNumCoresLineEdit->text();

    // Если регулярное выражение не подходит, то выставляем индикатор неверного формата
    bool is_matched = rx.match(current_text).hasMatch();
    bool is_overflow = false;

    // Если формат верный, то проверяется переполнение.
    // Количество введенных ядер не должно быть больше
    // количества физически доступных потоков
    // иначе это попросту не эффективно
    if (is_matched) {
        int max_cores = sysconf(_SC_NPROCESSORS_ONLN);
        int current_value = current_text.toInt();
        if (current_value > max_cores)
            is_overflow = true;
    }

    // Выставляем текст индикатора
    if (!is_matched) {
        ui->WrongFmtNumCoresLabel->setText("Введите число");
    } else if (is_overflow) {
        QString wrong_fmt_text = "Максимум: ";
        wrong_fmt_text += QString::fromStdString(std::to_string(sysconf(_SC_NPROCESSORS_ONLN)));
        ui->WrongFmtNumCoresLabel->setText(wrong_fmt_text);
    }

    // Выставляем видимость индикатора
    if (!is_matched || is_overflow) {
        ui->WrongFmtNumCoresLabel->setVisible(true);
    } else {
        ui->WrongFmtNumCoresLabel->setVisible(false);
    }
}

void CompilerSettingsDialog::on_CMakeNumCoresDecrementButton_clicked()
{
    // Декремент
    int current_value = ui->CMakeNumCoresLineEdit->text().toInt();

    if (current_value > 0) current_value--;

    ui->CMakeNumCoresLineEdit->setText(QString::fromStdString(std::to_string(current_value)));
    on_CMakeNumCoresLineEdit_editingFinished();
}

void CompilerSettingsDialog::on_CMakeNumCoresIncrementButton_clicked()
{
    // Инкремент с проверкой на переполнение по количеству потоков
    int current_value = ui->CMakeNumCoresLineEdit->text().toInt();
    int max_cores = sysconf(_SC_NPROCESSORS_ONLN);

    if (current_value < max_cores) current_value++;

    ui->CMakeNumCoresLineEdit->setText(QString::fromStdString(std::to_string(current_value)));
    on_CMakeNumCoresLineEdit_editingFinished();
}

void CompilerSettingsDialog::on_InputScaleLineEdit_editingFinished()
{
    // Проверка на соответствие float формату
    QRegularExpression rx("^(\\d+).(\\d+)$");
    QString current_text(ui->InputScaleLineEdit->text());
    bool is_matched = rx.match(current_text).hasMatch();

    if (!is_matched)
        ui->WrongFmtInputScaleLabel->setVisible(true);
    else
        ui->WrongFmtInputScaleLabel->setVisible(false);
}

void CompilerSettingsDialog::on_OutputScaleLineEdit_editingFinished()
{
    // Проверка на соответствие float формату
    QRegularExpression rx("^(\\d+).(\\d+)$");
    QString current_text(ui->OutputScaleLineEdit->text());
    bool is_matched = rx.match(current_text).hasMatch();

    if (!is_matched)
        ui->WrongFmtOutputScaleLabel->setVisible(true);
    else
        ui->WrongFmtOutputScaleLabel->setVisible(false);

}

void CompilerSettingsDialog::on_KcuApiVersionEditLine_editingFinished()
{
    // Проверка форматов ввода для API и IP.
    // Если у данного устройства API и IP введены в правильном формате, то все норм
    // иначе - высветим индикатор
    QRegularExpression rx("^(\\d+).(\\d+).(\\d+)$");
    QString current_api(ui->KcuApiVersionEditLine->text());
    QString current_ip(ui->KcuIpVersionEditLine->text());

    bool is_all_matched = rx.match(current_api).hasMatch() && rx.match(current_ip).hasMatch();

    if (!is_all_matched)
        ui->WrongFmtKcuVersionLabel->setVisible(true);
    else
        ui->WrongFmtKcuVersionLabel->setVisible(false);
}

void CompilerSettingsDialog::on_KcuIpVersionEditLine_editingFinished()
{
    // Проверка форматов ввода для API и IP.
    // Если у данного устройства API и IP введены в правильном формате, то все норм
    // иначе - высветим индикатор
    QRegularExpression rx("^(\\d+).(\\d+).(\\d+)$");
    QString current_api(ui->KcuApiVersionEditLine->text());
    QString current_ip(ui->KcuIpVersionEditLine->text());

    bool is_all_matched = rx.match(current_api).hasMatch() && rx.match(current_ip).hasMatch();

    if (!is_all_matched)
        ui->WrongFmtKcuVersionLabel->setVisible(true);
    else
        ui->WrongFmtKcuVersionLabel->setVisible(false);
}

void CompilerSettingsDialog::on_MobileApiVersionEditLine_editingFinished()
{
    // Проверка форматов ввода для API и IP.
    // Если у данного устройства API и IP введены в правильном формате, то все норм
    // иначе - высветим индикатор
    QRegularExpression rx("^(\\d+).(\\d+).(\\d+)$");
    QString current_api(ui->MobileApiVersionEditLine->text());
    QString current_ip(ui->MobileIpVersionEditLine->text());

    bool is_all_matched = rx.match(current_api).hasMatch() && rx.match(current_ip).hasMatch();

    if (!is_all_matched)
        ui->WrongFmtMobileVersionLabel->setVisible(true);
    else
        ui->WrongFmtMobileVersionLabel->setVisible(false);
}

void CompilerSettingsDialog::on_MobileIpVersionEditLine_editingFinished()
{
    // Проверка форматов ввода для API и IP.
    // Если у данного устройства API и IP введены в правильном формате, то все норм
    // иначе - высветим индикатор
    QRegularExpression rx("^(\\d+).(\\d+).(\\d+)$");
    QString current_api(ui->MobileApiVersionEditLine->text());
    QString current_ip(ui->MobileIpVersionEditLine->text());

    bool is_all_matched = rx.match(current_api).hasMatch() && rx.match(current_ip).hasMatch();

    if (!is_all_matched)
        ui->WrongFmtMobileVersionLabel->setVisible(true);
    else
        ui->WrongFmtMobileVersionLabel->setVisible(false);
}

void CompilerSettingsDialog::on_ServerApiVersionEditLine_editingFinished()
{
    // Проверка форматов ввода для API и IP.
    // Если у данного устройства API и IP введены в правильном формате, то все норм
    // иначе - высветим индикатор
    QRegularExpression rx("^(\\d+).(\\d+).(\\d+)$");
    QString current_api(ui->ServerApiVersionEditLine->text());
    QString current_ip(ui->ServerIpVersionEditLine->text());

    bool is_all_matched = rx.match(current_api).hasMatch() && rx.match(current_ip).hasMatch();

    if (!is_all_matched)
        ui->WrongFmtServerVersionLabel->setVisible(true);
    else
        ui->WrongFmtServerVersionLabel->setVisible(false);
}

void CompilerSettingsDialog::on_ServerIpVersionEditLine_editingFinished()
{
    // Проверка форматов ввода для API и IP.
    // Если у данного устройства API и IP введены в правильном формате, то все норм
    // иначе - высветим индикатор
    QRegularExpression rx("^(\\d+).(\\d+).(\\d+)$");
    QString current_api(ui->ServerApiVersionEditLine->text());
    QString current_ip(ui->ServerIpVersionEditLine->text());

    bool is_all_matched = rx.match(current_api).hasMatch() && rx.match(current_ip).hasMatch();

    if (!is_all_matched)
        ui->WrongFmtServerVersionLabel->setVisible(true);
    else
        ui->WrongFmtServerVersionLabel->setVisible(false);
}

