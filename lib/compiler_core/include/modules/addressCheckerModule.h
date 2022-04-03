#ifndef _INCLDUE_MODULES_ADDRESSCHECKERMODULE_H_
#define _INCLDUE_MODULES_ADDRESSCHECKERMODULE_H_

/**
 * @file addressCheckerModule.h
 * @author Ilya Biro (st.tell@mail.ru)
 * @brief Описание класса модуля проверки соответствия адресов и размеров весов
 * в файле описания сети.
 * @version 1.0
 * @date 2022-04-03
 * 
 * @copyright Copyright (c) 2022
 */

// Внешние зависимости
#include "../module.h"
#include "../settings/globalSettings.h"
#include "../jsonHandler.h"
#include "include/syntax_sugar.h"

// STL зависимости
#include <unordered_map>
#include <string>

// Boost зависимости
#include <boost/property_tree/ptree.hpp>


/*
 * --------------------------------------------------------------------
 *         Идентификаторы типов данных в формате HPM Scheduler
 * --------------------------------------------------------------------
 */ 

/**
 * @brief Имя индентификатора фильтров в HPM формате
 */
#define HPM_WEIGHTS_STRID "filters"

/**
 * @brief Имя индентификатора смещений в HPM формате
 */
#define HPM_BIAS_STRID "biases"

/**
 * @brief Имя индентификатора коэффициентов активаций в HPM формате
 */
#define HPM_NEGSCALE_STRID "activation_coefficients"

/**
 * @brief Имя индентификатора коэффициентов масштабирования в HPM формате
 */
#define HPM_POSSCALE_STRID "scale"


/**
 * @brief Хэдер сообщения об исключении модуля
 */
#define ADDR_CHECKER_THROW_DESC "Address Checker Module error. "


/*
 * --------------------------------------------------------------------
 *                             Aliases
 * --------------------------------------------------------------------
 */ 

/**
 * @brief Формат хранения JSON данных
 */
using json_buffer_t = boost::property_tree::ptree;

/**
 * @brief Формат хранения данных об одном слое из Pickle log файла
 * @details Pickle converter после окнвертации формирует буффер 
 * с подсчитанными адресами весов и размерами данных.
 * 
 * Формат хранения данных:
 * layer_name_1\n
 * \tdata_type *addr* *size*
 * \tdata_type *addr* *size*
 * ...
 * layer_name_2\n
 * \tdata_type *addr* *size*
 * \tdata_type *addr* *size*
 * ...
 * 
 * Наиболее оптимальный формат хранения данных в таком случае будет:
 * hashtable(str -> hashtable(str -> pair(int, int)))
 * Наиболее часто используемая операция - поиск по строковому ключу.
 */
using pickle_ld_t = std::unordered_map<std::string, std::pair<int, int>>;


/**
 * @brief Формат хранения информации из Pickle log
 */
using pickle_buffer_t = std::unordered_map<std::string, pickle_ld_t>;



/*
 * --------------------------------------------------------------------
 *                             Модуль
 * --------------------------------------------------------------------
 */

/**
 * @brief Модуль, который проверяет соответствие адресов и размеров весов
 * в описании сети после конвертации весов из Pickle формата.
 * 
 * @details Модуль требует наличия этапа конвертации весов в пайплайне компиляции.
 * В противном случае будут использованы логи с последней конвертации весов.
 * 
 * Использование старых логов не гарантирует корректность работы. В случае возникновения ошибки
 * модуль залогирует ее в кэш статус бара и завершит работу с исключением.
 * 
 * @exception std::runtime_error Ошибка выполнения. Выбрасывает исключение во всех ситуациях
 * с некорректной работой при этом логируя ошибку в кэш статус буффера переданный в конструктор.
 * 
 */
class AddressCheckerModule : public Module 
{  

public:

    /**
     * @brief Конструктор инициализирует внутренние поля модуля.
     * При передаче конструктора настроек важно помнить, чтобы были проинициализированы
     * настройки данного модуля.
     * 
     * @param _settings  - Глоабальные настройки компиляции. Используется только часть с настройками модуля
     * @param status_bar - Кэш статус бара. Используется для логгирования процесса. ! Не вызывает деструктор объекта. !
     */
    explicit AddressCheckerModule(
        IN const GlobalSettings&    _settings, 
        IN       StatusBufferCache* status_bar
        ) : Module(status_bar, ADDR_CHECKER_THROW_DESC), settings(_settings.addr_checker) {};
    
    /**
     * @brief Удаляет объект и высвобождает ресурсы.
     * @details Объект лога высвобождается из управления без вызова деструктора лога.
     * То есть объект с логом не должен удаляться в данном месте.
     */
    ~AddressCheckerModule() 
    {
    
        log = nullptr; 
        delete log;
    
    };

    /**
     * @brief Запускает выполнение процесса проверки адресов и размеров весов.
     * 
     * @return exit_module_status - код возврата.
     */
    exit_module_status runProcess() override;


protected:

    /**
     * @brief Переопределение метода проверки корректности настроек
     */
    void checkSettingsCorrectness() const override;

private:

    /*
    * --------------------------------------------------------------------
    *                     Поля и члены-данные
    * --------------------------------------------------------------------
    */

    /**
     * @brief Настройки модуля
     */
    AddrCheckerSettings settings;

    /**
     * @brief Буффер для описания сети
     */
    json_buffer_t json_buffer;

    /**
     * @brief Буффер для хранения данных лога Pickle
     */
    pickle_buffer_t pickle_buffer;

    /**
     * @brief Объект обработчика Json формата
     */
    JsonHandler json_handler;


    /*
    * --------------------------------------------------------------------
    *                     Закрытые методы
    * --------------------------------------------------------------------
    */

    /**
     * @brief Чтение Pickle log файла.
     */
    void readPickleBuffer();

    /**
     * @brief Чтение Json описания сети.
     */
    void readJSON();

    /**
     * @brief Формирует пару корректных значений.
     * 
     * @param list_node - Узел куда будет записана новая пара в виде JSON списка.
     * @param new_value - Пара новых значений.
     */
    void correctPair(
        IN OUT boost::property_tree::ptree& list_node, 
        IN     const std::pair<int, int>& new_value
    ) const;
    
    
    /**
     * @brief Коррекция всех данных JSON описания.
     * @details Требует присутствия всех слоев из JSON файла в Pickle логе.
     */
    void correctData();
    
    /**
     * @brief Запись JSON файла с корректированными значениями
     */
    void dumpJSON();

};

#endif // _INCLDUE_MODULES_ADDRESSCHECKERMODULE_H_
