#pragma once
#include <string>

namespace lab5::document_work
{
class Document
{
  public:
    Document(size_t id, const std::string& name, const std::string& text);

    size_t getId() const; // const в конце означает, что метод не изменяет поля объекта, только читает данные
    const std::string& getName() const;
    const std::string& getText() const;

  private:
    size_t id_;        // Уникальный идентификатор
    std::string name_; // Имя документа
    std::string text_; // Содержимое текста
};
} // namespace lab5::document_work
