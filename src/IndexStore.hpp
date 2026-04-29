#pragma once

#include "InvertedIndex.hpp"
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
    IndexStore() = default;
    Result<void> addDocument(const Document& doc);
    Result<void> removeDocument(size_t docId);
    Result<std::vector<Entry>> search(const std::string& word) const;
    Result<size_t> wordCount(const std::string& word, size_t docId) const;

    // Транзакция
    UpdateTransaction beginTransaction();

    // Внутренний метод для транзакции
    void assignIndex(std::unique_ptr<InvertedIndex> newIndex);

  private:
    std::unique_ptr<InvertedIndex> index_;
};
} // namespace lab_6
