#pragma once
#include <string>

class Document {
public:

    Document(size_t id, const std::string& name, const std::string& content);

    size_t getId() const; // const в конце означает, что метод не изменяет поля объекта, только читает данные
    const std::string& getName() const;
    const std::string& getContent() const;

private:
    size_t id_;            // Уникальный идентификатор
    std::string name_;     // Имя документа
    std::string content_;  // Содержимое текста
};
