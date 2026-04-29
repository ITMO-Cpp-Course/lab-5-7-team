#pragma once

#include "InvertedIndex.hpp"
#include "IndexError.hpp"
#include "Result.hpp"

#include <memory>
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
     Result<UpdateTransaction> beginTransaction();;



  private:
    std::unique_ptr<InvertedIndex> index_;
    bool transactionActive_ = false;   // true, если есть незавершённая транзакция
    void rollbackTransaction();   // добавляем метод отката для сброса флага
    void commitTransaction(std::unique_ptr<InvertedIndex> newIndex);   // Внутренний метод для транзакции
    friend class UpdateTransaction;
};
} // namespace lab_6
