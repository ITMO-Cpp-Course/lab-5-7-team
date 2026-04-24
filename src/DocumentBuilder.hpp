#pragma once

#include "Document.hpp"
#include <functional>
#include <string>
#include <vector>
namespace lab5::document_work
{

class DocumentBuilder
{
  public:
    DocumentBuilder() = default;
    Document Build(size_t id, const std::string& name, const std::string& text);

    static std::string ToLower(const std::string& text);

    static std::string ToUpper(const std::string& text);

    static std::string ToTitleWord(const std::string& text);

    static std::vector<std::string> SplitToWords(const std::string& text);
};

} // namespace lab5::document_work
