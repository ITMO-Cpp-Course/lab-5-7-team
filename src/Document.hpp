#pragma once
#include <string>
namespace lab5::document_work
{
    class Document
    {
    public:
        Document(size_t id, const std::string& name, const std::string& text);

        size_t getId() const;
        const std::string& getName() const;
        const std::string& getText() const;

    private:
        size_t id_;
        std::string name_;
        std::string text_;
    };
} // namespace lab5::document_work