#include "InvertedIndex.hpp"
#include <string>
#include <vector>

namespace InvertedIndex
{
void addDocument(const Document& document)
{
    int Id = document.getId();
    const std::vector<std::string>& words = document.getWords(); // методы класса Document
    documents_[docId] = std::make_shared<Document>(document);
    // сохраняем документ внутри хранилище documents_
    for (const std::string& word : words) // проходим по каждому слову из списка
    {
        std::vector<Entry>& entries = InvertedIndex_[word]; // каждое слово добавляем в хранилище
        bool found = false;
        for (Entry& entry : entries) // берем каждый entry из entries
        {                            // работаем с ссылкой на оригинальную запись
            if (entry.Id == Id)
            {
                found == true;
                entry.count++;
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

void removeDocument(int Id)
{
    auto it = documents_.find(Id); // номер ячейки, где лежит документ
    if (it == documents_.end())
    {
        return; // выход из метода
    }
    std::shared_ptr<Document> Ptr = it->second;
    // умный указатель на Document, чтобы работать со словами после удаления
    for (const std::string& word : words)
    {
        auto wordDoc = InvertedIndex_[word];
        std::vector<Entry>& entries = wordDoc->second;
        // передаем ссылку на вектор, который содержит пары айди-индекс
        entries.erase(std::remove_if(entries.begin(), entries.end(),
                                     // пробегает от начала до конца в entrues
                                     [Id](const Entry& entry) {
                                         return entry.Id == Id;
                                     }), // если запись для этого айди есть, remove_if перемещает ее в конец
                      entries.end());
        // erase удаляет все элементы, перемещенные в конец вектора
        if (entries.empty())
        { // если вектор (пара айди-индекс) пуста (индекс 0), то удаляем ее
            InvertedIndex_.erase(wordDoc);
        }
    }
    documents_.erase(it);
}

std::vector<Entry> search(const std::string& word) const
{
    auto it = InvertedIndex_.find(word);
    if (it != InvertedIndex_.end())
    {
        return it->second;
    } // если слово найдено, возвращаем vector<Entry>: пара айди-индекс
    return {};
}

int WordInDocument(const std::string& word, int Id) const
{
    auto it = InvertedIndex_.find(word); // находим итератор для слова
    if (it == InvertedIndex_.end())
    {
        return 0;
    }
    const std::vector<Entry>& entries = it->second;
    for (const Entry& entry : entries) // проходим по всем парам айди-индекс для слова
    {
        if (entry.Id == Id)
        {
            return entry.index; // айди совпадает с нашим - выдаем для него индекс
        }
    }
    return 0;
}

} // namespace InvertedIndex