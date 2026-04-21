#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace InvertedIndex
{
class Document;
struct Entry
{
    size_t index;
    int Id;
}; // каждому слову можем вызвать вектор, который сопостовляется со структорой и имеет свою пару

class InvertedIndex
{
  public:
    void addDocument(const Document& document);
    void removeDocument(int Id);
    // пользователь удаляет документ по его айди
    std::vector<Entry> search(const std::string& word) const; // принимет одно слово
    // возвращает список пар (айди документа, количество слов в этом документе)
    int WordInDocument(const std::string& word, int Id) const;
    // ищет слово только в одном документе

  private:
    std::unordered_map<std::string, std::vector<Entry>> InvertedIndex_;
    // хранилище пар для каждого слова
    std::unordered_map<int, std::shared_ptr<Document>> documents_;
    // хранилище документов по их айди
};

} // namespace InvertedIndex