#pragma once
#include "Document.hpp"
#include "DocumentBuilder.hpp"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace lab5::document_work
{
class Document;
class DocumentBuilder;
struct Entry
{
    size_t index;
    size_t docId;
    Entry() : docId(0), index(0);
    Entry(size_t Id, size_t ind) : docId(Id), index(ind);
}; // каждому слову можем вызвать вектор, который сопостовляется со структорой и имеет свою пару

class InvertedIndex
{
  public:
    void addDocument(const Document& document);
    void removeDocument(size_t Id);
    // пользователь удаляет документ по его айди
    std::vector<Entry> search(const std::string& word) const; // принимет одно слово
    // возвращает список пар (айди документа, количество слов в этом документе)
    int WordInDocument(const std::string& word, size_t Id) const;
    // ищет слово только в одном документе

  private:
    std::unordered_map<std::string, std::vector<Entry>> invertedIndex_;
    // хранилище пар для каждого слова
    std::unordered_map<int, std::shared_ptr<Document>> documents_;
    // хранилище документов по их айди
};

} // namespace lab5::document_work