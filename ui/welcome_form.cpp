#include "welcome_form.h"
#include "ui/welcome_form_ui.h"
#include "ui/welcome_form.h"
#include "include/settings_config.h"
#include "include/wrong_fmt_captures.h"

#include <QFileDialog>
#include <QRegularExpression>
#include <QStyle>
#include <boost/filesystem/operations.hpp>
#include <string>
#include <unistd.h>

// Конструктор принимает на вход родительский виджет + объект
// Содержащий настройки приложения.
WelcomeWizard::WelcomeWizard(QWidget *parent, SettingsBuffer* parent_settings)
    : QWizard(parent)
    , ui(new Ui::WelcomeWizard)
    , settings(parent_settings)
{
    // Инициализация UI
    ui->setupUi(this);

    // Инициализация состояний UI элементов
    initUiStates();
}

// Деструктор высвобождает ресурсы и сохраняет введенные данные
WelcomeWizard::~WelcomeWizard()
{
    // Сохранение данных
    saveSettings();

    settings->sync();

    // Так как settings - настройки родителя, то удалять их не нужно.
    // Деструктор объекта не должен быть удален. Удаляем только указатель.
    settings = nullptr;

    delete ui;
    delete settings;
}

// Инициализация состояний элементов интерфейса
void WelcomeWizard::initUiStates()
{
    // Инициализация индикаторов неверного формата ввода
    initWrongFormatIndicators();

    // Скрытие элементов, которые не должны быть на виду в обычном состоянии окон
    ui->NumCoresDecrement->setVisible(false);
    ui->NumCoresIncrement->setVisible(false);
    ui->NumberCoresLabel->setVisible(false);
    ui->NumberCoresLineEdit->setVisible(false);

}

// Выставляет индикаторы неверного формата в невидимый режим
void WelcomeWizard::initWrongFormatIndicators()
{
    ui->WrongArchiveNameLabel->setVisible(false);
    ui->WrongFmtNumberCoresLabel->setVisible(false);
    ui->WrongFmtNumberRunsLabel->setVisible(false);
    ui->WrongFmtCompilerDirectoryLabel->setVisible(false);
    ui->WrongFmtInputScaleLabel->setVisible(false);
    ui->WrongFmtOutputScaleLabel->setVisible(false);
}

// Сохранение настроек
void WelcomeWizard::saveSettings() {

    // Настройки сохраняются в глобальную группу
    settings->beginGroup(GLOBAL_SETTINGS_GROUP);

    settings->setValue("CompilerDirectory", ui->InputCompilerPathLineEdit->text());
    settings->setValue("CMakeNumberRuns", ui->NumberRunsLineEdit->text());
    settings->setValue("CMakeNumberCores", ui->NumberCoresLineEdit->text());
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
}

// :::: QT UI SLOTS :::::

void WelcomeWizard::on_ChangeCompilerPathPushButton_clicked()
{
    // Получаем директорию и вставляем ее в LineEdit
    QString directory = QFileDialog::getExistingDirectory(this, "Выберите директорию с компилятором", "/home/");

    if (!directory.isEmpty())
        ui->InputCompilerPathLineEdit->setText(directory);

    on_InputCompilerPathLineEdit_editingFinished();
}

void WelcomeWizard::on_NumberRunsLineEdit_editingFinished()
{
    // Проверка соответствия формату целого положительного числа
    QRegularExpression rx("^(\\d+)$");

    QString current_text = ui->NumberRunsLineEdit->text();

    // Если регулярное выражение не подходит, то выставляем индикатор неверного формата
    bool is_matched = rx.match(current_text).hasMatch();

    if (!is_matched) {
        ui->WrongFmtNumberRunsLabel->setVisible(true);
    } else {
        ui->WrongFmtNumberRunsLabel->setVisible(false);
    }

}

void WelcomeWizard::on_InputCompilerPathLineEdit_editingFinished()
{
    // Проверка существования директории при ручном вводе
    std::string path(ui->InputCompilerPathLineEdit->text().toStdString());

    if(!boost::filesystem::is_directory(path)) {
        ui->WrongFmtCompilerDirectoryLabel->setVisible(true);
    } else {
        ui->WrongFmtCompilerDirectoryLabel->setVisible(false);
    }
}

void WelcomeWizard::on_NumRunsIncrement_clicked()
{
    // Инкремент прибавляет к текущему значению 1
    int current_value = ui->NumberRunsLineEdit->text().toInt();

    current_value++;

    ui->NumberRunsLineEdit->setText(QString::fromStdString(std::to_string(current_value)));

    on_NumberRunsLineEdit_editingFinished();
}

void WelcomeWizard::on_NumRunsDecrement_clicked()
{
    // Декремент убавляет текущее значение на 1, если это возможно
    int current_value = ui->NumberRunsLineEdit->text().toInt();

    if (current_value > 0) current_value--;

    ui->NumberRunsLineEdit->setText(QString::fromStdString(std::to_string(current_value)));

    on_NumberRunsLineEdit_editingFinished();
}

void WelcomeWizard::on_ArchiveNameLineEdit_editingFinished()
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
        ui->WrongArchiveNameLabel->setText(WRONG_FMT_TEXT::bad_dir_format_short);
    } else if (is_not_zip){
        ui->WrongArchiveNameLabel->setText(WRONG_FMT_TEXT::not_zip_fmt);
    }

    // Если ошибка есть, показываем индикатор
    if (is_bad_format || is_not_zip) {
        ui->WrongArchiveNameLabel->setVisible(true);
    } else {
        ui->WrongArchiveNameLabel->setVisible(false);
    }

}

void WelcomeWizard::on_MakeParallelCheckBox_stateChanged(int arg1)
{
    // По умолчанию элементы не видны, когда CheckBox
    // не отмечен. Если его отметить, то состояние
    // visible переключается в True

    bool visible_state = false;

    if (ui->MakeParallelCheckBox->isChecked()) {
        visible_state = true;
    }

    ui->NumCoresDecrement->setVisible(visible_state);
    ui->NumCoresIncrement->setVisible(visible_state);
    ui->NumberCoresLabel->setVisible(visible_state);
    ui->NumberCoresLineEdit->setVisible(visible_state);
}

void WelcomeWizard::on_NumberCoresLineEdit_editingFinished()
{
    // Проверка соответствия формату целого положительного числа
    QRegularExpression rx("^(\\d+)$");

    QString current_text = ui->NumberCoresLineEdit->text();

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
        ui->WrongFmtNumberCoresLabel->setText("Введите число");
    } else if (is_overflow) {
        QString wrong_fmt_text = "Максимум: ";
        wrong_fmt_text += QString::fromStdString(std::to_string(sysconf(_SC_NPROCESSORS_ONLN)));
        ui->WrongFmtNumberCoresLabel->setText(wrong_fmt_text);
    }

    // Выставляем видимость индикатора
    if (!is_matched || is_overflow) {
        ui->WrongFmtNumberCoresLabel->setVisible(true);
    } else {
        ui->WrongFmtNumberCoresLabel->setVisible(false);
    }

}

void WelcomeWizard::on_NumCoresIncrement_clicked()
{
    // Инкремент с проверкой на переполнение по количеству потоков
    int current_value = ui->NumberCoresLineEdit->text().toInt();
    int max_cores = sysconf(_SC_NPROCESSORS_ONLN);

    if (current_value < max_cores) current_value++;

    ui->NumberCoresLineEdit->setText(QString::fromStdString(std::to_string(current_value)));
    on_NumberCoresLineEdit_editingFinished();
}

void WelcomeWizard::on_NumCoresDecrement_clicked()
{

    // Декремент
    int current_value = ui->NumberCoresLineEdit->text().toInt();

    if (current_value > 0) current_value--;

    ui->NumberCoresLineEdit->setText(QString::fromStdString(std::to_string(current_value)));
    on_NumberCoresLineEdit_editingFinished();
}

void WelcomeWizard::on_InputScaleLineEdit_editingFinished()
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

void WelcomeWizard::on_OutputScaleLineEdit_editingFinished()
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
