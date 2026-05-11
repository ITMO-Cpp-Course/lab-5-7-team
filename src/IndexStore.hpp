#pragma once

#include "IndexError.hpp"
#include "InvertedIndex.hpp"
#include "Result.hpp"
#include <memory>
#include <unordered_set>
#include <vector>

namespace lab_6
{
class Document;
struct Entry;
class UpdateTransaction;

class IndexStore
{
  public:
    IndexStore();
    Result<void> addDocument(const Document& doc);
    Result<void> removeDocument(size_t docId);
    Result<std::vector<Entry>> search(const std::string& word) const;
    Result<size_t> WordInDocument(const std::string& word, size_t docId) const;

    // Транзакция
    Result<UpdateTransaction> beginTransaction();

  private:
    friend class UpdateTransaction;
    InvertedIndex invertedIndex_;
    std::unordered_set<size_t> docIds_;// множество идентификаторов документов для быстрой проверки существования
    bool transactionActive_ = false; // true, если существует активная транзакци
};//Ключ — строка-слово (в нижнем регистре).
//Значение — вектор «вхождений» (структур Entry).
//docId — идентификатор документа,
//count (или index в твоей терминологии) — количество раз, которое слово встретилось в этом документе.
} // namespace lab_6
