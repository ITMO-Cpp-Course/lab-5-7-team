#include "InvertedIndex.hpp"
#include "DocumentBuilder.hpp"
#include <algorithm>
#include <string>
#include <vector>
namespace lab5::document_work
{
void InvertedIndex::addDocument(const Document& document)
{
    size_t Id = document.getId();
    std::string lower = DocumentBuilder::ToLower(document.getText());
    auto words = DocumentBuilder::SplitToWords(lower);

    // берем текст и сразу переводим в нижний регистр
    documents_[Id] = std::make_shared<Document>(document);
    // сохраняем документ внутри хранилище documents_
    for (const std::string& word : words) // проходим по каждому слову из списка
    {
        std::vector<Entry>& entries = invertedIndex_[word]; // каждое слово добавляем в хранилище
        bool found = false;
        for (Entry& entry : entries) // берем каждый entry из entries
        {                            // работаем с ссылкой на оригинальную запись
            if (entry.docId == Id)
            {
                found = true;
                entry.index++;
                break;
            }
        }
        if (!found)
        {
            entries.push_back(Entry(Id, 1));
            // стандартный метод добавления новой пары в конец вектора
        }
    }
}

void InvertedIndex::removeDocument(size_t Id)
{
    auto it = documents_.find(Id); // номер ячейки, где лежит документ
    if (it == documents_.end())
    {
        return; // выход из метода
    }
    std::shared_ptr<Document> Ptr = it->second;
    std::string lower = DocumentBuilder::ToLower(Ptr->getText());
    auto words = DocumentBuilder::SplitToWords(lower);

    for (const std::string& word : words)
    {
        auto wordDoc = invertedIndex_.find(word);
        if (wordDoc != invertedIndex_.end())
        {
            std::vector<Entry>& entries = wordDoc->second;
            // передаем ссылку на вектор, который содержит пары айди-индекс
            entries.erase(std::remove_if(entries.begin(), entries.end(),
                                         // пробегает от начала до конца в entrues
                                         [Id](const Entry& entry) {
                                             return entry.docId == Id;
                                         }), // если запись для этого айди есть, remove_if перемещает ее в конец
                          entries.end());
            // erase удаляет все элементы, перемещенные в конец вектора
            if (entries.empty())
            { // если вектор (пара айди-индекс) пуста (индекс 0), то удаляем ее
                invertedIndex_.erase(wordDoc);
            }
        }
    }
    documents_.erase(it);
}

std::vector<Entry> InvertedIndex::search(const std::string& word) const
{
    auto it = invertedIndex_.find(word);
    if (it != invertedIndex_.end())
    {
        return it->second;
    } // если слово найдено, возвращаем vector<Entry>: пара айди-индекс
    return {};
}

size_t InvertedIndex::WordInDocument(const std::string& word, size_t Id) const
{
    auto it = invertedIndex_.find(word); // находим итератор для слова
    if (it == invertedIndex_.end())
    {
        return 0;
    }
    const std::vector<Entry>& entries = it->second;
    for (const Entry& entry : entries) // проходим по всем парам айди-индекс для слова
    {
        if (entry.docId == Id)
        {
            return entry.index; // айди совпадает с нашим - выдаем для него индекс
        }
    }
    return 0;
}

} // namespace lab5::document_work