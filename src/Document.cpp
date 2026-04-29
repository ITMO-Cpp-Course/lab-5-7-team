#include "Document.hpp"
namespace lab_6
{
Document::Document(size_t id, const std::string& name, const std::string& text)
    : id_(id), name_(name), text_(text) // Инициализируем поля
{
}

size_t Document::getId() const
{
    return id_;
}

const std::string& Document::getName() const
{
    return name_;
}

const std::string& Document::getText() const
{
    return text_;
}
} // namespace lab_6