#pragma once

#include "InvertedIndex.hpp"
#include "IndexError.hpp"
#include "Result.hpp"
#include <unordered_set>
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
     Result<UpdateTransaction> beginTransaction();



  private:
    friend class UpdateTransaction;
    InvertedIndex invertedIndex_;
    std::unordered_set<size_t> docIds_;
    bool transactionActive_ = false;   // true, если существует активная транзакци
};
} // namespace lab_6
