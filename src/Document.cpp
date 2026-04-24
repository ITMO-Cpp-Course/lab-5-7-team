#include "Document.hpp"

namespace lab5::document_work
{
Document::Document(size_t id, const std::string& name, const std::string& text)
    : id_(id), name_(name), text(text) // Инициализируем поля
{
}

size_t Document::getId() const
{
    return id_; //  возвращаем значение приватного поля
}

const std::string& Document::getName() const
{
    return name_; // Возвращаем константную ссылку на поле name_
}

const std::string& Document::getText() const
{
    return text; // Возвращаем константную ссылку на поле content_
}
} // namespace lab5::document_work