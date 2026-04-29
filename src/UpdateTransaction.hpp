#pragma once
#include "Result.hpp"
#include <memory>
#include <vector>

namespace lab_6
{
class InvertedIndex;
class Document;
struct Entry;
class IndexStore;

class UpdateTransaction
{
  public:
    explicit UpdateTransaction(IndexStore& store);

    UpdateTransaction(const UpdateTransaction&) = delete;
    UpdateTransaction& operator=(const UpdateTransaction&) = delete;

    UpdateTransaction(UpdateTransaction&& other) noexcept;
    UpdateTransaction& operator=(UpdateTransaction&& other) noexcept;

    ~UpdateTransaction();

    // Операции над клоном
    Result<void> addDocument(const Document& doc);
    Result<void> removeDocument(size_t docId);
    Result<std::vector<Entry>> search(const std::string& word) const;

    // Фиксация
    Result<void> сommit();

  private:
    IndexStore* store_;
    std::unique_ptr<InvertedIndex> clone_;
    bool committed_;
};
} // namespace lab_6