#pragma once

#include "Document.hpp"
#include <functional>
#include <string>
#include <vector>

namespace lab_6
{

class DocumentBuilder
{
  public:
    DocumentBuilder() = default;
    static Document Build(size_t id, const std::string& name, const std::string& content);

    static std::string ToLower(const std::string& text); // нижний регистр

    static std::string ToUpper(const std::string& text); // верхний регистр

    static std::string ToTitleWord(const std::string& text); // первые буквы заглавные

    static std::vector<std::string> SplitToWords(const std::string& text); // разбивка на слова
};

} // namespace lab_6
