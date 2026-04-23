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

    std::string ToLower(const std::string& text) const;

    std::string ToUpper(const std::string& text) const;

    std::string ToTitleWord(const std::string& text) const;

    std::vector<std::string> SplitToWords(const std::string& text) const;
};

} // namespace lab5::document_work
