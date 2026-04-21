#include "Document.h"


Document::Document(size_t id, const std::string& name, const std::string& content)
    : id_(id), name_(name), content_(content) // Инициализируем поля
{

}

size_t Document::getId() const {
    return id_;      //  возвращаем значение приватного поля
}


const std::string& Document::getName() const {
    return name_;    // Возвращаем константную ссылку на поле name_
}


const std::string& Document::getContent() const {
    return content_; // Возвращаем константную ссылку на поле content_
}