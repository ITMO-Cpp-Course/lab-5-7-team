#pragma once

#include "InvertedIndex.hpp"
#include "Result.hpp"
#include <unordered_set>
#include <utility>

namespace lab_6
{

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
    InvertedIndex& index();
    void commit();
    bool isCommitted() const
    {
        return committed_;
    }

  private:
    IndexStore& store_;
    InvertedIndex draft_; // копия индекса
    bool committed_ = false;
};

} // namespace lab_6