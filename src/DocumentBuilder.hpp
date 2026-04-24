#pragma once

#include <functional>
#include <string>
#include <vector>

namespace lab5::document_work
{

class DocumentBuilder
{
  public:
    DocumentBuilder() = default;
    Document Build(size_t id, const std::string& name, const std::string& content);

    std::string ToLower(const std::string& text) const; // нижний регистр

    std::string ToUpper(const std::string& text) const; // верхний регистр

    std::string ToTitleWord(const std::string& text) const; // первые буквы заглавные

    std::vector<std::string> SplitToWords(const std::string& text) const; // разбивка на слова
};

} // namespace lab5::document_work
