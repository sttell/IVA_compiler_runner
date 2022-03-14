#ifndef _INCLUDE_JSONHANDLER_H_
#define _INCLUDE_JSONHANDLER_H_

#include "path.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <fstream>
#include <string>

#define JSON_HANDLER_THROW_DESC "JSON Handler Error. "
#define JSON_HANDLER_HW_SPECIFIER "_![hardwrite]"

// Тип узла в формате JSON
enum class NodeType {
    Map,
    List,
    Value,
    Root
};

// Тип поля в формате JSON
enum class PropertyType {
    Number,
    Bool,
    String
};

// Функции для работы с JSON форматом инкапсулированные в класс. Основано на базе Boost::property_tree
class JsonHandler {

public:
    // Базовые конструктор и деструктор.
    JsonHandler() : indentation_level(0), indentation_shift(0) {}
    JsonHandler(size_t indent) : indentation_level(0), indentation_shift(indent) {};
    ~JsonHandler() {}

    // Считывание JSON файла в буффер по ссылке.
    void read(const Path& input_path, boost::property_tree::ptree& buffer) const;
    
    // Запись буффера в JSON формате
    void dump(const Path& out_path, const boost::property_tree::ptree& buffer, int indent=-1);

private:
    size_t indentation_level;
    size_t indentation_shift;

    // Проверка для жесткой записи в файл(без прмения проверки типа)
    bool isHardWriteElement(const std::string& str) const;

    // Определение типа записываемого поля
    PropertyType getPropertyType(const std::string& property_str) const;

    // Определение типа переданного узла
    NodeType getNodeType(const boost::property_tree::ptree& node) const;
    
    // Запись имени узла при его наличии
    void dumpNodeName(const std::string& name, std::ofstream& fout) const;

    // Запись узла-хэш таблицы
    void dumpMap(const boost::property_tree::ptree& node, std::ofstream& fout, NodeType parent_type);

    // Запись узла-списка
    void dumpList(const boost::property_tree::ptree& node, std::ofstream& fout, NodeType parent_type);
    
    // Запись конечного поля
    void dumpProperty(const boost::property_tree::ptree& node, std::ofstream& fout, NodeType parent_type) const;
    
    // Запись узла
    void dumpNode(const boost::property_tree::ptree& node, std::ofstream& fout, NodeType parent_type);
};

#endif