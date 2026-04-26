#include "DocumentBuilder.hpp"
#include "Document.hpp"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

namespace lab5::document_work
{
Document DocumentBuilder::Build(size_t id, const std::string& name, const std::string& content)
{
    return Document(id, name, content);
}

std::string DocumentBuilder::ToLower(const std::string& text)
{
    std::string result = text;
    for (char& c : result)
    {
        c = std::tolower(static_cast<unsigned char>(c));
    }
    return result;
}

std::string DocumentBuilder::ToUpper(const std::string& text)
{
    std::string result = text;
    for (char& c : result)
    {
        c = std::toupper(static_cast<unsigned char>(c));
    }
    return result;
}

std::string DocumentBuilder::ToTitleWord(const std::string& text)
{
    std::string result = text;
    bool new_word = true;

    for (char& c : result)
    {
        if (std::isalpha(static_cast<unsigned char>(c)))
        {
            if (new_word)
            {
                c = std::toupper(static_cast<unsigned char>(c));
                new_word = false;
            }
            else
            {
                c = std::tolower(static_cast<unsigned char>(c));
            }
        }
        else
        {
            new_word = true;
        }
    }

    return result;
}

std::vector<std::string> DocumentBuilder::SplitToWords(const std::string& text)
{
    std::vector<std::string> words;
    std::stringstream ss(text);
    std::string word;

    while (ss >> word)
    {
        word.erase(
            std::remove_if(word.begin(), word.end(),
                           [](char c) { return std::ispunct(static_cast<unsigned char>(c)) && c != '-' && c != '\''; }),
            word.end());

        if (!word.empty())
        {
            words.push_back(word);
        }
    }

    return words;
}
} // namespace lab5::document_work
